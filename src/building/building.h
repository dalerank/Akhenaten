#pragma once

#include "city/labor_category.h"
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
#include "core/span.hpp"
#include "figure/action.h"
#include "figure/figure_type.h"
#include "game/resource.h"
#include "grid/point.h"
#include "sound/sound_city.h"
#include "core/variant.h"
#include "model.h"

#include <stdint.h>
#include <algorithm>

struct figure;
class io_buffer;
class building;
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
class building_small_mastaba;
class building_wood_cutter;
class building_recruiter;
class building_pavilion;
class building_statue;
class building_ferry;
class building_fort_ground;
class building_fort;
class building_fishing_wharf;
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
struct tooltip_context;
struct object_info;
struct painter;
struct mouse;

constexpr uint32_t MAX_BUILDINGS = 4000;

enum e_labor_state {
    LABOR_STATE_NONE,
    LABOR_STATE_PRESENT,
    LABOR_STATE_JUST_ENTERED
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
    BUILDING_SLOT_PRIEST = 2,
    BUILDING_SLOT_IMMIGRANT = 2,
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

building* building_get(int id);

class building {
private:
    enum { max_figures = 4 };
    class building_impl *_ptr = nullptr; // dcast

    std::array<figure_id, max_figures> figure_ids;

public:
    struct metainfo {
        int help_id;
        int text_id;
    };
    static building::metainfo &get_info(pcstr type);

public:
    int id;
    e_building_state state;
    uint8_t faction_id;
    uint8_t reserved_id;
    uint8_t size;
    uint8_t house_is_merged;
    uint8_t house_size;
    tile2i tile;
    e_building_type type;
    union {
        uint16_t data;
        e_house_level house_level;
        e_resource warehouse_resource_id;
        //        short workshop_type;
        short orientation;
        e_figure_type fort_figure_type;
        short native_meeting_center_id;
        short market_goods;
        short roadblock_exceptions;
        uint8_t barracks_priority;
    } subtype;
    unsigned short road_network_id;
    unsigned short creation_sequence_index;
    short houses_covered;
    short percentage_houses_covered;
    short house_population;
    short house_population_room;
    short distance_from_entry;
    short house_highest_population;
    short house_unreachable_ticks;
    tile2i road_access;
    short figure_spawn_delay;
    unsigned char figure_roam_direction;
    bool has_water_access;
    bool has_open_water_access;
    int prev_part_building_id;
    int next_part_building_id;
    e_resource first_material_id;
    e_resource second_material_id;
    short stored_amount_first;
    short stored_amount_second;
    bool has_well_access;
    short num_workers;
    e_fancy_state fancy_state;
    e_labor_category labor_category;
    e_resource output_resource_first_id;
    e_resource output_resource_second_id;
    uint8_t output_resource_second_rate;
    bool has_road_access;
    short house_criminal_active;
    uint8_t disease_days;
    uint8_t common_health;
    uint8_t malaria_risk;
    short damage_risk;
    short fire_risk;
    short fire_duration;
    unsigned char health_proof;
    unsigned char fire_proof; // cannot catch fire or collapse
    unsigned char damage_proof;
    unsigned char map_random_7bit;
    unsigned char house_tax_coverage;
    unsigned short tax_collector_id;
    short formation_id;
    union impl_data_t {
        struct dock_t {
            short queued_docker_id;
            int dock_tiles[2];
            sbitarray64 trading_goods;
            uint8_t num_ships;
            char orientation;
            short docker_ids[3];
            short trade_ship_id;
            uint8_t docker_anim_frame;
        } dock;
        struct market_t {
            uint16_t inventory[8];
            short pottery_demand;
            short luxurygoods_demand;
            short linen_demand;
            short beer_demand;
            short fetch_inventory_id;
        } market;
        struct granary_t {
            short resource_stored[16];
        } granary;
        struct guild_t {
            uint8_t max_workers;
        } guild;
        struct farm_t {
            uint8_t worker_frame;
        } farm;

        struct education_t {
            e_resource first_material_id;
            e_resource second_material_id;
        } education;

