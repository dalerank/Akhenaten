#include "building/figure.h"

#include "city/data_private.h"
#include "figuretype/entertainer.h"

#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "building/industry.h"
#include "building/building_bazaar.h"
#include "building/model.h"
#include "building/storage_yard.h"
#include "building/count.h"
#include "building/monument_mastaba.h"
#include "building/building_work_camp.h"
#include "city/buildings.h"
#include "city/data_private.h"
#include "city/entertainment.h"
#include "city/floods.h"
#include "city/message.h"
#include "city/population.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figure/formation_legion.h"
#include "figure/movement.h"
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

#include <cmath>
#include <algorithm>
#include <numeric>

const int generic_delay_table[] = {0, 1, 3, 7, 15, 29, 44};

figure* building::get_figure(int i) {
    return ::figure_get(get_figureID(i));
}
void building::bind_iob_figures(io_buffer* iob) {
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[0]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[1]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[2]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[3]);
}
void building::set_figure(int i, int figure_id) {
    //assert(figure_ids_array[i] == 0);
    figure_ids_array[i] = figure_id;
}

void building::set_figure(int i, figure* f) {
    set_figure(i, f ? f->id : 0);
}

void building::remove_figure(int i) {
    set_figure(i, 0);
}

bool building::has_figure(int i, int figure_id) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++) {
            if (has_figure(i, figure_id))
                has_any = true;
        }
        return has_any;
    } else {
        figure* f = this->get_figure(i);
        if (f->state
            && (f->home() == this || f->immigrant_home() == this)) { // check if figure belongs to this building...
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
        for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++) {
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
    for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++) {
        if (has_figure(i, f)) {
            return i;
        }
    }
    return -1;
}

int building::stored_amount(e_resource res) const {
    if (data.industry.first_material_id == res) {
        return stored_full_amount;
    }

    if (data.industry.second_material_id == res) {
        return data.industry.stored_amount_second;
    }

    if (output_resource_first_id == res) {
        return data.industry.ready_production;
    }

    // todo: dalerank, temporary, building should return own resource type only
    return stored_full_amount;
}

int building::need_resource_amount(e_resource resource) const {
    return max_storage_amount(resource) - stored_amount(resource);
}

int building::max_storage_amount(e_resource resource) const {
    return 200;
}

int building::stored_amount(int idx) const {
    switch (idx) {
    case 0: return stored_full_amount;
    case 1: return data.industry.stored_amount_second;
    }

    assert(false);
    return 0;
}

figure* building::create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir) {
    figure* f = figure_create(_type, road_access, created_dir);
    f->action_state = created_action;
    f->set_home(id);
    set_figure(slot, f);

    return f;
}

figure* building::create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) {
    figure* f = create_figure_generic(_type, created_action, slot, figure_roam_direction);

    f->set_destination(0);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    f->init_roaming_from_building(figure_roam_direction);
    f->set_home(id);

    // update building to have a different roamer direction for next time
    figure_roam_direction += 2;
    if (figure_roam_direction > 6) {
        figure_roam_direction = 0;
    }

    return f;
}

figure* building::create_figure_with_destination(e_figure_type _type, building* destination, e_figure_action created_action, e_building_slot slot) {
    figure* f = create_figure_generic(_type, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->set_destination(destination->id);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    return f;
}

figure* building::create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action, e_building_slot slot) {
    // TODO: industry cartpushers do not spawn in the correct place?

    figure* f = create_figure_generic(FIGURE_CART_PUSHER, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->load_resource(resource_id, quantity);
    f->set_destination(0);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    if (config_get(CONFIG_GP_CH_CART_SPEED_QUANTITY)) {
        f->progress_inside_speed = std::clamp(quantity / 400, 0, 2);
    }
    f->wait_ticks = 30;
    return f;
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
    if ((houses_covered <= 0 && labor_category != 255) || (labor_category == 255 && num_workers <= 0))
        show_on_problem_overlay = 2;
}

void building::common_spawn_labor_seeker(int min_houses) {
    if (city_population() <= 0) {
        return;
    }

    if (config_get(CONFIG_GP_CH_GLOBAL_LABOUR)) {
        // If it can access Rome
        houses_covered = std::min(300, distance_from_entry ? 2 * min_houses : 0);
    } else if (houses_covered <= min_houses) {
        if (has_figure(BUILDING_SLOT_LABOR_SEEKER)) { // no figure slot available!
            return;
        } else {
            create_roaming_figure(FIGURE_LABOR_SEEKER, FIGURE_ACTION_125_ROAMING, BUILDING_SLOT_LABOR_SEEKER);
        }
    }
}
bool building::common_spawn_figure_trigger(int min_houses) {
    check_labor_problem();
    if (has_figure(BUILDING_SLOT_SERVICE)) {
        return false;
    }

    if (has_road_access) {
        if (main() == this) { // only spawn from the main building
            common_spawn_labor_seeker(min_houses);
        }

        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            return false;
        }

        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;
            return true;
        }
    }

    return false;
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

    while (stored_full_amount >= min_carry) {
        int amounts_to_carry = std::min<int>(stored_full_amount, max_carry);
        if (only_full_loads) {
            amounts_to_carry -= amounts_to_carry % 100; // remove pittance
        }

        create_cartpusher(output_resource_first_id, amounts_to_carry);
        stored_full_amount -= amounts_to_carry;
        if (only_one || stored_full_amount == 0) {
            // done once, or out of goods?
            return true;
        }
    }

    return false;
}

