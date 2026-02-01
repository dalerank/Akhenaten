#include "building_house.h"

#include "city/city.h"
#include "city/city_warnings.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "core/object_property.h"
#include "core/custom_span.hpp"
#include "city/city_labor.h"
#include "game/resource.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/graphics.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/tiles.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"
#include "js/js_game.h"
#include "widget/widget_city.h"
#include "dev/debug.h"
#include <iostream>

#define MAX_DIR 4

declare_console_command_p(house_up) {
    buildings_house_do([] (building_house *house) {
        e_building_type next_level = (e_building_type)(BUILDING_HOUSE_CRUDE_HUT + house->house_level() + 1);
        house->change_to(house->base, next_level, true);
    });
};

declare_console_command_p(house_down) {
    buildings_house_do([] (building_house *house) {
        e_building_type prev_level = (e_building_type)(BUILDING_HOUSE_CRUDE_HUT + house->house_level() - 1);
        if (prev_level < BUILDING_HOUSE_CRUDE_HUT) {
            prev_level = BUILDING_HOUSE_VACANT_LOT;
        }
        house->change_to(house->base, prev_level, true);
    });
};

declare_console_var_int(house_up_delay, 1000)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_crude_hut)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_sturdy_hut)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_meager_shanty)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_common_shanty)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_rough_cottage)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_ordinary_cottage)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_modest_homestead)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_spacious_homestead)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_modest_apartment)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_spacious_apartment)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_common_residence)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_spacious_residence)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_elegant_residence)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_fancy_residence)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_common_manor)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_spacious_manor)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_elegant_manor)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_stately_manor)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_modest_estate)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_house_palatial_estate)

static const int HOUSE_TILE_OFFSETS_PH[] = {
  GRID_OFFSET(0, 0),
  GRID_OFFSET(1, 0),
  GRID_OFFSET(0, 1),
  GRID_OFFSET(1, 1), // 2x2
  GRID_OFFSET(2, 0),
  GRID_OFFSET(2, 1),
  GRID_OFFSET(2, 2),
  GRID_OFFSET(1, 2),
  GRID_OFFSET(0, 2), // 3x3
  GRID_OFFSET(3, 0),
  GRID_OFFSET(3, 1),
  GRID_OFFSET(3, 2),
  GRID_OFFSET(3, 3),
  GRID_OFFSET(2, 3),
  GRID_OFFSET(1, 3),
  GRID_OFFSET(0, 3) // 4x4
};

struct house_image_t : public image_desc {
    int num_types;
};

struct expand_direction_t {
    int x;
    int y;
    int offset;
};

expand_direction_t expand_direction;

const expand_direction_t EXPAND_DIRECTION_DELTA_PH[MAX_DIR] = {
    {0, 0, 0}, {-1, -1, -GRID_LENGTH - 1}, {-1, 0, -1}, {0, -1, -GRID_LENGTH}
};

struct merge_data_t {
    tile2i tile;
    int inventory[INVENTORY_MAX];
    int foods[INVENTORY_MAX];
    int population;
};

merge_data_t g_merge_data;

int house_tile_offsets(int i) {
    return HOUSE_TILE_OFFSETS_PH[i];
}
expand_direction_t expand_delta(int i) {
    return EXPAND_DIRECTION_DELTA_PH[i];
}

void building_house::on_undo() {
    /*nothing*/
}

void building_house::update_week() {
    building_impl::update_week();
}

void building_house::update_count() const {
    g_city.buildings.increase_count(type(), runtime_data().hsize > 0);
}

void building_house::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    for (int i = 0; i < 4; ++i) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.foods[i]);
    }

    uint16_t tmp;
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind_u16(d.image_id);

    for (int i = 0; i < 4; ++i) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.inventory[i + 4]);
    }

    iob->bind_u8(d.booth_juggler);
    iob->bind_u8(d.bandstand_juggler);
    iob->bind_u8(d.bandstand_musician);
    iob->bind_u8(d.senet_player);
    iob->bind_u8(d.magistrate);
    iob->bind_u8(d.bullfighter);
    iob->bind_u8(d.school);
    iob->bind_u8(d.library);
    iob->bind_u8(d.academy);
    iob->bind_u8(d.apothecary);
    iob->bind_u8(d.dentist);
    iob->bind_u8(d.mortuary);
    iob->bind_u8(d.physician);
    iob->bind_u8(d.temple_osiris);
    iob->bind_u8(d.temple_ra);
    iob->bind_u8(d.temple_ptah);
    iob->bind_u8(d.temple_seth);
    iob->bind_u8(d.temple_bast);
    iob->bind_u8(d.no_space_to_expand);
    iob->bind_u8(d.num_foods);
    iob->bind_u8(d.entertainment);
    iob->bind_u8(d.education);
    iob->bind_u8(d.health);
    iob->bind_u8(d.num_gods);
    iob->bind_u8(d.devolve_delay);
    iob->bind_u8(d.fancy_bazaar_access);
    iob->bind_u8(d.shrine_access);
    iob->bind_u8(d.bazaar_access);
    iob->bind_u8(d.water_supply);
    iob->bind_u8(d.pavillion_dancer);
    iob->bind_u8(d.pavillion_musician);
    iob->bind_u8(d.house_happiness);
    iob->bind_u8(d.is_merged);
    iob->bind_u8(d.criminal_active);
    iob->bind_u16(d.highest_population);
    iob->bind_u16(d.population);
    iob->bind_u8(d.tax_coverage);
    iob->bind_u16((uint16_t&)d.tax_collector_id);
    iob->bind_i16((int16_t &)d.tax_income_or_storage);
    iob->bind_u8(d.days_without_food);
    iob->bind_u8(d.hsize);
    iob->bind_u16(d.unreachable_ticks);
    iob->bind_u16(d.last_update_day);
    iob->bind_u8(d.drunkard_active);
    iob->bind_u8(d.nobles_with_bad_teeth);
    iob->bind_u8(d.toothache_probability);
    iob->bind_u8(d.fade_alpha);
    iob->bind_xstr<8>(d.image_key);
}

