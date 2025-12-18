#include "building_storage_room.h"

#include "building/building_storage_yard.h"
#include "game/game_events.h"
#include "graphics/image.h"
#include "grid/image.h"
#include "core/calc.h"
#include "city/city_resource.h"
#include "empire/trade_prices.h"
#include "city/city_finance.h"
#include "core/log.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_storage_room);

void building_storage_room::on_create(int orientation) {
}

void building_storage_room::update_image() {
    set_image(base.stored_first().type);
}

void building_storage_room::take_resource(int amount) {
    e_resource& resource = base.stored_first().type;
    consume_resource(resource, amount);
    if (stored_amount(resource) <= 0) {
        resource = RESOURCE_NONE;
    }
    update_image();
}

const storage_t *building_storage_room::storage() {
    return building_storage_get(base.storage_id);
}

void building_storage_room::set_image(e_resource resource) {
    int image_id;
    if (base.stored_first().value <= 0) {
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY);
    } else {
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_FILLED) + 4 * (resource - 1)
                    + resource_image_offset(resource, RESOURCE_IMAGE_STORAGE)
                    + (int)ceil((float)base.stored_first().value / 100.0f) - 1;
    }
    map_image_set(tile(), image_id);
}

void building_storage_room::add_import(e_resource resource) {
    store_resource(resource, 100);

    uint32_t price = trade_price_buy(resource);
    events::emit(event_stats_append_resource{ resource, 100 });
    events::emit(event_finance_request{ efinance_request_import, price });

    set_image(resource);
}

void building_storage_room::remove_export(e_resource resource) {
    consume_resource(resource, 100);
    if (base.stored_first().value <= 0) {
        base.stored_first().type = RESOURCE_NONE;
    }

    uint32_t price = trade_price_sell(resource);
    events::emit(event_stats_remove_resource{ resource, 100 });
    events::emit(event_finance_request{ efinance_request_export, price });

    set_image(base.stored_first().type);
}

int building_storage_room::distance_with_penalty(tile2i src, e_resource r, int distance_from_entry) {
    building_storage_yard* warehouse = yard();

    // check storage settings first
    if (warehouse->is_not_accepting(r)) {
        return 10000;
    }

    // check for spaces that already has some of the resource, first
    if (resource() == r && base.stored_first().value < 400) {
        return calc_distance_with_penalty(tile(), src, distance_from_entry, base.distance_from_entry);
    }

    // second pass, return the first
    if (resource() == RESOURCE_NONE) { // empty warehouse space
        return calc_distance_with_penalty(tile(), src, distance_from_entry, base.distance_from_entry);
    }

    return 10000;
}