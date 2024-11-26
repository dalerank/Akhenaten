#pragma once

#include "building/building_industry.h"

void building_workshop_draw_background(object_info &c, e_resource input_resource_a);
void building_workshop_draw_foreground(object_info &c);

class building_lamp_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_LAMP_WORKSHOP, building_lamp_workshop)
    building_lamp_workshop(building &b) : building_industry(b) {}

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    virtual void update_count() const override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_paint_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_PAINT_WORKSHOP, building_paint_workshop)
    building_paint_workshop(building &b) : building_industry(b) {}

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    virtual void update_count() const override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};