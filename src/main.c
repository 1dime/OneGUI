#include <stdbool.h>
#include "gui/linux.c"
#include "gui/widget.c"
#include "widgets/linux/text.c"
#include "properties/properties.c"

int start(widget_t *display)
{
    //When app starts, return success
    return EXIT_SUCCESS;
}

int update(widget_t *display)
{
    //Should be running once per frame...
    printf("Updating this frame...");
}

int main()
{
    property_t *properties = mk_property(HIDE_TOOLBAR_PROPERTY, (bool *) true);
    widget_t *display = make_display(0, 0, 500, 500, properties);
    widget_t *text_widget = mk_text(display, "Test", 100, 150, 10, 10, display);
    printf("Number of children: %i\n", display->numChildren);
    show_window(display);
}
