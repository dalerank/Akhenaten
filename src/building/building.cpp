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

building g_all_buildings[5000];
std::span<building> g_city_buildings = make_span(g_all_buildings);

const token_holder<e_building_state, BUILDING_STATE_UNUSED, BUILDING_STATE_COUNT> e_building_state_tokens;
const token_holder<e_building_type, BUILDING_NONE, BUILDING_MAX> e_building_type_tokens;

building_impl::static_params building_impl::static_params::dummy;

std::span<building>& city_buildings() {
    return g_city_buildings;
}

struct building_extra_data_t {
    int highest_id_in_use;
    int highest_id_ever;
    int created_sequence;
    //    int incorrect_houses;
    //    int unfixable_houses;
};

building_extra_data_t building_extra_data = {0, 0, 0};

int building_id_first(e_building_type type) {
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return i;
    }
    return MAX_BUILDINGS;
}

building* building_first(e_building_type type) {
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return b;
    }
    return nullptr;
}

building* building_next(int i, e_building_type type) {
    for (; i < MAX_BUILDINGS; ++i) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return b;
    }
    return nullptr;
}

building* building_get(int id) {
    return &g_all_buildings[id];
}

void building::new_fill_in_data_for_type(e_building_type _tp, tile2i _tl, int orientation) {
    assert(!_ptr);
    const auto &props = building_impl::params(_tp);
    type = _tp;
    tile = _tl;
    state = BUILDING_STATE_CREATED;
    faction_id = 1;
    reserved_id = false; // city_buildings_unknown_value();
    size = props.building_size;
    creation_sequence_index = building_extra_data.created_sequence++;
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

building* building_create(e_building_type type, tile2i tile, int orientation) {
    building* b = nullptr;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        if (g_all_buildings[i].state == BUILDING_STATE_UNUSED && !game_undo_contains_building(i)) {
            b = &g_all_buildings[i];
            break;
        }
    }

    if (!b) {
        city_warning_show(WARNING_DATA_LIMIT_REACHED);
        return &g_all_buildings[0];
    }

    b->clear_impl();

    memset(&(b->data), 0, sizeof(b->data));
    b->new_fill_in_data_for_type(type, tile, orientation);
    
    b->data.house.health = 100;

    return b;
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

static std::array<const building_impl::static_params *, BUILDING_MAX> *building_impl_params = nullptr;
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

building* building_at(int grid_offset) {
    return building_get(map_building_at(grid_offset));
}

building* building_at(int x, int y) {
    return building_get(map_building_at(MAP_OFFSET(x, y)));
}

building* building_at(tile2i point) {
    return building_get(map_building_at(point.grid_offset()));
}

bool building_exists_at(int grid_offset, building* b) {
    b = nullptr;
    int b_id = map_building_at(grid_offset);
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED) {
            return true;
        } else {
            b = nullptr;
        }
    }
    return false;
}
bool building_exists_at(tile2i tile, building* b) {
    b = nullptr;
    int b_id = map_building_at(tile);
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED)
            return true;
        else
            b = nullptr;
    }
    return false;
}

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
        b = &g_all_buildings[b->prev_part_building_id];
    }
    return &g_all_buildings[0];
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

static void building_delete_UNSAFE(building* b) {
    b->clear_related_data();
    int id = b->id;
    memset(b, 0, sizeof(building));
    b->id = id;
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

    if (type == BUILDING_FESTIVAL_SQUARE) {
        city_buildings_remove_festival_square();
    }

    dcast()->on_destroy();
    clear_impl();
}

e_overlay building::get_overlay() const {
    return const_cast<building*>(this)->dcast()->get_overlay();
}

void building_clear_all() {
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        memset(&g_all_buildings[i], 0, sizeof(building));
        g_all_buildings[i].id = i;
    }
    building_extra_data.highest_id_in_use = 0;
    building_extra_data.highest_id_ever = 0;
    building_extra_data.created_sequence = 0;
    //    extra.incorrect_houses = 0;
    //    extra.unfixable_houses = 0;
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
    auto cart = f->dcast_cartpusher();
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

int building_get_highest_id(void) {
    return building_extra_data.highest_id_in_use;
}

void building_update_highest_id(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Update Highest Id");
    auto& extra = building_extra_data;

    building_extra_data.highest_id_in_use = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        if (g_all_buildings[i].state != BUILDING_STATE_UNUSED)
            extra.highest_id_in_use = i;
    }
    if (extra.highest_id_in_use > extra.highest_id_ever)
        extra.highest_id_ever = extra.highest_id_in_use;
}

