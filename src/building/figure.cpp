#include "figuretype/entertainer.h"
#include "building/figure.h"

#include "building/barracks.h"
#include "building/granary.h"
#include "building/industry.h"
#include "building/market.h"
#include "building/model.h"
#include "building/warehouse.h"
#include "city/buildings.h"
#include "city/entertainment.h"
#include "city/message.h"
#include "city/population.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/image.h"
#include "figure/figure.h"
#include "figure/formation_legion.h"
#include "figure/movement.h"
#include "game/resource.h"
#include "map/building_tiles.h"
#include "map/desirability.h"
#include "map/image.h"
#include "map/random.h"
#include "map/road_access.h"
#include "map/terrain.h"
#include "map/water.h"

#include <math.h>
#include <city/floods.h>
#include <core/random.h>
#include <map/routing/routing.h>

const int generic_delay_table[] = {
        0,
        1,
        3,
        7,
        15,
        29,
        44
};

figure *building::get_figure(int i) {
    return figure_get(get_figureID(i));
}
void building::bind_iob_figures(io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[0]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[1]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[2]);
    iob->bind(BIND_SIGNATURE_UINT16, &figure_ids_array[3]);
}
void building::set_figure(int i, int figure_id) {
//    // correct index if out of bounds
//    if (i < 0)
//        i = 0;
//    if (i >= MAX_FIGURES_PER_BUILDING)
//        i = MAX_FIGURES_PER_BUILDING - 1;

//    // correct id if below zero
//    if (id < 0)
//        figure_id = 0;

    figure_ids_array[i] = figure_id;
}
void building::set_figure(int i, figure *f) {
//    if (f == nullptr)
//        return;
    set_figure(i, f->id);
}
void building::remove_figure(int i) {
    set_figure(i, 0);
}
bool building::has_figure(int i, int figure_id) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++)
            if (has_figure(i, figure_id))
                has_any = true;
        return has_any;
    } else {
        figure *f = get_figure(i);
        if (f->state && (f->home() == this || f->immigrant_home() == this)) { // check if figure belongs to this building...
            if (figure_id < 0) // only check if there is a figure
                return true;
            return (f->id == figure_id);
        } else { // decouple if figure does not belong to this building - assume cache is incorrect
            remove_figure(i);
            return false;
        }
    }
}
bool building::has_figure(int i, figure *f) {
    return has_figure(i, f->id);
}
bool building::has_figure_of_type(int i, int _type) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++)
            if (get_figure(i)->type == _type)
                has_any = true;
        return has_any;
    }
    else
        return (get_figure(i)->type == _type);
}
int building::get_figure_slot(figure *f) {
    // seatrch through all the slots, check if figure matches
    for (int i = 0; i < MAX_FIGURES_PER_BUILDING; i++) {
        if (has_figure(i, f))
            return i;
    }
    return -1;
}

