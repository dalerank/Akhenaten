#include "empire/trader_handler.h"

#include "empire/empire.h"
#include "empire/empire_traders.h"
#include "empire/trade_prices.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "city/city.h"
#include "game/game_events.h"
#include "io/io_buffer.h"
#include "empire/empire_map.h"
#include "figure/figure.h"

int empire_trader_handle::record_bought_resource(e_resource resource) {
    auto& traders = g_empire_traders.traders;
    constexpr int amount = 100;
    traders[handle].bought_amount += amount;
    traders[handle].bought_resources[resource] += amount;
    traders[handle].bought_value += trade_price_sell(resource);

    return amount;
}
int empire_trader_handle::record_sold_resource(e_resource resource) { 
    auto& traders = g_empire_traders.traders;
    constexpr int amount = 100;
    traders[handle].sold_amount += amount;
    traders[handle].sold_resources[resource] += amount;
    traders[handle].sold_value += trade_price_buy(resource);

    return amount;
}

int empire_trader_handle::bought_resources(e_resource resource) { 
    auto& traders = g_empire_traders.traders;
    return traders[handle].bought_resources[resource];
}

int empire_trader_handle::sold_resources(e_resource resource) { 
    auto& traders = g_empire_traders.traders;
    return traders[handle].sold_resources[resource];
}

bool empire_trader_handle::has_traded() {
    auto& traders = g_empire_traders.traders;
    return traders[handle].bought_amount || traders[handle].sold_amount;
}

bool empire_trader_handle::has_traded_max() { 
    auto& traders = g_empire_traders.traders;
    return traders[handle].bought_amount >= 1200 || traders[handle].sold_amount >= 1200;
}

empire_trader_handle empire_create_trader() {
    auto& traders = g_empire_traders.traders;
    auto it = std::find_if(traders.begin() + 1, traders.end(), [] (auto& t) { return t.is_active == false; });

    if (it == traders.end()) {
        return {};
    }

    auto& trader = *it;
    memset(&trader, 0, sizeof(trader));
    trader.is_active = true;
    return empire_trader_handle{ (uint8_t)std::distance(traders.begin(), it) };
}

void empire_trader_handle::back_to_city() {
    auto &traders = g_empire_traders.traders;
    traders[handle].state = empire_trader::estate_returning_home;
}

e_resource empire_trader_handle::get_buy_resource(building* b, empire_city_handle city, int amount) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return RESOURCE_NONE;
    }

    building_storage_room* space = warehouse->room();
    while (space) {
        e_resource resource = space->resource();
        if (space->stored_amount(resource) >= amount && g_empire.can_export_resource_to_city(city.handle, resource)) {
            // update stocks
            events::emit(event_stats_remove_resource{ resource, amount });
            space->take_resource(amount);

            // update finances
            uint32_t price = trade_price_sell(resource);
            events::emit(event_finance_request{ efinance_request_export, price });

            // update graphics
            space->set_image(resource);
            return resource;
        }
        space = space->next_room();
    }

    return RESOURCE_NONE;
}

e_resource empire_trader_handle::get_sell_resource(building* b, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return RESOURCE_NONE;
    }

    e_resource resource_to_import = city_trade_current_caravan_import_resource();
    int imp = RESOURCES_MIN;
    while (imp < RESOURCES_MAX && !g_empire.can_import_resource_from_city(city.handle, resource_to_import)) {
        imp++;
        resource_to_import = city_trade_next_caravan_import_resource();
    }

    if (imp >= RESOURCES_MAX) {
        return RESOURCE_NONE;
    }

    // add to existing bay with room
    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->stored_amount(resource_to_import) > 0) {
            space->add_import(resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
        space = space->next_room();
    }

    // add to empty bay
    space = warehouse->room();
    while (space) {
        if (!space->base.stored_first().type) {
            space->add_import(resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
        space = space->next_room();
    }
    // find another importable resource that can be added to this warehouse
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; r++) {
        resource_to_import = city_trade_next_caravan_backup_import_resource();
        if (g_empire.can_import_resource_from_city(city.handle, resource_to_import)) {
            space = warehouse->room();
            while (space) {
                if (space->stored_amount(resource_to_import) < 400) {
                    space->add_import(resource_to_import);
                    return resource_to_import;
                }
                space = space->next_room();
            }
        }
    }
    return RESOURCE_NONE;
}

io_buffer* iob_empire_traders = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_empire_traders;
    assert(data.traders.size() == 100);
    for (int i = 0; i < data.traders.size(); i++) {
        empire_trader& t = data.traders[i];
        t.id = i;
        iob->bind_u16(t.bought_amount);
        iob->bind_u8(t.trade_route_id);
        iob->bind_u8(t.current_route_point);
        iob->bind_u16(t.sold_amount);
        iob->bind_bool(t.is_active);
        iob->bind_bool(t.is_ship);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            t.bought_resources[r] *= 0.01;
            t.sold_resources[r] *= 0.01;
        }

        iob->bind_u8(t.movement_delay_max);
        for (int r = 1; r < RESOURCES_MAX; r++)
            iob->bind_u8((uint8_t&)t.bought_resources[r]);

        iob->bind____skip(1);
        for (int r = 1; r < RESOURCES_MAX; r++)
            iob->bind_u8((uint8_t &)t.sold_resources[r]);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            t.bought_resources[r] *= 100;
            t.sold_resources[r] *= 100;
        }

        iob->bind_u16(t.bought_value);
        iob->bind_u8(t.destination_city_id);
        iob->bind_u8((uint8_t&)t.state);
        iob->bind_u16(t.sold_value);
        iob->bind_u8(t.movement_delay);
        iob->bind____skip(1);
    }

    iob->bind____skip(4);
});

