#include "building_food_mill.h"

#include "building/building_storage_yard.h"
#include "building/construction/build_planner.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figuretype/figure_storageyard_cart.h"
#include "game/game_config.h"
#include "game/resource.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "grid/road_access.h"
#include "js/js_game.h"
#include "building/building_granary.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_food_mill);

// runtime_data is a raw stock array — no JS-exposed scalar props yet.
bvariant building_food_mill::get_property(const xstring &domain, const xstring &name) const {
    return inherited::get_property(domain, name);
}

bool building_food_mill::set_property(const xstring &domain, const xstring &name, const bvariant &value) {
    return inherited::set_property(domain, name, value);
}

namespace {
constexpr int k_size = 3;
constexpr int ONE_LOAD = 100;
constexpr int FULL_ORDER = 3200;
constexpr int THREEQUARTERS_ORDER = 2400;
constexpr int HALF_ORDER = 1600;
constexpr int QUARTER_ORDER = 800;
constexpr int INFINITE = 10000;

int placeholder_tile_image() {
    return image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED);
}

bool is_allowed_getting_source(building &b) {
    return b.type == BUILDING_GRANARY || b.type == BUILDING_STORAGE_YARD || b.type == BUILDING_STORAGE_ROOM;
}
} // namespace

void building_food_mill::on_create(int orientation) {
    runtime_data().resource_stored[RESOURCE_NONE] = (short)current_params().max_capacity_stored;
    base.storage_id = building_storage_create(BUILDING_FOOD_MILL);
}

void building_food_mill::on_place_update_tiles(int orientation, int variant) {
    map_building_tiles_add(id(), tile(), k_size, placeholder_tile_image(), TERRAIN_BUILDING);
}

void building_food_mill::update_graphic() {
    map_building_tiles_add(id(), tile(), k_size, placeholder_tile_image(), TERRAIN_BUILDING);
    building_impl::update_graphic();
}

void building_food_mill::update_day() {
    building_impl::update_day();
    runtime_data().resource_stored[RESOURCE_NONE]
        = (short)std::max(0, (int)current_params().max_capacity_stored - total_stored());
}

void building_food_mill::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &d = runtime_data();
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &d.resource_stored[i]);
    }
}

int building_food_mill::amount(e_resource resource) const {
    if (!resource_is_food(resource) || resource >= RESOURCES_FOODS_MAX) {
        return 0;
    }
    return runtime_data().resource_stored[resource];
}

int building_food_mill::freespace() const {
    return runtime_data().resource_stored[RESOURCE_NONE];
}

int building_food_mill::total_stored() const {
    int result = 0;
    for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
        if (resource_is_food(r)) {
            result += amount(r);
        }
    }
    return result;
}

bool building_food_mill::is_getting(e_resource resource) {
    const storage_t *s = storage();
    if (!s) {
        return false;
    }
    const int stock = amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] == FULL_ORDER)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= THREEQUARTERS_ORDER
            && stock < THREEQUARTERS_ORDER)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= HALF_ORDER
            && stock < HALF_ORDER)
        || (s->resource_state[resource] == STORAGE_STATE_GET && s->resource_max_get[resource] >= QUARTER_ORDER
            && stock < QUARTER_ORDER)) {
        return true;
    }
    return false;
}

bool building_food_mill::is_accepting(e_resource resource) const {
    if (!resource_is_food(resource)) {
        return false;
    }
    const storage_t *s = storage();
    if (!s || is_empty_all()) {
        return false;
    }
    return s->resource_state[resource] == STORAGE_STATE_ACCEPT
        || s->resource_state[resource] == STORAGE_STATE_GET;
}

bool building_food_mill::is_not_accepting(e_resource resource) const {
    return !is_accepting(resource);
}

int building_food_mill::food_variety() const {
    int n = 0;
    for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
        if (resource_is_food(r) && amount(r) > 0) {
            ++n;
        }
    }
    return std::min(n, 4);
}

int building_food_mill::add_resource(e_resource resource, int amount, bool force) {
    if (amount <= 0) {
        return -1;
    }
    if (!force && !resource_is_food(resource)) {
        return -1;
    }
    if (!resource_is_food(resource) || resource >= RESOURCES_FOODS_MAX) {
        return -1;
    }
    if (is_empty_all()) {
        return -1;
    }
    if (!force && is_not_accepting(resource)) {
        return -1;
    }

    auto &d = runtime_data();
    if (d.resource_stored[RESOURCE_NONE] <= 0) {
        return -1;
    }

    const int max_type = current_params().max_per_type > 0 ? current_params().max_per_type : 800;
    const int room_type = std::max(0, max_type - (int)d.resource_stored[resource]);
    const int room_total = std::max(0, (int)d.resource_stored[RESOURCE_NONE]);
    const int deliverable = std::min({amount, room_type, room_total});
    if (deliverable <= 0) {
        return -1;
    }

    d.resource_stored[resource] = (short)(d.resource_stored[resource] + deliverable);
    d.resource_stored[RESOURCE_NONE] = (short)(d.resource_stored[RESOURCE_NONE] - deliverable);
    return amount - deliverable;
}

