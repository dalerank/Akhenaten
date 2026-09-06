#include "figure_cartpusher.h"

#include "building/building_barracks.h"
#include "building/building_delivery_path.h"
#include "building/building_granary.h"
#include "building/building_food_mill.h"
#include "city/city_industry.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/monuments.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "city/city_recorded_paths.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "game/game.h"
#include "graphics/image.h"
#include "grid/figure.h"
#include "grid/road_network.h"
#include "grid/terrain.h"
#include "window/building/figures.h"
#include "graphics/elements/ui.h"
#include "grid/routing/routing_terrain.h"
#include "game/game_config.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_cartpusher);

const figure_cartpusher_action_tokens_t ANK_CONFIG_ENUM(figure_cartpusher_action_tokens)

static const int CART_OFFSET_MULTIPLE_LOADS_FOOD[] = {0, 0, 8, 16, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const int CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[] = {0, 0, 0, 0, 0, 8, 0, 16, 24, 32, 40, 48, 56, 64, 72, 80};
static const int CART_OFFSET_8_LOADS_FOOD[] = {0, 40, 48, 56, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void figure_carrier::load_resource(e_resource resource, int amount) {
    base.resource_id = resource;
    base.resource_amount_full = amount;
}

void figure_carrier::append_resource(e_resource resource, int amount) {
    assert(base.resource_id == RESOURCE_NONE || base.resource_id == resource);
    if (base.resource_id == RESOURCE_NONE) {
        base.resource_id = resource;
        base.resource_amount_full = 0;
    }
    base.resource_amount_full += amount;
}

int figure_carrier::dump_resource(int amount) {
    amount = std::min<int>(amount, base.resource_amount_full);
    base.resource_amount_full -= amount;

    // automatically clear field if carrying nothing
    if (base.resource_amount_full == 0)
        base.resource_id = RESOURCE_NONE;

    return base.resource_amount_full;
}

int figure::get_carrying_amount() {
    return resource_amount_full;
}

static bool building_keeps_visitor_paths(building *b) {
    return b && b->params().flags.keeps_visitor_paths;
}

static void cartpusher_handoff_visitor_path(figure &f, building *dest) {
    if (!f.trail_path_id) {
        return;
    }

    building *home = f.home();
    building *home_main = home ? home->main() : nullptr;
    building *dest_main = dest ? dest->main() : nullptr;
    const bool home_keeps = building_keeps_visitor_paths(home_main);
    const bool dest_keeps = building_keeps_visitor_paths(dest_main);

    if (home_keeps && dest_keeps) {
        const int copy = g_recorded_paths.duplicate(f.trail_path_id);
        if (copy) {
            g_recorded_paths.building_push(home_main->id, copy);
        }
        g_recorded_paths.handoff_to_building(f, dest_main->id);
    } else if (dest_keeps) {
        g_recorded_paths.handoff_to_building(f, dest_main->id);
    } else if (home_keeps) {
        g_recorded_paths.handoff_to_building(f, home_main->id);
    }
}

void figure_cartpusher::do_deliver(bool warehouseman, int action_done, int action_fail) {
    base.animctx.frame = 0;
    base.wait_ticks++;

    if ((!warehouseman && base.wait_ticks >= 10) || (warehouseman && base.wait_ticks >= 4)) {
        base.wait_ticks = 0;

        int carrying = base.get_carrying_amount();
        e_resource resource = base.get_resource();
        building *dest = destination();

        if (resource == RESOURCE_NONE || carrying <= 0) {
            cartpusher_handoff_visitor_path(base, dest);
            if (!base.trail_path_id) {
                figure_recorded_path_acquire(base);
            }
            base.progress_inside_speed = 0;
            return advance_action(action_done);

        } else if (!dest) {
            return advance_action(action_fail);

        } else {
            int amount_single_turn = std::min(carrying, UNITS_PER_LOAD);
            bool deposited = false;

            switch (dest->type) {
            case BUILDING_GRANARY:
            case BUILDING_GRANARY_UP:
            case BUILDING_FOOD_MILL:
            case BUILDING_STORAGE_YARD:
            case BUILDING_STORAGE_ROOM: {
                    building_storage *storage = dest->dcast_storage();
                    int accepting = storage ? storage->accepting_amount(resource) : 0;
                    int total_depositable = std::min<int>(carrying, accepting);

                    if (total_depositable <= 0) {
                        if (warehouseman) {
                            advance_action(ACTION_8_RECALCULATE);
                        } else {
                            determine_deliveryman_destination();
                        }
                        return;
                    }

                    int amount = storage->add_resource(base.resource_id, amount_single_turn, /*force*/false);
                    if (amount != -1) {
                        dump_resource(amount_single_turn);
                        deposited = true;
                    } else {
                        if (warehouseman) {
                            advance_action(action_fail);
                        } else {
                            determine_deliveryman_destination();
                        }
                        return;
                    }
                }
                break;

            case BUILDING_RECRUITER:
            case BUILDING_SHIPWRIGHT:
            case BUILDING_SCRIBAL_SCHOOL:
            case BUILDING_INDUSTRY_OFFICE:
            case BUILDING_SENET_HOUSE:
            case BUILDING_ZOO:
            case BUILDING_POLICE_STATION: {
                    building_impl *b = dest->dcast();
                    bool ok = b->add_resource(resource, amount_single_turn);
                    if (!ok) {
                        advance_action(action_fail);
                        return;
                    }
                    dump_resource(amount_single_turn);
                    deposited = true;
                }
                break;

            case BUILDING_VILLAGE_PALACE:
            case BUILDING_TOWN_PALACE:
            case BUILDING_CITY_PALACE: {
                    e_finance_request_type request_type = efinance_request_gold_delivered;
                    if (base.home()->dcast_mine()) {
                        request_type = efinance_request_gold_delivered;
                    } else if (base.home()->dcast_tax_collector()) {
                        request_type = efinance_request_tax_collected;
                    }
                    events::emit(event_finance_request{ request_type, amount_single_turn });
                    dump_resource(amount_single_turn);
                    deposited = true;
                }
                break;

            default:                              // workshop
                if (dest->stored_amount(resource) < 200) {
                    building_workshop_add_raw_material(dest, amount_single_turn, resource);
                    dump_resource(amount_single_turn);
                    deposited = true;
                } else {
                    return advance_action(action_fail);
                }
                break;
            }

            if (deposited) {
                cartpusher_handoff_visitor_path(base, dest);
            }
        }

        // Re-read after dump ? locals above are stale once the last load is dropped.
        if (base.get_resource() == RESOURCE_NONE || base.get_carrying_amount() <= 0) {
            if (!base.trail_path_id) {
                figure_recorded_path_acquire(base);
            }
            base.progress_inside_speed = 0;
            return advance_action(action_done);
        }
    }
}

void figure_cartpusher::calculate_destination(bool warehouseman) {
    set_destination(nullptr);
    base.animctx.frame = 0;
    base.wait_ticks++;

    if (!warehouseman) {
        if (base.wait_ticks > destination_wait_threshold()) {
            base.wait_ticks = 0;
            determine_deliveryman_destination();
        }
    } else {
        building* b = home();
        if (base.wait_ticks > 2) {
            base.wait_ticks = 0;
            if (home()->type == BUILDING_GRANARY || home()->type == BUILDING_FOOD_MILL) {
                determine_granaryman_destination();
            } else {
                determine_storageyard_cart_destination();
            }
        }
    }
}

int figure_cartpusher::destination_wait_threshold() {
    if (game_features::gameplay_enhanced_walker_move_boost.to_bool()) {
        return 10;
    }
    return current_params().wait_on_calculate_destination;
}

void figure_cartpusher::determine_deliveryman_destination() {
    base.destination_tile = tile2i::invalid;

    // before we start... check that resource is not empty.
    if (base.resource_id == RESOURCE_NONE || base.get_carrying_amount() == 0) {
        return advance_action(ACTION_27_CARTPUSHER_RETURNING);
    }

    building *home_b = home();
    if (!home_b) {
        return advance_action(ACTION_8_RECALCULATE);
    }
    auto pred = cartpusher_predict_deliveryman_destination(tile(), base.resource_id, *home_b);
    set_destination(pred.destination);

    if (has_destination()) {
        switch (pred.kind) {
        case e_delivery_dest_kind::palace:
            return advance_action(ACTION_11_CARTPUSHER_DELIVERING_GOLD);
        case e_delivery_dest_kind::storage_yard:
            return advance_action(ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
        case e_delivery_dest_kind::granary:
            return advance_action(ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
        case e_delivery_dest_kind::workshop:
            return advance_action(ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP);
        default:
            // Kind/destination mismatch ? don't keep a stuck dest into recalc.
            set_destination(nullptr);
            break;
        }
    }

    // Wait ? returning home would despawn and lose cargo already taken from home.
    base.min_max_seen = pred.understaffed ? 2 : 1;
    advance_action(ACTION_8_RECALCULATE);
}

void figure_cartpusher::determine_granaryman_destination() {
    int road_network_id = map_road_network_get(tile());
    building_granary *granary = home()->dcast_granary();
    building_food_mill *mill = home()->dcast_food_mill();

    if (!base.resource_id) {
        granary_getting_result dest = {0, tile2i::invalid};
        if (granary) {
            dest = granary->find_storage_for_getting();
        } else if (mill) {
            dest = mill->find_storage_for_getting();
        } else {
            poof();
            return;
        }

        set_destination(dest.building_id);
        if (has_destination()) {
            advance_action(ACTION_54_CARTPUSHER_GETTING_FOOD);
            if (!!game_features::gameplay_change_getting_granaries_go_offroad) {
                base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            }
        } else {
            poof();
        }
        return;
    }

    // Emptying / redistribution ? granary only (mill does not empty-out in v1).
    if (!granary) {
        advance_action(ACTION_56_CARTPUSHER_RETURNING_WITH_FOOD);
        return;
    }

    // delivering resource
    // priority 1: another granary
    tile2i dest_b;
    int granary_id = building_granary_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 0, 0, &dest_b);
    set_destination(granary_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
    }

    // priority 2: warehouse
    int warehouse_id = building_storage_yard_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 0, dest_b);
    set_destination(warehouse_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
    }

    // priority 3: granary even though resource is on stockpile
    int granary_second_id = building_granary_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 1, 0, &dest_b);
    set_destination(granary_second_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
    }
    // nowhere to go to: recalculate
    advance_action(ACTION_56_CARTPUSHER_RETURNING_WITH_FOOD);
}

void figure_cartpusher::determine_storageyard_cart_destination() {
    int road_network_id = map_road_network_get(tile());

    ////// getting resources!
    if (!base.resource_id) {
        tile2i dst;
        building_storage_yard *warhouse = home()->dcast_storage_yard();
        int building_id = warhouse
                            ? warhouse->for_getting((e_resource)base.collecting_item_id, &dst)
                            : 0;
        set_destination(building_id);
        if (has_destination()) {
            advance_action(ACTION_57_CARTPUSHER_GETTING_RESOURCE);
            base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else {
            advance_action(ACTION_53_CARTPUSHER_RETURNING_EMPTY);
        }
        return;
    }
    building* warehouse = home();

    ////// delivering resource!
    // priority 1: weapons to police stations (if destination already set)
    if (base.resource_id == RESOURCE_WEAPONS && has_destination()) {
        building* dest = destination();
        if (dest && dest->type == BUILDING_POLICE_STATION) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 2: weapons to barracks
    if (base.resource_id == RESOURCE_WEAPONS) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_RECRUITER, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 2: papyrus to scribal school / industry office
    if (base.resource_id == RESOURCE_PAPYRUS) {
        const e_building_type consumers[] = { BUILDING_SCRIBAL_SCHOOL, BUILDING_INDUSTRY_OFFICE };
        for (e_building_type consumer : consumers) {
            auto result = building_get_asker_for_resource(tile(), consumer, base.resource_id, road_network_id, warehouse->distance_from_entry);
            set_destination(result.building_id);
            if (has_destination()) {
                return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
            }
        }
    }

    // priority 3: timber to shipyard
    if (base.resource_id == RESOURCE_TIMBER) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_SHIPWRIGHT, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 4: beer to senet house
    if (base.resource_id == RESOURCE_BEER) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_SENET_HOUSE, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 4b: straw / game meat to zoo
    if (base.resource_id == RESOURCE_STRAW || base.resource_id == RESOURCE_GAMEMEAT) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_ZOO, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 5: raw materials to workshop
    {
        tile2i dest;
        int building_id = building_get_workshop_for_raw_material_with_room(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 6: food to granary
    {
        tile2i dest;
        int building_id = building_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 0, 0, &dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 7: food to getting granary
    {
        tile2i dest;
        int building_id = building_getting_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, &dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
        }
    }

    // priority 8: resource to other warehouse
    tile2i dest;
    int warehouse_id = building_storage_yard_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 0, dest);
    if (warehouse_id) {
        building *dest_building = building_get(warehouse_id);
        if (dest_building->main()->id == warehouse->id) {
            warehouse_id = 0;
        }
    }
    set_destination(warehouse_id);
    if (has_destination()) {
        return advance_action(ACTION_51_CARTPUSHER_DELIVERING_RESOURCE);
    }
    //    int empty_warehouse = building_storage_get(home()->storage_id)->empty_all; // deliver to another warehouse
    //    because this one is being emptied if (has_destination() && empty_warehouse) {
    //        if (homeID() == destinationID())
    //            poof();
    //        else
    //            advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    //        return;
    //    }

    //    // priority 6: raw material to well-stocked workshop
    //    set_destination(building_get_workshop_for_raw_material(tile_x, tile_y, resource_id,
    //    warehouse->distance_from_entry, road_network_id, &dst); if (destination_building_id) {
    //        remove_resource_from_warehouse();
    //        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    //    }

    // no destination: recalculate
    //    advance_action(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
}

void figure_cartpusher::figure_before_action() {
    if (has_destination()) {
        return;
    }

    building* b = home();
    if (!b->is_floodplain_farm()
        && (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id()) && !b->has_figure(1, id())))) {
        poof();
    }
}

void figure_cartpusher::figure_action() {
    OZZY_PROFILER_FUNCTION();

    base.use_cart = true;

    // Yield to cartpushers with a higher ID sharing the same tile to reduce visual overlap
    if (!!game_features::gameplay_change_cartpushers_yield_by_id) {
        int check_id = map_figure_id_get(tile());
        while (check_id > 0) {
            if (check_id != id()) {
                figure *other = figure_get(check_id);
                if (other->type == FIGURE_CART_PUSHER && check_id > id()) {
                    return;
                }
            }
            figure *other = figure_get(check_id);
            int next_id = other->next_figure;
            if (next_id == check_id || next_id == 0) {
                break;
            }
            check_id = next_id;
        }
    }

    building* b = home();
    int road_network_id = map_road_network_get(tile());
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_20_CARTPUSHER_INITIAL:
        calculate_destination(false);
        break;

    case ACTION_9_CARTPUSHER_DELIVERING_GOODS:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_12_CARTPUSHER_DELIVERING_UNLOADING_GOODS, ACTION_8_RECALCULATE);
        break;

    case ACTION_10_CARTPUSHER_DELIVERING_FOOD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_13_CARTPUSHER_DELIVERING_UNLOADING_FOODS, ACTION_8_RECALCULATE);
        break;

    case ACTION_11_CARTPUSHER_DELIVERING_GOLD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_14_CARTPUSHER_UNLOADING_GOLD, ACTION_8_RECALCULATE);
        break;

    case ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_24_CARTPUSHER_AT_WAREHOUSE, ACTION_8_RECALCULATE);
        break;

    case ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_25_CARTPUSHER_AT_GRANARY, ACTION_8_RECALCULATE);
        break;

    case ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_26_CARTPUSHER_AT_WORKSHOP, ACTION_8_RECALCULATE);
        break;

    case ACTION_12_CARTPUSHER_DELIVERING_UNLOADING_GOODS:
    case ACTION_13_CARTPUSHER_DELIVERING_UNLOADING_FOODS:
    case ACTION_14_CARTPUSHER_UNLOADING_GOLD:
    case ACTION_24_CARTPUSHER_AT_WAREHOUSE:
    case ACTION_25_CARTPUSHER_AT_GRANARY:
    case ACTION_26_CARTPUSHER_AT_WORKSHOP:
        do_deliver(false, ACTION_27_CARTPUSHER_RETURNING, ACTION_8_RECALCULATE);
        break;

    case ACTION_27_CARTPUSHER_RETURNING:
        // the CARTPUSHER figure will never be retrieving goods to carry back.
        // that's job for the WAREHOUSEMAN figure!
        // so there is no need for `cartpusher_do_deliver` action.
        if (b->is_floodplain_farm()) { // do not return to floodplain farms
            poof();
        } else if (do_returnhome(TERRAIN_USAGE_ROADS)) {
            // Arrived home (action_state becomes -1 ? dead next tick). Handoff lodge trail now ?
            // action_perform kills via set_state(DEAD) without calling before_poof/poof().
            if (b->params().flags.keeps_visitor_paths) {
                g_recorded_paths.handoff_to_building(base, b->main()->id);
            }
        }
        break;
    }
}

bool figure_cartpusher::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_FERRY_ROUTE);
}

void figure_cartpusher::update_animation() {
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(animkeys().death);
        return;
    }

    auto &d = runtime_data();
    const bool first_tick = d.movement_check_progress == 255;
    const bool moved = !first_tick && base.progress_on_tile != d.movement_check_progress;
    const bool on_water = map_terrain_is(tile(), TERRAIN_WATER);

    xstring animkey;
    if (!moved) {
        animkey = animkeys().idle;
    } else if (on_water) {
        animkey = animkeys().swim;
    } else {
        animkey = animkeys().walk;
    }

    image_set_animation(animkey);
    d.movement_check_progress = base.progress_on_tile;
}

