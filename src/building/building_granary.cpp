#include "building_granary.h"

#include "building/destruction.h"
#include "building/model.h"
#include "building/storage.h"
#include "building/building_storage_yard.h"
#include "city/message.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/game_environment.h"
#include "grid/routing/routing_terrain.h"
#include "graphics/elements/ui.h"
#include "grid/road_access.h"
#include "config/config.h"
#include "scenario/property.h"
#include "sound/effect.h"
#include "graphics/image_desc.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "figure/figure.h"
#include "game/game.h"
#include "window/building/distribution.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "figuretype/figure_storageyard_cart.h"

#include <cmath>

const int MAX_GRANARIES = 100;
const int ONE_LOAD = 100;
const int UNITS_PER_LOAD = 100;
const int CURSE_LOADS = 16;
const int INFINITE = 10000;
const int FULL_GRANARY = 3200;
const int THREEQUARTERS_GRANARY = 2400;
const int HALF_GRANARY = 1600;
const int QUARTER_GRANARY = 800;

buildings::model_t<building_granary> granary_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_granary);
void config_load_building_granary() {
    granary_m.load();
}

struct non_getting_granaries_t {
    int building_ids[MAX_GRANARIES];
    int num_items;
    int total_storage_wheat;
    int total_storage_vegetables;
    int total_storage_fruit;
    int total_storage_meat;
};

non_getting_granaries_t g_non_getting_granaries;

const building_storage *building_granary::storage() {
    return building_storage_get(base.storage_id);
}

int building_granary::amount(e_resource resource) {
    if (!resource_is_food(resource)) {
        return 0;
    }

    return data.granary.resource_stored[resource];
}

bool building_granary::is_accepting(e_resource resource) {
    const building_storage* s = building_storage_get(base.storage_id);
    int amount = this->amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] == FULL_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= THREEQUARTERS_GRANARY && amount < THREEQUARTERS_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= HALF_GRANARY && amount < HALF_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= QUARTER_GRANARY && amount < QUARTER_GRANARY)) {
        return true;
    } else {
        return false;
    }
}

bool building_granary::is_getting(e_resource resource) {
    const building_storage* s = storage();
    int amount = this->amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] == FULL_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= THREEQUARTERS_GRANARY && amount < THREEQUARTERS_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= HALF_GRANARY && amount < HALF_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= QUARTER_GRANARY && amount < QUARTER_GRANARY)) {
        return true; 
    } else {
        return false;
    }
}

bool building_granary_is_gettable(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->storage_id);
    if (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET)
        return true;
    else
        return false;
}

int building_granary::is_not_accepting(e_resource resource) {
    return !((is_accepting(resource) || is_getting(resource)));
}

int building_granary::add_resource(e_resource resource, int is_produced, int amount) {
    if (!resource_is_food(resource))
        return -1;

    if (data.granary.resource_stored[RESOURCE_NONE] <= 0)
        return -1; // no space

    if (is_not_accepting(resource))
        return -1;

    if (is_produced) {
        city_resource_add_produced_to_granary(ONE_LOAD);
    }

    int deliverable_amount = std::min<int>(data.granary.resource_stored[RESOURCE_NONE], amount);
    data.granary.resource_stored[resource] += deliverable_amount;
    data.granary.resource_stored[RESOURCE_NONE] -= deliverable_amount;
    return amount - deliverable_amount;
}

int building_granary::remove_resource(e_resource resource, int amount) {
    if (amount <= 0)
        return 0;

    int removed;
    if (data.granary.resource_stored[resource] >= amount) {
        removed = amount;
    } else {
        removed = data.granary.resource_stored[resource];
    }
    city_resource_remove_from_granary(resource, removed);
    data.granary.resource_stored[resource] -= removed;
    data.granary.resource_stored[RESOURCE_NONE] += removed;
    return amount - removed;
}

