#include "building.h"

#include "building/rotation.h"
#include "building/building_type.h"
#include "building/building_storage.h"
#include "building/destruction.h"
#include "city/buildings.h"
#include "city/city_population.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "widget/city/ornaments.h"
#include "core/svector.h"
#include "core/profiler.h"
#include "figure/formation_batalion.h"
#include "game/resource.h"
#include "game/undo.h"
#include "game/settings.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/random.h"
#include "grid/image.h"
#include "grid/routing/routing_terrain.h"
#include "construction/build_planner.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "io/io_buffer.h"
#include "graphics/graphics.h"
#include "monuments.h"
#include "overlays/city_overlay.h"
#include "sound/sound_building.h"
#include "city/city.h"
#include "figure/figure.h"
#include "figuretype/figure_cartpusher.h"
#include "core/object_property.h"
#include "graphics/view/view.h"
#include "game/game_config.h"
#include "core/random.h"
#include "sound/sound.h"

#include <string.h>
#include <map>

#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

declare_console_command_p(destroytype) {
    std::string args; is >> args;
    int type = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    
    buildings_valid_do([] (building &b) {
        b.destroy_by_collapse();
    }, (e_building_type)type);
};

const token_holder<e_building_state, BUILDING_STATE_UNUSED, BUILDING_STATE_COUNT> e_building_state_tokens;
const token_holder<e_building_type, BUILDING_NONE, BUILDING_MAX> ANK_CONFIG_ENUM(e_building_type_tokens);

static std::array<const building_static_params*, BUILDING_MAX> *building_impl_params = nullptr;
static std::array<const building_planer_renderer *, BUILDING_MAX> *building_planer_rends = nullptr;
building_static_params building_static_params::dummy;

void building::initialize(e_building_type _tp, tile2i _tl, int orientation) {
    assert(!_ptr);
    const auto &props = building_static_params::get(_tp);
    type = _tp;
    tile = _tl;
    state = BUILDING_STATE_CREATED;
    size = props.building_size;
    distance_from_entry = 0;

    map_random_7bit = map_random_get(tile.grid_offset()) & 0x7f;
    figure_roam_direction = map_random_7bit & 6;
    fire_proof = props.fire_proof;
    damage_proof = props.damage_proof;
    is_adjacent_to_water = map_terrain_is_adjacent_to_water(tile, size);
    des_influence = props.desirability.to_influence();

    max_workers = props.laborers;
    fire_risk_increase = props.fire_risk;
    damage_risk_increase = props.damage_risk;

    // unique data
    input = params().input;
    output = params().output;

    dcast()->on_create(orientation);
}

desirability_t::influence_t building_desirability_t::to_influence() const {
    desirability_t::influence_t inf;
    e_difficulty diff = g_settings.difficulty();
    auto approach_diff = [&] (auto &arr) { if (arr.empty()) return (int)0; return (int)arr[std::min<int>(diff, arr.size() - 1)]; };

    inf.size = 0;
    inf.value = approach_diff(value);
    inf.step = approach_diff(step);
    inf.step_size = approach_diff(step_size);
    inf.range = approach_diff(range);

    return inf;
}

void building_impl::acquire(e_building_type e, building &b) {
    static_assert(sizeof(building_impl) <= sizeof(building::ptr_buffer_t));

    using namespace buildings;
    for (auto static_ctor = BuildingCtorIterator::tail; static_ctor; static_ctor = static_ctor->next) {
        auto impl = static_ctor->func(e, b);
        if (impl) {
            return;
        }
    }

    //assert(false && "Cant find building type in config");
    b.acquire_impl<building_impl>();
}

bool building_impl::required_resource(e_resource r) const {
    return base.input.resource == r || base.input.resource_second== r;
}

int building_impl::stored_amount(e_resource r) const {
    if (base.input.resource == r) {
        return base.stored_amount_first;
    }

    if (base.input.resource_second == r) {
        return base.stored_amount_second;
    }

    return base.stored_amount_first;
}

resource_vec building_impl::required_resources() const { 
    if (base.input.resource == RESOURCE_NONE && base.input.resource_second == RESOURCE_NONE) {
        return {}; 
    }

    resource_vec r;
    if (base.input.resource != RESOURCE_NONE) {
        r.push_back(base.input.resource);
    }

    if (base.input.resource_second != RESOURCE_NONE) {
        r.push_back(base.input.resource_second);
    }

    return r;
}

metainfo building_impl::get_info() const {
    const auto &metainfo = !current_params().meta_id.empty()
                                ? base.get_info(current_params().meta_id)
                                : current_params().meta;
    return metainfo;
}

void building_impl::set_animation(const animation_t &anim) {
    base.anim.setup(anim);
}

xstring building_impl::get_sound() {
    return snd::get_building_info_sound(type());
}

const int building_static_params::base_img() const { return first_img(animkeys().base); }

void building_static_params::register_model(e_building_type e, const building_static_params &p) {
    if (!building_impl_params) {
        building_impl_params = new std::array<const building_static_params *, BUILDING_MAX>();
        std::fill(building_impl_params->begin(), building_impl_params->end(), nullptr);
    }
    (*building_impl_params)[e] = &p;
}

