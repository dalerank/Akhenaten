#include "screen.h"

#include "graphics/image.h"
#include "city/city_warnings.h"
#include "graphics/view/view.h"
#include "platform/renderer.h"
#include "graphics/graphics.h"
#include "window.h"

screen_t g_screen;

void screen_t::set_resolution(int w, int h) {
    width = w;
    height = h;
    dialog_offset.x = (width - 640) / 2;
    dialog_offset.y = (height - 480) / 2;

    g_render.clear_screen();
    g_render.set_clip_rectangle({ 0, 0 }, width, height);

    city_view_set_viewport(width, height);
    g_warning_manager.clear_all();
}