int building_house::get_fire_risk(int value) const {
    const bool is_empty = (house_level() == HOUSE_CRUDE_HUT) && is_vacant_lot();
    if (is_empty) {
        return 0;
    }

    return value;
}

void building_house::highlight_waypoints() {
    // nothing
}

bvariant building_house::get_property(const xstring &domain, const xstring &name) const {
    auto &d = runtime_data();
    if (domain == tags().house && name == tags().level_name) {
        int level = base.type - 10;
        return bvariant((pcstr)lang_get_string(29, level));
    }

    if (domain == tags().building && name == tags().tax_income_or_storage) {
        return bvariant(d.tax_income_or_storage);
    }

    return building_impl::get_property(domain, name);
}

void building_house::spawn_figure() {
    if (!has_road_access()) {
        return;
    }

    if (is_nobles() && house_population() > 20) {
        common_spawn_roamer(FIGURE_NOBLES, 0, (e_figure_action)125);
    }
}

template<typename T>
const building_house::house_params_t &house_static_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_house::house_params_t &)bparams;
}

const building_house::house_params_t &get_house_params(e_building_type type) {
    const auto &params = building_static_params::get(type);
    return house_static_params<building_house_crude_hut>(params);
};

const model_house &building_house::get_model(int level) {
    const auto &params = get_house_params(e_building_type(BUILDING_HOUSE_CRUDE_HUT + level));
    return params.model;
}

void building_house::create_vacant_lot(tile2i tile, int image_id) {
    building* b = building_create(BUILDING_HOUSE_VACANT_LOT, tile, 0);
    
    b->distance_from_entry = 0;
    map_building_tiles_add(b->id, b->tile, 1, image_id, TERRAIN_BUILDING);
}

resource_list building_house::consume_food_weekly() {
    if (!hsize()) {
        return {};
    }

    auto &d = runtime_data();

    int food_types = model().food_types;
    uint16_t amount_per_type = calc_adjust_with_percentage<short>(d.population, model().food_consumption_percentage);
    if (food_types > 1) {
        amount_per_type /= food_types;
    }

    if (amount_per_type > 0) {
        amount_per_type /= simulation_time_t::weeks_in_month;
        amount_per_type = std::max(amount_per_type, uint16_t(1));
    }

    d.num_foods = 0;
    resource_list food_types_eaten;
    if (g_scenario.kingdom_supplies_grain) {
        d.foods[0] = amount_per_type;
        food_types_eaten[RESOURCE_GRAIN] += amount_per_type;
        d.num_foods = 1;
        return food_types_eaten;
    }

    if (food_types <= 0) {
        return {};
    }

    int16_t want_consumed = amount_per_type * food_types;
    auto consume_food_impl = [&] {
        for (int t = INVENTORY_MIN_FOOD; t < INVENTORY_MAX_FOOD; t++) {
            const uint16_t exist_amount = std::min(d.foods[t], amount_per_type);
            if (exist_amount > 0) {
                want_consumed -= exist_amount;
                d.foods[t] -= exist_amount;
                d.num_foods += (exist_amount > 0) ? 1 : 0;
                e_resource food_res = g_city.allowed_foods(t);
                food_types_eaten.push_back({ food_res, amount_per_type });
            }
        }
    };

    // normal consumption, guess we have enough food
    consume_food_impl();

    if (want_consumed > 0) {
        // not enough food, try to consume more from available foods
        consume_food_impl();
    }

    return food_types_eaten;
}

resource_list building_house::consume_goods_weekly() {
    if (!hsize()) {
        return {};
    }
    
    resource_list good_types_consumed;
    auto &d = runtime_data();
    const model_house& model = get_model(house_level());

    auto consume_resource = [&] (int inventory, uint16_t amount) {
        if (amount <= 0) {
            return;
        }

        amount = std::min(amount, d.inventory[inventory]);
        d.inventory[inventory] -= amount;
        good_types_consumed.push_back({ (e_resource)inventory, amount });
    };

    consume_resource(INVENTORY_GOOD1, model.pottery);
    consume_resource(INVENTORY_GOOD2, model.jewelry);
    consume_resource(INVENTORY_GOOD3, model.linen);
    consume_resource(INVENTORY_GOOD4, model.beer);

    return good_types_consumed;
}

