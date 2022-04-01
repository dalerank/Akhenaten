#include "price_change.h"

#include "city/message.h"
#include "core/random.h"
#include "empire/trade_prices.h"
#include "game/time.h"
#include "scenario/data.h"

void scenario_price_change_init(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++) {
        random_generate_next();
        if (scenario_data.price_changes[i].year)
            scenario_data.price_changes[i].month = (random_byte() & 7) + 2;

    }
}

void scenario_price_change_process(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++) {
        if (!scenario_data.price_changes[i].year)
            continue;

        if (game_time_year() != scenario_data.price_changes[i].year + scenario_data.start_year ||
            game_time_month() != scenario_data.price_changes[i].month) {
            continue;
        }
        int amount = scenario_data.price_changes[i].amount;
        int resource = scenario_data.price_changes[i].resource;
        if (scenario_data.price_changes[i].is_rise) {
            if (trade_price_change(resource, amount))
                city_message_post(true, MESSAGE_PRICE_INCREASED, amount, resource);

        } else {
            if (trade_price_change(resource, -amount))
                city_message_post(true, MESSAGE_PRICE_DECREASED, amount, resource);

        }
    }
}

