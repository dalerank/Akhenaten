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

        // only check if there is a figure
        if (figure_id < 0)
            return (get_figureID(i) > 0);

        figure *f = get_figure(i);
        if (f->state && f->home() == this) { // check if figure belongs to this building...
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

figure *building::create_roaming_figure(int _type, int created_action, int slot) {
    figure *f = figure_create(_type, road_access_x, road_access_y, DIR_0_TOP_RIGHT);
    f->action_state = created_action;
    f->set_home(id);
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
    figure *f = figure_create(_type, road_access_x, road_access_y, DIR_0_TOP_RIGHT);
    f->action_state = created_action;
    f->set_home(id);
    f->set_destination(destination->id);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    return f;
}
figure *building::create_cartpusher(int goods, int quantity, int created_action, int slot) {
    figure *f = figure_create(FIGURE_CART_PUSHER, road_access_x, road_access_y, DIR_4_BOTTOM_LEFT);
    f->action_state = created_action;
    f->load_resource(quantity, goods);
    f->set_home(id);
    f->set_destination(0);
    f->set_immigrant_home(0);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    f->wait_ticks = 30;
}

static int worker_percentage(const building *b) {
    return calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
}
static int generic_spawn_delay(building *b, int delay_shift = 2) {
    int pct_workers = worker_percentage(b);
    if (pct_workers >= 100)
        return generic_delay_table[delay_shift + 0];
    else if (pct_workers >= 75)
        return generic_delay_table[delay_shift + 1];
    else if (pct_workers >= 50)
        return generic_delay_table[delay_shift + 2];
    else if (pct_workers >= 25)
        return generic_delay_table[delay_shift + 3];
    else if (pct_workers >= 1)
        return generic_delay_table[delay_shift + 4];
    else
        return -1;
}
static void check_labor_problem(building *b) {
    if ((b->houses_covered <= 0 && b->labor_category != 255) || (b->labor_category == 255 && b->num_workers <= 0))
        b->show_on_problem_overlay = 2;
}
static void spawn_labor_seeker(building *b, int x, int y, int min_houses) {
    if (city_population() <= 0)
        return;
    if (config_get(CONFIG_GP_CH_GLOBAL_LABOUR)) {
        // If it can access Rome
        if (b->distance_from_entry)
            b->houses_covered = 2 * min_houses;
        else
            b->houses_covered = 0;
    } else if (b->houses_covered <= min_houses) {
//        if (b->figure_2 != nullptr) { // no figure slot available!
//            return;
        if (b->has_figure(1)) { // no figure slot available!
            return;
//        figure *f = figure_get(b->figure_id2);
//        if (!f->state || f->type != FIGURE_LABOR_SEEKER || f->building_id != b->id)
//            b->figure_id2 = 0;
        } else
            b->create_roaming_figure(FIGURE_LABOR_SEEKER, FIGURE_ACTION_125_ROAMING, true);
    }
}

bool building::common_spawn_figure_trigger(int _type, int delay_shift) {
    check_labor_problem(this);
    if (has_figure_of_type(0, _type))
        return false;
    if (road_is_accessible) {
        spawn_labor_seeker(this, road_access_x, road_access_y, 100);
        int pct_workers = worker_percentage(this);
        int spawn_delay = generic_spawn_delay(this, delay_shift);
        if (spawn_delay == -1)
            return false;
        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;
            return true;
        }
    }
}

static void spawn_figure_labor_seeker_only(building *b, int min_houses = 100) {
    check_labor_problem(b);
    if (b->road_is_accessible)
        spawn_labor_seeker(b, b->road_access_x, b->road_access_y, min_houses);
}
static void spawn_figure_work_camp(building *b) {
    if (b->common_spawn_figure_trigger(FIGURE_WORKER_PH, 0)) {
        building *dest = building_get(building_determine_worker_needed());
        figure *f = b->create_figure_with_destination(FIGURE_WORKER_PH, dest);
        dest->data.industry.worker_id = f->id;
    }
}

static int common_spawn_roamer(building * b, int type, int created_action = FIGURE_ACTION_125_ROAMING) {
    if (b->common_spawn_figure_trigger(type, 0)) {
        b->create_roaming_figure(type, created_action);
        return 1;
    }
    return 0;
}

static int spawn_patrician(building *b, int spawned) {
    return common_spawn_roamer(b, FIGURE_PATRICIAN);
}
static void spawn_figure_engineers_post(building *b) {
    common_spawn_roamer(b, FIGURE_ENGINEER, FIGURE_ACTION_60_ENGINEER_CREATED);
}
static void spawn_figure_prefecture(building *b) {
    common_spawn_roamer(b, FIGURE_PREFECT, FIGURE_ACTION_70_PREFECT_CREATED);
}
static void spawn_figure_police(building *b) {
    common_spawn_roamer(b, FIGURE_POLICEMAN, FIGURE_ACTION_70_PREFECT_CREATED);
}

