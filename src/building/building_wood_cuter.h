#pragma once

#include "building/building.h"

class building_wood_cutter : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WOOD_CUTTERS, building_wood_cutter, building_impl)

    virtual building_wood_cutter *dcast_wood_cutter() override { return this; }

    struct runtime_data_t {
        uint8_t max_gatheres;
    } BUILDING_RUNTIME_DATA(runtime_data_t);

    virtual void on_create(int orientation) override;
    virtual bool is_administration() const override { return true; }
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    bool can_spawn_lumberjack(int max_gatherers_per_building, int carry_per_person);
};