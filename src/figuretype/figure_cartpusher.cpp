#include "figure_cartpusher.h"

#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "city/city_industry.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/monuments.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "game/game.h"
#include "graphics/image.h"
#include "grid/road_network.h"
#include "grid/terrain.h"
#include "window/building/figures.h"
#include "graphics/elements/ui.h"
#include "grid/routing/routing_terrain.h"
#include "game/game_config.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_cartpusher);

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

void figure_cartpusher::do_deliver(bool warehouseman, int action_done, int action_fail) {
    base.animctx.frame = 0;
    base.wait_ticks++;

    if ((!warehouseman && base.wait_ticks >= 10) || (warehouseman && base.wait_ticks >= 4)) {
        base.wait_ticks = 0;

        int carrying = base.get_carrying_amount();
        e_resource resource = base.get_resource();

        // carrying nothing? done!
        if (resource == RESOURCE_NONE || carrying <= 0) {
            base.progress_inside_speed = 0;
            return advance_action(action_done);

        } else {
            building* dest = destination();         

            int amount_single_turn = std::min(carrying, UNITS_PER_LOAD);
            int times = carrying / amount_single_turn;

            switch (dest->type) {
            case BUILDING_GRANARY:
            case BUILDING_STORAGE_YARD:
            case BUILDING_STORAGE_ROOM: {
                    building_storage *storage = dest->dcast_storage();
                    int accepting = storage ? storage->accepting_amount(resource) : 0;
                    int total_depositable = std::min<int>(carrying, accepting);
                    
                    if (total_depositable <= 0) {
                        advance_action(ACTION_8_RECALCULATE);
                        return;
                    }

                    int amount = storage->add_resource(base.resource_id, amount_single_turn, /*force*/false);
                    if (amount != -1) {
                        dump_resource(amount_single_turn);
                    } else {
                        advance_action(action_fail);
                        return;
                    }
                }
                break;

            case BUILDING_RECRUITER:
            case BUILDING_SHIPWRIGHT:
            case BUILDING_SCRIBAL_SCHOOL: 
            case BUILDING_SENET_HOUSE: {
                    building_impl *b = dest->dcast();
                    bool ok = b->add_resource(resource, amount_single_turn);
                    if (!ok) {
                        advance_action(action_fail);
                        return;
                    }
                    dump_resource(amount_single_turn);
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
                    events::emit(finance_request_t{ request_type, (uint32_t)amount_single_turn });
                    dump_resource(amount_single_turn);
                }
                break;

            default:                              // workshop
                if (dest->stored_amount(resource) < 200) {
                    building_workshop_add_raw_material(dest, amount_single_turn, resource);
                    dump_resource(amount_single_turn);
                } else {
                    return advance_action(action_fail);
                }
                break;
            }
        }

        // am I done?
        if (resource == RESOURCE_NONE || carrying <= 0) {
            return advance_action(action_done);
        }
    }
}

void figure_cartpusher::calculate_destination(bool warehouseman) {
    set_destination(nullptr);
    base.animctx.frame = 0;
    base.wait_ticks++;

    if (!warehouseman) {
        if (base.wait_ticks > current_params().wait_on_calculate_destination) {
            base.wait_ticks = 0;
            determine_deliveryman_destination();
        }
    } else {
        building* b = home();
        if (base.wait_ticks > 2) {
            base.wait_ticks = 0;
            if (home()->type == BUILDING_GRANARY) {
                determine_granaryman_destination();
            } else {
                determine_storageyard_cart_destination();
            }
        }
    }
}

