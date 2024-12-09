#include <list/item.hpp>

/*
ListItem: default constructor
*/
ListItem::ListItem()
{
    this->next = nullptr;
    this->previous = nullptr;
}

/*
ListItem: constructor that sets data
@param data: item data
*/
ListItem::ListItem(void *data)
{
    this->next = nullptr;
    this->previous = nullptr;
    this->data = data;
}

/*
getData: gets item data
@returns item data
*/
void *ListItem::getData()
{
    return this->data;
}

/*
setData: sets item data
@param data: item data
*/
void ListItem::setData(void *data)
{
    this->data = data;
}