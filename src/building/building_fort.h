#pragma once

#include "building/building.h"

class building_fort : public building_impl {
public:
    building_fort(building &b) : building_impl(b) {}
    virtual building_fort *dcast_fort() override { return this; }

    virtual void window_info_background(object_info &c) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void highlight_waypoints() override;

    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};

class building_fort_ground : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FORT_GROUND, building_fort_ground)
    building_fort_ground(building &b) : building_impl(b) {}
    virtual building_fort_ground *dcast_fort_ground() { return this; }
};

class building_fort_charioteers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_CHARIOTEERS, building_fort_charioteers)
    building_fort_charioteers(building &b) : building_fort(b) {}
};

class building_fort_archers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_ARCHERS, building_fort_archers)
    building_fort_archers(building &b) : building_fort(b) {}
};

class building_fort_infantry : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_INFANTRY, building_fort_infantry)
    building_fort_infantry(building &b) : building_fort(b) {}
};