static void spawn_figure_actor_colony(building *b) {
    if (b->common_spawn_figure_trigger(FIGURE_WORKER_PH, 0)) {
        building *dest = building_get(determine_venue_destination(b->road_access_x, b->road_access_y, BUILDING_THEATER, BUILDING_AMPHITHEATER, BUILDING_COLOSSEUM));
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            b->create_figure_with_destination(FIGURE_ACTOR, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        else
            b->create_figure_with_destination(FIGURE_ACTOR, dest, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}
static void spawn_figure_gladiator_school(building *b) {
    common_spawn_roamer(b, FIGURE_GLADIATOR, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
}
static void spawn_figure_lion_house(building *b) {
    common_spawn_roamer(b, FIGURE_LION_TAMER, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
}
static void spawn_figure_chariot_maker(building *b) {
    common_spawn_roamer(b, FIGURE_CHARIOTEER, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
}
static void spawn_figure_amphitheater(building *b) {
    // TODO
//    check_labor_problem(b);
//    if (has_figure_of_types(b, FIGURE_ACTOR, FIGURE_GLADIATOR))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        if (b->houses_covered <= 50 ||
//            (b->data.entertainment.days1 <= 0 && b->data.entertainment.days2 <= 0)) {
//            generate_labor_seeker(b, road.x, road.y);
//        }
//        int pct_workers = worker_percentage(b);
//        int spawn_delay;
//        if (pct_workers >= 100)
//            spawn_delay = 3;
//        else if (pct_workers >= 75)
//            spawn_delay = 7;
//        else if (pct_workers >= 50)
//            spawn_delay = 15;
//        else if (pct_workers >= 25)
//            spawn_delay = 29;
//        else if (pct_workers >= 1)
//            spawn_delay = 44;
//        else
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            figure *f;
//            if (b->data.entertainment.days1 > 0)
//                f = figure_create(FIGURE_GLADIATOR, road.x, road.y, DIR_0_TOP_RIGHT);
//            else
//                f = figure_create(FIGURE_ACTOR, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = FIGURE_ACTION_94_ENTERTAINER_ROAMING;
//            f->home() = b;
//            b->figure_id = f->id;
//            f->init_roaming();
//        }
//    }
}
static void spawn_figure_theater(building *b) {
    if (b->common_spawn_figure_trigger(FIGURE_ACTOR)) {
        if (b->data.entertainment.days1 <= 0)
            return;
        b->create_roaming_figure(FIGURE_ACTOR, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}
static void spawn_figure_hippodrome(building *b) {
    // TODO
//    check_labor_problem(b);
//    if (b->prev_part_building_id)
//        return;
//    building *part = b;
//    for (int i = 0; i < 2; i++) {
//        part = part->next();
//        if (part->id)
//            part->show_on_problem_overlay = b->show_on_problem_overlay;
//
//    }
//    if (b->has_figure_of_type(FIGURE_CHARIOTEER))
//        return;
//    map_point road;
//    if (map_has_road_access_hippodrome_rotation(b->x, b->y, &road, b->subtype.orientation)) {
//        if (b->houses_covered <= 50 || b->data.entertainment.days1 <= 0)
//            generate_labor_seeker(b, road.x, road.y);
//
//        int pct_workers = worker_percentage(b);
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
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_CHARIOTEER, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = FIGURE_ACTION_94_ENTERTAINER_ROAMING;
//            f->home() = b;
//            b->figure_id = f->id;
//            f->init_roaming();
//
//            if (!city_entertainment_hippodrome_has_race()) {
//                // create mini-horses
//                figure *horse1 = figure_create(FIGURE_HIPPODROME_HORSES, b->x + 2, b->y + 1, DIR_2_BOTTOM_RIGHT);
//                horse1->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
//                horse1->building_id = b->id;
//                horse1->set_resource(0);
//                horse1->speed_multiplier = 3;
//
//                figure *horse2 = figure_create(FIGURE_HIPPODROME_HORSES, b->x + 2, b->y + 2, DIR_2_BOTTOM_RIGHT);
//                horse2->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
//                horse2->building_id = b->id;
//                horse1->set_resource(1);
//                horse2->speed_multiplier = 2;
//
//                if (b->data.entertainment.days1 > 0) {
//                    if (city_entertainment_show_message_hippodrome())
//                        city_message_post(1, MESSAGE_WORKING_HIPPODROME, 0, 0);
//
//                }
//            }
//        }
//    }
}
static void spawn_figure_colosseum(building *b) {
    // TODO
//    check_labor_problem(b);
//    if (has_figure_of_types(b, FIGURE_GLADIATOR, FIGURE_LION_TAMER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        if (b->houses_covered <= 50 ||
//            (b->data.entertainment.days1 <= 0 && b->data.entertainment.days2 <= 0)) {
//            generate_labor_seeker(b, road.x, road.y);
//        }
//        int pct_workers = worker_percentage(b);
//        int spawn_delay;
//        if (pct_workers >= 100)
//            spawn_delay = 6;
//        else if (pct_workers >= 75)
//            spawn_delay = 12;
//        else if (pct_workers >= 50)
//            spawn_delay = 20;
//        else if (pct_workers >= 25)
//            spawn_delay = 40;
//        else if (pct_workers >= 1)
//            spawn_delay = 70;
//        else
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            figure *f;
//            if (b->data.entertainment.days1 > 0)
//                f = figure_create(FIGURE_LION_TAMER, road.x, road.y, DIR_0_TOP_RIGHT);
//            else {
//                f = figure_create(FIGURE_GLADIATOR, road.x, road.y, DIR_0_TOP_RIGHT);
//            }
//            f->action_state = FIGURE_ACTION_94_ENTERTAINER_ROAMING;
//            f->home() = b;
//            b->figure_id = f->id;
//            f->init_roaming();
//            if (b->data.entertainment.days1 > 0 || b->data.entertainment.days2 > 0) {
//                if (city_entertainment_show_message_colosseum())
//                    city_message_post(1, MESSAGE_WORKING_COLOSSEUM, 0, 0);
//
//            }
//        }
//    }
}

static void set_market_graphic(building *b) {
    if (b->state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(b->grid_offset) <= 30) {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_MARKET), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_MARKET_FANCY), TERRAIN_BUILDING);
    }
}
static void spawn_figure_market(building *b) {
    set_market_graphic(b);
    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 50);
        int pct_workers = worker_percentage(b);
        int spawn_delay;
        if (pct_workers >= 100)
            spawn_delay = 2;
        else if (pct_workers >= 75)
            spawn_delay = 5;
        else if (pct_workers >= 50)
            spawn_delay = 10;
        else if (pct_workers >= 25)
            spawn_delay = 20;
        else if (pct_workers >= 1)
            spawn_delay = 30;
        else
            return;
        if (!b->has_figure_of_type(0, FIGURE_MARKET_TRADER) && !b->has_figure_of_type(0, FIGURE_MARKET_BUYER)) {
            // market buyer
            building *dest = building_get(building_market_get_storage_destination(b));
            if (dest->id) {
                figure *f = b->create_figure_with_destination(FIGURE_MARKET_BUYER, dest, FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE);
                f->collecting_item_id = b->data.market.fetch_inventory_id;
            }
            else {
                // market trader
                b->figure_spawn_delay++;
                if (b->figure_spawn_delay > spawn_delay) {
                    b->figure_spawn_delay = 0;
                    b->create_roaming_figure(FIGURE_MARKET_TRADER);
                    return;
                }
            }
        }
    }
}

static void set_bathhouse_graphic(building *b) {
    if (b->state != BUILDING_STATE_VALID)
        return;
    if (map_terrain_exists_tile_in_area_with_type(b->x, b->y, b->size, TERRAIN_GROUNDWATER))
        b->has_water_access = 1;
    else
        b->has_water_access = 0;
    if (b->has_water_access && b->num_workers) {
        if (map_desirability_get(b->grid_offset) <= 30) {
            map_building_tiles_add(b->id, b->x, b->y, b->size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_WATER), TERRAIN_BUILDING);
        } else {
            map_building_tiles_add(b->id, b->x, b->y, b->size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_FANCY_WATER), TERRAIN_BUILDING);
        }
    } else {
        if (map_desirability_get(b->grid_offset) <= 30) {
            map_building_tiles_add(b->id, b->x, b->y, b->size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_NO_WATER), TERRAIN_BUILDING);
        } else {
            map_building_tiles_add(b->id, b->x, b->y, b->size,
                                   image_id_from_group(GROUP_BUILDING_BATHHOUSE_FANCY_NO_WATER), TERRAIN_BUILDING);
        }
    }
}
static void spawn_figure_bathhouse(building *b) {
    if (!b->has_water_access)
        b->show_on_problem_overlay = 2;
    common_spawn_roamer(b, FIGURE_BATHHOUSE_WORKER);
//    check_labor_problem(b);
//    if (!b->has_water_access)
//        b->show_on_problem_overlay = 2;
//
//    if (has_figure_of_type(b, FIGURE_BATHHOUSE_WORKER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road) && b->has_water_access) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = default_spawn_delay(b);
//        if (!spawn_delay)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_BATHHOUSE_WORKER);
//        }
//    }
}
static void spawn_figure_school(building *b) {
    check_labor_problem(b);
    if (b->has_figure_of_type(0, FIGURE_SCHOOL_CHILD))
        return;
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 50);
        int spawn_delay = generic_spawn_delay(b);
        if (spawn_delay == -1)
            return;
        b->figure_spawn_delay++;
        if (b->figure_spawn_delay > spawn_delay) {
            b->figure_spawn_delay = 0;

            figure *child1 = figure_create(FIGURE_SCHOOL_CHILD, road.x, road.y, DIR_0_TOP_RIGHT);
            child1->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(b->id);
            b->set_figure(0, child1->id); // first "child" (teacher) is the coupled figure to the school building
            child1->init_roaming_from_building(0);

            figure *child2 = figure_create(FIGURE_SCHOOL_CHILD, road.x, road.y, DIR_0_TOP_RIGHT);
            child2->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(b->id);
            child2->init_roaming_from_building(0);

            figure *child3 = figure_create(FIGURE_SCHOOL_CHILD, road.x, road.y, DIR_0_TOP_RIGHT);
            child3->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(b->id);
            child3->init_roaming_from_building(0);

            figure *child4 = figure_create(FIGURE_SCHOOL_CHILD, road.x, road.y, DIR_0_TOP_RIGHT);
            child4->action_state = FIGURE_ACTION_125_ROAMING;
            child1->set_home(b->id);
            child4->init_roaming_from_building(0);
        }
    }
}
static void spawn_figure_library(building *b) {
    common_spawn_roamer(b, FIGURE_LIBRARIAN);
    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_LIBRARIAN))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_LIBRARIAN);