template<bool use_offset>
static int house_image_group(int level) {
    const e_building_type btype = e_building_type(BUILDING_HOUSE_CRUDE_HUT + level);
    const auto &params = building_static_params::get(btype);
    const auto anim = params.animations["house"];
    int image_id = image_id_from_group(anim.pack, anim.id);

    return image_id + (use_offset ? anim.offset : 0);
}

void building_house::add_population(int num_people) {
    const int mul = is_merged() ? 4 : 1;
    const int max_people = get_model(house_level()).max_people * mul;

    int room = std::max(max_people - house_population(), 0);
    if (room < num_people) {
        num_people = room;
    }

    if (house_population() <= 0) {
        change_to(base, BUILDING_HOUSE_CRUDE_HUT);
    }

    auto &d = runtime_data();
    d.population += num_people;
    g_city.population.add(num_people);
    base.remove_figure(2);
}

void building_house::change_to(building &b, e_building_type new_type, bool force) {
    auto &d = *(building_house::runtime_data_t*)b.runtime_data;

    const int house_update_delay = std::min(house_up_delay(), 7);
    const int absolute_day = game.simtime.absolute_day(true);
    const bool can_update = (absolute_day - d.last_update_day < house_update_delay);
    if (!force && (house_update_delay > 0 && (new_type > b.type) && can_update)) {
        return;
    }

    b.clear_impl(); // clear old impl
    b.type = new_type;

    auto house = b.dcast_house();
    int image_id = house_image_group<false>(house->house_level());

    const auto &house_params = get_house_params(new_type);
    if (house->is_merged()) {
        const size_t max_anims = house_params.variants_merged.data.size();
        const size_t rand_anim = rand() % max_anims;        
        auto anim_it = house_params.variants_merged.data.begin();
        std::advance(anim_it, rand_anim);
        d.image_key = anim_it->first;
        image_id = anim_it->second.first_img();
    } else {
        const size_t max_anims = house_params.variants.data.size();
        const size_t rand_anim = rand() % max_anims;
        auto anim_it = house_params.variants.data.begin();
        std::advance(anim_it, rand_anim);
        d.image_key = anim_it->first;
        image_id = anim_it->second.first_img();
    }

    map_building_tiles_add(b.id, b.tile, b.size, image_id, TERRAIN_BUILDING);
    d.last_update_day = game.simtime.absolute_day(true);
    d.image_id = image_id;
}

int16_t building_house::population_room() const {
    const int mul = is_merged() ? 4 : 1;
    const int max_people = model().max_people * mul;

    const int room = std::max(max_people - house_population(), 0);
    const int house_pop = house_population();

    return (max_people - house_pop);
}

void building_house::change_to_vacant_lot() {
    auto &d = runtime_data();
    base.type = BUILDING_HOUSE_VACANT_LOT;

    d.population = 0;
    int vacant_lot_id = anim(animkeys().house).first_img();

    if (!is_merged()) {
        map_image_set(base.tile, vacant_lot_id);
        return;
    }

    map_building_tiles_remove(base.id, base.tile);
    d.is_merged = 0;
    d.hsize = 1;
    base.size = 1;
    map_building_tiles_add(base.id, base.tile, 1, vacant_lot_id, TERRAIN_BUILDING);

    building_house::create_vacant_lot(base.tile.shifted(1, 0), vacant_lot_id);
    building_house::create_vacant_lot(base.tile.shifted(0, 1), vacant_lot_id);
    building_house::create_vacant_lot(base.tile.shifted(1, 1), vacant_lot_id);
}

bool building_house::is_vacant_lot() const {
    return house_population() == 0;
}

static void prepare_for_merge(int building_id, int num_tiles) {
    for (int i = 0; i < INVENTORY_MAX; i++) {
        g_merge_data.inventory[i] = 0;
        g_merge_data.foods[i] = 0;
    }

    g_merge_data.population = 0;
    int grid_offset = MAP_OFFSET(g_merge_data.tile);
    for (int i = 0; i < num_tiles; i++) {
        int house_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(house_offset, TERRAIN_BUILDING)) {
            auto house = building_at(house_offset)->dcast_house();
            if (house && house->id() != building_id && house->runtime_data().hsize) {
                g_merge_data.population += house->house_population();
                for (int inv = 0; inv < INVENTORY_MAX; inv++) {
                    auto &housed = house->runtime_data();
                    g_merge_data.inventory[inv] += housed.inventory[inv];
                    g_merge_data.foods[inv] += housed.foods[inv];
                    housed.population = 0;
                    house->base.state = BUILDING_STATE_DELETED_BY_GAME;
                }
            }
        }
    }
}

