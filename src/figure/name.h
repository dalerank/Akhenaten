#ifndef FIGURE_NAME_H
#define FIGURE_NAME_H

#include "core/buffer.h"
#include "figure/type.h"

/**
 * @file
 * Figure name generation
 */

/**
 * Initializes the figure name generator.
 */
void figure_name_init(void);

/**
 * Determines a new name for the figure type
 * @param type Type of figure
 * @param enemy Enemy type if applicable
 * @return Name ID
 */
int figure_name_get(int type, int enemy);

#endif // FIGURE_NAME_H
