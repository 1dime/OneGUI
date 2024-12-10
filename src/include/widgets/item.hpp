#ifndef _ONEGUI_WIDGET_ITEM
#define _ONEGUI_WIDGET_ITEM
#include <list/item.hpp>
#include <properties/property.hpp>

struct WidgetItem : public ListItem
{
    int x, y;
    int width, height;
    void *widgetData;
    Property *properties;
    
    WidgetItem(int x, int y, int width, int height, void *widgetData, Property *properties)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->widgetData = widgetData;
        this->properties = properties;
    }
};
#endif