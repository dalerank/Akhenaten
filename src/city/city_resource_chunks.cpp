#include "city/city_resource_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_resource_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.space_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.stored_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.trade_status[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.trading_amount[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.mothballed[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.unk_00[i]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.resource.stockpiled[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_supply_months);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.operating);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.food_types_available[i]);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.food_types_eaten[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_needed_per_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.understaffed);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating_with_food);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.luxury_goods_kinds);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.granary_food_stored[i]);
    }
    verify_no_crash(iob->get_offset() == city_resource_chunk::size);
}
