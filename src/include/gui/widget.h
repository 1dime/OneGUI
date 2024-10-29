#ifndef _WIDGET_H_
#define _WIDGET_H_
#include <properties/properties.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct widget widget_t;
struct widget
{
    int x, y;
    int scaleX, scaleY;
    int numChildren;
    void *widgetData;
    void *(*widgetFunction)(widget_t *, widget_t *); //Any click on widget function
    void *(*draw)(widget_t *, widget_t *); //Draws widget on screen
    widget_t **childWidgets;
    property_t *properties; //Set by implementation
};

/*
build_widget: creates a new widget
@param x: x position
@param y: y position
@param scaleX: width
@param scaleY: length
@param widgetData: data such as window label, text label, etc
@param widgetFunction: function to be ran if widget is something like a button
@param drawFunction: function to be ran to draw widget on screen
@returns new widget
*/
widget_t *build_widget(int x, int y, int scaleX, int scaleY, void *widgetData, void *widgetFunction, void *drawFunction);

/*
add_child: Adds child widget to parent widget
@param parent: parent widget
@param child: child widget
*/
void add_child(widget_t *parent, widget_t *child);
#endif