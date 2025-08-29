#pragma once

#include "core/core.h"
#include "core/buffer.h"
#include "core/string.h"
#include "core/direction.h"
#include "core/circullar_buffer.h"
#include "figure/action.h"
#include "figure/formation.h"
#include "figure/figure_type.h"
#include "grid/point.h"
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
class figure_caravan_donkey;
class figure_transport_ship;
class figure_warship;

struct animation_t;

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

enum e_figure_draw_debug_mode {
    FIGURE_DRAW_DEBUG_ROUTING = 2
};

extern const token_holder<e_permission, epermission_none, epermission_count> e_permission_tokens;

class figure {
public:
    using ptr_buffer_t = char[24];
    ptr_buffer_t _ptr_buffer = { 0 };
    figure_impl *_ptr = nullptr;

    e_resource resource_id;
    uint16_t resource_amount_full; // full load counter

    uint16_t home_building_id;
    uint16_t immigrant_home_building_id;
    uint16_t destination_building_id;

    figure_id id;
    uint16_t sprite_image_id;
    uint16_t cart_image_id;
    animation_context anim;
    bool is_enemy_image;

    uint8_t alternative_location_index;
    bool flotsam_visible;
    uint16_t next_figure;
    e_figure_type type;

    bool use_cross_country;
    bool is_friendly;
    uint8_t state;
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
    uint8_t migrant_num_people;
    bool is_drawn;
    uint8_t min_max_seen;
    uint8_t movement_ticks_watchdog;
    short leading_figure_id;
    uint8_t attack_image_offset;
    uint8_t wait_ticks_missile;
    vec2i cart_offset;

    uint8_t empire_city_id;
    uint16_t trader_amount_bought;
    uint16_t name;
    uint8_t terrain_usage;
    e_move_type allow_move_type;
    uint8_t height_adjusted_ticks;
    uint8_t current_height;
    uint8_t target_height;
    uint8_t collecting_item_id; // NOT a resource ID for cartpushers! IS a resource ID for warehousemen
    uint8_t trade_ship_failed_dock_attempts;
    uint8_t phrase_sequence_exact;
    textid phrase;
    xstring phrase_key;
    uint8_t phrase_sequence_city;
    uint8_t trader_id;
    uint8_t wait_ticks_next_target;
    short target_figure_id;
    short targeted_by_figure_id;
    //unsigned short created_sequence;
    //unsigned short target_figure_created_sequence;
    unsigned char num_attackers;
    short attacker_id1;
    short attacker_id2;
    short opponent_id;
    vec2i cached_pos;

    // pharaoh

    // 7 bytes 00 00 00 00 00 00 00
    unsigned char routing_try_reroute_counter;
    uint16_t collecting_item_max;
    unsigned short sender_building_id;
    short market_lady_resource_image_offset;
    // 12 bytes FFFF FFFF FFFF FFFF FFFF FFFF
    short market_lady_returning_home_id;
    // 14 bytes 00 00 00 00 00 00 00 ...
    short market_lady_bought_amount;
    // 115 bytes
    uint8_t draw_debug_mode;
    union data_t {
        struct {
            short see_low_health;
            short reserved_1;
            short reserved_2;
        } herbalist;

        struct {
            short poor_taxed;
            short middle_taxed;
            short reach_taxed;
        } taxman;

        struct {
            short frame;
        } flotsam;

        struct {
            short offset;
            short max_step;
            short current_step;
        } fishpoint;

        struct {
            short idle_wait_count;
            building_id destination_bid;
        } bricklayer;

        struct {
            short idle_wait_count;
            building_id destination_bid;
        } stonemason;

        struct {
            short active_order;
        } warship;

        short value[3];
    } data;
    char festival_remaining_dances;
    
    figure_impl *dcast();

    figure(int _id) {
        // ...can't be bothered to add default values to ALL
        // the above members of "figure" ....for now...
        memset(this, 0, sizeof(figure));
        id = _id;
    };

    // map search tests
    bool in_roam_history(int goffset);
    void add_roam_history(int goffset);

    bool is_dead(); // figure.c
    bool is_enemy();
    bool is_herd();
    bool is_formation();        // formation_legion.c
    bool is_attacking_native(); // combat.c
    bool is_citizen();          // missile.c
    bool is_non_citizen();
    bool is_fighting_friendly(); // routing.c
    bool is_fighting_enemy();
    e_minimap_figure_color get_figure_color(); // minimap.c

    void kill();

