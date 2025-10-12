#pragma once

#include "building/building.h"

class building_temple_complex_upgrade : public building_impl {
public:
    building_temple_complex_upgrade(building &b) : building_impl(b) {}

    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void update_map_orientation(int orientation) override;
};

class building_temple_complex_altar : public building_temple_complex_upgrade {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR, building_temple_complex_altar, building_temple_complex_upgrade)
    virtual building_temple_complex_altar *dcast_temple_complex_altar() override { return this; }
};

class building_temple_complex_oracle : public building_temple_complex_upgrade {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE, building_temple_complex_oracle, building_temple_complex_upgrade)
    virtual building_temple_complex_oracle *dcast_temple_complex_oracle() override { return this; }

    virtual void on_place_checks() override;
};

class building_temple_complex_altar_ra : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, building_temple_complex_altar_ra, building_temple_complex_altar)
};