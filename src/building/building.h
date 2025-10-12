#pragma once

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
#include "sound/sound_city.h"
#include "core/variant.h"
#include "model.h"

#include <stdint.h>
#include <algorithm>

class io_buffer;
class figure;
class building_juggler_school;
class building_storage_yard;
class building_storage_room;
class building_brewery;
class building_pottery;
class building_bazaar;
class building_firehouse;
class building_architect_post;
class building_booth;
class building_apothecary;
class building_granary;
class building_water_supply;
class building_conservatory;
class building_courthouse;
class building_well;
class building_clay_pit;
class building_reed_gatherer;
class building_papyrus_maker;
class building_dock;
class building_mastaba;
class building_small_mastaba;
class building_medium_mastaba;
class building_wood_cutter;
class building_recruiter;
class building_pavilion;
class building_statue;
class building_ferry;
class building_fort;
class building_fort_ground;
class building_fishing_wharf;
class building_warship_wharf;
class building_shipyard;
class building_plaza;
class building_garden;
class building_house;
class building_burning_ruin;
class building_storage;
class building_temple;
class building_tax_collector;
class building_roadblock;
class building_mine;
class building_quarry;
class building_palace;
class building_festival_square;
class building_bandstand;
class building_routeblock;
class building_industry;
class building_guild;
class building_entertainment;
class building_mansion;
class building_physician;
class building_wharf;
class building_shrine;
class building_transport_wharf;
class building_temple_complex;
class building_temple_complex_altar;
class building_temple_complex_oracle;
class building_water_lift;
class building_monument;
class building_scribal_school;
class building_tower;
class building_senet_house;
class building_gatehouse;
struct tooltip_context;
struct object_info;
struct painter;
struct mouse;
struct water_access_tiles;
class build_planner;

constexpr uint32_t MAX_BUILDINGS = 4000;
using e_building_flags = uint32_t;

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

enum e_destroy_reason {
    e_destroy_simple = 0,
    e_destroy_collapse = 1,
    e_destroy_flooded = 2,
};

enum e_building_state {
    BUILDING_STATE_UNUSED = 0,
    BUILDING_STATE_VALID = 1,
    BUILDING_STATE_UNDO = 2,
    BUILDING_STATE_CREATED = 3,
    BUILDING_STATE_RUBBLE = 4,
    BUILDING_STATE_DELETED_BY_GAME = 5, // used for earthquakes, fires, house mergers
    BUILDING_STATE_DELETED_BY_PLAYER = 6,
    BUILDING_STATE_MOTHBALLED = 7,
    BUILDING_STATE_COUNT,
};
extern const token_holder<e_building_state, BUILDING_STATE_UNUSED, BUILDING_STATE_COUNT> e_building_state_tokens;

enum e_building_slot {
    BUILDING_SLOT_SERVICE = 0,
    BUILDING_SLOT_CARTPUSHER = 1,
    BUILDING_SLOT_MARKET_BUYER = 1,
    BUILDING_SLOT_LABOR_SEEKER = 2,
    BUILDING_SLOT_JUGGLER = 0,
    BUILDING_SLOT_DRUNKARD = 1,
    BUILDING_SLOT_MUSICIAN = 1,
    BUILDING_SLOT_DANCER = 2,
    BUILDING_SLOT_PRIEST = 2,
    BUILDING_SLOT_IMMIGRANT = 2,
    BUILDING_SLOT_HOMELESS = 2,
    BUILDING_SLOT_GOVERNOR = 3,
    BUILDING_SLOT_HUNTER = 3,
    BUILDING_SLOT_BOAT = 3,
    BUILDING_SLOT_BALLISTA = 3,
    BUILDING_SLOT_CARTPUSHER_2 = 3,
};

enum e_fancy_state {
    efancy_normal,
    efancy_good
};

class building_work_camp;
class building_farm;
struct building_static_params;

building* building_get(building_id id);

struct event_building_create { building_id bid; };

struct building_input {
    e_resource resource;
    e_resource resource_second;
};
using building_output = building_input;
ANK_CONFIG_STRUCT(building_input, resource, resource_second)

