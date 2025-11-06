#include "building_storage_yard.h"

#include "building/building_barracks.h"
#include "building/building_storage_room.h"
#include "building/building_granary.h"
#include "building/building_scribal_school.h"
#include "building/building_senet_house.h"
#include "city/city_industry.h"
#include "building/rotation.h"
#include "building/model.h"
#include "building/monuments.h"
#include "city/buildings.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "city/city_resource.h"
#include "city/city_labor.h"
#include "core/calc.h"
#include "core/vec2i.h"
#include "empire/trade_prices.h"
#include "game/tutorial.h"
#include "game/game.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/image_groups.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "figure/figure.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"
#include "game/game_config.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "figuretype/figure_storageyard_cart.h"
#include "construction/build_planner.h"
#include "figuretype/figure_sled.h"
#include "js/js_game.h"
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_storage_yard);

void building_storage_yard::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    planer.set_tiles_building(params.base_img(), 3);
}

int building_storage_yard::preview::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    planer.mark_construction(end, { 3, 3 }, TERRAIN_ALL, false);
    return 1;
}

void building_storage_yard::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    int global_rotation = building_rotation_global_rotation();
    int index_rotation = building_rotation_get_storage_fort_orientation(global_rotation);
    int corner = building_rotation_get_corner(index_rotation);
    vec2i corner_offset{ -5, -45 };
    vec2i place_offset{ 0, 0 };

    int image_id_hut = params.base_img();
    int image_id_space = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY);
    for (int i = 0; i < 9; i++) {
        if (i == corner) {
            planer.draw_building_ghost(ctx, image_id_hut, pixel + VIEW_OFFSETS[i]);
            ImageDraw::img_generic(ctx, image_id_hut + 17, pixel.x + VIEW_OFFSETS[i].x + corner_offset.x, pixel.y + VIEW_OFFSETS[i].y + corner_offset.y, COLOR_MASK_GREEN);
        } else {
            planer.draw_building_ghost(ctx, image_id_space, pixel + VIEW_OFFSETS[i] + place_offset);
        }
    }
}

int building_storage_yard::get_space_info() const {
    int total_amounts = 0;
    int empty_spaces = 0;

    const building_storage_room* space = room();
    while (space) {
        if (space->resource()) {
            total_amounts += space->base.stored_amount_first;
        } else {
            empty_spaces++;
        }
        space = space->next_room();
    }

    if (empty_spaces > 0) {
        return STORAGEYARD_ROOM;
    } 
    
    if (total_amounts < 3200) {
        return STORAGEYARD_SOME_ROOM;
    } 
    
    return STORAGEYARD_FULL;
}

int building_storage_yard::amount(e_resource resource) const {
    int total = 0;

    const building_storage_room *space = room();
    while (space) {
        if (space->resource() && space->resource() == resource) {
            total += space->base.stored_amount_first;
        }
        space = space->next_room();
    }
    return total;
}

int building_storage_yard::total_stored() const {
    int total_stored = 0;
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        total_stored += amount(r);
    }

    return total_stored;
}

int building_storage_yard::freespace(e_resource resource) {
    int freespace = 0;
    building_storage_room* space = room();
    while (space) {
        if (!space->resource()) {
            freespace += 400;
        } else if(space->resource() == resource) {
            freespace += (400 - space->base.stored_amount_first);
        }
        space = space->next_room();
    }
    return freespace;
}

int building_storage_yard::freespace() const {
    int freespace = 0;
    const building_storage_room* space = room();
    while (space) {
        if (!space->resource()) {
            freespace += 400;
        }
        space = space->next_room();
    }

    return freespace;
}

