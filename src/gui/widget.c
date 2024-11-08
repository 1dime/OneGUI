#include <gui/widget.h>

/*
build_widget: creates a new widget
@param x: x position
@param y: y position
@param width: width
@param length: length
@param widgetData: data such as window label, text label, etc
@param widgetFunction: function to be ran if widget is something like a button
@param drawFunction: function to be ran to draw widget on screen
@returns new widget
*/
widget_t *build_widget(int x, int y, int width, int length, void *widgetData, void *widgetFunction, void *drawFunction)
{
    widget_t *widget = (widget_t *) malloc(sizeof(widget_t));
    if(widget == NULL)
    {
        printf("error: build_widget(): memory allocation failure.\n");
        exit(EXIT_FAILURE);
    }
    widget->x = x;
    widget->y = y;
    widget->width =  width;
    widget->height = length;
    widget->numChildren = 0;
    widget->childWidgets = (widget_t **) malloc((widget->numChildren + 1) * sizeof(widget_t *));
    widget->widgetData = widgetData;
    widget->widgetFunction = widgetFunction;
    widget->draw = drawFunction;
    
    return widget;
}


/*
add_child: Adds child widget to parent widget
@param parent: parent widget
@param child: child widget
*/
void add_child(widget_t *parent, widget_t *child)
{
    //Make sure both parent and child are set
    if(parent == NULL || child == NULL)
    {
        printf("error: add_child(): either parent or child widgets are empty.\n");
        exit(EXIT_FAILURE);
    }
    
    parent->childWidgets[parent->numChildren] = child;
    parent->numChildren += 1;
}

/*
add_node: Adds widget to widget tree
@param tree: widget tree
@param node: node to be added
@returns modified tree
*/
widget_t *add_node(widget_t *tree, widget_t node)
{
    //Try to add node to tree
    widget_t *new_node = (widget_t *) malloc(sizeof(widget_t));
    new_node->x = node.x;
    new_node->y = node.y;
    new_node->numChildren = node.numChildren;
    new_node->widgetData = node.widgetData;
    new_node->widgetFunction = node.widgetFunction;
    new_node->draw = node.draw;
    new_node->childWidgets = node.childWidgets;
    new_node->properties = node.properties;
    new_node->prev = tree;

    tree->next = new_node;
    tree = tree->next;

    //And return the modified tree
    return tree;
}

/*
get_first: Gets first widget in widget tree
@param tree: widget tree
@returns first widget
*/
widget_t *get_first(widget_t *tree)
{
    //Go and get first widget
    while(tree->prev != NULL)
    {
        //Go to previous widget
        tree = tree->prev;
    }

    //And return the widget
    return tree;
}

/*
find_raw: looks for a widget in a widget tree
@param tree: widget tree
@param x: x position of widget
@param y: y position of widget
@param width: width of widget
@param height: height of widget
@returns modified widget tree
*/
widget_t *find_raw(widget_t *tree, int x, int y, int width, int height)
{
    //Go through all child widgets to find a given widget
    for(int index = 0; index < tree->numChildren; index++)
    {
        //Get current child widget and check it
        widget_t *child = tree->childWidgets[index];
        if(((child->x == x) && (child->y == y)) 
            && ((child->width == width) && (child->height == height)))
        {
            //We found the widget
            return child;
        }

        //Not found, search through child node and check if we found it
        widget_t *find_attmpt = find_raw(child, x, y, width, height);
        if(find_attmpt != NULL)
        {
            //Found widget
            return find_attmpt;
        }
    }

    //Not in child nodes, lets test the rest of the tree
    widget_t *node = get_first(tree);
    while(node->next != NULL)
    {
        //Check if current node is what we are searching for
        if(((node->x == x) && (node->y == y))
            && ((node->width == width) && (node->height == height)))
        {
            //Node is, return it
            return node;
        }

        //Node not found, move to next
        node = node->next;
    }

    //Node was not found
    return NULL;
}

/*
find: searches for widget in a given tree
@param tree: widget tree
@param node: widget node to be searched for
@returns node if found, null if not
*/
widget_t *find(widget_t *tree, widget_t node)
{
    //Look using raw data
    return find_raw(tree, node.x, node.y, node.width, node.height);
}