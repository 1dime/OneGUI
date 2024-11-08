#ifndef _WIDGET_H_
#define _WIDGET_H_
#include <properties/properties.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct widget widget_t;
struct widget
{
    int x, y;
    int width, height;
    int numChildren;
    void *widgetData;
    void *(*widgetFunction)(widget_t *, widget_t *); //Any click on widget function
    void *(*draw)(widget_t *, widget_t *); //Draws widget on screen
    widget_t **childWidgets;
    property_t *properties; //Set by implementation

    widget_t *next; //Node next to node
    widget_t *prev; //Node before node
};

/*
build_widget: creates a new widget
@param x: x position
@param y: y position
@param width: width
@param height: length
@param widgetData: data such as window label, text label, etc
@param widgetFunction: function to be ran if widget is something like a button
@param drawFunction: function to be ran to draw widget on screen
@returns new widget
*/
widget_t *build_widget(int x, int y, int width, int height, void *widgetData, void *widgetFunction, void *drawFunction);

/*
add_child: Adds child widget to parent widget
@param parent: parent widget
@param child: child widget
*/
void add_child(widget_t *parent, widget_t *child);

/*
add_node: Adds widget to widget tree
@param tree: widget tree
@param node: node to be added
@returns modified tree
*/
widget_t *add_node(widget_t *tree, widget_t node);

/*
get_first: Gets first widget in widget tree
@param tree: widget tree
@returns first widget
*/
widget_t *get_first(widget_t *tree);

/*
find_raw: looks for a widget in a widget tree
@param tree: widget tree
@param x: x position of widget
@param y: y position of widget
@param width: width of widget
@param height: height of widget
@returns widget if found, null if not
*/
widget_t *find_raw(widget_t *tree, int x, int y, int width, int height);
#endif