struct metainfo {
    uint16_t help_id;
    uint16_t text_id;
};
ANK_CONFIG_STRUCT(metainfo, help_id, text_id)

class building {
public:
    enum { max_figures = 4 };
    using ptr_buffer_t = char[16];

private:
    ptr_buffer_t _ptr_buffer = { 0 };
    class building_impl *_ptr = nullptr; // dcast

public:
    e_building_type type;
    building_id id;
    e_building_state state;
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
    short stored_amount_first;
    short stored_amount_second;
    bool has_well_access;
    uint8_t num_workers;
    uint8_t max_workers;
    e_fancy_state fancy_state;
    e_labor_category labor_category;
    building_output output;
    uint8_t output_resource_second_rate;
    bool has_road_access;
    uint8_t disease_days;
    uint8_t common_health;
    uint8_t malaria_risk;
    uint8_t spawned_worker_this_month;
    uint8_t curse_days_left;
    uint8_t blessing_days_left;
    uint16_t damage_risk;
    uint16_t fire_risk;

    int8_t damage_risk_increase;
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

    // runtime data, not saves to disk
    desirability_t::influence_t des_influence;

    animation_t minimap_anim;
    uint8_t show_on_problem_overlay;
    uint16_t deben_storage;
    animation_context anim;
    std::array<figure_id, max_figures> figure_ids;
    char runtime_data[512] = { 0 };

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
    bool is_farm();
    bool is_workshop();
    bool is_extractor();
    bool is_monument();
    bool is_palace();
    bool is_tax_collector();
    bool is_governor_mansion();
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
    int stored_amount(int idx = 0) const;
    int stored_amount(e_resource res) const;
    int mothball_toggle();
    
    figure* create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir);
    figure* create_roaming_figure(e_figure_type _type, e_figure_action created_action = FIGURE_ACTION_125_ROAMING, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure* create_figure_with_destination(e_figure_type _type, building* destination, e_figure_action created_action = ACTION_10_GOING, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure* create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action = FIGURE_ACTION_20_INITIAL, e_building_slot slot = BUILDING_SLOT_CARTPUSHER);

    int worker_percentage() const;
    int figure_spawn_timer();
    void check_labor_problem();
    bool common_spawn_figure_trigger(int min_houses, int slot = BUILDING_SLOT_SERVICE);
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action = FIGURE_ACTION_125_ROAMING);
    figure* common_spawn_goods_output_cartpusher(int min_carry = 100, int max_carry = 800);
    bool workshop_has_resources();

    void force_damage(bool fire, int8_t value);
    void destroy_by_collapse();
    void destroy_by_flooded();
    void destroy_by_fire();

    void mark_plague(int days);
    bool is_ajacent_tile(tile2i t) const;

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
    using building_model = buildings::model_t<clsid>;                                                   \
    using model_type = building_model;                                                                  \
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

struct building_desirability_t {
    svector<int8_t, 6> value;
    svector<int8_t, 6> step;
    svector<int8_t, 6> step_size;
    svector<int8_t, 6> range;

    desirability_t::influence_t to_influence() const;
};
ANK_CONFIG_STRUCT(building_desirability_t, value, step, step_size, range)

struct building_planner_update_rule {
    bool canals;
    bool roads;
    bool ferries;
    bool is_draggable;
    int relative_orientation;
    bool unique_building;
};
ANK_CONFIG_STRUCT(building_planner_update_rule, canals, roads, ferries, is_draggable, relative_orientation, unique_building)

struct building_planner_need_rule {
    bool meadow;
    bool rock;
    bool ore;
    bool altar;
    bool oracle;
    bool nearby_water;
    bool groundwater;
    bool shoreline;
    bool canals;
    bool floodplain_shoreline;
    bool water_access;
};
ANK_CONFIG_STRUCT(building_planner_need_rule, meadow, rock, ore, altar, oracle,
    nearby_water, groundwater, shoreline, canals, floodplain_shoreline, water_access)

