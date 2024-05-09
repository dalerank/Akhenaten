#include "building_well.h"

#include "grid/desirability.h"
#include "grid/image.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"

buildings::model_t<building_well> well_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_well);
void config_load_building_well() {
    well_m.load();
}

void building_well::update_month() {
    int avg_desirability = map_desirabilty_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30 ? efancy_good : efancy_normal);
    pcstr anim = (base.fancy_state == efancy_good) ? "fancy" : "base";
    map_image_set(tile(), well_m.anim[anim]);
}

void building_well::on_place_checks() {
    // nothing
}

void building_well::window_info_background(object_info &c) {
    c.help_id = 62;
    window_building_play_sound(&c, "wavs/well.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(109, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
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
        window_building_draw_description_at(c, 16 * c.bgsize.y - 160, 109, text_id);
    }
}

bool building_well::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    pcstr anim = (base.fancy_state == efancy_normal) ? "base_work" : "fancy_work";
    building_draw_normal_anim(ctx, point, &base, tile, well_m.anim[anim], color_mask);

    return true;
}