int building_granary::remove_for_getting_deliveryman(building* srcb, building* dstb, e_resource& resource) {
    const building_storage* s_src = building_storage_get(srcb->storage_id);
    const building_storage* s_dst = building_storage_get(dstb->storage_id);

    building_granary *dst = dstb->dcast_granary();
    building_granary *src = srcb->dcast_granary();

    int max_amount = 0;
    e_resource max_resource = RESOURCE_NONE;
    if (dst->is_getting(RESOURCE_GRAIN) && !src->is_gettable(RESOURCE_GRAIN)) {
        if (src->data.granary.resource_stored[RESOURCE_GRAIN] > max_amount) {
            max_amount = src->data.granary.resource_stored[RESOURCE_GRAIN];
            max_resource = RESOURCE_GRAIN;
        }
    }
    if (dst->is_getting(RESOURCE_MEAT) && !src->is_gettable(RESOURCE_MEAT)) {
        if (src->data.granary.resource_stored[RESOURCE_MEAT] > max_amount) {
            max_amount = src->data.granary.resource_stored[RESOURCE_MEAT];
            max_resource = RESOURCE_MEAT;
        }
    }

    if (dst->is_getting(RESOURCE_LETTUCE) && !src->is_gettable(RESOURCE_LETTUCE)) {
        if (src->data.granary.resource_stored[RESOURCE_LETTUCE] > max_amount) {
            max_amount = src->data.granary.resource_stored[RESOURCE_LETTUCE];
            max_resource = RESOURCE_LETTUCE;
        }
    }

    if (dst->is_getting(RESOURCE_FIGS) && !src->is_gettable(RESOURCE_FIGS)) {
        if (src->data.granary.resource_stored[RESOURCE_FIGS] > max_amount) {
            max_amount = src->data.granary.resource_stored[RESOURCE_FIGS];
            max_resource = RESOURCE_FIGS;
        }
    }

    if (config_get(CONFIG_GP_CH_GRANARIES_GET_DOUBLE)) {
        if (max_amount > 1600)
            max_amount = 1600;

    } else {
        if (max_amount > 800)
            max_amount = 800;
    }

    if (max_amount > dst->data.granary.resource_stored[RESOURCE_NONE]) {
        max_amount = dst->data.granary.resource_stored[RESOURCE_NONE];
    }

    src->remove_resource(max_resource, max_amount);
    resource = max_resource;

    return max_amount / UNITS_PER_LOAD;
}

bool building_granary::is_gettable(e_resource resource) {
    const building_storage* s = storage();
    return (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET);
}

granary_task_status building_granary::determine_worker_task() {
    int pct_workers = calc_percentage<int>(num_workers(), model_get_building(type())->laborers);
    if (pct_workers < 50) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    const building_storage* s = storage();
    if (s->empty_all) {
        // bring food to another granary
        for (e_resource res = RESOURCE_FOOD_MIN; res < RESOURCES_FOODS_MAX; res = (e_resource)(res + 1)) {
            if (data.granary.resource_stored[res])
                return {GRANARY_TASK_GETTING, res};
        }
        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    if (data.granary.resource_stored[RESOURCE_NONE] <= 0) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE}; // granary full, nothing to get
    }

    if (is_getting(RESOURCE_GRAIN)
        && g_non_getting_granaries.total_storage_wheat > ONE_LOAD) {
        return {GRANARY_TASK_GETTING, RESOURCE_GRAIN};
    }

    if (is_getting(RESOURCE_MEAT)
        && g_non_getting_granaries.total_storage_vegetables > ONE_LOAD) {
        return {GRANARY_TASK_GETTING, RESOURCE_MEAT};
    }

    if (is_getting(RESOURCE_LETTUCE)
        && g_non_getting_granaries.total_storage_fruit > ONE_LOAD) {
        return {GRANARY_TASK_GETTING, RESOURCE_LETTUCE};
    }

    if (is_getting(RESOURCE_FIGS) && g_non_getting_granaries.total_storage_meat > ONE_LOAD) {
        return {GRANARY_TASK_GETTING, RESOURCE_FIGS};
    }

    return {GRANARY_TASK_NONE, RESOURCE_NONE};
}

