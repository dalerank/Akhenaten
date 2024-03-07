#include "building_bazaar.h"

#include "figure/figure.h"
#include "building/storage.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "graphics/elements/ui.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "scenario/property.h"
#include "grid/desirability.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "graphics/image.h"
#include "window/building/distribution.h"
#include "graphics/graphics.h"
#include "game/game.h"

#include <numeric>

constexpr int Y_FOODS = 90;           // 234
constexpr int Y_GOODS = Y_FOODS + 20; // 174 //274

struct resource_data {
    int building_id;
    int distance;
    int num_buildings;
};

int building_bazaar_get_max_food_stock(building* market) {
    int max_stock = 0;
    if (market->id > 0 && market->type == BUILDING_BAZAAR) {
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            int stock = market->data.market.inventory[i];
            if (stock > max_stock)
                max_stock = stock;
        }
    }
    return max_stock;
}

int building_bazaar_get_max_goods_stock(building* market) {
    int max_stock = 0;
    if (market->id > 0 && market->type == BUILDING_BAZAAR) {
        for (int i = INVENTORY_MIN_GOOD; i < INVENTORY_MAX_GOOD; i++) {
            int stock = market->data.market.inventory[i];
            if (stock > max_stock)
                max_stock = stock;
        }
    }
    return max_stock;
}

static void update_food_resource(resource_data &data, int resource, const building &b, int distance) {
    if (!resource) {
        return;
    }

    if (b.data.granary.resource_stored[resource] > 100) {
        data.num_buildings++;
        if (distance < data.distance) {
            data.distance = distance;
            data.building_id = b.id;
        }
    }
}

static void update_good_resource(resource_data &data, e_resource resource, building &b, int distance) {
    building_storage_yard *warehouse = b.dcast_storage_yard();

    if (!city_resource_is_stockpiled(resource) && warehouse->amount(resource) > 0) {
        data.num_buildings++;

        if (distance < data.distance) {
            data.distance = distance;
            data.building_id = b.id;
        }
    }
}

bool is_good_accepted(int index, building* market) {
    int goods_bit = 1 << index;
    return !(market->subtype.market_goods & goods_bit);
}

void toggle_good_accepted(int index, building* market) {
    int goods_bit = (1 << index);
    market->subtype.market_goods ^= goods_bit;
}

void unaccept_all_goods(building* market) {
    market->subtype.market_goods = 0xFFFF;
}

