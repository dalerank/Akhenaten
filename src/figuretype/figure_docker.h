#pragma once

#include "figuretype/figure_cartpusher.h"

class figure_docker : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_DOCKER, figure_docker)
    figure_docker(figure *f) : figure_carrier(f) {}

    virtual void on_create() override {}
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_DOCKER, "dock_pusher"}; }
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual void update_animation() override;
    virtual void poof() override;

    int trader_id();
    int trader_city_id();
    bool deliver_import_resource(building *dock);
    tile2i get_trade_center_location();
    bool fetch_export_resource(building* dock);
    bool try_import_resource(building *b, e_resource resource, int city_id);
    int try_export_resource(building *b, e_resource resource, int city_id);
    int get_closest_warehouse_for_import(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource &import_resource);
    int get_closest_warehouse_for_export(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource &export_resource);
};