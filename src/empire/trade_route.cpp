#include "io/io_buffer.h"
#include <city/data_private.h>
#include "trade_route.h"
#include "core/game_environment.h"

#define MAX_ROUTES 20

struct route_resource {
    int limit;
    int traded;
};

static struct route_resource data[MAX_ROUTES][RESOURCES_MAX];

void trade_route_init(int route_id, int resource, int limit) {
    data[route_id][resource].limit = limit;
    data[route_id][resource].traded = 0;
}

int trade_route_limit(int route_id, int resource, int bonus_inclusion) {

    int bonus_points = 0;
    if (city_data.religion.ra_slightly_increased_trading_months_left > 0)
        bonus_points = 1;
    if (city_data.religion.ra_harshly_reduced_trading_months_left > 0)
        bonus_points -= 2;
    else if (city_data.religion.ra_slightly_reduced_trading_months_left > 0)
        bonus_points -= 1;

    // just to be safe...
    if (bonus_points < -2)
        bonus_points = -2;
    if (bonus_points > 1)
        bonus_points = 1;

    const int tiers[7] = {0, 0, 0, 1500, 2500, 4000, 4000};
    int bonus = 0;
    int base = data[route_id][resource].limit;
    switch (base) {
        case 0:
            bonus = tiers[2 + bonus_points];
            break;
        case 1500:
            bonus = tiers[3 + bonus_points] - 1500;
            break;
        case 2500:
            bonus = tiers[4 + bonus_points] - 2500;
            break;
        case 4000:
            bonus = tiers[5 + bonus_points] - 4000;
            break;
    }

    switch (bonus_inclusion) {
        case LIMIT_WITH_BONUS:
            return base + bonus;
        case LIMIT_BASE_ONLY:
            return base;
        case LIMIT_BONUS_ONLY:
            return bonus;
    }
}
int trade_route_traded(int route_id, int resource) {
    return data[route_id][resource].traded;
}

bool trade_route_increase_limit(int route_id, int resource) {
    switch (data[route_id][resource].limit) {
        case 0:
            data[route_id][resource].limit = 1500;
            break;
        case 1500:
            data[route_id][resource].limit = 2500;
            break;
        case 2500:
            data[route_id][resource].limit = 4000;
            break;
        default:
            return false;
    }
    return true;
}
bool trade_route_decrease_limit(int route_id, int resource) {
    switch (data[route_id][resource].limit) {
        case 4000:
            data[route_id][resource].limit = 2500;
            break;
        case 2500:
            data[route_id][resource].limit = 1500;
            break;
        case 1500:
            data[route_id][resource].limit = 0;
            break;
        default:
            return false;
    }
    return true;
}

void trade_route_increase_traded(int route_id, int resource) {
    data[route_id][resource].traded += 100;
}
void trade_route_reset_traded(int route_id) {
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        data[route_id][r].traded = 0;
    }
}

int trade_route_limit_reached(int route_id, int resource) {
//    return data[route_id][resource].traded >= data[route_id][resource].limit;
    return data[route_id][resource].traded >= trade_route_limit(route_id, resource);
}

io_buffer *iob_trade_routes_limits = new io_buffer([](io_buffer *iob) {
    for (int route_id = 0; route_id < MAX_ROUTES; route_id++) {
        for (int r = 0; r < RESOURCES_MAX; r++) {
            data[route_id][r].limit *= 0.01;
            iob->bind(BIND_SIGNATURE_INT32, &data[route_id][r].limit);
            data[route_id][r].limit *= 100;
//            data[route_id][r].traded = traded->read_i32() * 100;
        }
    }
});
io_buffer *iob_trade_routes_traded = new io_buffer([](io_buffer *iob) {
    for (int route_id = 0; route_id < MAX_ROUTES; route_id++) {
        for (int r = 0; r < RESOURCES_MAX; r++) {
            data[route_id][r].traded *= 0.01;
            iob->bind(BIND_SIGNATURE_INT32, &data[route_id][r].traded);
            data[route_id][r].traded *= 100;
//            data[route_id][r].limit = limit->read_i32() * 100;
        }
    }
});