figure *building::create_figure_generic(int _type, int created_action, int slot, int created_dir) {
    figure *f = figure_create(_type, road_access.x(), road_access.y(), created_dir);
    f->action_state = created_action;
    f->set_home(id);
    return f;
}
figure *building::create_roaming_figure(int _type, int created_action, int slot) {
    figure *f = create_figure_generic(_type, created_action, slot, figure_roam_direction);
    f->set_destination(0);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    f->init_roaming_from_building(figure_roam_direction);

    // update building to have a different roamer direction for next time
    figure_roam_direction += 2;
    if (figure_roam_direction > 6)
        figure_roam_direction = 0;

    return f;
}
figure *building::create_figure_with_destination(int _type, building *destination, int created_action, int slot) {
    figure *f = create_figure_generic(_type, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->set_destination(destination->id);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    return f;
}
figure *building::create_cartpusher(int resource_id, int quantity, int created_action, int slot) {
    // TODO: industry cartpushers do not spawn in the correct place?

    figure *f = create_figure_generic(FIGURE_CART_PUSHER, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->load_resource(quantity, resource_id);
    f->set_destination(0);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    f->wait_ticks = 30;
}

int building::worker_percentage() {
    return calc_percentage(num_workers, model_get_building(type)->laborers);
}
int building::figure_spawn_timer() {
    int pct_workers = worker_percentage();
    if (pct_workers >= 100)
        return 0;
    else if (pct_workers >= 75)
        return 1;
    else if (pct_workers >= 50)
        return 3;
    else if (pct_workers >= 25)
        return 7;
    else if (pct_workers >= 1)
        return 15;
    else
        return -1;
}
void building::check_labor_problem() {
    if ((houses_covered <= 0 && labor_category != 255) || (labor_category == 255 && num_workers <= 0))
        show_on_problem_overlay = 2;
}
void building::common_spawn_labor_seeker(int min_houses) {
    if (city_population() <= 0)
        return;
    if (config_get(CONFIG_GP_CH_GLOBAL_LABOUR)) {
        // If it can access Rome
        if (distance_from_entry)
            houses_covered = 2 * min_houses;
        else
            houses_covered = 0;
        if (houses_covered >= 300)
            houses_covered = 300;
    } else if (houses_covered <= min_houses) {
        if (has_figure(1)) // no figure slot available!
            return;
        else
            create_roaming_figure(FIGURE_LABOR_SEEKER, FIGURE_ACTION_125_ROAMING, true);
    }
}
bool building::common_spawn_figure_trigger(int min_houses) {
    check_labor_problem();
    if (has_figure(0))
        return false;
    if (has_road_access) {
        if (main() == this) // only spawn from the main building
            common_spawn_labor_seeker(min_houses);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1)
            return false;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;
            return true;
        }
    }
}
bool building::common_spawn_roamer(int type, int min_houses, int created_action) {
    if (common_spawn_figure_trigger(min_houses)) {
        create_roaming_figure(type, created_action);
        return true;
    }
    return false;
}
bool building::common_spawn_goods_output_cartpusher(bool only_one, bool only_full_loads, int min_carry, int max_carry) {
    // can only have one?
    if (only_one && has_figure_of_type(0, FIGURE_CART_PUSHER))
        return false;

    // no checking for work force? doesn't matter anyways.... there's no instance
    // in the game that allows cartpushers to spawn before the workers disappear!
    if (has_road_access) {
        while (stored_full_amount >= min_carry) {
            int amounts_to_carry = fmin(stored_full_amount, max_carry);
            if (only_full_loads)
                amounts_to_carry -= amounts_to_carry % 100; // remove pittance
            create_cartpusher(output_resource_id, amounts_to_carry);
            stored_full_amount -= amounts_to_carry;
            if (only_one || stored_full_amount == 0) // done once, or out of goods?
                return true;
        }
    }
    return false;
}

void building::spawn_figure_work_camp() {
    if (common_spawn_figure_trigger(100)) {
        building *dest = building_get(building_determine_worker_needed());
        figure *f = create_figure_with_destination(FIGURE_WORKER_PH, dest);
        dest->data.industry.worker_id = f->id;
    }
}

bool building::spawn_patrician(bool spawned) {
    return common_spawn_roamer(FIGURE_PATRICIAN, 50);
}
void building::spawn_figure_engineers_post() {
    common_spawn_roamer(FIGURE_ENGINEER, 50, FIGURE_ACTION_60_ENGINEER_CREATED);
}
void building::spawn_figure_firehouse() {
    common_spawn_roamer(FIGURE_PREFECT, 50, FIGURE_ACTION_70_PREFECT_CREATED);
}
void building::spawn_figure_police() {
    common_spawn_roamer(FIGURE_POLICEMAN, 50, FIGURE_ACTION_70_PREFECT_CREATED);
}