bool building::guild_has_resources() {
    assert(is_guild());
    bool hase_first_resource = (stored_full_amount >= 100);
    return hase_first_resource;
}

bool building::workshop_has_resources() {
    assert(is_workshop());
    bool has_second_material = true;
    if (data.industry.second_material_id != RESOURCE_NONE) {
        has_second_material = (data.industry.stored_amount_second > 100);
    }

    bool hase_first_resource = (stored_full_amount >= 100);
    return has_second_material && hase_first_resource;
}

void building::workshop_start_production() {
    assert(is_workshop());
    bool can_start_b = false;
    if (data.industry.second_material_id != RESOURCE_NONE) {
        can_start_b = (data.industry.stored_amount_second >= 100);
    } else {
        can_start_b = true;
    }

    bool can_start_a = (stored_full_amount >= 100);
    if (can_start_b && can_start_a) {
        data.industry.has_raw_materials = true;
        if (data.industry.stored_amount_second >= 100) {
            data.industry.stored_amount_second -= 100;
        }
        if (stored_full_amount >= 100) {
            stored_full_amount -= 100;
        }
    }
}

bool building::spawn_noble(bool spawned) {
    return common_spawn_roamer(FIGURE_NOBLES, 50);
}

void building::spawn_figure_police() {
    common_spawn_roamer(FIGURE_CONSTABLE, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}

void building::spawn_figure_dancer() {
    if (common_spawn_figure_trigger(50)) {
        building* dest= building_get(determine_venue_destination(road_access, BUILDING_PAVILLION, 0, 0));
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_DANCER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_DANCER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
    }
}

void building::spawn_figure_pavillion() {
    if (!is_main())
        return;
    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0)
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days2 > 0)
            create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days3_or_play > 0)
            create_roaming_figure(FIGURE_DANCER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}
void building::spawn_figure_senet() {
    // TODO
    //    check_labor_problem();
    //    if (prev_part_building_id)
    //        return;
    //    building *part = b;
    //    for (int i = 0; i < 2; i++) {
    //        part = part->next();
    //        if (part->id)
    //            part->show_on_problem_overlay = show_on_problem_overlay;
    //
    //    }
    //    if (has_figure_of_type(FIGURE_CHARIOTEER))
    //        return;
    //    map_point road;
    //    if (map_has_road_access_hippodrome_rotation(x, y, &road, subtype.orientation)) {
    //        if (houses_covered <= 50 || data.entertainment.days1 <= 0)
    //            generate_labor_seeker(road.x, road.y);
    //
    //        int pct_workers = worker_percentage();
    //        int spawn_delay;
    //        if (pct_workers >= 100)
    //            spawn_delay = 7;
    //        else if (pct_workers >= 75)
    //            spawn_delay = 15;
    //        else if (pct_workers >= 50)
    //            spawn_delay = 30;
    //        else if (pct_workers >= 25)
    //            spawn_delay = 50;
    //        else if (pct_workers >= 1)
    //            spawn_delay = 80;
    //        else
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            figure *f = figure_create(FIGURE_CHARIOTEER, road.x, road.y, DIR_0_TOP_RIGHT);
    //            f->action_state = FIGURE_ACTION_94_ENTERTAINER_ROAMING;
    //            f->home() = b;
    //            figure_id = f->id;
    //            f->init_roaming();
    //
    //            if (!city_entertainment_hippodrome_has_race()) {
    //                // create mini-horses
    //                figure *horse1 = figure_create(FIGURE_HIPPODROME_HORSES, x + 2, y + 1, DIR_2_BOTTOM_RIGHT);
    //                horse1->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
    //                horse1->building_id = id;
    //                horse1->set_resource(0);
    //                horse1->speed_multiplier = 3;
    //
    //                figure *horse2 = figure_create(FIGURE_HIPPODROME_HORSES, x + 2, y + 2, DIR_2_BOTTOM_RIGHT);
    //                horse2->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
    //                horse2->building_id = id;
    //                horse1->set_resource(1);
    //                horse2->speed_multiplier = 2;
    //
    //                if (data.entertainment.days1 > 0) {
    //                    if (city_entertainment_show_message_hippodrome())
    //                        city_message_post(true, MESSAGE_WORKING_HIPPODROME, 0, 0);
    //
    //                }
    //            }
    //        }
    //    }
}