struct building_planer_renderer {
    static const building_planer_renderer dummy;
    virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const;
    virtual bool can_construction_start(build_planner &p, tile2i start) const { return true; }
    virtual int setup_orientation(int orientation) const { return orientation; }
    virtual void setup_build(build_planner &planer) const {}
    virtual void setup_preview_graphics(build_planner &planer) const;
    virtual int setup_building_variant(e_building_type type, tile2i tile, int variant) const { return variant; }
    virtual int next_building_variant(e_building_type type, tile2i tile, int variant) const { return (variant + 1) % 4; }
    virtual int update_relative_orientation(build_planner &p, tile2i tile, int global_orientation) const { return global_orientation; }
    virtual int update_building_variant(build_planner &p) const;
    virtual int construction_update(build_planner &p, tile2i start, tile2i end) const;
    virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const;

    static void register_model(e_building_type e, const building_planer_renderer &p);
    static const building_planer_renderer& get(e_building_type e);
};

struct building_static_params {
    static building_static_params dummy;
    e_building_type type;
    pcstr name;
    bool fire_proof, damage_proof;
    xstring meta_id;
    metainfo meta;
    building_input input;
    building_output output;
    int output_resource_second_rate;
    e_labor_category labor_category;
    animations_t animations;
    uint8_t building_size;
    uint8_t min_houses_coverage;
    uint16_t production_rate;
    xstring info_title_id;
    int num_types;
    std::array<uint16_t, 5> cost;
    building_desirability_t desirability;
    uint16_t progress_max;

    svector<uint8_t, 5> laborers;
    svector<int8_t, 5> fire_risk;
    svector<int8_t, 5> damage_risk;

    building_planner_update_rule planner_update_rule;
    building_planner_need_rule needs;

    void archive_unload();
    void initialize();
    
    virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const;
    virtual void planer_ghost_blocked(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const;
    virtual bool planer_is_need_flag(e_building_flags flag) const;
    virtual int planer_can_place(build_planner &p, tile2i tile, tile2i end, int state) const { return state; }

    virtual bool is_unique_building() const { return planner_update_rule.unique_building; }
    virtual uint16_t get_cost() const;

    inline const int first_img(const xstring &anim_key) const { return animations[anim_key].first_img(); }
    const int base_img() const;

    static void register_model(e_building_type, const building_static_params &);
    static const building_static_params &get(e_building_type);
    static building_static_params &ref(e_building_type e);
};
ANK_CONFIG_STRUCT(building_static_params, 
    labor_category, fire_proof, damage_proof, input, output,
    fire_proof, damage_proof, animations, laborers, fire_risk, damage_risk, planner_update_rule, cost, desirability,
    output_resource_second_rate, num_types, building_size, info_title_id, progress_max, 
    meta_id, production_rate, min_houses_coverage)

class building_impl {
public:
    using preview = building_planer_renderer;                                                           