int building_food_mill::remove_resource(e_resource resource, int amount) {
    if (amount <= 0 || !resource_is_food(resource) || resource >= RESOURCES_FOODS_MAX) {
        return amount;
    }

    auto &d = runtime_data();
    const int removed = std::min<int>(d.resource_stored[resource], amount);
    d.resource_stored[resource] = (short)(d.resource_stored[resource] - removed);
    d.resource_stored[RESOURCE_NONE] = (short)(d.resource_stored[RESOURCE_NONE] + removed);
    if (removed > 0) {
        city_resource_remove_from_granary(resource, removed);
    }
    return amount - removed;
}

granary_task_status building_food_mill::determine_worker_task() {
    const int pct_workers = worker_percentage();
    if (pct_workers < current_params().min_workers_percent_for_tasks) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    if (is_empty_all() || freespace() <= 0) {
        return {GRANARY_TASK_NONE, RESOURCE_NONE};
    }

    for (const auto &r : resource_list::foods) {
        const int now = amount(r.type);
        const bool can_take = uint16_t(g_city.resource.gettable(r.type) - now) > ONE_LOAD;
        if (is_getting(r.type) && can_take) {
            return {GRANARY_TASK_GETTING, r.type};
        }
    }

    return {GRANARY_TASK_NONE, RESOURCE_NONE};
}

int building_food_mill::better_getting_source() {
    int min_dist = INFINITE;
    int min_building_id = 0;

    for (auto &b : city_buildings()) {
        if (!is_allowed_getting_source(b)) {
            continue;
        }

        building_storage *dest = b.dcast_storage();
        if (!dest || !dest->is_valid()) {
            continue;
        }

        if (!game_features::gameplay_change_getting_granaries_go_offroad) {
            if (b.dcast_granary()) {
                if (!building_granary_touches_network(b, road_network())) {
                    continue;
                }
            } else if (dest->road_network() != road_network()) {
                continue;
            }
        }

        int amount_gettable = 0;
        for (const auto &r : resource_list::foods) {
            if (is_getting(r.type) && !dest->is_gettable(r.type)) {
                amount_gettable = std::max(dest->amount(r.type), amount_gettable);
            }
        }

        if (amount_gettable <= 0) {
            continue;
        }

        int dist = calc_distance_with_penalty(vec2i(tilex() + 1, tiley() + 1),
                                              vec2i(dest->tilex() + 1, dest->tiley() + 1), distance_from_entry(),
                                              dest->distance_from_entry());
        if (amount_gettable <= 400) {
            dist *= 2;
        }

        if (dist < min_dist) {
            min_dist = dist;
            min_building_id = dest->id();
        }
    }

    return min_building_id;
}

granary_getting_result building_food_mill::find_storage_for_getting() {
    if (is_empty_all()) {
        return {0, tile2i::invalid};
    }

    bool any_getting = false;
    for (const auto &r : resource_list::foods) {
        any_getting |= is_getting(r.type);
    }
    if (!any_getting) {
        return {0, tile2i::invalid};
    }

    const int min_building_id = better_getting_source();
    if (!min_building_id) {
        return {0, tile2i::invalid};
    }

    building *better_b = building_get(min_building_id);
    if (better_b->dcast_granary()) {
        tile2i prefer = base.road_access.valid() ? base.road_access : base.tile;
        tile2i access = building_granary_access_on_network(*better_b, road_network(), prefer);
        return {min_building_id, access.valid() ? access : better_b->access_tile()};
    }
    return {min_building_id, better_b->access_tile()};
}

void building_food_mill::spawn_figure() {
    if (!game_features::gameplay_enhanced_food_mill.to_bool()) {
        return;
    }

    check_labor_problem();
    tile2i road = map_get_road_access_tile(tile(), size());
    if (!road.valid()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    if (has_figure_of_type(0, FIGURE_STORAGEYARD_CART)) {
        return;
    }

    auto task = determine_worker_task();
    if (task.status != GRANARY_TASK_GETTING) {
        return;
    }

    figure *f = figure_create(FIGURE_STORAGEYARD_CART, road, DIR_4_BOTTOM_LEFT);
    auto cart = smart_cast<figure_storageyard_cart>(f);
    cart->advance_action(ACTION_50_WAREHOUSECART_CREATED);
    base.set_figure(0, cart->id());
    cart->set_home(id());
    cart->load_resource(RESOURCE_NONE, 0);
}

void building_food_mill::draw_placeholder(painter &ctx, color color_mask) const {
    const color mask = color_mask ? color_mask : COLOR_MASK_GREEN;
    for (int dy = 0; dy < k_size; dy++) {
        for (int dx = 0; dx < k_size; dx++) {
            tile2i t = tile().shifted(dx, dy);
            vec2i px = g_camera.lookup_tile_to_pixel(t);
            build_planner::draw_flat_tile(ctx, px, mask);
        }
    }

    vec2i label = g_camera.lookup_tile_to_pixel(tile().shifted(1, 1));
    text_draw_centered("MILL", label.x - 40, label.y - 8, 80, FONT_SMALL_PLAIN, COLOR_WHITE);
}

bool building_food_mill::force_draw_flat_tile(painter &ctx, tile2i /*tile*/, vec2i pixel, color mask) {
    const color draw_mask = mask ? mask : COLOR_MASK_GREEN;
    build_planner::draw_flat_tile(ctx, pixel, draw_mask);
    return true;
}

bool building_food_mill::draw_ornaments_and_animations_height(painter &ctx, vec2i /*point*/, tile2i /*tile*/,
                                                             color color_mask) {
    draw_placeholder(ctx, color_mask);
    return true;
}
