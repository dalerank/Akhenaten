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
#include "core/xfunction.h"
#include "core/archive.h"
#include "core/object_property.h"
#include "core/svector.h"

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
    e_destroy_reason_max
};

enum e_building_flag : uint8_t {
    e_building_fancy = 0,
    e_building_monument = 1,
    e_building_extractor = 2,
    e_building_harvester = 3,
    e_building_farm = 4,
    e_building_fort = 5,
    e_building_education = 6,
    e_building_palace = 7,
    e_building_temple = 8,
    e_building_shrine = 9,
    e_building_tax_collector = 10,
    e_building_statue = 11,
    e_building_administration = 12,
    e_building_water_crossing = 13,
    e_building_infrastructure = 14,
    e_building_beautification = 15,
    e_building_guild = 16,
    e_building_industry = 17,
    e_building_workshop = 18,
    e_building_house = 19,
    e_building_wall = 20,
    e_building_defense = 21,
    e_building_temple_complex = 22,
    e_building_religion = 23,
    e_building_military = 24,
    e_building_entertainment = 25,
    e_building_food = 26,
    e_building_non_deletable = 27,
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

    inline uint16_t &operator[](e_resource r) {
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
        static uint16_t dummy = 0;
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


class building : public no_copy_assignment {
public:
    enum { max_figures = 4 };
    // The impl object is constructed in place in this buffer (see acquire_impl), so the buffer
    // has to carry an alignment that a bare char array does not: alignof(char[16]) is 1, while
    // every building_impl starts with a vtable pointer.
    struct alignas(8) ptr_buffer_t { char data[16]; };

private:
    ptr_buffer_t _ptr_buffer = {};
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
    svector<building_overlay_anim, 4> overlay_anims;
    std::array<figure_id, max_figures> figure_ids;

    static constexpr std::size_t runtime_data_align = 8;
    alignas(runtime_data_align) char runtime_data[186] = { 0 };
    bool play_animation = false;

    building();
    building* main();
    const building* main() const;
    inline building *next() { return building_get(next_part_building_id); }
    inline const building *next() const { return building_get(next_part_building_id); }
    inline bool has_next() const { return next_part_building_id > 0; }
    building* top_xy();
    bool is_main();

    inline bool is_valid() { return type != BUILDING_NONE && state == BUILDING_STATE_VALID; }
    inline bool is_valid() const { return type != BUILDING_NONE && state == BUILDING_STATE_VALID; }

    bool is_defense() const { return get_flag(e_building_defense); }
    bool is_farm() const { return get_flag(e_building_farm); }
    bool is_fort() const { return get_flag(e_building_fort); }
    bool is_floodplain_farm();
    bool is_workshop() const { return get_flag(e_building_workshop); }
    bool is_extractor() const { return get_flag(e_building_extractor); }
    bool is_monument() const;
    bool is_entertainment() const { return get_flag(e_building_entertainment); }
    bool is_harverster() const { return get_flag(e_building_harvester); }
    bool is_palace() const { return get_flag(e_building_palace); }
    bool is_temple() const { return get_flag(e_building_temple); }
    bool is_temple_complex() const { return get_flag(e_building_temple_complex); }
    bool is_house() const { return get_flag(e_building_house); }
    bool is_shrine() const { return get_flag(e_building_shrine); }
    bool is_guild() const { return get_flag(e_building_guild); }
    bool is_beautification() const { return get_flag(e_building_beautification); }

    bool is_industry() const { return get_flag(e_building_industry); }
    bool is_food_category() const { return get_flag(e_building_food); }
    bool is_infrastructure() const { return get_flag(e_building_infrastructure); }
    bool is_administration() const { return get_flag(e_building_administration); }
    bool is_religion() const { return get_flag(e_building_religion); }
    bool is_education() const { return get_flag(e_building_education); }
    bool is_military() const { return get_flag(e_building_military); }
    bool is_deletable() const { return !get_flag(e_building_non_deletable); }

    inline bool same_network(building &b) const { return road_network_id == b.road_network_id; }
    xstring get_sound();
    xstring cls_name() const;

    void clear_related_data();
    void clear_impl();
    void reset_impl();
    void setup_static_flags();
    void initialize(e_building_type type, tile2i tile, int orientation);

    e_overlay get_overlay() const;
    int get_figure_id(int i) const {
        verify_no_crash(i >= 0 && i < (int)max_figures);
        if (i < 0 || i >= (int)max_figures) {
            return 0;
        }
        return figure_ids[i];
    };

    figure* get_figure(int i) const;
    void set_figure(int i, int figure_id);
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

    void draw_usable_paths(painter &ctx);

    int worker_percentage() const;
    bool workshop_has_resources();

    void force_damage(e_damage_type type, int16_t value);
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
    BUILDING_CLASS_LIST(ALLOW_SMART_CAST_BUILDING)

    tile2i access_tile();

    static const metainfo &get_info(const xstring type);

    template<typename T>
    building_impl *acquire_impl() {
        // Impl subclasses are expected to hold no members of their own -- their state lives in
        // runtime_data. One that did would run over _ptr and the fields after it.
        static_assert(sizeof(T) <= sizeof(ptr_buffer_t), "building impl does not fit the inline buffer");
        static_assert(alignof(T) <= alignof(ptr_buffer_t), "building impl needs a stricter alignment");
        new (&_ptr_buffer) T(*this);
        _ptr = (building_impl *)&_ptr_buffer;
        return _ptr;
    }

private:
    void destroy_on_fire_impl(bool plagued);
    void destroy_linked_parts(bool on_fire);
};
ANK_CONFIG_PROPERTY(building, has_road_access, num_workers, max_workers, type, orientation, size,
    prev_part_building_id, next_part_building_id, formation_id, collapse_risk, fire_risk, malaria_risk, structure_damage, spawned_worker_this_month,
    current_desirability, has_water_access, has_well_access, curse_days_left,
    common_health, disease_days, has_plague, houses_covered, show_on_problem_overlay, play_animation, destroy_reason,
    fire_proof, road_network_id, distance_from_entry)

#define BUILDING_METAINFO(type, clsid, base_class)                                                      \
    clsid(building &b) : base_class(b) {}                                                               \
    static constexpr e_building_type TYPE = type;                                                       \
    static constexpr pcstr CLSID = #clsid;                                                              \
    using self_type = clsid;                                                                            \
    using model_type = buildings::model_t<clsid>;                                                       \
    using inherited = base_class;

#define BUILDING_RUNTIME_DATA_CHECKS(type)                                                              \
    static_assert(sizeof(type) < sizeof(building::runtime_data), #type " does not fit building::runtime_data"); \
    static_assert(alignof(type) <= building::runtime_data_align, #type " needs a stricter alignment")

#define BUILDING_RUNTIME_DATA(type) ;                                                                   \
    type& runtime_data() { BUILDING_RUNTIME_DATA_CHECKS(type); return *(type*)this->base.runtime_data; } \
    const type& runtime_data() const { BUILDING_RUNTIME_DATA_CHECKS(type); return *(type*)this->base.runtime_data; } \
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;           \
    virtual bool set_property(const xstring &domain, const xstring &name, const bvariant &value) override;

#define BUILDING_RUNTIME_DATA_T BUILDING_RUNTIME_DATA(runtime_data_t)

#define BUILDING_RUNTIME_DATA_IMPL(type)                                                                \
    bvariant type::get_property(const xstring& domain, const xstring& name) const {                     \
        auto result = archive_helper::get(runtime_data(), name, domain == tags().building);             \
        if (result) {                                                                                   \
            return result.value();                                                                      \
        }                                                                                               \
        return inherited::get_property(domain, name);                                                   \
    }                                                                                                   \
    bool type::set_property(const xstring& domain, const xstring& name, const bvariant& value) {        \
        if (domain == tags().building && archive_helper::set(runtime_data(), name, value, true)) {      \
            return true;                                                                                \
        }                                                                                               \
        return inherited::set_property(domain, name, value);                                            \
    }

#define BUILDING_STATIC_DATA(type) ;                                                                    \
    static const type &current_params() { return (const type &)building_static_params::get(TYPE); }

#define BUILDING_STATIC_DATA_T BUILDING_STATIC_DATA(static_params)

struct bproperty {
    xstring domain;
    xstring name;

    using handler_t = xfunction<bvariant(building &, const xstring &)>;
    handler_t handler;
};

template<typename T>
bool building_type_any_of(e_building_type type, const T& types) {
    return (std::find(types.begin(), types.end(), type) != types.end());
}

inline bool building_type_any_of(e_building_type type, const std::initializer_list<e_building_type>& types) {
    return (std::find(types.begin(), types.end(), type) != types.end());
}

inline bool building_type_any_of(building &b, const e_building_type &type) {
    return b.type == type;
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

building *building_begin();
building *building_end();