void building_granaries_calculate_stocks() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Granaries Calculate Stocks");
    g_non_getting_granaries.num_items = 0;
    for (int i = 0; i < MAX_GRANARIES; i++) {
        g_non_getting_granaries.building_ids[i] = 0;
    }

    g_non_getting_granaries.total_storage_wheat = 0;
    g_non_getting_granaries.total_storage_vegetables = 0;
    g_non_getting_granaries.total_storage_fruit = 0;
    g_non_getting_granaries.total_storage_meat = 0;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        const building_storage* s = building_storage_get(b->storage_id);
        int total_non_getting = 0;
        if (!building_granary_is_gettable(RESOURCE_GRAIN, b)) {
            total_non_getting += b->data.granary.resource_stored[RESOURCE_GRAIN];
            g_non_getting_granaries.total_storage_wheat += b->data.granary.resource_stored[RESOURCE_GRAIN];
        }

        if (!building_granary_is_gettable(RESOURCE_MEAT, b)) {
            total_non_getting += b->data.granary.resource_stored[RESOURCE_MEAT];
            g_non_getting_granaries.total_storage_vegetables += b->data.granary.resource_stored[RESOURCE_MEAT];
        }

        if (!building_granary_is_gettable(RESOURCE_LETTUCE, b)) {
            total_non_getting += b->data.granary.resource_stored[RESOURCE_LETTUCE];
            g_non_getting_granaries.total_storage_fruit += b->data.granary.resource_stored[RESOURCE_LETTUCE];
        }

        if (!building_granary_is_gettable(RESOURCE_FIGS, b)) {
            total_non_getting += b->data.granary.resource_stored[RESOURCE_FIGS];
            g_non_getting_granaries.total_storage_meat += b->data.granary.resource_stored[RESOURCE_FIGS];
        }

        if (total_non_getting > MAX_GRANARIES) {
            g_non_getting_granaries.building_ids[g_non_getting_granaries.num_items] = i;
            if (g_non_getting_granaries.num_items < MAX_GRANARIES - 2)
                g_non_getting_granaries.num_items++;
        }
    }
}

int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst) {
    if (scenario_property_kingdom_supplies_grain())
        return 0;

    if (!resource_is_food(resource))
        return 0;

    if (city_resource_is_stockpiled(resource) && !force_on_stockpile) {
        return 0;
    }

    int min_dist = INFINITE;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_granary* granary = building_get(i)->dcast_granary();
        if (!granary || !granary->is_valid())
            continue;

        if (!granary->has_road_access() || granary->distance_from_entry() <= 0 || granary->road_network() != road_network_id)
            continue;

        if (!config_get(CONFIG_GP_CH_UNDERSTAFFED_ACCEPT_GOODS)) {
            int pct_workers = calc_percentage<int>(granary->num_workers(), model_get_building(granary->type())->laborers);
            if (pct_workers < 75) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }
        const building_storage* s = granary->storage();
        if (granary->is_not_accepting(resource) || s->empty_all)
            continue;

        if (config_get(CONFIG_GP_CH_DELIVER_ONLY_TO_ACCEPTING_GRANARIES)) {
            if (granary->is_getting(resource))
                continue;
        }

        if (granary->data.granary.resource_stored[RESOURCE_NONE] >= ONE_LOAD) {
            // there is room
            int dist = calc_distance_with_penalty(vec2i(granary->tilex() + 1, granary->tiley() + 1), tile, distance_from_entry, granary->distance_from_entry());
            if (dist < min_dist) {
                min_dist = dist;
                min_building_id = i;
            }
        }
    }
    // deliver to center of granary
    building* min = building_get(min_building_id);
    tile2i granary_tile = min->tile.shifted(1, 1);
    map_point_store_result(granary_tile, *dst);
    return min_building_id;
}

int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst) {
    if (scenario_property_kingdom_supplies_grain())
        return 0;

    if (!resource_is_food(resource))
        return 0;

    if (city_resource_is_stockpiled(resource))
        return 0;

    int min_dist = INFINITE;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_granary* granary = building_get(i)->dcast_granary();
        if (!granary || !granary->is_valid())
            continue;

        if (!granary->has_road_access() || granary->distance_from_entry() <= 0 || granary->road_network() != road_network_id)
            continue;

        int pct_workers = calc_percentage<int>(granary->num_workers(), model_get_building(granary->type())->laborers);
        if (pct_workers < 100)
            continue;

        const building_storage* s = granary->storage();
        if (granary->is_getting(resource) || s->empty_all)
            continue;

        if (granary->data.granary.resource_stored[RESOURCE_NONE] > ONE_LOAD) {
            // there is room
            int dist = calc_distance_with_penalty(vec2i(granary->tilex() + 1, granary->tiley() + 1), tile, distance_from_entry, granary->distance_from_entry());
            if (dist < min_dist) {
                min_dist = dist;
                min_building_id = i;
            }
        }
    }

    building* min = building_get(min_building_id);
    tile2i storing_tile = min->tile.shifted(1, 1);
    map_point_store_result(storing_tile, *dst);
    return min_building_id;
}

