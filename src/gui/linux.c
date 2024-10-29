#include <gui/linux.h>
#include <properties/properties.h>

/*
hide_toolbar: hides close, minimize, and maximize toolbar
@param window: the window itself
@param display: display being used
*/
void hide_toolbar(Window window, Display *display)
{
    //Create variables necessary for modifying X11 properties
    Atom atom = XInternAtom(display, "_MOTIF_WM_HINTS", false);
    if((&atom) == NULL)
    {
        printf("hide_toolbar(): failed to hide close, minimize, and maximize buttons.\n");
        return;
    }

    //Create the hints
    struct
    {
        unsigned long flags;
        unsigned long functions;
        unsigned long decorations;
        long mode;
        unsigned long status;
    } hints = {2, 0, 0, 0, 0};

    //Now apply changes
    XChangeProperty(display, window, atom, atom, 32, PropModeReplace, (unsigned char *) &hints, 5);
}

/*
make_display: Creates a display widget with window as child
@param x: x position
@param y: y position
@param width: width
@param length: length
@param properties: list of GUI-related properties
@returns new window widget
*/
widget_t *make_display(int x, int y, int width, int length, property_t *properties)
{
    //Create variables for making a new display and window
    Display *display;
    Window window;
    XEvent event;
    int screen;

    //Open connection to X server
    display = XOpenDisplay(NULL);
    if(display == NULL)
    {
        printf("error: make_display(): failed to open display.\n");
        exit(EXIT_FAILURE);
    }

    //Create a window
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), x, y, width, length, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    //Now check if we should hide the toolbar
    if(get_bool(properties, HIDE_TOOLBAR_PROPERTY))
    {
        //Hide the window toolbar
        printf("Hiding toolbar...");
        hide_toolbar(window, display);
    }

    //Now make a widget for the display and window
    widget_t *displayWidget = build_widget(x, y, width, length, (void *) display, NULL, NULL);
    widget_t *windowWidget = build_widget(x, y, width, length, (void *) window, NULL, NULL);
    add_child(displayWidget, windowWidget);
    add_child(displayWidget, build_widget(x, y, width, length, (void *) &event, NULL, NULL));
    add_child(displayWidget, build_widget(x, y, width, length, (void *) screen, NULL, NULL));

    //And return the display widget
    return displayWidget;
}

/*
show_window: Starts showing window
@param display: display widget containing window
*/
int show_window(widget_t *display)
{
    //Get the display and window
    Display *disp = (Display *) display->widgetData;
    Window w = (Window) display->childWidgets[0]->widgetData;
    XEvent event;

    //And get the screen
    intptr_t screen = (intptr_t) (display->childWidgets[2]->widgetData);
    
    //Now initialize properties
    property_t *properties = mk_property("Root", NULL);

    //And show the window
    XSelectInput(disp, w, ExposureMask | KeyPressMask);
    XMapWindow(disp, w);

    //And run the start function
    int res = start(display);
    while(res != EXIT_FAILURE)
    {
        //Get next event
        XNextEvent(disp, &event);

        //Go through all child widgets and draw them if possible
        for(int index = 0; index < display->numChildren; index++)
        {
            //Get current child widget
            widget_t *child = display->childWidgets[index];
            //Try to draw current widget
            if(child->draw != NULL)
            {
                child->draw(display, child);
            }
        }

        //And run the update function
        res = update(display);
    }


    //We stopped showing
    XCloseDisplay(disp);

    //Return results of start operation
    return res;
}
