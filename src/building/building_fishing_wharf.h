#pragma once

#include "building/building.h"

class building_fishing_wharf : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FISHING_WHARF, building_fishing_wharf)

    building_fishing_wharf(building &b) : building_impl(b) {}
    virtual building_fishing_wharf *dcast_fishing_wharf() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void update_count() const override;
    virtual void update_day() override;
    virtual void spawn_figure() override;
    virtual void on_place_checks() override;
    virtual void on_undo() override;
    virtual void update_map_orientation(int orientation) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WHARF; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void window_info_background(object_info &c) override;
};