        struct industry_t {
            short ready_production;
            short progress;
            short progress_max;
            bool spawned_worker_this_month;
            uint8_t max_gatheres;
            int unk_b[10];
            bool has_fish;
            uint8_t unk_c[13];
            uint8_t produce_multiplier;
            uint8_t blessing_days_left;
            uint8_t orientation;
            bool has_raw_materials;
            unsigned char curse_days_left;
            int unk_6[5];
            short reserved_id_13;
            int unk_40[40];
            e_labor_state labor_state;
            uint8_t labor_days_left;
            int unk_12[10];
            building_id work_camp_id;
            figure_id worker_id;
            e_figure_type processed_figure;
        } industry;

        struct {
            uint8_t orientation;
            e_figure_type process_type;
            bool reparing;
        } wharf;

        struct entertainment_t {
            uint8_t spawned_entertainer_days;
            uint8_t num_shows;
            uint8_t juggler_visited;
            uint8_t musician_visited;
            uint8_t dancer_visited;
            uint8_t play_index;
            uint32_t booth_corner_grid_offset;
            uint32_t latched_venue_main_grid_offset;
            uint32_t latched_venue_add_grid_offset;
            uint8_t orientation;
            uint8_t ent_reserved_u8;
            e_resource consume_material_id;
        } entertainment;

        struct {
            uint16_t foods[8];
            uint16_t inventory[8];
            uint8_t juggler;
            uint8_t bandstand_juggler;
            uint8_t bandstand_musician;
            uint8_t pavilion_dancer;
            uint8_t senet_player;
            uint8_t magistrate;
            uint8_t hippodrome;
            uint8_t school;
            uint8_t library;
            uint8_t academy;
            uint8_t apothecary;
            uint8_t dentist;
            uint8_t mortuary;
            uint8_t physician;
            uint8_t temple_osiris;
            uint8_t temple_ra;
            uint8_t temple_ptah;
            uint8_t temple_seth;
            uint8_t temple_bast;
            uint8_t no_space_to_expand;
            uint8_t num_foods;
            uint8_t entertainment;
            uint8_t education;
            uint8_t health;
            uint8_t num_gods;
            uint8_t shrine_access;
            uint8_t devolve_delay;
            uint8_t evolve_text_id;
            uint8_t bazaar_access;
            uint8_t water_supply;
        } house;
        struct {
            uint8_t variant;
            uint8_t statue_offset;
            uint8_t temple_complex_attachments;
            uint8_t resources_pct[RESOURCES_MAX];
            uint16_t workers[5];
            int8_t phase;
            uint8_t upgrades;
            uint8_t orientation;
        } monuments;
    } data;
    int tax_income_or_storage;
    unsigned char house_days_without_food;
    bool has_plague;
    signed char desirability;
    bool is_deleted;
    bool is_adjacent_to_water;
    uint16_t storage_id;
    union {
        signed char house_happiness;
        signed char native_anger;
    } sentiment;
    animation_t minimap_anim;
    uint8_t show_on_problem_overlay;
    uint16_t deben_storage;
    animation_context anim;

    building();
    building* main();
    inline building *next() { return building_get(next_part_building_id); }
    inline const building *next() const { return building_get(next_part_building_id); }
    inline bool has_next() const { return next_part_building_id > 0; }
    building* top_xy();
    bool is_main();

    inline bool is_valid() { return type != BUILDING_NONE && state == BUILDING_STATE_VALID; }
    bool is_house();
    bool is_fort();
    bool is_defense();
    bool is_farm();
    bool is_workshop();
    bool is_extractor();
    bool is_monument();
    bool is_palace();
    bool is_tax_collector();
    bool is_governor_mansion();
    bool is_temple();
    bool is_large_temple();
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
    vfs::path get_sound();

    void clear_related_data();
    void clear_impl();
    void reset_impl();
    void new_fill_in_data_for_type(e_building_type type, tile2i tile, int orientation);

    e_overlay get_overlay() const;
    const int get_figure_id(int i) const { return figure_ids[i]; };

    figure* get_figure(int i);
    void bind_iob_figures(io_buffer* iob);
    void set_figure(int i, int figure_id = -1);
    void set_figure(int i, figure* f);
    void remove_figure(int i);
    void remove_figure_by_id(int id);
    bool has_figure(int i, int figure_id = -1);
    bool has_figure(int i, figure* f);
    bool has_figure_of_type(int i, e_figure_type _type);
    int get_figure_slot(figure* f);
    int need_resource_amount(e_resource resource) const;
    int max_storage_amount(e_resource res) const;
    int stored_amount(int idx = 0) const;
    int stored_amount(e_resource res) const;
    
