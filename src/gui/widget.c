#include <gui/widget.h>

/*
build_widget: creates a new widget
@param x: x position
@param y: y position
@param width: width
@param length: length
@param widgetData: data such as window label, text label, etc
@param widgetFunction: function to be ran if widget is something like a button
@param drawFunction: function to be ran to draw widget on screen
@returns new widget
*/
widget_t *build_widget(int x, int y, int width, int length, void *widgetData, void *widgetFunction, void *drawFunction)
{
    widget_t *widget = (widget_t *) malloc(sizeof(widget_t));
    if(widget == NULL)
    {
        printf("error: build_widget(): memory allocation failure.\n");
        exit(EXIT_FAILURE);
    }
    widget->x = x;
    widget->y = y;
    widget->scaleX =  width;
    widget->scaleY = length;
    widget->numChildren = 0;
    widget->childWidgets = (widget_t **) malloc((widget->numChildren + 1) * sizeof(widget_t *));
    widget->widgetData = widgetData;
    widget->widgetFunction = widgetFunction;
    widget->draw = drawFunction;
    
    return widget;
}


/*
add_child: Adds child widget to parent widget
@param parent: parent widget
@param child: child widget
*/
void add_child(widget_t *parent, widget_t *child)
{
    //Make sure both parent and child are set
    if(parent == NULL || child == NULL)
    {
        printf("error: add_child(): either parent or child widgets are empty.\n");
        exit(EXIT_FAILURE);
    }
    
    parent->childWidgets[parent->numChildren] = child;
    parent->numChildren += 1;
}