void building::spawn_figure_library() {
    common_spawn_roamer(FIGURE_LIBRARIAN, 50);
    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_LIBRARIAN))
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
    //            create_roaming_figure(road.x, road.y, FIGURE_LIBRARIAN);
    //        }
    //    }
}
void building::spawn_figure_mortuary() {
    common_spawn_roamer(FIGURE_EMBALMER, 50);
    //    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_BARBER))
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
    //            create_roaming_figure(road.x, road.y, FIGURE_BARBER);
    //        }
    //    }
}

void building::spawn_figure_dentist() {
    common_spawn_roamer(FIGURE_DENTIST, 50);
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

void building::set_greate_palace_graphic() {
    if (state != BUILDING_STATE_VALID)
        return;

    if (map_desirability_get(tile.grid_offset()) <= 30) {
        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_PALACE), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(id, tile, size, image_id_from_group(GROUP_BUILDING_PALACE_FANCY), TERRAIN_BUILDING);
    }
}

void building::spawn_figure_tax_collector() {
    if (type == BUILDING_TOWN_PALACE) {
        set_greate_palace_graphic();
    }

    //common_spawn_roamer(FIGURE_TAX_COLLECTOR, 50);

    check_labor_problem();
    if (has_figure_of_type(0, FIGURE_TAX_COLLECTOR)) {
        return;
    }

    if (!has_road_access) {
        return;
    }

    common_spawn_labor_seeker(50);

    int pct_workers = worker_percentage();
    int spawn_delay;
    if (pct_workers >= 100) {
        spawn_delay = 0;
    } else if (pct_workers >= 75) {
        spawn_delay = 1;
    } else if (pct_workers >= 50) {
        spawn_delay = 3;
    } else if (pct_workers >= 25) {
        spawn_delay = 7;
    } else if (pct_workers >= 1) {
        spawn_delay = 15;
    } else {
        return;
    }

    figure_spawn_delay++;
    if (figure_spawn_delay > spawn_delay) {
        figure_spawn_delay = 0;
        create_roaming_figure(FIGURE_TAX_COLLECTOR, FIGURE_ACTION_40_TAX_COLLECTOR_CREATED);
    }
}

int building::get_onespot_ready_production() {
    switch (type) {
    case BUILDING_POTTERY_WORKSHOP: return 10;
    }

    return 100;
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
        create_cartpusher(output_resource_first_id, get_onespot_ready_production());
    }
}