void building_update_state(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building State Update");
    bool land_recalc = false;
    bool wall_recalc = false;
    bool road_recalc = false;
    bool water_routes_recalc = false;
    bool aqueduct_recalc = false;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = &g_all_buildings[i];
        if (b->state == BUILDING_STATE_CREATED)
            b->state = BUILDING_STATE_VALID;

        if (b->state != BUILDING_STATE_VALID || !b->house_size) {
            if (b->state == BUILDING_STATE_UNDO || b->state == BUILDING_STATE_DELETED_BY_PLAYER) {
                if (b->type == BUILDING_MUD_TOWER || b->type == BUILDING_MUD_GATEHOUSE) {
                    wall_recalc = true;
                    road_recalc = true;
                } else if (b->type == BUILDING_WATER_LIFT) {
                    aqueduct_recalc = true;
                } else if (b->type == BUILDING_GRANARY) {
                    road_recalc = true;
                } else if (b->type == BUILDING_FERRY) {
                    water_routes_recalc = true;
                }

                map_building_tiles_remove(i, b->tile);
                road_recalc = true; // always recalc underlying road tiles
                land_recalc = true;
                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_RUBBLE) {
                if (b->house_size > 0) {
                    city_population_remove_home_removed(b->house_population);
                }

                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_DELETED_BY_GAME) {
                building_delete_UNSAFE(b);
            } 
        }
    }
    if (wall_recalc) {
        map_tiles_update_all_walls();
    }

    if (aqueduct_recalc) {
        map_tiles_update_all_canals(0);
    }

    if (land_recalc) {
        map_routing_update_land();
    }

    if (road_recalc) {
        map_tiles_update_all_roads();
    }

    if (water_routes_recalc) {
        map_routing_update_ferry_routes();
    }
}

void building_update_desirability(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building Update Desirability");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = &g_all_buildings[i];
        if (b->state != BUILDING_STATE_VALID)
            continue;

        b->desirability = g_desirability.get_max(b->tile, b->size);
        if (b->is_adjacent_to_water) {
            b->desirability += 10;
        }

        switch (map_elevation_at(b->tile.grid_offset())) {
        case 0:
            break;
        case 1:
            b->desirability += 10;
            break;
        case 2:
            b->desirability += 12;
            break;
        case 3:
            b->desirability += 14;
            break;
        case 4:
            b->desirability += 16;
            break;
        default:
            b->desirability += 18;
            break;
        }
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
        map_highlight_set(base.road_access, 2);
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
        map_highlight_set(road_tile, 1);
    }

    hx = tilex() + 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, 1);
    }

    hx = tilex();
    hy = tiley() + 8;
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, 1);
    }

    hx = tilex() - 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, 1);
    }
}

void building_impl::on_tick(bool refresh_only) {
    if (!base.anim.valid()) {
        return;
    }

    base.anim.update(refresh_only);
}

bool resource_required_by_workshop(building* b, e_resource resource) {
    switch (resource) {
    case RESOURCE_CLAY: return (b->type == BUILDING_POTTERY_WORKSHOP || b->type == BUILDING_BRICKS_WORKSHOP);
    case RESOURCE_STRAW: return (b->type == BUILDING_BRICKS_WORKSHOP || b->type == BUILDING_CATTLE_RANCH);
    case RESOURCE_BARLEY: return b->type == BUILDING_BREWERY_WORKSHOP;
    case RESOURCE_REEDS: return b->type == BUILDING_PAPYRUS_WORKSHOP;
    case RESOURCE_FLAX: return b->type == BUILDING_WEAVER_WORKSHOP;
    case RESOURCE_GEMS: return b->type == BUILDING_JEWELS_WORKSHOP;
    case RESOURCE_COPPER: return b->type == BUILDING_WEAPONSMITH;
    case RESOURCE_TIMBER: return b->type == BUILDING_CHARIOTS_WORKSHOP;
    case RESOURCE_HENNA: return b->type == BUILDING_PAINT_WORKSHOP;
    case RESOURCE_OIL: return b->type == BUILDING_LAMP_WORKSHOP;
    default:
        ; // false
    }
    return false;
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

    city_labor_set_category(type, labor_category);

    anim.load(arch);
}

static void io_type_data(io_buffer *iob, building *b, size_t version) {
    auto &data = b->data;

    b->dcast()->bind_dynamic(iob, version);
    if (building_is_large_temple(b->type) || building_is_monument(b->type)) {
        iob->bind____skip(38);
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.orientation);
        for (int i = 0; i < 5; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &data.monuments.workers[i]);
        }
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.phase);
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.statue_offset);
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.temple_complex_attachments);
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.variant);

        for (int i = 0; i < RESOURCES_MAX; i++) {
            iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.resources_pct[i]);
        }
    } else {
        ; // nothing
    }
}

