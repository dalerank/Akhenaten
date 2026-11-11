#include "building_granary.h"

#include "building/destruction.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city_buildings.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "grid/routing/routing_terrain.h"
#include "graphics/elements/ui.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "game/game_config.h"
#include "scenario/scenario.h"
#include "sound/effect.h"
#include "graphics/image_desc.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "figure/figure.h"
#include "game/game.h"
#include "city/city_labor.h"
#include "figuretype/figure_storageyard_cart.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include <cmath>

const int ONE_LOAD = 100;
const int CURSE_LOADS = 16;
const int INFINITE = 10000;
const int FULL_GRANARY = 3200;
const int THREEQUARTERS_GRANARY = 2400;
const int HALF_GRANARY = 1600;
const int QUARTER_GRANARY = 800;

BUILDING_RUNTIME_DATA_IMPL(building_granary)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_granary);

int building_granary::amount(e_resource resource) const {
    if (!resource_is_food(resource)) {
        return 0;
    }

    if (resource >= RESOURCES_FOODS_MAX) {
        return 0;
    }

    return runtime_data().resource_stored[resource];
}

bool building_granary::is_accepting(e_resource resource) {
    const storage_t* s = storage();
    int amount = this->amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_ACCEPT && s->resource_max_accept[resource] == FULL_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_ACCEPT && s->resource_max_accept[resource] >= THREEQUARTERS_GRANARY && amount < THREEQUARTERS_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_ACCEPT && s->resource_max_accept[resource] >= HALF_GRANARY && amount < HALF_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_ACCEPT && s->resource_max_accept[resource] >= QUARTER_GRANARY && amount < QUARTER_GRANARY)) {
        return true;
    } else {
        return false;
    }
}

bool building_granary::is_getting(e_resource resource) {
    const storage_t* s = storage();
    int amount = this->amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] == FULL_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= THREEQUARTERS_GRANARY && amount < THREEQUARTERS_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= HALF_GRANARY && amount < HALF_GRANARY)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= QUARTER_GRANARY && amount < QUARTER_GRANARY)) {
        return true;
    } else {
        return false;
    }
}

bool building_granary::is_not_accepting(e_resource resource) {
    return !((is_accepting(resource) || is_getting(resource)));
}

int building_granary::add_resource(e_resource resource, int amount, bool force) {
    if (!force && !resource_is_food(resource)) {
        return -1;
    }

    if (is_empty_all()) {
        return -1;
    }

    auto &d = runtime_data();
    if (d.resource_stored[RESOURCE_NONE] <= 0) {
        return -1; // no space
    }

    if (!force && is_not_accepting(resource)) {
        return -1;
    }

    if (resource >= RESOURCES_FOODS_MAX) {
        return -1;
    }

    if (!force && this->amount(resource) <= 0) {
        int types = 0;
        for (const auto &r : resource_list::foods) {
            if (this->amount(r.type) > 0) {
                types++;
            }
        }
        if (types >= current_params().allow_food_types) {
            return -1;
        }
    }

    const int deliverable_amount = std::min<int>(d.resource_stored[RESOURCE_NONE], amount);
    d.resource_stored[resource] += deliverable_amount;
    d.resource_stored[RESOURCE_NONE] -= deliverable_amount;

    events::emit(event_granary_resource_added{ id(), resource, deliverable_amount });

    return amount - deliverable_amount;
}

int building_granary::total_stored() const {
    int result = 0;
    for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
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

    if (resource >= RESOURCES_FOODS_MAX) {
        return 0;
    }

    auto &d = runtime_data();
    const int removed = std::min<int>(d.resource_stored[resource], amount);

    events::emit(event_granary_resource_removed{ id(), resource, removed });

    city_resource_remove_from_granary(resource, removed);
    d.resource_stored[resource] -= removed;
    d.resource_stored[RESOURCE_NONE] += removed;

    return amount - removed;
}