void building::spawn_figure_farm_harvests() {
    if (is_floodplain_farm()) { // floodplain farms
        // In OG Pharaoh, farms can NOT send out a cartpusher if the cartpusher
        // from the previous harvest is still alive. The farm will get "stuck"
        // and remain in active production till flooded, though the farm worker
        // still displays with the harvesting animation.
        if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER))
            return;

        if (has_road_access && data.industry.progress > 0) {
            int grid_offset = tile.grid_offset();
            int farm_fertility = map_get_fertility_for_farm(grid_offset);

            data.industry.ready_production = data.industry.progress * farm_fertility / 100;
            int expected_produce = farm_expected_produce(this);
            {
                figure *f = create_cartpusher(output_resource_first_id, expected_produce);
                building_farm_deplete_soil(this);

                f->sender_building_id = this->id;

                data.industry.progress = 0;
                data.industry.ready_production = 0;
                data.industry.worker_id = 0;
                data.industry.work_camp_id = 0;
                data.industry.labor_state = LABOR_STATE_NONE;
                data.industry.labor_days_left = 0;
                num_workers = 0;
            }

            if (output_resource_second_id != RESOURCE_NONE) {
                int rate = std::max<int>(1, output_resource_second_rate);
                int second_produce_expected = expected_produce / rate;
                figure *f = create_cartpusher(output_resource_second_id, second_produce_expected, FIGURE_ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER_2);
                f->sender_building_id = this->id;
            }
        }
    } else { // meadow farms
        if (has_road_access) {
            if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
                return;
            }
            create_cartpusher(output_resource_first_id, farm_expected_produce(this));
            building_industry_start_new_production(this);
        }
    }
}

void building::spawn_figure_wharf() {
    check_labor_problem();
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            ; // nothing
        } else {
            figure_spawn_delay++;
            if (data.industry.fishing_boat_id == 0 && figure_spawn_delay > spawn_delay) {
                figure_spawn_delay = 0;

                if (config_get(CONFIG_GP_CH_FISHING_WHARF_SPAWN_BOATS)) {
                    tile2i dock_tile(data.dock.dock_tiles[0]);
                    figure* f = figure_create(FIGURE_FISHING_BOAT, dock_tile, DIR_4_BOTTOM_LEFT);
                    f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
                    f->set_home(id);
                    set_figure(BUILDING_SLOT_BOAT, f);
                    random_generate_next();
                    f->wait_ticks = random_short() % 30; // ok
                    f->allow_move_type = EMOVE_BOAT;
                    data.industry.fishing_boat_id = f->id;
                }
            }
        }
    }
    
    bool cart_spawned = common_spawn_goods_output_cartpusher();
    if (cart_spawned) {
        if (data.industry.has_fish) {
            data.industry.has_fish = (stored_full_amount > 0);
        }
    }
}

void building::spawn_figure_shipyard() {
    //    check_labor_problem();
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        if (has_figure_of_type(FIGURE_FISHING_BOAT))
    //            return;
    //        int pct_workers = worker_percentage();
    //        if (pct_workers >= 100)
    //            data.industry.progress += 10;
    //        else if (pct_workers >= 75)
    //            data.industry.progress += 8;
    //        else if (pct_workers >= 50)
    //            data.industry.progress += 6;
    //        else if (pct_workers >= 25)
    //            data.industry.progress += 4;
    //        else if (pct_workers >= 1)
    //            data.industry.progress += 2;
    //
    //        if (data.industry.progress >= 160) {
    //            data.industry.progress = 0;
    //            map_point boat;
    //            if (map_water_can_spawn_fishing_boat(x, y, size, &boat)) {
    //                figure *f = figure_create(FIGURE_FISHING_BOAT, boat.x, boat.y, DIR_0_TOP_RIGHT);
    //                f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
    //                f->home() = b;
    //                figure_id = f->id;
    //            }
    //        }
    //    }
}

void building::spawn_figure_dock() {
    //    check_labor_problem();
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        int pct_workers = worker_percentage();
    //        int max_dockers;
    //        if (pct_workers >= 75)
    //            max_dockers = 3;
    //        else if (pct_workers >= 50)
    //            max_dockers = 2;
    //        else if (pct_workers > 0)
    //            max_dockers = 1;
    //        else {
    //            max_dockers = 0;
    //        }
    //        // count existing dockers
    //        int existing_dockers = 0;
    //        for (int i = 0; i < 3; i++) {
    //            if (data.dock.docker_ids[i]) {
    //                if (figure_get(data.dock.docker_ids[i])->type == FIGURE_DOCKER)
    //                    existing_dockers++;
    //                else {
    //                    data.dock.docker_ids[i] = 0;
    //                }
    //            }
    //        }
    //        if (existing_dockers > max_dockers) {
    //            // too many dockers, poof one of them
    //            for (int i = 2; i >= 0; i--) {
    //                if (data.dock.docker_ids[i]) {
    //                    figure_get(data.dock.docker_ids[i])->poof();
    //                    break;
    //                }
    //            }
    //        } else if (existing_dockers < max_dockers) {
    //            figure *f = figure_create(FIGURE_DOCKER, road.x, road.y, DIR_4_BOTTOM_LEFT);
    //            f->action_state = FIGURE_ACTION_132_DOCKER_IDLING;
    //            f->home() = b;
    //            for (int i = 0; i < 3; i++) {
    //                if (!data.dock.docker_ids[i]) {
    //                    data.dock.docker_ids[i] = f->id;
    //                    break;
    //                }
    //            }
    //        }
    //    }
}