//        }
//    }
}
static void spawn_figure_academy(building *b) {
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_TEACHER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_TEACHER);
//        }
//    }
}
static void spawn_figure_barber(building *b) {
    common_spawn_roamer(b, FIGURE_BARBER);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_BARBER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_BARBER);
//        }
//    }
}
static void spawn_figure_doctor(building *b) {
    common_spawn_roamer(b, FIGURE_DOCTOR);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_DOCTOR))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_DOCTOR);
//        }
//    }
}
static void spawn_figure_hospital(building *b) {
    common_spawn_roamer(b, FIGURE_SURGEON);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_SURGEON))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_SURGEON);
//        }
//    }
}
static void spawn_figure_physician(building *b) {
    common_spawn_roamer(b, FIGURE_BATHHOUSE_WORKER);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_BATHHOUSE_WORKER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_BATHHOUSE_WORKER);
//        }
//    }
}
static void spawn_figure_magistrate(building *b) {
    common_spawn_roamer(b, FIGURE_MAGISTRATE);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_MAGISTRATE))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = generic_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_MAGISTRATE);
//        }
//    }
}
static void spawn_figure_temple(building *b) {
    common_spawn_roamer(b, FIGURE_PRIEST);
//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_PRIEST) ||
//        (building_is_large_temple(b->type) && b->prev_part_building_id)) {
//        return;
//    }
//
//    map_point road;
//    if ((building_is_temple(b->type) && map_has_road_access(b->x, b->y, b->size, &road)) ||
//        (building_is_large_temple(b->type) && map_has_road_access_temple_complex(b->x, b->y, &road))) {
//
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int pct_workers = worker_percentage(b);
//        int spawn_delay;
//        if (model_get_building(b->type)->laborers <= 0)
//            spawn_delay = 7;
//        else if (pct_workers >= 100)
//            spawn_delay = 3;
//        else if (pct_workers >= 75)
//            spawn_delay = 7;
//        else if (pct_workers >= 50)
//            spawn_delay = 10;
//        else if (pct_workers >= 25)
//            spawn_delay = 15;
//        else if (pct_workers >= 1)
//            spawn_delay = 20;
//        else
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_PRIEST);
//        }
//    }
}

