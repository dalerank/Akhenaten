#pragma once

#include "city/object_info.h"
#include "building/building.h"
#include "window/window_building_info.h"

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
 * - Supports custom drawing of ornaments and animations
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

    /**
     * @brief Spawns architect figures from this building
     * 
     * Creates architect figures that will perform various tasks around the city
     * such as building maintenance, construction assistance, and infrastructure
     * improvements. The spawning behavior depends on the building's state and
     * the city's needs.
     */
    virtual void spawn_figure() override;
    
    /**
     * @brief Updates the building's visual appearance
     * 
     * Refreshes the building's graphics based on its current state
     */
    virtual void update_graphic() override;
    
    /**
     * @brief Returns the sound channel for this building's audio
     * @return SOUND_CHANNEL_CITY_ENGINEERS_POST - engineer post sound effects
     */
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_ENGINEERS_POST; }
    
    /**
     * @brief Draws building ornaments and animations with height consideration
     * 
     * Renders decorative elements and animated components of the building,
     * taking into account the building's height and position for proper
     * visual layering and depth effects.
     * 
     * @param ctx The painter context for rendering
     * @param point The screen position to draw at
     * @param tile The tile position of the building
     * @param color_mask Color tinting to apply
     * @return true if drawing was successful, false otherwise
     */
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

struct info_window_architect_post : public building_info_window_t<info_window_architect_post> {
    virtual void window_info_background(object_info& c) override {
        building_info_window::common_info_background(c);
    }
};