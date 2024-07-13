#pragma once

#include "core/buffer.h"
#include "game/resource.h"

struct trade_route {
    enum e_limit { 
        e_limit_with_bonus, 
        e_limit_base_only, 
        e_limit_bonus_only 
    };

    struct route_resource {
        int limit;
        int traded;
    };

    route_resource resources[RESOURCES_MAX];

    int limit_reached(e_resource resource);
    int limit(e_resource resource, int bonus_inclusion = e_limit_with_bonus) const;
    void reset_traded();
    void increase_traded(e_resource resource, int amount);
    bool decrease_limit(e_resource resource);
    bool increase_limit(e_resource resource);
    int traded(e_resource resource) const;
    void init(e_resource resource, int limit);
};