#pragma once

#include "figuretype/figure_cartpusher.h"
#include "empire/empire_city.h"
#include "empire/trader_handler.h"

enum e_docker_action {
    ACTION_132_DOCKER_IDLING = 132,
    ACTION_133_DOCKER_IMPORT_QUEUE = 133,
    ACTION_134_DOCKER_EXPORT_QUEUE = 134,
    ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE = 135,
    ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE = 136,
    ACTION_137_DOCKER_EXPORT_RETURNING = 137,
    ACTION_138_DOCKER_IMPORT_RETURNING = 138,
    ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE = 139,
    ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE = 140,
};

class figure_docker : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_DOCKER, figure_docker)
    figure_docker(figure *f) : figure_carrier(f) {}

    virtual void on_create() override {}
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual void update_animation() override;
    virtual void poof() override;

    empire_trader_handle trader();
    empire_city_handle trader_city();

    bool deliver_import_resource(building *dock);
    tile2i get_trade_center_location();
    bool fetch_export_resource(building* dock);
    bool try_import_resource(building *b, e_resource resource, empire_city_handle city_id);
    bool try_export_resource(building *b, e_resource resource, empire_city_handle city_id);
    building_dest get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, e_resource &import_resource);
    building_dest get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, e_resource &export_resource);
};