#include "figure/figure.h"

#include "building/building.h"
#include "city/city.h"
#include "city/warning.h"
#include "core/random.h"
#include "core/calc.h"
#include "core/svector.h"
#include "empire/empire.h"
#include "figure/figure_names.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "graphics/animkeys.h"
#include "sound/sound_walker.h"

#include <string.h>
#include <map>
#include "dev/debug.h"

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

struct figure_data_t {
    int created_sequence;
    bool initialized;
    std::array<figure*, MAX_FIGURES> figures;
};

figure_data_t g_figure_data = {0, false};

declare_console_command_p(killall, console_command_killall);
void console_command_killall(std::istream &, std::ostream &) {
    for (auto &f: map_figures()) {
        if (f->is_valid()) {
            f->poof();
        }
    }

    city_warning_show_console("Killed all walkers");
}

figure *figure_get(int id) {
    return g_figure_data.figures[id];
}

std::span<figure *> map_figures() {
    return make_span(g_figure_data.figures.data(), g_figure_data.figures.size());
}

figure *figure_take_from_pool () {
    auto it = std::find_if(g_figure_data.figures.begin() + 1, g_figure_data.figures.end(), [] (auto &f) { return f->available(); });
    return it != g_figure_data.figures.end() ? *it : nullptr;
}

figure* figure_create(e_figure_type type, tile2i tile, int dir) {
    figure *f = figure_take_from_pool();
    if (!f) {
        return figure_get(0);
    }

    f->state = FIGURE_STATE_ALIVE;
    f->faction_id = 1;
    f->type = type;
    f->use_cross_country = false;
    f->terrain_usage = -1;
    f->is_friendly = true;
    f->created_sequence = g_figure_data.created_sequence++;
    f->direction = dir;
    f->roam_length = 0;
    f->source_tile = tile;
    f->destination_tile = tile;
    f->previous_tile = tile;
    f->tile = tile;
    f->destination_tile.set(0, 0);
    f->cc_coords.x = 15 * tile.x();
    f->cc_coords.y = 15 * tile.y();
    f->progress_on_tile = 8;
    f->progress_inside = 0;
    f->progress_inside_speed = 0;
    f->phrase_sequence_city = f->phrase_sequence_exact = random_byte() & 3;
    f->name = figure_name_get(type, 0);
    f->map_figure_add();

    f->dcast()->on_create();

    return f;
}

void figure_clear_all() {
    if (!g_figure_data.initialized) {
        return;
    }

    for (auto *f : g_figure_data.figures) {
        int figure_id = f->id;
        f->clear_impl();
        memset(f, 0, sizeof(figure));
        f->state = FIGURE_STATE_NONE;
        f->id = figure_id;
    }
}

void figure::figure_delete_UNSAFE() {
    dcast()->on_destroy();

    if (has_home()) {
        building* b = home();
        b->remove_figure_by_id(id);
    }

    switch (type) {
    case FIGURE_BALLISTA:
        if (has_home())
            home()->remove_figure(3);
        break;

    case FIGURE_ENEMY_CAESAR_LEGIONARY:
        g_city.kingdome.mark_soldier_killed();
        break;
    }

    if (empire_city_id) {
        g_empire.city(empire_city_id)->remove_trader(id);
    }

    route_remove();
    map_figure_remove();

    int figure_id = id;
    state = FIGURE_STATE_NONE;
    memset(this, 0, sizeof(figure));
    id = figure_id;
}

figure_impl *figure::dcast() {
    if (_ptr) {
        return _ptr;
    }

    _ptr = figures::create(type, this);
    return _ptr;
}

figure_immigrant *figure::dcast_immigrant() { return dcast()->dcast_immigrant(); }
figure_cartpusher *figure::dcast_cartpusher() { return dcast()->dcast_cartpusher(); }
figure_storageyard_cart *figure::dcast_storageyard_cart() { return dcast()->dcast_storageyard_cart(); }
figure_trade_ship *figure::dcast_trade_ship() { return dcast()->dcast_trade_ship(); }
figure_sled *figure::dcast_sled() { return dcast()->dcast_sled(); }
figure_musician *figure::dcast_musician() { return dcast()->dcast_musician(); }
figure_dancer *figure::dcast_dancer() { return dcast()->dcast_dancer(); }
figure_labor_seeker *figure::dcast_labor_seeker() { return dcast()->dcast_labor_seeker(); }
figure_worker *figure::dcast_worker() { return dcast()->dcast_worker(); }
figure_soldier *figure::dcast_soldier() { return dcast()->dcast_soldier(); }
figure_fishing_boat *figure::dcast_fishing_boat() { return dcast()->dcast_fishing_boat(); }
figure_fishing_point *figure::dcast_fishing_point() { return dcast()->dcast_fishing_point(); }
figure_caravan_donkey *figure::dcast_caravan_donkey() { return dcast()->dcast_caravan_donkey(); }

