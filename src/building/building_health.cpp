#include "building_health.h"

#include "building/building.h"
#include "building/figure.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"

buildings::model_t<building_apothecary> apothercary_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_health);
void config_load_building_health() {
    apothercary_m.load();
}


static void building_health_draw_info(object_info& c, int help_id, const char* type, int group_id, e_figure_type ftype) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building *b = building_get(c.building_id);

    if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        window_building_draw_description(c, group_id, e_text_figure_on_patrol);
    } else if (!c.has_road_access) {
        window_building_draw_description(c, e_text_building, e_text_building_no_roads);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, e_text_no_workers);
    } else {
        window_building_draw_description(c, group_id, e_text_works_fine);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_apothecary::window_info_background(object_info& c) {
    building_health_draw_info(c, 63, "apothecary", e_text_building_apothecary, FIGURE_HERBALIST);
}

void building_dentist_draw_info(object_info& c) {
    building_health_draw_info(c, 65, "dentist", e_text_building_dentist, FIGURE_DENTIST);
}

void building_mortuary_draw_info(object_info& c) {
    building_health_draw_info(c, 66, "mortuary", e_text_building_mortuary, FIGURE_EMBALMER);
}

void building_apothecary::spawn_figure() {
    common_spawn_roamer(FIGURE_HERBALIST, 50, FIGURE_ACTION_62_HERBALIST_ROAMING);
    //    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_DOCTOR))
    //        return;
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        int spawn_delay = figure_spawn_timer();
    //        if (spawn_delay == -1)
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            create_roaming_figure(road.x, road.y, FIGURE_DOCTOR);
    //        }
    //    }
}

bool building_apothecary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = apothercary_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}