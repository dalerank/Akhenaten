#include "building/building_conservatory.h"

#include "building/building_dance_school.h"
#include "figuretype/figure_entertainer.h"
#include "building/count.h"

#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "js/js_game.h"

buildings::model_t<building_conservatory> conservatory_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_conservatory);
void config_load_building_conservatory() {
    conservatory_m.load();
}

void building_conservatory::window_info_background(object_info& c) {
    building_entertainment_school_draw_info(c, "conservatory", 75);
}

void building_conservatory::spawn_figure() {
    if (common_spawn_figure_trigger(50)) {
        int dest_id = figure_entertainer::determine_venue_destination(base.road_access, {BUILDING_PAVILLION, BUILDING_BANDSTAND});
        building* dest = building_get(dest_id);
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_MUSICIAN, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_MUSICIAN, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
    }
}

bool building_conservatory::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        const animation_t &anim = conservatory_m.anim["work"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}