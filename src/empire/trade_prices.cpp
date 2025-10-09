#include "trade_prices.h"

#include "io/io_buffer.h"
#include "city/city.h"
#include "js/js_game.h"

stable_array<trade_price> ANK_VARIABLE(default_prices);

trade_price prices[RESOURCES_MAX];

void trade_prices_reset() {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        prices[i] = default_prices[i];
    }
}

bool trade_price_change(e_resource resource, int amount) {
    if (amount < 0 && prices[resource].sell <= 0) {
        // cannot lower the price to negative
        return false;
    }
    if (amount < 0 && prices[resource].sell <= -amount) {
        prices[resource].buy = 2;
        prices[resource].sell = 0;
    } else {
        prices[resource].buy += amount;
        prices[resource].sell += amount;
    }
    return true;
}

int trade_price_buy(e_resource resource) {
    return prices[resource].buy;
}

int trade_price_sell(e_resource resource, int bonus_inclusion) {
    switch (bonus_inclusion) {
    case PRICE_WITH_BONUS: return prices[resource].sell * (g_city.religion.ra_150_export_profits_months_left > 0 ? 1.5f : 1.0f);
    case PRICE_ONLY_BASE: return prices[resource].sell;
    case PRICE_ONLY_BONUS: return prices[resource].sell * (g_city.religion.ra_150_export_profits_months_left > 0 ? 0.5f : 0.0f);
    }

    return 999;
}

io_buffer* iob_trade_prices = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].buy);
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].sell);
    }
});