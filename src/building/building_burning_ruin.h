#pragma once

#include "building/building.h"

class building_burning_ruin : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BURNING_RUIN, building_burning_ruin, building_impl)
    virtual building_burning_ruin *dcast_burning_ruin() override { return this; }

    // OG counts fire_duration up from initial_burned_days() past RUIN_BURN_DAYS; here it counts down
    // (firemen and clear.cpp read it as "remaining"), so fire_duration == RUIN_BURN_DAYS + 1 - og_duration.
    static constexpr int RUIN_BURN_DAYS = 32;
    // OG walker_rules[WALKER_RULE_FIRE_OUT_DURATION]: a fireman pins og_duration here, so the next update() rubbles.
    static constexpr int FIRE_OUT_DURATION = 32;

    struct static_params : public building_static_params {
        int fire_animations;
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_tick(bool refresh_only) override;
    virtual void update_animation() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BURNING_RUIN; }
    virtual bool target_route_tile_blocked(int grid_offset) const override;
    bool update();

    tile2i can_be_accessed();
    void extinguish() { base.fire_duration = RUIN_BURN_DAYS + 1 - FIRE_OUT_DURATION; }

    static int initial_burned_days(const building& b) { return (b.map_random_7bit & 7) + 1; }
    static void update_all_ruins();
    static xspan<uint16_t> get_all();
    static std::pair<int, tile2i> get_closest_from(tile2i tile);
};
ANK_CONFIG_STRUCT(building_burning_ruin::static_params, fire_animations)