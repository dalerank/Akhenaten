#include "graphics/elements/ui.h"

#include "platform/arguments.h"
#include "graphics/no_resource_ui.h"
#include "graphics/elements/button.h"
#include "graphics/graphics.h"
#include "core/app.h"

void (*button_border_draw)(vec2i, vec2i, bool) = ui::button_border_draw;
void (*graphics_draw_background)(painter&, int, float, vec2i) = &ui::graphics_draw_background;

void ANK_REGISTER_APPLICATION_MODULE(ui_module_init) {
    button_border_draw = g_args.no_resource() ? ui::no_resource::button_border_fill : ui::button_border_draw;
    graphics_draw_background = g_args.no_resource() ? ui::no_resource::graphics_draw_background : ui::graphics_draw_background;
    font_use_internal_only(g_args.no_resource());
}