    building_impl(building &b) : base(b) {}
    virtual void on_create(int orientation) {}
    virtual void on_place(int orientation, int variant);
    virtual void on_place_update_tiles(int orientation, int variant);
    virtual void on_place_checks();
    virtual void on_destroy() {}
    virtual void on_before_collapse() {}
    virtual void on_before_flooded() {}
    virtual void on_undo() {}
    virtual void on_post_load() {}
    virtual void spawn_figure() {}
    virtual void update_graphic();
    virtual void update_month() {}
    virtual void update_day();
    virtual void remove_dead_figures();
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask);
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) { return false; }
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual bool force_draw_top_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual e_overlay get_overlay() const { return OVERLAY_NONE; }
    virtual bool need_road_access() const { return true; }
    virtual bool can_play_animation() const;
    virtual void update_count() const;
    virtual void update_map_orientation(int orientation) {}
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_NONE; }
    virtual int animation_speed(int speed) const { return speed; }
    virtual int get_fire_risk(int value) const { return value; }
    virtual textid get_tooltip() const { return {0, 0}; }
    virtual int ready_production() const { return current_params().production_rate; }
    virtual void draw_normal_anim(painter &ctx, vec2i point, tile2i tile, color mask);
    virtual void draw_normal_anim(painter &ctx, const animation_context &ranim, vec2i point, tile2i tile, color mask);
    virtual void draw_tooltip(tooltip_context *c) {};
    virtual void bind_dynamic(io_buffer *iob, size_t version);
    virtual bvariant get_property(const xstring &domain, const xstring &name) const;
    virtual bool add_resource(e_resource resource, int amount) { return false; }
    virtual int get_orientation() const { return base.orientation; }
    virtual void on_config_reload() {}
    virtual void set_water_access_tiles(const water_access_tiles &tiles) {}
    virtual void start_production() {}

    virtual void remove_worker(figure_id fid) {}
    virtual void add_workers(figure_id fid) {}

    #define ALLOW_SMART_CAST_BUILDING_I(type) virtual building_##type *dcast_##type() { return nullptr; }
    ALLOW_SMART_CAST_BUILDING_I(farm)
    ALLOW_SMART_CAST_BUILDING_I(brewery)
    ALLOW_SMART_CAST_BUILDING_I(pottery)
    ALLOW_SMART_CAST_BUILDING_I(storage_yard)
    ALLOW_SMART_CAST_BUILDING_I(storage_room)
    ALLOW_SMART_CAST_BUILDING_I(juggler_school)
    ALLOW_SMART_CAST_BUILDING_I(bazaar)
    ALLOW_SMART_CAST_BUILDING_I(firehouse)
    ALLOW_SMART_CAST_BUILDING_I(architect_post)
    ALLOW_SMART_CAST_BUILDING_I(booth)
    ALLOW_SMART_CAST_BUILDING_I(apothecary)
    ALLOW_SMART_CAST_BUILDING_I(granary)
    ALLOW_SMART_CAST_BUILDING_I(water_supply)
    ALLOW_SMART_CAST_BUILDING_I(conservatory)
    ALLOW_SMART_CAST_BUILDING_I(courthouse)
    ALLOW_SMART_CAST_BUILDING_I(well)
    ALLOW_SMART_CAST_BUILDING_I(clay_pit)
    ALLOW_SMART_CAST_BUILDING_I(reed_gatherer)
    ALLOW_SMART_CAST_BUILDING_I(papyrus_maker)
    ALLOW_SMART_CAST_BUILDING_I(dock)
    ALLOW_SMART_CAST_BUILDING_I(work_camp)
    ALLOW_SMART_CAST_BUILDING_I(mastaba)
    ALLOW_SMART_CAST_BUILDING_I(small_mastaba)
    ALLOW_SMART_CAST_BUILDING_I(medium_mastaba)
    ALLOW_SMART_CAST_BUILDING_I(wood_cutter)
    ALLOW_SMART_CAST_BUILDING_I(recruiter)
    ALLOW_SMART_CAST_BUILDING_I(pavilion)
    ALLOW_SMART_CAST_BUILDING_I(statue)
    ALLOW_SMART_CAST_BUILDING_I(ferry)
    ALLOW_SMART_CAST_BUILDING_I(fort)
    ALLOW_SMART_CAST_BUILDING_I(fort_ground)
    ALLOW_SMART_CAST_BUILDING_I(fishing_wharf)
    ALLOW_SMART_CAST_BUILDING_I(shipyard)
    ALLOW_SMART_CAST_BUILDING_I(plaza)
    ALLOW_SMART_CAST_BUILDING_I(garden)
    ALLOW_SMART_CAST_BUILDING_I(house)
    ALLOW_SMART_CAST_BUILDING_I(burning_ruin)
    ALLOW_SMART_CAST_BUILDING_I(storage)
    ALLOW_SMART_CAST_BUILDING_I(temple)
    ALLOW_SMART_CAST_BUILDING_I(tax_collector)
    ALLOW_SMART_CAST_BUILDING_I(roadblock)
    ALLOW_SMART_CAST_BUILDING_I(mine)
    ALLOW_SMART_CAST_BUILDING_I(quarry)
    ALLOW_SMART_CAST_BUILDING_I(palace)
    ALLOW_SMART_CAST_BUILDING_I(festival_square)
    ALLOW_SMART_CAST_BUILDING_I(bandstand)
    ALLOW_SMART_CAST_BUILDING_I(routeblock)
    ALLOW_SMART_CAST_BUILDING_I(industry)
    ALLOW_SMART_CAST_BUILDING_I(guild)
    ALLOW_SMART_CAST_BUILDING_I(entertainment)
    ALLOW_SMART_CAST_BUILDING_I(mansion)
    ALLOW_SMART_CAST_BUILDING_I(physician)
    ALLOW_SMART_CAST_BUILDING_I(wharf)
    ALLOW_SMART_CAST_BUILDING_I(warship_wharf)
    ALLOW_SMART_CAST_BUILDING_I(shrine)
    ALLOW_SMART_CAST_BUILDING_I(transport_wharf)
    ALLOW_SMART_CAST_BUILDING_I(temple_complex)
    ALLOW_SMART_CAST_BUILDING_I(temple_complex_altar)
    ALLOW_SMART_CAST_BUILDING_I(temple_complex_oracle)
    ALLOW_SMART_CAST_BUILDING_I(water_lift)
    ALLOW_SMART_CAST_BUILDING_I(monument)
    ALLOW_SMART_CAST_BUILDING_I(scribal_school)
    ALLOW_SMART_CAST_BUILDING_I(tower)
    ALLOW_SMART_CAST_BUILDING_I(senet_house)
    ALLOW_SMART_CAST_BUILDING_I(gatehouse)

    inline building_impl *next() { return base.next()->dcast(); }
    inline building_impl *main() { return base.main()->dcast(); }
    inline bool is_main() const { return base.is_main(); }
    inline bool has_figure(int slot) { return base.has_figure(slot); }
    inline bool is_valid() const { return base.is_valid(); }
    inline e_building_state state() const { return base.state; }
    inline void check_labor_problem() { base.check_labor_problem(); }
    inline int worker_percentage() const { return base.worker_percentage(); }
    inline void common_spawn_labor_seeker(int min_houses) { base.common_spawn_labor_seeker(min_houses); }
    inline bool common_spawn_figure_trigger(int min_houses, int slot = BUILDING_SLOT_SERVICE) { return base.common_spawn_figure_trigger(min_houses, slot); }
    inline bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action) { return base.common_spawn_roamer(type, min_houses, created_action); }
    inline int max_workers() const { return base.max_workers; }
    inline int pct_workers() const { return calc_percentage<int>(num_workers(), max_workers()); }
    inline int get_figure_id(int i) const { return base.get_figure_id(i); }
    inline int need_resource_amount(e_resource r) const { return base.need_resource_amount(r); }
    inline const building_static_params &current_params() const { return building_static_params::get(type()); }
    inline const building_static_params &current_params() { return building_static_params::get(type()); }
    figure *get_figure_in_slot(int i);

    inline bool has_figure_of_type(int i, e_figure_type _type) { return base.has_figure_of_type(i, _type);  }
    inline figure *create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action = ACTION_10_GOING, e_building_slot slot = BUILDING_SLOT_SERVICE) { return base.create_figure_with_destination(_type, destination, created_action, slot); }
    inline figure *create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) { return base.create_roaming_figure(_type, created_action, slot); }
    inline figure *create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir) { return base.create_figure_generic(_type, created_action, slot, created_dir); }
    inline figure *create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action = FIGURE_ACTION_20_INITIAL, e_building_slot slot = BUILDING_SLOT_CARTPUSHER) { return base.create_cartpusher(resource_id, quantity, created_action, slot); }
    inline figure *get_figure(int slot) { return base.get_figure(slot); }
    inline const figure *get_figure(int slot) const { return base.get_figure(slot); }
    
    inline building_id id() const { return base.id; }
    inline tile2i tile() const { return base.tile; }
    inline int tilex() const { return base.tile.x(); }
    inline int tiley() const { return base.tile.y(); }

    inline int size() const { return base.size; }
    inline e_building_type type() const { return base.type; }

    inline int figure_spawn_timer() const { return base.figure_spawn_timer(); }
    inline int num_workers() const { return base.num_workers; }
    inline bool has_road_access() const { return base.has_road_access; }
    inline short distance_from_entry() const { return base.distance_from_entry; }
    inline int road_network() const { return base.road_network_id; }
    inline const animation_t &anim(const xstring &key) const { return current_params().animations[key]; }
    inline const int first_img(const xstring &key) const { return  current_params().first_img(key); }
    inline const int base_img() const { return  current_params().base_img(); }
 
    virtual bool is_workshop() const { return false; }
    virtual bool is_administration() const { return false; }
    virtual bool is_unique_building() const { return false; }
    virtual void destroy_by_poof(bool clouds);
    virtual void highlight_waypoints();
    virtual void on_tick(bool refresh_only);

    virtual resource_vec required_resources() const;
    virtual bool required_resource(e_resource) const;
    virtual int stored_amount(e_resource) const;
    metainfo get_info() const;
    void set_animation(const animation_t &anim);
    xstring get_sound();
    inline void set_animation(const xstring &key) { set_animation(anim(key)); }

    static void acquire(e_building_type e, building &b);

    building &base;
};