void building::spawn_figure_juggler() {
    if (common_spawn_figure_trigger(50)) {
        building *dest = building_get(determine_venue_destination(road_access.x(), road_access.y(), BUILDING_PAVILLION, BUILDING_BANDSTAND, BUILDING_BOOTH));
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            if (dest->id > 0)
                create_figure_with_destination(FIGURE_JUGGLER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else
            common_spawn_roamer(FIGURE_ACTOR, 50,FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}
void building::spawn_figure_musician() {
    if (common_spawn_figure_trigger(50)) {
        building *dest = building_get(determine_venue_destination(road_access.x(), road_access.y(), BUILDING_PAVILLION, BUILDING_BANDSTAND, 0));
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            if (dest->id > 0)
                create_figure_with_destination(FIGURE_MUSICIAN, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else
            common_spawn_roamer(FIGURE_GLADIATOR, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}
void building::spawn_figure_dancer() {
    if (common_spawn_figure_trigger(50)) {
        building *dest = building_get(determine_venue_destination(road_access.x(), road_access.y(), BUILDING_PAVILLION, 0, 0));
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            if (dest->id > 0)
                create_figure_with_destination(FIGURE_DANCER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else
            common_spawn_roamer(FIGURE_LION_TAMER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}

void building::spawn_figure_booth() {
    if (!is_main())
        return;
    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0)
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}
void building::spawn_figure_bandstand() {
    if (!is_main())
        return;
    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0)
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days2 > 0)
            create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
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

void building::set_market_graphic() {
    if (state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(tile.grid_offset()) <= 30) {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_MARKET), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_MARKET_FANCY), TERRAIN_BUILDING);
    }
}
void building::spawn_figure_market() {
    set_market_graphic();
    check_labor_problem();

    if (common_spawn_figure_trigger(50)) {
        // market buyer
        if (!has_figure_of_type(1, FIGURE_MARKET_BUYER)) {
            building *dest = building_get(building_market_get_storage_destination(this));
            if (dest->id) {
                figure *f = create_figure_with_destination(FIGURE_MARKET_BUYER, dest, FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, 1);
                f->collecting_item_id = data.market.fetch_inventory_id;
            }
        }

        // market trader
        int spawn_delay = figure_spawn_timer();
        if (!has_figure_of_type(0, FIGURE_MARKET_TRADER)) {
            if (data.market.inventory[0] > 0
                || data.market.inventory[1] > 0
                || data.market.inventory[2] > 0
                || data.market.inventory[3] > 0
                || data.market.inventory[4] > 0
                || data.market.inventory[5] > 0
                || data.market.inventory[6] > 0) { // do not spawn trader if bazaar is 100% empty!
                figure_spawn_delay++;
                if (figure_spawn_delay > spawn_delay) {
                    figure_spawn_delay = 0;
                    create_roaming_figure(FIGURE_MARKET_TRADER);
                    return;
                }
            }
        }
    }
}

void building::set_bathhouse_graphic() {
    if (state != BUILDING_STATE_VALID)
        return;
    if (map_terrain_exists_tile_in_area_with_type(tile.x(), tile.y(), size, TERRAIN_GROUNDWATER))
        has_water_access = true;
    else
        has_water_access = false;
    if (has_water_access && num_workers) {
        if (map_desirability_get(tile.grid_offset()) <= 30) {
            map_building_tiles_add(id, tile.x(), tile.y(), size,
                                   image_id_from_group(GROUP_BUILDING_WATER_SUPPLY), TERRAIN_BUILDING);
        } else {
            map_building_tiles_add(id, tile.x(), tile.y(), size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_FANCY_WATER), TERRAIN_BUILDING);
        }
    } else {
        if (map_desirability_get(tile.grid_offset()) <= 30) {
            map_building_tiles_add(id, tile.x(), tile.y(), size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_NO_WATER), TERRAIN_BUILDING);
        } else {
            map_building_tiles_add(id, tile.x(), tile.y(), size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_FANCY_NO_WATER), TERRAIN_BUILDING);
        }
    }
}
void building::spawn_figure_bathhouse() {
    if (!has_water_access)
        show_on_problem_overlay = 2;
    common_spawn_roamer(FIGURE_BATHHOUSE_WORKER, 50);
//    check_labor_problem();
//    if (!has_water_access)
//        show_on_problem_overlay = 2;
//
//    if (has_figure_of_type(FIGURE_BATHHOUSE_WORKER))
//        return;
//    map_point road;
//    if (map_has_road_access(x, y, size, &road) && has_water_access) {
//        spawn_labor_seeker(50);
//        int spawn_delay = default_spawn_delay();
//        if (!spawn_delay)
//            return;
//        figure_spawn_delay++;
//        if (figure_spawn_delay > spawn_delay) {
//            figure_spawn_delay = 0;
//            create_roaming_figure(road.x, road.y, FIGURE_BATHHOUSE_WORKER);
//        }
//    }
}
void building::spawn_figure_school() {
    check_labor_problem();
    if (has_figure_of_type(0, FIGURE_SCHOOL_CHILD))
        return;
    map_point road;
    if (map_has_road_access(tile.x(), tile.y(), size, &road)) {
        common_spawn_labor_seeker(50);
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1)
            return;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;

            figure *child1 = figure_create(FIGURE_SCHOOL_CHILD, road.x(), road.y(), DIR_0_TOP_RIGHT);
            child1->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(id);
            set_figure(0, child1->id); // first "child" (teacher) is the coupled figure to the school building
            child1->init_roaming_from_building(0);

            figure *child2 = figure_create(FIGURE_SCHOOL_CHILD, road.x(), road.y(), DIR_0_TOP_RIGHT);
            child2->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(id);
            child2->init_roaming_from_building(0);

            figure *child3 = figure_create(FIGURE_SCHOOL_CHILD, road.x(), road.y(), DIR_0_TOP_RIGHT);
            child3->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(id);
            child3->init_roaming_from_building(0);

            figure *child4 = figure_create(FIGURE_SCHOOL_CHILD, road.x(), road.y(), DIR_0_TOP_RIGHT);
            child4->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(id);
            child4->init_roaming_from_building(0);
        }
    }
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
void building::spawn_figure_barber() {
    common_spawn_roamer(FIGURE_BARBER, 50);
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
void building::spawn_figure_doctor() {
    common_spawn_roamer(FIGURE_DOCTOR, 50);
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
void building::spawn_figure_hospital() {
    common_spawn_roamer(FIGURE_SURGEON, 50);
}
void building::spawn_figure_physician() {
    common_spawn_roamer(FIGURE_BATHHOUSE_WORKER, 50);
}
void building::spawn_figure_magistrate() {
    common_spawn_roamer(FIGURE_MAGISTRATE, 50);
}
void building::spawn_figure_temple() {
    if (is_main())
        common_spawn_roamer(FIGURE_PRIEST, 50);
}

void building::set_water_supply_graphic() {
    if (state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(tile.grid_offset()) <= 30) {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_WATER_SUPPLY), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_WATER_SUPPLY) + 2, TERRAIN_BUILDING);
    }
}
void building::spawn_figure_watersupply() {
    common_spawn_roamer(FIGURE_WATER_CARRIER, 50);
//    set_water_supply_graphic();

//    check_labor_problem();
//    if (has_figure_of_type(FIGURE_WATER_CARRIER))
//        return;
//    map_point road;
//    if (map_has_road_access(x, y, size, &road)) {
//        spawn_labor_seeker(100);
//        int pct_workers = worker_percentage();
//        int spawn_delay;
//        if (pct_workers >= 100)
//            spawn_delay = 0;
//        else if (pct_workers >= 75)
//            spawn_delay = 1;
//        else if (pct_workers >= 50)
//            spawn_delay = 3;
//        else if (pct_workers >= 25)
//            spawn_delay = 7;
//        else if (pct_workers >= 1)
//            spawn_delay = 15;
//        else
//            return;
//        figure_spawn_delay++;
//        if (figure_spawn_delay > spawn_delay) {
//            figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_WATER_CARRIER, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = ACTION_1_ROAMING;
//            f->home() = b;
//            figure_id = f->id;
//        }
//    }
}