    figure* create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir);
    figure* create_roaming_figure(e_figure_type _type, e_figure_action created_action = FIGURE_ACTION_125_ROAMING, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure* create_figure_with_destination(e_figure_type _type, building* destination, e_figure_action created_action = ACTION_10_GOING, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure* create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action = FIGURE_ACTION_20_CARTPUSHER_INITIAL, e_building_slot slot = BUILDING_SLOT_CARTPUSHER);

    int worker_percentage();
    int figure_spawn_timer();
    void check_labor_problem();
    bool common_spawn_figure_trigger(int min_houses);
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action = FIGURE_ACTION_125_ROAMING);
    bool common_spawn_goods_output_cartpusher(bool only_one = true, bool only_full_loads = true, int min_carry = 100, int max_carry = 800);
    bool workshop_has_resources();
    bool guild_has_resources();
    void workshop_start_production();

public:
    building_impl *dcast();
    building_farm *dcast_farm();
    building_brewery *dcast_brewery();
    building_pottery *dcast_pottery();
    building_storage_yard *dcast_storage_yard();
    building_storage_room *dcast_storage_room();
    building_juggler_school *dcast_juggler_school();
    building_bazaar *dcast_bazaar();
    building_firehouse *dcast_firehouse();
    building_architect_post *dcast_architect_post();
    building_booth *dcast_booth();
    building_apothecary *dcast_apothecary();
    building_granary *dcast_granary();
    building_water_supply *dcast_water_supply();
    building_conservatory *dcast_conservatory();
    building_courthouse *dcast_courthouse();
    building_well *dcast_well();
    building_clay_pit *dcast_clay_pit();
    building_reed_gatherer *dcast_reed_gatherer();
    building_papyrus_maker *dcast_papyrus_maker();
    building_dock *dcast_dock();
    building_work_camp *dcast_work_camp();
    building_small_mastaba *dcast_small_mastaba();
    building_wood_cutter *dcast_wood_cutter();
    building_recruiter *dcast_recruiter();
    building_pavilion *dcast_pavilion();
    building_statue *dcast_statue();
    building_ferry *dcast_ferry();
    building_fort *dcast_fort();
    building_fort_ground *dcast_fort_ground();
    building_fishing_wharf *dcast_fishing_wharf();
    building_shipyard *dcast_shipyard();
    building_plaza *dcast_plaza();
    building_garden *dcast_garden();
    building_house *dcast_house();
    building_burning_ruin *dcast_burning_ruin();
    building_storage *dcast_storage();
    building_temple *dcast_temple();
    building_tax_collector *dcast_tax_collector();
    building_roadblock *dcast_roadblock();
    building_routeblock *dcast_routeblock();
    building_mine *dcast_mine();
    building_quarry *dcast_quarry();
    building_palace *dcast_palace();
    building_festival_square *dcast_festival_square();
    building_bandstand *dcast_bandstand();
    building_industry *dcast_industry();
    building_guild *dcast_guild();
    building_entertainment *dcast_entertainment();

    bool spawn_noble(bool spawned);
    void set_water_supply_graphic();
    void spawn_figure_industry();
    void spawn_figure_native_hut();
    void spawn_figure_native_meeting();

    int get_figures_number(e_figure_type ftype);

    void update_native_crop_progress();
    tile2i access_tile();
    bool figure_generate();

    void monument_add_workers(int fid);
    void monument_remove_worker(int fid);
    void industry_add_workers(int fid);
    void industry_remove_worker(int fid);
};

#define BUILDING_METAINFO(type, clsid) static constexpr e_building_type TYPE = type; static constexpr pcstr CLSID = #clsid;
class building_impl {
public:
    struct static_params {
        e_building_type type;
        static static_params dummy;
        pcstr name;
        bool fire_proof;
        bool damage_proof;
        bool is_draggable;
        bstring64 meta_id;
        building::metainfo meta;
        e_resource output_resource;
        e_resource output_resource_second;
        int output_resource_second_rate;
        e_labor_category labor_category;
        animations_t anim;
        uint8_t building_size;
        int window_info_height_id;
        int planer_relative_orientation;
        uint16_t production_rate;
        bool unique_building;

        void load(archive arch);
    };

