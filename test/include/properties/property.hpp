#ifndef _ONEGUI_PROPERTIES
#define _ONEGUI_PROPERTIES
#define TOOLBAR_ENABLED_PROPERTY "ToolbarEnabled"

#include <dict/item.hpp>
#include <fstream>
#include <iostream>
#include <list/list.hpp>
#include <properties/nlohmann/json.hpp>

using json = nlohmann::json;
class Property: public List
{
    private:
        json parseProperties(const char *path);
        bool readProperties(json propertiesData);
    public:
        Property();
        Property(const char *path);
        Property(const char *key, void *value);
        Property(DictItem *item);
        char *key();
        void *value();

        //All makes converting value() to a data type easier
        std::string valueAsString();
        int valueAsInt();
        float valueAsFloat();
        bool valueAsBoolean();
};
#endif