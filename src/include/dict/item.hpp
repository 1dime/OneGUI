#ifndef _ONEGUI_DICT_ITEM
#define _ONEGUI_DICT_ITEM
#include <string>
#include <list/item.hpp>

struct DictItem : public ListItem
{
    std::string k;
    void *v;
    DictItem(std::string k, void *v)
    {
        this->k = k;
        this->v = v;
    }
};

#endif