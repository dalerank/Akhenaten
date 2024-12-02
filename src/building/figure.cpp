#include "city/city.h"

#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "building/building_farm.h"
#include "building/industry.h"
#include "building/building_bazaar.h"
#include "building/model.h"
#include "building/building_storage_yard.h"
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

int building::stored_amount(e_resource res) const {
    if (first_material_id == res) {
        return stored_amount_first;
    }

    if (second_material_id == res) {
        return stored_amount_second;
    }

    if (output_resource_first_id == res) {
        return data.industry.ready_production;
    }

    // todo: dalerank, temporary, building should return own resource type only
    return stored_amount_first;
}

int building::need_resource_amount(e_resource resource) const {
    return max_storage_amount(resource) - stored_amount(resource);
}

int building::max_storage_amount(e_resource resource) const {
    return 200;
}

int building::stored_amount(int idx) const {
    switch (idx) {
    case 0: return stored_amount_first;
    case 1: return stored_amount_second;
    }

    assert(false);
    return 0;
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

bool building::guild_has_resources() {
    assert(is_guild());
    bool hase_first_resource = (stored_amount_first >= 100);
    return hase_first_resource;
}

bool building::workshop_has_resources() {
    assert(is_workshop());
    bool has_second_material = true;
    if (second_material_id != RESOURCE_NONE) {
        has_second_material = (stored_amount_second > 100);
    }

    bool hase_first_resource = (stored_amount_first >= 100);
    return has_second_material && hase_first_resource;
}

void building::workshop_start_production() {
    assert(is_workshop());
    bool can_start_b = false;
    if (second_material_id != RESOURCE_NONE) {
        can_start_b = (stored_amount_second >= 100);
    } else {
        can_start_b = true;
    }

    bool can_start_a = (stored_amount_first >= 100);
    if (can_start_b && can_start_a) {
        data.industry.has_raw_materials = true;
        if (stored_amount_second >= 100) {
            stored_amount_second -= 100;
        }
        if (stored_amount_first >= 100) {
            stored_amount_first -= 100;
        }
    }
}

bool building::spawn_noble(bool spawned) {
    return common_spawn_roamer(FIGURE_NOBLES, 50);
}


//void building::set_water_supply_graphic() {
//    if (state != BUILDING_STATE_VALID) {
//        return;
//    }
//
//    has_water_access = map_terrain_exists_tile_in_area_with_type(tile.x(), tile.y(), size, TERRAIN_GROUNDWATER);
//
//    if (map_desirability_get(tile.grid_offset()) <= 30) {
//        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_WATER_SUPPLY), TERRAIN_BUILDING);
//    } else {
//        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_WATER_SUPPLY) + 2, TERRAIN_BUILDING);
//    }
//}

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

void building::spawn_figure_industry() {
    check_labor_problem();
    if (!has_road_access) {
        return;
    }

    common_spawn_labor_seeker(50);
    if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return;
    }

    if (building_industry_has_produced_resource(*this)) {
        building_industry_start_new_production(this);
        int ready_production = dcast()->ready_production();
        create_cartpusher(output_resource_first_id, ready_production);
    }
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

void building::spawn_figure_native_hut() {
    //    map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_NATIVE) + (map_random_get(grid_offset) & 1));
    //    if (has_figure_of_type(FIGURE_INDIGENOUS_NATIVE))
    //        return;
    //    int x_out, y_out;
    //    if (subtype.native_meeting_center_id > 0 &&
    //        map_terrain_get_adjacent_road_or_clear_land(x, y, size, &x_out, &y_out)) {
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > 4) {
    //            figure_spawn_delay = 0;
    //            figure *f = figure_create(FIGURE_INDIGENOUS_NATIVE, x_out, y_out, DIR_0_TOP_RIGHT);
    //            f->action_state = FIGURE_ACTION_158_NATIVE_CREATED;
    //            f->home() = b;
    //            figure_id = f->id;
    //        }
    //    }
}
void building::spawn_figure_native_meeting() {
    //    map_building_tiles_add(id, x, y, 2,
    //                           image_id_from_group(GROUP_BUILDING_NATIVE) + 2, TERRAIN_BUILDING);
    //    if (city_buildings_is_mission_post_operational() && !has_figure_of_type(FIGURE_NATIVE_TRADER)) {
    //        int x_out, y_out;
    //        if (map_terrain_get_adjacent_road_or_clear_land(tile.x(), tile.y(), size, &x_out, &y_out)) {
    //            figure_spawn_delay++;
    //            if (figure_spawn_delay > 8) {
    //                figure_spawn_delay = 0;
    //                figure *f = figure_create(FIGURE_NATIVE_TRADER, x_out, y_out, DIR_0_TOP_RIGHT);
    //                f->action_state = FIGURE_ACTION_162_NATIVE_TRADER_CREATED;
    //                f->home() = b;
    //                figure_id = f->id;
    //            }
    //        }
    //    }
}

void building::update_native_crop_progress() {
    data.industry.progress++;
    if (data.industry.progress >= 5) {
        data.industry.progress = 0;
    }

    int img_id = building_impl::params(BUILDING_BARLEY_FARM).anim["farmland"].first_img();
    map_image_set(tile.grid_offset(), img_id + data.industry.progress);
}

tile2i building::access_tile() {
    switch (type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_SIDE:
        return main()->tile.shifted(0, 10);
    }

    return road_access;
}

bool building::figure_generate() {
    show_on_problem_overlay = 0;

    bool noble_generated = false;
    if (type >= BUILDING_HOUSE_COMMON_MANOR && type <= BUILDING_HOUSE_PALATIAL_ESTATE) {
        noble_generated = spawn_noble(noble_generated);
    } else if (is_workshop() || is_extractor()) {// farms are handled by a separate cycle in Pharaoh!
        spawn_figure_industry();
    } else if (is_administration()) {
        common_spawn_figure_trigger(50);

        if (is_governor_mansion() && !has_figure(BUILDING_SLOT_GOVERNOR)) {
            tile2i road_tile = map_closest_road_within_radius(tile, size, 2);
            if (road_tile.valid()) {
                figure *f = figure_create(FIGURE_GOVERNOR, road_tile, DIR_4_BOTTOM_LEFT);
                f->advance_action(FIGURE_ACTION_120_GOVERNOR_CREATED);
                f->set_home(this);
                f->wait_ticks = 10 + (map_random_7bit & 0xf);
                set_figure(BUILDING_SLOT_GOVERNOR, f);
            }
        } else {
            dcast()->spawn_figure();
        }
    } else {
        // single building type
        switch (type) {
        case BUILDING_UNUSED_NATIVE_HUT_88: spawn_figure_native_hut(); break;
        case BUILDING_UNUSED_NATIVE_MEETING_89: spawn_figure_native_meeting(); break;
        case BUILDING_UNUSED_NATIVE_CROPS_93: update_native_crop_progress(); break;

        default:
            dcast()->spawn_figure();
            break;
        }
    }

    return true;
}