const building_static_params &building_static_params::get(e_building_type e) {
    auto p = building_impl_params->at(e);
    return (p == nullptr) ? building_static_params::dummy : *p;
}

building_static_params &building_static_params::ref(e_building_type e) {
    auto *cfg = building_impl_params->at(e);
    assert(cfg);
    return *const_cast<building_static_params *>(cfg);
}


const building_impl *building::dcast() const {
    if (!_ptr) {
        building_impl::acquire(type, const_cast<building&>(*this));
    }

    assert(!!_ptr);
    return _ptr;
}

building_impl *building::dcast() {
    if (!_ptr) {
        building_impl::acquire(type, *this);
    }

    assert(!!_ptr);
    return _ptr;
}

building::building() {
}

building* building::main() {
    if (prev_part_building_id <= 0) {
        return this;
    }

    building* b = this;
    for (int guard = 0; guard < 99; guard++) {
        if (b->prev_part_building_id <= 0) {
            return b;
        }
        b = building_get(b->prev_part_building_id);
    }

    return building_get(0);
}

building* building::top_xy() {
    building* b = main();
    int x = b->tile.x();
    int y = b->tile.y();
    building* top = b;
    while (b->next_part_building_id <= 0) {
        b = next();
        if (b->tile.x() < x)
            top = b;
        if (b->tile.y() < y)
            top = b;
    }
    return top;
}

bool building::is_main() {
    return (prev_part_building_id == 0);
}

void building::clear_impl() {
    memset(&_ptr_buffer, 0, sizeof(ptr_buffer_t));
    _ptr = nullptr;
}

void building::reset_impl() {
    _ptr = nullptr;
}


xstring building::get_sound() {
    return snd::get_building_info_sound(type);
}

void building::clear_related_data() {
    if (storage_id) {
        building_storage_delete(storage_id);
        storage_id = 0;
    }

    if (type == BUILDING_DISTRIBUTION_CENTER_UNUSED)
        city_buildings_remove_distribution_center(this);

    if (building_is_fort(type)) {
        formation_batalion_delete_for_fort(this);
    }

    if (type == BUILDING_RESERVED_TRIUMPHAL_ARCH_56) {
        city_buildings_remove_triumphal_arch();
        //building_menu_update(BUILDSET_NORMAL);
    }

    dcast()->on_destroy();
    clear_impl();
}

e_overlay building::get_overlay() const {
    return const_cast<building*>(this)->dcast()->get_overlay();
}

// void building_totals_add_corrupted_house(int unfixable)
//{
//     extra.incorrect_houses++;
//     if (unfixable) {
//         extra.unfixable_houses++;
//     }
// }

bool building::is_defense() {
    return building_is_defense(type);
}
bool building::is_farm() {
    return building_is_farm(type);
}
bool building::is_workshop() {
    return building_is_workshop(type);
}
bool building::is_extractor() {
    return building_is_extractor(type);
}
bool building::is_monument() {
    return building_is_monument(type);
}
bool building::is_palace() {
    return building_is_palace(type);
}
bool building::is_tax_collector() {
    return building_is_tax_collector(type);
}
bool building::is_temple() {
    return building_is_temple(type);
}
bool building::is_temple_complex() const {
    return building_is_temple_complex(type);
}
bool building::is_shrine() const {
    return building_is_shrine(type);
}
bool building::is_guild() {
    return building_is_guild(type);
}
bool building::is_beautification() {
    return building_is_beautification(type);
}
bool building::is_water_crossing() {
    return building_is_water_crossing(type);
}

bool building::is_industry() {
    return building_is_industry(type);
}
bool building::is_food_category() {
    return building_is_food_category(type);
}
bool building::is_infrastructure() {
    return building_is_infrastructure(type);
}
bool building::is_administration() {
    return building_is_administration(type);
}
bool building::is_religion() {
    return building_is_religion(type);
}

bool building::is_education() {
    return building_is_education(type);
}
bool building::is_military() {
    return building_is_military(type);
}

bool building::common_spawn_figure_trigger(int min_houses, int slot) {
    check_labor_problem();
    if (!has_road_access) {
        return false;
    }

    if (main() == this) { // only spawn from the main building
        common_spawn_labor_seeker(min_houses);
    }

    if (has_figure(slot)) {
        return false;
    }

    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return false;
    }

    figure_spawn_delay++;
    if (figure_spawn_delay > spawn_delay) {
        figure_spawn_delay = 0;
        return true;
    }

    return false;
}


figure *building::create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir) {
    figure *f = figure_create(_type, road_access, created_dir);
    f->action_state = created_action;
    f->set_home(id);
    set_figure(slot, f);

    return f;
}

figure *building::create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action, e_building_slot slot) {
    figure *f = create_figure_generic(FIGURE_CART_PUSHER, created_action, slot, DIR_4_BOTTOM_LEFT);
    auto cart = ::smart_cast<figure_cartpusher>(f);
    if (!cart) {
        return f;
    }

    cart->load_resource(resource_id, quantity);
    cart->set_destination(nullptr);
    
    set_figure(slot, cart->id()); // warning: this overwrites any existing figure!
    if (!!game_features::gameplay_change_cart_speed_depends_quntity) {
        f->progress_inside_speed = std::clamp(quantity / 400, 0, 2);
    }
    cart->base.wait_ticks = 30;

    return f;
}

