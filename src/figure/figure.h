#pragma once

#include "core/core.h"
#include "core/interlocked.h"
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
#include "figure/figure_static_params.h"
#include "figure/figure_impl.h"
#include "figure/figure_classes.h"

#include <algorithm>
#include <memory.h>
#include <vector>

struct tooltip_context;
class building;

struct animation_t;

constexpr int MAX_FIGURES = 2000;
constexpr int MAX_CLOUD_IMAGE_OFFSETS = 19;

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
    e_figure_flag_inattack = 1 << 4,
    e_figure_flag_invisible = 1 << 5,
    e_figure_flag_use_cart = 1 << 6,
};

class figure {
public:
    using ptr_buffer_t = char[16];
    using debug_lines_t = hvector<bstring32, 8>;

private:
    ptr_buffer_t _ptr_buffer = { 0 };
    figure_impl *_ptr = nullptr;
    debug_lines_t *_debug_lines;

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
    volatile bool mt_render_worker;
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
    uint8_t num_attackers;
    short attacker_id1;
    short attacker_id2;
    short opponent_id;
    vec2i main_cached_pos;
    vec2i main_sort_pixel;
    vec2i cart_cached_pos;

    uint8_t routing_try_reroute_counter;
    uint16_t collecting_item_max;
    building_id sender_building_id;

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
    ALLOW_SMART_CAST_FIGURE(hyena)
    ALLOW_SMART_CAST_FIGURE(antelope)
    ALLOW_SMART_CAST_FIGURE(animal)
    ALLOW_SMART_CAST_FIGURE(ballista)
    ALLOW_SMART_CAST_FIGURE(market_buyer)
    ALLOW_SMART_CAST_FIGURE(bricklayer)
    ALLOW_SMART_CAST_FIGURE(ferry_boat)
    ALLOW_SMART_CAST_FIGURE(soldier)
    ALLOW_SMART_CAST_FIGURE(enemy)
    ALLOW_SMART_CAST_FIGURE(worker)

    figure(int _id) {
        // ...can't be bothered to add default values to ALL
        // the above members of "figure" ....for now...
        memset((void*)this, 0, sizeof(figure));
        id = _id;
    };

    // map search tests
    bool in_roam_history(int goffset);
    void add_roam_history(int goffset);

    void apply_damage(int hit_dmg, figure_id attaker_id);

    debug_lines_t &debug_lines();
    void debug_lines_clear();

    bool is_dead();
    inline bool is_enemy() const { return !!(flags & e_figure_flag_enemy); }
    inline bool is_criminal() const { return !!(flags & e_figure_flag_criminal); }
    inline bool is_friendly() const { return !!(flags & e_figure_flag_friendly); }
    inline bool is_soldier() const { return !!(flags & e_figure_flag_soldier); }
    inline bool in_attack() const { return !!(flags & e_figure_flag_inattack); }
    inline bool is_visible() const { return !(flags & e_figure_flag_invisible); }

    inline void set_flag(e_figure_flag fl, bool v = true) {
        if (v) { flags |= fl; }
        else { flags &= ~fl; }
    }

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
    void set_direction(int dir);
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
    void acquire_attack();

    // image.c
    void image_set_animation(const animation_t &anim);
    void image_set_animation(const xstring &anim);
    void image_set_animation(int collection, int group, int offset = 0, int max_frames = 12, int duration = 1, bool loop = true);
    void figure_image_update(bool refresh_only);
    int figure_image_corpse_offset();
    int figure_image_missile_launcher_offset();
    int figure_image_direction();
    vec2i tile_pixel_coords();


    vec2i adjust_pixel_offset(const vec2i pixel);
    vec2i crowd_pixel_offset() const;
    vec2i main_sprite_pixel() const;
    vec2i cart_sprite_pixel() const;

    void draw_debug(painter &ctx);
    void draw_tooltip(tooltip_context *c) const;
    void draw_main_sprite(painter &ctx, vec2i pixel, int highlight);
    void draw_cart_sprite(painter &ctx, vec2i pixel, int highlight);
    void draw(painter &ctx, int highlight);
    void draw_map_flag(vec2i pixel, int highlight, vec2i* coord_out = nullptr);

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
    void figure_synthesize_phrase_file(const xstring& path);

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

figure *figure_create(e_figure_type type, tile2i tile, int dir);
int figure_movement_can_launch_cross_country_missile(tile2i src, tile2i dst);
void figure_create_explosion_cloud(tile2i tile, int size);

template <typename dest_type>
inline dest_type *smart_cast(figure *f) {
    return ::smart_cast<dest_type*>(f->dcast());
}