template <typename dest_type, typename r_type = std::add_pointer_t<std::remove_pointer_t<dest_type>>>
inline r_type smart_cast(building *b) {
    return ::smart_cast<r_type>(b->dcast());
}

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


inline bool building_is_house(e_building_type type) { return type >= BUILDING_HOUSE_VACANT_LOT && type <= BUILDING_HOUSE_PALATIAL_ESTATE; }
bool building_is_fort(int type);
bool building_is_defense(e_building_type type);
bool building_is_farm(e_building_type type);
inline bool building_is_farm(building &b) { return building_is_farm(b.type); }
bool building_is_floodplain_farm(building &b);
bool building_is_workshop(int type);
bool building_is_extractor(int type);
bool building_is_harvester(e_building_type type);
bool building_is_monument(e_building_type type);
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

GENERATE_SMART_CAST(building_impl)
#define GENERATE_SMART_CAST_BUILDING(type) GENERATE_SMART_CAST_CUSTOM(building_##type, type)

GENERATE_SMART_CAST_BUILDING(farm)
GENERATE_SMART_CAST_BUILDING(juggler_school)
GENERATE_SMART_CAST_BUILDING(storage_yard)
GENERATE_SMART_CAST_BUILDING(storage_room)
GENERATE_SMART_CAST_BUILDING(brewery)
GENERATE_SMART_CAST_BUILDING(pottery)
GENERATE_SMART_CAST_BUILDING(bazaar)
GENERATE_SMART_CAST_BUILDING(firehouse)
GENERATE_SMART_CAST_BUILDING(architect_post)
GENERATE_SMART_CAST_BUILDING(booth)
GENERATE_SMART_CAST_BUILDING(apothecary)
GENERATE_SMART_CAST_BUILDING(granary)
GENERATE_SMART_CAST_BUILDING(water_supply)
GENERATE_SMART_CAST_BUILDING(conservatory)
GENERATE_SMART_CAST_BUILDING(courthouse)
GENERATE_SMART_CAST_BUILDING(well)
GENERATE_SMART_CAST_BUILDING(clay_pit)
GENERATE_SMART_CAST_BUILDING(reed_gatherer)
GENERATE_SMART_CAST_BUILDING(papyrus_maker)
GENERATE_SMART_CAST_BUILDING(dock)
GENERATE_SMART_CAST_BUILDING(mastaba)
GENERATE_SMART_CAST_BUILDING(small_mastaba)
GENERATE_SMART_CAST_BUILDING(medium_mastaba)
GENERATE_SMART_CAST_BUILDING(wood_cutter)
GENERATE_SMART_CAST_BUILDING(recruiter)
GENERATE_SMART_CAST_BUILDING(pavilion)
GENERATE_SMART_CAST_BUILDING(statue)
GENERATE_SMART_CAST_BUILDING(ferry)
GENERATE_SMART_CAST_BUILDING(fort)
GENERATE_SMART_CAST_BUILDING(fort_ground)
GENERATE_SMART_CAST_BUILDING(fishing_wharf)
GENERATE_SMART_CAST_BUILDING(warship_wharf)
GENERATE_SMART_CAST_BUILDING(shipyard)
GENERATE_SMART_CAST_BUILDING(plaza)
GENERATE_SMART_CAST_BUILDING(garden)
GENERATE_SMART_CAST_BUILDING(house)
GENERATE_SMART_CAST_BUILDING(burning_ruin)
GENERATE_SMART_CAST_BUILDING(storage)
GENERATE_SMART_CAST_BUILDING(temple)
GENERATE_SMART_CAST_BUILDING(tax_collector)
GENERATE_SMART_CAST_BUILDING(roadblock)
GENERATE_SMART_CAST_BUILDING(mine)
GENERATE_SMART_CAST_BUILDING(quarry)
GENERATE_SMART_CAST_BUILDING(palace)
GENERATE_SMART_CAST_BUILDING(festival_square)
GENERATE_SMART_CAST_BUILDING(bandstand)
GENERATE_SMART_CAST_BUILDING(routeblock)
GENERATE_SMART_CAST_BUILDING(industry)
GENERATE_SMART_CAST_BUILDING(guild)
GENERATE_SMART_CAST_BUILDING(entertainment)
GENERATE_SMART_CAST_BUILDING(mansion)
GENERATE_SMART_CAST_BUILDING(physician)
GENERATE_SMART_CAST_BUILDING(wharf)
GENERATE_SMART_CAST_BUILDING(shrine)
GENERATE_SMART_CAST_BUILDING(transport_wharf)
GENERATE_SMART_CAST_BUILDING(temple_complex)
GENERATE_SMART_CAST_BUILDING(temple_complex_altar)
GENERATE_SMART_CAST_BUILDING(temple_complex_oracle)
GENERATE_SMART_CAST_BUILDING(water_lift)
GENERATE_SMART_CAST_BUILDING(monument)
GENERATE_SMART_CAST_BUILDING(scribal_school)
GENERATE_SMART_CAST_BUILDING(tower)
GENERATE_SMART_CAST_BUILDING(senet_house)
GENERATE_SMART_CAST_BUILDING(gatehouse)
GENERATE_SMART_CAST_BUILDING(work_camp)

