#include "building_granary.h"

#include "building/destruction.h"
#include "building/model.h"
#include "building/building_storage_yard.h"
#include "building/count.h"
#include "city/message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city_buildings.h"
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
#include "dev/debug.h"
#include "js/js_game.h"

#include <cmath>
#include <iostream>

const int MAX_GRANARIES = 100;
const int ONE_LOAD = 100;
const int CURSE_LOADS = 16;
const int INFINITE = 10000;
const int FULL_GRANARY = 3200;
const int THREEQUARTERS_GRANARY = 2400;
const int HALF_GRANARY = 1600;
const int QUARTER_GRANARY = 800;

declare_console_command(addchickpeas, game_cheat_add_resource<RESOURCE_CHICKPEAS>);
declare_console_command(addgamemeat, game_cheat_add_resource<RESOURCE_GAMEMEAT>);

buildings::model_t<building_granary> granary_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_granary);
void config_load_building_granary() {
    granary_m.load();
}

struct city_storages_t {
    svector<int, MAX_GRANARIES> granaries;
    svector<int, MAX_GRANARIES> warhouses;

    resource_list total_storage;
};

city_storages_t g_gettable_storages;

int building_granary::amount(e_resource resource) const {
    if (!resource_is_food(resource)) {
        return 0;
    }

    return runtime_data().resource_stored[resource];
}

bool building_granary::is_accepting(e_resource resource) {
    const storage_t* s = storage();
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
    const storage_t* s = storage();
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

int building_granary::is_not_accepting(e_resource resource) {
    return !((is_accepting(resource) || is_getting(resource)));
}

int building_granary::add_resource(e_resource resource, bool is_produced, int amount, bool force) {
    if (!force && !resource_is_food(resource)) {
        return -1;
    }

    auto &d = runtime_data();
    if (d.resource_stored[RESOURCE_NONE] <= 0) {
        return -1; // no space
    }

    if (is_not_accepting(resource)) {
        return -1;
    }

    if (is_produced) {
        city_resource_add_produced_to_granary(amount);
    }

    int deliverable_amount = std::min<int>(d.resource_stored[RESOURCE_NONE], amount);
    d.resource_stored[resource] += deliverable_amount;
    d.resource_stored[RESOURCE_NONE] -= deliverable_amount;
    return amount - deliverable_amount;
}

int building_granary::total_stored() const {
    int result = 0;
    for (e_resource r = RESOURCE_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
        result += amount(r);
    }

    return result;
}

int building_granary::freespace() const {
    return runtime_data().resource_stored[RESOURCE_NONE];
}

int building_granary::remove_resource(e_resource resource, int amount) {
    if (amount <= 0) {
        return 0;
    }

    auto &d = runtime_data();
    int removed = std::min<int>(d.resource_stored[resource], amount);

    city_resource_remove_from_granary(resource, removed);
    d.resource_stored[resource] -= removed;
    d.resource_stored[RESOURCE_NONE] += removed;

    return amount - removed;
}

granary_task_status building_granary::determine_worker_task() {
    int pct_workers = calc_percentage<int>(num_workers(), model_get_building(type())->laborers);
    if (pct_workers < 50) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    if (is_empty_all()) {
        // bring food to another granary
        for (const auto &r: resource_list::foods) {
            if (amount(r.type) > 0)
                return {GRANARY_TASK_EMPTYING, r.type};
        }

        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    if (freespace() <= 0) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE}; // granary full, nothing to get
    }

    for (const auto &r : resource_list::foods) {
        int now = amount(r.type);
        bool can_take = (g_gettable_storages.total_storage[r.type] - now) > ONE_LOAD;
        if (is_getting(r.type) && can_take) {
            return {GRANARY_TASK_GETTING, r.type};
        }
    }

    return {GRANARY_TASK_NONE, RESOURCE_NONE};
}

