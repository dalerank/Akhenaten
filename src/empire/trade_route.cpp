#include "trade_route.h"
#include "core/game_environment.h"

#define MAX_ROUTES 20

struct route_resource {
    int limit;
    int traded;
};

static struct route_resource data[MAX_ROUTES][36];

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
            data[route_id][resource].limit = 15;
            break;
        case 15:
            data[route_id][resource].limit = 25;
            break;
        case 25:
            data[route_id][resource].limit = 40;
            break;
        default:
            return 0;
    }
    return 1;
}

int trade_route_decrease_limit(int route_id, int resource) {
    switch (data[route_id][resource].limit) {
        case 40:
            data[route_id][resource].limit = 25;
            break;
        case 25:
            data[route_id][resource].limit = 15;
            break;
        case 15:
            data[route_id][resource].limit = 0;
            break;
        default:
            return 0;
    }
    return 1;
}

void trade_route_increase_traded(int route_id, int resource) {
    data[route_id][resource].traded++;
}

void trade_route_reset_traded(int route_id) {
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        data[route_id][r].traded = 0;
    }
}

int trade_route_limit_reached(int route_id, int resource) {
    return data[route_id][resource].traded >= data[route_id][resource].limit;
}

void trade_routes_save_state(buffer *limit, buffer *traded) {
    for (int route_id = 0; route_id < MAX_ROUTES; route_id++) {
        for (int r = 0; r < RESOURCE_MAX[GAME_ENV]; r++) {
            limit->write_i32(data[route_id][r].limit);
            traded->write_i32(data[route_id][r].traded);
        }
    }
}

void trade_routes_load_state(buffer *limit, buffer *traded) {
    for (int route_id = 0; route_id < MAX_ROUTES; route_id++) {
        for (int r = 0; r < RESOURCE_MAX[GAME_ENV]; r++) {
            data[route_id][r].limit = limit->read_i32();
            data[route_id][r].traded = traded->read_i32();
        }
    }
}