building *building_bazaar::get_storage_destination() {
    resource_data resources[INVENTORY_MAX];

    for (int i = 0; i < INVENTORY_MAX; i++) {
        resources[i].building_id = 0;
        resources[i].num_buildings = 0;
        resources[i].distance = 40;
    }

    buildings_valid_do([&] (building &b) {
        if (!b.has_road_access || b.distance_from_entry <= 0 || b.road_network_id != base.road_network_id) {
            return;
        }

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_MARKET, &b)) {
            return;
        }

        int distance = calc_maximum_distance(base.tile, b.tile);
        if (distance >= 40) {
            return;
        }

        if (b.type == BUILDING_GRANARY) {
            if (scenario_property_kingdom_supplies_grain()) {
                return;
            }

            // todo: fetch map available foods?
            update_food_resource(resources[0], ALLOWED_FOODS(0), b, distance);
            update_food_resource(resources[1], ALLOWED_FOODS(1), b, distance);
            update_food_resource(resources[2], ALLOWED_FOODS(2), b, distance);
            update_food_resource(resources[3], ALLOWED_FOODS(3), b, distance);

        } else if (b.type == BUILDING_STORAGE_YARD) {
            // goods
            update_good_resource(resources[INVENTORY_GOOD1], RESOURCE_POTTERY, b, distance);
            update_good_resource(resources[INVENTORY_GOOD2], RESOURCE_LUXURY_GOODS, b, distance);
            update_good_resource(resources[INVENTORY_GOOD3], RESOURCE_LINEN, b, distance);
            update_good_resource(resources[INVENTORY_GOOD4], RESOURCE_BEER, b, distance);
        }
    }, BUILDING_GRANARY, BUILDING_STORAGE_YARD);

    // update demands
    if (data.market.pottery_demand)
        data.market.pottery_demand--;
    else
        resources[INVENTORY_GOOD1].num_buildings = 0;

    if (data.market.furniture_demand)
        data.market.furniture_demand--;
    else
        resources[INVENTORY_GOOD2].num_buildings = 0;

    if (data.market.oil_demand)
        data.market.oil_demand--;
    else
        resources[INVENTORY_GOOD3].num_buildings = 0;

    if (data.market.wine_demand)
        data.market.wine_demand--;
    else
        resources[INVENTORY_GOOD4].num_buildings = 0;

    int can_go = 0;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        if (resources[i].num_buildings) {
            can_go = 1;
            break;
        }
    }

    if (!can_go) {
        return building_get(0);
    }

    // prefer food if we don't have it
    if (!data.market.inventory[0] && resources[0].num_buildings && is_good_accepted(0, &base)) {
        data.market.fetch_inventory_id = 0;
        return building_get(resources[0].building_id);

    } else if (!data.market.inventory[1] && resources[1].num_buildings && is_good_accepted(1, &base)) {
        data.market.fetch_inventory_id = 1;
        return building_get(resources[1].building_id);

    } else if (!data.market.inventory[2] && resources[2].num_buildings && is_good_accepted(2, &base)) {
        data.market.fetch_inventory_id = 2;
        return building_get(resources[2].building_id);

    } else if (!data.market.inventory[3] && resources[3].num_buildings && is_good_accepted(3, &base)) {
        data.market.fetch_inventory_id = 3;
        return building_get(resources[3].building_id);
    }

    // then prefer resource if we don't have it
    if (!data.market.inventory[INVENTORY_GOOD1] && resources[INVENTORY_GOOD1].num_buildings && is_good_accepted(INVENTORY_GOOD1, &base)) {
        data.market.fetch_inventory_id = INVENTORY_GOOD1;
        return building_get(resources[INVENTORY_GOOD1].building_id);

    } else if (!data.market.inventory[INVENTORY_GOOD2] && resources[INVENTORY_GOOD2].num_buildings && is_good_accepted(INVENTORY_GOOD2, &base)) {
        data.market.fetch_inventory_id = INVENTORY_GOOD2;
        return building_get(resources[INVENTORY_GOOD2].building_id);

    } else if (!data.market.inventory[INVENTORY_GOOD3] && resources[INVENTORY_GOOD3].num_buildings && is_good_accepted(INVENTORY_GOOD3, &base)) {
        data.market.fetch_inventory_id = INVENTORY_GOOD3;
        return building_get(resources[INVENTORY_GOOD3].building_id);

    } else if (!data.market.inventory[INVENTORY_GOOD4] && resources[INVENTORY_GOOD4].num_buildings && is_good_accepted(INVENTORY_GOOD4, &base)) {
        data.market.fetch_inventory_id = INVENTORY_GOOD4;
        return building_get(resources[INVENTORY_GOOD4].building_id);
    }

    // then prefer smallest stock below 50
    int min_stock = 50;
    int fetch_inventory = -1;
    if (resources[0].num_buildings && data.market.inventory[0] < min_stock && is_good_accepted(0, &base)) {
        min_stock = data.market.inventory[0];
        fetch_inventory = 0;
    }

    if (resources[1].num_buildings && data.market.inventory[1] < min_stock && is_good_accepted(1, &base)) {
        min_stock = data.market.inventory[1];
        fetch_inventory = 1;
    }

    if (resources[2].num_buildings && data.market.inventory[2] < min_stock && is_good_accepted(2, &base)) {
        min_stock = data.market.inventory[2];
        fetch_inventory = 2;
    }

    if (resources[3].num_buildings && data.market.inventory[3] < min_stock && is_good_accepted(3, &base)) {
        min_stock = data.market.inventory[3];
        fetch_inventory = 3;
    }

    if (resources[INVENTORY_GOOD1].num_buildings && data.market.inventory[INVENTORY_GOOD1] < min_stock && is_good_accepted(INVENTORY_GOOD1, &base)) {
        min_stock = data.market.inventory[INVENTORY_GOOD1];
        fetch_inventory = INVENTORY_GOOD1;
    }

    if (resources[INVENTORY_GOOD2].num_buildings && data.market.inventory[INVENTORY_GOOD2] < min_stock && is_good_accepted(INVENTORY_GOOD2, &base)) {
        min_stock = data.market.inventory[INVENTORY_GOOD2];
        fetch_inventory = INVENTORY_GOOD2;
    }

    if (resources[INVENTORY_GOOD3].num_buildings && data.market.inventory[INVENTORY_GOOD3] < min_stock && is_good_accepted(INVENTORY_GOOD3, &base)) {
        min_stock = data.market.inventory[INVENTORY_GOOD3];
        fetch_inventory = INVENTORY_GOOD3;
    }

    if (resources[INVENTORY_GOOD4].num_buildings && data.market.inventory[INVENTORY_GOOD4] < min_stock && is_good_accepted(INVENTORY_GOOD4, &base)) {
        fetch_inventory = INVENTORY_GOOD4;
    }

    if (fetch_inventory == -1) {
        // all items well stocked: pick food below threshold
        if (resources[0].num_buildings && data.market.inventory[0] < 600 && is_good_accepted(0, &base)) {
            fetch_inventory = 0;
        }
        if (resources[1].num_buildings && data.market.inventory[1] < 400 && is_good_accepted(1, &base)) {
            fetch_inventory = 1;
        }
        if (resources[2].num_buildings && data.market.inventory[2] < 400 && is_good_accepted(2, &base)) {
            fetch_inventory = 2;
        }
        if (resources[3].num_buildings && data.market.inventory[3] < 400 && is_good_accepted(3, &base)) {
            fetch_inventory = 3;
        }
    }

    if (fetch_inventory < 0) {
        return building_get(0);
    }

    data.market.fetch_inventory_id = fetch_inventory;
    return building_get(resources[fetch_inventory].building_id);
}