void building::spawn_figure_granary() {
    check_labor_problem();
    map_point road;
    if (map_get_road_access_tile(tile, size, road)) { // map_has_road_access_granary(x, y, &road)
        common_spawn_labor_seeker(100);

        if (has_figure_of_type(0, FIGURE_STORAGE_YARD_DELIVERCART)) {
            return;
        }

        auto task = building_granary_determine_worker_task(this);
        if (task.status != GRANARY_TASK_NONE) {
            figure* f = figure_create(FIGURE_STORAGE_YARD_DELIVERCART, road, DIR_4_BOTTOM_LEFT);
            f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
            f->load_resource(task.resource, 0);
            set_figure(0, f->id);
            f->set_home(id);
        }
    }
}

int building::get_figures_number(e_figure_type ftype) {
    int gatherers_this_yard = 0;
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure* f = figure_get(i);
        if (f->has_type(ftype) && f->has_home(this)) {        // figure with type on map and  belongs to this building
            gatherers_this_yard++;
        }
    }

    return gatherers_this_yard;
}

bool building::can_spawn_bricklayer_man(e_figure_type ftype, int max_gatherers_per_building) {
    if (!is_guild()) {
        return false;
    }

    bool can_spawn = false;
    switch (ftype) {
    case FIGURE_BRICKLAYER:
        can_spawn = building_count_active(BUILDING_SMALL_MASTABA)
                        && (get_figures_number(FIGURE_BRICKLAYER) < data.guild.max_workers);
        break;
    }

    return can_spawn;
}

bool building::can_spawn_gatherer(e_figure_type ftype, int max_gatherers_per_building, int carry_per_person) {
    bool resource_reachable = false;
    switch (ftype) {
    case FIGURE_REED_GATHERER:
        resource_reachable = map_routing_citizen_found_terrain(road_access, nullptr, TERRAIN_MARSHLAND);
        break;

    case FIGURE_LUMBERJACK:
        resource_reachable = map_routing_citizen_found_terrain(road_access, nullptr, TERRAIN_TREE);
        break;
    }

    if (!resource_reachable) {
        return false;
    }

    int gatherers_this_yard = get_figures_number(ftype);

    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
        && gatherers_this_yard + (stored_amount() / carry_per_person) < (max_loads - gatherers_this_yard)) {
        return true;
    }

    return false;
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

void building::spawn_figure_tower() {
    check_labor_problem();
    map_point road;
    if (map_get_road_access_tile(tile, size, road)) {
        common_spawn_labor_seeker(50);
        if (num_workers <= 0)
            return;

        if (has_figure(0) && !has_figure(3)) { // has sentry but no ballista -> create
            create_figure_generic(FIGURE_BALLISTA, FIGURE_ACTION_180_BALLISTA_CREATED, BUILDING_SLOT_BALLISTA, DIR_0_TOP_RIGHT);
        }

        if (!has_figure(0)) {
            building_barracks_request_tower_sentry();
        }
    }
}
void building::spawn_figure_barracks() {
    check_labor_problem();
    //    map_point road;
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        //        if (pct_workers >= 100)
        //            spawn_delay = 8;
        //        else if (pct_workers >= 75)
        //            spawn_delay = 12;
        //        else if (pct_workers >= 50)
        //            spawn_delay = 16;
        //        else if (pct_workers >= 25)
        //            spawn_delay = 32;
        //        else if (pct_workers >= 1)
        //            spawn_delay = 48;
        //        else
        //            return;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;
            switch (subtype.barracks_priority) {
            case PRIORITY_FORT:
                if (!barracks_create_soldier())
                    barracks_create_tower_sentry();
                break;
            default:
                if (!barracks_create_tower_sentry())
                    barracks_create_soldier();
            }
        }
    }
}