figure *building::create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action, e_building_slot slot) {
    figure *f = create_figure_generic(_type, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->set_destination(destination->id);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    return f;
}

figure *building::create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) {
    figure *f = create_figure_generic(_type, created_action, slot, figure_roam_direction);

    f->set_destination(nullptr);

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    f->init_roaming_from_building(figure_roam_direction);
    f->set_home(id);

    // update building to have a different roamer direction for next time
    figure_roam_direction += 2;
    if (figure_roam_direction > 6) {
        figure_roam_direction = 0;
    }

    return f;
}

int building::stored_amount(e_resource res) const {
    building *b = (building *)this;
    return b->dcast()->stored_amount(res);
}

int building::need_resource_amount(e_resource resource) const {
    return max_storage_amount(resource) - stored_amount(resource);
}

bool building::need_resource(e_resource resource) const {
    return ((building*)this)->dcast()->required_resource(resource);
}

int building::max_storage_amount(e_resource resource) const {
    return 200;
}

int building::stored_amount(int idx) const {
    switch (idx) {
    case 0: return stored_amount_first;
    case 1: return stored_amount_second;
    }

    assert(false);
    return 0;
}

bool building::workshop_has_resources() {
    assert(is_workshop());
    bool has_second_material = true;
    if (input.resource_second != RESOURCE_NONE) {
        has_second_material = (stored_amount_second > 100);
    }

    bool hase_first_resource = (stored_amount_first >= 100);
    return has_second_material && hase_first_resource;
}

void building::force_damage(bool fire, int8_t value) {
    const bool valid = (state == BUILDING_STATE_VALID || state == BUILDING_STATE_MOTHBALLED);
    if (!valid) {
        return;
    }

    if (fire) {
        fire_risk += value;
    } else {    
        damage_risk += value;
    }
}

void building::destroy_by_collapse() {
    assert(is_main());

    events::emit(event_collase_damage{ id });

    destroy_reason = e_destroy_collapse;
    state = BUILDING_STATE_RUBBLE;
    dcast()->on_before_collapse();
    map_building_tiles_set_rubble(id, tile, size);
    figure_create_explosion_cloud(tile, size);
    destroy_linked_parts(false);
    g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
}

void building::destroy_by_flooded() {
    assert(is_main());

    events::emit(event_flooded_damage{ id });

    destroy_reason = e_destroy_flooded;
    state = BUILDING_STATE_RUBBLE;
    dcast()->on_before_flooded();
    map_building_tiles_set_rubble(id, tile, size);
    destroy_linked_parts(false);
    g_sound.play_effect(SOUND_EFFECT_FLOODED);
}

void building::destroy_on_fire_impl(bool plagued) {
    game_undo_disable();
    fire_risk = 0;
    damage_risk = 0;

    events::emit(event_fire_damage{ id });

    //int was_tent = b->house_size && b->data.house.level <= HOUSE_STURDY_HUT;
    state = BUILDING_STATE_DELETED_BY_GAME;
    output.resource = RESOURCE_NONE;
    output.resource_second = RESOURCE_NONE;
    distance_from_entry = 0;
    clear_related_data();

    int waterside_building = 0;
    if (type == BUILDING_DOCK || type == BUILDING_FISHING_WHARF || type == BUILDING_SHIPWRIGHT) {
        waterside_building = 1;
    }

    map_building_tiles_remove(id, tile);
    unsigned int rand_int = random_short();

    grid_area varea = map_grid_get_area(tile, size, 0);
    map_grid_area_foreach(varea, [plagued] (tile2i tile) {
        if (map_terrain_is(tile, TERRAIN_WATER)) {
            return;
        }

        // FIXME: possible can't render image & fire animation
        building *ruin = building_create(BUILDING_BURNING_RUIN, tile, 0);
        ruin->has_plague = plagued;
    });

    if (waterside_building) {
        map_routing_update_water();
    }
}

void building::destroy_by_fire() {
    assert(is_main());

    destroy_on_fire_impl(false);
    destroy_linked_parts(true);
    g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
}

void building::destroy_linked_parts(bool on_fire) {
    building *part = this;
    for (int i = 0; i < 99; i++) {
        if (part->prev_part_building_id <= 0) {
            break;
        }

        int part_id = part->prev_part_building_id;
        part = building_get(part_id);
        if (on_fire) {
            part->destroy_on_fire_impl(false);
        } else {
            map_building_tiles_set_rubble(part_id, part->tile, part->size);
            part->state = BUILDING_STATE_RUBBLE;
        }
    }

    part = this;
    for (int i = 0; i < 99; i++) {
        part = part->next();
        if (part->id <= 0) {
            break;
        }

        if (on_fire) {
            part->destroy_on_fire_impl(false);
        } else {
            map_building_tiles_set_rubble(part->id, part->tile, part->size);
            part->state = BUILDING_STATE_RUBBLE;
        }
    }
}

void building::mark_plague(int days) {
    assert(is_main());
    disease_days = days;
    has_plague = true;
}