static void set_water_supply_graphic(building *b) {
    if (b->state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(b->grid_offset) <= 30) {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_BATHHOUSE_WATER), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_BATHHOUSE_WATER) + 2, TERRAIN_BUILDING);
    }
}
static void spawn_figure_watersupply(building *b) {
    common_spawn_roamer(b, FIGURE_WATER_CARRIER);
//    set_water_supply_graphic(b);

//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_WATER_CARRIER))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 100);
//        int pct_workers = worker_percentage(b);
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
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_WATER_CARRIER, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = ACTION_1_ROAMING;
//            f->home() = b;
//            b->figure_id = f->id;
//        }
//    }
}

static void set_senate_graphic(building *b) {
    if (b->state != BUILDING_STATE_VALID)
        return;
    if (map_desirability_get(b->grid_offset) <= 30) {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_SENATE), TERRAIN_BUILDING);
    } else {
        map_building_tiles_add(b->id, b->x, b->y, b->size,
                               image_id_from_group(GROUP_BUILDING_SENATE_FANCY), TERRAIN_BUILDING);
    }
}
static void spawn_figure_tax_collector(building *b) {
    if (b->type == BUILDING_SENATE_UPGRADED)
        set_senate_graphic(b);

    common_spawn_roamer(b, FIGURE_TAX_COLLECTOR);

//    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_TAX_COLLECTOR))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int pct_workers = worker_percentage(b);
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
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_TAX_COLLECTOR, road.x, road.y, DIR_0_TOP_RIGHT);
//            f->action_state = FIGURE_ACTION_40_TAX_COLLECTOR_CREATED;
//            f->home() = b;
//            b->figure_id = f->id;
//        }
//    }
}
static void spawn_figure_senate(building *b) {
    check_labor_problem(b);
//    if (b->has_figure_of_type(FIGURE_MAGISTRATE))
//        return;
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 50);
//        int spawn_delay = default_spawn_delay(b);
//        if (spawn_delay == -1)
//            return;
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > spawn_delay) {
//            b->figure_spawn_delay = 0;
//            create_roaming_figure(b, road.x, road.y, FIGURE_MAGISTRATE);
//        }
    }
}
static void spawn_figure_mission_post(building *b) {
//    if (b->has_figure_of_type(FIGURE_MISSIONARY))
//        return;
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        if (city_population() > 0) {
//            city_buildings_set_mission_post_operational();
//            b->figure_spawn_delay++;
//            if (b->figure_spawn_delay > 1) {
//                b->figure_spawn_delay = 0;
//                create_roaming_figure(b, road.x, road.y, FIGURE_MISSIONARY);
//            }
//        }
//    }
}

#include "city/data.h"

static void spawn_figure_industry(building *b) {
//    if (true) // todo: floodplain farms
//        return;

    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        if (b->labor_category != 255) { // normal farms
            spawn_labor_seeker(b, road.x, road.y, 50);
            if (b->has_figure_of_type(0, FIGURE_CART_PUSHER))
                return;
            if (building_industry_has_produced_resource(b)) {
                building_industry_start_new_production(b);
                b->create_cartpusher(b->output_resource_id, 100);
//                figure *f = figure_create(FIGURE_CART_PUSHER, road.x, road.y, DIR_4_BOTTOM_LEFT);
//                f->action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
////                f->resource_id = b->output_resource_id;
////                f->loads_counter = 1;
//                f->load_resource(100, b->output_resource_id);
//                f->home() = b;
//                b->figure_id = f->id;
//                f->wait_ticks = 30;
            }
        } else { // floodplain farms!!
            if (b->has_figure_of_type(0, FIGURE_CART_PUSHER))
                return;
            if (building_industry_has_produced_resource(b)) {
                b->create_cartpusher(b->output_resource_id, b->data.industry.progress / 2.5);
//                figure *f = figure_create(FIGURE_CART_PUSHER, road.x, road.y, DIR_4_BOTTOM_LEFT);
//                f->action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
////                f->resource_id = b->output_resource_id;
////                f->loads_counter = b->data.industry.progress / 250;
//                f->load_resource(b->data.industry.progress / 2.5, b->output_resource_id);
//                f->home() = b;
//                b->figure_id = f->id;
//                f->wait_ticks = 30;
                building_farm_deplete_soil(b);
                b->data.industry.progress = 0;
                b->data.industry.worker_id = 0;
                b->data.industry.labor_state = 0;
                b->data.industry.labor_days_left = 0;
                b->num_workers = 0;
            }
        }
    }
}
static void spawn_figure_wharf(building *b) {
//    check_labor_problem(b);
//    if (b->data.industry.fishing_boat_id) {
//        figure *f = figure_get(b->data.industry.fishing_boat_id);
//        if (f->state != FIGURE_STATE_ALIVE || f->type != FIGURE_FISHING_BOAT)
//            b->data.industry.fishing_boat_id = 0;
//
//    }
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        if (b->has_figure_of_type(FIGURE_CART_PUSHER))
//            return;
//        if (b->figure_spawn_delay) {
//            b->figure_spawn_delay = 0;
//            b->data.industry.has_fish = 0;
//            b->output_resource_id = RESOURCE_MEAT_C3;
//            figure *f = figure_create(FIGURE_CART_PUSHER, road.x, road.y, DIR_4_BOTTOM_LEFT);
//            f->action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
//            f->set_resource(RESOURCE_MEAT_C3);
//            f->home() = b;
//            b->figure_id = f->id;
//            f->wait_ticks = 30;
//        }
//    }
}
static void spawn_figure_shipyard(building *b) {
//    check_labor_problem(b);
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        if (b->has_figure_of_type(FIGURE_FISHING_BOAT))
//            return;
//        int pct_workers = worker_percentage(b);
//        if (pct_workers >= 100)
//            b->data.industry.progress += 10;
//        else if (pct_workers >= 75)
//            b->data.industry.progress += 8;
//        else if (pct_workers >= 50)
//            b->data.industry.progress += 6;
//        else if (pct_workers >= 25)
//            b->data.industry.progress += 4;
//        else if (pct_workers >= 1)
//            b->data.industry.progress += 2;
//
//        if (b->data.industry.progress >= 160) {
//            b->data.industry.progress = 0;
//            map_point boat;
//            if (map_water_can_spawn_fishing_boat(b->x, b->y, b->size, &boat)) {
//                figure *f = figure_create(FIGURE_FISHING_BOAT, boat.x, boat.y, DIR_0_TOP_RIGHT);
//                f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
//                f->home() = b;
//                b->figure_id = f->id;
//            }
//        }
//    }
}
static void spawn_figure_dock(building *b) {
//    check_labor_problem(b);
//    map_point road;
//    if (map_has_road_access(b->x, b->y, b->size, &road)) {
//        spawn_labor_seeker(b, road.x, road.y, 50);
//        int pct_workers = worker_percentage(b);
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
//            if (b->data.dock.docker_ids[i]) {
//                if (figure_get(b->data.dock.docker_ids[i])->type == FIGURE_DOCKER)
//                    existing_dockers++;
//                else {
//                    b->data.dock.docker_ids[i] = 0;
//                }
//            }
//        }
//        if (existing_dockers > max_dockers) {
//            // too many dockers, poof one of them
//            for (int i = 2; i >= 0; i--) {
//                if (b->data.dock.docker_ids[i]) {
//                    figure_get(b->data.dock.docker_ids[i])->poof();
//                    break;
//                }
//            }
//        } else if (existing_dockers < max_dockers) {
//            figure *f = figure_create(FIGURE_DOCKER, road.x, road.y, DIR_4_BOTTOM_LEFT);
//            f->action_state = FIGURE_ACTION_132_DOCKER_IDLING;
//            f->home() = b;
//            for (int i = 0; i < 3; i++) {
//                if (!b->data.dock.docker_ids[i]) {
//                    b->data.dock.docker_ids[i] = f->id;
//                    break;
//                }
//            }
//        }
//    }
}
static void spawn_figure_warehouse(building *b) {
    check_labor_problem(b);
    building *space = b;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id)
            space->show_on_problem_overlay = b->show_on_problem_overlay;
    }
    map_point road;
    if (map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, b->size, &road) ||
        map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, 3, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 100);
        if (b->has_figure_of_type(0, FIGURE_WAREHOUSEMAN))
            return;
        int resource = 0;
        int amount = 0;
        int task = building_warehouse_determine_worker_task(b, &resource, &amount);
        if (task != WAREHOUSE_TASK_NONE) {
            figure *f = figure_create(FIGURE_WAREHOUSEMAN, road.x, road.y, DIR_4_BOTTOM_LEFT);
            f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
            if (task == WAREHOUSE_TASK_GETTING) {
                f->load_resource(0, RESOURCE_NONE);
                f->collecting_item_id = resource;
            } else {
                if (amount >= 0) { // delivering
                    f->load_resource(amount * 100, resource);
                    building_warehouse_remove_resource(b, resource, amount);
                }
                else // getting
                    f->load_resource(0, resource);
            }
            b->set_figure(0, f->id);
            f->set_home(b->id);
        }
    }
}
static void spawn_figure_granary(building *b) {
    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) { //map_has_road_access_granary(b->x, b->y, &road)
        spawn_labor_seeker(b, road.x, road.y, 100);
        if (b->has_figure_of_type(0, FIGURE_WAREHOUSEMAN))
            return;
        int task = building_granary_determine_worker_task(b);
        if (task != GRANARY_TASK_NONE) {
            figure *f = figure_create(FIGURE_WAREHOUSEMAN, road.x, road.y, DIR_4_BOTTOM_LEFT);
            f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
            f->load_resource(0, task);
            b->set_figure(0, f->id);
            f->set_home(b->id);
        }
    }
}

