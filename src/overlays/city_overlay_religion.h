#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_religion : public city_overlay {
    city_overlay_religion();

    virtual bool show_figure(const figure *f) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual int get_column_height(const building *b) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    virtual bool show_building(const building *b) const override;
};

struct city_overlay_religion_god : public city_overlay {
    city_overlay_religion_god();

    bool show_figure(const figure *f) const override;
    void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    bool show_building(const building *b) const override;
};

struct city_overlay_religion_osiris : public city_overlay_religion_god {
    city_overlay_religion_osiris() {
        type = OVERLAY_RELIGION_OSIRIS;
    }
};

struct city_overlay_religion_ra : public city_overlay_religion_god {
    city_overlay_religion_ra() {
        type = OVERLAY_RELIGION_RA;
    }
};

struct city_overlay_religion_ptah : public city_overlay_religion_god {
    city_overlay_religion_ptah() {
        type = OVERLAY_RELIGION_PTAH;
        buildings = {BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH};
    }
};

struct city_overlay_religion_seth : public city_overlay_religion_god {
    city_overlay_religion_seth() {
        type = OVERLAY_RELIGION_SETH;
        buildings = {BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH};
    }
};

struct city_overlay_religion_bast : public city_overlay_religion_god {
    city_overlay_religion_bast() {
        type = OVERLAY_RELIGION_BAST;
        buildings = {BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST};
    }
};

city_overlay* city_overlay_for_religion();
city_overlay* city_overlay_for_religion_osiris();
city_overlay* city_overlay_for_religion_ra();
city_overlay* city_overlay_for_religion_ptah();
city_overlay* city_overlay_for_religion_seth();
city_overlay* city_overlay_for_religion_bast();