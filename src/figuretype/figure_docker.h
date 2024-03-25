#pragma once

#include "figure/figure.h"

class figure_docker : public figure_impl {
public:
    figure_docker(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual e_figure_sound phrase() const override { return {FIGURE_DOCKER, "dock_pusher"}; }
    virtual bool window_info_background(object_info &ctx) override;
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;

    int deliver_import_resource(building *dock);
    tile2i get_trade_center_location();
    int fetch_export_resource(building* dock);
    bool try_import_resource(building *b, e_resource resource, int city_id);
    int try_export_resource(building *b, e_resource resource, int city_id);
    int get_closest_warehouse_for_import(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource &import_resource);
    int get_closest_warehouse_for_export(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource &export_resource);
};