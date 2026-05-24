#include "distribution.h"

#include "graphics/elements/image_button.h"
#include "graphics/elements/scrollbar.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "building/building_dock.h"
#include "building/building_storage_yard.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "window/window_building_info.h"
#include "game/game.h"

static void go_to_orders(int param1, int param2);
static void granary_orders(int param1, int param2);
static void warehouse_orders(int index, int param2);
static void market_orders(int index, int param2);
static void storage_toggle_permissions(int index, int param2);



std::pair<bstring64, e_font> window_dock_get_order_instruction(int instr_kind, e_resource resource, int dock_order) {
    switch (dock_order) {
    case DOCK_ORDER_STATE_TRADE:
        return { "Trade", FONT_NORMAL_WHITE_ON_DARK };

    case DOCK_ORDER_STATE_DONT_TRADE:
        return { "Don't trade", FONT_NORMAL_BLACK_ON_DARK };
    }

    assert(false);
    return { "", FONT_INVALID };
}

std::pair<bstring64, e_font> window_building_get_order_instruction(int instr_kind, const storage_t &storage, e_resource resource) {
    switch (storage.resource_state[resource]) {
    case STORAGE_STATE_ACCEPT: {
        int max_accept = storage.resource_max_accept[resource];
        bstring64 text;
        text.printf("%d", max_accept);

        if (max_accept == 3200) { text = ui::str(99, 28); }
        else if (max_accept == 2400) { text = ui::str(99, 27); }
        else if (max_accept == 1600) { text = ui::str(99, 26); }
        else if (max_accept == 800) { text = ui::str(99, 25); }

        pcstr adv_text = "";
        if (max_accept == 2400 || max_accept == 1600 || max_accept == 800)
            adv_text = ui::str(99, 29);

        bstring64 full_text;
        full_text.printf("%s %s %s", ui::str(99, 18), text.c_str(), adv_text);
        return { full_text, FONT_NORMAL_WHITE_ON_DARK };
    }

    case STORAGE_STATE_REFUSE:
        return { ui::str(99, 8), FONT_NORMAL_BLACK_ON_DARK };

    case STORAGE_STATE_GET: {
        int max_get = storage.resource_max_get[resource];
        bstring64 text;
        text.printf("%d", max_get);
        if (max_get == 3200) { text = ui::str(99, 31); }
        else if (max_get == 2400) { text = ui::str(99, 27); }
        else if (max_get == 1600) { text = ui::str(99, 26); }
        else if (max_get == 800) { text = ui::str(99, 25); }

        pcstr adv_text = "";
        if (max_get == 2400 || max_get == 1600 || max_get == 800)
            adv_text = ui::str(99, 29);

        bstring64 full_text;
        full_text.printf("%s %s %s", ui::str(99, 19), text.c_str(), adv_text);
        return { full_text, FONT_NORMAL_YELLOW };
    }
    case STORAGE_STATE_EMPTY:
        return { ui::str(99, 21), FONT_NORMAL_BLACK_ON_DARK };
    }

    return { "unknown_storage", FONT_NORMAL_BLACK_ON_DARK };
}

static void order_quantity_increase_decrease(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.bid);
    int resource;

    building_bazaar *bazaar = b->dcast_bazaar();
    if (bazaar) {
        return;
    }

    building_dock *dock = b->dcast_dock();
    if (dock) {
        return;
    }

    if (b->type == BUILDING_STORAGE_YARD) {
        resource = g_city.resource.available().at(index - 1).type;
    } else {
        resource = g_city.resource.available_foods().at(index - 1).type;
    }

    building_storage_increase_decrease_resource_state(b->storage_id, resource, param2);
}

static void market_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    building_bazaar* bazaar = building_get(data.bid)->dcast_bazaar();
    if (index == 0) {
        bazaar->unaccept_all_goods();
    }
}

static void granary_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    int storage_id = building_get(data.bid)->storage_id;
    if (index == 0)
        building_storage_toggle_empty_all(storage_id);
    else if (index == 1)
        building_storage_accept_none(storage_id);

    //    window_invalidate();
}
static void warehouse_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    if (index == 0) {
        int storage_id = building_get(data.bid)->storage_id;
        building_storage_toggle_empty_all(storage_id);
    } else if (index == 1) {
        int storage_id = building_get(data.bid)->storage_id;
        building_storage_accept_none(storage_id);
    } else if (index == 2) {
        int storage_id = building_get(data.bid)->storage_id;
        building_storage_accept_none(storage_id);
    }
    //    window_invalidate();
}
