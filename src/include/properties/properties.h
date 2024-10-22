#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#define HIDE_TOOLBAR_PROPERTY "hideToolbar"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Properties for gui
typedef struct property property_t;
struct property
{
    char *key;
    void *value;
    property_t *nxt;
    property_t *prev;
};

/*
mk_property: Creates a new property
@param key: key associated with value
@param value: value assigned to key
@returns new property
*/
property_t *mk_property(const char *key, const void *value);

/*
final_property: Gets the last property in list
@param properties: linked list of properties
@returns final property
*/
property_t *final_property(property_t *properties);

/*
first_property: Gets first property in properties
@param properties: list of properties
@returns first property
*/
property_t *first_property(property_t *properties);

/*
set_value: Adds key and value to properties list
@param properties: list of properties
@param key: key associated with value
@param value: value assigned to key
@returns 0 if key and value are added, 1 if not or if it already exists
*/
int set_value(property_t *properties, const char *key, const void *value);

/*
get_value: Gets value associated with key
@param properties: list of properties
@param key: key to find
@returns value if key is in list, null if not
*/
void *get_value(property_t *properties, const char *key);

/*
get_bool: Gets boolean value associated with key
@param properties: list of properties
@param key: key to find
@returns true if key exists, false if not or if error occurred
*/
bool get_bool(property_t *properties, const char *key);

/*
get_int: Gets integer value associated with key
@param properties: properties list
@param key: key to look for in properties
@returns integer value stored
*/
intptr_t get_int(property_t *properties, const char *key);
#endif