bool building::is_ajacent_tile(tile2i t) const {
    grid_area area = map_grid_get_area(tile, size, 1);
    return area.contains(t);
}

const building_static_params &building::params() const {
    return building_static_params::get(type);
}

xstring building::cls_name() const {
    const auto &params = building_static_params::get(type);
    if (!params.info_title_id.empty()) {
        return params.info_title_id;
    }

    const auto &m = params.meta;
    return ui::str(m.text_id, 0);
}

tile2i building::access_tile() {
    switch (type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_SIDE:
        return main()->tile.shifted(0, 10);

    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_MEDIUM_MASTABA_ENTRANCE:
    case BUILDING_MEDIUM_MASTABA_WALL:
    case BUILDING_MEDIUM_MASTABA_SIDE:
        return main()->tile.shifted(0, 14);
    }

    return road_access;
}

int building::get_figures_number(e_figure_type ftype) {
    int figures_this_yard = 0;
    for (int i = 0; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f->has_type(ftype) && f->has_home(this)) {        // figure with type on map and  belongs to this building
            figures_this_yard++;
        }
    }

    return figures_this_yard;
}

bool building::common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action) {
    if (common_spawn_figure_trigger(min_houses)) {
        create_roaming_figure(type, created_action);
        return true;
    }
    return false;
}

figure* building::common_spawn_goods_output_cartpusher(int min_carry, int max_carry) {
    // can only have one?
    if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return nullptr;
    }

    // no checking for work force? doesn't matter anyways.... there's no instance
    // in the game that allows cartpushers to spawn before the workers disappear!
    if (!has_road_access) {
        return nullptr;
    }

    while (stored_amount_first >= min_carry) {
        int amounts_to_carry = std::min<int>(stored_amount_first, max_carry);
        amounts_to_carry -= amounts_to_carry % 100; // remove pittance

        figure* f = create_cartpusher(output.resource, amounts_to_carry);
        stored_amount_first -= amounts_to_carry;
        return f;
    }

    return nullptr;
}

void building::common_spawn_labor_seeker(int min_houses) {
    if (g_city.population.current <= 0) {
        return;
    }

    if (!!game_features::gameplay_change_global_labour) {
        // If it can access kingdome
        houses_covered = std::min(300, distance_from_entry ? 2 * min_houses : 0);
        return;
    }

    if (houses_covered > min_houses) {
        return;
    }

    if (has_figure(BUILDING_SLOT_LABOR_SEEKER)) { // no figure slot available!
        return;
    }

    create_roaming_figure(FIGURE_LABOR_SEEKER, FIGURE_ACTION_125_ROAMING, BUILDING_SLOT_LABOR_SEEKER);
}

void building::check_labor_problem() {
    if ((houses_covered <= 0 && labor_category != LABOR_CATEGORY_INVALID) || (labor_category == LABOR_CATEGORY_INVALID && num_workers <= 0)) {
        show_on_problem_overlay = 2;
    }
}

int building::worker_percentage() const {
    return calc_percentage<int>(num_workers, max_workers);
}

int building::figure_spawn_timer() {
    int pct_workers = worker_percentage();
    if (pct_workers >= 100) {
        return 0;
    } else if (pct_workers >= 75) {
        return 1;
    } else if (pct_workers >= 50) {
        return 3;
    } else if (pct_workers >= 25) {
        return 7;
    } else if (pct_workers >= 1) {
        return 15;
    } else {
        return -1;
    }
}

bool building::has_figure(int i, figure *f) {
    return has_figure(i, f->id);
}

bool building::has_figure_of_type(int i, e_figure_type _type) {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        bool has_any = false;
        for (int i = 0; i < max_figures; i++) {
            if (get_figure(i)->type == _type) {
                has_any = true;
            }
        }

        return has_any;
    } else {
        return (get_figure(i)->type == _type);
    }
}

int building::get_figure_slot(figure *f) {
    // search through all the slots, check if figure matches
    for (int i = 0; i < max_figures; i++) {
        if (has_figure(i, f)) {
            return i;
        }
    }
    return -1;
}

void building::set_figure(int i, int figure_id) {
    //assert(figure_ids_array[i] == 0);
    figure_ids[i] = figure_id;
}

void building::set_figure(int i, figure *f) {
    set_figure(i, f ? f->id : 0);
}

void building::remove_figure(int i) {
    set_figure(i, 0);
}

void building::remove_figure_by_id(int id) {
    for (auto &fid : figure_ids) {
        if (fid == id) {
            fid = 0;
        }
    }
}

figure *building::get_figure(int i) const {
    return ::figure_get(get_figure_id(i));
}

bool building::has_figure(int i, int figure_id) const {
    // seatrch through all the figures if index is -1
    if (i == -1) {
        assert(figure_id > 0);
        for (int i = 0; i < max_figures; i++) {
            figure* f = this->get_figure(i);
            if (f->id == figure_id) {
                return true;
            }
        }
        return false;
    } 

    figure *f = this->get_figure(i);
    if (figure_id == -1) {
        return f->id > 0;
    }

    return (f->id == figure_id);
}

///////////////

