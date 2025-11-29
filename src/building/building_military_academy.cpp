#include "building_military_academy.h"

#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "figuretype/figure_magistrate.h"
#include "grid/road_access.h"
#include "core/calc.h"
#include "graphics/animation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_military_academy);

static building_id get_closest_fort(building* academy) {
    building_id closest_fort_id = 0;
    int min_distance = 10000;
    
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID) {
            continue;
        }
        
        // Check if it's a fort
        if (b->type != BUILDING_FORT_INFANTRY && 
            b->type != BUILDING_FORT_ARCHERS && 
            b->type != BUILDING_FORT_CHARIOTEERS && 
            b->type != BUILDING_FORT_GROUND) {
            continue;
        }
        
        if (!map_has_road_access(b->tile, b->size)) {
            continue;
        }
        
        int dist = calc_maximum_distance(academy->tile, b->tile);
        if (dist < min_distance) {
            min_distance = dist;
            closest_fort_id = b->id;
        }
    }
    
    return closest_fort_id;
}

void building_military_academy::spawn_figure() {
    if (!common_spawn_figure_trigger(current_params().min_houses_coverage)) {
        return;
    }
    
    // Find closest fort
    building_id fort_id = get_closest_fort(&base);
    
    figure* f = create_roaming_figure(FIGURE_MAGISTRATE, (e_figure_action)ACTION_70_MAGISTRATE_CREATED, BUILDING_SLOT_SERVICE);
    
    if (fort_id > 0) {
        building* fort = building_get(fort_id);
        tile2i road_tile = map_get_road_access_tile(fort->tile, fort->size);
        if (road_tile.valid()) {
            f->destination_tile = road_tile;
            f->action_state = ACTION_74_MAGISTRATE_GOING_TO_FORT;
        }
    }
}

void building_military_academy::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
    building_impl::update_graphic();
}