#pragma once

#include "building_fwd.h"
#include "city/labor_category.h"
#include "city/city_labor.h"
#include "core/xstring.h"
#include "core/bitarray.h"
#include "core/tokenum.h"
#include "core/vec2i.h"
#include "core/core.h"
#include "core/calc.h"
#include "content/dir.h"
#include "graphics/animation.h"
#include "graphics/color.h"
#include "building/building_type.h"
#include "overlays/city_overlay_fwd.h"
#include "figure/action.h"
#include "figure/figure_type.h"
#include "game/resource.h"
#include "grid/point.h"
#include "grid/desirability.h"
#include "grid/crime.h"
#include "sound/sound_city.h"
#include "game/difficulty.h"
#include "core/variant.h"
#include "building_static_params.h"
#include "building_model.h"
#include "building_impl.h"
#include "building_cast.h"

#include <stdint.h>
#include <algorithm>

class io_buffer;
class figure;

struct tooltip_context;
struct object_info;
struct painter;
struct mouse;
struct water_access_tiles;
class build_planner;

constexpr uint32_t MAX_BUILDINGS = 4000;

struct blocked_tile {
    tile2i tile;
    bool blocked;
};
using blocked_tile_vec = svector<blocked_tile, 36>;

struct building_dest {
    building_id bid;
    tile2i tile;
};

enum e_labor_state {
    LABOR_STATE_NONE,
    LABOR_STATE_PRESENT,
    LABOR_STATE_JUST_ENTERED
};

enum e_destroy_reason : uint8_t {
    e_destroy_simple = 0,
    e_destroy_collapse = 1,
    e_destroy_flooded = 2,
    e_destroy_enemy = 3,
};

enum e_building_flag : uint8_t {
    e_building_fancy = 0,
    e_building_monument = 1,
    e_building_extractor = 2,
    e_building_harvester = 3,
    e_building_farm = 4,
};

class building_work_camp;
class building_farm;
struct building_static_params;

building* building_get(building_id id);

struct event_building_create { building_id bid; };

struct building_store : public std::array<resource_value, 4> {
    inline building_store() {}

    inline building_store(std::initializer_list<e_resource> r) {
        const std::size_t n = std::min(r.size(), size());
        std::transform(r.begin(), r.begin() + n, begin(),
            [] (e_resource e) { return resource_value{ e, 0 }; }
        );
    }

    inline int &operator[](e_resource r) {
        for (auto &it: *this) {
            if (it.type == r) {
                return it.value;
            }
        };

        for (auto &it : *this) {
            if (it.type == RESOURCE_NONE) {
                it.type = r;
                it.value = 0;
                return it.value;
            }
        }

        verify_no_crash(false);
        static int dummy = 0;
        return dummy;
    }

    inline int get(e_resource r) const {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        return it == end() ? 0 : it->value;
    }

    inline int operator[](e_resource r) const {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        return it == end() ? 0 : it->value;
    }

    inline void append(const building_store &o) {
        for (auto &t : o) {
            (*this)[t.type] += t.value;
        }
    }

    inline bool any() const { return std::find_if(begin(), end(), [] (auto &it) { return it.value > 0; }) != end(); }
    inline int sum() const { return std::accumulate(begin(), end(), 0, [] (int r, resource_value it) { return r + it.value; }); }
};


class building {
public:
    enum { max_figures = 4 };
    using ptr_buffer_t = char[16];

private:
    ptr_buffer_t _ptr_buffer = { 0 };
    class building_impl *_ptr = nullptr; // dcast

public:
    e_building_type type;
    e_building_state state;

    building_id id;
    uint8_t size;
    tile2i tile;
    uint8_t orientation;
    short native_meeting_center_id;
    uint16_t road_network_id;
    short houses_covered;
    short percentage_houses_covered;
    short distance_from_entry;
    tile2i road_access;
    short figure_spawn_delay;
    unsigned char figure_roam_direction;
    bool has_water_access;
    bool has_open_water_access;
    figure_id prev_part_building_id;
    figure_id next_part_building_id;

    building_input input;
    building_output output;

    bool has_well_access;
    uint8_t num_workers;
    uint8_t max_workers;
    sbitarray64 flags;
    e_labor_category labor_category;
    uint8_t output_resource_second_rate;
    bool has_road_access;
    uint8_t disease_days;
    uint8_t common_health;
    uint8_t spawned_worker_this_month;
    uint8_t curse_days_left;
    uint8_t blessing_days_left;

    uint8_t malaria_risk;
    uint16_t structure_damage;
    uint16_t collapse_risk;
    uint16_t fire_risk;

