#pragma once

#include "game/resource.h"
#include "building/building.h"

class building_bazaar : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BAZAAR, building_bazaar)

    building_bazaar(building &b) : building_impl(b) {}
    virtual building_bazaar *dcast_bazaar() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BAZAAR_ACCESS; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MARKET; }
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    building *get_storage_destination();
    void draw_simple_background(object_info &c);
    void draw_orders_background(object_info &c);
    void draw_orders_foreground(object_info &c);
    int max_food_stock();
    int max_goods_stock();
    bool is_good_accepted(int index);
    void toggle_good_accepted(int index);
    void unaccept_all_goods();
};

