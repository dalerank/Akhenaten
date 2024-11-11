#pragma once

#include "overlays/city_overlay.h"
#include "city/city_religion.h"

city_overlay* city_overlay_for_religion();
struct city_overlay_religion : public city_overlay_t<OVERLAY_RELIGION> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

template<e_overlay TYPE>
struct city_overlay_religion_god : public city_overlay_t<TYPE> {
    e_god _god;

    inline city_overlay_religion_god(e_god god) {
        _god = god;
    }

    virtual int get_column_height(const building *b) const override {
        if (!b->house_size) {
            return NO_COLUMN;
        }

        int value = 0;
        switch (_god) {
        case GOD_OSIRIS: value = b->data.house.temple_osiris; break;
        case GOD_RA: value = b->data.house.temple_ra; break;
        case GOD_PTAH: value = b->data.house.temple_ptah; break;
        case GOD_SETH: value = b->data.house.temple_seth; break;
        case GOD_BAST: value = b->data.house.temple_bast; break;
        }

        return value / 10;
    }
};

city_overlay* city_overlay_for_religion_osiris();
struct city_overlay_religion_osiris : public city_overlay_religion_god<OVERLAY_RELIGION_OSIRIS> {
    city_overlay_religion_osiris() : city_overlay_religion_god(GOD_OSIRIS) {}
};

city_overlay* city_overlay_for_religion_ra();
struct city_overlay_religion_ra : public city_overlay_religion_god<OVERLAY_RELIGION_RA> {
    city_overlay_religion_ra() : city_overlay_religion_god(GOD_RA) {}
};

city_overlay* city_overlay_for_religion_ptah();
struct city_overlay_religion_ptah : public city_overlay_religion_god<OVERLAY_RELIGION_PTAH> {
    city_overlay_religion_ptah() : city_overlay_religion_god(GOD_PTAH) {}
};

city_overlay* city_overlay_for_religion_seth();
struct city_overlay_religion_seth : public city_overlay_religion_god<OVERLAY_RELIGION_SETH> {
    city_overlay_religion_seth() : city_overlay_religion_god(GOD_SETH) {}
};

city_overlay* city_overlay_for_religion_bast();
struct city_overlay_religion_bast : public city_overlay_religion_god<OVERLAY_RELIGION_BAST> {
    city_overlay_religion_bast() : city_overlay_religion_god(GOD_BAST) {}
};