void building_house::merge_impl() {
    prepare_for_merge(id(), 4);

    auto &d = runtime_data();
    base.size = 2;
    d.hsize = 2;
    d.population += g_merge_data.population;

    for (int i = 0; i < INVENTORY_MAX; i++) {
        d.foods[i] += g_merge_data.foods[i];
        d.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<false>(house_level()) + 4;

    if (anim("house").offset) {
        image_id += 1;
    }

    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;

    d.is_merged = true;
    map_building_tiles_add(id(), tile(), 2, image_id, TERRAIN_BUILDING);
}

void building_house::merge() {
    if (is_merged()) {
        return;
    }

    if (!game_features::gameplay_change_all_houses_merge) {
        if ((map_random_get(base.tile) & 7) >= 5)
            return;
    }

    int num_house_tiles = 0;
    for (int i = 0; i < 4; i++) {
        int tile_offset = base.tile.grid_offset() + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            auto other_house = building_at(tile_offset)->dcast_house();
            if (!other_house) {
                continue;
            }

            if (other_house->id() == base.id) {
                num_house_tiles++;
            } else if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize
                     && (other_house->house_level() == house_level())
                     && !other_house->is_merged()) {
                num_house_tiles++;
            }
        }
    }

    if (num_house_tiles == 4) {
        g_merge_data.tile = tile2i(tilex() + expand_delta(0).x, tiley() + expand_delta(0).y);
        merge_impl();
    }
}

e_house_progress building_house::check_requirements(house_demands* demands) {
    auto &d = runtime_data();
    const model_house& model = this->model();
    
    // If house is unreachable beyond threshold, it should devolve
    if (d.unreachable_ticks >= model.unreachable_ticks_devolve_threshold) {
        return e_house_decay;
    }
    
    // If house requires food and has been without food for too long, it should devolve
    if (model.food_types > 0 && model.days_without_food_devolve_threshold > 0) {
        if (d.days_without_food >= model.days_without_food_devolve_threshold) {
            return e_house_decay;
        }
    }
    
    e_house_progress status = check_evolve_desirability();
    if (!has_required_goods_and_services(0, demands)) { // check if it will devolve to previous step
        status = e_house_decay;
    } else if (status == e_house_evolve) { // check if it can evolve to the next step
        // House cannot evolve if it's unreachable beyond threshold
        // If threshold is 0, any unreachable state blocks evolution
        if (model.unreachable_ticks_block_evolve_threshold == 0) {
            if (d.unreachable_ticks > 0) {
                status = e_house_none;
            } else {
                status = has_required_goods_and_services(1, demands);
            }
        } else {
            if (d.unreachable_ticks >= model.unreachable_ticks_block_evolve_threshold) {
                status = e_house_none;
            } else {
                status = has_required_goods_and_services(1, demands);
            }
        }
        
        // House cannot evolve if it's been without food (only for houses that require food)
        if (model.food_types > 0 && d.days_without_food > 0) {
            status = e_house_none;
        }
    }

    return status;
}

e_house_progress building_house::has_required_goods_and_services(int for_upgrade, house_demands* demands) {
    int level = house_level();
    if (for_upgrade) {
        ++level;
    }

    const model_house& model = get_model(level);
    // water
    int water = model.water;
    if (!base.has_water_access) {
        if (water >= 2) {
            ++demands->missing.fountain;
            return e_house_none;
        }
        if (water == 1 && !base.has_well_access) {
            ++demands->missing.well;
            return e_house_none;
        }
    }
    // entertainment
    int entertainment = model.entertainment;
    auto &d = runtime_data();
    if (d.entertainment < entertainment) {
        if (d.entertainment)
            ++demands->missing.more_entertainment;
        else {
            ++demands->missing.entertainment;
        }
        return e_house_none;
    }
    // education
    int education = model.education;
    if (d.education < education) {
        if (d.education)
            ++demands->missing.more_education;
        else {
            ++demands->missing.education;
        }
        return e_house_none;
    }

    if (education == 2) {
        ++demands->requiring.school;
        ++demands->requiring.library;
    } else if (education == 1)
        ++demands->requiring.school;

    // religion
    int religion = model.religion;
    if (d.num_gods < religion) {
        if (religion == 1) {
            ++demands->missing.religion;
            return e_house_none;
        } else if (religion == 2) {
            ++demands->missing.second_religion;
            return e_house_none;
        } else if (religion == 3) {
            ++demands->missing.third_religion;
            return e_house_none;
        }
    } else if (religion > 0)
        ++demands->requiring.religion;

    // dentist
    int dentist = model.dentist;
    if (d.dentist < dentist) {
        ++demands->missing.dentist;
        return e_house_none;
    }

    if (dentist == 1) {
        ++demands->requiring.dentist;
    }

    // physician
    int physician_required = model.physician;
    if (d.physician < physician_required) {
        ++demands->missing.physician;
        return e_house_none;
    }
    if (physician_required == 1) {
        ++demands->requiring.physician;
    }

    // health
    int health_need = model.health;
    if (d.health < health_need) {
        if (health_need < 2)
            ++demands->missing.dentist;
        else {
            ++demands->missing.physician;
        }
        return e_house_none;
    }
    if (health_need >= 1) {
        ++demands->requiring.physician;
    }

    // food types
    int foodtypes_required = model.food_types;
    int foodtypes_available = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        foodtypes_available += (d.foods[i] > 0) ? 1 : 0;
    }

    if (foodtypes_available < foodtypes_required) {
        ++demands->missing.food;
        return e_house_none;
    }

    // goods
    if (d.inventory[INVENTORY_GOOD1] < model.pottery)
        return e_house_none;

    if (d.inventory[INVENTORY_GOOD3] < model.linen)
        return e_house_none;

    if (d.inventory[INVENTORY_GOOD2] < model.jewelry)
        return e_house_none;

    int beer = model.beer;
    if (beer && d.inventory[INVENTORY_GOOD4] <= 0)
        return e_house_none;

    if (beer > 1 && !city_resource_multiple_wine_available()) {
        ++demands->missing.second_wine;
        return e_house_none;
    }

    // fancy bazaar access (for high-level houses)
    if (model.fancy_bazaar && d.fancy_bazaar_access <= 0) {
        return e_house_none;
    }

    return e_house_evolve;
}

