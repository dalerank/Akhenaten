#include <game/io/io_buffer.h>
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

int trade_route_limit(int route_id, int resource) {
    return data[route_id][resource].limit;
}
int trade_route_traded(int route_id, int resource) {
    return data[route_id][resource].traded;
}

int trade_route_increase_limit(int route_id, int resource) {
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
            return 0;
    }
    return 1;
}
int trade_route_decrease_limit(int route_id, int resource) {
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
            return 0;
    }
    return 1;
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
    return data[route_id][resource].traded >= data[route_id][resource].limit;
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