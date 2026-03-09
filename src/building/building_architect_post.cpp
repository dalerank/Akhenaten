/**
 * @file building_architect_post.cpp
 * @brief Implementation of the architect post building functionality
 *
 * This file contains the implementation for the architect post building,
 * which is responsible for spawning architect figures and managing
 * building-related console commands for debugging purposes.
 */

#include "building_architect_post.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_architect_post);

bool building_architect_post::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}