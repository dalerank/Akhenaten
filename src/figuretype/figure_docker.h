#pragma once

#include "figuretype/figure_cartpusher.h"
#include "empire/empire_city.h"
#include "empire/trader_handler.h"

class building_dock;

enum e_docker_action : uint16_t {
    ACTION_0_DOCKER_IDLING = 0,
    ACTION_1_DOCKER_IMPORT_QUEUE = 1,
    ACTION_2_DOCKER_EXPORT_QUEUE = 2,
    ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE = 3,
    ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE = 4,
    ACTION_5_DOCKER_EXPORT_RETURNING = 5,
    ACTION_6_DOCKER_IMPORT_RETURNING = 6,
    ACTION_7_DOCKER_IMPORT_AT_WAREHOUSE = 7,
    ACTION_8_DOCKER_RECALCULATE = 8,
    ACTION_9_DOCKER_EXPORT_AT_WAREHOUSE = 9,

    ACTION_10_DOCKER_MAX
};
using figure_docker_action_tokens_t = token_holder<e_docker_action, ACTION_0_DOCKER_IDLING, ACTION_10_DOCKER_MAX>;
extern const figure_docker_action_tokens_t figure_docker_action_tokens;

class figure_docker : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_DOCKER, figure_docker)
    figure_docker(figure *f) : figure_carrier(f) {}

    virtual void on_create() override {}
    virtual void on_destroy() override;
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void poof() override;

    empire_trader_handle trader();
    empire_city_handle trader_city();

    virtual void set_cart_offset(int direction) const override;

    bool deliver_import_resource(building *dock);
    tile2i get_trade_center_location();
    bool fetch_export_resource(building* dock);
    int try_import_resource(building *b, e_resource resource, empire_city_handle city_id);
    int try_export_resource(building *b, e_resource resource, empire_city_handle city_id);
    building_dest get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &import_resource);
    building_dest get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &export_resource);
};
