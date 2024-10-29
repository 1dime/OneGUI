#include <widgets/linux/text.h>

/*
draw_text: Default function for drawing text
@param display: display widget
@param text: text to be drawn
@param x: x position
@param y: y position
@returns text widget
*/
void *draw_text(widget_t *display, widget_t *text_widget)
{
    //Get display and window from display widget
    Display *disp = display->widgetData;
    Window wind = display->childWidgets[0]->widgetData;
    GC gc = DefaultGC(disp, (int) display->childWidgets[2]->widgetData);

    //And draw the text
    XDrawString(disp, wind, gc, text_widget->x, text_widget->y, (char *) text_widget->widgetData, strlen((char *) text_widget->widgetData));
}

/*
mk_text: Creates a simple text widget
@param display: Display widget
@param text: Text widget displays
@param x: x-position
@param y: y-position
@param scaleX: scale of widget, on x axis
@param scaleY: scale of widget, on y axis
@param parent: Parent widget, if any
*/
widget_t *mk_text(widget_t *display, const char *text, int x, int y, int scaleX, int scaleY, widget_t *parent)
{
    //Get current display and window
    Display *disp = (Display *) display->widgetData;
    Window window = (Window) display->childWidgets[0]->widgetData;
    GC gc = DefaultGC(disp, (int) display->childWidgets[2]->widgetData);

    //Make a new widget
    widget_t *text_widget = build_widget(x, y, scaleX, scaleY, (void *) text, NULL, draw_text);
    
    //Add text widget to parent if it is set
    if(parent != NULL)
    {
        //Add text widget to parent
        add_child(parent, text_widget);
    }


    //And return the text widget
    return text_widget;
}