int building_storage_yard::add_resource(e_resource resource, int amount, bool force) {
    assert(id() > 0);

    if (!force && is_not_accepting(resource)) {
        return -1;
    }

    // check the initial provided space itself, first
    bool look_for_space = true;
    // repeat until no space left... easier than calculating all amounts by hand.
    int amount_left = amount;
    int amount_last_turn = amount;
    building_storage_room* space = room();
    while (amount_left > 0) {
        if (look_for_space) {
            bool space_found = false;
            while (space) {
                if (!space->resource() || space->resource() == resource) {
                    if (space->base.stored_amount_first < 400) {
                        space_found = true;
                        break;
                    }
                }
                space = space->next_room();
            }

            if (!space_found) {
                return -1; // no space found at all!
            }
        }

        space->runtime_data().resource_id = resource;
        int space_on_tile = 400 - space->base.stored_amount_first;
        int unloading_amount = std::min<int>(space_on_tile, amount_left);
        space->base.stored_amount_first += unloading_amount;
        space_on_tile -= unloading_amount;
        events::emit(event_stats_append_resource{resource, unloading_amount});
        
        if (space_on_tile == 0) {
            look_for_space = true;
        }
        
        space->set_image(resource);
        amount_last_turn = amount_left;
        amount_left -= unloading_amount;

        if (amount_left == amount_last_turn)
            return amount_left;
    }
    return amount_left;
}

int building_storage_yard::remove_resource(e_resource resource, int amount) {
    building_storage_room* space = room();
    while (space) {
        if (amount <= 0) {
            return 0;
        }

        if (space->resource() != resource || space->base.stored_amount_first <= 0) {
            space = space->next_room();
            continue;
        }

        if (space->base.stored_amount_first > amount) {
            events::emit(event_stats_remove_resource{ resource, amount });
            space->base.stored_amount_first -= amount;
            amount = 0;

        } else {
            events::emit(event_stats_remove_resource{ resource, space->base.stored_amount_first });
            amount -= space->base.stored_amount_first;
            space->base.stored_amount_first = 0;
            space->runtime_data().resource_id = RESOURCE_NONE;
        }
        space->set_image(resource);
        space = space->next_room();
    }

    return amount;
}

void building_storage_yard::remove_resource_curse(int amount) {  
    building_storage_room* space = room();
    while(space && amount > 0) {
        if (space->base.stored_amount_first <= 0) {
            continue;
        }

        e_resource resource = space->resource();
        if (space->base.stored_amount_first > amount) {
            events::emit(event_stats_remove_resource{ resource, amount });
            space->base.stored_amount_first -= amount;
            amount = 0;
        } else {
            events::emit(event_stats_remove_resource{ resource, space->base.stored_amount_first });
            amount -= space->base.stored_amount_first;
            space->base.stored_amount_first = 0;
            space->runtime_data().resource_id = RESOURCE_NONE;
        }
        space->set_image(resource);
        space = space->next_room();
    }
}

constexpr int FULL_WAREHOUSE = 3200;
constexpr int THREEQ_WAREHOUSE = 2400;
constexpr int HALF_WAREHOUSE = 1600;
constexpr int QUARTER_WAREHOUSE = 800;

bool building_storage_yard::is_accepting(e_resource resource) {
    const storage_t* s = storage();

    int amount = this->amount(resource);
    bool accepting = (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT);
    bool fool_storage = (s->resource_max_accept[resource] == FULL_WAREHOUSE);
    bool threeq_storage = (s->resource_max_accept[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE);
    bool half_storage = (s->resource_max_accept[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE);
    bool quart_storage = (s->resource_max_accept[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE);

    return (accepting && (fool_storage || threeq_storage || half_storage || quart_storage));
}

bool building_storage_yard::is_getting(e_resource resource) {
    const storage_t* s = storage();
    int amount = this->amount(resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] == FULL_WAREHOUSE) 
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE / 100)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE / 100)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE / 100)) {
        return true;
    } else {
        return false;
    }
}

bool building_storage_yard::is_not_accepting(e_resource resource) {
    return !((is_accepting(resource) || is_getting(resource)));
}

bool building_storage_yard::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    const auto &cover = anim("cover");
    auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
    command.image_id = cover.first_img();
    command.pixel = point + cover.pos;
    command.mask = color_mask;

    return true;
}

