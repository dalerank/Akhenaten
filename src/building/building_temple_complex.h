#pragma once

#include "building/building.h"

class building_temple_complex : public building_impl {
public:
    building_temple_complex(building &b) : building_impl(b) {}

    virtual building_temple_complex *dcast_temple_complex() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_count() const override;
    virtual void on_post_load() override;
    virtual void on_place(int orientation, int variant) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
};

class building_temple_complex_osiris : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_OSIRIS, building_temple_complex_osiris)
    building_temple_complex_osiris(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_OSIRIS; }
};


class building_temple_complex_ra : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_RA, building_temple_complex_ra)
    building_temple_complex_ra(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_RA; }
};
  
class building_temple_complex_ptah : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_PTAH, building_temple_complex_ptah)
    building_temple_complex_ptah(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_PTAH; }
};

class building_temple_complex_seth : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_SETH, building_temple_complex_seth)
    building_temple_complex_seth(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_SETH; }
};

class building_temple_complex_bast : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_BAST, building_temple_complex_bast)
    building_temple_complex_bast(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_BAST; }
};