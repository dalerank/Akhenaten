#include "price_change.h"

#include "city/message.h"
#include "core/random.h"
#include "empire/trade_prices.h"
#include "game/game.h"
#include "scenario/scenario.h"

void scenario_price_change_init(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        random_generate_next();
        if (g_scenario_data.price_changes[i].year)
            g_scenario_data.price_changes[i].month = (random_byte() & 7) + 2;
    }
}

void scenario_price_change_process(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        if (!g_scenario_data.price_changes[i].year)
            continue;

        if (game.simtime.year != g_scenario_data.price_changes[i].year + g_scenario_data.start_year
            || game.simtime.month != g_scenario_data.price_changes[i].month) {
            continue;
        }
        int amount = g_scenario_data.price_changes[i].amount;
        int resource = g_scenario_data.price_changes[i].resource;
        if (g_scenario_data.price_changes[i].is_rise) {
            if (trade_price_change(resource, amount))
                city_message_post(true, MESSAGE_PRICE_INCREASED, amount, resource);

        } else {
            if (trade_price_change(resource, -amount))
                city_message_post(true, MESSAGE_PRICE_DECREASED, amount, resource);
        }
    }
}
