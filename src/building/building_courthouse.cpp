#include "building/building_courthouse.h"

#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"

#include "graphics/animation.h"
#include "city/labor.h"
#include "js/js_game.h"

buildings::model_t<building_courthouse> courthouse_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_courthouse);
void config_load_building_courthouse() {
    courthouse_m.load();
}

void building_courthouse::spawn_figure() {
    common_spawn_roamer(FIGURE_MAGISTRATE, 50, FIGURE_ACTION_125_ROAMING);
}

void building_courthouse::window_info_background(object_info &c) {
    const int LANG_GROUP_ID = 176;
    c.help_id = 76;
    window_building_play_sound(&c, "Wavs/forum.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(LANG_GROUP_ID, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 10);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 5);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 6);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 7);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 8);
    else {
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 9);
    }

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

bool building_courthouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = courthouse_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}