int building_granary::for_getting(tile2i* dst) {
    const building_storage* s_src = storage();
    if (s_src->empty_all)
        return 0;

    if (scenario_property_kingdom_supplies_grain()) {
        return 0;
    }

    int is_getting = 0;
    if (this->is_getting(RESOURCE_GRAIN) || this->is_getting(RESOURCE_MEAT)
        || this->is_getting(RESOURCE_LETTUCE) || this->is_getting(RESOURCE_FIGS)) {
        is_getting = 1;
    }

    if (is_getting <= 0) {
        return 0;
    }

    int min_dist = INFINITE;
    int min_building_id = 0;
    for (int i = 0; i < g_non_getting_granaries.num_items; i++) {
        building_granary* b = building_get(g_non_getting_granaries.building_ids[i])->dcast_granary();
        if (!config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD)) {
            if (b->road_network() != road_network()) {
                continue;
            }
        }
        const building_storage* s = b->storage();
        int amount_gettable = 0;

        if ((this->is_getting(RESOURCE_GRAIN)) && !b->is_gettable(RESOURCE_GRAIN)) {
            amount_gettable += b->data.granary.resource_stored[RESOURCE_GRAIN];
        }
        if ((this->is_getting(RESOURCE_MEAT)) && !b->is_gettable(RESOURCE_MEAT)) {
            amount_gettable += b->data.granary.resource_stored[RESOURCE_MEAT];
        }
        if ((this->is_getting(RESOURCE_LETTUCE)) && !b->is_gettable(RESOURCE_LETTUCE)) {
            amount_gettable += b->data.granary.resource_stored[RESOURCE_LETTUCE];
        }
        if ((this->is_getting(RESOURCE_FIGS)) && !b->is_gettable(RESOURCE_FIGS)) {
            amount_gettable += b->data.granary.resource_stored[RESOURCE_FIGS];
        }
        if (amount_gettable > 0) {
            int dist = calc_distance_with_penalty(vec2i(tilex() + 1, tiley() + 1), vec2i(tilex() + 1, tiley() + 1), distance_from_entry(), b->distance_from_entry());
            if (amount_gettable <= 400)
                dist *= 2; // penalty for less food

            if (dist < min_dist) {
                min_dist = dist;
                min_building_id = b->id();
            }
        }
    }

    building* min = building_get(min_building_id);
    tile2i storing_tile = min->tile.shifted(1, 1);
    map_point_store_result(storing_tile, *dst);
    return min_building_id;
}

void building_granary::bless() {
    int min_stored = INFINITE;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY)
            continue;

        int total_stored = 0;
        for (e_resource r = RESOURCE_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
            total_stored += this->amount(r);
        }

        if (total_stored < min_stored) {
            min_stored = total_stored;
            min_building = b;
        }
    }

    building_granary *granary = min_building->dcast_granary();
    if (granary) {
        for (int n = 0; n < 6; n++) {
            granary->add_resource(RESOURCE_GRAIN, 0, 100);
        }
        for (int n = 0; n < 6; n++) {
            granary->add_resource(RESOURCE_MEAT, 0, 100);
        }
        for (int n = 0; n < 6; n++) {
            granary->add_resource(RESOURCE_LETTUCE, 0, 100);
        }
        for (int n = 0; n < 6; n++) {
            granary->add_resource(RESOURCE_FIGS, 0, 100);
        }
    }
}

