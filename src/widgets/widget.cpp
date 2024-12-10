#include <widgets/widget.hpp>

/*
Widget: default constructor
*/
Widget::Widget()
{
    this->head = new ListItem();
}

/*
Widget: creates widget with WidgetItem parameters
@param x: x position
@param y: y position
@param width: width of widget
@param height: height of widget
@param widgetData: any data the widget holds
@param properties: widget properties
*/
Widget::Widget(int x, int y, int width, int height, void *widgetData, Property *properties)
{
    WidgetItem *item = new WidgetItem(x, y, width, height, widgetData, properties);
    this->head = new ListItem((void *) item);
}

/*
Widget: creates widget using WidgetItem
*/
Widget::Widget(WidgetItem *item)
{
    this->head = new ListItem((void *) item);
}

/*
draw: draws widget on screen
*/
void Widget::draw()
{
    std::cout << "Drawing on screen" << std::endl;
}

/*
onClick: ran when widget is clicked
*/
void Widget::onClick()
{
    std::cout << "Clicked." << std::endl;
}