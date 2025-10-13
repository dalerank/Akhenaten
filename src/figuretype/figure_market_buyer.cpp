#include "figure_market_buyer.h"

#include "market.h"
#include "building/building_house.h"
#include "building/building_granary.h"
#include "window/building/figures.h"
#include "core/log.h"
#include "building/building_storage_yard.h"
#include "building/building_bazaar.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "game/game.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_groups.h"
#include "game/game_config.h"
#include "city/city_health.h"
#include "grid/building.h"
#include "city/ratings.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_market_buyer);

void figure_market_buyer::figure_before_action() {
    building* b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(BUILDING_SLOT_MARKET_BUYER, id())) {
        poof();
    }
}

void figure_market_buyer::figure_action() {
    bool ok = false;
    switch (action_state()) {
    case 8:
    case FIGURE_ACTION_144_MARKET_BUYER_CREATE:
        break;

    case FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE:
        ok = do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_146_MARKET_BUYER_RETURNING);
        if (ok) {
            if (base.collecting_item_id > 3) {
                if (!take_resource_from_storageyard(destination())) {
                    advance_action(FIGURE_ACTION_146_MARKET_BUYER_RETURNING);
                }

            } else {
                if (!take_food_from_storage(home(), destination())) {
                    advance_action(FIGURE_ACTION_146_MARKET_BUYER_RETURNING);
                }
            }
        }
        break;

    case 9:
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_146_MARKET_BUYER_RETURNING:
        if (base.do_returnhome()) {
            home()->figure_spawn_delay = -3;
            //logs::info("stop");
        }
        break;
    }
}

sound_key figure_market_buyer::phrase_key() const {
    svector<sound_key, 10> keys;
    if (action_state() == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        keys.push_back("goto_store");
    } else if (action_state() == FIGURE_ACTION_146_MARKET_BUYER_RETURNING) {
        keys.push_back("buyer_back_to_market");
    } 

    if (g_city.health.value < 30) {
        keys.push_back("buyer_city_has_low_health");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("buyer_no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("buyer_city_have_no_army");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("buyer_much_unemployments");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("buyer_gods_are_angry");
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back("buyer_city_is_bad_reputation");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("buyer_too_much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("buyer_low_entertainment");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("buyer_city_is_amazing");
    } else if (sentiment > 50) {
        keys.push_back("buyer_city_is_good");
    }

    int index = rand() % keys.size();
    return keys[index];

}

void distribute_good(building* b, building* market, int stock_wanted, int inventory_resource) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &housed = house->runtime_data();
    int amount_wanted = stock_wanted - housed.inventory[inventory_resource];

    auto &d = bazaar->runtime_data();
    if (d.inventory[inventory_resource] > 0 && amount_wanted > 0) {
        if (amount_wanted <= d.inventory[inventory_resource]) {
            housed.inventory[inventory_resource] += amount_wanted;
            d.inventory[inventory_resource] -= amount_wanted;
        } else {
            housed.inventory[inventory_resource] += d.inventory[inventory_resource];
            d.inventory[inventory_resource] = 0;
        }
    }
}

void distribute_market_resources(building* b, building* market) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &marketd = bazaar->runtime_data();
    auto &housed = house->runtime_data();
    int level = house->house_level();
    if (level < HOUSE_PALATIAL_ESTATE) {
        level++;
    }

    int max_food_stocks = 4 * housed.highest_population;
    int food_types_stored_max = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        if (housed.foods[i] >= max_food_stocks)
            food_types_stored_max++;
    }

    const model_house& model = model_get_house(level);
    if (model.food_types > food_types_stored_max) {
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            if (housed.foods[i] >= max_food_stocks) {
                continue;
            }

            if (marketd.inventory[i] >= max_food_stocks) {
                housed.foods[i] += max_food_stocks;
                marketd.inventory[i] -= max_food_stocks;
                break;
            } else if (marketd.inventory[i]) {
                housed.foods[i] += marketd.inventory[i];
                marketd.inventory[i] = 0;
                break;
            }
        }
    }
    if (model.pottery) {
        marketd.pottery_demand = 10;
        distribute_good(b, market, 8 * model.pottery, INVENTORY_GOOD1);
    }

    int goods_no = 4;
    if (!!game_features::gameplay_houses_stockpile_more) {
        goods_no = 8;
    }

    if (model.jewelry) {
        marketd.luxurygoods_demand = 10;
        distribute_good(b, market, goods_no * model.jewelry, INVENTORY_GOOD2);
    }
    if (model.linen) {
        marketd.linen_demand = 10;
        distribute_good(b, market, goods_no * model.linen, INVENTORY_GOOD3);
    }
    if (model.beer) {
        marketd.beer_demand = 10;
        distribute_good(b, market, goods_no * model.beer, INVENTORY_GOOD4);
    }
}


