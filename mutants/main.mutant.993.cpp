#include <cassert>
#include <cstring>
#include <string>
#include <properties/property.hpp>
#include <widgets/widget.hpp>
#include <iostream>

void testDictItem();
void testListItem();
void testList();
void testJson();
void testProperty();
void testWidget();

int main()
{
    //Test the dict item class
    testDictItem();

    //And test the list item class
    testListItem();

    //Now test the list class
    testList();

    //And test the JSON class (by nlohmann)
    testJson();

    //Then test the property class
    testProperty();

    //And the widget class
    testWidget();
}

//Tests the DictItem structure
void testDictItem()
{
    //Create a new DictItem
    const char *key = "First";
    char *valueChars = "Value";
    std::string *value = new std::string(valueChars);
    DictItem *item = new DictItem(key, static_cast<void *>(value));

    //And test if the key and value match
    assert(("DictItem: key does not match stored", (std::strcmp(key, item->k.c_str())) == 0));
    assert(("DictItem: value does not match stored", (std::strcmp(value->c_str(), (static_cast<std::string *>(item->v))->c_str())) == 0));
}

//Tests ListItem structure
void testListItem()
{
    //Create two new list items
    char *firstListDataChars = "Test";
    char *secondListDataChars = "Test2";
    std::string *firstListData = new std::string(firstListDataChars);
    std::string *secondListData = new std::string(secondListDataChars);
    ListItem *firstItem = new ListItem(static_cast<void *>(firstListData));
    ListItem *secondItem = new ListItem(static_cast<void *>(secondListData));

    //Add second item to first
    firstItem->next = secondItem;

    //Now test if the second item was added
    assert(("ListItem: failed to add second list item to first", (firstItem->next == secondItem)));
    
    //And test the first item's parameters
    assert(("ListItem: First Item: data is not the same", (std::strcmp(firstListData->c_str(), (static_cast<std::string *>(firstItem->getData())->c_str())) == 0)));

    //And the second item's parameters
    assert(("ListItem: Second Item: data is not the same", (std::strcmp(secondListData->c_str(), (static_cast<std::string *>(secondItem->getData())->c_str())) == 0)));
}

//Checks if a list was added
bool listAdded(List *head, List *list)
{
    //Get items from both lists
    ListItem *headItem = (ListItem *) head->getItem();
    ListItem *listItem = (ListItem *) list->getItem();

    //And return if they are equal
    return std::strcmp((static_cast<std::string *>(headItem->getData()))->c_str(),
                    (static_cast<std::string *>(listItem->getData()))->c_str()) == 0;
}

//Tests List class
void testList()
{
    //Create the parameters for two lists
    char *firstListData = "First";
    char *secondListData = "Second";
    std::string *firstListString = new std::string(firstListData);
    std::string *secondListString = new std::string(secondListData);

    //And create two lists
    List *firstList = new List(new ListItem(static_cast<void *>(firstListString)));
    List *secondList = new List(new ListItem(static_cast<void *>(secondListString)));

    //Now add second list to first
    firstList->addItem(secondList->getItem());

    //And test if the second list was added
    assert(("List: failed to add second list to first", (listAdded(firstList, secondList))));
    firstList->setItem(firstList->getItem()->previous);

    //Then test first list's parameters
    assert(("List: First List: data is not the same", (std::strcmp(firstListString->c_str(), (static_cast<std::string *>(firstList->getItem()->getData()))->c_str())) == 0));

    //And test second list's parameters
    assert(("List: Second List: data is not the same", (std::strcmp(secondListString->c_str(), (static_cast<std::string *>(secondList->getItem()->getData()))->c_str())) == 0));
}

//Tests nlohmann's JSON
void testJson()
{
    //Create a simple key and value for json
    char *key = "Key";
    char *value = "Value";

    //And add them to new json element
    nlohmann::json data;
    data[key] = value;

    //Now test the data
    assert(("Json: key does not match", (data.contains(key) == true)));
    assert(("Json: value does not match", ((std::strcmp(value, data[key].get<std::string>().c_str()) == 0))));
}

//Tests the Property class
void testProperty()
{
    //Create a basic property
    char *key = "Cartoonish";
    std::string *value = new std::string("Test");
    Property *property = new Property();
    property->addItem(new DictItem(key, static_cast<void *>(value)));

    //Make sure property key and value match
    assert(("Property: Key does not match", (std::strcmp(key, property->key()) == 0)));
    assert(("Property: Value does not match", (std::strcmp(value->c_str(), property->valueAsString().c_str()) == 0)));
}