void city_granaries_calculate_stocks() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Storages Calculate Stocks");

    g_gettable_storages.granaries.clear();
    g_gettable_storages.warhouses.clear();

    g_gettable_storages.total_storage.clear();

    buildings_valid_do([] (building &b) {
        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse) {
            g_gettable_storages.warhouses.push_back(b.id);
            for (const auto &r : resource_list::foods) {
                g_gettable_storages.total_storage[r.type] += warehouse->amount(r.type);
            }
        }

        building_granary *granary = b.dcast_granary();
        if (granary) {
            g_gettable_storages.granaries.push_back(b.id);
            for (const auto &r : resource_list::foods) {
                g_gettable_storages.total_storage[r.type] += granary->is_gettable(RESOURCE_GRAIN)
                                                                ? granary->amount(r.type)
                                                                : 0; 
            }
        }
    }, BUILDING_GRANARY, BUILDING_STORAGE_YARD);
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
            int pct_workers = granary->worker_percentage();
            if (pct_workers < 75) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }

        if (granary->is_not_accepting(resource) || granary->is_empty_all())
            continue;

        if (config_get(CONFIG_GP_CH_DELIVER_ONLY_TO_ACCEPTING_GRANARIES)) {
            if (granary->is_getting(resource))
                continue;
        }

        const auto &d = granary->runtime_data();
        if (d.resource_stored[RESOURCE_NONE] >= ONE_LOAD) {
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

        int pct_workers = granary->worker_percentage();
        if (pct_workers < 100)
            continue;

        if (granary->is_getting(resource) || granary->is_empty_all())
            continue;

        const auto &d = granary->runtime_data();
        if (d.resource_stored[RESOURCE_NONE] > ONE_LOAD) {
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

template<class T>
int better_getting_storage(const T &ids, building_granary *home) {
    int min_dist = INFINITE;
    int min_building_id = 0;

    for (const auto &id: ids) {
        building_storage* dest = building_get(id)->dcast_storage();

        if (!config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD)) {
            if (dest->road_network() != home->road_network()) {
                continue;
            }
        }

        int amount_gettable = 0;
        for (const auto &r : resource_list::foods) {
            if ((home->is_getting(r.type)) && !dest->is_gettable(r.type)) {
                amount_gettable = std::max(dest->amount(r.type), amount_gettable);
            }
        }

        if (amount_gettable > 0) {
            int dist = calc_distance_with_penalty(vec2i(home->tilex() + 1, home->tiley() + 1), vec2i(dest->tilex() + 1, dest->tiley() + 1), 
                                                  home->distance_from_entry(), dest->distance_from_entry());
            if (amount_gettable <= 400) {
                dist *= 2; // penalty for less food
            }

            if (dist < min_dist) {
                min_dist = dist;
                min_building_id = dest->id();
            }
        }
    }

    return min_building_id;
}

granary_getting_result building_granary::find_storage_for_getting() {
    if (is_empty_all()) {
        return {0, tile2i::invalid};
    }

    //if (scenario_property_kingdom_supplies_grain()) {
    //    return {0, tile2i::invalid};
    //}

    bool is_getting = false;
    for (const auto &r : resource_list::foods) {
        is_getting |= this->is_getting(r.type);
    }

    if (!is_getting) {
        return {0, tile2i::invalid};
    }

    int min_building_id = better_getting_storage(g_gettable_storages.granaries, this);
    if (!min_building_id) {
        min_building_id = better_getting_storage(g_gettable_storages.warhouses, this);
    }

    building* better_b = building_get(min_building_id);
    tile2i road_tile = better_b->access_tile();
    return {min_building_id, road_tile};
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
    if (!granary) {
        return;
    }

    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_GRAIN, 0, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_MEAT, 0, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_LETTUCE, 0, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_FIGS, 0, 100, true);
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
        max_building->destroy_by_fire();
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
    runtime_data().resource_stored[RESOURCE_NONE] = capacity_stored();
    base.storage_id = building_storage_create(BUILDING_GRANARY);
}

void building_granary::update_day() {
    building_impl::update_day();
    runtime_data().resource_stored[RESOURCE_NONE] = capacity_stored() - total_stored();
}

void building_granary::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(2);
    iob->bind____skip(2);

    auto &d = runtime_data();
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &d.resource_stored[i]);
    }
}

void building_granary::on_place_checks() {
    construction_warnings warnings;
    const bool has_bazaar = building_count_active(BUILDING_BAZAAR) > 0;

    warnings.add_if(!has_bazaar, "#build_bazaars_to_distribute_food");
}

void building_granary::spawn_figure() {
    check_labor_problem();
    tile2i road = map_get_road_access_tile(tile(), size());
    if (!road.valid()) {
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
    auto cart = smart_cast<figure_storageyard_cart>(f);

    cart->advance_action(FIGURE_ACTION_50_WAREHOUSEMAN_CREATED);
    base.set_figure(0, cart->id());
    cart->set_home(id());
    if (task.status == GRANARY_TASK_GETTING) {
        cart->load_resource(RESOURCE_NONE, 0);
    } else if (task.status == GRANARY_TASK_EMPTYING) {
        cart->load_resource(task.resource, 0);
    }
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

textid building_granary::get_tooltip() const {
    return window_building_get_tooltip_granary_orders();
}

void building_granary::draw_stores(vec2i point, color color_mask, painter &ctx) {
    int last_spot_filled = 0;
    int resources_id = granary_m.anim["resources"].first_img();

    const auto &d = runtime_data();
    for (int r = 1; r < 9; r++) {
        if (d.resource_stored[r] > 0) {
            int spots_filled = ceil((float)(d.resource_stored[r] - 199) / (float)400); // number of "spots" occupied by food
            if (spots_filled == 0 && d.resource_stored[r] > 0)
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