bool building_house::has_devolve_delay(int status) {
    auto &d = runtime_data();
    const int max_delay = model().devolve_delay;
    if (status == e_house_decay && d.devolve_delay < max_delay) {
        d.devolve_delay++;
        return true;
    } else {
        d.devolve_delay = 0;
        return false;
    }
}

void building_house::decay_tax_coverage() {
    if (!is_valid() || !hsize()) {
        return;
    }

    auto &housed = runtime_data();
    if (housed.tax_coverage) {
        housed.tax_coverage--;
    }
}

void building_house::update_monthly_nobles_toothache() {
    if (!is_nobles() || house_population() <= 0) {
        return;
    }

    auto &housed = runtime_data();
    housed.toothache_probability = std::min<uint8_t>(housed.toothache_probability + 10, 100);

    int random_value = rand() % 100;
    if (random_value < housed.toothache_probability) {
        housed.toothache_probability = 0;
        housed.nobles_with_bad_teeth = std::min<uint8_t>(housed.nobles_with_bad_teeth + 1, 255);
    }
}

void building_house::decay_services() {
    if (!hsize()) {
        return;
    }

    auto &housed = runtime_data();
    decay_service(housed.booth_juggler);
    decay_service(housed.bandstand_juggler);
    decay_service(housed.bandstand_musician);
    decay_service(housed.pavillion_musician);
    decay_service(housed.senet_player);
    decay_service(housed.magistrate);
    decay_service(housed.bullfighter);
    decay_service(housed.school);
    decay_service(housed.library);
    decay_service(housed.academy);
    decay_service(housed.apothecary);
    decay_service(housed.dentist);
    decay_service(housed.mortuary);
    decay_service(housed.physician);
    decay_service(housed.temple_osiris);
    decay_service(housed.temple_ra);
    decay_service(housed.temple_ptah);
    decay_service(housed.temple_seth);
    decay_service(housed.temple_bast);
    decay_service(housed.bazaar_access);
    decay_service(housed.drunkard_active);
}

bool building_house::can_expand(int num_tiles) {
    // merge with other houses
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                auto other_house = building_at(tile_offset)->dcast_house();
                if (!other_house) {
                    continue;
                }

                if (other_house->id() == id()) {
                    ok_tiles++;
                } else if (other_house->is_valid() && other_house->hsize()) {
                    if (other_house->house_level() <= house_level()) {
                        ok_tiles++;
                    }
                }
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }
    // merge with houses and empty terrain
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR)) {
                ok_tiles++;
                continue;
            } 
            
            if (!map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                continue;
            }

            auto other_house = building_at(tile_offset)->dcast_house();
            if (!other_house) {
                continue;
            }

            if (other_house->id() == id()) {
                ok_tiles++;
                continue;
            } 
            
            if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize
                && other_house->house_level() <= house_level()) {
                ok_tiles++;
            }
        }

        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }
    // merge with houses, empty terrain and gardens
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR)) {
                ok_tiles++;
                continue;
            } 

            if (map_terrain_is(tile_offset, TERRAIN_GARDEN) && !game_features::gameplay_change_houses_dont_expand_into_gardens) {
                ok_tiles++;
                continue;
            }
            
            if (!map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                continue;
            }

            auto other_house = building_at(tile_offset)->dcast_house();
            if (!other_house) {
                continue;
            }

            if (other_house->id() == id()) {
                ok_tiles++;
            } 
            
            const bool may_expand = other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize && other_house->house_level() <= house_level();
            ok_tiles += may_expand ? 1 : 0;
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }

    runtime_data().no_space_to_expand = 1;
    return false;
}

e_house_progress building_house::check_evolve_desirability() {
    const int level = house_level();
    const int evolve_des = (level >= HOUSE_PALATIAL_ESTATE) ? 1000 : model() .evolve_desirability;

    const int current_des = base.current_desirability;
    e_house_progress status;

    auto &d = runtime_data();
    if (current_des <= model().devolve_desirability) {
        status = e_house_decay;
        d.evolve_text = "#cannot_evolve_cause_low_desirability"; 
    } else if (current_des >= evolve_des) {
        status = e_house_evolve;
        d.evolve_text = "#house_upgrade_inprogress";
    } else {
        status = e_house_none;
        d.evolve_text = "#house_upgrade_inprogress";
    }

    return status;
}