bool figure_market_buyer::take_resource_from_storageyard(building* b) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    e_resource resource;
    switch (base.collecting_item_id) {
    case INVENTORY_GOOD1: resource = RESOURCE_POTTERY; break;
    case INVENTORY_GOOD2: resource = RESOURCE_LUXURY_GOODS; break;
    case INVENTORY_GOOD3: resource = RESOURCE_LINEN; break;
    case INVENTORY_GOOD4: resource = RESOURCE_BEER; break;

    default:
        return false;
    }

    int stored = warehouse->amount(resource);
    int num_loads = std::min<int>(stored, 200);

    if (num_loads <= 0) {
        return false;
    }

    warehouse->remove_resource(resource, num_loads);

    // create delivery boys
    int boy1 = create_delivery_boy(id());
    if (num_loads > 100) {
        create_delivery_boy(boy1);
    }

    return true;
}

int provide_market_goods(building* market, tile2i tile) {
    int serviced = 0;
    grid_area area = map_grid_get_area(tile, 1, 2);

    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        building_id bid = map_building_at(grid_offset);
        auto house = building_get(bid)->dcast_house();
        if (house && house->house_population() > 0) {
            distribute_market_resources(&house->base, market);
            serviced++;
        }
    });
    return serviced;
}

int figure_market_buyer::create_delivery_boy(int leader_id) {
    figure* boy = figure_create(FIGURE_DELIVERY_BOY, tile(), 0);
    boy->leading_figure_id = leader_id;
    boy->collecting_item_id = base.collecting_item_id;
    boy->set_home(base.homeID());
    return boy->id;
}

int figure_market_buyer::provide_service() {
    int houses_serviced = 0;
    if (!game_features::gameplay_buyers_dont_distribute) {
        houses_serviced = provide_market_goods(home(), tile());
    }

    return houses_serviced;
}

figure_sound_t figure_market_buyer::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

bool figure_market_buyer::window_info_background(object_info &c) {
    painter ctx = game.painter();
    figure *f = c.figure_get();

    const uint16_t big_image = f->anim(animkeys().big_image).first_img();
    ImageDraw::img_generic(ctx, big_image, c.offset + vec2i{28, 112});

    lang_text_draw(254, base.name, c.offset.x + 90, c.offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    int width = lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (action_state() == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        width += lang_text_draw(129, 17, c.offset.x + 90 + width, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(base.collecting_item_id);
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c.offset + vec2i{90 + width, 135});
    } else if (action_state() == FIGURE_ACTION_146_MARKET_BUYER_RETURNING) {
        width += lang_text_draw(129, 18, c.offset.x + 90 + width, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(base.collecting_item_id);
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c.offset + vec2i{90 + width, 135});
    }

    if (c.nfigure.phrase.valid()) {
        lang_text_draw_multiline(c.nfigure.phrase.group, c.nfigure.phrase.id, c.offset + vec2i{90, 160}, 16 * (c.bgsize.x - 8), FONT_NORMAL_BLACK_ON_DARK);
    }

    return true;
}

int figure_market_buyer::take_food_from_storage(building* market, building* b) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }

    e_resource resource;
    switch (base.collecting_item_id) {
    case 0: resource = g_city.allowed_foods(0); break;
    case 1: resource = g_city.allowed_foods(1); break;
    case 2: resource = g_city.allowed_foods(2); break;
    case 3: resource = g_city.allowed_foods(3); break;

    default:
        return 0;
    }

    building_storage *storage = b->dcast_storage();
    if (!storage) {
        return 0;
    }

    int market_units = bazaar->runtime_data().inventory[base.collecting_item_id];
    int storage_units = storage->amount(resource);

    const int max_units = (base.collecting_item_id == 0 ? 700 : 600) - market_units;
    const int max_num_loads = max_units / 100;
    const int num_loads = std::clamp(storage_units / 100, 0, max_num_loads);

    if (num_loads <= 0) {
        return 0;
    }

    storage->remove_resource(resource, 100 * num_loads);

    // create delivery boys
    int previous_boy = id();
    for (int i = 0; i < num_loads; i++) {
        previous_boy = create_delivery_boy(previous_boy);
    }

    return 1;
}
