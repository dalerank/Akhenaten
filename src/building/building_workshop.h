#pragma once

#include "building/building_industry.h"

void building_workshop_draw_foreground(object_info &c);

class building_lamp_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_LAMP_WORKSHOP, building_lamp_workshop, building_industry)

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_paint_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_PAINT_WORKSHOP, building_paint_workshop, building_industry)

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};