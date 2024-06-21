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
#include "scenario/scenario.h"
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

const building_storage *building_granary::storage() const {
    return building_storage_get(base.storage_id);
}

int building_granary::amount(e_resource resource) const {
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

int building_granary::total_stored() const {
    int result = 0;
    for (e_resource r = RESOURCE_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
        result += amount(r);
    }

    return result;
}

int building_granary::space_for() const {
    return data.granary.resource_stored[RESOURCE_NONE];
}

bool building_granary::is_empty_all() const {
    return storage()->empty_all;
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

void city_granaries_calculate_stocks() {
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
            total_stored = warehouse->total_stored();
        } else if (b->type == BUILDING_GRANARY) {
            building_granary *granary = b->dcast_granary();
            total_stored = granary->total_stored();
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

void building_granary_draw_anim(building &b, vec2i point, tile2i tile, color mask, painter &ctx) {

}

void building_granary::on_create(int orientation) {
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
    draw_stores(point, mask, ctx);
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

void building_granary::draw_stores(vec2i point, color color_mask, painter &ctx) {
    int last_spot_filled = 0;
    int resources_id = granary_m.anim["resources"].first_img();
    for (int r = 1; r < 9; r++) {
        if (data.granary.resource_stored[r] > 0) {
            int spots_filled = ceil((float)(data.granary.resource_stored[r] - 199) / (float)400); // number of "spots" occupied by food
            if (spots_filled == 0 && data.granary.resource_stored[r] > 0)
                spots_filled = 1;

            for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
                // draw sprite on each granary "spot"
                vec2i spot_pos = granary_offsets_ph[spot];
                ImageDraw::img_generic(ctx, resources_id + r, point + spot_pos + vec2i{110, -74}, color_mask);
            }

            last_spot_filled += spots_filled;
        }
    }
}