building_id building_storage_yard_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int* understaffed, tile2i &dst) {
    int min_dist = 10000;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_room* room = building_get(i)->dcast_storage_room();
        if (!room || !room->is_valid()) {
            continue;
        }

        if (!room->has_road_access() || room->base.distance_from_entry <= 0 || room->road_network() != road_network_id)
            continue;

        building_storage_yard* warehouse = room->yard();
        if (warehouse->is_not_accepting(resource) || warehouse->is_empty_all()) {
            continue;
        }

        if (!game_features::gameplay_change_understaffed_accept_goods) {
            int pct_workers = warehouse->pct_workers();
            if (pct_workers < 100) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }

        int dist = room->distance_with_penalty(tile, resource, distance_from_entry);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            min_building_id = i;
        }
    }

    // abuse null building space
    building* b = building_get(min_building_id)->main();
    if (b->has_road_access == 1) {
        map_point_store_result(b->tile, dst);
    } else {
        dst = map_has_road_access_rotation(b->orientation, b->tile, 3);
        if (!dst.valid()) {
            return 0;
        }
    }

    return min_building_id;
}

int building_storage_yard::for_getting(e_resource resource, tile2i* dst) {
    int min_dist = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_yard *other_warehouse = building_get(i)->dcast_storage_yard();
        if (!other_warehouse || !other_warehouse->is_valid()) {
            continue;
        }

        if (i == id()) {
            continue;
        }

        int amounts_stored = 0;
        building_storage_room* space = other_warehouse->room();
        const storage_t* s = space->storage();
        while (space) {
            if (space->base.stored_amount_first > 0) {
                if (space->resource() == resource)
                    amounts_stored += space->base.stored_amount_first;
            }
            space = space->next_room();
        }

        if (amounts_stored > 0 && !other_warehouse->is_gettable(resource)) {
            int dist = calc_distance_with_penalty(other_warehouse->tile(), tile(), base.distance_from_entry, other_warehouse->base.distance_from_entry);
            dist -= 4 * (amounts_stored / 100);
            if (dist < min_dist) {
                min_dist = dist;
                min_building = &other_warehouse->base;
            }
        }
    }
    if (min_building) {
        if (dst) {
            map_point_store_result(min_building->road_access, *dst);
        }
        return min_building->id;
    } else
        return 0;
}

static bool determine_granary_accept_foods(resource_list &foods, int road_network) {
    if (g_scenario.kingdom_supplies_grain) {
        return false;
    }

    foods.clear();
    buildings_valid_do([&] (building &b) {
        building_granary *granary = b.dcast_granary();
        assert(granary);
        if (!granary->has_road_access()) {
            return;
        }

        if (road_network != granary->road_network()) {
            return;
        }

        int pct_workers = granary->pct_workers();
        if (pct_workers < 100 || granary->amount(RESOURCE_NONE) < 1200) {
            return;
        }

        if (granary->is_empty_all()) {
            return;
        }

        for (const auto &r : resource_list::foods) {
            if (granary->is_accepting(r.type)) {
                foods[r.type] = 1;
            }
        }

    }, BUILDING_GRANARY);

    return foods.any();
}


static bool contains_non_stockpiled_food(building* b, const resource_list &foods) {
    building_storage_room *space = b->dcast_storage_room();
    if (!space) {
        return false;
    }

    if (space->base.stored_amount_first <= 0) {
        return false;
    }

    e_resource resource = space->resource();
    if (g_city.resource.is_stockpiled(resource)) {
        return false;
    }

    if (resource_type_any_of(resource, RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE, RESOURCE_FIGS)) {
        return (foods[resource] > 0);
    }

    return false;
}