    int8_t collapse_risk_increase;
    int8_t fire_risk_increase;

    short fire_duration;
    uint8_t health_proof;
    uint8_t fire_proof; // cannot catch fire or collapse
    uint8_t damage_proof;
    uint8_t map_random_7bit;
    short formation_id;
    bool has_plague;
    int8_t current_desirability;
    bool is_deleted;
    bool is_adjacent_to_water;
    e_destroy_reason destroy_reason;
    uint16_t storage_id;
    union {
        int8_t native_anger;
    } sentiment;

    building_store storage;

    void consume_resource(e_resource r, int16_t amount) { storage[r] -= amount; }
    void store_resource(e_resource r, int16_t amount) { storage[r] += amount; }

    // runtime data, not saves to disk
    desirability_t::influence_t des_influence;
    crime_t::influence_t crime_influence;

    animation_t minimap_anim;
    uint8_t show_on_problem_overlay;
    uint16_t deben_storage;
    animation_context anim;
    std::array<animation_context, 4> anims;
    std::array<figure_id, max_figures> figure_ids;
    char runtime_data[186] = { 0 };

    building();
    building* main();
    inline building *next() { return building_get(next_part_building_id); }
    inline const building *next() const { return building_get(next_part_building_id); }
    inline bool has_next() const { return next_part_building_id > 0; }
    building* top_xy();
    bool is_main();

    inline bool is_valid() { return type != BUILDING_NONE && state == BUILDING_STATE_VALID; }
    inline bool is_valid() const { return type != BUILDING_NONE && state == BUILDING_STATE_VALID; }

    bool is_defense();
    bool is_farm() const { return get_flag(e_building_farm); }
    bool is_floodplain_farm();
    bool is_workshop();
    bool is_extractor();
    bool is_monument() const;
    bool is_harverster() const { return get_flag(e_building_harvester); }
    bool is_palace();
    bool is_tax_collector();
    bool is_temple();
    bool is_temple_complex() const;
    bool is_shrine() const;
    bool is_guild();
    bool is_beautification();
    bool is_water_crossing();

    bool is_industry();
    bool is_food_category();
    bool is_infrastructure();
    bool is_administration();
    bool is_religion();
    bool is_education();
    bool is_military();

    inline bool same_network(building &b) const { return road_network_id == b.road_network_id; }
    xstring get_sound();
    xstring cls_name() const;

    void clear_related_data();
    void clear_impl();
    void reset_impl();
    void initialize(e_building_type type, tile2i tile, int orientation);

    e_overlay get_overlay() const;
    int get_figure_id(int i) const { return figure_ids[i]; };

    figure* get_figure(int i) const;
    void set_figure(int i, int figure_id = -1);
    void set_figure(int i, figure* f);
    void remove_figure(int i);
    void remove_figure_by_id(int id);
    bool has_figure(int i, int figure_id = -1) const;
    bool has_figure(int i, figure* f);
    bool has_figure_of_type(int i, e_figure_type _type);
    int get_figure_slot(figure* f);
    int need_resource_amount(e_resource resource) const;
    bool need_resource(e_resource resource) const;
    int max_storage_amount(e_resource res) const;
    int stored_amount(e_resource res) const;

    const resource_value& stored_first() const { return storage.data()[0]; }
    resource_value& stored_first() { return storage.data()[0]; }

    const resource_value& stored_second() const { return storage.data()[1]; }
    
    int mothball_toggle();
    
    figure* create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir);
    figure* create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot);
    figure* create_figure_with_destination(e_figure_type _type, building* destination, e_figure_action created_action, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure* create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action, e_building_slot slot);

    int worker_percentage() const;
    int figure_spawn_timer();
    void check_labor_problem();
    bool common_spawn_figure_trigger(int min_houses, int slot = BUILDING_SLOT_SERVICE);
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action);
    figure* common_spawn_goods_output_cartpusher(int min_carry = 100, int max_carry = 800);
    bool workshop_has_resources();

    void force_damage(e_damage_type type, int8_t value);
    void destroy_by_collapse();
    void destroy_by_flooded();
    void destroy_by_fire();

    int animation_offset(int image_id, int grid_offset, int max_frames, int duration);

    void mark_plague(int days);
    bool is_ajacent_tile(tile2i t) const;

    void set_flag(e_building_flag flag, bool value) { flags.set(flag, value); }
    bool get_flag(e_building_flag flag) const { return flags.is_set(flag); }

