#include "empire/empire.h"

#include "trade_route.h"
#include "io/io_buffer.h"
#include "city/city.h"

#include <algorithm>
#include <limits>

void trade_route::init(e_resource resource, int limit) {
    if (resource != RESOURCE_NONE) {
        resources[resource].limit = limit;
        resources[resource].traded = 0;
    } else {
        resources[resource].limit = std::numeric_limits<uint16_t>::max();
        resources[resource].traded = std::numeric_limits<uint16_t>::max();
    }
}

void trade_route::set_limit(e_resource resource, int limit) {
    if (resource != RESOURCE_NONE && resource < RESOURCES_MAX) {
        resources[resource].limit = (uint16_t)std::max(0, limit);
    }
}

void trade_route::set_traded(e_resource resource, int traded) {
    if (resource != RESOURCE_NONE && resource < RESOURCES_MAX) {
        resources[resource].traded = (uint16_t)std::max(0, traded);
    }
}

int trade_route::limit(e_resource resource, int bonus_inclusion) const {
    int bonus_points = 0;
    if (g_city.religion.ra_slightly_increased_trading_months_left > 0)
        bonus_points = 1;
    if (g_city.religion.ra_harshly_reduced_trading_months_left > 0)
        bonus_points -= 2;
    else if (g_city.religion.ra_slightly_reduced_trading_months_left > 0)
        bonus_points -= 1;

    // just to be safe...
    if (bonus_points < -2)
        bonus_points = -2;
    if (bonus_points > 1)
        bonus_points = 1;

    const int tiers[7] = {0, 0, 0, 1500, 2500, 4000, 4000};
    int bonus = 0;
    int base = resources[resource].limit;
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
    case e_limit_with_bonus:
        return base + bonus;
    case e_limit_base_only:
        return base;
    case e_limit_bonus_only:
        return bonus;
    }

    return 0;
}

int trade_route::traded(e_resource resource) const {
    return resources[resource].traded;
}

bool trade_route::increase_limit(e_resource resource) {
    switch (resources[resource].limit) {
    case 0:
        resources[resource].limit = 1500;
        break;
    case 1500:
        resources[resource].limit = 2500;
        break;
    case 2500:
        resources[resource].limit = 4000;
        break;
    default:
        return false;
    }
    return true;
}
bool trade_route::decrease_limit(e_resource resource) {
    switch (resources[resource].limit) {
    case 4000:
        resources[resource].limit = 2500;
        break;

    case 2500:
        resources[resource].limit = 1500;
        break;

    case 1500:
        resources[resource].limit = 0;
        break;
    default:
        return false;
    }
    return true;
}

void trade_route::increase_traded(e_resource resource, int amount) {
    resources[resource].traded += amount;
}

void trade_route::reset_traded() {
    for (const auto &r: resource_list::all) {
        resources[r.type].traded = 0;
    }
}

int trade_route::limit_reached(e_resource resource) {
    return resources[resource].traded >= limit(resource);
}