granary_task_status building_granary::determine_worker_task() {
    const int pct_workers = worker_percentage();
    if (pct_workers < current_params().min_workers_percent_for_tasks) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE, 0};
    }

    for (const auto &r : resource_list::foods) {
        if (!is_emptying(r.type)) {
            continue;
        }
        const int in_storage = amount(r.type);
        if (in_storage > 0) {
            return {GRANARY_TASK_EMPTYING, r.type, in_storage};
        }
    }

    if (is_empty_all()) {
        e_resource best_resource = RESOURCE_NONE;
        int max_amount = 0;
        for (const auto &r: resource_list::foods) {
            int resource_amount = amount(r.type);
            if (resource_amount > max_amount) {
                max_amount = resource_amount;
                best_resource = r.type;
            }
        }

        if (best_resource != RESOURCE_NONE && max_amount > 0) {
            return {GRANARY_TASK_EMPTYING, best_resource, max_amount};
        }

        return {GRANARY_TASK_NONE, RESOURCE_NONE, 0};
    }

    if (freespace() <= 0) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE, 0};
    }

    if (pct_workers < current_params().min_workers_percent_for_getting) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE, 0};
    }

    for (const auto &r : resource_list::foods) {
        int now = amount(r.type);
        const int gettable = (int)g_city.resource.gettable(r.type) - now;
        const bool can_take = gettable > ONE_LOAD;
        if (!is_getting(r.type) || !can_take) {
            continue;
        }

        const storage_t *s = storage();
        const int target = s->resource_max_get[r.type] > 0 ? s->resource_max_get[r.type] : FULL_GRANARY;
        const int lacking = std::max(0, target - now);
        const e_granary_task kind = (lacking > target / 2) ? GRANARY_TASK_GETTING_MOAR : GRANARY_TASK_GETTING;
        return {kind, r.type, gettable};
    }

    return {GRANARY_TASK_NONE, RESOURCE_NONE, 0};
}

tile2i building_granary_access_on_network(const building &granary, int road_network_id, tile2i prefer_near) {
    if (road_network_id <= 0 || !granary.has_road_access) {
        return tile2i::invalid;
    }

    const building *main = granary.main();
    if (!main || !main->is_valid()) {
        return tile2i::invalid;
    }

    offsets_array offsets;
    map_grid_adjacent_offsets(main->size, offsets);
    const int base_offset = main->tile.grid_offset();
    const bool use_prefer = prefer_near.valid();

    tile2i best = tile2i::invalid;
    float best_dist = 1e9f;
    for (const auto &tile_delta : offsets) {
        const int grid_offset = base_offset + tile_delta;
        if (!road_tile_valid_access(grid_offset)) {
            continue;
        }
        if (map_road_network_get(grid_offset) != road_network_id) {
            continue;
        }
        tile2i candidate(grid_offset);
        if (!use_prefer) {
            return candidate;
        }
        const float d = candidate.dist(prefer_near);
        if (d < best_dist) {
            best_dist = d;
            best = candidate;
        }
    }
    return best;
}