public:
    building_impl *dcast();
    const building_impl *dcast() const;

    template<typename T>
    T *dcast() {
        return smart_cast<T*>(dcast());
    }

    template<typename T>
    const T *dcast() const {
        return smart_cast<T *>(dcast());
    }

    const building_static_params &params() const;
    
    #define ALLOW_SMART_CAST_BUILDING(type) building_##type *dcast_##type() { return dcast<building_##type>(); };
    ALLOW_SMART_CAST_BUILDING(farm)
    ALLOW_SMART_CAST_BUILDING(brewery)
    ALLOW_SMART_CAST_BUILDING(pottery);
    ALLOW_SMART_CAST_BUILDING(storage_yard)
    ALLOW_SMART_CAST_BUILDING(storage_room)
    ALLOW_SMART_CAST_BUILDING(juggler_school)
    ALLOW_SMART_CAST_BUILDING(bazaar)
    ALLOW_SMART_CAST_BUILDING(firehouse)
    ALLOW_SMART_CAST_BUILDING(architect_post)
    ALLOW_SMART_CAST_BUILDING(booth)
    ALLOW_SMART_CAST_BUILDING(apothecary)
    ALLOW_SMART_CAST_BUILDING(granary)
    ALLOW_SMART_CAST_BUILDING(water_supply)
    ALLOW_SMART_CAST_BUILDING(conservatory)
    ALLOW_SMART_CAST_BUILDING(courthouse)
    ALLOW_SMART_CAST_BUILDING(well)
    ALLOW_SMART_CAST_BUILDING(clay_pit)
    ALLOW_SMART_CAST_BUILDING(reed_gatherer)
    ALLOW_SMART_CAST_BUILDING(papyrus_maker)
    ALLOW_SMART_CAST_BUILDING(dock)
    ALLOW_SMART_CAST_BUILDING(work_camp)
    ALLOW_SMART_CAST_BUILDING(mastaba)
    ALLOW_SMART_CAST_BUILDING(small_mastaba)
    ALLOW_SMART_CAST_BUILDING(wood_cutter)
    ALLOW_SMART_CAST_BUILDING(recruiter)
    ALLOW_SMART_CAST_BUILDING(pavilion)
    ALLOW_SMART_CAST_BUILDING(statue)
    ALLOW_SMART_CAST_BUILDING(ferry)
    ALLOW_SMART_CAST_BUILDING(fort)
    ALLOW_SMART_CAST_BUILDING(fort_ground)
    ALLOW_SMART_CAST_BUILDING(fishing_wharf)
    ALLOW_SMART_CAST_BUILDING(shipyard)
    ALLOW_SMART_CAST_BUILDING(plaza)
    ALLOW_SMART_CAST_BUILDING(garden)
    ALLOW_SMART_CAST_BUILDING(house)
    ALLOW_SMART_CAST_BUILDING(burning_ruin)
    ALLOW_SMART_CAST_BUILDING(storage)
    ALLOW_SMART_CAST_BUILDING(temple)
    ALLOW_SMART_CAST_BUILDING(tax_collector)
    ALLOW_SMART_CAST_BUILDING(roadblock)
    ALLOW_SMART_CAST_BUILDING(routeblock)
    ALLOW_SMART_CAST_BUILDING(mine)
    ALLOW_SMART_CAST_BUILDING(quarry)
    ALLOW_SMART_CAST_BUILDING(palace)
    ALLOW_SMART_CAST_BUILDING(festival_square)
    ALLOW_SMART_CAST_BUILDING(bandstand)
    ALLOW_SMART_CAST_BUILDING(industry)
    ALLOW_SMART_CAST_BUILDING(guild)
    ALLOW_SMART_CAST_BUILDING(entertainment)
    ALLOW_SMART_CAST_BUILDING(mansion)
    ALLOW_SMART_CAST_BUILDING(physician)
    ALLOW_SMART_CAST_BUILDING(dentist)
    ALLOW_SMART_CAST_BUILDING(wharf)
    ALLOW_SMART_CAST_BUILDING(warship_wharf)
    ALLOW_SMART_CAST_BUILDING(temple_complex)
    ALLOW_SMART_CAST_BUILDING(temple_complex_altar)
    ALLOW_SMART_CAST_BUILDING(temple_complex_oracle)
    ALLOW_SMART_CAST_BUILDING(water_lift)
    ALLOW_SMART_CAST_BUILDING(monument)
    ALLOW_SMART_CAST_BUILDING(tower)
    ALLOW_SMART_CAST_BUILDING(senet_house)
    ALLOW_SMART_CAST_BUILDING(gatehouse)
    ALLOW_SMART_CAST_BUILDING(dancer_school)
    ALLOW_SMART_CAST_BUILDING(transport_wharf)
    ALLOW_SMART_CAST_BUILDING(police_station)
    ALLOW_SMART_CAST_BUILDING(mortuary)
    ALLOW_SMART_CAST_BUILDING(pyramid)
    ALLOW_SMART_CAST_BUILDING(small_stepped_pyramid)
    ALLOW_SMART_CAST_BUILDING(medium_stepped_pyramid)

    int get_figures_number(e_figure_type ftype);

    tile2i access_tile();

    static const metainfo &get_info(const xstring type);

    template<typename T>
    building_impl *acquire_impl() {
        new (&_ptr_buffer) T(*this);
        _ptr = (building_impl *)&_ptr_buffer;
        return _ptr;
    }