static void create_house_tile(e_building_type type, tile2i tile, int image_id, int population, custom_span<int> inventory, custom_span<int> foods) {
    auto house = building_create(type, tile, 0)->dcast_house();

    auto &housed = house->runtime_data();
    housed.population = population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] = foods[i];
        housed.inventory[i] = inventory[i];
    }
    house->base.distance_from_entry = 0;
    map_building_tiles_add(house->id(), house->tile(), 1, image_id + (map_random_get(house->tile()) & 1), TERRAIN_BUILDING);
}

static void split_size2(building* b, e_building_type new_type) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto house = b->dcast_house();
    auto &housed = house->runtime_data();
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 4;
        inventory_remainder[i] = housed.inventory[i] % 4;
        foods_per_tile[i] = housed.foods[i] / 4;
        foods_remainder[i] = housed.foods[i] % 4;
    }

    int population_per_tile = housed.population / 4;
    int population_remainder = housed.population % 4;

    map_building_tiles_remove(b->id, b->tile);

    // main tile
    b->type = new_type;
    b->size = 1;
    housed.hsize = 1;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    b->distance_from_entry = 0;

    const int image_id = house_image_group<true>(house->house_level());
    map_building_tiles_add(b->id, b->tile, b->size, image_id + (map_random_get(b->tile) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(b->type, b->tile.shifted(1, 0), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

static void split_size3(building* b) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto house = b->dcast_house();
    auto &housed = house->runtime_data();
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 9;
        inventory_remainder[i] = housed.inventory[i] % 9;
        foods_per_tile[i] = housed.foods[i] / 9;
        foods_remainder[i] = housed.foods[i] % 9;
    }

    int population_per_tile = housed.population / 9;
    int population_remainder = housed.population % 9;

    map_building_tiles_remove(b->id, b->tile);

    // main tile
    b->type = BUILDING_HOUSE_SPACIOUS_APARTMENT;
    b->size = 1;
    housed.hsize = 1;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    b->distance_from_entry = 0;

    const int image_id = house_image_group<true>(house->house_level());
    map_building_tiles_add(b->id, b->tile, b->size, image_id + (map_random_get(b->tile) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(b->type, b->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(2, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(0, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(2, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house::split(int num_tiles) {
    int grid_offset = MAP_OFFSET(g_merge_data.tile);
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset + house_tile_offsets(i);
        if (!map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            continue;
        }

        auto other_house = building_at(tile_offset)->dcast_house();
        if (!other_house) {
            continue;
        }

        if (other_house->id() != id() && (other_house->runtime_data().hsize > 0)) {
            if (other_house->is_merged()) {
                split_size2(&other_house->base, other_house->type());
            } else if (other_house->runtime_data().hsize == 2) {
                split_size2(&other_house->base, BUILDING_HOUSE_SPACIOUS_APARTMENT);
            } else if (other_house->runtime_data().hsize == 3) {
                split_size3(&other_house->base);
            }
        }
    }
}

const model_house &building_house::model() const {
    return get_model(house_level());
}

void building_house_common_manor::devolve_to_fancy_residence() {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = runtime_data();

    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 6;
        inventory_remainder[i] = housed.inventory[i] % 6;
        foods_per_tile[i] = housed.foods[i] / 6;
        foods_remainder[i] = housed.foods[i] % 6;
    }

    int population_per_tile = house_population() / 6;
    int population_remainder = house_population() % 6;

    map_building_tiles_remove(id(), tile());

    // main tile
    base.type = BUILDING_HOUSE_FANCY_RESIDENCE;
    base.size = 2;
    housed.hsize = 2;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    base.distance_from_entry = 0;

    int image_id = house_image_group<true>(house_level());
    map_building_tiles_add(id(), tile(), size(), image_id + (map_random_get(tile()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 0), image_id, population_per_tile,inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(0, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(1, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house_modest_estate::devolve_to_statel_manor() {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = runtime_data();

    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 8;
        inventory_remainder[i] = housed.inventory[i] % 8;
        foods_per_tile[i] = housed.foods[i] / 8;
        foods_remainder[i] = housed.foods[i] % 8;
    }
    int population_per_tile = house_population() / 8;
    int population_remainder = house_population() % 8;

    map_building_tiles_remove(id(), tile());

    // main tile
    base.type = BUILDING_HOUSE_STATELY_MANOR;
    base.size = 3;
    housed.hsize = 3;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    base.distance_from_entry = 0;

    int image_id = house_image_group<true>(house_level());
    map_building_tiles_add(id(), tile(), size(), image_id, TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 0), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(0, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(1, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house::check_for_corruption() {
    //data.house.no_space_to_expand = 0;
    //
    //// house offset is corrupted??
    //if (tile().grid_offset() != MAP_OFFSET(tilex(), tiley())
    //    || map_building_at(tile().grid_offset()) != house->id) {
    //    int map_width = scenario_map_data()->width;
    //    int map_height = scenario_map_data()->height;
    //    //        int map_width, map_height;
    //    //        map_grid_size(&map_width, &map_height); // get map size and store in temp vars
    //
    //    // go through tiles and find tile belonging to the house
    //    for (int y = 0; y < map_height; y++) {
    //        for (int x = 0; x < map_width; x++) {
    //            int grid_offset = MAP_OFFSET(x, y); // get offset of current tile (global map tile offset)
    //            if (map_building_at(grid_offset) == house->id) { // does this tile belong to the house I'm searching for??
    //                house->tile.set(grid_offset);
    //                //                    house->tile.grid_offset() = grid_offset; // set house offset to this tile's
    //                //                    offset (i.e. lowest x & y; north-west corner) house->tile.x() =
    //                //                    MAP_X(grid_offset); // set house coords (x) to tile's coords (x)
    //                //                    house->tile.y() = MAP_Y(grid_offset); // set house coords (y) to tile's coords
    //                //                    (y) building_totals_add_corrupted_house(0);
    //                return;
    //            }
    //        }
    //    }
    //    //        building_totals_add_corrupted_house(1);
    //    house->state = BUILDING_STATE_RUBBLE;
    //}
}

void building_house::on_create(int orientation) {
    auto &d = runtime_data();
    base.common_health = 100;
    d.house_happiness = 50;

    if (house_level() == 0) {
        d.population = 0;
    }

    d.hsize = 0;
    d.fade_alpha = 0;
    if (type() >= BUILDING_HOUSE_CRUDE_HUT && type() <= BUILDING_HOUSE_SPACIOUS_APARTMENT) {
        d.hsize = 1;
    } else if (type() >= BUILDING_HOUSE_COMMON_RESIDENCE && type() <= BUILDING_HOUSE_FANCY_RESIDENCE) {
        d.hsize = 2;
    } else if (type() >= BUILDING_HOUSE_COMMON_MANOR && type() <= BUILDING_HOUSE_STATELY_MANOR) {
        d.hsize = 3;
    } else if (type() >= BUILDING_HOUSE_MODEST_ESTATE && type() <= BUILDING_HOUSE_PALATIAL_ESTATE) {
        d.hsize = 4;
    }
}

void building_house::on_destroy() {
    g_city.population.remove_home_removed(house_population());
}

void building_house::on_post_load() {
    building_impl::on_post_load();

    const int imgid = map_image_at(tile());
    map_building_tiles_add(id(), tile(), size(), imgid, TERRAIN_BUILDING);

    auto &d = runtime_data();
    const auto &house_params = get_house_params(base.type);
    if (d.image_key.empty()) {
        const auto &variants = house_params.variants.data;
        auto it = std::find_if(variants.begin(), variants.end(), [imgid] (auto &i) { return i.second.first_img() == imgid; });
        if (it != variants.end()) {
            d.image_key = it->first;
        }
    }

    if (d.image_key.empty()) {
        const auto &variants_merged = house_params.variants_merged.data;
        auto it = std::find_if(variants_merged.begin(), variants_merged.end(), [imgid] (auto &i) { return i.second.first_img() == imgid; });
        if (it != variants_merged.end()) {
            d.image_key = it->first;
        }
    }
}

void building_house::on_place_checks() {
    if (type() != BUILDING_HOUSE_VACANT_LOT) {
        return;
    }

    construction_warnings warnings;
    const int city_population = g_city.population.current;
    const bool need_more_food = (city_population >= 200 && !g_scenario.kingdom_supplies_grain && g_city.resource.food_percentage_produced() <= 95);
    warnings.add_if(need_more_food, "#people_eat_more_than_produce");
}

bool building_house_crude_hut::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    int status = check_requirements(demands);
    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_STURDY_HUT);
    }

    return false;
}

bool building_house_sturdy_hut::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_MEAGER_SHANTY);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_CRUDE_HUT);
    }

    return false;
}

bool building_house_meager_shanty::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_COMMON_SHANTY);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_STURDY_HUT);
    }

    return false;
}

bool building_house_common_shanty::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_ROUGH_COTTAGE);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_MEAGER_SHANTY);
    }

    return false;
}

