#include "building/building_conservatory.h"

#include "building/building_entertainment.h"
#include "figuretype/entertainer.h"

#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "js/js_game.h"

namespace model {

struct conservatory_t {
    static constexpr e_building_type type = BUILDING_CONSERVATORY;
    e_labor_category labor_category;
    animations_t anim;
};

conservatory_t conservatory;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_conservatory);
void config_load_building_conservatory() {
    g_config_arch.r_section("building_conservatory", [] (archive arch) {
        model::conservatory.labor_category = arch.r_type<e_labor_category>("labor_category");
        model::conservatory.anim.load(arch);
    });

    city_labor_set_category(model::conservatory);
}

void building_conservatory::window_info_background(object_info& c) {
    building_entertainment_school_draw_info(c, "conservatory", 75);
}

void building_conservatory::spawn_figure() {
    if (common_spawn_figure_trigger(50)) {
        building* dest = building_get(determine_venue_destination(base.road_access, BUILDING_PAVILLION, BUILDING_BANDSTAND, 0));
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_MUSICIAN, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_MUSICIAN, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
    }
}

bool building_conservatory::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        const animation_t &anim = model::conservatory.anim["work"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}