void building::set_senate_graphic() {
    if (state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(tile.grid_offset()) <= 30) {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_SENATE), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(id, tile.x(), tile.y(), size,
                               image_id_from_group(GROUP_BUILDING_SENATE_FANCY), TERRAIN_BUILDING);
    }
}
void building::spawn_figure_tax_collector() {
    if (type == BUILDING_SENATE_UPGRADED)
        set_senate_graphic();

    common_spawn_roamer(FIGURE_TAX_COLLECTOR, 50);

//    check_labor_problem();
//    if (has_figure_of_type(FIGURE_TAX_COLLECTOR))
//        return;
//    map_point road;
//    if (map_has_road_access(x, y, size, &road)) {
//        spawn_labor_seeker(50);
//        int pct_workers = worker_percentage();
//        int spawn_delay;
//        if (pct_workers >= 100)
//            spawn_delay = 0;
//        else if (pct_workers >= 75)
//            spawn_delay = 1;
//        else if (pct_workers >= 50)
//            spawn_delay = 3;
//        else if (pct_workers >= 25)
//            spawn_delay = 7;
//        else if (pct_workers >= 1)
//            spawn_delay = 15;
//        else
//            return;
//        figure_spawn_delay++;
//        if (figure_spawn_delay > spawn_delay) {
//            figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_TAX_COLLECTOR, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = FIGURE_ACTION_40_TAX_COLLECTOR_CREATED;
//            f->home() = b;
//            figure_id = f->id;
//        }
//    }
}

