#include <list/list.hpp>

/*
List: default constructor
*/
List::List()
{
    //Set the head pointer
    this->head = new ListItem();
}

/*
List: constructor with head pointer set
@param head: head pointer
*/
List::List(ListItem *head)
{
    //Set head pointer and make sure it is valid
    this->head = head;
    if(this->head == nullptr)
        this->head = new ListItem();
}

/*
getLeafItem: gets leaf item from list
@returns leaf item (leaf node)
*/
ListItem *List::getLeafItem()
{
    //Find the leaf item
    ListItem *headCopy = this->head;
    while(headCopy->next != nullptr)
    {
        headCopy = headCopy->next;
    }

    return headCopy;
}

/*
getRootItem: gets root item from list
@returns root item (root node)
*/
ListItem *List::getRootItem()
{
    //Find the root item
    ListItem *headCopy = this->head;
    while(headCopy->previous != nullptr)
    {
        headCopy = headCopy->previous;
    }

    return headCopy;
}

/*
addItem: adds item to list
@param item: list item to be added
*/
void List::addItem(ListItem *item)
{
    this->head = this->getLeafItem();
    item->previous = this->head;
    this->head->next = item;
    this->head = this->head->next;
}


/*
getItem: gets current item
@returns current item
*/
ListItem *List::getItem()
{
    return this->head;
}

/*
setItem: sets current item
@param item: new current item
*/
void List::setItem(ListItem *item)
{
    this->head = item;
}

/*
next: gets next item
@returns next item
*/
ListItem *List::next()
{
    if(this->nextRan)
    {
        this->head = this->head->next;
    }
    this->nextRan = true;
    return this->head->next;
}

/*
next: sets next item to another
@param item: new next item
*/
void List::next(ListItem *item)
{
    this->head->next = item;
}

/*
previous: gets previous item
@returns previous item
*/
ListItem *List::previous()
{
    if(this->previousRan)
    {
        this->head = this->head->previous;
    }
    this->previousRan = true;
    return this->head->previous;
}

/*
previous: sets previous item
@param item: new previous item
*/
void List::previous(ListItem *item)
{
    this->head->previous = item;
}