#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

static void building_shrine_draw_info(object_info& c, const char* type, int text_id, int image_offset) {
    view_context ctx = view_context_main();
    c.help_id = 67;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(161, text_id, c.x_offset, c.y_offset + 12, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    if (c.has_road_access) {
        ImageDraw::img_generic(ctx, image_offset + image_id_from_group(GROUP_PANEL_WINDOWS), c.x_offset + 190, c.y_offset + 16 * c.height_blocks - 148);
    } else {
        window_building_draw_description_at(c, 16 * c.height_blocks - 128, 69, 25);
    }
}

void building_shrine_osiris_draw_info(object_info& c) {
    building_shrine_draw_info(c, "shrine_osiris", 0, 21);
}
void building_shrine_ra_draw_info(object_info& c) {
    building_shrine_draw_info(c, "shrine_ra", 2, 22);
}
void building_shrine_ptah_draw_info(object_info& c) {
    building_shrine_draw_info(c, "shrine_ptah", 4, 23);
}
void building_shrine_seth_draw_info(object_info& c) {
    building_shrine_draw_info(c, "shrine_seth", 6, 24);
}
void building_shrine_bast_draw_info(object_info& c) {
    building_shrine_draw_info(c, "shrine_bast", 8, 25);
}