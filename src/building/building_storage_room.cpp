#include "building_storage_room.h"

#include "building/building_storage_yard.h"
#include "graphics/image.h"
#include "grid/image.h"
#include "core/calc.h"
#include "city/city_resource.h"
#include "empire/trade_prices.h"
#include "city/finance.h"
#include "core/log.h"

buildings::model_t<building_storage_room> storage_room_m;

inline building_storage_room::building_storage_room(building &b) : building_impl(b), stored_full_amount(b.stored_amount_first) {
}

void building_storage_room::on_create(int orientation) {
}

void building_storage_room::window_info_background(object_info &ctx) {
    yard()->window_info_background(ctx);
}

void building_storage_room::window_info_foreground(object_info &ctx) {
    yard()->window_info_foreground(ctx);
}

const storage_t *building_storage_room::storage() {
    return building_storage_get(base.storage_id);
}

void building_storage_room::set_image(e_resource resource) {
    int image_id;
    if (base.stored_amount_first <= 0) {
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY);
    } else {
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_FILLED) + 4 * (resource - 1)
                    + resource_image_offset(resource, RESOURCE_IMAGE_STORAGE)
                    + (int)ceil((float)stored_full_amount / 100.0f) - 1;
    }
    map_image_set(tile(), image_id);
}

void building_storage_room::add_import(e_resource resource) {
    city_resource_add_to_storageyard(resource, 100);
    stored_full_amount += 100;
    base.subtype.warehouse_resource_id = resource;

    int price = trade_price_buy(resource);
    city_finance_process_import(price);

    set_image(resource);
}

void building_storage_room::remove_export(e_resource resource) {
    city_resource_remove_from_storageyard(resource, 100);
    stored_full_amount -= 100;
    if (stored_full_amount <= 0) {
        base.subtype.warehouse_resource_id = RESOURCE_NONE;
    }

    int price = trade_price_sell(resource);
    city_finance_process_export(price);

    set_image(resource);
}

int building_storage_room::distance_with_penalty(tile2i src, e_resource resource, int distance_from_entry) {
    building_storage_yard* warehouse = yard();

    // check storage settings first
    if (warehouse->is_not_accepting(resource)) {
        return 10000;
    }

    // check for spaces that already has some of the resource, first
    if (base.subtype.warehouse_resource_id == resource && base.stored_amount_first < 400) {
        return calc_distance_with_penalty(tile(), src, distance_from_entry, base.distance_from_entry);
    }

    // second pass, return the first
    if (base.subtype.warehouse_resource_id == RESOURCE_NONE) { // empty warehouse space
        return calc_distance_with_penalty(tile(), src, distance_from_entry, base.distance_from_entry);
    }

    return 10000;
}