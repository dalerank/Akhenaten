#pragma once

#include "building/building.h"

class building_temple : public building_impl {
public:
    building_temple(building &b) : building_impl(b) {}
    virtual building_temple *dcast_temple() override { return this; }

    //virtual void on_create() override;
    virtual e_overlay get_overlay() const override;
    virtual e_sound_channel_city sound_channel() const override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};

struct building_temple_osiris : public building_temple {
    building_temple_osiris(building &b) : building_temple(b) {}
    BUILDING_METAINFO(BUILDING_TEMPLE_OSIRIS, building_temple_osiris);
};

struct building_temple_ra : public building_temple {
    building_temple_ra(building &b) : building_temple(b) {}
    BUILDING_METAINFO(BUILDING_TEMPLE_RA, building_temple_ra);
};

struct building_temple_ptah : public building_temple {
    building_temple_ptah(building &b) : building_temple(b) {}
    BUILDING_METAINFO(BUILDING_TEMPLE_PTAH, building_temple_ptah);
};

struct building_temple_seth : public building_temple {
    building_temple_seth(building &b) : building_temple(b) {}
    BUILDING_METAINFO(BUILDING_TEMPLE_SETH, building_temple_seth);
};

struct building_temple_bast : public building_temple {
    building_temple_bast(building &b) : building_temple(b) {}
    BUILDING_METAINFO(BUILDING_TEMPLE_BAST, building_temple_bast);
};