    building_impl(building &b) : base(b), data(b.data) {}
    virtual void on_create(int orientation) {}
    virtual void on_place(int orientation, int variant);
    virtual void on_place_update_tiles(int orientation, int variant);
    virtual void on_place_checks();
    virtual void on_destroy() {}
    virtual void on_undo() {}
    virtual void on_post_load() {}
    virtual void spawn_figure() {}
    virtual void update_graphic();
    virtual void update_month() {}
    virtual void update_day();
    virtual void window_info_background(object_info &ctx) {}
    virtual void window_info_foreground(object_info &ctx) {}
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
    virtual int get_produce_uptick_per_day() const { return base.num_workers; }
    virtual int get_fire_risk(int value) const { return value; }
    virtual textid get_tooltip() const { return {0, 0}; }
    virtual int ready_production() const { return params().production_rate; }
    virtual void draw_normal_anim(painter &ctx, vec2i point, tile2i tile, color mask);
    virtual void draw_tooltip(tooltip_context *c) {};
    virtual const static_params &params() const { return params(type()); }
    virtual void bind_dynamic(io_buffer *iob, size_t version);
    virtual bvariant get_property(const xstring &domain, const xstring &name) const;
    virtual bool add_resource(e_resource resource, int amount) { return false; }

    virtual building_farm *dcast_farm() { return nullptr; }
    virtual building_brewery *dcast_brewery() { return nullptr; }
    virtual building_pottery *dcast_pottery() { return nullptr; }
    virtual building_storage_yard *dcast_storage_yard() { return nullptr; }
    virtual building_storage_room *dcast_storage_room() { return nullptr; }
    virtual building_juggler_school *dcast_juggler_school() { return nullptr; }
    virtual building_bazaar *dcast_bazaar() { return nullptr; }
    virtual building_firehouse *dcast_firehouse() { return nullptr; }
    virtual building_architect_post *dcast_architect_post() { return nullptr; }
    virtual building_booth *dcast_booth() { return nullptr; }
    virtual building_apothecary *dcast_apothecary() { return nullptr; }
    virtual building_granary *dcast_granary() { return nullptr; }
    virtual building_water_supply *dcast_water_supply() { return nullptr; }
    virtual building_conservatory *dcast_conservatory() { return nullptr; }
    virtual building_courthouse *dcast_courthouse() { return nullptr; }
    virtual building_well *dcast_well() { return nullptr; }
    virtual building_clay_pit *dcast_clay_pit() { return nullptr; }
    virtual building_reed_gatherer *dcast_reed_gatherer() { return nullptr; }
    virtual building_papyrus_maker *dcast_papyrus_maker() { return nullptr; }
    virtual building_dock *dcast_dock() { return nullptr; }
    virtual building_work_camp *dcast_work_camp() { return nullptr; }
    virtual building_small_mastaba *dcast_small_mastaba() { return nullptr; }
    virtual building_wood_cutter *dcast_wood_cutter() { return nullptr; }
    virtual building_recruiter *dcast_recruiter() { return nullptr; }
    virtual building_pavilion *dcast_pavilion() { return nullptr; }
    virtual building_statue *dcast_statue() { return nullptr; }
    virtual building_ferry *dcast_ferry() { return nullptr; }
    virtual building_fort *dcast_fort() { return nullptr; }
    virtual building_fort_ground *dcast_fort_ground() { return nullptr; }
    virtual building_fishing_wharf *dcast_fishing_wharf() { return nullptr; }
    virtual building_shipyard *dcast_shipyard() { return nullptr; }
    virtual building_plaza *dcast_plaza() { return nullptr; }
    virtual building_garden *dcast_garden() { return nullptr; }
    virtual building_house *dcast_house() { return nullptr; }
    virtual building_burning_ruin *dcast_burning_ruin() { return nullptr; }
    virtual building_storage *dcast_storage() { return nullptr; }
    virtual building_temple *dcast_temple() { return nullptr; }
    virtual building_tax_collector *dcast_tax_collector() { return nullptr; }
    virtual building_roadblock *dcast_roadblock() { return nullptr; }
    virtual building_mine *dcast_mine() { return nullptr; }
    virtual building_quarry *dcast_quarry() { return nullptr; }
    virtual building_palace *dcast_palace() { return nullptr; }
    virtual building_festival_square *dcast_festival_square() { return nullptr; }
    virtual building_bandstand *dcast_bandstand() { return nullptr; }
    virtual building_routeblock *dcast_routeblock() { return nullptr; }
    virtual building_industry *dcast_industry() { return nullptr; }
    virtual building_guild *dcast_guild() { return nullptr; }
    virtual building_entertainment *dcast_entertainment() { return nullptr; }

