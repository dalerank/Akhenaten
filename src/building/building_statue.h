#pragma once

#include "building/building.h"

class building_statue : public building_impl {
public:
    building_statue(building &b) : building_impl(b) {}
    virtual building_statue *dcast_statue() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual bool is_workshop() const override { return true; }
    virtual void window_info_background(object_info &c) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void update_map_orientation(int map_orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    static int get_image(int type, int orientation, int variant);
    int get_image_from_value(int type, int combined, int variant, int map_orientation);
};

class building_small_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STATUE, building_small_statue)
    building_small_statue(building &b) : building_statue(b) {}
};

class building_medium_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STATUE, building_medium_statue)
    building_medium_statue(building &b) : building_statue(b) {}
};

class building_large_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STATUE, building_large_statue)
    building_large_statue(building &b) : building_statue(b) {}
};

int building_statue_random_variant(int type, int variant);
int building_statue_next_variant(int type, int variant);
