#pragma once

#include "building/building.h"

class building_shrine : public building_impl {
public:
    building_shrine(building &b) : building_impl(b) {}
    virtual building_shrine *dcast_shrine() override { return this; }

    virtual void on_place_checks() override;
    virtual e_overlay get_overlay() const override;
};

struct building_shrine_osiris : public building_shrine {
    BUILDING_METAINFO(BUILDING_SHRINE_OSIRIS, building_shrine_osiris, building_shrine);
};

struct building_shrine_ra : public building_shrine {
    BUILDING_METAINFO(BUILDING_SHRINE_RA, building_shrine_ra, building_shrine);
};

struct building_shrine_ptah : public building_shrine {
    BUILDING_METAINFO(BUILDING_SHRINE_PTAH, building_shrine_ptah, building_shrine);
};

struct building_shrine_seth : public building_shrine {
    BUILDING_METAINFO(BUILDING_SHRINE_SETH, building_shrine_seth, building_shrine);
};

struct building_shrine_bast : public building_shrine {
    BUILDING_METAINFO(BUILDING_SHRINE_BAST, building_shrine_bast, building_shrine);
};