    inline building_impl *next() { return base.next()->dcast(); }
    inline building_impl *main() { return base.main()->dcast(); }
    inline bool is_main() const { return base.is_main(); }
    inline bool is_valid() const { return base.is_valid(); }
    inline e_building_state state() const { return base.state; }
    inline void check_labor_problem() { base.check_labor_problem(); }
    inline int worker_percentage() const { return base.worker_percentage(); }
    inline void common_spawn_labor_seeker(int min_houses) { base.common_spawn_labor_seeker(min_houses); }
    inline bool common_spawn_figure_trigger(int min_houses) { return base.common_spawn_figure_trigger(min_houses); }
    inline bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action) { return base.common_spawn_roamer(type, min_houses, created_action); }
    inline const model_building *model() const { return model_get_building(type()); }
    inline int max_workers() const { return model_get_building(type())->laborers; }
    inline int pct_workers() const { return calc_percentage<int>(num_workers(), max_workers()); }

    inline bool has_figure_of_type(int i, e_figure_type _type) { return base.has_figure_of_type(i, _type);  }
    inline figure *create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action = ACTION_10_GOING, e_building_slot slot = BUILDING_SLOT_SERVICE) { return base.create_figure_with_destination(_type, destination, created_action, slot); }
    inline figure *create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) { return base.create_roaming_figure(_type, created_action, slot); }
    inline figure *create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir) { return base.create_figure_generic(_type, created_action, slot, created_dir); }
    inline figure *create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action = FIGURE_ACTION_20_CARTPUSHER_INITIAL, e_building_slot slot = BUILDING_SLOT_CARTPUSHER) { return base.create_cartpusher(resource_id, quantity, created_action, slot); }
    inline figure *get_figure(int slot) { return base.get_figure(slot); }
    inline const figure *get_figure(int slot) const { return base.get_figure(slot); }
    
    inline int id() const { return base.id; }
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
    inline const animation_t &anim(const xstring &key) const { return params().anim[key]; }

    virtual bool is_workshop() const { return false; }
    virtual bool is_administration() const { return false; }
    virtual bool is_unique_building() const { return false; }
    virtual void destroy_by_poof(bool clouds);
    virtual void highlight_waypoints();
    virtual void on_tick(bool refresh_only);

    using resources_vec = std::array<e_resource, 4>;
    virtual resources_vec required_resource() const { return {}; }
    building::metainfo get_info() const;
    void set_animation(const animation_t &anim);
    vfs::path get_sound();
    inline void set_animation(const xstring &key) { set_animation(anim(key)); }

    static void params(e_building_type, const static_params &);
    static const static_params &params(e_building_type);

    building &base;
    building::impl_data_t &data;
};

inline bool building_is_house(e_building_type type) { return type >= BUILDING_HOUSE_VACANT_LOT && type <= BUILDING_HOUSE_PALATIAL_ESTATE; }

int building_id_first(e_building_type type);
building* building_first(e_building_type type);

building* building_next(int id, e_building_type type);

inline building* building_begin() { return building_get(1); }
inline building* building_end() { return building_get(MAX_BUILDINGS); }

template<typename ... Args>
bool building_type_any_of(e_building_type type, Args ... args) {
    int types[] = {args...};
    return (std::find(std::begin(types), std::end(types), type) != std::end(types));
}

template<typename ... Args>
bool building_type_any_of(building &b, Args ... args) {
    return building_type_any_of(b.type, args...);
}

template<typename ... Args>
bool building_type_none_of(building &b, Args ... args) {
    int types[] = {args...};
    return (std::find(std::begin(types), std::end(types), b.type) == std::end(types));
}

template<typename Array, typename ... Args>
void buildings_get(Array &arr, Args ... args) {
    int types[] = {args...};
    for (const auto &type : types) {
        for (building *it = building_begin(), *e = building_end(); it != e; ++it) {
            if (it->type == type) {
                arr.push_back(it);
            }
        }
    }
}

building* building_create(e_building_type type, tile2i tile, int orientation);

building* building_at(int grid_offset);
building* building_at(int x, int y);
building* building_at(tile2i point);
bool building_exists_at(int grid_offset, building* b);

bool building_exists_at(tile2i point, building* b);