bool building_is_fort(int type) {
    return type == BUILDING_FORT_CHARIOTEERS || type == BUILDING_FORT_ARCHERS || type == BUILDING_FORT_INFANTRY;
}

bool building_is_defense(e_building_type type) {
    return building_type_any_of(type, { BUILDING_BRICK_WALL, BUILDING_BRICK_GATEHOUSE, BUILDING_BRICK_TOWER });
}

bool building_is_farm(e_building_type type) {
    return (type >= BUILDING_BARLEY_FARM && type <= BUILDING_CHICKPEAS_FARM) || type == BUILDING_FIGS_FARM
           || type == BUILDING_HENNA_FARM;
}

bool building_is_floodplain_farm(building &b) {
    return (building_is_farm(b.type) && map_terrain_is(b.tile.grid_offset(), TERRAIN_FLOODPLAIN));
}

bool building_is_workshop(int type) {
    return (type >= BUILDING_BREWERY_WORKSHOP && type <= BUILDING_POTTERY_WORKSHOP)
           || (type >= BUILDING_PAPYRUS_WORKSHOP && type <= BUILDING_CHARIOTS_WORKSHOP) || type == BUILDING_CATTLE_RANCH
           || type == BUILDING_LAMP_WORKSHOP || type == BUILDING_PAINT_WORKSHOP;
}

bool building_is_extractor(int type) {
    return (type == BUILDING_STONE_QUARRY || type == BUILDING_LIMESTONE_QUARRY || type == BUILDING_CLAY_PIT)
           || type == BUILDING_GOLD_MINE || type == BUILDING_GEMSTONE_MINE || type == BUILDING_COPPER_MINE
           || type == BUILDING_GRANITE_QUARRY || type == BUILDING_SANDSTONE_QUARRY;
}

bool building_is_harvester(e_building_type type) {
    return (type == BUILDING_REED_GATHERER || type == BUILDING_WOOD_CUTTERS);
}

bool building_is_monument(e_building_type type) {
    switch (type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_SIDE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_MEDIUM_MASTABA_SIDE:
    case BUILDING_MEDIUM_MASTABA_WALL:
    case BUILDING_MEDIUM_MASTABA_ENTRANCE:
    case BUILDING_PYRAMID:
    case BUILDING_SPHINX:
    case BUILDING_MAUSOLEUM:
    case BUILDING_ALEXANDRIA_LIBRARY:
    case BUILDING_CAESAREUM:
    case BUILDING_PHAROS_LIGHTHOUSE:
    case BUILDING_SMALL_ROYAL_TOMB:
    case BUILDING_ABU_SIMBEL:
    case BUILDING_MEDIUM_ROYAL_TOMB:
    case BUILDING_LARGE_ROYAL_TOMB:
    case BUILDING_GRAND_ROYAL_TOMB:
    case BUILDING_SUN_TEMPLE:
        return true;

    default:
        return false;
    }
}

bool building_is_palace(e_building_type type) {
    return building_type_any_of(type, { BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE });
}

bool building_is_tax_collector(e_building_type type) {
    return building_type_any_of(type, { BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED });
}

bool building_is_governor_mansion(e_building_type type) {
    return (type >= BUILDING_PERSONAL_MANSION && type <= BUILDING_DYNASTY_MANSION);
}

bool building_is_temple(e_building_type type) {
    return (type >= BUILDING_TEMPLE_OSIRIS && type <= BUILDING_TEMPLE_BAST);
}

bool building_is_temple_complex(e_building_type type) {
    return (type >= BUILDING_TEMPLE_COMPLEX_OSIRIS && type <= BUILDING_TEMPLE_COMPLEX_BAST);
}

bool building_is_shrine(e_building_type type) {
    return (type >= BUILDING_SHRINE_OSIRIS && type <= BUILDING_SHRINE_BAST);
}
bool building_is_guild(e_building_type type) {
    return building_type_any_of(type, { BUILDING_CARPENTERS_GUILD, BUILDING_STONEMASONS_GUILD, BUILDING_BRICKLAYERS_GUILD });
}
bool building_is_statue(e_building_type type) {
    return (type >= BUILDING_SMALL_STATUE && type <= BUILDING_LARGE_STATUE);
}
bool building_is_beautification(e_building_type type) {
    return building_is_statue(type) || type == BUILDING_GARDENS || type == BUILDING_PLAZA;
}
bool building_is_water_crossing(e_building_type type) {
    return (type == BUILDING_FERRY) || type == BUILDING_LOW_BRIDGE || type == BUILDING_UNUSED_SHIP_BRIDGE_83;
}

bool building_is_industry_type(building* b) {
    return b->output.resource || b->dcast_industry();
}

bool building_is_industry(e_building_type type) {
    if (building_is_extractor(type))
        return true;
    if (building_is_harvester(type))
        return true;
    if (building_is_workshop(type))
        return true;
    if (building_is_farm(type))
        return true;
    if (building_is_guild(type))
        return true;
    if (type == BUILDING_DOCK || type == BUILDING_SHIPWRIGHT)
        return true;
    if (type == BUILDING_STORAGE_YARD || type == BUILDING_STORAGE_ROOM)
        return true;
    return false;
}

