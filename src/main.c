#include <stdbool.h>
#include "gui/linux.c"
#include "gui/widget.c"
#include "properties/properties.c"
#include <ui/parser.h>

int start(widget_t *display)
{
    return EXIT_SUCCESS;
}

void update(widget_t *display)
{
    printf("Updating this frame...");
}

int main()
{
    property_t *properties = mk_property(HIDE_TOOLBAR_PROPERTY, (bool *) true);
    widget_t *display = make_display(0, 0, 100, 100, properties);
    show_window(display);
}
