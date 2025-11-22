#pragma once

#include "core/core.h"
#include "core/buffer.h"
#include "core/string.h"
#include "core/direction.h"
#include "core/circullar_buffer.h"
#include "figure/action.h"
#include "figure/formation.h"
#include "figure/figure_type.h"
#include "empire/empire_city.h"
#include "grid/point.h"
#include "grid/routing/routing_fwd.h"
#include "graphics/image_desc.h"
#include "io/io_buffer.h"
#include "window/building/common.h"
#include "figure_phrase.h"
#include "core/tokenum.h"
#include "graphics/animation.h"
#include "sound/sound_walker.h"

#include <algorithm>
#include <memory.h>

class building;
class figure_impl;
class figure_immigrant;
class figure_cartpusher;
class figure_storageyard_cart;
class figure_trade_ship;
class figure_sled;
class figure_musician;
class figure_dancer;
class figure_labor_seeker;
class figure_worker;
class figure_soldier;
class figure_fishing_boat;
class figure_fishing_point;
class figure_trade_caravan;
class figure_caravan_donkey;
class figure_transport_ship;
class figure_stonemason;
class figure_warship;
class figure_enemy;
class figure_enemy_archer;
class figure_enemy_spearman;
class figure_fireman;
class figure_missile;
class figure_emigrant;
class figure_homeless;
class figure_festival_guy;
class figure_ostrich;
class figure_antelope;
class figure_hippo;
class figure_animal;
class figure_ballista;
class figure_market_buyer;
class figure_bricklayer;

struct animation_t;
struct figure_static_params;

constexpr int MAX_FIGURES = 2000;
constexpr int MAX_CLOUD_IMAGE_OFFSETS = 19;

enum e_minimap_figure_color {
    FIGURE_COLOR_NONE = 0,
    FIGURE_COLOR_SOLDIER = 1,
    FIGURE_COLOR_ENEMY = 2,
    FIGURE_COLOR_WOLF = 3,
    FIGURE_COLOR_ANIMAL = 4
};

enum e_nearby { 
    NEARBY_ANY, 
    NEARBY_ANIMAL, 
    NEARBY_HOSTILE 
};

enum e_move_type : uint8_t {
    EMOVE_TERRAIN = 0,
    EMOVE_WATER = 1,
    EMOVE_DEEPWATER = 2,
    EMOVE_AMPHIBIAN = 3,
};

struct nearby_result {
    figure_id fid = 0;
    int distance = 0;
};

enum e_figure_draw_mode { 
    e_figure_draw_none = 0, 
    e_figure_draw_overlay = 0x1,
    e_figure_draw_routing = 0x2,
    e_figure_draw_carry = 0x4,
    e_figure_draw_building = 0x8,
    e_figure_draw_festival = 0x10,
    e_figure_cross_country_move = 0x20,
};

enum e_figure_flag {
    e_figure_flag_none = 0,
    e_figure_flag_enemy = 1 << 0,
    e_figure_flag_friendly = 1 << 1,
    e_figure_flag_soldier = 1 << 2,
    e_figure_flag_criminal = 1 << 3,
};

class figure {
public: 
    using ptr_buffer_t = char[16];

private:
    ptr_buffer_t _ptr_buffer = { 0 };
    figure_impl *_ptr = nullptr;

public:
    char runtime_data[40] = { 0 };
    e_resource resource_id;
    uint16_t resource_amount_full; // full load counter

    uint16_t home_building_id;
    uint16_t destination_building_id;

    figure_id id;
    uint16_t main_image_id;
    uint16_t cart_image_id;
    bool use_cart;
    animation_context animctx;

    uint8_t alternative_location_index;
    figure_id next_figure;
    e_figure_type type;

    bool use_cross_country;
    e_figure_state state;
    uint8_t faction_id; // 1 = city, 0 = enemy
    uint8_t action_state_before_attack;
    uint8_t direction;
    uint8_t previous_tile_direction;
    uint8_t attack_direction;
    tile2i tile;
    tile2i previous_tile;
    tile2i source_tile;
    tile2i destination_tile;

