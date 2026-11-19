#include "empire/trade_route_chunks.h"

#include "io/io_buffer.h"
#include "empire/empire.h"

void trade_routes_limits_chunk::bind_data(io_buffer* iob, size_t version) {
    auto data = g_empire.get_routes();
    for (int route_id = 0; route_id < empire_t::MAX_ROUTES; route_id++) {
        auto& resources = data[route_id].resources;
        for (const auto& r : resource_list::values) {
            resources[r.type].limit /= 100;
            iob->bind(BIND_SIGNATURE_UINT16, &resources[r.type].limit);
            iob->bind(BIND_SIGNATURE_UINT16, &resources[r.type].unk_01);
            resources[r.type].limit *= 100;
        }
        // assert(resources[RESOURCE_NONE].limit ==
        // std::numeric_limits<uint16_t>::max());
    }
}

void trade_routes_traded_chunk::bind_data(io_buffer* iob, size_t version) {
    auto data = g_empire.get_routes();
    for (int route_id = 0; route_id < empire_t::MAX_ROUTES; route_id++) {
        auto& resources = data[route_id].resources;
        for (const auto& r : resource_list::values) {
            resources[r.type].traded /= 100;
            iob->bind(BIND_SIGNATURE_UINT16, &resources[r.type].traded);
            iob->bind(BIND_SIGNATURE_UINT16, &resources[r.type].unk_02);
            resources[r.type].traded *= 100;
        }
        // assert(resources[RESOURCE_NONE].traded ==
        // std::numeric_limits<uint16_t>::max());
    }
}