storage_worker_task building_storage_yard_determine_getting_up_resources(building* b) {
    building_storage_yard* warehouse = b->dcast_storage_yard();
    for (e_resource check_resource = RESOURCES_MIN; check_resource < RESOURCES_MAX; ++check_resource) {
        if (!warehouse->is_getting(check_resource) || g_city.resource.is_stockpiled(check_resource)) {
            continue;
        }

        int total_stored = 0; // total amounts of resource in warehouse!
        int room = 0;         // total potential room for resource!
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_amount_first <= 0) { // this space (tile) is empty! FREE REAL ESTATE
                room += 4;
            }

            if (space->resource() == check_resource) { // found a space (tile) with resource on it!
                total_stored += space->base.stored_amount_first;   // add loads to total, if any!
                room += 400 - space->base.stored_amount_first;     // add room to total, if any!
            }
            space = space->next_room();
        }

        int requesting = warehouse->accepting_amount(check_resource);
        int lacking = requesting - total_stored;

        // determine if there's enough room for more to accept, depending on "get up to..." settings!
        if (room >= 0 && lacking > 0 && g_city.resource.yards_stored(check_resource) - total_stored > 0) {
            if (!warehouse->for_getting(check_resource, 0)) { // any other place contain this resource..?
                continue;
            }

            // bug in original Pharaoh: warehouses send out two cartpushers even if there is no room!
            e_storageyard_task status = lacking > requesting / 2
                                            ? STORAGEYARD_TASK_GETTING_MOAR
                                            : STORAGEYARD_TASK_GETTING;
            return {status, &warehouse->base, lacking, check_resource};
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_weapons(building *b) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    if (g_city.buildings.count_active(BUILDING_RECRUITER) <= 0) {
        return { STORAGEYARD_TASK_NONE };
    }

    const bool need_weapons = (g_city.military.has_infantry_batalions() || !!game_features::gameplay_recruiter_not_need_forts);
    if (!need_weapons) {
        return { STORAGEYARD_TASK_NONE };
    }

    const bool weapons_stockpile = g_city.resource.is_stockpiled(RESOURCE_WEAPONS);
    if (weapons_stockpile) {
        return { STORAGEYARD_TASK_NONE };
    }

    auto result = building_get_asker_for_resource(warehouse->tile(), BUILDING_RECRUITER, RESOURCE_WEAPONS, warehouse->road_network(), warehouse->distance_from_entry());
    building* barracks = building_get(result.building_id);
    int barracks_want = barracks->need_resource_amount(RESOURCE_WEAPONS);

    if (barracks_want > 0 && warehouse->road_network() == barracks->road_network_id) {
        int available = 0;
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_amount_first > 0 && space->resource() == RESOURCE_WEAPONS) {
                available += space->base.stored_amount_first;
            }
            space = space->next_room();
        }

        if (available > 0) {
            int amount = std::min(available, barracks_want);
            return {STORAGEYARD_TASK_DELIVERING, &warehouse->base, amount, RESOURCE_WEAPONS};
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_timber_to_shipyard_school(building * b) {
    if (g_city.buildings.count_active(BUILDING_SHIPWRIGHT) <= 0 || g_city.resource.is_stockpiled(RESOURCE_TIMBER)) {
        return { STORAGEYARD_TASK_NONE };
    }

    auto warehouse = b->dcast_storage_yard();
    auto result = building_get_asker_for_resource(warehouse->tile(), BUILDING_SHIPWRIGHT, RESOURCE_TIMBER, warehouse->road_network(), warehouse->distance_from_entry());
    building *shipyard = building_get(result.building_id);
    int school_want = shipyard->need_resource_amount(RESOURCE_TIMBER);

    if (school_want > 0 && warehouse->road_network() == shipyard->road_network_id) {
        int available = 0;
        auto space = warehouse->room();
        for (int i = 0; i < 8; i++) {
            if (space->base.stored_amount_first > 0 && space->resource() == RESOURCE_TIMBER) {
                available += space->base.stored_amount_first;
            }
            space = space->next_room();
        }

        if (available > 0) {
            int amount = std::min(available, school_want);
            return { STORAGEYARD_TASK_DELIVERING, &warehouse->base, amount, RESOURCE_TIMBER };
        }
    }

    return { STORAGEYARD_TASK_NONE };
}

storage_worker_task building_storageyard_deliver_beer_to_senet_house(building *b) {
    if (g_city.buildings.count_active(BUILDING_SENET_HOUSE) <= 0 || g_city.resource.is_stockpiled(RESOURCE_BEER)) {
        return { STORAGEYARD_TASK_NONE };
    }

    auto warehouse = b->dcast_storage_yard();
    auto result = building_get_asker_for_resource(warehouse->tile(), BUILDING_SENET_HOUSE, RESOURCE_BEER, warehouse->road_network(), warehouse->distance_from_entry());
    auto senet_house = building_get_ex<building_senet_house>(result.building_id);
    if (!senet_house) {
        return { STORAGEYARD_TASK_NONE };
    }

    const int school_want = senet_house->need_resource_amount(RESOURCE_BEER);

    if (school_want > 0 && warehouse->road_network() == senet_house->road_network()) {
        int available = 0;
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_amount_first > 0 && space->resource() == RESOURCE_BEER) {
                available += space->base.stored_amount_first;
            }
            space = space->next_room();
        }

        if (available > 0) {
            int amount = std::min(available, school_want);
            return { STORAGEYARD_TASK_DELIVERING, &warehouse->base, amount, RESOURCE_BEER };
        }
    }

    return { STORAGEYARD_TASK_NONE };
}

