#ifndef _LINUX_H_
#define _LINUX_H_
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <gui/widget.h>

/*
start: Initialize your application
@param display: Display widget
@returns 0 if successful, 1 if failed
*/
extern int start(widget_t *display);

/*
update: draws every frame
@param display: Display widget
*/
extern int update(widget_t *display);

/*
make_display: Creates a window widget
@param x: x position
@param y: y position
@param width: width
@param height: length
@returns new window widget
*/
widget_t *make_display(int x, int y, int width, int length, property_t *properties);

/*
show_window: Starts showing window
@param display: display widget containing window
*/
int show_window(widget_t *display);
#endif