bool building_is_food_category(e_building_type type) {
    if (building_is_farm(type)) { // special case for food-producing farms
        return (type >= BUILDING_GRAIN_FARM && type <= BUILDING_CHICKPEAS_FARM) || type == BUILDING_FIGS_FARM;
    }

    if (type == BUILDING_GRANARY || type == BUILDING_BAZAAR || type == BUILDING_WORK_CAMP
        || type == BUILDING_FISHING_WHARF || type == BUILDING_CATTLE_RANCH || type == BUILDING_HUNTING_LODGE) {
        return true;
    }

    return false;
}

bool building_is_infrastructure(e_building_type type) {
    if (type == BUILDING_ARCHITECT_POST || type == BUILDING_FIREHOUSE || type == BUILDING_POLICE_STATION)
        return true;

    if (building_is_water_crossing(type))
        return true;

    return false;
}

bool building_is_administration(e_building_type type) {
    if (building_is_palace(type) || building_is_tax_collector(type) || building_is_governor_mansion(type)) {
        return true;
    }

    if (type == BUILDING_COURTHOUSE) {
        return true;
    }

    return false;
}

bool building_is_religion(e_building_type type) {
    if (building_is_temple(type) || building_is_temple_complex(type) || building_is_shrine(type)) {
        return true;
    }

    if (type == BUILDING_FESTIVAL_SQUARE) {
        return true;
    }

    return false;
}

bool building_is_entertainment(e_building_type type) {
    if (type == BUILDING_BOOTH || type == BUILDING_BANDSTAND || type == BUILDING_PAVILLION) {
        return true;
    }

    if (type == BUILDING_JUGGLER_SCHOOL || type == BUILDING_CONSERVATORY || type == BUILDING_DANCE_SCHOOL) {
        return true;
    }

    if (type == BUILDING_SENET_HOUSE || type == BUILDING_ZOO) {
        return true;
    }

    return false;
}

bool building_is_education(e_building_type type) {
    return building_type_any_of(type, { BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ACADEMY });
}

bool building_is_military(e_building_type type) {
    if (building_is_fort(type)) {
        return true;
    }
    
    if (building_type_any_of(type, { BUILDING_MILITARY_ACADEMY, BUILDING_RECRUITER, BUILDING_FORT_GROUND })) {
        return true;
    }
    
    return false;
}

bool building_is_draggable(e_building_type type) {
    if (BUILDING_CLEAR_LAND == type) {
        return true;
    }

    return building_static_params::get(type).planner_update_rule.is_draggable;
}

int building::mothball_toggle() {
    if (state == BUILDING_STATE_VALID) {
        state = BUILDING_STATE_MOTHBALLED;
        num_workers = 0;
    } else if (state == BUILDING_STATE_MOTHBALLED) {
        state = BUILDING_STATE_VALID;
    }

    return state;
}

void building_impl::on_place(int orientation, int variant) {
    const auto &p = current_params();
    
    base.fire_proof = p.fire_proof;
    base.damage_proof = p.damage_proof;

    base.output_resource_second_rate = p.output_resource_second_rate;

    on_place_update_tiles(orientation, variant);
    update_graphic();
}

void building_impl::on_place_update_tiles(int orientation, int variant) {
    map_building_tiles_add(id(), tile(), base.size, base_img(), TERRAIN_BUILDING);
}

void building_impl::on_place_checks() {
    // check road access
    switch (type()) {
    case BUILDING_NONE:
    case BUILDING_CLEAR_LAND:
        return;
    }

    construction_warnings warnings;
    const bool has_road = map_has_road_access(tile(), size());
    warnings.add_if(!has_road, "#needs_road_access");

    const bool need_workers = (base.max_workers > 0 && g_city.labor.workers_needed >= 10);
    warnings.add_if(need_workers, "#city_needs_more_workers");
}

void building_impl::update_graphic() {
    base.minimap_anim = anim("minimap");
}

void building_impl::remove_dead_figures() {
    for (int i = 0; i < base.max_figures; i++) {
        figure* f = this->get_figure(i);
        if (f->state != FIGURE_STATE_ALIVE) {
            base.figure_ids[i] = 0;
        }
    }
}

void building_impl::update_day() {
    update_graphic();
    remove_dead_figures();
}

figure *building_impl::get_figure_in_slot(int slot) {
    return figure_get(get_figure_id(slot));
}

bool building_impl::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (!base.anim.key) {
        int image_id = map_image_at(tile.grid_offset());
        building_draw_normal_anim(ctx, point, &base, tile, image_id, color_mask);
    } else {
        draw_normal_anim(ctx, point, tile, color_mask);
    }

    if (base.has_plague) {
        int skull_img = image_id_from_group(GROUP_PLAGUE_SKULL);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = skull_img;
        command.pixel = { point.x + 18, point.y - 32 };
        command.mask = color_mask;
    }

    return false;
}

bool building_impl::can_play_animation() const {
    return base.main()->num_workers > 0;
}

void building_impl::update_count() const {
    g_city.buildings.increase_count(base.type, base.num_workers > 0);
}

void building_impl::draw_normal_anim(painter &ctx, vec2i pixel, tile2i tile, color mask) {
    if (!can_play_animation()) {
        return;
    }

    draw_normal_anim(ctx, base.anim, pixel, tile, mask);
}