int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst) {
    if (g_scenario.kingdom_supplies_grain)
        return 0;

    if (!resource_is_food(resource))
        return 0;

    if (g_city.resource.is_stockpiled(resource) && !force_on_stockpile) {
        return 0;
    }

    // Priority order (as in original Pharaoh):
    // 1. First try granaries in "Accept" mode
    // 2. Then try granaries in "Get" mode
    // 3. Always avoid "Empty All" mode

    int min_dist = INFINITE;
    int min_building_id = 0;

    // First pass: look for granaries in "Accept" mode
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_granary* granary = building_get(i)->dcast_granary();
        if (!granary || !granary->is_valid())
            continue;

        if (!granary->has_road_access() || !building_granary_touches_network(granary->base, road_network_id))
            continue;

        if (!game_features::gameplay_change_understaffed_accept_goods) {
            int pct_workers = granary->worker_percentage();
            if (pct_workers < granary->current_params().min_workers_percent_for_accepting) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }

        if (granary->is_empty_all())
            continue;

        // Priority 1: Only "Accept" mode granaries
        if (!granary->is_accepting(resource))
            continue;

        if (!!game_features::gameplay_change_only_deliver_to_accepting_granaries) {
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

    // If found accepting granary, use it
    if (min_building_id != 0) {
        building* min = building_get(min_building_id);
        tile2i access = building_granary_access_on_network(*min, road_network_id, tile);
        map_point_store_result(access.valid() ? access : min->tile.shifted(1, 1), *dst);
        return min_building_id;
    }

    // Second pass: look for granaries in "Get" mode (only if no "Accept" granaries found)
    if (!game_features::gameplay_change_only_deliver_to_accepting_granaries) {
        min_dist = INFINITE;
        min_building_id = 0;

        for (int i = 1; i < MAX_BUILDINGS; i++) {
            building_granary* granary = building_get(i)->dcast_granary();
            if (!granary || !granary->is_valid())
                continue;

            if (!granary->has_road_access() || !building_granary_touches_network(granary->base, road_network_id))
                continue;

            if (!game_features::gameplay_change_understaffed_accept_goods) {
                int pct_workers = granary->worker_percentage();
                if (pct_workers < granary->current_params().min_workers_percent_for_accepting) {
                    if (understaffed)
                        *understaffed += 1;
                    continue;
                }
            }

            // Always avoid "Empty All" mode
            if (granary->is_empty_all())
                continue;

            // Priority 2: Only "Get" mode granaries
            if (!granary->is_getting(resource))
                continue;

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
    }

    if (min_building_id == 0) {
        return 0;
    }
    building* min = building_get(min_building_id);
    tile2i access = building_granary_access_on_network(*min, road_network_id, tile);
    map_point_store_result(access.valid() ? access : min->tile.shifted(1, 1), *dst);
    return min_building_id;
}

int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst) {
    if (g_scenario.kingdom_supplies_grain) {
        return 0;
    }

    if (!resource_is_food(resource))
        return 0;

    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    int min_dist = INFINITE;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_granary* granary = building_get(i)->dcast_granary();
        if (!granary || !granary->is_valid())
            continue;

        if (!granary->has_road_access() || !building_granary_touches_network(granary->base, road_network_id))
            continue;

        int pct_workers = granary->worker_percentage();
        if (pct_workers < granary->current_params().min_workers_percent_for_getting)
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

    if (min_building_id == 0) {
        return 0;
    }
    building* min = building_get(min_building_id);
    tile2i access = building_granary_access_on_network(*min, road_network_id, tile);
    map_point_store_result(access.valid() ? access : min->tile.shifted(1, 1), *dst);
    return min_building_id;
}

template<e_building_type T>
int building_granary::better_getting_storage() {
    int min_dist = INFINITE;
    int min_building_id = 0;

    for (auto &b : city_buildings()) {
        if (b.type != T || b.id == id()) {
            continue;
        }

        building_storage *dest = b.dcast_storage();
        if (!dest || !dest->is_valid()) {
            continue;
        }

        if (!game_features::gameplay_change_getting_granaries_go_offroad) {
            if (dest->road_network() != road_network()) {
                continue;
            }
        }

        int amount_gettable = 0;
        for (const auto &r : resource_list::foods) {
            if (is_getting(r.type) && !dest->is_gettable(r.type)) {
                amount_gettable = std::max(dest->amount(r.type), amount_gettable);
            }
        }

        if (amount_gettable > 0) {
            int dist = calc_distance_with_penalty(vec2i(tilex() + 1, tiley() + 1),
                                                  vec2i(dest->tilex() + 1, dest->tiley() + 1), distance_from_entry(),
                                                  dest->distance_from_entry());
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

    int min_building_id = better_getting_storage<BUILDING_GRANARY>();
    if (!min_building_id) {
        min_building_id = better_getting_storage<BUILDING_STORAGE_YARD>();
    }
    if (!min_building_id) {
        return {0, tile2i::invalid};
    }

    building *better_b = building_get(min_building_id);
    return {min_building_id, better_b->access_tile()};
}

void building_granary::bless() {
    int min_stored = INFINITE;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        building_granary* granary = b->dcast_granary();
        if (!granary || b->state != BUILDING_STATE_VALID)
            continue;

        int total_stored = 0;
        for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
            total_stored += granary->amount(r);
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
        granary->add_resource(RESOURCE_GRAIN, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_MEAT, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_LETTUCE, 100, true);
    }
    for (int n = 0; n < 6; n++) {
        granary->add_resource(RESOURCE_FIGS, 100, true);
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
        } else if (b->dcast_granary()) {
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
        messages::popup("message_fire_in_the_city", max_building->type, max_building->tile.grid_offset());
        max_building->destroy_by_fire();
        map_routing_update_land();
    } else {
        auto warehouse = max_building->dcast_storage_yard();
        if (warehouse) {
            warehouse->remove_resource_curse(CURSE_LOADS);
        } 
        
        auto granary = max_building->dcast_granary();
        if (granary) {
            resource_list resources({ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE, RESOURCE_FIGS });
            granary->remove_resources(resources, CURSE_LOADS * UNITS_PER_LOAD);
        }
    }
}

void building_granary_draw_anim(building &b, vec2i point, tile2i tile, color mask, painter &ctx) {

}

void building_granary::on_create(int orientation) {
    runtime_data().resource_stored[RESOURCE_NONE] = current_params().max_capacty_stored;
    base.storage_id = building_storage_create(BUILDING_GRANARY, base.id);
}

void building_granary::on_post_load() {
    building_impl::on_post_load();
}

void building_granary::update_day() {
    building_impl::update_day();
    runtime_data().resource_stored[RESOURCE_NONE] = current_params().max_capacty_stored - total_stored();
}

void building_granary::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(2);
    iob->bind____skip(2);

    auto &d = runtime_data();
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &d.resource_stored[i]);
    }
}