void figure_cartpusher::determine_deliveryman_destination() {
    tile2i dst;
    int road_network_id = map_road_network_get(tile());
    building* warehouse = home();
    int understaffed_storages = 0;

    base.destination_tile = tile2i::invalid;

    // before we start... check that resource is not empty.
    if (base.resource_id == RESOURCE_NONE || base.get_carrying_amount() == 0) {
        return advance_action(FIGURE_ACTION_15_RETURNING2);
    }

    // first: gold deliverers
    if (base.resource_id == RESOURCE_GOLD) {
        int senate_id = g_city.buildings.get_palace_id();
        building* b = building_get(senate_id);
        if (senate_id && b->state == BUILDING_STATE_VALID && b->num_workers >= 5) {
            set_destination(senate_id);
            return advance_action(ACTION_11_CARTPUSHER_DELIVERING_GOLD);
        }
    }

    // priority 1: warehouse if resource is on stockpile
    building_id stockpile_id = building_storage_yard_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, dst);
    set_destination(stockpile_id);
    if (!g_city.resource.is_stockpiled(base.resource_id)) {
        set_destination(nullptr);
    }

    if (has_destination()) {
        return advance_action(ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
    }

    // priority 2: accepting granary for food
    int granary_food_id = building_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 0, &understaffed_storages, &dst);
    set_destination(granary_food_id);
    if (!!game_features::gameplay_change_farms_deliver_close) {
        int dist = 0;
        building* src_building = home();
        building* dst_building = destination();
        if (src_building->dcast_farm() || src_building->dcast_fishing_wharf()) {
            dist = calc_distance_with_penalty(src_building->tile, dst_building->tile, src_building->distance_from_entry,dst_building->distance_from_entry);
        }

        if (dist >= 64) {
            set_destination(nullptr);
        }
    }

    if (has_destination()) {
        return advance_action(ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }

    // priority 3: workshop for raw material
    int workshop_id = building_get_workshop_for_raw_material_with_room(tile(), (e_resource)base.resource_id, warehouse->distance_from_entry, road_network_id, dst);
    set_destination(workshop_id);
    if (has_destination()) {
        return advance_action(ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP);
    }

    // priority 4: warehouse
    int warehouse_id = building_storage_yard_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, dst);
    set_destination(warehouse_id);
    if (has_destination()) {
        return advance_action(ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
    }

    // priority 5: granary forced when on stockpile
    int granary_id = building_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 1, &understaffed_storages, &dst);
    set_destination(granary_id);
    if (!!game_features::gameplay_change_farms_deliver_close) {
        int dist = 0;
        building* src_building = home();
        building* dst_building = destination();
        if (src_building->dcast_farm() || src_building->dcast_fishing_wharf()) {
            dist = calc_distance_with_penalty(src_building->tile, dst_building->tile, src_building->distance_from_entry, dst_building->distance_from_entry);
        }

        if (dist >= 64) {
            set_destination(nullptr);
        }
    }

    if (has_destination()) {
        return advance_action(ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }

    // no one will accept
    base.min_max_seen = understaffed_storages ? 2 : 1;
    advance_action(ACTION_8_RECALCULATE);
}