void building_bazaar::update_graphic() {
    if (base.state != BUILDING_STATE_VALID) {
        return;
    }

    e_image_id img_id = (map_desirability_get(base.tile.grid_offset()) <= 30) ? IMG_BAZAAR : IMG_BAZAAR_FANCY;
    map_building_tiles_add(base.id, base.tile, base.size, image_group(img_id), TERRAIN_BUILDING);
}

void building_bazaar::update_day() {
    update_graphic();
}

void building_bazaar::spawn_figure() {
    base.check_labor_problem();

    if (common_spawn_figure_trigger(50)) {
        // market buyer
        int spawn_delay = base.figure_spawn_timer();
        if (!base.has_figure_of_type(1, FIGURE_MARKET_BUYER)) {
            base.figure_spawn_delay++;
            if (base.figure_spawn_delay > spawn_delay) {
                building *dest = get_storage_destination();
                if (dest->id) {
                    base.figure_spawn_delay = 0;
                    figure *f = base.create_figure_with_destination(FIGURE_MARKET_BUYER, dest, FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, BUILDING_SLOT_MARKET_BUYER);
                    f->collecting_item_id = data.market.fetch_inventory_id;
                }
            }
        }

        // market trader
        if (!base.has_figure_of_type(0, FIGURE_MARKET_TRADER)) {
            int bazar_inventory = std::accumulate(data.market.inventory, data.market.inventory + 7, 0);
            if (bazar_inventory > 0) { // do not spawn trader if bazaar is 100% empty!
                base.figure_spawn_delay++;
                if (base.figure_spawn_delay > spawn_delay) {
                    base.figure_spawn_delay = 0;
                    base.create_roaming_figure(FIGURE_MARKET_TRADER);
                    return;
                }
            }
        }
    }
}

int window_building_handle_mouse_market(const mouse* m, object_info &c) {
    auto &data = g_window_building_distribution;
    return generic_buttons_handle_mouse(m, c.offset.x + 80, c.offset.y + 16 * c.height_blocks - 34, data.go_to_orders_button.data(), 1, &data.focus_button_id);
}

int window_building_handle_mouse_market_orders(const mouse* m, object_info &c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    data.resource_focus_button_id = 0;

    // resources
    int num_resources = city_resource_get_available_market_goods()->size;
    data.building_id = c.building_id;
    return generic_buttons_handle_mouse(m, c.offset.x + 205, y_offset + 46, data.orders_resource_buttons.data(), num_resources, &data.resource_focus_button_id);
}

int building_bazaar::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return window_building_handle_mouse_market_orders(m, c);
    }

    return window_building_handle_mouse_market(m, c);
}