void building_granary::spawn_figure() {
    check_labor_problem();
    tile2i road = map_get_road_access_tile(tile(), size());
    if (!road.valid()) {
        return;
    }

    // OG: when both carts are out, labor seeker is not dispatched (can lose labor access).
    const bool cart0 = has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_STORAGEYARD_CART);
    const bool cart1 = has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_STORAGEYARD_CART);
    if (!(cart0 && cart1)) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
    }

    auto task = determine_worker_task();
    if (task.status == GRANARY_TASK_NONE) {
        return;
    }

    auto spawn_cart = [&](int slot) {
        figure *f = figure_create(FIGURE_STORAGEYARD_CART, road, DIR_4_BOTTOM_LEFT);
        auto cart = smart_cast<figure_storageyard_cart>(f);
        if (!cart) {
            f->poof();
            return;
        }

        cart->advance_action(ACTION_50_WAREHOUSECART_CREATED);
        base.set_figure(slot, cart->id());
        cart->set_home(id());

        if (task.status == GRANARY_TASK_GETTING || task.status == GRANARY_TASK_GETTING_MOAR) {
            cart->load_resource(RESOURCE_NONE, 0);
            cart->base.collecting_item_id = task.resource;
            cart->base.collecting_item_max = std::min(task.amount, storageyard_cart_getting_load_cap(task.resource));
        } else if (task.status == GRANARY_TASK_EMPTYING) {
            const int haul = std::min<int>(task.amount, 400);
            cart->load_resource(task.resource, haul);
            remove_resource(task.resource, haul);
        }
    };

    if (!cart0) {
        spawn_cart(BUILDING_SLOT_SERVICE);
    } else if (task.status == GRANARY_TASK_GETTING_MOAR && !cart1) {
        spawn_cart(BUILDING_SLOT_CARTPUSHER);
    }
}

void building_granary::update_graphic() {
    if (base.state != BUILDING_STATE_VALID) {
        return;
    }

    const bool is_fancy = g_desirability.get(base.tile) > current_params().fancy_treshold_desirability;
    base.set_flag(e_building_fancy, is_fancy);

    const xstring &animkey = is_fancy ? animkeys().fancy : animkeys().base;
    map_building_tiles_add(base.id, base.tile, base.size, first_img(animkey), TERRAIN_BUILDING);

    building_impl::update_graphic();
}

bool building_granary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_stores(point, mask, ctx);
    building_draw_normal_anim(ctx, point + vec2i{114, 2}, &base, tile, anim("work"), mask);
    if (num_workers() > max_workers() / 2) {
        building_draw_normal_anim(ctx, point + vec2i{96, -4}, &base, tile, anim("work"), mask);
    }

    return false;
}

void building_granary::draw_stores(vec2i point, color color_mask, painter &ctx) {
    int last_spot_filled = 0;
    int resources_id = first_img("resources");

    const auto &d = runtime_data();
    const vec2i begin_spot_pos = current_params().begin_spot_pos;
    const auto &res_image_offsets = current_params().res_image_offsets;
    const int max_spots = (int)res_image_offsets.size();
    for (int r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; r++) {
        if (d.resource_stored[r] <= 0 || last_spot_filled >= max_spots) {
            continue;
        }

        // One roof hole per ~400 units (first hole from 1 unit).
        int spots_filled = (int)ceil((float)(d.resource_stored[r] - 199) / (float)400);
        if (spots_filled <= 0) {
            spots_filled = 1;
        }
        spots_filled = std::min(spots_filled, max_spots - last_spot_filled);

        for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
            vec2i spot_pos = res_image_offsets[spot];
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
            command.image_id = resources_id + (r - RESOURCES_FOOD_MIN);
            command.pixel = point + spot_pos + begin_spot_pos;
            command.mask = color_mask;
        }

        last_spot_filled += spots_filled;
    }
}