#include "city/data.h"

void building::spawn_figure_industry() {
    check_labor_problem();
    if (has_road_access) {
        common_spawn_labor_seeker(50);
        if (has_figure_of_type(0, FIGURE_CART_PUSHER))
            return;
        if (building_industry_has_produced_resource(this)) {
            building_industry_start_new_production(this);
            create_cartpusher(output_resource_id, 100);
        }
    }
}
void building::spawn_figure_farms() {
    bool is_floodplain = building_is_floodplain_farm(this);
    if (!is_floodplain && has_road_access) { // only for meadow farms
        common_spawn_labor_seeker(50);
        if (building_farm_time_to_deliver(false, output_resource_id)) // UGH!!
            spawn_figure_farm_harvests();
    }
}
void building::spawn_figure_farm_harvests() {
    if (is_floodplain_farm()) { // floodplain farms
        // In OG Pharaoh, farms can NOT send out a cartpusher if the cartpusher
        // from the previous harvest is still alive. The farm will get "stuck"
        // and remain in active production till flooded, though the farm worker
        // still displays with the harvesting animation.
        if (has_figure_of_type(0, FIGURE_CART_PUSHER))
            return;
        if (has_road_access && data.industry.progress > 0) {
            create_cartpusher(output_resource_id, farm_expected_produce(this));
            building_farm_deplete_soil(this);
            data.industry.progress = 0;
            data.industry.worker_id = 0;
            data.industry.labor_state = 0;
            data.industry.labor_days_left = 0;
            num_workers = 0;
        }
    } else { // meadow farms
        if (has_road_access) {
            if (has_figure_of_type(0, FIGURE_CART_PUSHER))
                return;
            create_cartpusher(output_resource_id, farm_expected_produce(this));
            building_industry_start_new_production(this);
        }
    }
}
void building::spawn_figure_wharf() {
    common_spawn_figure_trigger(100);
//    if (common_spawn_figure_trigger()) {
//        create_figure_generic(FIGURE_FISHING_BOAT, ACTION_8_RECALCULATE, 0, DIR_4_BOTTOM_LEFT);
//    }
    common_spawn_goods_output_cartpusher();




//    check_labor_problem();
//    if (data.industry.fishing_boat_id) {
//        figure *f = figure_get(data.industry.fishing_boat_id);
//        if (f->state != FIGURE_STATE_ALIVE || f->type != FIGURE_FISHING_BOAT)
//            data.industry.fishing_boat_id = 0;
//
//    }
//    map_point road;
//    if (map_has_road_access(x, y, size, &road)) {
//        spawn_labor_seeker(50);
//        if (has_figure_of_type(FIGURE_CART_PUSHER))
//            return;
//        if (figure_spawn_delay) {
//            figure_spawn_delay = 0;
//            data.industry.has_fish = 0;
//            output_resource_id = RESOURCE_FIGS;
//            figure *f = figure_create(FIGURE_CART_PUSHER, road.x, road.y, DIR_4_BOTTOM_LEFT);
//            f->action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
//            f->set_resource(RESOURCE_FIGS);
//            f->home() = b;
//            figure_id = f->id;
//            f->wait_ticks = 30;
//        }
//    }
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
void building::spawn_figure_warehouse() {
    check_labor_problem();
    building *space = this;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id)
            space->show_on_problem_overlay = show_on_problem_overlay;
    }
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int resource = 0;
        int amount = 0;
        int task = building_warehouse_determine_worker_task(this, &resource, &amount);
        if (task != WAREHOUSE_TASK_NONE && amount > 0) {

            // assume amount has been set to more than one.
//            if (true) // TODO: multiple loads setting?????
//                amount = 1;

            if (!has_figure(0)) {
                figure *f = figure_create(FIGURE_WAREHOUSEMAN, road_access.x(), road_access.y(), DIR_4_BOTTOM_LEFT);
                f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;

                switch (task) {
                    case WAREHOUSE_TASK_GETTING:
                    case WAREHOUSE_TASK_GETTING_MOAR:
                        f->load_resource(0, RESOURCE_NONE);
                        f->collecting_item_id = resource;
                        break;
                    case WAREHOUSE_TASK_DELIVERING:
                    case WAREHOUSE_TASK_EMPTYING:
                        amount = fmin(amount, 400);
                        f->load_resource(amount, resource);
                        building_warehouse_remove_resource(this, resource, amount);
                        break;
                }
                set_figure(0, f->id);
                f->set_home(id);

            } else if (task == WAREHOUSE_TASK_GETTING_MOAR && !has_figure_of_type(1,FIGURE_WAREHOUSEMAN)) {
                figure *f = figure_create(FIGURE_WAREHOUSEMAN, road_access.x(), road_access.y(), DIR_4_BOTTOM_LEFT);
                f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;

                f->load_resource(0, RESOURCE_NONE);
                f->collecting_item_id = resource;

                set_figure(1, f->id);
                f->set_home(id);
            }
        }
    }
}
void building::spawn_figure_granary() {
    check_labor_problem();
    map_point road;
    if (map_has_road_access(tile.x(), tile.y(), size, &road)) { //map_has_road_access_granary(x, y, &road)
        common_spawn_labor_seeker(100);
        if (has_figure_of_type(0, FIGURE_WAREHOUSEMAN))
            return;
        int task = building_granary_determine_worker_task(this);
        if (task != GRANARY_TASK_NONE) {
            figure *f = figure_create(FIGURE_WAREHOUSEMAN, road.x(), road.y(), DIR_4_BOTTOM_LEFT);
            f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
            f->load_resource(0, task);
            set_figure(0, f->id);
            f->set_home(id);
        }
    }
}

