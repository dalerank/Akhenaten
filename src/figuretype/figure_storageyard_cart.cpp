#include "figuretype/figure_storageyard_cart.h"

#include "core/profiler.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_granary.h"
#include "grid/road_network.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game.h"
#include "js/js_game.h"
#include "game/game_config.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_storageyard_cart);

void figure_storageyard_cart::figure_before_action() {
    if (has_destination()) {
        return;
    }

    building* b = home();
    if (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id()) && !b->has_figure(1, id()))) {
        poof();
    }
}

std::pair<e_resource, int> acquire_resource_for_getting_deliveryman(building* srcb, building* dstb) {
    building_storage *dst = dstb->dcast_storage();
    building_storage *src = srcb->dcast_storage();

    const storage_t* s_src = src->storage();
    const storage_t* s_dst = dst->storage();

    int max_amount = 0;
    e_resource max_resource = RESOURCE_NONE;
    for (const auto &r : resource_list::foods) {
        if (dst->is_getting(r.type) && !src->is_gettable(r.type)) {
            if (src->amount(r.type) > max_amount) {
                max_amount = src->amount(r.type);
                max_resource = r.type;
            }
        }
    }

    if (!!game_features::gameplay_change_granaries_get_double) {
        max_amount = std::min(max_amount, 400);
    } else {
        max_amount = std::min(max_amount, 200);
    }

    max_amount = std::min<int>(max_amount, dst->freespace());
    return {max_resource, max_amount};
}

void figure_storageyard_cart::do_retrieve(int action_done) {
    base.wait_ticks++;
    base.animctx.frame = 0;
    if (base.wait_ticks < 4) {
        return;
    }

    building* dest = destination();
    const bool is_storage = building_type_any_of(dest->type, { BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_STORAGE_ROOM });
    if (!is_storage) {
        advance_action(action_done);
    }

    building_storage *home_storage = home()->dcast_storage();
    building_storage *dest_storage = dest->dcast_storage();

    if (base.collecting_item_id == RESOURCE_NONE) {
        auto loads = acquire_resource_for_getting_deliveryman(destination(), home());
        base.collecting_item_id = loads.first;
        base.collecting_item_max = loads.second;
    } 

    int home_accepting_quantity = home_storage->accepting_amount((e_resource)base.collecting_item_id);
    int carry_amount_goal_max = std::min<int>(base.collecting_item_max, home_accepting_quantity);

    // grab goods, quantity & max load changed by above settings;
    int previous_amount = base.get_carrying_amount();
    if (base.get_carrying_amount() < carry_amount_goal_max) {
        int left_amount = dest_storage->remove_resource((e_resource)base.collecting_item_id, UNITS_PER_LOAD);
        int dest_stored_amount = dest_storage->amount((e_resource)base.collecting_item_id);
        append_resource((e_resource)base.collecting_item_id, (UNITS_PER_LOAD - left_amount));
        base.wait_ticks = 0;
    }

    // if load is finished, go back home
    if (previous_amount == base.get_carrying_amount()) {
        advance_action(action_done);
        base.wait_ticks = 4;
    }
}

void figure_storageyard_cart::figure_action() {
    OZZY_PROFILER_FUNCTION();
    int road_network_id = map_road_network_get(tile());

    base.use_cart = true;
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_50_WAREHOUSECART_CREATED:
        calculate_destination(true);
        break;

    case ACTION_51_WAREHOUSECART_DELIVERING_RESOURCE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_52_WAREHOUSECART_AT_DELIVERY_BUILDING, ACTION_8_RECALCULATE);
        break;

    case ACTION_52_WAREHOUSECART_AT_DELIVERY_BUILDING:
        do_deliver(true, ACTION_53_WAREHOUSECART_RETURNING_EMPTY, ACTION_53_WAREHOUSECART_RETURNING_EMPTY);
        break;

    case ACTION_53_WAREHOUSECART_RETURNING_EMPTY:
        do_returnhome(TERRAIN_USAGE_ROADS);
        break;

    case ACTION_54_WAREHOUSECART_GETTING_FOOD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_55_WAREHOUSECART_AT_GRANARY_GETTING, ACTION_8_RECALCULATE);
        break;

    case ACTION_55_WAREHOUSECART_AT_GRANARY_GETTING:
        do_retrieve(ACTION_56_WAREHOUSECART_RETURNING_WITH_FOOD);
        break;

    case ACTION_56_WAREHOUSECART_RETURNING_WITH_FOOD:
    case ACTION_59_WAREHOUSECART_RETURNING_WITH_RESOURCE:
        if (do_returnhome(TERRAIN_USAGE_ROADS)) {
            set_destination(home());
            advance_action(ACTION_60_WAREHOUSECART_UNLOADING_AT_HOME);
        }
        break;

    case ACTION_60_WAREHOUSECART_UNLOADING_AT_HOME:
        do_deliver(true, /*action_done*/-1, ACTION_8_RECALCULATE);
        break;

    case ACTION_57_WAREHOUSECART_GETTING_RESOURCE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_58_WAREHOUSECART_AT_WAREHOUSE_GETTING_GOODS, ACTION_8_RECALCULATE);
        break;

    case ACTION_58_WAREHOUSECART_AT_WAREHOUSE_GETTING_GOODS: // used exclusively for getting resources
        do_retrieve(ACTION_59_WAREHOUSECART_RETURNING_WITH_RESOURCE);
        break;
    }
}