bool figure::in_roam_history(int goffset) {
    return roam_history.exist(goffset);
}

void figure::add_roam_history(int goffset) {
#ifdef _MSC_VER
    if (IsDebuggerPresent() && !roam_history.empty()) {
        assert(roam_history.tail() != goffset);
    }
#endif // _MSC_VER
    roam_history.push_tail(goffset);
}

bool figure::is_dead() {
    return (state != FIGURE_STATE_ALIVE) 
                || (action_state == FIGURE_ACTION_149_CORPSE);
}

bool figure::is_boat() {
    return  (allow_move_type == EMOVE_WATER || allow_move_type == EMOVE_DEEPWATER);
}

bool figure::can_move_by_water() {
    return dcast()->can_move_by_water();
}

bool figure::can_move_by_terrain() {
    return (allow_move_type == EMOVE_TERRAIN || allow_move_type == EMOVE_AMPHIBIAN);
}

void figure::set_direction_to(building *b) {
    direction = calc_general_direction(tile, b->tile);
}

void figure::clear_impl() {
    delete _ptr;
    _ptr = nullptr;
}

void figure::poof() {
    dcast()->before_poof();
    set_state(FIGURE_STATE_DEAD);
}

bool figure::is_enemy() {
    return type >= FIGURE_ENEMY43_SPEAR && type <= FIGURE_ENEMY_CAESAR_LEGIONARY;
}

bool figure::is_herd() {
    return type >= FIGURE_BIRDS && type <= FIGURE_ANTELOPE;
}

building* figure::home() {
    return building_get(home_building_id);
};

building* figure::destination() {
    return building_get(destination_building_id);
};

void figure::set_home(int _id) {
    home_building_id = _id;
};

void figure::set_destination(int _id) {
    destination_building_id = _id;
};
void figure::set_home(building* b) {
    home_building_id = b->id;
};
void figure::set_destination(building* b) {
    destination_building_id = b->id;
};

bool figure::has_home(int _id) {
    if (_id == -1)
        return (home_building_id != 0);

    return (home_building_id == _id);
}

bool figure::is_citizen() {
    if (action_state != FIGURE_ACTION_149_CORPSE) {
        if ((type && type != FIGURE_EXPLOSION && type != FIGURE_STANDARD_BEARER && type != FIGURE_MAP_FLAG
            && type != FIGURE_FLOTSAM && type < FIGURE_INDIGENOUS_NATIVE)
            || type == FIGURE_TOWER_SENTRY) {
            return id;
        }
    }

    return 0;
}

bool figure::is_non_citizen() {
    if (action_state == FIGURE_ACTION_149_CORPSE)
        return 0;

    if (is_enemy()) {
        return id;
    }

    if (type == FIGURE_INDIGENOUS_NATIVE && action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
        return id;

    if (/*type == FIGURE_WOLF*/ type == FIGURE_OSTRICH || type == FIGURE_BIRDS || type == FIGURE_ANTELOPE)
        return id;

    return 0;
}

bool figure::has_home(building* b) {
    return (b == home());
}

bool figure::has_destination(int _id) {
    if (_id == -1) {
        return (destination_building_id != 0);
    }

    return (destination_building_id == _id);
}

bool figure::has_destination(building* b) {
    return (b == destination());
}

void figure::noble_action() {

}

e_minimap_figure_color figure::get_figure_color() {
    if (is_enemy()) {
        return FIGURE_COLOR_ENEMY;
    }

    if (type == FIGURE_INDIGENOUS_NATIVE && action_state == FIGURE_ACTION_159_NATIVE_ATTACKING) {
        return FIGURE_COLOR_ENEMY;
    }

    return dcast()->minimap_color();
}

void figure::kill() {
    if (state != FIGURE_STATE_ALIVE) {
        return;
    }

    advance_action(FIGURE_ACTION_149_CORPSE);
    set_state(FIGURE_STATE_DYING);
}

void figure_impl::on_create() {
    assert(base.tile.x() < GRID_LENGTH && base.tile.y() < GRID_LENGTH);
}

void figure_impl::on_post_load() {
    on_change_terrain(0, base.terrain_type);
}

void figure_impl::on_change_terrain(int old, int current) {
    const bool is_water = (!!(base.terrain_type & TERRAIN_WATER) || !!(base.terrain_type & TERRAIN_DEEPWATER));
    const bool is_swim_animaion = base.anim.id == animkeys().swim;
    const bool is_walk_animaion = base.anim.id == animkeys().walk;
    const bool is_moving_animation = is_swim_animaion || is_walk_animaion;

    if (!is_moving_animation) {
        return;
    }

    if (is_water && is_walk_animaion) {
        image_set_animation(animkeys().swim);
    } else if (!is_water && is_swim_animaion) {
        image_set_animation(animkeys().walk);
    }
}

void figure_impl::figure_roaming_action() {
    switch (action_state()) {
    case FIGURE_ACTION_150_ATTACK:
        base.figure_combat_handle_attack();
        break;

    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case FIGURE_ACTION_125_ROAMING:
    case ACTION_1_ROAMING:
        base.do_roam();
        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
    case ACTION_2_ROAMERS_RETURNING:
        base.do_returnhome();
        break;
    }
}

void figure_impl::figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) {
    base.draw_figure_main(ctx, base.cached_pos, highlight, coord_out);
}

