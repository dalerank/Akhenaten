#include "figure/trader.h"

#include "empire/trade_prices.h"
#include "core/game_environment.h"

#include <string.h>
#include "io/io_buffer.h"

#define MAX_TRADERS 100

struct trader {
    int32_t bought_amount;
    int32_t bought_value;
    uint16_t bought_resources[RESOURCES_MAX];

    int32_t sold_amount;
    int32_t sold_value;
    uint16_t sold_resources[RESOURCES_MAX];
};

static struct {
    struct trader traders[MAX_TRADERS];
    int next_index;
} data;

void traders_clear(void) {
    memset(&data, 0, sizeof(data));
}

int trader_create(void) {
    int trader_id = data.next_index++;
    if (data.next_index >= MAX_TRADERS)
        data.next_index = 0;

    memset(&data.traders[trader_id], 0, sizeof(struct trader));
    return trader_id;
}

void trader_record_bought_resource(int trader_id, int resource) {
    data.traders[trader_id].bought_amount += 100;
    data.traders[trader_id].bought_resources[resource] += 100;
    data.traders[trader_id].bought_value += trade_price_sell(resource);
}

void trader_record_sold_resource(int trader_id, int resource) {
    data.traders[trader_id].sold_amount += 100;
    data.traders[trader_id].sold_resources[resource] += 100;
    data.traders[trader_id].sold_value += trade_price_buy(resource);
}

int trader_bought_resources(int trader_id, int resource) {
    return data.traders[trader_id].bought_resources[resource];
}

int trader_sold_resources(int trader_id, int resource) {
    return data.traders[trader_id].sold_resources[resource];
}

int trader_has_traded(int trader_id) {
    return data.traders[trader_id].bought_amount || data.traders[trader_id].sold_amount;
}

int trader_has_traded_max(int trader_id) {
    return data.traders[trader_id].bought_amount >= 1200 || data.traders[trader_id].sold_amount >= 1200;
}

io_buffer *iob_figure_traders = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < MAX_TRADERS; i++) {
        struct trader *t = &data.traders[i];
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