#pragma once

#include "figuretype/figure_cartpusher.h"
#include "empire/empire_city.h"
#include "empire/trader_handler.h"

class building_dock;
class building_storage_yard;
class figure_trade_ship;

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
    // Ferry states: the shared ids 6/7 are taken by our import states, see ferry_*_action().
    ACTION_10_DOCKER_ON_FERRY = 10,
    ACTION_11_DOCKER_WAIT_FOR_FERRY = 11,

    ACTION_12_DOCKER_MAX
};
using figure_docker_action_tokens_t = token_holder<e_docker_action, ACTION_0_DOCKER_IDLING, ACTION_12_DOCKER_MAX>;
extern const figure_docker_action_tokens_t figure_docker_action_tokens;

// Pharaoh FIGURE_ACTION_DOCKER_* ids. They overlap ours (OG 8 = idle, ours 8 = recalculate).
// TODO: remap OG savegame dockers to our ids on load.
enum e_docker_og_action : uint16_t {
    ACTION_OG_6_DOCKER_ON_FERRY = 6,
    ACTION_OG_7_DOCKER_WAIT_FOR_FERRY = 7,
    ACTION_OG_8_DOCKER_IDLE = 8,
    ACTION_OG_9_DOCKER_IMPORT_QUEUE = 9,
    ACTION_OG_10_DOCKER_EXPORT_QUEUE = 10,
    ACTION_OG_11_DOCKER_IMPORT_TO_STORAGEYARD = 11,
    ACTION_OG_12_DOCKER_EXPORT_TO_STORAGEYARD = 12,
    ACTION_OG_13_DOCKER_EXPORT_RETURNING = 13,
    ACTION_OG_14_DOCKER_RETURNING = 14,
    ACTION_OG_15_DOCKER_IMPORT_AT_STORAGEYARD = 15,
    ACTION_OG_16_DOCKER_EXPORT_AT_STORAGEYARD = 16,
};

class figure_docker : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_DOCKER, figure_docker)
    figure_docker(figure *f) : figure_carrier(f) {}

    struct static_params : public figure_static_params {
        uint16_t load_amount;   // units per load (OG 100)
        uint8_t max_loads;      // loads per trip (OG trade.c: 4)
        uint16_t room_capacity; // storage room capacity (OG 400)
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        // Cargo already sold to the ship (export); never handed back to it as import cargo.
        bool export_cargo;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void on_destroy() override;
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual short ferry_wait_action() const override { return ACTION_11_DOCKER_WAIT_FOR_FERRY; }
    virtual short ferry_ride_action() const override { return ACTION_10_DOCKER_ON_FERRY; }
    // OG ferry reroute sets action 8, which is the docker's idle state there.
    virtual short ferry_reroute_action() const override { return ACTION_0_DOCKER_IDLING; }

    empire_trader_handle trader();
    empire_city_handle trader_city();

    virtual void set_cart_offset(int direction) const override;

    static int haul_amount();
    static int import_loads(building_storage_yard *warehouse, e_resource resource, int max_amount);

    bool deliver_import_resource(building *dock);
    bool fetch_export_resource(building *dock);
    int try_import_resource(building *b, e_resource resource, empire_city_handle city_id);
    int try_export_resource(building *b, e_resource resource, empire_city_handle city_id);
    building_dest get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &import_resource);
    building_dest get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &export_resource);

private:
    figure_trade_ship *moored_ship();
    void return_home();
    void return_cargo_to_ship();
};
ANK_CONFIG_STRUCT(figure_docker::static_params, load_amount, max_loads, room_capacity)
