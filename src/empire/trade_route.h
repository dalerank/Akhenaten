#ifndef EMPIRE_TRADE_ROUTE_H
#define EMPIRE_TRADE_ROUTE_H

#include "core/buffer.h"
#include "game/resource.h"

void trade_route_init(int route_id, int resource, int limit);

enum {
    LIMIT_WITH_BONUS,
    LIMIT_BASE_ONLY,
    LIMIT_BONUS_ONLY
};

int trade_route_limit(int route_id, int resource, int bonus_inclusion = LIMIT_WITH_BONUS);
int trade_route_traded(int route_id, int resource);

/**
 * Increases the trade limit of the resource
 * @param route_id Trade route
 * @param resource Resource
 * @return True on success, false if the limit couldn't be increased
 */
bool trade_route_increase_limit(int route_id, int resource);

/**
 * Decreases the trade limit of the resource
 * @param route_id Trade route
 * @param resource Resource
 * @return True on success, false if the limit couldn't be decreased
 */
bool trade_route_decrease_limit(int route_id, int resource);
void trade_route_increase_traded(int route_id, int resource);
void trade_route_reset_traded(int route_id);
int trade_route_limit_reached(int route_id, int resource);

#endif // EMPIRE_TRADE_ROUTE_H