//Returns if a widget was added to a widget list
bool widgetAdded(Widget *head, Widget *widget)
{
    WidgetItem *headItems = (WidgetItem *) ((ListItem *) head->getItem())->getData();
    WidgetItem *widgetItems = (WidgetItem *) ((ListItem *) widget->getItem())->getData();
    return ((headItems->x == widgetItems->x)
        && (headItems->y == widgetItems->y)
        && (headItems->width == widgetItems->width)
        && (headItems->height == widgetItems->height)
        && (std::strcmp(((std::string *) headItems->widgetData)->c_str(), ((std::string *) widgetItems->widgetData)->c_str()) == 0)
        && (std::strcmp(headItems->properties->key(), widgetItems->properties->key()) == 0)
        && (std::strcmp(headItems->properties->valueAsString().c_str(), widgetItems->properties->valueAsString().c_str()) == 0));
}

//Tests widget structure
void testWidget()
{
    //Create parameters for two widgets
    int firstX = 0;
    int secondX = 1;
    int firstY = 1;
    int secondY = 2;
    int firstWidth = 2;
    /*int secondWidth = 3;*/
    int firstHeight = 3;
    int secondHeight = 4;
    std::string *firstWidgetData = new std::string("First");
    std::string *secondWidgetData = new std::string("Second");
    char *firstPropKey = (char *) "KeyOne";
    char *secondPropKey = (char *) "KeyTwo";
    std::string *firstPropVal = new std::string("Radio");
    std::string *secondPropVal = new std::string("Paranoia");
    Property *firstProperty = new Property();
    firstProperty->addItem(new DictItem(firstPropKey, static_cast<void *>(firstPropVal)));
    Property *secondProperty = new Property();
    secondProperty->addItem(new DictItem(secondPropKey, static_cast<void *>(secondPropVal)));

    //And create the two widgets
    Widget *firstWidget = new Widget(firstX, firstY, firstWidth, firstHeight, static_cast<void *>(firstWidgetData), firstProperty);
    Widget *secondWidget = new Widget(secondX, secondY, secondWidth, secondHeight, static_cast<void *>(secondWidgetData), secondProperty);

    //Now add the second widget to the first
    firstWidget->addItem(secondWidget->getItem());

    //Test that the second widget was added successfully
    assert(("Failed to add second widget to first", (widgetAdded(firstWidget, secondWidget)) == true));
    firstWidget->setItem(firstWidget->getItem()->previous);

    //Now test the first widget's properties
    WidgetItem *firstWidgetParams = (WidgetItem *) ((ListItem *) firstWidget->getItem())->getData();
    assert(("Widget: First Widget: x is not the same value", (firstX == firstWidgetParams->x)));
    assert(("Widget: First Widget: y is not the same value", (firstY == firstWidgetParams->y)));
    assert(("Widget: First Widget: width is not the same value", (firstWidth == firstWidgetParams->width)));
    assert(("Widget: First Widget: height is not the same value", (firstHeight == firstWidgetParams->height)));
    assert(("Widget: First Widget: data is not the same", (std::strcmp(firstWidgetData->c_str(), (static_cast<std::string *>(firstWidgetParams->widgetData))->c_str()) == 0)));
    assert(("Widget: First Widget: Property: key is not the same", (std::strcmp(firstPropKey, firstWidgetParams->properties->key()) == 0)));
    assert(("Widget: First Widget: Property: value is not the same", (std::strcmp(firstPropVal->c_str(), firstWidgetParams->properties->valueAsString().c_str()) == 0)));

    //And test the second widget's properties
    WidgetItem *secondWidgetParams = (WidgetItem *) ((ListItem *) secondWidget->getItem())->getData();
    assert(("Widget: Second Widget: x is not the same value", (secondX == secondWidgetParams->x)));
    assert(("Widget: Second Widget: y is not the same value", (secondY == secondWidgetParams->y)));
    assert(("Widget: Second Widget: width is not the same value", (secondWidth == secondWidgetParams->width)));
    assert(("Widget: Second Widget: height is not the same value", (secondHeight == secondWidgetParams->height)));
    assert(("Widget: Second Widget: data is not the same", (std::strcmp(secondWidgetData->c_str(), (static_cast<std::string *>(secondWidgetParams->widgetData))->c_str()) == 0)));
    assert(("Widget: Second Widget: Property: key is not the same", (std::strcmp(secondPropKey, secondWidgetParams->properties->key()) == 0)));
    assert(("Widget: Second Widget: Property: value is not the same", (std::strcmp(secondPropVal->c_str(), secondWidgetParams->properties->valueAsString().c_str()) == 0)));
}