#ifndef _ONEGUI_WIDGET
#define _ONEGUI_WIDGET
#include <iostream>
#include <list/list.hpp>
#include <properties/property.hpp>
#include <widgets/item.hpp>

class Widget : public List
{
    public:
        Widget();
        Widget(int x, int y, int width, int height, void *widgetData, Property *properties);
        Widget(WidgetItem *item);
        virtual void draw();
        virtual void onClick();
};
#endif