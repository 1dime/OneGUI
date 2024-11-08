#ifndef _WIDGETS_LINUX_TEXT_H_
#define _WIDGETS_LINUX_TEXT_H_
#include <gui/widget.h>
#include <gui/linux.h>

/*
draw_text: Default function for drawing text
@param display: display widget
@param text: text to be drawn
@param x: x position
@param y: y position
@returns text widget
*/
void *draw_text(widget_t *display, widget_t *text_widget);

/*
mk_text: Creates a simple text widget
@param window: Window widget
@param text: Text widget displays
@param x: x-position
@param y: y-position
@param width: scale of widget, on x axis
@param height: scale of widget, on y axis
@param parent: Parent widget, if any
*/
widget_t *mk_text(widget_t *window, const char *text, int x, int y, int width, int height, widget_t *parent);
#endif