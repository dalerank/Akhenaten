#pragma once

#include "building/building.h"

struct building_storage;

class building_storage_room : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_STORAGE_ROOM, building_storage_room)

    building_storage_room(building &b) : building_impl(b), stored_full_amount(b.stored_full_amount) {}

    virtual void on_create(int orientation) override;
    virtual building_storage_room *dcast_storage_room() { return this; }
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_STORAGE_YARD; }

    const building_storage *storage();
    building_storage_yard *yard() { return main()->dcast_storage_yard(); }
    building_storage_room *next_room() { return next()->dcast_storage_room(); }
    void set_image(e_resource resource);
    void add_import(e_resource resource);
    bool is_this_space_the_best(tile2i tile, e_resource resource, int distance_from_entry);
    void remove_export(e_resource resource);
    int accepting_amount(e_resource resource);

    short &stored_full_amount;
};