namespace buildings {

typedef building_impl* (*create_building_function_cb)(e_building_type, building&);
typedef void (*load_building_static_params_cb)();

using BuildingCtorIterator = FuncLinkedList<create_building_function_cb>;
using BuildingParamIterator = FuncLinkedList<load_building_static_params_cb>;

template<typename T>
struct model_t : public building_static_params {
    using building_type = T;
    static constexpr e_building_type TYPE = T::TYPE;
    static constexpr pcstr CLSID = T::CLSID;

    model_t() {
        name = CLSID;
        type = TYPE;

        static BuildingCtorIterator ctor_handler(&create);
        static BuildingParamIterator static_params_handler(&static_params_load);
        static typename T::preview planer_renderer;

        building_static_params::register_model(TYPE, *this);
        building_planer_renderer::register_model(TYPE, planer_renderer);
    }

    static void static_params_load() {
        building_static_params &base = building_static_params::ref(TYPE);

        const bool loaded = g_config_arch.r(CLSID, base);
        assert(loaded);

        base.initialize();
    }

    static building_impl *create(e_building_type e, building &b) {
        if (e == TYPE) {
            return b.acquire_impl<building_type>();
        }
        return nullptr;
    }
};

} // buildings

namespace archive_helper {
    template<typename T> 
    inline void reader(archive, buildings::model_t<T> &) {
        // nothing to do, loaded in base class
    }

    template<typename T>
    inline void reader(buildings::model_t<T> &) {
        // nothing to do, loaded in base class
    }
}
