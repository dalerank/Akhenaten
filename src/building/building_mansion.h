#pragma once

#include "building/building.h"

class building_mansion : public building_impl {
public:
    using inherited = building_impl;

    building_mansion(building &b) : building_impl(b) {}
    virtual building_mansion *dcast_mansion() override { return this; }

    struct runtime_data_t {
        int32_t personal_savings_storage;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_place(int orientation, int variant) override;
    virtual void spawn_figure() override;
    virtual void update_animation() override { base.play_animation = true; es(__func__); }
    virtual void update_graphic() override;
    virtual void on_post_load() override;
    virtual void update_count() const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MANSION; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    virtual bool is_protected_by_police() const override;
    static void check_theft_from_mansions();

    static bool exist_in_city();
};
ANK_CONFIG_PROPERTY(building_mansion::runtime_data_t, personal_savings_storage)

class building_personal_mansion : public building_mansion {
public:
    BUILDING_METAINFO(BUILDING_PERSONAL_MANSION, building_personal_mansion, building_mansion)
};

class building_family_mansion : public building_mansion {
public:
    BUILDING_METAINFO(BUILDING_FAMILY_MANSION, building_family_mansion, building_mansion)
};

class building_dynasty_mansion : public building_mansion {
public:
    BUILDING_METAINFO(BUILDING_DYNASTY_MANSION, building_dynasty_mansion, building_mansion)
};