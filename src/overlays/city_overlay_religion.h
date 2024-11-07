#pragma once

#include "overlays/city_overlay.h"
#include "city/city_religion.h"

city_overlay* city_overlay_for_religion();
struct city_overlay_religion : public city_overlay {
    city_overlay_religion();

    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

struct city_overlay_religion_god : public city_overlay {
    e_god _god;

    inline city_overlay_religion_god(e_overlay mode, e_god god) {
        type = mode;
        _god = god;
        column_type = COLUMN_TYPE_WATER_ACCESS;
    }

    virtual int get_column_height(const building *b) const override;
};

city_overlay* city_overlay_for_religion_osiris();
struct city_overlay_religion_osiris : public city_overlay_religion_god {
    city_overlay_religion_osiris() : city_overlay_religion_god(OVERLAY_RELIGION_OSIRIS, GOD_OSIRIS) {}
};

city_overlay* city_overlay_for_religion_ra();
struct city_overlay_religion_ra : public city_overlay_religion_god {
    city_overlay_religion_ra() : city_overlay_religion_god(OVERLAY_RELIGION_RA, GOD_RA) {}
};

city_overlay* city_overlay_for_religion_ptah();
struct city_overlay_religion_ptah : public city_overlay_religion_god {
    city_overlay_religion_ptah() : city_overlay_religion_god(OVERLAY_RELIGION_PTAH, GOD_PTAH) {}
};

city_overlay* city_overlay_for_religion_seth();
struct city_overlay_religion_seth : public city_overlay_religion_god {
    city_overlay_religion_seth() : city_overlay_religion_god(OVERLAY_RELIGION_SETH, GOD_SETH) {}
};

city_overlay* city_overlay_for_religion_bast();
struct city_overlay_religion_bast : public city_overlay_religion_god {
    city_overlay_religion_bast() : city_overlay_religion_god(OVERLAY_RELIGION_BAST, GOD_BAST) {}
};
