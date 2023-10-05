#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

void building_booth_draw_info(object_info &c) {
    c.help_id = 71;
    window_building_play_sound(&c, snd::get_building_info_sound("booth"));
    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(72, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);
    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, 72, 4);
    } else if (!b->data.entertainment.num_shows) {
        window_building_draw_description(c, 72, 2);
    } else if (b->data.entertainment.days1) {
        window_building_draw_description(c, 72, 3);
    }

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 6);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(72, 6, c.x_offset + 32, c.y_offset + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.x_offset + width + 32, c.y_offset + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(72, 7 + b->data.entertainment.days3_or_play, c.x_offset + 32, c.y_offset + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(72, 5, c.x_offset + 32, c.y_offset + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
}