bool building_house_rough_cottage::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_ORDINARY_COTTAGE);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_COMMON_SHANTY);
    }

    return false;
}

bool building_house_ordinary_cottage::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_MODEST_HOMESTEAD);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_ROUGH_COTTAGE);
    }

    return false;
}

bool building_house_modest_homestead::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_ORDINARY_COTTAGE);
    }

    return false;
}

bool building_house_spacious_homestead::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_MODEST_APARTMENT);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_MODEST_HOMESTEAD);
    }

    return false;
}

bool building_house_modest_apartment::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_APARTMENT);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
    }

    return false;
}

void building_house_spacious_apartment::expand_to_common_residence() {
    split(4);
    prepare_for_merge(id(), 4);

    auto &housed = runtime_data();

    base.type = BUILDING_HOUSE_COMMON_RESIDENCE;
    base.size = 2;
    housed.hsize = 2;
    housed.population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house_level()) + (map_random_get(tile().grid_offset()) & 1);
    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_spacious_apartment::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        if (can_expand(4)) {
            runtime_data().is_merged = false;
            expand_to_common_residence();
            map_tiles_gardens_update_all();
            return true;
        }
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_MODEST_APARTMENT);
    }

    return false;
}

bool building_house_common_residence::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    merge();
    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_RESIDENCE);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_APARTMENT);
    }

    return false;
}