storage_worker_task building_storageyard_deliver_papyrus_to_scribal_school(building *b) {
    if (g_city.buildings.count_active(BUILDING_SCRIBAL_SCHOOL) <= 0 || g_city.resource.is_stockpiled(RESOURCE_PAPYRUS)) {
        return { STORAGEYARD_TASK_NONE };
    }

    auto warehouse = b->dcast_storage_yard();
    auto result = building_get_asker_for_resource(warehouse->tile(), BUILDING_SCRIBAL_SCHOOL, RESOURCE_PAPYRUS, warehouse->road_network(), warehouse->distance_from_entry());
    auto scribal_school = building_get_ex<building_scribal_school>(result.building_id);
    if (!scribal_school) {
        return { STORAGEYARD_TASK_NONE };
    }

    const int school_want = scribal_school->need_resource_amount(RESOURCE_PAPYRUS);

    if (school_want > 0 && warehouse->road_network() == scribal_school->road_network()) {
        int available = 0;
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_amount_first > 0 && space->resource() == RESOURCE_PAPYRUS) {
                available += space->base.stored_amount_first;
            }
            space = space->next_room();
        }

        if (available > 0) {
            int amount = std::min(available, school_want);
            return {STORAGEYARD_TASK_DELIVERING, &warehouse->base, amount, RESOURCE_PAPYRUS};
        }
    }

    return { STORAGEYARD_TASK_NONE };
}

