#include "figure/trader.h"

#include "core/game_environment.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "city/city.h"
#include "io/io_buffer.h"
#include "empire/empire_map.h"
#include "figure/figure.h"

#include "city/trade.h"

#define MAX_TRADERS 100

struct trader {
    int32_t bought_amount;
    int32_t bought_value;
    uint16_t bought_resources[RESOURCES_MAX];

    int32_t sold_amount;
    int32_t sold_value;
    uint16_t sold_resources[RESOURCES_MAX];
};

struct figure_trader_data_t {
    struct trader traders[MAX_TRADERS];
    int next_index;
};

figure_trader_data_t g_figure_trader_data;

void traders_clear(void) {
    auto &data = g_figure_trader_data;
    memset(&data, 0, sizeof(data));
}

int trader_create(void) {
    auto &data = g_figure_trader_data;
    int trader_id = data.next_index++;
    if (data.next_index >= MAX_TRADERS) {
        data.next_index = 0;
    }

    memset(&data.traders[trader_id], 0, sizeof(struct trader));
    return trader_id;
}

int trader_record_bought_resource(int trader_id, e_resource resource) {
    constexpr int amount = 100;
    auto &data = g_figure_trader_data;
    data.traders[trader_id].bought_amount += amount;
    data.traders[trader_id].bought_resources[resource] += amount;
    data.traders[trader_id].bought_value += trade_price_sell(resource);

    return amount;
}

int trader_record_sold_resource(int trader_id, e_resource resource) {
    constexpr int amount = 100;
    auto &data = g_figure_trader_data;
    data.traders[trader_id].sold_amount += amount;
    data.traders[trader_id].sold_resources[resource] += amount;
    data.traders[trader_id].sold_value += trade_price_buy(resource);

    return amount;
}

int trader_bought_resources(int trader_id, e_resource resource) {
    auto &data = g_figure_trader_data;
    return data.traders[trader_id].bought_resources[resource];
}

int trader_sold_resources(int trader_id, e_resource resource) {
    auto &data = g_figure_trader_data;
    return data.traders[trader_id].sold_resources[resource];
}

int trader_has_traded(int trader_id) {
    auto &data = g_figure_trader_data;
    return data.traders[trader_id].bought_amount || data.traders[trader_id].sold_amount;
}

int trader_has_traded_max(int trader_id) {
    auto &data = g_figure_trader_data;
    return data.traders[trader_id].bought_amount >= 1200 || data.traders[trader_id].sold_amount >= 1200;
}

e_resource trader_get_buy_resource(building* b, int city_id, int amount) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return RESOURCE_NONE;
    }

    building_storage_room* space = warehouse->room();
    while (space) {
        e_resource resource = space->resource();
        if (space->base.stored_amount_first >= amount && g_empire.can_export_resource_to_city(city_id, resource)) {
            // update stocks
            g_city.resource.remove_from_storageyard_stats(resource, amount);
            space->take_resource(amount);

            // update finances
            city_finance_process_export(trade_price_sell(resource));

            // update graphics
            space->set_image(resource);
            return resource;
        }
        space = space->next_room();
    }
    return RESOURCE_NONE;
}

e_resource trader_get_sell_resource(building* b, int city_id) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return RESOURCE_NONE;
    }

    e_resource resource_to_import = city_trade_current_caravan_import_resource();
    int imp = RESOURCE_MIN;
    while (imp < RESOURCES_MAX && !g_empire.can_import_resource_from_city(city_id, resource_to_import)) {
        imp++;
        resource_to_import = city_trade_next_caravan_import_resource();
    }

    if (imp >= RESOURCES_MAX) {
        return RESOURCE_NONE;
    }

    // add to existing bay with room
    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->base.stored_amount_first > 0 && space->base.stored_amount_first < 400
            && space->resource() == resource_to_import) {
            space->add_import(resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
        space = space->next_room();
    }
    // add to empty bay
    space = warehouse->room();
    while (space) {
        if (!space->base.stored_amount_first) {
            space->add_import(resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
        space = space->next_room();
    }
    // find another importable resource that can be added to this warehouse
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        resource_to_import = city_trade_next_caravan_backup_import_resource();
        if (g_empire.can_import_resource_from_city(city_id, resource_to_import)) {
            space = warehouse->room();
            while (space) {
                if (space->base.stored_amount_first < 400 && space->resource() == resource_to_import) {
                    space->add_import(resource_to_import);
                    return resource_to_import;
                }
                space = space->next_room();
            }
        }
    }
    return RESOURCE_NONE;
}

io_buffer* iob_figure_traders = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_figure_trader_data;
    for (int i = 0; i < MAX_TRADERS; i++) {
        struct trader* t = &data.traders[i];
        iob->bind(BIND_SIGNATURE_INT32, &t->bought_amount);
        iob->bind(BIND_SIGNATURE_INT32, &t->sold_amount);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            t->bought_resources[r] *= 0.01;
            t->sold_resources[r] *= 0.01;
        }

        for (int r = 0; r < RESOURCES_MAX; r++)
            iob->bind(BIND_SIGNATURE_UINT8, &t->bought_resources[r]);
        for (int r = 0; r < RESOURCES_MAX; r++)
            iob->bind(BIND_SIGNATURE_UINT8, &t->sold_resources[r]);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            t->bought_resources[r] *= 100;
            t->sold_resources[r] *= 100;
        }
        iob->bind(BIND_SIGNATURE_INT32, &t->bought_value);
        iob->bind(BIND_SIGNATURE_INT32, &t->sold_value);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.next_index);
});