bool building_house_spacious_residence::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_ELEGANT_RESIDENCE);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_COMMON_RESIDENCE);
    }

    return false;
}

bool building_house_elegant_residence::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_FANCY_RESIDENCE);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_RESIDENCE);
    }

    return false;
}

void building_house_fancy_residence::expand_to_common_manor() {
    split(9);
    prepare_for_merge(id(), 9);

    auto &housed = runtime_data();
    base.type = BUILDING_HOUSE_COMMON_MANOR;
    base.size = 3;
    housed.hsize = 3;
    housed.population += g_merge_data.population;

    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }

    int image_id = house_image_group<true>(house_level());
    map_building_tiles_remove(id(), base.tile);
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), base.tile, base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_fancy_residence::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        if (can_expand(9)) {
            expand_to_common_manor();
            map_tiles_gardens_update_all();
            return true;
        }
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_ELEGANT_RESIDENCE);
    }

    return false;
}

bool building_house_common_manor::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_MANOR);
    } else if (status == e_house_decay) {
        devolve_to_fancy_residence();
    }

    return false;
}

void building_house_common_manor::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

bool building_house_spacious_manor::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_ELEGANT_MANOR);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_COMMON_MANOR);
    }

    return false;
}

void building_house_spacious_manor::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

bool building_house_elegant_manor::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_STATELY_MANOR);
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_SPACIOUS_MANOR);
    }

    return false;
}

void building_house_elegant_manor::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

void building_house_stately_manor::expand_to_modest_estate() {
    split(16);
    prepare_for_merge(id(), 16);

    auto &housed = runtime_data();

    base.type = BUILDING_HOUSE_MODEST_ESTATE;
    base.size = 4;
    housed.hsize = 4;
    housed.population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house_level());
    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_stately_manor::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve && can_expand(16)) {
        expand_to_modest_estate();
        map_tiles_gardens_update_all();
        return true;
    } else if (status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_ELEGANT_MANOR);
    }

    return false;
}

void building_house_stately_manor::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

bool building_house_modest_estate::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_requirements(demands);
    if (has_devolve_delay(status)) {
        return false;
    }

    if (status == e_house_evolve) {
        change_to(base, BUILDING_HOUSE_PALATIAL_ESTATE);
    } else if (status == e_house_decay) {
        devolve_to_statel_manor();
    }

    return false;
}

void building_house_modest_estate::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

void building_house_palatial_estate::update_month() {
    building_house::update_month();
    update_monthly_nobles_toothache();
}

bool building_house_palatial_estate::evolve(house_demands* demands) {
    if (house_population() <= 0) {
        return false;
    }

    e_house_progress status = check_evolve_desirability();
    if (!has_required_goods_and_services(0, demands)) {
        status = e_house_decay;
    }

    if (!has_devolve_delay(status) && status == e_house_decay) {
        change_to(base, BUILDING_HOUSE_MODEST_ESTATE);
    }

    return false;
}

void building_house::update_fade_alpha() {
    auto &d = runtime_data();
    
    // Check if cursor is over this house building
    extern screen_city_t g_screen_city;
    tile2i current_tile = g_screen_city.current_tile;
    
    bool is_hovered = false;
    if (current_tile.valid()) {
        int hover_building_id = map_building_at(current_tile);
        building* hover_b = building_get(hover_building_id);
        
        if (hover_b && hover_b->main()->id == base.main()->id && hover_b->dcast_house()) {
            is_hovered = true;
        }
    }
    
    if (is_hovered) {
        if (d.fade_alpha < 255) {
            d.fade_alpha = std::min<int>(255, d.fade_alpha + 15); // Increase by 15 per frame
        }
    } else {
        if (d.fade_alpha > 0) {
            d.fade_alpha = std::max<int>(0, d.fade_alpha - 10); // Decrease by 10 per frame
        }
    }
}

bool building_house::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);
    
    update_fade_alpha();
    
    auto &d = runtime_data();
    if (d.fade_alpha > 0) {
        const auto &params = get_house_params(base.type);
        
        if (!params.variants_merged_inside.empty() && is_merged()) {
            const auto& ranim = params.variants_merged_inside[d.image_key];
              
            if (ranim.first_img() > 0) {
                auto &command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                command.image_id = ranim.first_img();
                command.pixel = point;
                command.mask = (d.fade_alpha << COLOR_BITSHIFT_ALPHA) | (color_mask != 0 ? (color_mask & 0x00FFFFFF) : 0x00FFFFFF);
                command.flags = ImgFlag_Alpha;
            }
        }
    }
    
    return true;
}

bool building_house::target_route_tile_blocked(int grid_offset) const {
    return house_level() > 0 || house_population() > 0;
}
