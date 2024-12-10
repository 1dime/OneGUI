#ifndef _ONEGUI_LIST
#define _ONEGUI_LIST
#include <list/item.hpp>

class List
{
    private:
        bool nextRan;
        bool previousRan;
    protected:
        ListItem *head;
    public:
        List();
        List(ListItem *head);
        ListItem *getLeafItem();
        ListItem *getRootItem();
        void addItem(ListItem *item);
        ListItem *getItem();
        void setItem(ListItem *item);
        ListItem *next();
        void next(ListItem *nextNode);
        ListItem *previous();
        void previous(ListItem *prevNode);
};
#endif