    bool is_boat();
    bool can_move_by_water();
    bool can_move_by_terrain();
    void set_direction_to(building *b);
    void clear_impl();

    void poof();
    inline bool available() { return state == FIGURE_STATE_NONE; };
    inline bool is_valid() const { return state != FIGURE_STATE_NONE; }
    inline bool is_alive() { return state == FIGURE_STATE_ALIVE; }
    inline bool has_type(e_figure_type value) { return type == value; }
    inline bool has_state(e_figure_state value) { return state == value; }

    inline void set_state(e_figure_state s) { state = s; };
    void bind(io_buffer* iob);

    // figure/figure.c
    void figure_delete_UNSAFE();
    building* home();

    building* destination();
    const int homeID() const {
        return home_building_id;
    }
    const int immigrant_homeID() const {
        return immigrant_home_building_id;
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

    // image.c
    void image_set_animation(const animation_t &anim);
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
    vec2i adjust_pixel_offset(const vec2i &pixel);
    //    void draw_figure(int x, int y, int highlight);
    void draw_figure_main(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out = nullptr);
    void draw_figure_cart(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out = nullptr);
    void city_draw_figure(painter &ctx, int highlight, vec2i* coord_out = nullptr);
    //    void city_draw_selected_figure(int x, int y, pixel_coordinate *coord);
    void draw_figure_with_cart(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out = nullptr);
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
    bool do_roam(int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = ACTION_2_ROAMERS_RETURNING);
    bool do_goto(tile2i dest, int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_gotobuilding(building* dest, bool stop_at_road = true, e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_returnhome(e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1);
    bool do_exitbuilding(bool invisible, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_enterbuilding(bool invisible, building* b, short NEXT_ACTION = -1, short FAIL_ACTION = -1);

    void rioter_action();
    void editor_flag_action();
    void noble_action();
    void indigenous_native_action();
    void enemy43_spear_action();
    void enemy44_sword_action();
    void enemy45_sword_action();
    void enemy_camel_action();
    void enemy_elephant_action();
    void enemy_chariot_action();
    void enemy49_fast_sword_action();
    void enemy50_sword_action();
    void enemy51_spear_action();
    void enemy52_mounted_archer_action();
    void enemy53_axe_action();
    void enemy_gladiator_action();
    void enemy_kingdome_soldier_action();
    void ballista_action();
    void zebra_action();
    void hippodrome_horse_action();

    int is_nearby(int category, int* distance, int max_distance = 10000, bool gang_on = true);
    bool herd_roost(int step, int bias, int max_dist, int terrain_mask);

    inline void set_resource(e_resource resource) { resource_id = resource; }
    e_resource get_resource() const { return resource_id; }
    int get_carrying_amount();
    void determine_deliveryman_destination_food();
    void cart_update_image();
    
    int trader_total_bought();
    int trader_total_sold();

    int target_is_alive();

    int figure_rioter_collapse_building();

    void enemy_initial(formation* m);
    void enemy_marching(const formation* m);
    void enemy_fighting(const formation* m);
    void enemy_action(formation* m);
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

    // sound.c
    void play_die_sound();
    void play_hit_sound();

    // phrase.c
    void figure_phrase_determine();
    int figure_phrase_play();

    // service.c
    int figure_service_provide_coverage();

    // grid/marshland.c
    bool find_resource_tile(int resource_type, tile2i &out);

    template<typename T>
    figure_impl *acquire_impl() {
        new (&_ptr_buffer) T(this);
        _ptr = (figure_impl *)&_ptr_buffer;
        return _ptr;
    }
};

#define FIGURE_METAINFO(type, clsid) using self_type = clsid;   \
    using figure_model = figures::model_t<self_type>;           \
    static constexpr pcstr CLSID = #clsid;                      \
    static constexpr e_figure_type TYPE = type;                 


class figure_impl {
public:
    struct static_params {
        static static_params dummy;

        e_figure_type ftype;
        pcstr name;
        animations_t anim;
        figure_sounds_t sounds;
        int8_t terrain_usage;
        uint16_t max_roam_length;
        uint8_t speed_mult;
        metainfo meta;
        e_permission permission;

        virtual void load(archive arch);
    };

    figure_impl(figure *f) : base(*f), data(f->data) {}

    virtual void on_create();
    virtual void on_destroy() {}
    virtual void on_post_load();
    virtual void on_change_terrain(int old, int current);
    virtual void figure_action() {}
    virtual void figure_before_action() {}
    virtual void figure_roaming_action();
    virtual bool window_info_background(object_info &ctx) { return false; }
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out);
    virtual void before_poof() {}
    virtual void poof() { base.poof(); }
    virtual figure_phrase_t phrase() const { return {FIGURE_NONE, ""}; }
    virtual e_overlay get_overlay() const { return OVERLAY_NONE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const;
    virtual sound_key phrase_key() const { return "empty"; }
    virtual int provide_service() { return 0; }
    virtual bool play_die_sound() { return false; }
    virtual void update_animation();
    virtual void update_day() {}
    virtual bool can_move_by_water() const;
    virtual int y_correction(int y) const { return y; }
    virtual void cart_update_image() { base.cart_update_image(); }
    virtual void main_update_image();
    virtual e_minimap_figure_color minimap_color() const { return FIGURE_COLOR_NONE; }
    virtual const animations_t &anim() const { return params().anim; }
    virtual const static_params &params() const { return params(type()); }
    virtual void kill();
    virtual void on_action_changed(int saved_action) {}
    virtual void on_config_reload() {}
    virtual void on_update_home() {}
    virtual xstring action_tip() const { static xstring tip(""); return tip; }

    static void params(e_figure_type, const static_params &);
    static const static_params &params(e_figure_type);
    static void acquire(e_figure_type e, figure &b);

    virtual figure_immigrant *dcast_immigrant() { return nullptr; }
    virtual figure_cartpusher *dcast_cartpusher() { return nullptr; }
    virtual figure_storageyard_cart *dcast_storageyard_cart() { return nullptr; }
    virtual figure_trade_ship *dcast_trade_ship() { return nullptr; }
    virtual figure_sled *dcast_sled() { return nullptr; }
    virtual figure_musician *dcast_musician() { return nullptr; }
    virtual figure_dancer *dcast_dancer() { return nullptr; }
    virtual figure_labor_seeker *dcast_labor_seeker() { return nullptr; }
    virtual figure_worker *dcast_worker() { return nullptr; }
    virtual figure_soldier *dcast_soldier() { return nullptr; }
    virtual figure_fishing_boat *dcast_fishing_boat() { return nullptr; }
    virtual figure_fishing_point *dcast_fishing_point() { return nullptr; }
    virtual figure_caravan_donkey *dcast_caravan_donkey() { return nullptr; }
    virtual figure_warship *dcast_warship() { return nullptr; }
    virtual figure_transport_ship *dcast_transport_ship() { return nullptr; }

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
    inline const animation_t &anim(const xstring &anim_key) const { return anim()[anim_key]; }
    inline animation_context &animation() { return base.anim; }
    inline const animation_context &animation() const { return base.anim; }
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
    inline e_permission get_permission() const { return params().permission; }

    bvariant get_property(const xstring &domain, const xstring &name) const;

    metainfo get_info() const;

    figure &base;
    figure::data_t &data;
};

GENERATE_SMART_CAST(figure_impl)
#define GENERATE_SMART_CAST_FIGURE(type) GENERATE_SMART_CAST_CUSTOM(figure_##type, type)
GENERATE_SMART_CAST_FIGURE(fishing_point)
GENERATE_SMART_CAST_FIGURE(immigrant)
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
GENERATE_SMART_CAST_FIGURE(transport_ship)

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
struct model_t : public figure_impl::static_params {
    using figure_type = T;
    static constexpr e_figure_type TYPE = T::TYPE;
    static constexpr pcstr CLSID = T::CLSID;

    model_t() {
        name = CLSID;
        ftype = TYPE;

        static FigureCtorIterator config_handler(&create);
        static FigureStaticParamIterator static_params_handler(&static_params_load);
        
        figure_impl::params(TYPE, *this);
    }

    void archive_load() {
        bool loaded = false;
        g_config_arch.r_section(name, [&] (archive arch) {
            static_params::load(arch);
            loaded = true;
            this->archive_load(arch);
        });
        assert(loaded);
    }

    virtual void archive_load(archive) {
        /*overload options*/
    }

    static void static_params_load() {
        const model_t &item = static_cast<const model_t &>(figure_impl::params(TYPE));
        assert(item.TYPE == TYPE);
        const_cast<model_t &>(item).archive_load();
    }

    static figure_impl *create(e_figure_type e, figure &f) {
        if (e == TYPE) {
            return f.acquire_impl<figure_type>();
        }
        return nullptr;
    }
};

} // end namespace figures
    