void building_impl::draw_normal_anim(painter &ctx, const animation_context &ranim, vec2i pixel, tile2i tile, color mask) {
    if (!ranim.valid()) {
        return;
    }

    vec2i pos = pixel + ranim.pos;
    auto &command = ImageDraw::create_subcommand(render_command_t::ert_generic);
    command.image_id = ranim.start_frame() + ranim.current_frame();
    command.pixel = pos;
    command.mask = mask;
    command.flags = ranim.flags;
}

void building_impl::bind_dynamic(io_buffer *iob, size_t version) {
    assert(base.output.resource == current_params().output.resource);
}

const bproperty bproperties[] = {
    { tags().stored, xstring("*"),
        [] (building &b, const xstring &name) {
            e_resource res = resource_type(name);
            return bvariant(b.stored_amount(res));
        }
    },

    { tags().text, xstring("*"),
        [] (building &b, const xstring &name) {
             int id = atoi(name.c_str());
             const auto &m = building_static_params::get(b.type).meta;
             return bvariant(ui::str(m.text_id, id));
        }
    },

    { tags().building, tags().name, [] (building &b, const xstring &) { return bvariant(b.cls_name()); }},
    { tags().building, tags().num_workers, [] (building &b, const xstring &) { return bvariant(b.num_workers); }},
    { tags().model, tags().laborers, [] (building &b, const xstring &) { return bvariant(b.max_workers); }},
    { tags().building, tags().output_resource, [] (building &b, const xstring &) { return bvariant(resource_name(b.output.resource)); }},
    { tags().building, tags().second_output_resource, [] (building &b, const xstring &) { return bvariant(resource_name(b.output.resource_second)); }},
    { tags().building, tags().first_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.input.resource)); }},
    { tags().building, tags().first_material_stored, [] (building &b, const xstring &) { return bvariant(b.stored_amount_first); }},
    { tags().building, tags().second_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.input.resource_second)); }},
    { tags().building, tags().second_material_stored, [] (building &b, const xstring &) { return bvariant(b.stored_amount_second); }},
    { tags().farm, tags().fertility, [] (building &b, const xstring &) { return bvariant(map_get_fertility_for_farm(b.tile.grid_offset())); }},
};

bvariant building_impl::get_property(const xstring &domain, const xstring &name) const {
    static const xstring wildname("*");
    for (const auto &prop: bproperties) {
        if (prop.domain != domain) {
            continue;
        }

        if (prop.name == name || prop.name == wildname) {
            return prop.handler(base, name);
        }
    }

    return bvariant();
}

void building_impl::destroy_by_poof(bool clouds) {
    building_destroy_by_poof(&base, clouds);
}

void building_impl::highlight_waypoints() { // highlight the 4 routing tiles for roams from this building
    map_clear_highlights();
    if (has_road_access()) {
        map_highlight_set(base.road_access, ehighligth_red);
    }

    int hx, hy;
    hx = tilex();
    hy = tiley() - 8;
    map_grid_bound(&hx, &hy);
    tile2i road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex() + 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex();
    hy = tiley() + 8;
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex() - 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }
}

void building_impl::on_tick(bool refresh_only) {
    if (!base.anim.valid()) {
        return;
    }

    base.anim.update(refresh_only);
}

void building_static_params::archive_unload() {
}

void building_static_params::initialize() {
    if (production_rate == 0 ) production_rate = 100;
    if (min_houses_coverage == 0) min_houses_coverage = 100;

    city_labor_t::set_category(type, labor_category);
}

void add_building(building *b, int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    const auto &params = b->params();
    switch (b->type) {
        // houses
    case BUILDING_HOUSE_STURDY_HUT:
    case BUILDING_HOUSE_MEAGER_SHANTY:
    case BUILDING_HOUSE_COMMON_SHANTY:
    case BUILDING_HOUSE_ROUGH_COTTAGE:
    case BUILDING_HOUSE_ORDINARY_COTTAGE:
    case BUILDING_HOUSE_MODEST_HOMESTEAD:
    case BUILDING_HOUSE_SPACIOUS_HOMESTEAD:
    case BUILDING_HOUSE_MODEST_APARTMENT:
    case BUILDING_HOUSE_SPACIOUS_APARTMENT:
    case BUILDING_HOUSE_COMMON_RESIDENCE:
    case BUILDING_HOUSE_SPACIOUS_RESIDENCE:
    case BUILDING_HOUSE_ELEGANT_RESIDENCE:
    case BUILDING_HOUSE_FANCY_RESIDENCE:
    case BUILDING_HOUSE_COMMON_MANOR:
    case BUILDING_HOUSE_SPACIOUS_MANOR:
    case BUILDING_HOUSE_ELEGANT_MANOR:
    case BUILDING_HOUSE_STATELY_MANOR:
    case BUILDING_HOUSE_MODEST_ESTATE:
    case BUILDING_HOUSE_PALATIAL_ESTATE:
        //add_building_tiles_image(b, params.anim["house"].first_img());
        {
            int image_id = params.animations["house"].first_img();
            map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
        }
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        //add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH) + orientation - 1);
        {
            int image_id = image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH) + orientation - 1;
            map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
        }
        map_terrain_add_triumphal_arch_roads(b->tile.x(), b->tile.y(), orientation);
        city_buildings_build_triumphal_arch();
        g_city_planner.reset();
        break;

    default:
        b->dcast()->on_place(orientation, variant);
        break;
    }
}

