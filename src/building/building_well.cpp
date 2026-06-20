#include "building_well.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "city/city_warnings.h"
#include "grid/image.h"
#include "grid/water_supply.h"
#include "widget/city/ornaments.h"
#include "city/city_labor.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_well);

void building_well::update_month() {
    int avg_desirability = g_desirability.get_avg(tile(), current_params().desirability_range_check);

    const bool is_fancy = (avg_desirability > current_params().desirability_fancy);
    base.set_flag(e_building_fancy, is_fancy);
    const xstring animkey = is_fancy ? animkeys().fancy : animkeys().base;

    map_image_set(tile(), anim(animkey));
}

void building_well::on_place_checks() {
    // Do NOT chain to building_impl::on_place_checks() here. A well needs groundwater,
    // not road access, and has no labor -- the base would emit spurious #needs_road_access
    // and #city_needs_more_workers warnings. Same rationale as building_irrigation_ditch
    // and building_road (both deliberately skip the base). The only relevant check is
    // groundwater presence below.
    construction_warnings warnings;

    int has_water = map_terrain_is(tile(), TERRAIN_GROUNDWATER);
    warnings.add_if(!has_water, "#needs_groundwater");
}

void building_well::update_graphic() {
    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }

    const xstring animkey = base.get_flag(e_building_fancy) ? animkeys().base_work : animkeys().fancy_work;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_well::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {   
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

bool building_well::can_play_animation() const {
    const e_well_status status = map_water_supply_is_well_unnecessary(id(), current_params().unnecessary_range_check);
    if (status != WELL_NECESSARY) {
        return false;
    }

    return true;
}
