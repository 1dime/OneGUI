#ifndef _ONEGUI_ITEM
#define _ONEGUI_ITEM

class ListItem
{
    private:
        void *data;
    public:
        ListItem();
        ListItem(void *data);
        ListItem *next;
        ListItem *previous;
        void *getData();
        void setData(void *data);
};
#endif