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

TEST(Main, Basic)
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

//Creates a new string using deepstate
char *makeDSString(size_t size)
{
  char *str = (char *) DeepState_Malloc(size);
  for(int index = 0; index < size; index++)
  {
    str[index] = DeepState_Char();
  }
  
  //Return the string
  return str;
}

//Tests the DictItem structure
void testDictItem()
{
    //Create a new DictItem
    char *key = makeDSString(4);
    char *value = makeDSString(4);
    
    std::string *value = new std::string(valueChars);
    DictItem *item = new DictItem(key, static_cast<void *>(value));

    //And test if the key and value match
    ASSERT(std::strcmp(key, item->k.c_str())) == 0) << "DictItem: key does not match stored.";
    ASSERT(std::strcmp(value->c_str(), (static_cast<std::string *>(item->v))->c_str())) == 0) << "DictItem: value does not match stored.";
}

//Tests ListItem structure
void testListItem()
{
    //Create two new list items
    char *firstListDataChars = makeDSString(4);
    char *secondListDataChars = makeDSString(4);
    std::string *firstListData = new std::string(firstListDataChars);
    std::string *secondListData = new std::string(secondListDataChars);
    ListItem *firstItem = new ListItem(static_cast<void *>(firstListData));
    ListItem *secondItem = new ListItem(static_cast<void *>(secondListData));

    //Add second item to first
    firstItem->next = secondItem;

    //Now test if the second item was added
    ASSERT(firstItem->next == secondItem) << "ListItem: failed to add second list item to first.";
    //And test the first item's parameters
    ASSERT(std::strcmp(firstListData->c_str(), (static_cast<std::string *>(firstItem->getData())->c_str())) == 0) << "ListItem: First Item: data is not the same";
    //And the second item's parameters
    ASSERT(std::strcmp(secondListData->c_str(), (static_cast<std::string *>(secondItem->getData())->c_str())) == 0) << "ListItem: Second Item: data is not the same";
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
    char *firstListData = makeDSString(4);
    char *secondListData = makeDSString(4);
    std::string *firstListString = new std::string(firstListData);
    std::string *secondListString = new std::string(secondListData);

    //And create two lists
    List *firstList = new List(new ListItem(static_cast<void *>(firstListString)));
    List *secondList = new List(new ListItem(static_cast<void *>(secondListString)));

    //Now add second list to first
    firstList->addItem(secondList->getItem());

    //And test if the second list was added
    ASSERT(listAdded(firstList, secondList)) << "List: failed to add second list to first.";
    firstList->setItem(firstList->getItem()->previous);

    //Then test first list's parameters
    ASSERT((std::strcmp(firstListString->c_str(), (static_cast<std::string *>(firstList->getItem()->getData()))->c_str())) == 0) << "List: First List: data is not the same.";

    //And test second list's parameters
    ASSERT((std::strcmp(secondListString->c_str(), (static_cast<std::string *>(secondList->getItem()->getData()))->c_str())) == 0) << "List: Second List: data is not the same";
}

//Tests nlohmann's JSON
void testJson()
{
    //Create a simple key and value for json
    char *key = makeDSString(4);
    char *value = makeDSString(4);

    //And add them to new json element
    nlohmann::json data;
    data[key] = value;

    //Now test the data
    ASSERT(data.contains(key) == true) << "Json: key does not match";
    ASSERT(std::strcmp(value, data[key].get<std::string>().c_str()) == 0) << "Json: value does not match";
}

//Tests the Property class
void testProperty()
{
    //Create a basic property
    char *key = makeDSString(4);
    char *value = makeDSString(4);
    std::string *value = new std::string(value);
    Property *property = new Property();
    property->addItem(new DictItem(key, static_cast<void *>(value)));

    //Make sure property key and value match
    ASSERT(std::strcmp(key, property->key()) == 0) << "Property: Key does not match";
    ASSERT(std::strcmp(value->c_str(), property->valueAsString().c_str()) == 0) << "Property: Value does not match";
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
    char *firstDataChars = makeDSString(4);
    char *secondDataChars = makeDSString(4);
    char *firstPropChars = makeDSString(4);
    char *secondPropChars = makeDSString(4);
    int firstX = DeepState_Int();
    int secondX = DeepState_Int();
    int firstY = DeepState_Int();
    int secondY = DeepState_Int();
    int firstWidth = DeepState_Int();
    int secondWidth = DeepState_Int();
    int firstHeight = DeepState_Int();
    int secondHeight = DeepState_Int();
    
    std::string *firstWidgetData = new std::string(firstDataChars);
    std::string *secondWidgetData = new std::string(secondDataChars);
    
    char *firstPropKey = (char *) makeDSString(4);
    char *secondPropKey = (char *) makeDSString(4);
    
    std::string *firstPropVal = new std::string(firstPropChars);
    std::string *secondPropVal = new std::string(secondPropChars);
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
    ASSERT(widgetAdded(firstWidget, secondWidget)) << "Widget: Failed to add second widget to first.";
    firstWidget->setItem(firstWidget->getItem()->previous);

    //Now test the first widget's properties
    WidgetItem *firstWidgetParams = (WidgetItem *) ((ListItem *) firstWidget->getItem())->getData();
    ASSERT(firstX == firstWidgetParams->x) << "Widget: First Widget: x is not the same value.";
    ASSERT(firstY == firstWidgetParams->y) << "Widget: First Widget: y is not the same value.";
    ASSERT(firstWidth == firstWidgetParams->width) << "Widget: First Widget: width is not the same.";
    ASSERT(firstHeight == firstWidgetParams->height) << "Widget: First Widget: height is not the same value.";
    ASSERT(std::strcmp(firstWidgetData->c_str(), (static_cast<std::string *>(firstWidgetParams->widgetData))->c_str()) == 0) << "Widget: First Widget: data is not the same";
    ASSERT((std::strcmp(firstPropKey, firstWidgetParams->properties->key()) == 0)) << "Widget: First Widget: Property: key is not the same";
    ASSERT((std::strcmp(firstPropVal->c_str(), firstWidgetParams->properties->valueAsString().c_str()) == 0)) << "Widget: First Widget: Property: value is not the same";

    //And test the second widget's properties
    WidgetItem *secondWidgetParams = (WidgetItem *) ((ListItem *) secondWidget->getItem())->getData();
    ASSERT(secondX == secondWidgetParams->x) << "Widget: Second Widget: x is not the same value.";
    ASSERT(secondY == secondWidgetParams->y) << "Widget: Second Widget: y is not the same value.";
    ASSERT(secondWidth == secondWidgetParams->width) << "Widget: Second Widget: width is not the same.";
    ASSERT(secondHeight == secondWidgetParams->height) << "Widget: Second Widget: height is not the same value.";
    ASSERT(std::strcmp(secondWidgetData->c_str(), (static_cast<std::string *>(secondWidgetParams->widgetData))->c_str()) == 0) << "Widget: Second Widget: data is not the same";
    ASSERT((std::strcmp(secondPropKey, secondWidgetParams->properties->key()) == 0)) << "Widget: Second Widget: Property: key is not the same";
    ASSERT((std::strcmp(secondPropVal->c_str(), secondWidgetParams->properties->valueAsString().c_str()) == 0)) << "Widget: Second Widget: Property: value is not the same";
}