#include "city/data_private.h"

static bool can_spawn_hunter(building *b) { // no cache because fuck the system (also I can't find the memory offset for this)
    int lodges = 0;
    int hunters_total = 0;
    int hunters_this_lodge = 0;
    int huntables = city_data.figure.animals;
//    for (int b = 0; b < MAX_BUILDINGS[GAME_ENV]; b++) {
//        if (building_get(b)->type == 115)
//            lodges++;
//    }
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->type == 73) { // hunter
            hunters_total++;
            if (f->home() == b) // belongs to this lodge
                hunters_this_lodge++;
        }
        if (hunters_total >= huntables)
            break;
    }
    if (hunters_total < huntables && hunters_this_lodge < 3 && hunters_this_lodge + b->loads_stored < 5)
        return true;
    return false;
}
static void spawn_figure_hunting_lodge(building *b) {
    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 50);
        int pct_workers = worker_percentage(b);
        int spawn_delay;
        if (pct_workers >= 100)
            spawn_delay = 0;
        else if (pct_workers >= 75)
            spawn_delay = 1;
        else if (pct_workers >= 50)
            spawn_delay = 3;
        else if (pct_workers >= 25)
            spawn_delay = 7;
        else if (pct_workers >= 1)
            spawn_delay = 15;
        else
            return;
        b->figure_spawn_delay++;
        if (b->figure_spawn_delay > spawn_delay && can_spawn_hunter(b)) {
            b->figure_spawn_delay = 0;
            figure *f = figure_create(FIGURE_HUNTER, road.x, road.y, DIR_4_BOTTOM_LEFT);
            f->action_state = ACTION_8_RECALCULATE;
            f->set_home(b->id);
//            f->wait_ticks = 30;
//            f->loads_counter = 1;
        }
        if (b->has_figure_of_type(0, FIGURE_CART_PUSHER))
            return;
        if (b->loads_stored) {
            figure *f = figure_create(FIGURE_CART_PUSHER, road.x, road.y, DIR_4_BOTTOM_LEFT);
            f->action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
            int loads_to_carry = fmin(b->loads_stored, 4);
            b->loads_stored -= loads_to_carry;
            f->load_resource(loads_to_carry * 100, RESOURCE_GAMEMEAT);
            f->set_home(b->id);
            b->set_figure(0, f->id);
            f->wait_ticks = 30;
        }
    }
}

