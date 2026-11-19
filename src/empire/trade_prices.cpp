#include "trade_prices.h"
#include "core/xvalue.h"

#include "city/city.h"
#include "js/js_register.h"

stable_array<trade_price> ANK_VARIABLE(default_prices);

void trade_prices_reset() {
    auto& prices = xvalue<trade_prices_t>::ref().prices;
    for (int i = 0; i < RESOURCES_MAX; i++) {
        prices[i] = default_prices[i];
    }
}

bool trade_price_change(e_resource resource, int amount) {
    auto& prices = xvalue<trade_prices_t>::ref().prices;
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
    auto& prices = xvalue<trade_prices_t>::ref().prices;
    return prices[resource].buy;
}

int trade_price_sell(e_resource resource, int bonus_inclusion) {
    auto& prices = xvalue<trade_prices_t>::ref().prices;
    switch (bonus_inclusion) {
    case PRICE_WITH_BONUS: return prices[resource].sell * (g_city.religion.ra_150_export_profits_months_left > 0 ? 1.5f : 1.0f);
    case PRICE_ONLY_BASE: return prices[resource].sell;
    case PRICE_ONLY_BONUS: return prices[resource].sell * (g_city.religion.ra_150_export_profits_months_left > 0 ? 0.5f : 0.0f);
    }

    return 999;
}
