#pragma once

#include "building/building_type.h"
#include "game/resource.h"
#include "grid/point.h"

class building;

enum class e_delivery_dest_kind : uint8_t {
    none = 0,
    storage_yard,
    granary,
    workshop,
    palace,
    recruiter,
};

enum class e_delivery_path_reason : uint8_t {
    ok = 0,
    no_road,
    no_destination,
    understaffed,
};

struct cartpusher_deliveryman_prediction {
    building_id destination = 0;
    tile2i access_tile;
    e_delivery_dest_kind kind = e_delivery_dest_kind::none;
    int understaffed = 0;
};

// Same priority chain as figure_cartpusher::determine_deliveryman_destination (no figure mutation).
// road_network_id < 0 → use map_road_network_get(from_tile) only (cart parity).
cartpusher_deliveryman_prediction cartpusher_predict_deliveryman_destination(tile2i from_tile,
                                                                             e_resource resource,
                                                                             building &home,
                                                                             int road_network_id = -1);

struct delivery_path_query {
    building_id from = 0;
    e_resource resource = RESOURCE_NONE;
    building_id to = 0;
    e_delivery_dest_kind kind = e_delivery_dest_kind::none;
    e_delivery_path_reason reason = e_delivery_path_reason::no_destination;
    tile2i from_access;
    tile2i to_access;
    bool has_route = false;
    bool from_live_cart = false;
};

bool building_shows_delivery_paths(const building &b);
delivery_path_query building_predict_delivery(const building &b, e_resource r = RESOURCE_NONE);
bool delivery_path_fill_road(delivery_path_query &q, uint8_t *dirs, int *out_len, int max_len);