    uint16_t missile_damage;
    uint16_t damage;

    uint8_t terrain_type;
    short wait_ticks;
    short action_state;
    uint8_t progress_inside_speed;
    int8_t progress_inside;
    uint8_t progress_on_tile;
    short routing_path_id;
    short routing_path_current_tile;
    short routing_path_length;

    uint8_t in_building_wait_ticks;
    uint8_t outside_road_ticks;

    short max_roam_length;
    short roam_length;

    bool roam_wander_freely;
    uint8_t roam_random_counter;
    circular_buffer<int, 6> roam_history;
    int8_t roam_turn_direction;
    int8_t roam_ticks_until_next_turn;

    vec2i cc_coords;
    vec2i cc_destination;
    vec2i cc_delta;
    short cc_delta_xy;
    uint8_t cc_direction; // 1 = x, 2 = y
    uint8_t speed_multiplier;

    short formation_id;
    uint8_t index_in_formation;
    uint8_t formation_at_rest;
    bool is_main_drawn;
    bool is_cart_drawn;
    uint8_t min_max_seen;
    uint8_t movement_ticks_watchdog;
    short leading_figure_id;
    uint8_t attack_image_offset;
    uint8_t wait_ticks_missile;
    vec2i cart_offset;

    bstring32 name;
    uint8_t terrain_usage;
    e_move_type allow_move_type;
    uint8_t height_adjusted_ticks;
    uint8_t current_height;
    uint8_t target_height;
    uint8_t collecting_item_id; // NOT a resource ID for cartpushers! IS a resource ID for warehousemen
    xstring phrase_key;
    figure_id target_figure_id;
    short targeted_by_figure_id;
    //unsigned short created_sequence;
    //unsigned short target_figure_created_sequence;
    unsigned char num_attackers;
    short attacker_id1;
    short attacker_id2;
    short opponent_id;
    vec2i main_cached_pos;
    vec2i cart_cached_pos;

    // 7 bytes 00 00 00 00 00 00 00
    unsigned char routing_try_reroute_counter;
    uint16_t collecting_item_max;
    unsigned short sender_building_id;

    // 115 bytes
    uint8_t draw_mode;
    uint32_t flags;
    
    figure_impl *dcast();
    const figure_impl *dcast() const;

    template<typename T>
    T *dcast() {
        return smart_cast<T *>(dcast());
    }

    template<typename T>
    const T *dcast() const {
        return smart_cast<T *>(dcast());
    }

    #define ALLOW_SMART_CAST_FIGURE(type) figure_##type *dcast_##type() { return dcast<figure_##type>(); }
    ALLOW_SMART_CAST_FIGURE(immigrant)
    ALLOW_SMART_CAST_FIGURE(emigrant)
    ALLOW_SMART_CAST_FIGURE(homeless)
    ALLOW_SMART_CAST_FIGURE(festival_guy)
    ALLOW_SMART_CAST_FIGURE(enemy_spearman)
    ALLOW_SMART_CAST_FIGURE(ostrich)
    ALLOW_SMART_CAST_FIGURE(hippo)
    ALLOW_SMART_CAST_FIGURE(antelope)
    ALLOW_SMART_CAST_FIGURE(animal)
    ALLOW_SMART_CAST_FIGURE(ballista)
    ALLOW_SMART_CAST_FIGURE(market_buyer)
    ALLOW_SMART_CAST_FIGURE(bricklayer)

    figure(int _id) {
        // ...can't be bothered to add default values to ALL
        // the above members of "figure" ....for now...
        memset(this, 0, sizeof(figure));
        id = _id;
    };

    // map search tests
    bool in_roam_history(int goffset);
    void add_roam_history(int goffset);

    void apply_damage(int hit_dmg, figure_id attaker_id);