void building_bazaar::draw_simple_background(object_info &c) {
    c.help_id = 2;
    window_building_play_sound(&c, "wavs/market.wav");
    {
        ui::begin_widget(c.offset);

        ui::panel({0, 0}, {c.width_blocks, c.height_blocks}, UiFlags_PanelOuter);
        ui::label(97, 0, vec2i{0, 10}, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_LabelCentered, 16 * c.width_blocks);

        ui::panel({16, 136}, {c.width_blocks - 2, 4}, UiFlags_PanelInner);

        int text_id = get_employment_info_text_id(&c, &base, 142, 1);
        draw_employment_details(&c, &base, 142, text_id);
    }
    painter ctx = game.painter();
    e_font font;

    std::pair<int, int> reason = {0, 0};
    if (!c.has_road_access) {
        reason = {69, 25};
    }

    if (base.num_workers <= 0) {
        reason = {97, 2};
    }

    if (reason.first) {
        ui::label(reason.first, reason.second, vec2i{32, 56}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_LabelMultiline, 16 * (c.width_blocks - 4));
        return;
    }

    int image_id = image_id_resource_icon(0);
    if (data.market.inventory[0] || data.market.inventory[1] || data.market.inventory[2]
        || data.market.inventory[3]) {
            {
                //
            }
    } else {
        window_building_draw_description_at(c, 48, 97, 4);
    }

    // food stocks
    // todo: fetch map available foods?
    int food1 = ALLOWED_FOODS(0);
    int food2 = ALLOWED_FOODS(1);
    int food3 = ALLOWED_FOODS(2);
    int food4 = ALLOWED_FOODS(3);

    if (food1) {
        font = is_good_accepted(0, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(ctx, image_id + food1, c.offset + vec2i{32, Y_FOODS});
        text_draw_number(data.market.inventory[0], '@', " ", c.offset.x + 64, c.offset.y + Y_FOODS + 4, font);
    }

    if (food2) {
        font = is_good_accepted(1, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(ctx, image_id + food2, c.offset + vec2i{142, Y_FOODS});
        text_draw_number(data.market.inventory[1], '@', " ", c.offset.x + 174, c.offset.y + Y_FOODS + 4, font);
    }

    if (food3) {
        font = is_good_accepted(2, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(ctx, image_id + food3, c.offset + vec2i{252, Y_FOODS});
        text_draw_number(data.market.inventory[2], '@', " ", c.offset.x + 284, c.offset.y + Y_FOODS + 4, font);
    }

    if (food4) {
        font = is_good_accepted(3, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(ctx, image_id + food4, c.offset + vec2i{362, Y_FOODS});
        text_draw_number(data.market.inventory[3], '@', " ", c.offset.x + 394, c.offset.y + Y_FOODS + 4, font);
    }

    // good stocks
    font = is_good_accepted(INVENTORY_GOOD1, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
    ImageDraw::img_generic(ctx, image_id + INV_RESOURCES[0], c.offset.x + 32, c.offset.y + Y_GOODS);
    text_draw_number(data.market.inventory[INVENTORY_GOOD1], '@', " ", c.offset.x + 64, c.offset.y + Y_GOODS + 4, font);

    font = is_good_accepted(INVENTORY_GOOD2, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
    ImageDraw::img_generic(ctx, image_id + INV_RESOURCES[1], c.offset.x + 142, c.offset.y + Y_GOODS);
    text_draw_number(data.market.inventory[INVENTORY_GOOD2], '@', " ", c.offset.x + 174, c.offset.y + Y_GOODS + 4, font);

    font = is_good_accepted(INVENTORY_GOOD3, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
    ImageDraw::img_generic(ctx, image_id + INV_RESOURCES[2], c.offset.x + 252, c.offset.y + Y_GOODS);
    text_draw_number(data.market.inventory[INVENTORY_GOOD3], '@', " ", c.offset.x + 284, c.offset.y + Y_GOODS + 4, font);

    font = is_good_accepted(INVENTORY_GOOD4, &base) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
    ImageDraw::img_generic(ctx, image_id + INV_RESOURCES[3], c.offset.x + 362, c.offset.y + Y_GOODS);
    text_draw_number(data.market.inventory[INVENTORY_GOOD4], '@', " ", c.offset.x + 394, c.offset.y + Y_GOODS + 4, font);
}

void building_bazaar::draw_orders_background(object_info &c) {
    c.help_id = 2;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28 - 11);
    lang_text_draw_centered(97, 7, c.offset.x, y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c.offset.x + 16, y_offset + 42, c.width_blocks - 2, 21 - 10);
}

void building_bazaar::window_info_background(object_info &c) {
    if (c.storage_show_special_orders)
        draw_orders_background(c);
    else
        draw_simple_background(c);
}

void building_bazaar::draw_orders_foreground(object_info &c) {
    auto &data = g_window_building_distribution;
    draw_orders_background(c);
    int line_x = c.offset.x + 215;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    painter ctx = game.painter();

    building* b = building_get(c.building_id);
    //    backup_storage_settings(storage_id); // TODO: market state backup
    const resources_list* list = city_resource_get_available_market_goods();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;
        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(ctx, image_id, c.offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c.offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i)
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, nullptr, resource, line_x, y_offset + 51 + line_y, is_good_accepted(i, b));
    }

    // accept none button
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    draw_accept_none_button(c->offset.x + 394, y_offset + 404, data.orders_focus_button_id == 1);
    //}
    //    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
    //        button_border_draw(c->offset.x + 80, y_offset + 382 - 10 * 16, 16 * (c->width_blocks - 10), 20,
    //                           data.orders_focus_button_id == 2 ? 1 : 0);
    //        lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 - 10 * 16,
    //                                16 * (c->width_blocks - 10), FONT_NORMAL_BLACK);
    //    }
}

void building_bazaar::draw_simple_foreground(object_info &c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c.offset.x + 80, c.offset.y + 16 * c.height_blocks - 34, 16 * (c.width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c.offset.x + 80, c.offset.y + 16 * c.height_blocks - 30, 16 * (c.width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}

void building_bazaar::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders)
        draw_orders_foreground(ctx);
    else
        draw_simple_foreground(ctx);
}
