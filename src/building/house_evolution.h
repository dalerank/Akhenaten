#pragma once

#include "building/building.h"

/**
 * Determine the text to show for evolution of a house, stored in house->evolve_text_id
 * @param house House to determine text for
 * @param worst_desirability_building The ID of the building with worst contribution to desirability
 */
void building_house_determine_evolve_text(building* house, int worst_desirability_building);

/**
 * Determine building with worst contribution to desirability
 * @param house House to determine worst building for
 * @return Worst desirability building ID
 */
int building_house_determine_worst_desirability_building(building* house);