void figure_cartpusher::determine_granaryman_destination() {
    int road_network_id = map_road_network_get(tile());
    building_granary* granary = home()->dcast_granary();

    if (!base.resource_id) {
        // getting granaryman
        granary_getting_result dest = granary->find_storage_for_getting();
        set_destination(dest.building_id);
        if (has_destination()) {
            advance_action(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD);
            if (!!game_features::gameplay_change_getting_granaries_go_offroad) {
                base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            }
        } else {
            poof();
        }
        return;
    }

    // delivering resource
    // priority 1: another granary
    tile2i dest_b;
    int granary_id = building_granary_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 0, 0, &dest_b);
    set_destination(granary_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }

    // priority 2: warehouse
    int warehouse_id = building_storage_yard_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 0, dest_b);
    set_destination(warehouse_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }

    // priority 3: granary even though resource is on stockpile
    int granary_second_id = building_granary_for_storing(tile(), base.resource_id, granary->distance_from_entry(), road_network_id, 1, 0, &dest_b);
    set_destination(granary_second_id);
    if (has_destination()) {
        granary->remove_resource(base.resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // nowhere to go to: recalculate
    advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
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
            advance_action(FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE);
            base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else {
            advance_action(FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY);
        }
        return;
    }
    building* warehouse = home();

    ////// delivering resource!
    // priority 1: weapons to barracks
    if (base.resource_id == RESOURCE_WEAPONS) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_RECRUITER, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 2: paryrus to scribal school
    if (base.resource_id == RESOURCE_PAPYRUS) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_SCRIBAL_SCHOOL, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 3: timber to shipyard
    if (base.resource_id == RESOURCE_TIMBER) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_SHIPWRIGHT, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 4: beer to senet house
    if (base.resource_id == RESOURCE_BEER) {
        auto result = building_get_asker_for_resource(tile(), BUILDING_SENET_HOUSE, base.resource_id, road_network_id, warehouse->distance_from_entry);
        set_destination(result.building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 5: raw materials to workshop
    {
        tile2i dest;
        int building_id = building_get_workshop_for_raw_material_with_room(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 6: food to granary
    {
        tile2i dest;
        int building_id = building_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 0, 0, &dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 7: food to getting granary
    {
        tile2i dest;
        int building_id = building_getting_granary_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, &dest);
        set_destination(building_id);
        if (has_destination()) {
            return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
    }

    // priority 8: resource to other warehouse
    tile2i dest;
    int warehouse_id = building_storage_yard_for_storing(tile(), base.resource_id, warehouse->distance_from_entry, road_network_id, 0, dest);
    set_destination(warehouse_id);
    if (has_destination()) {
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
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
    if (!building_is_floodplain_farm(*b)
        && (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id()) && !b->has_figure(1, id())))) {
        poof();
    }
}

void figure_cartpusher::before_poof() {
}

void figure_cartpusher::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Cartpusher");
    building* b = home();
    int road_network_id = map_road_network_get(tile());

    base.use_cart = true;
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_20_CARTPUSHER_INITIAL:
        calculate_destination(false);
        break;

    case ACTION_9_CARTPUSHER_DELIVERING_GOODS:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_12_DELIVERING_UNLOADING_GOODS, ACTION_8_RECALCULATE);
        break;

    case ACTION_10_CARTPUSHER_DELIVERING_FOOD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_13_DELIVERING_UNLOADING_FOODS, ACTION_8_RECALCULATE);
        break;

    case ACTION_11_CARTPUSHER_DELIVERING_GOLD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_14_UNLOADING_GOLD, ACTION_8_RECALCULATE);
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

    case 12: // storage yard
    case 13: // granary
    case 14: // palace
    case ACTION_24_CARTPUSHER_AT_WAREHOUSE:
    case ACTION_25_CARTPUSHER_AT_GRANARY:
    case ACTION_26_CARTPUSHER_AT_WORKSHOP:
        do_deliver(false, FIGURE_ACTION_15_RETURNING2, ACTION_8_RECALCULATE);
        break;

    case FIGURE_ACTION_15_RETURNING2:
    case ACTION_27_CARTPUSHER_RETURNING:
        // the CARTPUSHER figure will never be retrieving goods to carry back.
        // that's job for the WAREHOUSEMAN figure!
        // so there is no need for `cartpusher_do_deliver` action.
        if (building_is_floodplain_farm(*b)) { // do not return to floodplain farms
            poof();
        } else {
            do_returnhome(TERRAIN_USAGE_ROADS);
        }
        break;
    }
}

figure_sound_t figure_cartpusher::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

bool figure_cartpusher::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_FERRY_ROUTE);
}

sound_key figure_cartpusher::phrase_key() const {
    if (action_state(ACTION_20_CARTPUSHER_INITIAL, ACTION_24_CARTPUSHER_AT_WAREHOUSE)) {
        return "i_have_no_destination";
    }

    if (action_state(ACTION_27_CARTPUSHER_RETURNING, FIGURE_ACTION_15_RETURNING2)) {
        return "back_to_home";
    }

    if (action_state(ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE,
                     ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY,
                     ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP,
                     ACTION_11_CARTPUSHER_DELIVERING_GOLD)) {
        return "delivering_items";
    }

    return {};
}