static void spawn_figure_native_hut(building *b) {
//    map_image_set(b->grid_offset, image_id_from_group(GROUP_BUILDING_NATIVE) + (map_random_get(b->grid_offset) & 1));
//    if (b->has_figure_of_type(FIGURE_INDIGENOUS_NATIVE))
//        return;
//    int x_out, y_out;
//    if (b->subtype.native_meeting_center_id > 0 &&
//        map_terrain_get_adjacent_road_or_clear_land(b->x, b->y, b->size, &x_out, &y_out)) {
//        b->figure_spawn_delay++;
//        if (b->figure_spawn_delay > 4) {
//            b->figure_spawn_delay = 0;
//            figure *f = figure_create(FIGURE_INDIGENOUS_NATIVE, x_out, y_out, DIR_0_TOP_RIGHT);
//            f->action_state = FIGURE_ACTION_158_NATIVE_CREATED;
//            f->home() = b;
//            b->figure_id = f->id;
//        }
//    }
}
static void spawn_figure_native_meeting(building *b) {
//    map_building_tiles_add(b->id, b->x, b->y, 2,
//                           image_id_from_group(GROUP_BUILDING_NATIVE) + 2, TERRAIN_BUILDING);
//    if (city_buildings_is_mission_post_operational() && !b->has_figure_of_type(FIGURE_NATIVE_TRADER)) {
//        int x_out, y_out;
//        if (map_terrain_get_adjacent_road_or_clear_land(b->x, b->y, b->size, &x_out, &y_out)) {
//            b->figure_spawn_delay++;
//            if (b->figure_spawn_delay > 8) {
//                b->figure_spawn_delay = 0;
//                figure *f = figure_create(FIGURE_NATIVE_TRADER, x_out, y_out, DIR_0_TOP_RIGHT);
//                f->action_state = FIGURE_ACTION_162_NATIVE_TRADER_CREATED;
//                f->home() = b;
//                b->figure_id = f->id;
//            }
//        }
//    }
}

