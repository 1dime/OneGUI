#ifndef _WIDGETS_LINUX_BUTTON_H_
#define _WIDGETS_LINUX_BUTTON_H_
#include <gui/widget.h>
#include <gui/linux.h>


/*
draw_button: draws a button widget on a display
@param display: display widget
@param button: the button widget
@returns nothing by default
*/
void *draw_button(widget_t *display, widget_t *button);

/*
on_click: ran when a button widget is clicked
@param display: the display widget
@param button: button widget
@returns nothing by default
*/
void *on_click(widget_t *display, widget_t *button);

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
widget_t *mk_button(widget_t *display, const char *text, int x, int y, int width, int height, widget_t *parent);

#endif