io_buffer* iob_buildings = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        //        building_state_load_from_buffer(buf, &all_buildings[i]);
        auto b = &g_all_buildings[i];
        int sind = (int)iob->get_offset();
        if (sind == 640) {
            int a = 2134;
        }

        iob->bind(BIND_SIGNATURE_UINT8, &b->state);
        iob->bind(BIND_SIGNATURE_UINT8, &b->faction_id);
        iob->bind(BIND_SIGNATURE_UINT8, &b->reserved_id);
        iob->bind(BIND_SIGNATURE_UINT8, &b->size);
        iob->bind(BIND_SIGNATURE_UINT8, &b->house_is_merged);
        iob->bind(BIND_SIGNATURE_UINT8, &b->house_size);
        iob->bind(BIND_SIGNATURE_TILE2I, b->tile);
        iob->bind____skip(2);
        iob->bind____skip(4);
        iob->bind(BIND_SIGNATURE_INT16, &b->type);
        iob->bind(BIND_SIGNATURE_INT16, &b->subtype.data); // which union field we use does not matter
        iob->bind(BIND_SIGNATURE_UINT16, &b->road_network_id);
        iob->bind(BIND_SIGNATURE_UINT16, &b->creation_sequence_index);
        iob->bind(BIND_SIGNATURE_INT16, &b->houses_covered);
        iob->bind(BIND_SIGNATURE_INT16, &b->percentage_houses_covered);

        iob->bind(BIND_SIGNATURE_INT16, &b->house_population);
        iob->bind(BIND_SIGNATURE_INT16, &b->house_population_room);
        iob->bind(BIND_SIGNATURE_INT16, &b->distance_from_entry);
        iob->bind(BIND_SIGNATURE_INT16, &b->house_highest_population);

        iob->bind(BIND_SIGNATURE_INT16, &b->house_unreachable_ticks);
        iob->bind(BIND_SIGNATURE_TILE2I, b->road_access);

        b->bind_iob_figures(iob);

        iob->bind(BIND_SIGNATURE_INT16, &b->figure_spawn_delay);
        iob->bind(BIND_SIGNATURE_UINT8, &b->figure_roam_direction);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_water_access);

        iob->bind(BIND_SIGNATURE_UINT8, &b->common_health);
        iob->bind(BIND_SIGNATURE_UINT8, &b->malaria_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->prev_part_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->next_part_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->stored_amount_first);
        iob->bind(BIND_SIGNATURE_UINT8, &b->disease_days);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_well_access);

        iob->bind(BIND_SIGNATURE_INT16, &b->num_workers);
        iob->bind(BIND_SIGNATURE_UINT8, &b->labor_category); // FF
        iob->bind(BIND_SIGNATURE_UINT8, &b->output_resource_first_id);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_road_access);
        iob->bind(BIND_SIGNATURE_UINT8, &b->house_criminal_active);

        iob->bind(BIND_SIGNATURE_INT16, &b->damage_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->fire_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->fire_duration);
        iob->bind(BIND_SIGNATURE_UINT8, &b->fire_proof);

        iob->bind(BIND_SIGNATURE_UINT8, &b->map_random_7bit); // 20 (workcamp 1)
        iob->bind(BIND_SIGNATURE_UINT8, &b->house_tax_coverage);
        iob->bind(BIND_SIGNATURE_UINT8, &b->health_proof);
        iob->bind(BIND_SIGNATURE_INT16, &b->formation_id); 

        io_type_data(iob, b, version); // 102 for PH

        int currind = iob->get_offset() - sind;
        assert(currind > 0);
        iob->bind____skip(184 - currind);

        iob->bind(BIND_SIGNATURE_INT16, &b->tax_income_or_storage);
        iob->bind(BIND_SIGNATURE_INT16, &b->stored_amount_second);
        iob->bind(BIND_SIGNATURE_UINT8, &b->house_days_without_food);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_plague); // 1

        iob->bind(BIND_SIGNATURE_INT8, &b->desirability);
        iob->bind(BIND_SIGNATURE_UINT8, &b->is_deleted);
        iob->bind(BIND_SIGNATURE_UINT8, &b->is_adjacent_to_water);

        iob->bind(BIND_SIGNATURE_UINT8, &b->storage_id);
        iob->bind(BIND_SIGNATURE_INT8, &b->sentiment.house_happiness); // which union field we use does not matter // 90 for house, 50 for wells
        iob->bind(BIND_SIGNATURE_UINT8, &b->show_on_problem_overlay); // 1
        iob->bind(BIND_SIGNATURE_UINT16, &b->deben_storage); // 2
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_open_water_access); // 1
        iob->bind(BIND_SIGNATURE_UINT8, &b->output_resource_second_id); // 1
        iob->bind(BIND_SIGNATURE_UINT8, &b->output_resource_second_rate); // 1

        iob->bind(BIND_SIGNATURE_INT16, &b->fancy_state); // 2
        iob->bind(BIND_SIGNATURE_INT8, &b->first_material_id);
        iob->bind(BIND_SIGNATURE_INT8, &b->second_material_id);
        // 59 additional bytes
        iob->bind____skip(59); // temp for debugging
                               //            assert(iob->get_offset() - sind == 264);
        g_all_buildings[i].id = i;

        if (version <= 164) { 
            b->common_health = 100;
            b->malaria_risk = 0;
            b->disease_days = 0;
            b->health_proof = 0;
        }
    }
    building_extra_data.created_sequence = 0;
});

io_buffer* iob_building_highest_id = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &building_extra_data.highest_id_in_use);
});

io_buffer* iob_building_highest_id_ever = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &building_extra_data.highest_id_ever);
    iob->bind____skip(4);
    //    highest_id_ever->skip(4);
});