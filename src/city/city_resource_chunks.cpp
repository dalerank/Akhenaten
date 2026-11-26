#include "city/city_resource_chunks.h"

#include "city/city_resource.h"
#include "io/io_buffer.h"

void city_resource_chunk::bind_data(io_buffer* iob) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &city_resource().space_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &city_resource().stored_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_resource().trade_status[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &city_resource().trading_amount[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_resource().mothballed[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_resource().unk_00[i]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_resource().stockpiled[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().food_supply_months);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().granaries.operating);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &city_resource().food_types_available[i]);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &city_resource().food_types_eaten[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().food_needed_per_month);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().granaries.understaffed);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().granaries.not_operating);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().granaries.not_operating_with_food);
    iob->bind(BIND_SIGNATURE_INT32, &city_resource().luxury_goods_kinds);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &city_resource().granary_food_stored[i]);
    }
    verify_no_crash(iob->get_offset() == city_resource_chunk::size);
}
