#include <game/io/io_buffer.h>
#include "trade_prices.h"
#include "core/game_environment.h"

struct trade_price {
    int32_t buy;
    int32_t sell;
};

static const struct trade_price DEFAULT_PRICES[RESOURCES_MAX] = {
        {0,   0},
        {28,  22},
        {38,  30},
        {38,  30}, // wheat, vegetables, fruit
        {42,  34},
        {44,  36},
        {44,  36},
        {215, 160}, // olives, vines, meat, wine
        {180, 140},
        {60,  40},
        {50,  35},
        {40,  30}, // oil, iron, timber, clay
        {200, 140},
        {250, 180},
        {200, 150},
        {180, 140} // marble, weapons, furniture, pottery
};

static struct trade_price prices[RESOURCES_MAX];

void trade_prices_reset(void) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        prices[i] = DEFAULT_PRICES[i];
    }
}
int trade_price_change(int resource, int amount) {
    if (amount < 0 && prices[resource].sell <= 0) {
        // cannot lower the price to negative
        return 0;
    }
    if (amount < 0 && prices[resource].sell <= -amount) {
        prices[resource].buy = 2;
        prices[resource].sell = 0;
    } else {
        prices[resource].buy += amount;
        prices[resource].sell += amount;
    }
    return 1;
}

int trade_price_buy(int resource) {
    return prices[resource].buy;
}
int trade_price_sell(int resource) {
    return prices[resource].sell;
}

io_buffer *iob_trade_prices = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].buy);
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].sell);
    }
});