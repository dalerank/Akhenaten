#include "building_dance_school.h"
#include "building_dance_school.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "graphics/animation.h"
#include "figuretype/figure_entertainer.h"
#include "js/js_game.h"

buildings::model_t<building_dancer_school> dancer_school_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_dancer_school);
void config_load_building_dancer_school() {
    dancer_school_m.load();
}

void building_entertainment_school_draw_info(object_info& c, pcstr type, int group_id) {
    c.help_id = 75;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, 7);
    } else if (c.worker_percentage >= 100) {
        window_building_draw_description(c, group_id, 2);
    } else if (c.worker_percentage >= 75) {
        window_building_draw_description(c, group_id, 3);
    } else if (c.worker_percentage >= 50) {
        window_building_draw_description(c, group_id, 4);
    } else if (c.worker_percentage >= 25) {
        window_building_draw_description(c, group_id, 5);
    } else {
        window_building_draw_description(c, group_id, 6);
    }
    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_dancer_school::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
}

void building_dancer_school::spawn_figure() {
    if (common_spawn_figure_trigger(50)) {
        int building_id = figure_entertainer::determine_venue_destination(base.road_access, {BUILDING_PAVILLION});
        building* dest= building_get(building_id);
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_DANCER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_DANCER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
    }
}

bool building_dancer_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = dancer_school_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_dancer_school::window_info_background(object_info &c) {
    building_entertainment_school_draw_info(c, "dancer_school", 76);
}

void building_bullfight_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "bullfight_school", 78);
}