static void spawn_figure_tower(building *b) {
    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 50);
        if (b->num_workers <= 0)
            return;
        if (b->has_figure(0) && !b->has_figure(3)) { // has sentry but no ballista -> create
            figure *f = figure_create(FIGURE_BALLISTA, b->x, b->y, DIR_0_TOP_RIGHT);
            b->set_figure(3, f->id);
            f->set_home(b->id);
            f->action_state = FIGURE_ACTION_180_BALLISTA_CREATED;
        }
        if (!b->has_figure(0))
            building_barracks_request_tower_sentry();

    }
}
static void spawn_figure_barracks(building *b) {
    check_labor_problem(b);
    map_point road;
    if (map_has_road_access(b->x, b->y, b->size, &road)) {
        spawn_labor_seeker(b, road.x, road.y, 100);
        int pct_workers = worker_percentage(b);
        int spawn_delay;
        if (pct_workers >= 100)
            spawn_delay = 8;
        else if (pct_workers >= 75)
            spawn_delay = 12;
        else if (pct_workers >= 50)
            spawn_delay = 16;
        else if (pct_workers >= 25)
            spawn_delay = 32;
        else if (pct_workers >= 1)
            spawn_delay = 48;
        else
            return;
        b->figure_spawn_delay++;
        if (b->figure_spawn_delay > spawn_delay) {
            b->figure_spawn_delay = 0;
            map_has_road_access(b->x, b->y, b->size, &road);
            switch (b->subtype.barracks_priority) {
                case PRIORITY_FORT:
                    if (!building_barracks_create_soldier(b, road.x, road.y))
                        building_barracks_create_tower_sentry(b, road.x, road.y);

                    break;
                default:
                    if (!building_barracks_create_tower_sentry(b, road.x, road.y))
                        building_barracks_create_soldier(b, road.x, road.y);

            }

        }
    }
}

static void update_native_crop_progress(building *b) {
    b->data.industry.progress++;
    if (b->data.industry.progress >= 5)
        b->data.industry.progress = 0;

    map_image_set(b->grid_offset, image_id_from_group(GROUP_BUILDING_FARMLAND) + b->data.industry.progress);
}

