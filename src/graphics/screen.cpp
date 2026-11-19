#include "screen.h"

#include "graphics/image.h"
#include "game/game_events.h"
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

    g_camera.set_screen_size(width, height);
    events::emit(event_screen_resized{width, height});
}