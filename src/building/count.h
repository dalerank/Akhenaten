#pragma once

#include "building/building_type.h"
#include "core/buffer.h"
#include "game/resource.h"

/**
 * Updates the building counts and does some extra work on the side
 */
void building_entertainment_update();
void building_count_update();

/**
 * Returns the active building count for the type
 * @param type Building type
 * @return Number of active buildings
 */
int building_count_active(e_building_type type);

/**
 * Returns the building count for the type
 * @param type Building type
 * @return Total number of buildings
 */
int building_count_total(e_building_type type);

/**
 * Returns the active building count for the resource type
 * @param resource Resource type
 * @return Number of active buildings
 */
int building_count_industry_active(e_resource resource);

/**
 * Returns the building count for the resource type
 * @param resource Resource type
 * @return Total number of buildings
 */
int building_count_industry_total(e_resource resource);
void building_increase_type_count(int type, bool active);