bool building_planer_renderer::is_need_flag(build_planner &planer, e_building_flags flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &needs = params.needs;
    switch (flag) {
    case e_building_flag::Meadow: return needs.meadow;
    case e_building_flag::Rock: return needs.rock;
    case e_building_flag::Ore: return needs.ore;
    case e_building_flag::TempleUpgradeAltar: return needs.altar;
    case e_building_flag::TempleUpgradeOracle: return needs.oracle;
    case e_building_flag::NearbyWater: return needs.nearby_water;
    case e_building_flag::Groundwater: return needs.groundwater;
    case e_building_flag::ShoreLine: return needs.shoreline;
    case e_building_flag::Canals: return needs.canals;
    case e_building_flag::FloodplainShore: return needs.floodplain_shoreline;
    }

    return false;
}

bool building_planer_renderer::ghost_allow_tile(build_planner &p, tile2i tile) const {
    return (map_has_figure_at(tile) == false);
};
const building_planer_renderer building_planer_renderer::dummy;

void building_planer_renderer::register_model(e_building_type e, const building_planer_renderer &p) {
    if (!building_planer_rends) {
        building_planer_rends = new std::array<const building_planer_renderer *, BUILDING_MAX>();
        std::fill(building_planer_rends->begin(), building_planer_rends->end(), nullptr);
    }
    (*building_planer_rends)[e] = &p;
}

void building_planer_renderer::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    for (int row = 0; row < planer.size.y; row++) {
        for (int column = 0; column < planer.size.x; column++) {
            vec2i current_coord = planer.pixel_coord_offset(row, column);
            color color_mask = (planer.is_blocked_tile(row, column) || fully_blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
            planer.draw_flat_tile(current_coord, color_mask, ctx);
        }
    }
}

void building_planer_renderer::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    planer.draw_tile_graphics_array(ctx, start, end, pixel);
}

int building_planer_renderer::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    // by default, get size from building's properties
    const auto &params = building_static_params::get(planer.build_type);
    assert(params.building_size > 0);

    // correct building placement for city orientations
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        end = end.shifted(-params.building_size + 1, 0);
        break;

    case DIR_4_BOTTOM_LEFT:
        end = end.shifted(-params.building_size + 1, -params.building_size + 1);
        break;

    case DIR_6_TOP_LEFT:
        end = end.shifted(0, -params.building_size + 1);
        break;
    }

    // create building
    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, end, orientation);
    game_undo_add_building(b);
    if (b->id <= 0) { // building creation failed????
        return 0;
    }

    add_building(b, orientation, variant);
    planer.last_created_building = b;

    return 1;
}

int building_planer_renderer::update_building_variant(build_planner &planer) const {
    return planer.building_variant;
}

int building_planer_renderer::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    int special_flags = planer.special_flags;
    if ((special_flags & e_building_flag::Meadow) || (special_flags & e_building_flag::Rock)
        || (special_flags & e_building_flag::Trees) || (special_flags & e_building_flag::NearbyWater)
        || (special_flags & e_building_flag::Walls) || (special_flags & e_building_flag::Groundwater)
        || (special_flags & e_building_flag::Water) || (special_flags & e_building_flag::ShoreLine)
        || (special_flags & e_building_flag::Road) || (special_flags & e_building_flag::Intersection)) {
        return 0;
    }

    int real_orientation = (city_view_orientation() / 2) % 2;
    if (real_orientation == 0) {
        planer.mark_construction(planer.north_tile, planer.size, TERRAIN_ALL, true);
    } else {
        planer.mark_construction(planer.north_tile, planer.size, TERRAIN_ALL, true);
    }

    return 0;
}


void building_planer_renderer::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    int img_id = params.base_img();
    if (!img_id) {
        img_id = params.first_img(animkeys().preview);
    }
    img_id += params.planner_update_rule.relative_orientation * planer.relative_orientation;
    planer.set_tiles_building(img_id, params.building_size);
}

const building_planer_renderer &building_planer_renderer::get(e_building_type e) {
    auto p = building_planer_rends->at(e);
    return (p == nullptr) ? building_planer_renderer::dummy : *p;
}

uint16_t building_static_params::get_cost() const {
    const uint16_t mcost = this->cost.get();
    return mcost;
}

io_buffer* iob_building_highest_id = new io_buffer([](io_buffer* iob, size_t version) {
    //iob->bind(BIND_SIGNATURE_INT32, &building_extra_data.highest_id_in_use);
    iob->bind____skip(4);
});

io_buffer* iob_building_highest_id_ever = new io_buffer([](io_buffer* iob, size_t version) {
    //iob->bind(BIND_SIGNATURE_INT32, &building_extra_data.highest_id_ever);
    iob->bind____skip(4);
    iob->bind____skip(4);
    //    highest_id_ever->skip(4);
});