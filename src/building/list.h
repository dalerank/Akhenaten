#pragma once

#include "core/custom_span.hpp"

/**
 * Clears the large building list
 * @param clear_entries Whether to clear the item values as well
 */
void building_list_large_clear(int clear_entries);

/**
 * Adds a building to the large list
 * @param building_id Building ID
 */
void building_list_large_add(int building_id);

/**
 * Returns the number of buildings on the large list
 * @return List size
 */
int building_list_large_size(void);

/**
 * Returns the items on the large list
 * @return List of building IDs
 */
const int* building_list_large_items(void);
