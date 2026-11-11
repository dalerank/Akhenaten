#pragma once

#include "core/buffer.h"
#include "figure/figure_type.h"
#include "core/bstring.h"

/**
 * Initializes the figure name generator.
 */
void figure_name_init();

/**
 * Determines a new name for the figure type
 * @param type Type of figure
 * @return Name ID
 */
bstring32 figure_name_get(int type);

// OG name counter table (41 slots); -1 for an out-of-range slot or a type without an OG name group.
int figure_name_counter(int slot);
