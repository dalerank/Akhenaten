#pragma once

#include "overlays/city_overlay.h"
#include "city/city_religion.h"
#include "building/building_house.h"

struct city_overlay_religion : public city_overlay_t<OVERLAY_RELIGION> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};

template<e_overlay TYPE>
struct city_overlay_religion_god : public city_overlay_t<TYPE> {
    e_god _god;

    inline city_overlay_religion_god(e_god god) {
        _god = god;
    }

    virtual int get_column_height(const building *b) const override {
        auto house = ((building*)b)->dcast_house();

        if (!house || !house->house_population()) {
            return COLUMN_TYPE_NONE;
        }

        int value = 0;
        auto &housed = house->runtime_data();
        switch (_god) {
        case GOD_OSIRIS: value = housed.temple_osiris; break;
        case GOD_RA: value = housed.temple_ra; break;
        case GOD_PTAH: value = housed.temple_ptah; break;
        case GOD_SETH: value = housed.temple_seth; break;
        case GOD_BAST: value = housed.temple_bast; break;
        }

        return value / 10;
    }
};

struct city_overlay_religion_osiris : public city_overlay_religion_god<OVERLAY_RELIGION_OSIRIS> {
    city_overlay_religion_osiris() : city_overlay_religion_god(GOD_OSIRIS) {}
};

struct city_overlay_religion_ra : public city_overlay_religion_god<OVERLAY_RELIGION_RA> {
    city_overlay_religion_ra() : city_overlay_religion_god(GOD_RA) {}
};

struct city_overlay_religion_ptah : public city_overlay_religion_god<OVERLAY_RELIGION_PTAH> {
    city_overlay_religion_ptah() : city_overlay_religion_god(GOD_PTAH) {}
};

struct city_overlay_religion_seth : public city_overlay_religion_god<OVERLAY_RELIGION_SETH> {
    city_overlay_religion_seth() : city_overlay_religion_god(GOD_SETH) {}
};

struct city_overlay_religion_bast : public city_overlay_religion_god<OVERLAY_RELIGION_BAST> {
    city_overlay_religion_bast() : city_overlay_religion_god(GOD_BAST) {}
};
