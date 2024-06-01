#pragma once

#include "overlays/city_overlay.h"

city_overlay* city_overlay_for_religion();
struct city_overlay_religion : public city_overlay {
    city_overlay_religion();

    virtual int get_column_height(const building *b) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

struct city_overlay_religion_god : public city_overlay {
    city_overlay_religion_god();
};

city_overlay* city_overlay_for_religion_osiris();
struct city_overlay_religion_osiris : public city_overlay_religion_god {
    city_overlay_religion_osiris() { type = OVERLAY_RELIGION_OSIRIS; }
};

city_overlay* city_overlay_for_religion_ra();
struct city_overlay_religion_ra : public city_overlay_religion_god {
    city_overlay_religion_ra() { type = OVERLAY_RELIGION_RA; }
};

city_overlay* city_overlay_for_religion_ptah();
struct city_overlay_religion_ptah : public city_overlay_religion_god {
    city_overlay_religion_ptah() { type = OVERLAY_RELIGION_PTAH; }
};

city_overlay* city_overlay_for_religion_seth();
struct city_overlay_religion_seth : public city_overlay_religion_god {
    city_overlay_religion_seth() { type = OVERLAY_RELIGION_SETH; }
};

city_overlay* city_overlay_for_religion_bast();
struct city_overlay_religion_bast : public city_overlay_religion_god {
    city_overlay_religion_bast() { type = OVERLAY_RELIGION_BAST; }
};
