#pragma once

#include "building/building.h"

/**
 * @brief Building class representing an Architect Post in the city
 *
 * The Architect Post is a specialized building that provides architectural services
 * to the city. It spawns architect figures who can perform various construction
 * and maintenance tasks throughout the city. This building is essential for
 * maintaining and improving the city's infrastructure.
 *
 * Key features:
 * - Spawns architect figures for city maintenance
 * - Displays damage overlay to show building condition
 * - Plays engineer post sound effects
 */
class building_architect_post : public building_impl {
public:
    // registers this building type with the game engine
    BUILDING_METAINFO(BUILDING_ARCHITECT_POST, building_architect_post, building_impl)

    /**
     * @brief Safe cast to architect post type
     * @return Pointer to this building as architect post, or nullptr if cast fails
     */
    virtual building_architect_post *dcast_architect_post() override { return this; }
};