#include "city/data_private.h"

bool building::can_spawn_hunter() { // no cache because fuck the system (also I can't find the memory offset for this)
    int hunters_total = 0;
    int hunters_this_lodge = 0;
    int huntables = city_data.figure.animals;
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->is(FIGURE_HUNTER)) { // figure with type on map
            hunters_total++;
            if (f->has_home(this)) // belongs to this building
                hunters_this_lodge++;
        }
        if (hunters_total >= huntables)
            break;
    }
    // max 3 per building
    // can not have more hunters than preys on map
    // can only spawn if there's space for more game meat in the building
    if (hunters_total < huntables && hunters_this_lodge < 3 && hunters_this_lodge + (stored_full_amount / 100) < (5 - hunters_this_lodge))
        return true;
    return false;
}
void building::spawn_figure_hunting_lodge() {
    check_labor_problem();
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1)
            return;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay && can_spawn_hunter()) {
            figure_spawn_delay = 0;
            create_figure_generic(FIGURE_HUNTER, ACTION_8_RECALCULATE, 0, DIR_4_BOTTOM_LEFT);
        }
    }
    common_spawn_goods_output_cartpusher();
}

bool building::can_spawn_gatherer(figure_type ftype, int max_gatherers_per_building, int carry_per_person) {
    int gatherers_this_yard = 0;
    bool resource_reachable = false;
    switch (ftype) {
        case FIGURE_REED_GATHERER:
            resource_reachable = map_routing_citizen_found_terrain(road_access.x(), road_access.y(), nullptr, nullptr, TERRAIN_MARSHLAND);
            break;
        case FIGURE_LUMBERJACK:
            resource_reachable = map_routing_citizen_found_terrain(road_access.x(), road_access.y(), nullptr, nullptr, TERRAIN_TREE);
            break;
    }
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->is(ftype)) { // figure with type on map
            if (f->has_home(this)) // belongs to this building
                gatherers_this_yard++;
        }
    }
    // max 5 per building
    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
    && gatherers_this_yard + (stored_full_amount / carry_per_person) < (max_loads - gatherers_this_yard))
        return true;
    return false;
}
void building::spawn_figure_reed_gatherers() {
    check_labor_problem();
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1)
            return;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;

            while (can_spawn_gatherer(FIGURE_REED_GATHERER, 5, 50)) {
                auto f = create_figure_generic(FIGURE_REED_GATHERER, ACTION_8_RECALCULATE, 0, DIR_4_BOTTOM_LEFT);
                random_generate_next();
                f->wait_ticks = random_short() % 30; // ok
            }
        }
    }
    common_spawn_goods_output_cartpusher();
}

