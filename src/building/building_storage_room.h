#pragma once

#include "building/building.h"

struct storage_t;

class building_storage_room : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_STORAGE_ROOM, building_storage_room, building_impl)

    virtual building_storage *dcast_storage() override { return main()->dcast_storage(); }
    virtual building_storage_room *dcast_storage_room() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override { /*nothing*/ }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }
    virtual bool can_play_animation() const override { return false; }
    virtual int get_fire_risk(int value) const override { return 0; }

    e_resource resource() const { return base.storage.data()[0].type; }
    void take_resource(int amount);

    const storage_t *storage();
    building_storage_yard *yard() { return main()->dcast_storage_yard(); }
    building_storage_room *next_room() { return next()->dcast_storage_room(); }
    const building_storage_room *next_room() const { return ((building_impl*)this)->next()->dcast_storage_room(); }
    void set_image(e_resource resource);
    void add_import(e_resource resource);
    int distance_with_penalty(tile2i tile, e_resource resource, int distance_from_entry);
    void remove_export(e_resource resource);
};