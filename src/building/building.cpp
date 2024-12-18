#include "building.h"

#include "building/rotation.h"
#include "building/building_type.h"
#include "building/building_storage.h"
#include "building/count.h"
#include "building/destruction.h"
#include "city/buildings.h"
#include "city/population.h"
#include "city/warnings.h"
#include "widget/city/ornaments.h"
#include "city/warning.h"
#include "core/svector.h"
#include "core/profiler.h"
#include "figure/formation_legion.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/random.h"
#include "grid/image.h"
#include "grid/routing/routing_terrain.h"
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
#include "config/config.h"

#include <string.h>
#include <map>

#include "dev/debug.h"
#include <iostream>

declare_console_command_p(destroytype, game_cheat_destroy_type)
void game_cheat_destroy_type(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int type = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    
    buildings_valid_do([] (building &b) {
        building_destroy_by_collapse(&b);
    }, (e_building_type)type);
};

const token_holder<e_building_state, BUILDING_STATE_UNUSED, BUILDING_STATE_COUNT> e_building_state_tokens;
const token_holder<e_building_type, BUILDING_NONE, BUILDING_MAX> e_building_type_tokens;
static std::array<const building_impl::static_params *, BUILDING_MAX> *building_impl_params = nullptr;

building_impl::static_params building_impl::static_params::dummy;

void building::new_fill_in_data_for_type(e_building_type _tp, tile2i _tl, int orientation) {
    assert(!_ptr);
    const auto &props = building_impl::params(_tp);
    type = _tp;
    tile = _tl;
    state = BUILDING_STATE_CREATED;
    faction_id = 1;
    reserved_id = false; // city_buildings_unknown_value();
    size = props.building_size;
    //creation_sequence_index = building_extra_data.created_sequence++;
    sentiment.house_happiness = 50;
    distance_from_entry = 0;

    map_random_7bit = map_random_get(tile.grid_offset()) & 0x7f;
    figure_roam_direction = map_random_7bit & 6;
    fire_proof = props.fire_proof;
    damage_proof = props.damage_proof;
    is_adjacent_to_water = map_terrain_is_adjacent_to_water(tile, size);

    // house size
    house_size = 0;
    if (type >= BUILDING_HOUSE_CRUDE_HUT && type <= BUILDING_HOUSE_SPACIOUS_APARTMENT) {
        house_size = 1;
    } else if (type >= BUILDING_HOUSE_COMMON_RESIDENCE && type <= BUILDING_HOUSE_FANCY_RESIDENCE) {
        house_size = 2;
    } else if (type >= BUILDING_HOUSE_COMMON_MANOR && type <= BUILDING_HOUSE_STATELY_MANOR) {
        house_size = 3;
    } else if (type >= BUILDING_HOUSE_MODEST_ESTATE && type <= BUILDING_HOUSE_PALATIAL_ESTATE) {
        house_size = 4;
    }

    // subtype
    if (is_house()) {
        subtype.house_level = (e_house_level)(type - BUILDING_HOUSE_VACANT_LOT);
    } else {
        subtype.house_level = HOUSE_CRUDE_HUT;
    }

    // unique data
    switch (type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        data.monuments.variant = (10 - (2 * orientation)) % 8; // ugh!
        break;

    default:
        output_resource_first_id = RESOURCE_NONE;
        dcast()->on_create(orientation);
        break;
    }
}

