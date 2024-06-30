#include "figuretype/figure_storageyard_cart.h"

#include "core/profiler.h"
#include "grid/road_network.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game.h"
#include "js/js_game.h"

figures::model_t<figure_storageyard_cart> storageyard_cart_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_storageyard_cart);
void config_load_figure_storageyard_cart() {
    storageyard_cart_m.load();
}

void figure_storageyard_cart::figure_before_action() {
    if (has_destination()) {
        return;
    }

    building* b = home();
    if (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id()) && !b->has_figure(1, id()))) {
        poof();
    }
}

void figure_storageyard_cart::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Warehouse Man");
    int road_network_id = map_road_network_get(tile());
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_50_WAREHOUSEMAN_CREATED:
        calculate_destination(true);
        break;

    case ACTION_9_DELIVERING_GOODS:
    case FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING, ACTION_8_RECALCULATE);
        break;

    case ACTION_12_DELIVERING_UNLOADING_GOODS:
    case FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING:
        do_deliver(true, ACTION_11_RETURNING_EMPTY);
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
        do_returnhome(TERRAIN_USAGE_ROADS);
        break;

    case FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY_GETTING, ACTION_8_RECALCULATE);
        break;

    case FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY_GETTING:
        do_retrieve(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
        break;

    case ACTION_14_RETURNING_WITH_FOOD:
    case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
    case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
        if (do_returnhome(TERRAIN_USAGE_ROADS)) {
            set_destination(home());
            do_deliver(true, 0);
        }
        break;

    case ACTION_15_GETTING_GOODS:
    case FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE_GETTING_GOODS,ACTION_8_RECALCULATE);
        break;

    case FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE_GETTING_GOODS: // used exclusively for getting resources
        do_retrieve(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
        break;
    }
}

void figure_storageyard_cart::figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i *coord_out) {
    base.draw_figure_with_cart(ctx, base.cached_pos, highlight, coord_out);
}