void building_figure_generate(void) {
    int patrician_generated = 0;
    building_barracks_decay_tower_sentry_request();
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        if (b->type == BUILDING_WAREHOUSE_SPACE || (b->type == BUILDING_HIPPODROME && b->prev_part_building_id))
            continue;

        // update building road access
        map_point road;
        b->road_is_accessible = map_has_road_access(b->x, b->y, b->size, &road);
        b->road_access_x = road.x;
        b->road_access_y = road.y;

        b->show_on_problem_overlay = 0;
        // range of building types
        if (b->type >= BUILDING_HOUSE_SMALL_VILLA && b->type <= BUILDING_HOUSE_LUXURY_PALACE) {
            patrician_generated = spawn_patrician(b, patrician_generated);
        }
        else if (b->is_farm() || b->is_workshop() || b->is_extractor())
            spawn_figure_industry(b);
        else if (b->is_tax_collector())
            spawn_figure_tax_collector(b);
        else if (b->is_senate())
            spawn_figure_senate(b);
        else if (b->is_temple() || b->is_large_temple())
            spawn_figure_temple(b);
        else {
            // single building type
            switch (b->type) {
                case BUILDING_WAREHOUSE:
                    spawn_figure_warehouse(b); break;
                case BUILDING_GRANARY:
                    spawn_figure_granary(b); break;
                case BUILDING_TOWER:
                    spawn_figure_tower(b); break;
                case BUILDING_ENGINEERS_POST:
                    spawn_figure_engineers_post(b); break;
                case BUILDING_PREFECTURE:
                    if (GAME_ENV == ENGINE_ENV_PHARAOH)
                        spawn_figure_police(b);
                    else
                        spawn_figure_prefecture(b);
                    break;
                case BUILDING_FIREHOUSE:
                    spawn_figure_prefecture(b); break;
                case BUILDING_WATER_SUPPLY:
                    spawn_figure_watersupply(b); break;
                case BUILDING_ACTOR_COLONY:
                    spawn_figure_actor_colony(b); break;
                case BUILDING_GLADIATOR_SCHOOL:
                    spawn_figure_gladiator_school(b); break;
                case BUILDING_LION_HOUSE:
                    spawn_figure_lion_house(b); break;
                case BUILDING_CHARIOT_MAKER:
                    spawn_figure_chariot_maker(b); break;
                case BUILDING_AMPHITHEATER:
                    spawn_figure_amphitheater(b); break;
                case BUILDING_THEATER:
                    spawn_figure_theater(b); break;
                case BUILDING_HIPPODROME:
                    spawn_figure_hippodrome(b); break;
                case BUILDING_COLOSSEUM:
                    spawn_figure_colosseum(b); break;
                case BUILDING_MARKET:
                    spawn_figure_market(b); break;
                case BUILDING_PHYSICIAN:
                    spawn_figure_physician(b); break;
                case BUILDING_BATHHOUSE:
                    spawn_figure_bathhouse(b); break;
                case BUILDING_SCHOOL:
                    spawn_figure_school(b); break;
                case BUILDING_LIBRARY:
                    spawn_figure_library(b); break;
                case BUILDING_ACADEMY:
                    spawn_figure_academy(b); break;
                case BUILDING_BARBER:
                    spawn_figure_barber(b); break;
                case BUILDING_DOCTOR:
                    spawn_figure_doctor(b); break;
                case BUILDING_HOSPITAL:
                    spawn_figure_hospital(b); break;
                case BUILDING_MISSION_POST:
                    spawn_figure_mission_post(b); break;
                case BUILDING_DOCK:
                    spawn_figure_dock(b); break;
                case BUILDING_WHARF:
                    spawn_figure_wharf(b); break;
                case BUILDING_SHIPYARD:
                    spawn_figure_shipyard(b); break;
                case BUILDING_NATIVE_HUT:
                    spawn_figure_native_hut(b); break;
                case BUILDING_NATIVE_MEETING:
                    spawn_figure_native_meeting(b); break;
                case BUILDING_NATIVE_CROPS:
                    update_native_crop_progress(b); break;
                case BUILDING_FORT:
                    formation_legion_update_recruit_status(b); break;
                case BUILDING_BARRACKS:
                    spawn_figure_barracks(b); break;
                case BUILDING_VILLAGE_PALACE:
                case BUILDING_TOWN_PALACE:
                case BUILDING_CITY_PALACE:
                case BUILDING_MILITARY_ACADEMY:
                    spawn_figure_labor_seeker_only(b); break;
                case BUILDING_HUNTING_LODGE:
                    spawn_figure_hunting_lodge(b); break;
                case BUILDING_WORK_CAMP:
                    spawn_figure_work_camp(b); break;
                case BUILDING_COURTHOUSE:
                    spawn_figure_magistrate(b); break;
            }
        }
    }
}
