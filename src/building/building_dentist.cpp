#include "building/building_dentist.h"

#include "building/building_health.h"
#include "building/building_house.h"
#include "io/gamefiles/lang.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include "figuretype/figure_dentist.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dentist);

void building_dentist::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_dentist::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_dentist::spawn_figure() {
    common_spawn_roamer(FIGURE_DENTIST, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
}

building_id building_dentist::find_noble_house_with_max_bad_teeth() {
    building_house *max_house = nullptr;
    uint8_t max_bad_teeth = 0;
    
    buildings_house_do([&] (auto house) {
        if (!house->is_nobles() || house->house_population() <= 0) {
            return;
        }
        
        if (!house->base.has_road_access || house->base.distance_from_entry <= 0) {
            return;
        }
        
        if (house->base.road_network_id != base.road_network_id) {
            return;
        }
        
        auto &housed = house->runtime_data();
        if (housed.nobles_with_bad_teeth > max_bad_teeth) {
            max_bad_teeth = housed.nobles_with_bad_teeth;
            max_house = house;
        }
    });
    
    return max_house ? max_house->id() : 0;
}

void building_dentist::update_month() {
    building_impl::update_month();
    
    if (has_figure(BUILDING_SLOT_SERVICE)) {
        return;
    }
    
    if (num_workers() <= 0 || !has_road_access()) {
        return;
    }
    
    building_id noble_house_id = find_noble_house_with_max_bad_teeth();
    if (noble_house_id > 0) {
        building *noble_house = building_get(noble_house_id);
        if (noble_house && noble_house->is_valid()) {

            create_figure_with_destination(FIGURE_DENTIST, noble_house, 
                (e_figure_action)ACTION_64_DENTIST_GOING_TO_NOBLE_HOUSE, BUILDING_SLOT_SERVICE);
        }
    }
}