    bool is_dead(); 
    inline bool is_enemy() const { return !!(flags & e_figure_flag_enemy); }
    inline bool is_criminal() const { return !!(flags & e_figure_flag_criminal); }
    inline bool is_friendly() const { return !!(flags & e_figure_flag_friendly); }
    inline bool is_soldier() const { return !!(flags & e_figure_flag_soldier); }
    bool is_herd();
    bool is_citizen();          
    bool is_non_citizen();
    bool is_fighting_friendly(); 
    bool is_fighting_enemy();
    e_minimap_figure_color get_figure_color(); 
    const figure_static_params &params() const;
    const animation_t &anim(const xstring &key);

    void kill();

    bool is_boat();
    bool can_move_by_water();
    bool can_move_by_terrain();
    void set_direction_to(building *b);
    void clear_impl();

    e_figure_category category() const;
    uint16_t max_damage() const;
    int8_t attack_value() const;
    int8_t defense_value() const;
    int8_t missile_defense_value() const;

    void poof();
    inline bool available() { return state == FIGURE_STATE_NONE; };
    inline bool is_valid() const { return state != FIGURE_STATE_NONE; }
    inline bool is_alive() { return state == FIGURE_STATE_ALIVE; }
    inline bool has_type(e_figure_type value) { return type == value; }
    inline bool has_state(e_figure_state value) { return state == value; }
    bool has_cart() const;

    inline void set_state(e_figure_state s) { state = s; };
    void bind(io_buffer* iob);

    // figure/figure.c
    void figure_delete_UNSAFE();
    building* home();

    building* destination();
    const int homeID() const {
        return home_building_id;
    }
    const int destinationID() const {
        return destination_building_id;
    }

    void set_home(int _id);
    void set_destination(building_id _id);
    void set_home(building* b);
    void set_destination(building* b);
    bool has_home(int _id = -1);
    bool has_home(building* b);
    bool has_destination(int _id = -1);
    bool has_destination(building* b);
    xstring action_tip();

    //    bool is_roamer();

    // grid/figure.c
    void map_figure_add();
    void map_figure_update();
    void map_figure_remove();
    void figure_route_add();
    void route_remove();

    void reset_flags();

    // image.c
    void image_set_animation(const animation_t &anim);
    void image_set_animation(const xstring &anim);
    void image_set_animation(int collection, int group, int offset = 0, int max_frames = 12, int duration = 1, bool loop = true);
    void figure_image_update(bool refresh_only);
    void figure_image_set_sled_offset(int direction);
    void figure_image_set_cart_offset(int direction);
    int figure_image_corpse_offset();
    int figure_image_missile_launcher_offset();
    int figure_image_direction();
    vec2i tile_pixel_coords();

    // city_figure.c
    void draw_debug();
    vec2i adjust_pixel_offset(const vec2i pixel);
    vec2i main_sprite_pixel() const;
    vec2i cart_sprite_pixel() const;
    //    void draw_figure(int x, int y, int highlight);
    void draw_figure_main(painter &ctx, vec2i pixel, int highlight);
    void draw_figure_cart(painter &ctx, vec2i pixel, int highlight);
    void city_draw_figure(painter &ctx, int highlight);
    //    void city_draw_selected_figure(int x, int y, pixel_coordinate *coord);
    void draw_map_flag(vec2i pixel, int highlight, vec2i* coord_out = nullptr);

    // movement.c
    void advance_figure_tick();
    void set_target_height_bridge();
    void set_target_height_building();
    e_permission get_permission_for_figure();
    void move_to_next_tile();
    void set_next_tile_and_direction();
    void advance_route_tile(int roaming_enabled);
    void init_roaming_from_building(int roam_dir);
    void roam_set_direction();
    void move_ticks(int num_ticks, bool roaming_enabled = false);
    int roam_ticks(int num_ticks);
    void follow_ticks(int num_ticks);
    void advance_attack();
    void set_cross_country_direction(int x_src, int y_src, int x_dst, int y_dst, int is_missile);
    void set_cross_country_destination(tile2i dst);
    bool move_ticks_cross_country(int num_ticks);

    void cross_country_update_delta();
    void cross_country_advance_x();
    void cross_country_advance_y();
    void cross_country_advance();

