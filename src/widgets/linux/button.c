#include <widgets/linux/button.h>


/*
draw_button: draws a button widget on a display
@param display: display widget
@param button: the button widget
@returns nothing by default
*/
void *draw_button(widget_t *display, widget_t *button)
{
    //Get display, window, and GC
    Display *disp = (Display *) display->widgetData;
    Window wind = (Window) display->childWidgets[0]->widgetData;
    GC gc = DefaultGC(disp, (int) display->childWidgets[2]->widgetData);
    const char *text = (const char *) button->widgetData;

    //Calculate center for x and y, to add button to
    int x = button->x;
    int y = button->y;
    int centerX = (x + button->width) / 2;
    int centerY = (y + button->height) / 2;
    //Now, draw a rectangle
    XDrawRectangle(disp, wind, gc, button->x, button->y, button->width, button->height);
    XDrawString(disp, wind, gc, centerX, centerY, text, strlen(text));
}

/*
on_click: ran when a button widget is clicked
@param display: the display widget
@param button: button widget
@returns nothing by default
*/
void *on_click(widget_t *display, widget_t *button)
{
    //Button was clicked, print that
    printf("Button was clicked.\n");
}

/*
mk_button: Creates a new button at given x and y positions
@param display: the display widget
@param text: text of button
@param x: button x position
@param y: y position
@param width: width of entire button
@param height: height of entire button
@param parent: parent widget
@returns new button widget
*/
widget_t *mk_button(widget_t *display, const char *text, int x, int y, int width, int height, widget_t *parent)
{
    //Create a new button widget
    widget_t *button = build_widget(x, y, width, height, text, on_click, draw_button);
    //Add button widget to parent if parent is set
    if(parent != NULL)
    {
        //Add button as child to parent
        add_child(parent, button);
    }

    //Now return the new button widget
    return button;
}