void building_granary_storageyard_curse(int big) {
    int max_stored = 0;
    building* max_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        int total_stored = 0;
        if (b->type == BUILDING_STORAGE_YARD) {
            building_storage_yard *warehouse = b->dcast_storage_yard();
            for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
                total_stored += warehouse->amount(r);
            }
        } else if (b->type == BUILDING_GRANARY) {
            building_granary *granary = b->dcast_granary();
            for (e_resource r = RESOURCE_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
                total_stored += granary->amount(r);
            }
            total_stored /= UNITS_PER_LOAD;
        } else {
            continue;
        }
        if (total_stored > max_stored) {
            max_stored = total_stored;
            max_building = b;
        }
    }
    if (!max_building) {
        return;
    }

    if (big) {
        city_message_disable_sound_for_next_message();
        city_message_post(false, MESSAGE_FIRE, max_building->type, max_building->tile.grid_offset());
        building_destroy_by_fire(max_building);
        map_routing_update_land();
    } else {
        if (max_building->type == BUILDING_STORAGE_YARD) {
            building_storageyard_remove_resource_curse(max_building, CURSE_LOADS);
        } else if (max_building->type == BUILDING_GRANARY) {
            building_granary *granary = max_building->dcast_granary();
            int amount = granary->remove_resource(RESOURCE_GRAIN, CURSE_LOADS * UNITS_PER_LOAD);
            amount = granary->remove_resource(RESOURCE_MEAT, amount);
            amount = granary->remove_resource(RESOURCE_LETTUCE, amount);
            granary->remove_resource(RESOURCE_FIGS, amount);
        }
    }
}

static vec2i granary_offsets_ph[] = {
    {0, 0},
    {16, 9},
    {35, 18},
    {51, 26},
    {-16, 7},
    {1, 16},
    {20, 26},
    {37, 35},
};

void set_granary_res_offset(int i, vec2i v) {
    granary_offsets_ph[i] = v;
}

void draw_granary_stores(const building &b, vec2i point, color color_mask, painter &ctx) {
    int last_spot_filled = 0;
    for (int r = 1; r < 9; r++) {
        if (b.data.granary.resource_stored[r] > 0) {
            int spots_filled = ceil((float)(b.data.granary.resource_stored[r] - 199) / (float)400); // number of "spots" occupied by food
            if (spots_filled == 0 && b.data.granary.resource_stored[r] > 0)
                spots_filled = 1;

            for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
                // draw sprite on each granary "spot"
                vec2i spot_pos = granary_offsets_ph[spot];
                ImageDraw::img_generic(ctx, image_group(IMG_GRANARY_RESOURCES) + r, point + spot_pos + vec2i{110, -74}, color_mask);
            }

            last_spot_filled += spots_filled;
        }
    }
}

void building_granary_draw_anim(building &b, vec2i point, tile2i tile, color mask, painter &ctx) {

}

void building_granary::on_create() {
    data.granary.resource_stored[RESOURCE_NONE] = 3200;
    base.storage_id = building_storage_create(BUILDING_GRANARY);
}

void building_granary::spawn_figure() {
    check_labor_problem();
    map_point road;
    if (!map_get_road_access_tile(tile(), size(), road)) { // map_has_road_access_granary(x, y, &road)
        return;
    }
    
    common_spawn_labor_seeker(100);
    if (has_figure_of_type(0, FIGURE_STORAGEYARD_CART)) {
        return;
    }

    auto task = determine_worker_task();
    if (task.status == GRANARY_TASK_NONE) {
        return;
    }

    figure* f = figure_create(FIGURE_STORAGEYARD_CART, road, DIR_4_BOTTOM_LEFT);
    auto cart = f->dcast_storageyard_cart();

    cart->base.action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
    cart->load_resource(task.resource, 0);
    base.set_figure(0, cart->id());
    cart->set_home(id());
}

bool building_granary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_granary_stores(base, point, mask, ctx);
    int max_workers = model_get_building(BUILDING_GRANARY)->laborers;
    building_draw_normal_anim(ctx, point + vec2i{114, 2}, &base, tile, granary_m.anim["work"], mask);
    if (num_workers() > max_workers / 2) {
        building_draw_normal_anim(ctx, point + vec2i{96, -4}, &base, tile, granary_m.anim["work"], mask);
    }

    return false;
}

std::pair<int, int> building_granary::get_tooltip() const {
    return window_building_get_tooltip_granary_orders();
}

void window_building_draw_granary_orders(object_info* c) {
    c->help_id = 3;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);
    outer_panel_draw(vec2i{c->offset.x, y_offset}, 29, 28 - 15);
    lang_text_draw_centered(98, 6, c->offset.x, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, y_offset + 42, c->width_blocks - 2, 21 - 15);
}