figure_sound_t figure_impl::get_sound_reaction(xstring key) const {
    pcstr fname = snd::get_walker_reaction(key);
    return {key, fname, 0, 0};
}

bool figure_impl::can_move_by_water() const {
    return (base.allow_move_type == EMOVE_WATER || base.allow_move_type == EMOVE_DEEPWATER || base.allow_move_type == EMOVE_AMPHIBIAN);
}

void figure_impl::main_update_image() {
    if (base.state == FIGURE_STATE_DYING) {
        base.sprite_image_id = base.anim.start() + base.anim.current_frame();
    } else {
        base.sprite_image_id = base.anim.start() + base.figure_image_direction() + 8 * base.anim.current_frame();
    }
}

static std::map<e_figure_type, const figure_impl::static_params *> *figure_impl_params = nullptr;

void figure_impl::kill() {
    base.kill();
}

void figure_impl::params(e_figure_type e, const static_params &p) {
    if (!figure_impl_params) {
        figure_impl_params = new std::map<e_figure_type, const figure_impl::static_params *>();
    }
    figure_impl_params->insert(std::make_pair(e, &p));
}

const figure_impl::static_params &figure_impl::params(e_figure_type e) {
    auto it = figure_impl_params->find(e);
    return (it == figure_impl_params->end()) ? figure_impl::static_params::dummy : *it->second;
}

void figure_impl::advance_action(int action, tile2i t) {
    advance_action(action);
    base.destination_tile = t;
}

void figure_impl::set_destination(building *b, tile2i t) {
    base.set_destination(b);
    base.destination_tile = t;
}

figure_impl::static_params figure_impl::static_params::dummy;
void figure_impl::static_params::load(archive arch) {
    anim.load(arch);
    sounds.load(arch);
    terrain_usage = arch.r_int("terrain_usage");
    max_roam_length = arch.r_int("max_roam_length");
    speed_mult = arch.r_int("speed_mult", 1);
}

void figure_impl::update_animation() {
    xstring animkey;
    if (!base.anim.id) {
        animkey = animkeys().walk;
    }
 
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    }    

    if (!!animkey) {
        image_set_animation(animkey);
    }
}

figure_impl *figures::create(e_figure_type e, figure *data) {
    for (FigureCtorIterator *s = FigureCtorIterator::tail; s; s = s->next) {
        auto impl = s->func(e, data);
        if (impl) {
            return impl;
        }
    }

    assert(false);
    return new figure_impl(data);
}

void init_figures() {
    if (g_figure_data.initialized) {
        return;
    }

    for (int i = 0; i < MAX_FIGURES; i++) {
        g_figure_data.figures[i] = new figure(i);

    }

    g_figure_data.initialized = true;
}

void figure_init_scenario(void) {
    init_figures();
    g_figure_data.created_sequence = 0;
}