    // actions.c
    void action_perform();
    void advance_action(short next_action);
    bool do_roam(int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = ACTION_126_ROAMER_RETURNING);
    bool do_goto(tile2i dest, int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_gotobuilding(building* dest, bool stop_at_road = true, e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_returnhome(e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1);
    bool do_exitbuilding(bool invisible, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_enterbuilding(bool invisible, building* b, short NEXT_ACTION = -1, short FAIL_ACTION = -1);

    void editor_flag_action();
    void hippodrome_horse_action();

    nearby_result is_nearby(int category, int max_distance = 10000, bool gang_on = true, std::function<bool(figure *)> avoid = [] (auto f) { return false; });

    inline void set_resource(e_resource resource) { resource_id = resource; }
    e_resource get_resource() const { return resource_id; }
    int get_carrying_amount();
    void cart_image_update();
    
    int trader_total_sold();

    int target_is_alive();
    int get_direction();
    int get_missile_direction(const formation* m);

    void javelin_launch_missile();
    void legionary_attack_adjacent_enemy();
    int find_mop_up_target();

    void figure_combat_handle_corpse();
    void resume_activity_after_attack();
    void hit_opponent();
    void figure_combat_handle_attack();
    void figure_combat_attack_figure_at(int grid_offset);
    int figure_image_normalize_direction(int dir);

    // sound.c
    void play_die_sound();
    void play_hit_sound();

    // phrase.c
    void figure_phrase_determine();
    int figure_play_phrase_file();

    // service.c
    int figure_service_provide_coverage();

    resource_tile find_resource_tile(e_resource resource);

    template<typename T>
    figure_impl *acquire_impl() {
        new (&_ptr_buffer) T(this);
        _ptr = (figure_impl *)&_ptr_buffer;
        return _ptr;
    }
};

#define FIGURE_METAINFO(type, clsid)                            \
    using self_type = clsid;                                    \
    using model_type = figures::model_t<clsid>;                 \
    static constexpr pcstr CLSID = #clsid;                      \
    static constexpr e_figure_type TYPE = type;                                               

#define FIGURE_RUNTIME_DATA(type) ;                                                                   \
    type& runtime_data() { return *(type*)this->base.runtime_data; }                                  \
    const type& runtime_data() const { static_assert(sizeof(type) < sizeof(figure::runtime_data)); return *(type*)this->base.runtime_data; }  

#define FIGURE_RUNTIME_DATA_T FIGURE_RUNTIME_DATA(runtime_data_t)

#define FIGURE_STATIC_DATA(type) ;                              \
    static const type &current_params() { return (const type &)figure_static_params::get(TYPE); }

#define FIGURE_STATIC_DATA_T FIGURE_STATIC_DATA(static_params)

struct fproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(figure&, const xstring&)> handler;
};

struct figure_static_params {
    static figure_static_params dummy;

    e_figure_type ftype;
    pcstr name;

    int8_t terrain_usage;
    animations_t animations;
    figure_sounds_t sounds;
    uint16_t max_roam_length;
    uint8_t speed_mult;
    metainfo meta;
    e_permission permission;
    bool is_enemy;
    bool is_soldier;
    e_figure_category category;
    uint16_t max_damage;
    int8_t attack_value;
    int8_t defense_value;
    int8_t missile_defense_value;
    uint16_t corpse_time_delay;

    static void set(e_figure_type, const figure_static_params &);
    static const figure_static_params &get(e_figure_type);
    static figure_static_params &ref(e_figure_type);

    void initialize();
};
ANK_CONFIG_STRUCT(figure_static_params, terrain_usage,  animations, sounds, 
    max_roam_length, speed_mult, meta, permission, is_enemy, is_soldier, category, attack_value, defense_value,
    missile_defense_value, corpse_time_delay)

class figure_impl {
public:
    figure_impl(figure *f) : base(*f) {}

    virtual void on_create();
    virtual void on_destroy() {}
    virtual void on_post_load();
    virtual void on_change_terrain(int old, int current);
    virtual void on_attacked(figure *attacker);
    virtual void figure_action() {}
    virtual void figure_before_action() {}
    virtual void figure_roaming_action();
    virtual bool window_info_background(object_info &ctx) { return false; }
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight);
    virtual void before_poof() {}
    virtual void poof() { base.poof(); }
    virtual e_overlay get_overlay() const { return OVERLAY_NONE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const;
    virtual sound_key phrase_key() const { return "empty"; }
    virtual sound_key default_phrase_key() const;
    virtual int provide_service() { return 0; }
    virtual bool play_die_sound() { return false; }
    virtual void update_animation();
    virtual void update_day() {}
    virtual bool can_move_by_water() const;
    virtual void cart_image_update() { base.cart_image_update(); }
    virtual void main_image_update();
    virtual e_minimap_figure_color minimap_color() const { return FIGURE_COLOR_NONE; }
    virtual const animations_t &anim() const { return current_params().animations; }
    virtual void kill();
    virtual void on_action_changed(int saved_action) {}
    virtual void on_config_reload() {}
    virtual void on_update_home() {}
    virtual xstring action_tip() const { static xstring tip(""); return tip; }
    virtual void debug_show_properties() {}
    virtual void debug_draw() {}
    virtual bool is_home(const building *b) const { return base.home_building_id > 0 && base.home_building_id == b->id; }
    virtual empire_city_handle empire_city() const { return empire_city_handle{}; }
    virtual void formation_reset_to_initial(const formation *m) {}
    virtual void apply_damage(int hit_dmg, figure_id attaker_id) { base.damage += hit_dmg; }

    static void acquire(e_figure_type e, figure &b);
    virtual bvariant get_property(const xstring &domain, const xstring &name) const;

    #define ALLOW_SMART_CAST_FIGURE_I(type) virtual figure_##type *dcast_##type() { return nullptr; }
    ALLOW_SMART_CAST_FIGURE_I(immigrant)
    ALLOW_SMART_CAST_FIGURE_I(emigrant)
    ALLOW_SMART_CAST_FIGURE_I(homeless)
    ALLOW_SMART_CAST_FIGURE_I(cartpusher)
    ALLOW_SMART_CAST_FIGURE_I(storageyard_cart)
    ALLOW_SMART_CAST_FIGURE_I(trade_ship)
    ALLOW_SMART_CAST_FIGURE_I(sled)
    ALLOW_SMART_CAST_FIGURE_I(musician)
    ALLOW_SMART_CAST_FIGURE_I(dancer)
    ALLOW_SMART_CAST_FIGURE_I(labor_seeker)
    ALLOW_SMART_CAST_FIGURE_I(worker)
    ALLOW_SMART_CAST_FIGURE_I(soldier)
    ALLOW_SMART_CAST_FIGURE_I(fishing_boat)
    ALLOW_SMART_CAST_FIGURE_I(fishing_point)
    ALLOW_SMART_CAST_FIGURE_I(caravan_donkey)
    ALLOW_SMART_CAST_FIGURE_I(trade_caravan)
    ALLOW_SMART_CAST_FIGURE_I(warship)
    ALLOW_SMART_CAST_FIGURE_I(transport_ship)
    ALLOW_SMART_CAST_FIGURE_I(stonemason)
    ALLOW_SMART_CAST_FIGURE_I(enemy)
    ALLOW_SMART_CAST_FIGURE_I(enemy_archer)
    ALLOW_SMART_CAST_FIGURE_I(enemy_spearman)
    ALLOW_SMART_CAST_FIGURE_I(missile)
    ALLOW_SMART_CAST_FIGURE_I(fireman)
    ALLOW_SMART_CAST_FIGURE_I(festival_guy)
    ALLOW_SMART_CAST_FIGURE_I(ostrich)
    ALLOW_SMART_CAST_FIGURE_I(antelope)
    ALLOW_SMART_CAST_FIGURE_I(hippo)
    ALLOW_SMART_CAST_FIGURE_I(animal)
    ALLOW_SMART_CAST_FIGURE_I(ballista)
    ALLOW_SMART_CAST_FIGURE_I(market_buyer)
    ALLOW_SMART_CAST_FIGURE_I(bricklayer)

    inline building *home() { return base.home(); }
    inline e_figure_type type() const { return base.type; }
    inline int id() { return base.id; }
    inline short action_state() const { return base.action_state; }

    template<typename ... Args>
    bool action_state(const Args... args) const {
        int states[] = {args...};
        return std::find(std::begin(states), std::end(states), base.action_state) != std::end(states);
    }

    inline uint8_t direction() const { return base.direction; }
    inline const building *home() const { return base.home(); }
    inline const animation_t &anim(const xstring &anim_key) const { return base.anim(anim_key); }
    inline animation_context &animation() { return base.animctx; }
    inline const animation_context &animation() const { return base.animctx; }
    inline void advance_action(int action) { int saved_action = action; base.advance_action(action); on_action_changed(saved_action); }
           void advance_action(int action, tile2i t);
    inline bool do_returnhome(e_terrain_usage terrainchoice, short next_action = -1) { return base.do_returnhome(terrainchoice, next_action); }
    inline bool do_gotobuilding(building *dest, bool stop_at_road = true, e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1) { return base.do_gotobuilding(dest, stop_at_road, terrainchoice, NEXT_ACTION, FAIL_ACTION); }
    inline bool do_enterbuilding(bool invisible, building *b, short next_action = -1, short fail_action = -1) { return base.do_enterbuilding(invisible, b, next_action, fail_action); }
    inline bool do_exitbuilding(bool invisible, short next_action = -1, short fail_action = -1) { return base.do_exitbuilding(invisible, next_action, fail_action); }
    inline bool do_roam(int terrainchoice, short next_action) { return base.do_roam(terrainchoice, next_action); }
    inline bool do_goto(tile2i dest, int terrainchoice = TERRAIN_USAGE_ROADS, short next_action = -1, short fail_action = -1) { return base.do_goto(dest, terrainchoice, next_action, fail_action); }
    inline tile2i tile() const { return base.tile; }
    inline int tilex() const { return base.tile.x(); }
    inline int tiley() const { return base.tile.y(); }
    inline building *destination() const { return base.destination(); }
    inline void route_remove() { base.route_remove(); }
    inline void image_set_animation(const xstring &anim_key) { image_set_animation(anim(anim_key)); }
    inline void image_set_animation(const animation_t &anim) { base.image_set_animation(anim); }
    inline void follow_ticks(int num_ticks) { base.follow_ticks(num_ticks); }
    inline bool has_destination(int _id = -1) { return base.has_destination(_id); }
    inline void set_destination(building_id _id) { base.set_destination(_id); }
    inline void set_destination(building *b) { base.set_destination(b); }
           void set_destination(building *b, tile2i t);
    inline void set_home(int _id) { base.set_home(_id); }
    inline void set_home(building *b) { base.set_home(b); }
    inline void set_direction_to(building *b) { return base.set_direction_to(b); }
    inline bool is_alive() const { return base.is_alive(); }
    inline e_permission get_permission() const { return current_params().permission; }

    struct static_params : figure_static_params {};
    inline const static_params &current_params() const { return (const static_params &)figure_static_params::get(type()); }
    inline const static_params &current_params() { return (static_params &)figure_static_params::get(type()); }
    inline const static_params &params() const { return (const static_params &)figure_static_params::get(type()); }
    inline const static_params &params() { return (static_params &)figure_static_params::get(type()); }

    metainfo get_info() const;

    figure &base;
};

GENERATE_SMART_CAST(figure_impl)
#define GENERATE_SMART_CAST_FIGURE(type) GENERATE_SMART_CAST_CUSTOM(figure_##type, type)
GENERATE_SMART_CAST_FIGURE(fishing_point)
GENERATE_SMART_CAST_FIGURE(immigrant)
GENERATE_SMART_CAST_FIGURE(emigrant)
GENERATE_SMART_CAST_FIGURE(homeless)
GENERATE_SMART_CAST_FIGURE(cartpusher)
GENERATE_SMART_CAST_FIGURE(storageyard_cart)
GENERATE_SMART_CAST_FIGURE(trade_ship)
GENERATE_SMART_CAST_FIGURE(sled)
GENERATE_SMART_CAST_FIGURE(musician)
GENERATE_SMART_CAST_FIGURE(dancer)
GENERATE_SMART_CAST_FIGURE(labor_seeker)
GENERATE_SMART_CAST_FIGURE(worker)
GENERATE_SMART_CAST_FIGURE(fishing_boat)
GENERATE_SMART_CAST_FIGURE(soldier)
GENERATE_SMART_CAST_FIGURE(warship)
GENERATE_SMART_CAST_FIGURE(caravan_donkey)
GENERATE_SMART_CAST_FIGURE(trade_caravan)
GENERATE_SMART_CAST_FIGURE(transport_ship)
GENERATE_SMART_CAST_FIGURE(stonemason)
GENERATE_SMART_CAST_FIGURE(enemy)
GENERATE_SMART_CAST_FIGURE(enemy_archer)
GENERATE_SMART_CAST_FIGURE(enemy_spearman)
GENERATE_SMART_CAST_FIGURE(missile)
GENERATE_SMART_CAST_FIGURE(fireman)
GENERATE_SMART_CAST_FIGURE(festival_guy)
GENERATE_SMART_CAST_FIGURE(ostrich)
GENERATE_SMART_CAST_FIGURE(antelope)
GENERATE_SMART_CAST_FIGURE(hippo)
GENERATE_SMART_CAST_FIGURE(animal)
GENERATE_SMART_CAST_FIGURE(ballista)
GENERATE_SMART_CAST_FIGURE(market_buyer)
GENERATE_SMART_CAST_FIGURE(bricklayer)

template <typename dest_type>
inline dest_type *smart_cast(figure *b) {
    return ::smart_cast<dest_type*>(b->dcast());
}

figure *figure_create(e_figure_type type, tile2i tile, int dir);
int figure_movement_can_launch_cross_country_missile(tile2i src, tile2i dst);
void figure_create_explosion_cloud(tile2i tile, int size);

namespace figures {

figure_impl *create(e_figure_type, figure&);
typedef figure_impl* (*create_figure_function_cb)(e_figure_type, figure&);
typedef void (*load_figure_static_params_cb)();

using FigureCtorIterator = FuncLinkedList<create_figure_function_cb>;
using FigureStaticParamIterator = FuncLinkedList<load_figure_static_params_cb>;

template<typename T>
struct model_t {
    using figure_type = T;
    static constexpr e_figure_type TYPE = T::TYPE;
    static constexpr pcstr CLSID = T::CLSID;

    static typename T::static_params &static_params() {
        static typename T::static_params _instance;
        return _instance;
    }

    model_t() {
        static_assert(sizeof(T) == sizeof(figure_impl), "Derived class contains extra data");

        static_params().name = CLSID;
        static_params().ftype = TYPE;

        static FigureCtorIterator config_handler(&create);
        static FigureStaticParamIterator static_params_handler(&static_params_load);
        
        figure_static_params::set(TYPE, static_params());
    }

    static void static_params_load() {
        figure_static_params &base = figure_static_params::ref(TYPE);

        bool loaded = g_config_arch.r(CLSID, base);
        assert(loaded);

        g_config_arch.r(CLSID, static_params());

        base.initialize();
    }

    static figure_impl *create(e_figure_type e, figure &f) {
        if (e == TYPE) {
            return f.acquire_impl<figure_type>();
        }
        return nullptr;
    }
};

} // end namespace figures

namespace archive_helper {
    template<>
    inline void reader<figure_impl::static_params>(archive arch, figure_impl::static_params &params) {
        figure_static_params &fparams = (figure_static_params &)params;
        archive_helper::reader(arch, fparams);
    }
}