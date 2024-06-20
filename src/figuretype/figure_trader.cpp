#include "figure_trader.h"

#include "core/calc.h"
#include "city/trade.h"
#include "empire/empire_map.h"
#include "empire/empire.h"
#include "game/game.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/storage.h"
#include "grid/road_access.h"
#include "graphics/painter.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "figure/trader.h"

void figure_trader::trader_buy(int amounts) {
    base.trader_amount_bought += amounts;
}

void figure_trader::trader_sell(int amounts) {
    base.resource_amount_full += amounts;
    //    resource_amount_loads += amounts / 100;
}

bool figure_trader::can_buy(building* warehouse, int city_id) {
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return false;

    if (base.trader_total_bought() >= 800)
        return false;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, warehouse))
        return false;

    building* space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && space->stored_full_amount >= 100
            && empire_can_export_resource_to_city(city_id, space->subtype.warehouse_resource_id)) {
            return true;
        }
    }
    return false;
}

bool figure_trader::can_sell(building* b, int city_id) {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    if (base.trader_total_sold() >= 800) {
        return false;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_TRADERS)) {
        return false;
    }

    auto* storage = warehouse->storage();
    if (storage->empty_all)
        return false;

    int num_importable = 0;
    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
        if (!warehouse->is_not_accepting(r)) {
            if (empire_can_import_resource_from_city(city_id, r))
                num_importable++;
        }
    }

    if (num_importable <= 0)
        return false;

    int can_import = 0;
    e_resource resource = city_trade_current_caravan_import_resource();
    if (!warehouse->is_not_accepting(resource) && empire_can_import_resource_from_city(city_id, resource)) {
        can_import = 1;
    } else {
        for (int i = RESOURCE_MIN; i < RESOURCES_MAX; i++) {
            resource = city_trade_next_caravan_import_resource();
            if (!warehouse->is_not_accepting(resource) && empire_can_import_resource_from_city(city_id, resource)) {
                can_import = 1;
                break;
            }
        }
    }

    if (can_import) {
        // at least one resource can be imported and accepted by this warehouse
        // check if warehouse can store any importable goods
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_full_amount < 400) {
                if (!space->base.stored_full_amount) {
                    // empty space
                    return true;
                }

                if (empire_can_import_resource_from_city(city_id, space->base.subtype.warehouse_resource_id))
                    return true;
            }
            space = space->next_room();
        }
    }
    return false;
}

int figure_trader::get_closest_storageyard(tile2i tile, int city_id, int distance_from_entry, tile2i &warehouse) {
    bool exportable[RESOURCES_MAX];
    bool importable[RESOURCES_MAX];
    exportable[RESOURCE_NONE] = false;
    importable[RESOURCE_NONE] = false;

    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
        exportable[r] = empire_can_export_resource_to_city(city_id, r);
        if (base.trader_amount_bought >= 800) {
            exportable[r] = false;
        }

        if (city_id) {
            importable[r] = empire_can_import_resource_from_city(city_id, r);
        } else { // exclude own city (id=0), shouldn't happen, but still..
            importable[r] = false;
        }

        if (base.get_carrying_amount() >= 800) {
            importable[r] = false;
        }
    }

    int num_importable = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        num_importable += importable[r] ? 1 : 0;
    }

    int min_distance = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_yard* warehouse = building_get(i)->dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid()) {
            continue;
        }

        if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
            continue;
        }

        if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_TRADERS)) {
            continue;
        }

        const building_storage* s = warehouse->storage();
        int num_imports_for_warehouse = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1)) {
            if (!warehouse->is_not_accepting(r) && empire_can_import_resource_from_city(city_id, r)) {
                num_imports_for_warehouse++;
            }
        }
        int distance_penalty = 32;
        building_storage_room* space = warehouse->room();
        while (space) {
            if (exportable[space->base.subtype.warehouse_resource_id])
                distance_penalty -= 4;

            if (num_importable && num_imports_for_warehouse && !s->empty_all) {
                for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
                    if (!warehouse->is_not_accepting(city_trade_next_caravan_import_resource()))
                        break;
                }

                e_resource resource = city_trade_current_caravan_import_resource();
                if (!warehouse->is_not_accepting(resource)) {
                    if (space->base.subtype.warehouse_resource_id == RESOURCE_NONE)
                        distance_penalty -= 16;

                    if (importable[space->base.subtype.warehouse_resource_id] && space->stored_full_amount < 400
                        && space->base.subtype.warehouse_resource_id == resource) {
                        distance_penalty -= 8;
                    }
                }
            }
            space = space->next_room();
        }

        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(warehouse->tile(), tile, distance_from_entry, warehouse->base.distance_from_entry);
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building = &warehouse->base;
            }
        }
    }

    if (!min_building)
        return 0;

    if (min_building->has_road_access == 1) {
        map_point_store_result(min_building->tile, warehouse);
    } else if (!map_get_road_access_tile(min_building->tile, 3, warehouse)) {
        return 0;
    }

    return min_building->id;
}

void figure_trader::draw_trader(object_info* c) {
    painter ctx = game.painter();
    figure* f = &base;
    const empire_city* city = g_empire.city(f->empire_city_id);
    int width = lang_text_draw(64, f->type, c->offset.x + 40, c->offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw(21, city->name_id, c->offset.x + 40 + width, c->offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);

    width = lang_text_draw(129, 1, c->offset.x + 40, c->offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_amount(8, 10, f->type == FIGURE_TRADE_SHIP ? 1200 : 800, c->offset.x + 40 + width, c->offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);

    int trader_id = f->trader_id;
    if (f->type == FIGURE_TRADE_SHIP) {
        int text_id;
        switch (f->action_state) {
        case FIGURE_ACTION_114_TRADE_SHIP_ANCHORED:
            text_id = 6;
            break;
        case FIGURE_ACTION_112_TRADE_SHIP_MOORED:
            text_id = 7;
            break;
        case FIGURE_ACTION_115_TRADE_SHIP_LEAVING:
            text_id = 8;
            break;
        default:
            text_id = 9;
        break;
        }
        lang_text_draw(129, text_id, c->offset.x + 40, c->offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int text_id;
        switch (f->action_state) {
        case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
            text_id = 12;
            break;
        case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
            text_id = 10;
            break;
        case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
            if (trader_has_traded(trader_id))
                text_id = 11;
            else
                text_id = 13;
            break;
        default:
            text_id = 11;
            break;
        }
        lang_text_draw(129, text_id, c->offset.x + 40, c->offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);
    }

    if (trader_has_traded(trader_id)) {
        // bought
        int y_base = c->offset.y + 180;
        width = lang_text_draw(129, 4, c->offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_bought_resources(trader_id, r)) {
                width += text_draw_number(trader_bought_resources(trader_id, r), '@'," ", c->offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c->offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // sold
        y_base = c->offset.y + 210;
        width = lang_text_draw(129, 5, c->offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_sold_resources(trader_id, r)) {
                width += text_draw_number(trader_sold_resources(trader_id, r), '@', " ", c->offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c->offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    } else { // nothing sold/bought (yet)
             // buying
        int y_base = c->offset.y + 180;
        width = lang_text_draw(129, 2, c->offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (city->buys_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c->offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // selling
        y_base = c->offset.y + 210;
        width = lang_text_draw(129, 3, c->offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->sells_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c->offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    }
}