private:
    void destroy_on_fire_impl(bool plagued);
    void destroy_linked_parts(bool on_fire);
};

#define BUILDING_METAINFO(type, clsid, base_class)                                                      \
    clsid(building &b) : base_class(b) {}                                                               \
    static constexpr e_building_type TYPE = type;                                                       \
    static constexpr pcstr CLSID = #clsid;                                                              \
    using self_type = clsid;                                                                            \
    using model_type = buildings::model_t<clsid>;                                                       \
    using inherited = base_class;                                                                       

#define BUILDING_RUNTIME_DATA(type) ;                                                                   \
    type& runtime_data() { return *(type*)this->base.runtime_data; }                                    \
    const type& runtime_data() const { static_assert(sizeof(type) < sizeof(building::runtime_data)); return *(type*)this->base.runtime_data; }

#define BUILDING_RUNTIME_DATA_T BUILDING_RUNTIME_DATA(runtime_data_t)

#define BUILDING_STATIC_DATA(type) ;                                                                    \
    static const type &current_params() { return (const type &)building_static_params::get(TYPE); }

#define BUILDING_STATIC_DATA_T BUILDING_STATIC_DATA(static_params)

struct bproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(building&, const xstring&)> handler;
};

template<typename T>
bool building_type_any_of(e_building_type type, const T& types) {
    return (std::find(types.begin(), types.end(), type) != types.end());
}

inline bool building_type_any_of(e_building_type type, const std::initializer_list<e_building_type>& types) {
    return (std::find(types.begin(), types.end(), type) != types.end());
}

inline bool building_type_any_of(building &b, const e_building_type &type) {
    return b.type = type;
}

inline bool building_type_any_of(building &b, const std::initializer_list<e_building_type> &types) {
    return building_type_any_of(b.type, types);
}

template<typename T>
bool building_type_none_of(building &b, const T& types) {
    return (std::find(types.begin(), types.end(), b.type) == types.end());
}

inline bool building_type_none_of(building &b, const std::initializer_list<e_building_type> &types) {
    return (std::find(types.begin(), types.end(), b.type) == types.end());
}

void add_building(building *b, int orientation, int variant);

namespace buildings {
    template<typename T>
    building_impl *model_t<T>::create(e_building_type e, building &b) {
        if (e == TYPE) {
            return b.template acquire_impl<building_type>();
        }
        return nullptr;
    }
}

template <typename dest_type, typename r_type>
inline r_type smart_cast(building *b) {
    return ::smart_cast<r_type>(b->dcast());
}

inline bool building_is_house(e_building_type type) { return type >= BUILDING_HOUSE_CRUDE_HUT && type <= BUILDING_HOUSE_PALATIAL_ESTATE; }
bool building_is_fort(int type);
bool building_is_defense(e_building_type type);
bool building_is_workshop(int type);
bool building_is_administration(e_building_type type);
bool building_is_palace(e_building_type type);
bool building_is_tax_collector(e_building_type type);
bool building_is_governor_mansion(e_building_type type);
bool building_is_temple(e_building_type type);
bool building_is_temple_complex(e_building_type type);
bool building_is_shrine(e_building_type type);
bool building_is_guild(e_building_type type);
bool building_is_statue(e_building_type type);
bool building_is_beautification(e_building_type type);
bool building_is_water_crossing(e_building_type type);
bool building_is_industry_type(building* b);

bool building_is_industry(e_building_type type);
bool building_is_food_category(e_building_type type);
bool building_is_infrastructure(e_building_type type);
bool building_is_religion(e_building_type type);
bool building_is_entertainment(e_building_type type);
bool building_is_education(e_building_type type);
bool building_is_military(e_building_type type);

bool building_is_draggable(e_building_type type);
building *building_begin();
building *building_end();