void figure::bind(io_buffer* iob) {
    figure* f = this;
    int tmpe;
    iob->bind(BIND_SIGNATURE_UINT8, &f->alternative_location_index);
    iob->bind(BIND_SIGNATURE_UINT8, &tmpe);
    iob->bind(BIND_SIGNATURE_UINT8, &f->is_enemy_image);
    iob->bind(BIND_SIGNATURE_UINT8, &f->flotsam_visible);

    //    f->sprite_image_id = buf->read_i16() + 18;
    f->sprite_image_id -= 18;
    iob->bind(BIND_SIGNATURE_UINT16, &f->sprite_image_id);
    f->sprite_image_id += 18;

    iob->bind(BIND_SIGNATURE_INT16, &f->anim.frame);
    iob->bind(BIND_SIGNATURE_UINT16, &f->next_figure);
    iob->bind(BIND_SIGNATURE_UINT8, &f->type);
    iob->bind(BIND_SIGNATURE_UINT8, &f->resource_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->use_cross_country);
    iob->bind(BIND_SIGNATURE_UINT8, &f->is_friendly);
    iob->bind(BIND_SIGNATURE_UINT8, &f->state);
    iob->bind(BIND_SIGNATURE_UINT8, &f->faction_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->action_state_before_attack);
    iob->bind(BIND_SIGNATURE_INT8, &f->direction);
    iob->bind(BIND_SIGNATURE_INT8, &f->previous_tile_direction);
    iob->bind(BIND_SIGNATURE_INT8, &f->attack_direction);
    iob->bind(BIND_SIGNATURE_UINT32, f->tile);
    iob->bind(BIND_SIGNATURE_UINT32, f->previous_tile);
    iob->bind(BIND_SIGNATURE_UINT16, &f->missile_damage);
    iob->bind(BIND_SIGNATURE_UINT16, &f->damage);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT32, f->destination_tile);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &f->progress_on_tile);              // 9
    iob->bind(BIND_SIGNATURE_UINT32, f->source_tile);
    iob->bind(BIND_SIGNATURE_UINT16, &f->formation_position_x.soldier);
    iob->bind(BIND_SIGNATURE_UINT16, &f->formation_position_y.soldier);
    iob->bind(BIND_SIGNATURE_INT8, &f->terrain_type);               // 0
    iob->bind(BIND_SIGNATURE_UINT8, &f->progress_inside_speed);
    iob->bind(BIND_SIGNATURE_INT16, &f->wait_ticks);                // 0
    iob->bind(BIND_SIGNATURE_INT16, &f->action_state);              // 9
    iob->bind(BIND_SIGNATURE_INT16, &f->routing_path_id);           // 12
    iob->bind(BIND_SIGNATURE_INT16, &f->routing_path_current_tile); // 4
    iob->bind(BIND_SIGNATURE_INT16, &f->routing_path_length);       // 28
    iob->bind(BIND_SIGNATURE_UINT8, &f->in_building_wait_ticks);    // 0
    iob->bind(BIND_SIGNATURE_UINT8, &f->outside_road_ticks);        // 1
    iob->bind(BIND_SIGNATURE_UINT16, &f->max_roam_length);
    iob->bind(BIND_SIGNATURE_UINT16, &f->roam_length);
    iob->bind(BIND_SIGNATURE_UINT8, &f->roam_wander_freely);
    iob->bind(BIND_SIGNATURE_UINT8, &f->roam_random_counter);
    iob->bind(BIND_SIGNATURE_INT8, &f->roam_turn_direction);
    iob->bind(BIND_SIGNATURE_INT8, &f->roam_ticks_until_next_turn); // 0 ^^^^
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_coords.x);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_coords.y);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_destination.x);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_destination.y);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_delta.x);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_delta.y);
    iob->bind(BIND_SIGNATURE_INT16, &f->cc_delta_xy);
    iob->bind(BIND_SIGNATURE_UINT8, &f->cc_direction);
    iob->bind(BIND_SIGNATURE_UINT8, &f->speed_multiplier);
    iob->bind(BIND_SIGNATURE_INT16, &f->home_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &f->immigrant_home_building_id);
    iob->bind(BIND_SIGNATURE_UINT16, &f->destination_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &f->formation_id);       // formation: 10
    iob->bind(BIND_SIGNATURE_UINT8, &f->index_in_formation); // 3
    iob->bind(BIND_SIGNATURE_UINT8, &f->formation_at_rest);
    iob->bind(BIND_SIGNATURE_UINT8, &f->migrant_num_people);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &f->min_max_seen);
    iob->bind(BIND_SIGNATURE_UINT8, &f->movement_ticks_watchdog);
    iob->bind(BIND_SIGNATURE_INT16, &f->leading_figure_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->attack_image_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &f->wait_ticks_missile);
    iob->bind(BIND_SIGNATURE_INT8, &f->cart_offset.x);
    iob->bind(BIND_SIGNATURE_INT8, &f->cart_offset.y);
    iob->bind(BIND_SIGNATURE_UINT8, &f->empire_city_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->trader_amount_bought);
    iob->bind(BIND_SIGNATURE_UINT16, &f->name); // 6
    iob->bind(BIND_SIGNATURE_UINT8, &f->terrain_usage);
    iob->bind(BIND_SIGNATURE_UINT8, &f->allow_move_type);
    iob->bind(BIND_SIGNATURE_UINT16, &f->resource_amount_full); // 4772 >>>> 112 (resource amount! 2-bytes)
    iob->bind(BIND_SIGNATURE_UINT8, &f->height_adjusted_ticks);
    iob->bind(BIND_SIGNATURE_UINT8, &f->current_height);
    iob->bind(BIND_SIGNATURE_UINT8, &f->target_height);
    iob->bind(BIND_SIGNATURE_UINT8, &f->collecting_item_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->trade_ship_failed_dock_attempts);
    iob->bind(BIND_SIGNATURE_UINT8, &f->phrase_sequence_exact);
    iob->bind(BIND_SIGNATURE_UINT8, &f->phrase.id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->phrase_sequence_city);
    iob->bind(BIND_SIGNATURE_INT8, &f->progress_inside);
    iob->bind(BIND_SIGNATURE_UINT8, &f->trader_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->wait_ticks_next_target);
    iob->bind(BIND_SIGNATURE_INT16, &f->target_figure_id);
    iob->bind(BIND_SIGNATURE_INT16, &f->targeted_by_figure_id);
    iob->bind(BIND_SIGNATURE_UINT16, &f->created_sequence);
    iob->bind(BIND_SIGNATURE_UINT16, &f->target_figure_created_sequence);
    //    iob->bind(BIND_SIGNATURE_UINT8, &f->figures_sametile_num);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &f->num_attackers);
    iob->bind(BIND_SIGNATURE_INT16, &f->attacker_id1);
    iob->bind(BIND_SIGNATURE_INT16, &f->attacker_id2);
    iob->bind(BIND_SIGNATURE_INT16, &f->opponent_id);
    //        iob->bind____skip(239);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT16, &f->collecting_item_max);       
    iob->bind(BIND_SIGNATURE_UINT8, &f->routing_try_reroute_counter);                       // 269
    iob->bind(BIND_SIGNATURE_UINT16, &f->phrase.group);                       // 269
    iob->bind(BIND_SIGNATURE_UINT16, &f->sender_building_id);                        // 0
    iob->bind(BIND_SIGNATURE_INT32, &f->market_lady_resource_image_offset); // 03 00 00 00
    iob->bind____skip(12);                                                  // FF FF FF FF FF ...
    iob->bind(BIND_SIGNATURE_INT16, &f->market_lady_returning_home_id);     // 26
    iob->bind____skip(14);                                                  // 00 00 00 00 00 00 00 ...
    iob->bind(BIND_SIGNATURE_INT16, &f->market_lady_bought_amount);         // 200
    iob->bind____skip(115);
    iob->bind(BIND_SIGNATURE_UINT8, &f->draw_debug_mode);     // 6
    iob->bind(BIND_SIGNATURE_INT16, &f->local_data.value[0]); // -1
    iob->bind(BIND_SIGNATURE_INT16, &f->local_data.value[1]); // -1
    iob->bind(BIND_SIGNATURE_INT16, &f->local_data.value[2]); // -1
    iob->bind____skip(44);
    iob->bind(BIND_SIGNATURE_INT8, &f->festival_remaining_dances);
    iob->bind____skip(27);

    f->cart_image_id -= 18;
    iob->bind(BIND_SIGNATURE_UINT16, &f->cart_image_id);
    f->cart_image_id += 18;

    iob->bind____skip(2);

    draw_debug_mode = 0;
}

io_buffer* iob_figures = new io_buffer([](io_buffer* iob, size_t version) {
    init_figures();
    for (int i = 0; i < MAX_FIGURES; i++) {
        figure_get(i)->bind(iob); // doing this because some members are PRIVATE.
        figure_get(i)->id = i;
    }
});

io_buffer* iob_figure_sequence = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_figure_data.created_sequence);
});