#include "building_well.h"

#include "grid/desirability.h"
#include "grid/image.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"

void building_well::update_month() {
    int avg_desirability = map_desirabilty_avg(tile(), 4);
    map_image_set(tile(), avg_desirability > 30 ? IMG_WELL_FANCY : IMG_WELL);
}

void building_well::window_info_background(object_info &c) {
    c.help_id = 62;
    window_building_play_sound(&c, "wavs/well.wav");
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(109, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    int well_necessity = map_water_supply_is_well_unnecessary(c.building_id, 2);
    int text_id = 0;
    if (well_necessity == WELL_NECESSARY) { // well is OK
        text_id = 1;
    } else if (well_necessity == WELL_UNNECESSARY_FOUNTAIN) { // all houses have fountain
        text_id = 2;
    } else if (well_necessity == WELL_UNNECESSARY_NO_HOUSES) { // no houses around
        text_id = 3;
    }

    if (text_id) {
        window_building_draw_description_at(c, 16 * c.height_blocks - 160, 109, text_id);
    }
}
