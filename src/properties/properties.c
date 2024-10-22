#include <properties/properties.h>

/*
mk_property: Creates a new property
@param key: key associated with value
@param value: value assigned to key
@returns new property
*/
property_t *mk_property(const char *key, const void *value)
{
    //Create a new property node
    property_t *property = (property_t *) malloc(sizeof(property_t));
    property->key = (char *) key;
    property->value = (void *) value;
    return property;
}

/*
final_property: Gets the last property in list
@param properties: linked list of properties
@returns final property
*/
property_t *final_property(property_t *properties)
{
    //Find the last property
    while(properties->nxt != NULL)
    {
        properties = properties->nxt;
    }

    return properties;
}

/*
first_property: Gets first property in properties
@param properties: list of properties
@returns first property
*/
property_t *first_property(property_t *properties)
{
    while(properties->prev != NULL)
    {
        properties = properties->prev;
    }

    return properties;
}

/*
set_value: Adds key and value to properties list
@param properties: list of properties
@param key: key associated with value
@param value: value assigned to key
@returns 0 if key and value are added, 1 if not or if it already exists
*/
int set_value(property_t *properties, const char *key, const void *value)
{
    //Make sure key is not in properties
    if(get_value(properties, key) != NULL)
    {
        //Key is in properties
        return 1;
    }

    //Create a new property node
    property_t *node = mk_property(key, value);
    //And add it to our properties
    node->prev = properties;
    properties->nxt = node;
    properties = properties->nxt;
    return 0;
}

/*
get_value: Gets value associated with key
@param properties: list of properties
@param key: key to find
@returns value if key is in list, null if not
*/
void *get_value(property_t *properties, const char *key)
{
    //Check if current property contains key
    if(strcmp(properties->key, key) == 0)
        //Return its value
        return properties->value;
    //Get the root of our properties
    property_t *root = first_property(properties);
    while(root->nxt != NULL)
    {
        if(strcmp(root->key, key) == 0)
        {
            return root->value;
        }

        //Go over to the next node
        root = root->nxt;
    }

    //Was not found
    return NULL;
}

/*
get_bool: Gets boolean value associated with key
@param properties: list of properties
@param key: key to find
@returns true if key exists, false if not or if error occurred
*/
bool get_bool(property_t *properties, const char *key)
{
    //Get boolean value associated with key
    return (bool)((bool *) get_value(properties, key));
}

/*
get_int: Gets integer value associated with key
@param properties: properties list
@param key: key to look for in properties
@returns integer value stored
*/
intptr_t get_int(property_t *properties, const char *key)
{
    //Get integer value associated with key
    return (intptr_t) get_value(properties, key);
}