void building::spawn_figure_wood_cutters() {
    check_labor_problem();
    if (has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1)
            return;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;

            while (can_spawn_gatherer(FIGURE_LUMBERJACK, 3, 25)) {
                auto f = create_figure_generic(FIGURE_LUMBERJACK, ACTION_8_RECALCULATE, 0, DIR_4_BOTTOM_LEFT);
                random_generate_next();
                f->wait_ticks = random_short() % 30; // ok
            }
        }
    }
    common_spawn_goods_output_cartpusher();
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
    if (map_has_road_access(tile.x(), tile.y(), size, &road)) {
        common_spawn_labor_seeker(50);
        if (num_workers <= 0)
            return;
        if (has_figure(0) && !has_figure(3)) // has sentry but no ballista -> create
            create_figure_generic(FIGURE_BALLISTA, FIGURE_ACTION_180_BALLISTA_CREATED, 3, DIR_0_TOP_RIGHT);
        if (!has_figure(0))
            building_barracks_request_tower_sentry();
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
    if (data.industry.progress >= 5)
        data.industry.progress = 0;

    map_image_set(tile.grid_offset(), image_id_from_group(GROUP_BUILDING_FARMLAND) + data.industry.progress);
}

void building::update_road_access() {
    // update building road access
//    map_point road;
    switch (type) {
        case BUILDING_WAREHOUSE:
            has_road_access = map_has_road_access(tile.x(), tile.y(), 3, &road_access);
            break;
        case BUILDING_BURNING_RUIN:
            has_road_access = burning_ruin_can_be_accessed(tile.x(), tile.y(), &road_access);
            break;
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST:
            if (is_main()) {
                int orientation = (5 - (data.monuments.variant / 2)) % 4;
                has_road_access = map_has_road_access_temple_complex(tile.x(), tile.y(), orientation, false, &road_access);
            }
            break;
        default:
            if (id == 17)
                int a = 4;
            has_road_access = map_has_road_access(tile.x(), tile.y(), size, &road_access);
            break;
    }
    // TODO: Temple Complexes
//    road_access.x() = road.x;
//    road_access.y() = road.y;
}
bool building::figure_generate() {
    show_on_problem_overlay = 0;

    bool patrician_generated = false;
    if (type >= BUILDING_HOUSE_SMALL_VILLA && type <= BUILDING_HOUSE_LUXURY_PALACE)
        patrician_generated = spawn_patrician(patrician_generated);
    else if (type == BUILDING_REED_GATHERER)
        spawn_figure_reed_gatherers();
    else if (type == BUILDING_WOOD_CUTTERS)
        spawn_figure_wood_cutters();
    else if (is_workshop() || is_extractor()) // farms are handled by a separate cycle in Pharaoh!
        spawn_figure_industry();
    else if (is_tax_collector())
        spawn_figure_tax_collector();
    else if (is_senate())
        common_spawn_figure_trigger(50);
    else if (is_temple() || is_large_temple())
        spawn_figure_temple();
    else {
        // single building type
        switch (type) {
            case BUILDING_WAREHOUSE:
                spawn_figure_warehouse(); break;
            case BUILDING_GRANARY:
                spawn_figure_granary(); break;
            case BUILDING_TOWER:
                spawn_figure_tower(); break;
            case BUILDING_ENGINEERS_POST:
                spawn_figure_engineers_post(); break;
            case BUILDING_POLICE_STATION:
                if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    spawn_figure_police();
                else
                    spawn_figure_firehouse();
                break;
            case BUILDING_FIREHOUSE:
                spawn_figure_firehouse(); break;
            case BUILDING_WATER_SUPPLY:
                spawn_figure_watersupply(); break;
            case BUILDING_JUGGLER_SCHOOL:
                spawn_figure_juggler(); break;
            case BUILDING_CONSERVATORY:
                spawn_figure_musician(); break;
            case BUILDING_DANCE_SCHOOL:
                spawn_figure_dancer(); break;
            case BUILDING_BANDSTAND:
                spawn_figure_bandstand(); break;
            case BUILDING_BOOTH:
                spawn_figure_booth(); break;
            case BUILDING_SENET_HOUSE:
                spawn_figure_senet(); break;
            case BUILDING_PAVILLION:
                spawn_figure_pavillion(); break;
            case BUILDING_MARKET:
                spawn_figure_market(); break;
            case BUILDING_PHYSICIAN:
                spawn_figure_physician(); break;
            case BUILDING_MENU_MONUMENTS:
                spawn_figure_bathhouse(); break;
            case BUILDING_SCHOOL:
                spawn_figure_school(); break;
            case BUILDING_LIBRARY:
                spawn_figure_library(); break;
            case BUILDING_WATER_LIFT:
                common_spawn_figure_trigger(50); break;
            case BUILDING_DENTIST:
                spawn_figure_barber(); break;
            case BUILDING_APOTHECARY:
                spawn_figure_doctor(); break;
            case BUILDING_MORTUARY:
                spawn_figure_hospital(); break;
//            case BUILDING_MISSION_POST:
//                spawn_figure_mission_post(); break;
            case BUILDING_DOCK:
                spawn_figure_dock(); break;
            case BUILDING_FISHING_WHARF:
                spawn_figure_wharf(); break;
            case BUILDING_SHIPYARD:
                spawn_figure_shipyard(); break;
            case BUILDING_NATIVE_HUT:
                spawn_figure_native_hut(); break;
            case BUILDING_NATIVE_MEETING:
                spawn_figure_native_meeting(); break;
            case BUILDING_NATIVE_CROPS:
                update_native_crop_progress(); break;
            case BUILDING_BARLEY_FARM:
            case BUILDING_FLAX_FARM:
            case BUILDING_GRAIN_FARM:
            case BUILDING_LETTUCE_FARM:
            case BUILDING_POMEGRANATES_FARM:
            case BUILDING_CHICKPEAS_FARM:
            case BUILDING_FIGS_FARM:
            case BUILDING_HENNA_FARM:
                spawn_figure_farms(); break;
            case BUILDING_MENU_FORTS:
                formation_legion_update_recruit_status(this); break;
            case BUILDING_RECRUITER:
                spawn_figure_barracks(); break;
            case BUILDING_VILLAGE_PALACE:
            case BUILDING_TOWN_PALACE:
            case BUILDING_CITY_PALACE:
            case BUILDING_MILITARY_ACADEMY:
                common_spawn_figure_trigger(100); break;
            case BUILDING_HUNTING_LODGE:
                spawn_figure_hunting_lodge(); break;
            case BUILDING_WORK_CAMP:
                spawn_figure_work_camp(); break;
            case BUILDING_COURTHOUSE:
                spawn_figure_magistrate(); break;
        }
    }
}

void building_figure_generate(void) {
    building_barracks_decay_tower_sentry_request();
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        if (b->type == BUILDING_WAREHOUSE_SPACE || (b->type == BUILDING_SENET_HOUSE && b->prev_part_building_id))
            continue;

        b->update_road_access();
        b->figure_generate();
    }
}