void building::update_native_crop_progress() {
    data.industry.progress++;
    if (data.industry.progress >= 5) {
        data.industry.progress = 0;
    }

    map_image_set(tile.grid_offset(), image_id_from_group(GROUP_BUILDING_FARMLAND) + data.industry.progress);
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

void building::update_road_access() {
    // update building road access
}

bool building::figure_generate() {
    show_on_problem_overlay = 0;

    bool noble_generated = false;
    if (type >= BUILDING_HOUSE_COMMON_MANOR && type <= BUILDING_HOUSE_LUXURY_PALACE) {
        noble_generated = spawn_noble(noble_generated);
    } else if (type == BUILDING_REED_GATHERER) {
        spawn_figure_reed_gatherers();
    } else if (type == BUILDING_WOOD_CUTTERS) {
        spawn_figure_wood_cutters();
    } else if (is_workshop() || is_extractor()) {// farms are handled by a separate cycle in Pharaoh!
        spawn_figure_industry();
    } else if (is_tax_collector()) {
        spawn_figure_tax_collector();
    } else if (is_administration()) {
        common_spawn_figure_trigger(50);

        if (is_governor_mansion() && !has_figure(BUILDING_SLOT_GOVERNOR)) {
            tile2i road_tile;
            if (map_closest_road_within_radius(tile, size, 2, road_tile)) {
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
        case BUILDING_GRANARY: spawn_figure_granary(); break;
        case BUILDING_MUD_TOWER: spawn_figure_tower(); break;
        case BUILDING_POLICE_STATION: spawn_figure_police(); break;
        case BUILDING_DANCE_SCHOOL: spawn_figure_dancer(); break;
        case BUILDING_SENET_HOUSE: spawn_figure_senet(); break;
        case BUILDING_PAVILLION: spawn_figure_pavillion(); break;
        case BUILDING_SCRIBAL_SCHOOL: spawn_figure_school(); break;
        case BUILDING_LIBRARY: spawn_figure_library(); break;
        case BUILDING_WATER_LIFT: common_spawn_figure_trigger(50); break;
        case BUILDING_DENTIST: spawn_figure_dentist(); break;
        case BUILDING_MORTUARY: spawn_figure_mortuary(); break;
        case BUILDING_DOCK: spawn_figure_dock(); break;
        case BUILDING_FISHING_WHARF: spawn_figure_wharf(); break;
        case BUILDING_SHIPWRIGHT: spawn_figure_shipyard(); break;
        case BUILDING_UNUSED_NATIVE_HUT_88: spawn_figure_native_hut(); break;
        case BUILDING_UNUSED_NATIVE_MEETING_89: spawn_figure_native_meeting(); break;
        case BUILDING_UNUSED_NATIVE_CROPS_93: update_native_crop_progress(); break;

        case BUILDING_BARLEY_FARM:
        case BUILDING_FLAX_FARM:
        case BUILDING_GRAIN_FARM:
        case BUILDING_LETTUCE_FARM:
        case BUILDING_POMEGRANATES_FARM:
        case BUILDING_CHICKPEAS_FARM:
        case BUILDING_FIGS_FARM:
        case BUILDING_HENNA_FARM:
            spawn_figure_farms();
            break;

        case BUILDING_FORT_CHARIOTEERS:
        case BUILDING_FORT_ARCHERS:
        case BUILDING_FORT_INFANTRY:
            formation_legion_update_recruit_status(this);
            break;

        case BUILDING_RECRUITER:
            spawn_figure_barracks();
            break;

        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
        case BUILDING_CITY_PALACE:
        case BUILDING_MILITARY_ACADEMY:
            common_spawn_figure_trigger(100);
            break;

        default:
            dcast()->spawn_figure();
            break;
        }
    }

    return true;
}

void building::school_add_papyrus(int amount) {
    if (id > 0) {
        stored_full_amount += amount;
    }
}

void building_figure_generate() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure Generate");
    building_barracks_decay_tower_sentry_request();
    int max_id = building_get_highest_id();
    buildings_valid_do([] (building &b) {
        if (b.type == BUILDING_STORAGE_YARD_SPACE || (b.type == BUILDING_SENET_HOUSE && b.prev_part_building_id)) {
            return;
        }

        //b->update_road_access();
        b.figure_generate();
    });
}
