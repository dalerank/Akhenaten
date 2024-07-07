#include "building_storage_room.h"

#include "building/building_storage_yard.h"
#include "building/storage.h"

#include "graphics/image.h"
#include "grid/image.h"
#include "core/calc.h"
#include "city/city_resource.h"
#include "empire/trade_prices.h"
#include "city/finance.h"
#include "core/log.h"

buildings::model_t<building_storage_room> storage_room_m;

inline building_storage_room::building_storage_room(building &b) : building_impl(b), stored_full_amount(b.stored_full_amount) {
}

void building_storage_room::on_create(int orientation) {
}

void building_storage_room::window_info_background(object_info &ctx) {
    yard()->window_info_background(ctx);
}

void building_storage_room::window_info_foreground(object_info &ctx) {
    yard()->window_info_foreground(ctx);
}

const building_storage *building_storage_room::storage() {
    return building_storage_get(base.storage_id);
}

void building_storage_room::set_image(e_resource resource) {
    int image_id;
    if (base.stored_full_amount <= 0) {
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

int building_storage_room::accepting_amount(e_resource resource) {
    return get_storage_accepting_amount(&base, resource);
}

bool building_storage_room::is_this_space_the_best(tile2i tile, e_resource resource, int distance_from_entry) {
    building_storage_yard* warehouse = yard();

    // check storage settings first
    if (warehouse->is_not_accepting(resource)) {
        return 0;
    }

    // check for spaces that already has some of the resource, first
    building_storage_room *check = warehouse->room();
    while (check) {
        if (check->base.subtype.warehouse_resource_id == resource && check->base.stored_full_amount < 400) {
            if (check == this)
                return calc_distance_with_penalty(this->tile(), tile, distance_from_entry, this->base.distance_from_entry);
            else
                return false;
        }
        check = check->next_room();
    }

    // second pass, return the first
    check = warehouse->room();
    while (check) {
        if (check->base.subtype.warehouse_resource_id == RESOURCE_NONE) { // empty warehouse space
            if (check == this) {
                return calc_distance_with_penalty(this->tile(), tile, distance_from_entry, this->base.distance_from_entry);
            } else {
                return false;
            }
        }
        check = check->next_room();
    }
    return 0;
}