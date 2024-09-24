#include "building/building_physician.h"

#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "sound/sound_building.h"
#include "io/gamefiles/lang.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "js/js_game.h"

buildings::model_t<building_physician> bphysician_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_physician);
void config_load_building_physician() {
    bphysician_m.load();
}

void building_physician::window_info_background(object_info& c) {
    c.help_id = 64;
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(e_text_building_physician, e_text_title, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building *b = building_get(c.building_id);
    window_building_play_sound(&c, b->get_sound());
    //if (!b->has_water_access)
    //    window_building_draw_description(c, 83, 4);

    if (b->has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_PHYSICIAN)) {
        window_building_draw_description(c, e_text_building_physician, e_text_figure_on_patrol);
    } else if (!c.has_road_access) {
        window_building_draw_description(c, e_text_building, e_text_building_no_roads);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, e_text_building_physician, e_text_no_workers);
    } else {
        window_building_draw_description(c, e_text_building_physician, e_text_works_fine);
    }

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_physician::spawn_figure() {
    common_spawn_roamer(FIGURE_PHYSICIAN, 50, FIGURE_ACTION_125_ROAMING);
}

bool building_physician::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = bphysician_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}