void building_clear_all();
// void building_totals_add_corrupted_house(int unfixable);

bool building_is_fort(int type);
bool building_is_defense(e_building_type type);
bool building_is_farm(e_building_type type);
inline bool building_is_farm(building &b) { return building_is_farm(b.type); }
bool building_is_floodplain_farm(building &b);
bool building_is_workshop(int type);
bool building_is_extractor(int type);
bool building_is_harvester(e_building_type type);
bool building_is_monument(int type);
bool building_is_administration(e_building_type type);
bool building_is_palace(e_building_type type);
bool building_is_tax_collector(e_building_type type);
bool building_is_governor_mansion(e_building_type type);
bool building_is_temple(int type);
bool building_is_large_temple(int type);
bool building_is_shrine(int type);
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

int building_get_highest_id();
void building_update_highest_id();
void building_update_state();
void building_update_desirability();

int building_mothball_toggle(building* b);
int building_mothball_set(building* b, int value);
bool resource_required_by_workshop(building* b, e_resource resource);

std::span<building>& city_buildings();

template <typename T>
inline building* building_first(T pred) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid() && pred(*it)) {
            return it;
        }
    }
    return nullptr;
}

template <typename ... Args>
inline building* building_first_of_type(Args ... types) {
    for (auto &b: city_buildings()) {
        if (b.is_valid() && building_type_any_of(b, types...)) {
            return &b;
        }
    }
    return nullptr;
}

template<typename T>
inline building* buildings_valid_first(T func) {
    for (auto &b: city_buildings()) {
        if (b.is_valid()) {
            if (func(b)) {
                return &b;
            }
        }
    }
    return nullptr;
}

template<typename T>
void buildings_valid_do(T func) {
    for (auto &b: city_buildings()) {
        if (b.is_valid()) {
            func(b);
        }
    }
}

template<typename T, typename F>
void buildings_valid_do(F func) {
    for (auto &b: city_buildings()) {
        if (!b.is_valid()) {
            continue;
        }
        T *ptr = smart_cast<T*>(b.dcast());
        if (ptr) {
            func(ptr);
        }
    }
}

template<typename T>
void buildings_valid_farms_do(T func) {
    for (auto &b: city_buildings()) {
        if (b.is_valid() && building_is_farm(b)) {
            func(b);
        }
    }
}

template<typename ... Args, typename T>
void buildings_valid_do(T func, Args ... args) {
    for (auto &b: city_buildings()) {
        if (b.is_valid() && building_type_any_of(b, args...)) {
            func(b);
        }
    }
}

template<typename T>
void buildings_house_do(T func) {
    for (auto &b: city_buildings()) {
        if (b.is_valid() && building_is_house(b.type)) {
            func(b);
        }
    }
}

template<typename T>
void buildings_workshop_do(T func) {
    for (auto &b: city_buildings()) {
        if (b.is_valid() && building_is_workshop(b.type)) {
            func(b);
        }
    }
}

namespace buildings {

building_impl *create(e_building_type, building&);
typedef building_impl* (*create_building_function_cb)(e_building_type, building&);
typedef void (*load_building_static_params_cb)();

using BuildingCtorIterator = FuncLinkedList<create_building_function_cb>;
using BuildingParamIterator = FuncLinkedList<load_building_static_params_cb>;

template<typename T>
struct model_t : public building_impl::static_params {
    using building_type = T;
    static constexpr e_building_type TYPE = T::TYPE;
    static constexpr pcstr CLSID = T::CLSID;

    model_t() {
        name = CLSID;
        type = TYPE;

        static BuildingCtorIterator ctor_handler(&create);
        static BuildingParamIterator static_params_handler(&static_params_load);

        building_impl::params(TYPE, *this);
    }

    void load() {
        bool loaded = false;
        g_config_arch.r_section(name, [&] (archive arch) {
            static_params::load(arch);
            loaded = true;
            this->load(arch);
        });
        assert(loaded);
    }

    virtual void load(archive) {
        /*overload options*/
    }

    static void static_params_load() {
        const model_t &item = static_cast<const model_t&>(building_impl::params(TYPE));
        assert(item.TYPE == TYPE);
        const_cast<model_t&>(item).load();
    }

    static building_impl *create(e_building_type e, building &data) {
        if (e == TYPE) {
            return new building_type(data);
        }
        return nullptr;
    }
};

} // buildings
