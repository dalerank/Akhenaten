#ifndef BUILDING_COUNT_H
#define BUILDING_COUNT_H

#include "core/buffer.h"
#include "building/type.h"
#include "game/resource.h"

/**
 * @file
 * Building totals
 */

/**
 * Updates the building counts and does some extra work on the side
 */
void building_entertainment_update();
void building_count_update(void);

/**
 * Returns the active building count for the type
 * @param type Building type
 * @return Number of active buildings
 */
int building_count_active(int type);

/**
 * Returns the building count for the type
 * @param type Building type
 * @return Total number of buildings
 */
int building_count_total(int type);

/**
 * Returns the active building count for the resource type
 * @param resource Resource type
 * @return Number of active buildings
 */
int building_count_industry_active(int resource);

/**
 * Returns the building count for the resource type
 * @param resource Resource type
 * @return Total number of buildings
 */
int building_count_industry_total(int resource);

#endif // BUILDING_COUNT_H