storage_worker_task building_storageyard_deliver_resource_to_workshop(building *b) {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    auto space = warehouse->room();
    for (; space; space = space->next_room()) {
        if (space->base.stored_amount_first <= 0) {
            continue;
        }

        e_resource check_resource = space->resource();
        if (g_city.resource.is_stockpiled(check_resource)) {
            continue;
        }

        storage_worker_task task = {STORAGEYARD_TASK_NONE};
        buildings_workshop_do([&] (building &b) {
            if (!b.need_resource(space->resource()) || b.need_resource_amount(check_resource) < 100) {
                return;
            }
            task = {STORAGEYARD_TASK_DELIVERING, &space->base, 100, space->resource()};
        });

        if (task.result == STORAGEYARD_TASK_DELIVERING) {
            return task;
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storage_yard::deliver_food_to_gettingup_granary(building *b) {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    resource_list granary_resources;
    if (!g_city.determine_granary_get_foods(granary_resources, warehouse->road_network())) {
        return {STORAGEYARD_TASK_NONE};
    }

    auto space = warehouse->room();
    while (space) {
        if (contains_non_stockpiled_food(&space->base, granary_resources)) {
            // always one load only for granaries?
            return {STORAGEYARD_TASK_DELIVERING, &space->base, 100, space->resource()};
        }
        space = space->next_room();
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_food_to_accepting_granary(building *b) {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    resource_list granary_resources;
    if (determine_granary_accept_foods(granary_resources, warehouse->road_network()) && !g_scenario.kingdom_supplies_grain) {
        auto space = warehouse->room();
        while (space) {
            if (contains_non_stockpiled_food(&space->base, granary_resources)) {
                // always one load only for granaries?
                return {STORAGEYARD_TASK_DELIVERING, &space->base, 100, space->resource()};
            }
            space = space->next_room();
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_to_monuments(building *b) {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    svector<building *, 10> monuments;
    buildings_valid_do([&] (building &b) { 
        auto monument = b.dcast_monument();
        if (!monument) {
            return;
        }

        auto &monumentd = monument->runtime_data();
        if (!monuments.full() && monumentd.phase != MONUMENT_FINISHED) {
            monuments.push_back(&b);
        }
    });

    if (monuments.empty()) {
        return {STORAGEYARD_TASK_NONE};
    }

    auto space = warehouse->room();
    for (; space; space = space->next_room()) {
        int available = space->base.stored_amount_first;
        if (!space->resource() || available <= 0) {
            continue;
        }

        e_resource resource = space->resource();
        if (g_city.resource.is_stockpiled(resource)) {
            continue;
        }

        for (auto monument : monuments) {
            int monuments_want = building_monument_needs_resource(monument, resource);
            if (monuments_want > 0) {
                int amount = std::min(available, monuments_want);
                return {STORAGEYARD_TASK_MONUMENT, &space->base, amount, resource, monument};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storage_yard_deliver_emptying_resources(building *b) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return { STORAGEYARD_TASK_NONE };
    }

    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        if (!warehouse->is_emptying(r)) {
            continue;
        }

        int in_storage = warehouse->amount(r);
        if (in_storage > 0) {
            return {STORAGEYARD_TASK_EMPTYING, nullptr, in_storage, r};
        }
    }

    return { STORAGEYARD_TASK_NONE };
}

storage_worker_task building_storage_yard::determine_worker_task() {
    // check workers - if less than enough, no task will be done today.
    if (pct_workers() < 50) {
        return {STORAGEYARD_TASK_NONE};
    }

    using action_type = decltype(building_storageyard_deliver_weapons);
    action_type *actions[] = {
        &building_storage_yard_determine_getting_up_resources,      // getting up resources
        &building_storageyard_deliver_weapons,                      // deliver weapons to barracks
        &building_storageyard_deliver_resource_to_workshop,         // deliver raw materials to workshops
        &building_storageyard_deliver_papyrus_to_scribal_school,    // deliver papyrus materials to scribal school
        &building_storageyard_deliver_beer_to_senet_house,          // deliver raw materials to workshops
        &building_storageyard_deliver_timber_to_shipyard_school,    // deliver raw materials to workshops
        &building_storage_yard::deliver_food_to_gettingup_granary,  // deliver food to getting granary
        &building_storageyard_deliver_food_to_accepting_granary,    // deliver food to accepting granary
        &building_storage_yard_deliver_emptying_resources,          // emptying resource
        &building_storageyard_deliver_to_monuments,                 // monuments resource
    };

    for (const auto &action : actions) {
        storage_worker_task task = (*action)(&base);
        if (task.result != STORAGEYARD_TASK_NONE) {
            return task;
        }
    }
    
    // move goods to other warehouses
    if (is_empty_all()) {
        auto space = room();
        while (space) {
            if (space->base.stored_amount_first > 0) {
                return {STORAGEYARD_TASK_DELIVERING, &space->base, space->base.stored_amount_first, space->resource()};
            }
            space = space->next_room();
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

void building_storage_yard::on_create(int orientation) {
    base.orientation = building_rotation_global_rotation();

    if (!!game_features::gameplay_change_warehouses_dont_accept) {
        building_storage_accept_none(base.storage_id);
    }
}

building* building_storage_yard::add_storageyard_space(int x, int y, building* prev) {
    building* b = building_create(BUILDING_STORAGE_ROOM, tile2i(x, y), 0);
    game_undo_add_building(b);
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    map_building_tiles_add(b->id, tile2i(x, y), 1, image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY), TERRAIN_BUILDING);
    return b;
}

void building_storage_yard::on_place_update_tiles(int orientation, int variant) {
    tile2i offset[9] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {2, 2}};
    int global_rotation = building_rotation_global_rotation();
    int corner = building_rotation_get_corner(2 * global_rotation);

    base.storage_id = building_storage_create(BUILDING_STORAGE_YARD);
    base.prev_part_building_id = 0;

    tile2i shifted_tile = tile().shifted(offset[corner]);

    int base_image = base_img();
    map_building_tiles_add(id(), shifted_tile, 1, base_image, TERRAIN_BUILDING);

    building* prev = &base;
    for (int i = 0; i < 9; i++) {
        if (i == corner) {
            continue;
        }
        prev = add_storageyard_space(tilex() + offset[i].x(), tiley() + offset[i].y(), prev);
    }

    base.tile = tile().shifted(offset[corner]);
    game_undo_adjust_building(&base);

    prev->next_part_building_id = 0;
}

void building_storage_yard::on_place_checks() {
    construction_warnings warnings;

    const bool has_road_access = map_has_road_access(tile(), 3);
    warnings.add_if(!has_road_access, "#needs_road_access");
}

void building_storage_yard::spawn_figure() {
    base.check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    building *space = &base;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id) {
            space->show_on_problem_overlay = base.show_on_problem_overlay;
        }
    }

    base.common_spawn_labor_seeker(current_params().min_houses_coverage);
    auto task = determine_worker_task();
    if (task.result == STORAGEYARD_TASK_NONE || task.amount <= 0) {
        return;
    }

    if (!base.has_figure(BUILDING_SLOT_SERVICE) && task.result == STORAGEYARD_TASK_MONUMENT) {
        figure *leader = base.create_figure_with_destination(FIGURE_SLED_PULLER, task.dest, FIGURE_ACTION_50_SLED_PULLER_CREATED);
        leader->set_direction_to(task.dest);
        for (int i = 0; i < 5; ++i) {
            figure *follower = base.create_figure_with_destination(FIGURE_SLED_PULLER, task.dest, FIGURE_ACTION_50_SLED_PULLER_CREATED);
            follower->set_direction_to(task.dest);
            follower->wait_ticks = i * 4;
        }

        figure *f = figure_create(FIGURE_SLED, base.tile, 0);
        figure_sled *sled = smart_cast<figure_sled>(f);
        sled->set_destination(task.dest);
        sled->set_direction_to(task.dest);
        sled->load_resource(task.resource, task.amount);
        sled->base.leading_figure_id = leader->id;
        remove_resource(task.resource, task.amount);

    } else if (!base.has_figure(BUILDING_SLOT_SERVICE)) {
        figure* f = figure_create(FIGURE_STORAGEYARD_CART, base.road_access, DIR_4_BOTTOM_LEFT);
        auto cart = smart_cast<figure_storageyard_cart>(f);
        assert(cart);
        if (!cart) {
            f->poof();
            return;
        }

        cart->advance_action(FIGURE_ACTION_50_WAREHOUSEMAN_CREATED);

        switch (task.result) {
        case STORAGEYARD_TASK_GETTING:
        case STORAGEYARD_TASK_GETTING_MOAR:
            cart->load_resource(RESOURCE_NONE, 0);
            cart->base.collecting_item_id = task.resource;
            break;

        case STORAGEYARD_TASK_DELIVERING:
        case STORAGEYARD_TASK_EMPTYING:
            task.amount = std::min<int>(task.amount, 400);
            cart->load_resource(task.resource, task.amount);
            remove_resource(task.resource, task.amount);
            break;

        default:
            assert(false);
        }
        base.set_figure(0, f->id);
        f->set_home(base.id);

    } else if (task.result == STORAGEYARD_TASK_GETTING_MOAR && !base.has_figure_of_type(1, FIGURE_STORAGEYARD_CART)) {
        figure* f = figure_create(FIGURE_STORAGEYARD_CART, base.road_access, DIR_4_BOTTOM_LEFT);
        auto cart = smart_cast<figure_storageyard_cart>(f);
        cart->base.action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;
        cart->load_resource(RESOURCE_NONE, 0);
        cart->base.collecting_item_id = task.resource;

        base.set_figure(1, cart->id());
        cart->set_home(base.id);
    }
}

void building_storage_yard::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;

    set_animation(animkey);
}

building_storage_yard *storage_yard_cast(building *b) {
    auto yard = b->dcast_storage_yard();
    if (yard) {
        return yard;
    }

    auto room = b->dcast_storage_room();
    if (room) {
        return room->yard();
    }

    return nullptr;
}