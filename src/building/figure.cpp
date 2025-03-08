#include "city/city.h"

#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "building/building_farm.h"
#include "building/industry.h"
#include "building/building_bazaar.h"
#include "building/model.h"
#include "building/building_storage_yard.h"
#include "building/building_industry.h"
#include "building/count.h"
#include "building/monument_mastaba.h"
#include "building/building_work_camp.h"
#include "city/buildings.h"
#include "city/entertainment.h"
#include "city/city_floods.h"
#include "city/message.h"
#include "city/population.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figure/formation_legion.h"
#include "figure/movement.h"
#include "figuretype/figure_entertainer.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/image.h"
#include "grid/random.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "grid/floodplain.h"
#include "config/config.h"

#include "figuretype/figure_cartpusher.h"

#include <cmath>
#include <algorithm>
#include <numeric>

const int generic_delay_table[] = {0, 1, 3, 7, 15, 29, 44};

figure* building::get_figure(int i) {
    return ::figure_get(get_figure_id(i));
}

void building::bind_iob_figures(io_buffer* iob) {
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids[0]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids[1]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids[2]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids[3]);
}

void building::set_figure(int i, int figure_id) {
    //assert(figure_ids_array[i] == 0);
    figure_ids[i] = figure_id;
}

void building::set_figure(int i, figure* f) {
    set_figure(i, f ? f->id : 0);
}

void building::remove_figure(int i) {
    set_figure(i, 0);
}

void building::remove_figure_by_id(int id) {
    for (auto &fid : figure_ids) {
        if (fid == id) {
            fid = 0;
        }
    }
}

bool building::has_figure(int i, int figure_id) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < max_figures; i++) {
            if (has_figure(i, figure_id))
                has_any = true;
        }
        return has_any;
    } else {
        figure* f = this->get_figure(i);
        if (f->state
            && (f->home() == this || building_get(f->immigrant_home_building_id) == this)) { // check if figure belongs to this building...
            if (figure_id < 0)                                       // only check if there is a figure
                return true;
            return (f->id == figure_id);
        } else { // decouple if figure does not belong to this building - assume cache is incorrect
            remove_figure(i);
            return false;
        }
    }
}
bool building::has_figure(int i, figure* f) {
    return has_figure(i, f->id);
}

bool building::has_figure_of_type(int i, e_figure_type _type) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < max_figures; i++) {
            if (get_figure(i)->type == _type) {
                has_any = true;
            }
        }

        return has_any;
    } else {
        return (get_figure(i)->type == _type);
    }
}

int building::get_figure_slot(figure* f) {
    // search through all the slots, check if figure matches
    for (int i = 0; i < max_figures; i++) {
        if (has_figure(i, f)) {
            return i;
        }
    }
    return -1;
}

int building::worker_percentage() {
    return calc_percentage<int>(num_workers, model_get_building(type)->laborers);
}

int building::figure_spawn_timer() {
    int pct_workers = worker_percentage();
    if (pct_workers >= 100) {
        return 0;
    } else if (pct_workers >= 75) {
        return 1;
    } else if (pct_workers >= 50) {
        return 3;
    } else if (pct_workers >= 25) {
        return 7;
    } else if (pct_workers >= 1) {
        return 15;
    } else {
        return -1;
    }
}

void building::check_labor_problem() {
    if ((houses_covered <= 0 && labor_category != 255) || (labor_category == 255 && num_workers <= 0)) {
        show_on_problem_overlay = 2;
    }
}

void building::common_spawn_labor_seeker(int min_houses) {
    if (city_population() <= 0) {
        return;
    }

    if (config_get(CONFIG_GP_CH_GLOBAL_LABOUR)) {
        // If it can access Rome
        houses_covered = std::min(300, distance_from_entry ? 2 * min_houses : 0);
        return;
    } 
    
    if (houses_covered > min_houses) {
        return;
    }

    if (has_figure(BUILDING_SLOT_LABOR_SEEKER)) { // no figure slot available!
        return;
    } 
    
    create_roaming_figure(FIGURE_LABOR_SEEKER, FIGURE_ACTION_125_ROAMING, BUILDING_SLOT_LABOR_SEEKER);
}

bool building::common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action) {
    if (common_spawn_figure_trigger(min_houses)) {
        create_roaming_figure(type, created_action);
        return true;
    }
    return false;
}

bool building::common_spawn_goods_output_cartpusher(bool only_one, bool only_full_loads, int min_carry, int max_carry) {
    // can only have one?
    if (only_one && has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return false;
    }

    // no checking for work force? doesn't matter anyways.... there's no instance
    // in the game that allows cartpushers to spawn before the workers disappear!
    if (!has_road_access) {
        return false;
    }

    while (stored_amount_first >= min_carry) {
        int amounts_to_carry = std::min<int>(stored_amount_first, max_carry);
        if (only_full_loads) {
            amounts_to_carry -= amounts_to_carry % 100; // remove pittance
        }

        create_cartpusher(output_resource_first_id, amounts_to_carry);
        stored_amount_first -= amounts_to_carry;
        if (only_one || stored_amount_first == 0) {
            // done once, or out of goods?
            return true;
        }
    }

    return false;
}

void building::set_water_supply_graphic() {
    //if (state != BUILDING_STATE_VALID) {
    //    return;
    //}
    //
    //has_water_access = map_terrain_exists_tile_in_area_with_type(tile.x(), tile.y(), size, TERRAIN_GROUNDWATER);
    //
    //if (has_water_access && num_workers) {
    //    if (map_desirability_get(tile.grid_offset()) <= 30) {
    //        map_building_tiles_add(id, tile, size, IMG_WATER_SUPPLY, TERRAIN_BUILDING);
    //    } else {
    //        map_building_tiles_add(id, tile, size, IMG_WATER_SUPPLY_FANCY, TERRAIN_BUILDING);
    //    }
    //} else {
    //    if (map_desirability_get(tile.grid_offset()) <= 30) {
    //        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_BATHHOUSE_NO_WATER), TERRAIN_BUILDING);
    //    } else {
    //        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_BATHHOUSE_FANCY_NO_WATER), TERRAIN_BUILDING);
    //    }
    //}
}

int building::get_figures_number(e_figure_type ftype) {
    int figures_this_yard = 0;
    for (int i = 0; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->has_type(ftype) && f->has_home(this)) {        // figure with type on map and  belongs to this building
            figures_this_yard++;
        }
    }

    return figures_this_yard;
}