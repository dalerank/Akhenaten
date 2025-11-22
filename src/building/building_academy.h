#pragma once

// Header for the "Academy" building implementation.
// The Academy belongs to the education system and is responsible for spawning
// related figures, rendering decorative elements, and updating graphics.

#include "building/building.h"

// "Academy" building class. Inherits from the base building implementation.
class building_academy : public building_impl {
public:
    // Registers building metainfo within the system (RTTI/factory).
    BUILDING_METAINFO(BUILDING_ACADEMY, building_academy, building_impl)

    // Called when the building is created.
    // orientation — the orientation when placed on the map.
    virtual void on_create(int orientation) override {}

    // City sound channel for this building (disabled).
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }

    // Spawns a worker/service figure associated with the Academy.
    virtual void spawn_figure() override;

    // Updates the building graphics/animations depending on state.
    virtual void update_graphic() override;

    // Renders decorative elements and animations at height level.
    // ctx   — drawing context;
    // point — screen coordinates of the tile's base point;
    // tile  — map tile coordinates;
    // mask  — color mask/shadows/lighting.
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};