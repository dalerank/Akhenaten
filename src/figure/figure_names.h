#pragma once

#include "core/buffer.h"
#include "figure/figure_type.h"

/**
 * Initializes the figure name generator.
 */
void figure_name_init();

/**
 * Determines a new name for the figure type
 * @param type Type of figure
 * @param enemy Enemy type if applicable
 * @return Name ID
 */
int figure_name_get(int type, int enemy);