void building::monument_remove_worker(int fid) {
    for (auto &wid : data.monuments.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

building_impl *buildings::create(e_building_type e, building &data) {
    for (BuildingCtorIterator *s = BuildingCtorIterator::tail; s; s = s->next) {
        auto impl = s->func(e, data);
        if (impl) {
            return impl;
        }
    }

    return new building_impl(data);
}

bool building_impl::required_resource(e_resource r) const {
    return base.first_material_id == r || base.second_material_id == r;
}

resource_vec building_impl::required_resources() const { 
    if (base.first_material_id == RESOURCE_NONE && base.second_material_id == RESOURCE_NONE) {
        return {}; 
    }

    resource_vec r;
    if (base.first_material_id != RESOURCE_NONE) {
        r.push_back(base.first_material_id);
    }

    if (base.second_material_id != RESOURCE_NONE) {
        r.push_back(base.second_material_id);
    }

    return r;
}

metainfo building_impl::get_info() const {
    const auto &metainfo = !params().meta_id.empty()
                                ? base.get_info(params().meta_id)
                                : params().meta;
    return metainfo;
}

void building_impl::set_animation(const animation_t &anim) {
    base.anim.setup(anim);
}

vfs::path building_impl::get_sound() {
    return snd::get_building_info_sound(type());
}

void building_impl::params(e_building_type e, const static_params &p) {
    if (!building_impl_params) {
        building_impl_params = new std::array<const building_impl::static_params *, BUILDING_MAX>();
        std::fill(building_impl_params->begin(), building_impl_params->end(), nullptr);
    }
    (*building_impl_params)[e] = &p;
}

const building_impl::static_params &building_impl::params(e_building_type e) {
    auto p = building_impl_params->at(e);
    return (p == nullptr) ? building_impl::static_params::dummy : *p;
}

building_impl *building::dcast() {
    if (!_ptr) {
        _ptr = buildings::create(type, *this);
    }
    assert(!!_ptr);
    return _ptr;
}

building_farm *building::dcast_farm() { return dcast()->dcast_farm(); }
building_brewery *building::dcast_brewery() { return dcast()->dcast_brewery(); }
building_pottery *building::dcast_pottery() { return dcast()->dcast_pottery(); }
building_storage_yard *building::dcast_storage_yard() { return dcast()->dcast_storage_yard(); }
building_storage_room *building::dcast_storage_room() { return dcast()->dcast_storage_room(); }
building_juggler_school *building::dcast_juggler_school() { return dcast()->dcast_juggler_school(); }
building_bazaar *building::dcast_bazaar() { return dcast()->dcast_bazaar(); }
building_firehouse *building::dcast_firehouse() { return dcast()->dcast_firehouse(); }
building_architect_post *building::dcast_architect_post() { return dcast()->dcast_architect_post(); }
building_booth *building::dcast_booth() { return dcast()->dcast_booth(); }
building_apothecary *building::dcast_apothecary() { return dcast()->dcast_apothecary(); }
building_granary *building::dcast_granary() { return dcast()->dcast_granary(); }
building_water_supply *building::dcast_water_supply() { return dcast()->dcast_water_supply(); }
building_conservatory *building::dcast_conservatory() { return dcast()->dcast_conservatory(); }
building_courthouse *building::dcast_courthouse() { return dcast()->dcast_courthouse(); }
building_well *building::dcast_well() { return dcast()->dcast_well(); }
building_clay_pit *building::dcast_clay_pit() { return dcast()->dcast_clay_pit(); }
building_reed_gatherer *building::dcast_reed_gatherer() { return dcast()->dcast_reed_gatherer(); }
building_papyrus_maker *building::dcast_papyrus_maker() { return dcast()->dcast_papyrus_maker(); }
building_dock *building::dcast_dock() { return dcast()->dcast_dock(); }
building_work_camp *building::dcast_work_camp() { return dcast()->dcast_work_camp(); }
building_small_mastaba *building::dcast_small_mastaba() { return dcast()->dcast_small_mastaba(); }
building_wood_cutter *building::dcast_wood_cutter() { return dcast()->dcast_wood_cutter(); }
building_recruiter *building::dcast_recruiter() { return dcast()->dcast_recruiter(); }
building_pavilion *building::dcast_pavilion() { return dcast()->dcast_pavilion(); }
building_statue *building::dcast_statue() { return dcast()->dcast_statue(); }
building_ferry *building::dcast_ferry() { return dcast()->dcast_ferry(); }
building_fort *building::dcast_fort() { return dcast()->dcast_fort(); }
building_fort_ground *building::dcast_fort_ground() { return dcast()->dcast_fort_ground(); }
building_fishing_wharf *building::dcast_fishing_wharf() { return dcast()->dcast_fishing_wharf(); }
building_shipyard *building::dcast_shipyard() { return dcast()->dcast_shipyard(); }
building_plaza *building::dcast_plaza() { return dcast()->dcast_plaza(); }
building_garden *building::dcast_garden() { return dcast()->dcast_garden(); }
building_house *building::dcast_house() { return dcast()->dcast_house(); }
building_burning_ruin *building::dcast_burning_ruin() { return dcast()->dcast_burning_ruin(); }
building_storage *building::dcast_storage() { return dcast()->dcast_storage(); }
building_temple *building::dcast_temple() { return dcast()->dcast_temple(); }
building_tax_collector *building::dcast_tax_collector() { return dcast()->dcast_tax_collector(); }
building_roadblock *building::dcast_roadblock() { return dcast()->dcast_roadblock(); }
building_routeblock *building::dcast_routeblock() { return dcast()->dcast_routeblock(); }
building_mine *building::dcast_mine() { return dcast()->dcast_mine(); }
building_quarry *building::dcast_quarry() { return dcast()->dcast_quarry(); }
building_palace *building::dcast_palace() { return dcast()->dcast_palace(); }
building_festival_square *building::dcast_festival_square() { return dcast()->dcast_festival_square(); }
building_bandstand *building::dcast_bandstand() { return dcast()->dcast_bandstand(); }
building_industry *building::dcast_industry() { return dcast()->dcast_industry(); }
building_guild *building::dcast_guild() { return dcast()->dcast_guild(); }
building_entertainment *building::dcast_entertainment() { return dcast()->dcast_entertainment(); }
building_mansion *building::dcast_mansion() { return dcast()->dcast_mansion(); }
building_physician *building::dcast_physician() { return dcast()->dcast_physician(); }
building_wharf *building::dcast_wharf() { return dcast()->dcast_wharf(); }
building_warship_wharf *building::dcast_warship_wharf() { return dcast()->dcast_warship_wharf(); }

building::building() {
}

void building::industry_add_workers(int fid) {
    data.industry.worker_id = fid;
}

void building::industry_remove_worker(int fid) {
    if (data.industry.worker_id == id) {
        data.industry.worker_id = 0;
    }
}

void building::monument_add_workers(int fid) {
    for (auto &wid : data.monuments.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

building* building::main() {
    building* b = this;
    for (int guard = 0; guard < 99; guard++) {
        if (b->prev_part_building_id <= 0)
            return b;
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
    delete _ptr;
    _ptr = nullptr;
}

void building::reset_impl() {
    _ptr = nullptr;
}


vfs::path building::get_sound() {
    return snd::get_building_info_sound(type);
}

void building::clear_related_data() {
    if (storage_id) {
        building_storage_delete(storage_id);
        storage_id = 0;
    }

    if (is_governor_mansion()) {
        city_buildings_remove_mansion(this);
    }

    if (type == BUILDING_RECRUITER) {
        city_buildings_remove_recruiter(this);
    }

    if (type == BUILDING_DISTRIBUTION_CENTER_UNUSED)
        city_buildings_remove_distribution_center(this);

    if (building_is_fort(type)) {
        formation_legion_delete_for_fort(this);
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

bool building::is_house() {
    return building_is_house(type);
}
bool building::is_fort() {
    return building_is_fort(type);
}
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
bool building::is_governor_mansion() {
    return building_is_governor_mansion(type);
}
bool building::is_temple() {
    return building_is_temple(type);
}
bool building::is_large_temple() {
    return building_is_large_temple(type);
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
    cart->set_destination(0);
    cart->base.immigrant_home_building_id = 0;

    set_figure(slot, cart->id()); // warning: this overwrites any existing figure!
    if (config_get(CONFIG_GP_CH_CART_SPEED_QUANTITY)) {
        f->progress_inside_speed = std::clamp(quantity / 400, 0, 2);
    }
    cart->wait_ticks = 30;

    return f;
}

figure *building::create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action, e_building_slot slot) {
    figure *f = create_figure_generic(_type, created_action, slot, DIR_4_BOTTOM_LEFT);
    f->set_destination(destination->id);
    f->immigrant_home_building_id = 0;

    set_figure(slot, f->id); // warning: this overwrites any existing figure!
    return f;
}

figure *building::create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) {
    figure *f = create_figure_generic(_type, created_action, slot, figure_roam_direction);

    f->set_destination(0);
    f->immigrant_home_building_id = 0;

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
    if (first_material_id == res) {
        return stored_amount_first;
    }

    if (second_material_id == res) {
        return stored_amount_second;
    }

    if (output_resource_first_id == res) {
        return data.industry.ready_production;
    }

    // todo: dalerank, temporary, building should return own resource type only
    return stored_amount_first;
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

bool building::guild_has_resources() {
    assert(is_guild());
    bool hase_first_resource = (stored_amount_first >= 100);
    return hase_first_resource;
}

bool building::workshop_has_resources() {
    assert(is_workshop());
    bool has_second_material = true;
    if (second_material_id != RESOURCE_NONE) {
        has_second_material = (stored_amount_second > 100);
    }

    bool hase_first_resource = (stored_amount_first >= 100);
    return has_second_material && hase_first_resource;
}

void building::workshop_start_production() {
    assert(is_workshop());
    bool can_start_b = false;
    if (second_material_id != RESOURCE_NONE) {
        can_start_b = (stored_amount_second >= 100);
    } else {
        can_start_b = true;
    }

    bool can_start_a = (stored_amount_first >= 100);
    if (can_start_b && can_start_a) {
        data.industry.has_raw_materials = true;
        if (stored_amount_second >= 100) {
            stored_amount_second -= 100;
        }
        if (stored_amount_first >= 100) {
            stored_amount_first -= 100;
        }
    }
}

tile2i building::access_tile() {
    switch (type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_SIDE:
        return main()->tile.shifted(0, 10);
    }

    return road_access;
}

///////////////

bool building_is_fort(int type) {
    return type == BUILDING_FORT_CHARIOTEERS || type == BUILDING_FORT_ARCHERS || type == BUILDING_FORT_INFANTRY;
}

bool building_is_defense(e_building_type type) {
    return building_type_any_of(type, BUILDING_BRICK_WALL, BUILDING_BRICK_GATEHOUSE, BUILDING_BRICK_TOWER);
}

bool building_is_farm(e_building_type type) {
    return (type >= BUILDING_BARLEY_FARM && type <= BUILDING_CHICKPEAS_FARM) || type == BUILDING_FIGS_FARM
           || type == BUILDING_HENNA_FARM;
}

bool building_is_floodplain_farm(building &b) {
    return (building_is_farm(b.type) && map_terrain_is(b.tile.grid_offset(), TERRAIN_FLOODPLAIN)); // b->data.industry.labor_state >= 1 // b->labor_category == 255
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

bool building_is_monument(int type) {
    switch (type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_SIDE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
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
    return building_type_any_of(type, BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE);
}

bool building_is_tax_collector(e_building_type type) {
    return building_type_any_of(type, BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED);
}

bool building_is_governor_mansion(e_building_type type) {
    return (type >= BUILDING_PERSONAL_MANSION && type <= BUILDING_DYNASTY_MANSION);
}

bool building_is_temple(int type) {
    return (type >= BUILDING_TEMPLE_OSIRIS && type <= BUILDING_TEMPLE_BAST);
}

bool building_is_large_temple(int type) {
    return (type >= BUILDING_TEMPLE_COMPLEX_OSIRIS && type <= BUILDING_TEMPLE_COMPLEX_BAST);
}

bool building_is_shrine(int type) {
    return (type >= BUILDING_SHRINE_OSIRIS && type <= BUILDING_SHRINE_BAST);
}
bool building_is_guild(e_building_type type) {
    return building_type_any_of(type, BUILDING_CARPENTERS_GUILD, BUILDING_STONEMASONS_GUILD, BUILDING_BRICKLAYERS_GUILD);
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
    return b->output_resource_first_id || b->dcast_industry();
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
    if (building_is_temple(type) || building_is_large_temple(type) || building_is_shrine(type)) {
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
    return building_type_any_of(type, BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ACADEMY);
}

bool building_is_military(e_building_type type) {
    if (building_is_fort(type)) {
        return true;
    }
    
    if (building_type_any_of(BUILDING_MILITARY_ACADEMY, BUILDING_RECRUITER, BUILDING_FORT_GROUND)) {
        return true;
    }
    
    return false;
}

bool building_is_draggable(e_building_type type) {
    switch (type) {
    case BUILDING_CLEAR_LAND:
    case BUILDING_IRRIGATION_DITCH:
    case BUILDING_MUD_WALL:
        return true;

    default:
        return building_impl::params(type).is_draggable;
    }
}

int building_mothball_toggle(building* b) {
    if (b->state == BUILDING_STATE_VALID) {
        b->state = BUILDING_STATE_MOTHBALLED;
        b->num_workers = 0;
    } else if (b->state == BUILDING_STATE_MOTHBALLED) {
        b->state = BUILDING_STATE_VALID;
    }

    return b->state;
}

int building_mothball_set(building* b, int mothball) {
    if (mothball) {
        if (b->state == BUILDING_STATE_VALID) {
            b->state = BUILDING_STATE_MOTHBALLED;
            b->num_workers = 0;
        }
    } else if (b->state == BUILDING_STATE_MOTHBALLED) {
        b->state = BUILDING_STATE_VALID;
    }

    return b->state;
}

void building_impl::on_place(int orientation, int variant) {
    auto &p = params();
    
    base.fire_proof = p.fire_proof;
    base.damage_proof = p.damage_proof;
    if (p.input_resource) {
        base.first_material_id = p.input_resource;
    }

    if (p.input_resource_second) {
        base.second_material_id = p.input_resource_second;
    }

    base.output_resource_first_id = p.output_resource;
    base.output_resource_second_id = p.output_resource_second;
    base.output_resource_second_rate = p.output_resource_second_rate;

    on_place_update_tiles(orientation, variant);
    update_graphic();
}

void building_impl::on_place_update_tiles(int orientation, int variant) {
    int img_id = anim(animkeys().base).first_img();
    map_building_tiles_add(id(), tile(), base.size, img_id, TERRAIN_BUILDING);
}

void building_impl::on_place_checks() {
    // check road access
    switch (type()) {
    case BUILDING_NONE:
    case BUILDING_CLEAR_LAND:
    case BUILDING_IRRIGATION_DITCH:
    case BUILDING_TEMPLE_COMPLEX_ALTAR:
    case BUILDING_TEMPLE_COMPLEX_ORACLE:
        return;

    default:
        ; // nothing
    }

    if (!map_has_road_access(tile(), size())) {
        building_construction_warning_show(WARNING_ROAD_ACCESS_NEEDED);
    }

    if (!building_construction_has_warning()) {
        if (model_get_building(type())->laborers > 0 && g_city.labor.workers_needed >= 10) {
            building_construction_warning_show(WARNING_WORKERS_NEEDED);
        }
    }
}

void building_impl::update_graphic() {
    base.minimap_anim = anim("minimap");
}

void building_impl::update_day() {
    update_graphic();
}

figure *building_impl::get_figure_in_slot(int slot) {
    return figure_get(get_figure_id(slot));
}


bool building_impl::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (!base.anim.id) {
        int image_id = map_image_at(tile.grid_offset());
        building_draw_normal_anim(ctx, point, &base, tile, image_id, color_mask);
    } else {
        draw_normal_anim(ctx, point, tile, color_mask);
    }

    if (base.has_plague) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_PLAGUE_SKULL), point.x + 18, point.y - 32, color_mask);
    }

    return false;
}

bool building_impl::can_play_animation() const {
    return base.main()->num_workers > 0;
}

void building_impl::update_count() const {
    if (!base.house_size) {
        building_increase_type_count(base.type, base.num_workers > 0);
    } else {
        building_increase_type_count(base.type, base.house_size > 0);
    }
}

void building_impl::draw_normal_anim(painter &ctx, vec2i pixel, tile2i tile, color mask) {
    if (!base.anim.valid()) {
        return;
    }

    if (!can_play_animation()) {
        return;
    }

    vec2i pos = pixel + base.anim.pos;
    ImageDraw::img_sprite(ctx, base.anim.start() + base.anim.current_frame(), pos.x, pos.y, mask);
}

void building_impl::bind_dynamic(io_buffer *iob, size_t version) {
    assert(base.output_resource_first_id == RESOURCE_NONE);
}

struct bproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(building &, const xstring &)> handler;
};

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
             const auto &m = building_impl::params(b.type).meta;
             return bvariant(ui::str(m.text_id, id));
        }
    },

    { tags().building, tags().name, [] (building &b, const xstring &) { const auto &m = building_impl::params(b.type).meta; return bvariant(ui::str(m.text_id, 0)); }},
    { tags().building, tags().tax_income_or_storage, [] (building &b, const xstring &) { return bvariant(b.tax_income_or_storage); }},
    { tags().building, tags().num_workers, [] (building &b, const xstring &) { return bvariant(b.num_workers); }},
    { tags().model, tags().laborers, [] (building &b, const xstring &) { const auto model = model_get_building(b.type); return bvariant(model->laborers); }},
    { tags().industry, tags().progress, [] (building &b, const xstring &) { int pct_done = calc_percentage<int>(b.data.industry.progress, b.data.industry.progress_max); return bvariant(pct_done); }},
    { tags().building, tags().output_resource, [] (building &b, const xstring &) { return bvariant(resource_name(b.output_resource_first_id)); }},
    { tags().building, tags().first_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.first_material_id)); }},
    { tags().building, tags().first_material_stored, [] (building &b, const xstring &) { return bvariant(b.stored_amount_first); }},
    { tags().building, tags().second_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.second_material_id)); }},
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

    if (base.house_size) { // building doesn't send roamers
        return;
    }

    int hx, hy;
    hx = tilex();
    hy = tiley() - 8;
    map_grid_bound(&hx, &hy);
    map_point road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
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

void building_impl::static_params::load(archive arch) {
    labor_category = arch.r_type<e_labor_category>("labor_category");
    fire_proof = arch.r_bool("fire_proof");
    damage_proof = arch.r_bool("damage_proof");
    input_resource = arch.r_type<e_resource>("input_resource");
    input_resource_second = arch.r_type<e_resource>("input_resource_second");
    output_resource = arch.r_type<e_resource>("output_resource");
    output_resource_second = arch.r_type<e_resource>("output_resource_second");
    output_resource_second_rate = arch.r_int("output_resource_second_rate");
    meta_id = arch.r_string("meta_id");
    meta.help_id = arch.r_int("info_help_id");
    meta.text_id = arch.r_int("info_text_id");
    window_info_height_id = arch.r_int("window_info_height_id");
    building_size = arch.r_int("building_size");
    unique_building = arch.r_bool("unique_building");
    planer_relative_orientation = arch.r_int("planer_relative_orientation");
    is_draggable = arch.r_bool("is_draggable");
    production_rate = arch.r_uint("production_rate", 100);
    check_water_access = arch.r_bool("check_water_access");

    city_labor_set_category(type, labor_category);

    anim.load(arch);
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