void window_building_draw_granary(object_info* c) {
    auto &data = g_window_building_distribution;
    c->help_id = 3;
    c->go_to_advisor.left_a = ADVISOR_LABOR;
    c->go_to_advisor.left_b = ADVISOR_POPULATION;
    data.building_id = c->building_id;
    window_building_play_sound(c, "wavs/granary.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(98, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    if (!c->has_road_access) {
        window_building_draw_description_at(c, 40, 69, 25);
    } else if (scenario_property_kingdom_supplies_grain()) {
        window_building_draw_description_at(c, 40, 98, 4);
    } else {
        int total_stored = 0;
        for (int i = RESOURCE_FOOD_MIN; i < RESOURCES_FOODS_MAX; i++) {
            total_stored += b->data.granary.resource_stored[i];
        }

        int width = lang_text_draw(98, 2, c->offset.x + 34, c->offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 16, total_stored, c->offset.x + 34 + width, c->offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

        width = lang_text_draw(98, 3, c->offset.x + 220, c->offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 16, b->data.granary.resource_stored[RESOURCE_NONE], c->offset.x + 220 + width, c->offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

        // todo: fetch map available foods?
        int food1 = ALLOWED_FOODS(0);
        int food2 = ALLOWED_FOODS(1);
        int food3 = ALLOWED_FOODS(2);
        int food4 = ALLOWED_FOODS(3);
        painter ctx = game.painter();
        //        resource_image_offset(RESOURCE_FIGS, RESOURCE_IMAGE_ICON);

        int image_id = image_id_resource_icon(0);
        if (food1) { // wheat
            ImageDraw::img_generic(ctx, image_id + food1, c->offset.x + 34, c->offset.y + 68);
            width = text_draw_number(b->data.granary.resource_stored[food1], '@', " ", c->offset.x + 68, c->offset.y + 75, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food1, c->offset.x + 68 + width, c->offset.y + 75, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food2) { // fruit
            ImageDraw::img_generic(ctx, image_id + food2, c->offset.x + 240, c->offset.y + 68);
            width = text_draw_number(b->data.granary.resource_stored[food2], '@', " ", c->offset.x + 274, c->offset.y + 75,FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food2, c->offset.x + 274 + width, c->offset.y + 75, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food3) { // vegetables
            ImageDraw::img_generic(ctx, image_id + food3, c->offset.x + 34, c->offset.y + 92);
            width = text_draw_number(b->data.granary.resource_stored[food3], '@', " ", c->offset.x + 68, c->offset.y + 99, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food3, c->offset.x + 68 + width, c->offset.y + 99, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food4) { // meat/fish
            ImageDraw::img_generic(ctx, image_id + food4, c->offset.x + 240, c->offset.y + 92);
            width = text_draw_number(b->data.granary.resource_stored[food4], '@', " ", c->offset.x + 274, c->offset.y + 99,FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food4, c->offset.x + 274 + width, c->offset.y + 99, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 5);
    window_building_draw_employment(c, 142);
}

void building_granary::window_info_background(object_info &ctx) {
    if (ctx.storage_show_special_orders) {
        window_building_draw_granary_orders(&ctx);
    } else {
        window_building_draw_granary(&ctx);
    }
}

void window_building_draw_granary_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    window_building_draw_granary_orders(c);
    int line_x = c->offset.x + 215;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);

    int storage_id = building_get(c->building_id)->storage_id;
    backup_storage_settings(storage_id);
    const building_storage* storage = building_storage_get(storage_id);
    const resources_list* list = city_resource_get_available_foods();
    painter ctx = game.painter();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;
        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(ctx, image_id, c->offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(c->offset.x + 165, y_offset + 49, data.orders_decrease_arrows.data(), 1, i);
            image_buttons_draw(c->offset.x + 165 + 18, y_offset + 49, data.orders_increase_arrows.data(), 1, i);
        }
    }

    // emptying button
    button_border_draw(c->offset.x + 80, y_offset + 404 - 15 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(98, 8, c->offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(98, 7, c->offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // accept none button
    button_border_draw(c->offset.x + 80, y_offset + 382 - 15 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}

void window_building_draw_granary_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    draw_permissions_buttons(c->offset.x + 58, c->offset.y + 19 * c->height_blocks - 82, 1);
}

void building_granary::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders) {
        window_building_draw_granary_orders_foreground(&ctx);
    } else {
        window_building_draw_granary_foreground(&ctx);
    }
}

int building_granary::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return window_building_handle_mouse_granary_orders(m, &c);
    } else {
        return window_building_handle_mouse_granary(m, &c);
    }
}
