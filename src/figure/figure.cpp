#include "figure/figure.h"

#include "building/building.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "core/random.h"
#include "core/calc.h"
#include "core/svector.h"
#include "empire/empire.h"
#include "figure/figure_names.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "graphics/animkeys.h"
#include "sound/sound_walker.h"
#include "graphics/view/lookup.h"
#include "core/object_property.h"
#include "core/profiler.h"
#include "widget/widget_city.h"
#include "figuretype/editor.h"
#include "figure/image.h"
#include "game/game.h"
#include "game/game_config.h"
#include "grid/routing/routing.h"
#include "js/js_game.h"

#include <string.h>
#include <map>
#include "dev/debug.h"

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

static const vec2i crowd_offsets[] = {
    {0, 0}, {3, 0}, {3, 3}, {-3, 6}, {-3, -3},
    {0, -6}, {6, 0}, {0, 6}, {-6, 0}, {3, -6},
    {-3, 6}, {6, 3}, {-6, -3}, {6, -3}, {-6, 3},
    {3, 6}, {-3, -6}, {0,-10}, {10,0}, {0, 10}, {-10, 0}
};
constexpr int crowd_offsets_size = (int)std::size(crowd_offsets);

static std::array<const figure_static_params *, FIGURE_MAX> figure_impl_params;

using e_permission_tokens_t = token_holder<e_permission, epermission_none, epermission_count>;
const e_permission_tokens_t ANK_CONFIG_ENUM(e_permission_tokens);

const vec2i default_cart_offset{ 0, -7 };

declare_console_command_p(kill_all_figures) {
    for (auto &f: map_figures()) {
        if (f->is_valid()) {
            f->poof();
        }
    }

    events::emit(event_city_warning{ "Killed all walkers" });
}

declare_console_command_p(create_figure) {
    std::string args; is >> args;
    int f_type = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    if (!f_type) {
        return;
    }

    const mouse& m = mouse::get();
    tile2i current_tile = g_screen_city.update_city_view_coords(m);;
    figure_create((e_figure_type)f_type, current_tile, 1);
}

bool figure::do_exitbuilding(bool invisible, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    // "go to" home, but stop at road = go to entrance
    return do_gotobuilding(home(), true, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

bool figure::do_enterbuilding(bool invisible, building *b, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    return do_gotobuilding(b, false, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

bool figure::do_roam(int terrainchoice, short NEXT_ACTION) {
    terrain_usage = terrainchoice;
    roam_length++;
    if (roam_length >= max_roam_length) { // roam over, return home
        destination_tile.set(0);
        roam_length = 0;
        set_destination(nullptr);
        route_remove();
        advance_action(NEXT_ACTION);
        return true;
    } else {
        roam_ticks(speed_multiplier);
    }
    return false;
}

int figure::target_is_alive() {
    if (target_figure_id <= 0)
        return 0;

    figure *target = figure_get(target_figure_id);
    if (!target->is_dead() /* && target->created_sequence == target_figure_created_sequence */)
        return 1;

    return 0;
}

void figure::reset_flags() {
    flags = 0;
    flags |= (params().is_enemy ? e_figure_flag_enemy : e_figure_flag_friendly);
    flags |= (params().is_soldier ? e_figure_flag_soldier : e_figure_flag_none);
}

resource_tile figure::find_resource_tile(e_resource resource) {
    switch (resource) {
    case RESOURCE_REEDS:
        return map_routing_citizen_found_reeds(tile);

    case RESOURCE_TIMBER:
        return map_routing_citizen_found_timber(tile);
    }

    return { RESOURCE_NONE, tile2i::invalid };
}

static int get_nearest_enemy(int x, int y, int *distance) {
    int min_enemy_id = 0;
    int min_dist = 10000;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE || f->targeted_by_figure_id)
            continue;

        int dist;
        if (f->type == FIGURE_PROTESTER || f->type == FIGURE_RIOTER)
            dist = calc_maximum_distance(tile2i(x, y), f->tile);
        else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->is_enemy())
            dist = calc_maximum_distance(tile2i(x, y), f->tile);
        else if (f->is_enemy())
            dist = 3 * calc_maximum_distance(tile2i(x, y), f->tile);
        else if (f->type == FIGURE_HYENA)
            dist = 4 * calc_maximum_distance(tile2i(x, y), f->tile);
        else
            continue;
        if (dist < min_dist) {
            min_dist = dist;
            min_enemy_id = i;
        }
    }
    *distance = min_dist;
    return min_enemy_id;
}

nearby_result figure::is_nearby(int rule, int max_distance, bool gang_on, std::function<bool(figure *)> avoid) {
    figure_id fid = 0;
    int lowest_distance = max_distance;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f->is_dead()) {
            continue;
        }

        if (!gang_on && f->targeted_by_figure_id) {
            continue;
        }

        const bool should_avoid = avoid(f);
        if (should_avoid) {
            continue;
        }

        bool category_check = false;
        switch (rule) {
        case NEARBY_ANY: // any dude
            if (f->category() != 0)
                category_check = true;
            break;

        case NEARBY_ANIMAL: // animal
            if (f->category() == figure_category_animal || f->is_herd())
                category_check = true;
            break;

        case NEARBY_HOSTILE: // hostile
            if (f->is_enemy() || f->is_criminal())
                category_check = true;
            break;
        }

        // pass on to inner distance check
        if (category_check) {
            int dist = calc_maximum_distance(tile, f->tile);
            if (dist <= max_distance) {
                if (f->targeted_by_figure_id)
                    dist *= 2; // penalty
                if (rule == NEARBY_HOSTILE) {
                    if (f->type == FIGURE_TOMB_ROBER || f->type == FIGURE_RIOTER)
                        dist = calc_maximum_distance(tile, f->tile);
                    else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->is_enemy())
                        dist = calc_maximum_distance(tile, f->tile);
                    else if (f->is_enemy())
                        dist = 3 * calc_maximum_distance(tile, f->tile);
                    // else if (f->type == FIGURE_WOLF)
                    //     dist = 4 * calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
                    //                    else
                    //                        continue;
                }
                if (dist < lowest_distance) {
                    lowest_distance = dist;
                    fid = i;
                    //                    if (!gang_on)
                    //                        return figure_id;
                }
            }
        }
    }

    return { fid, lowest_distance };
}

bool figure::do_goto(tile2i dest, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    OZZY_PROFILER_SECTION("Figure/Goto");
    terrain_usage = terrainchoice;
    if (use_cross_country) {
        terrain_usage = TERRAIN_USAGE_ANY;
    }

    // refresh routing if destination is different
    if (destination_tile != dest) {
        OZZY_PROFILER_SECTION("Figure/Goto/Route remove (no dest)");
        route_remove();
    }

    // set up destination and move!!!
    if (use_cross_country) {
        OZZY_PROFILER_SECTION("Figure/Goto/CrossCountry");
        set_cross_country_destination(dest);
        if (move_ticks_cross_country(1) == 1) {
            advance_action(NEXT_ACTION);
            return true;
        }
    } else {
        OZZY_PROFILER_SECTION("Figure/Goto/MoveTicks");
        destination_tile = dest;
        move_ticks(speed_multiplier);
    }

    // check if destination is reached/figure is lost/etc.
    if (direction == DIR_FIGURE_NONE) {
        advance_action(NEXT_ACTION);
        direction = previous_tile_direction;
        return true;
    }

    if (direction == DIR_FIGURE_REROUTE) {
        OZZY_PROFILER_SECTION("Figure/Goto/Route Remove (reroute)");
        route_remove();
    }

    if (direction == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(FAIL_ACTION);
    }

    return false;
}

void figure::advance_action(short next_action) {
    if (state == FIGURE_STATE_DYING && next_action != FIGURE_ACTION_149_CORPSE) {
        return;
    }
    action_state = next_action;
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

    case FIGURE_ENEMY_KINGDOME_INFANTRY:
        g_city.kingdome.mark_soldier_killed();
        break;

    default:
        ; // nothing
    }

    route_remove();
    map_figure_remove();

    int figure_id = id;
    state = FIGURE_STATE_NONE;
    memset(this, 0, sizeof(figure));
    id = figure_id;
}

figure_impl *figure::dcast() {
    if (!id) {
        return nullptr;
    }

    if (!_ptr) {
        figure_impl::acquire(type, *this);
    }

    assert(!!_ptr);
    return _ptr;
}

const figure_impl *figure::dcast() const {
    if (!id) {
        return nullptr;
    }

    if (!_ptr) {
        figure_impl::acquire(type, *(figure*)this);
    }

    assert(!!_ptr);
    return _ptr;
}

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

void figure::apply_damage(int hit_dmg, figure_id attaker_id) {
    dcast()->apply_damage(hit_dmg, attaker_id);
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
    memset(&_ptr_buffer, 0, sizeof(ptr_buffer_t));
    _ptr = nullptr;
}

e_figure_category figure::category() const {
    return figure_static_params::get(type).category;
}

uint16_t figure::max_damage() const {
    return figure_static_params::get(type).max_damage;
}

int8_t figure::attack_value() const {
    return figure_static_params::get(type).attack_value;
}

int8_t figure::missile_defense_value() const {
    return figure_static_params::get(type).missile_defense_value;
}

int8_t figure::defense_value() const {
    return figure_static_params::get(type).defense_value;
}

void figure::poof() {
    dcast()->before_poof();
    set_state(FIGURE_STATE_DEAD);
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
    dcast()->on_update_home();
};

void figure::set_destination(building_id _id) {
    destination_building_id = _id;
};

void figure::set_home(building* b) {
    home_building_id = b->id;
};

void figure::set_destination(building* b) {
    destination_building_id = b ? b->id : 0;
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

void figure_impl::acquire(e_figure_type e, figure &f) {
    static_assert(sizeof(figure_impl) <= sizeof(figure::ptr_buffer_t));

    using namespace figures;
    for (auto static_ctor = FigureCtorIterator::tail; static_ctor; static_ctor = static_ctor->next) {
        auto impl = static_ctor->func(e, f);
        if (impl) {
            return;
        }
    }

    assert(false && "Cant find building type in config");
    f.acquire_impl<figure_impl>();
}

bool figure::is_non_citizen() {
    if (action_state == FIGURE_ACTION_149_CORPSE)
        return 0;

    if (is_enemy()) {
        return id;
    }

    if (type == FIGURE_INDIGENOUS_NATIVE && is_enemy())
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

xstring figure::action_tip() {
    return dcast()->action_tip();
}

int figure::get_direction() {
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK)
        dir = attack_direction;
    else if (direction < 8)
        dir = direction;
    else {
        dir = previous_tile_direction;
    }
    return figure_image_normalize_direction(dir);
}

int figure::get_missile_direction(const formation *m) {
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK)
        dir = attack_direction;
    else if (m->missile_fired || direction < 8)
        dir = direction;
    else {
        dir = previous_tile_direction;
    }
    return figure_image_normalize_direction(dir);
}


e_minimap_figure_color figure::get_figure_color() {
    if (is_enemy()) {
        return FIGURE_COLOR_ENEMY;
    }

    return dcast()->minimap_color();
}

const figure_static_params& figure::params() const {
    return figure_static_params::get(type);
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

    if (base.name.len() < 4) {
        base.name = figure_name_get(base.type);
    }
}

void figure_impl::on_attacked(figure *attacker) {
    if (base.state != FIGURE_STATE_ALIVE) {
        return;
    }

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        return;
    }

    kill();
}

void figure_impl::on_change_terrain(int old, int current) {
    const bool is_water = (!!(current & TERRAIN_WATER) || !!(current & TERRAIN_DEEPWATER)
                            && !(current & TERRAIN_SHORE))
                            && !(current & TERRAIN_BUILDING);

    const bool is_swim_animaion = base.animctx.key == animkeys().swim;
    const bool is_walk_animaion = base.animctx.key == animkeys().walk;
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

    case ACTION_125_ROAMER_ROAMING:
        base.do_roam();
        break;

    case ACTION_126_ROAMER_RETURNING:
        base.do_returnhome();
        break;
    }
}

vec2i figure::main_sprite_pixel() const {
    return lookup_tile_to_pixel(tile);
}

vec2i figure::cart_sprite_pixel() const {
    vec2i r = main_cached_pos + cart_offset + default_cart_offset;
    return r;
}

void figure::draw_figure_cart(painter &ctx, vec2i pixel, int highlight) {
    const image_t *img = image_get(cart_image_id);
    auto& command = ImageDraw::create_subcommand(render_command_t::ert_sprite);
    command.image_id = cart_image_id;
    command.pixel = pixel;
    command.mask = COLOR_MASK_NONE;

    is_cart_drawn = true;
}

void figure_impl::figure_draw(painter &ctx, vec2i pixel, int highlight) {
    base.draw_figure_main(ctx, base.main_cached_pos, highlight);
}

figure_sound_t figure_impl::get_sound_reaction(xstring key) const {
    return params().sounds[key];
}

sound_key figure_impl::default_phrase_key() const {
    e_god_mood god_mood = g_city.religion.least_mood();

    if (city_resource_food_supply_months() <= 0) {
        return "def_no_food_in_city";
    }

    const int unemployment_pct = g_city.labor.unemployment_percentage;
    if (unemployment_pct >= 17) {
        return "def_too_much_unemployments";
    }

    if (g_city.labor.workers_needed >= 10) {
        return "def_need_more_workers";
    }

    if (g_city.avg_coverage.average_entertainment == 0) {
        return "def_low_entertainment";
    }

    if (god_mood == GOD_MOOD_VERY_ANGRY) {
        return "def_gods_very_angry";
    }

    if (g_city.avg_coverage.average_entertainment <= 10) {
        return "def_little_entertainment";
    }
    
    if (god_mood == GOD_MOOD_ANGRY) {
        return "def_gods_angry";
    }
    
    if (g_city.avg_coverage.average_entertainment <= 20) {
        return "def_need_entertainment";
    }
    
    if (city_resource_food_supply_months() >= 4 && unemployment_pct <= 5 &&
        g_city.avg_coverage.average_health > 0 && g_city.avg_coverage.average_education > 0) {
        if (g_city.population.current < 500) {
            return "def_city_not_bad";
        }
        
        return "def_city_may_be_better";
    } 
    
    if (unemployment_pct >= 10) {
        return "def_city_need_some_workers";
    }

    return "def_city_is_good";
}

bool figure_impl::can_move_by_water() const {
    return (base.allow_move_type == EMOVE_WATER || base.allow_move_type == EMOVE_DEEPWATER || base.allow_move_type == EMOVE_AMPHIBIAN);
}

void figure_impl::main_image_update() {
    if (base.state == FIGURE_STATE_DYING) {
        base.main_image_id = base.animctx.start_frame() + base.animctx.current_frame();
    } else {
        base.main_image_id = base.animctx.start_frame() + base.figure_image_direction() + 8 * base.animctx.current_frame();
    }
}

bool figure::do_returnhome(e_terrain_usage terrainchoice, short NEXT_ACTION) {
    return do_gotobuilding(home(), true, terrainchoice, NEXT_ACTION);
}

void figure_impl::kill() {
    base.kill();
}

void figure_static_params::set(e_figure_type e, const figure_static_params &p) {
    //if (!figure_impl_params) {
    //    figure_impl_params = new std::map<e_figure_type, const figure_impl::static_params *>();
    //}
    figure_impl_params[e] = &p;
}

const figure_static_params &figure_static_params::get(e_figure_type e) {
    const auto* cfg = figure_impl_params[e];
    return (!cfg ? figure_static_params::dummy : *cfg);
}

figure_static_params &figure_static_params::ref(e_figure_type e) {
    auto *cfg = figure_impl_params[e];
    assert(cfg);
    return *const_cast<figure_static_params*>(cfg);
}

void figure_impl::advance_action(int action, tile2i t) {
    advance_action(action);
    base.destination_tile = t;
}

void figure_impl::set_destination(building *b, tile2i t) {
    base.set_destination(b);
    base.destination_tile = t;
}

metainfo figure_impl::get_info() const {
    return params().meta;
}

figure_static_params figure_static_params::dummy;
void figure_static_params::initialize() {
    assert(animations.data.size() > 0);

    if (speed_mult == 0) speed_mult = 1;
    if (max_damage == 0) max_damage = 100;
    if (corpse_time_delay == 0) corpse_time_delay = 128;
}

void figure_impl::update_animation() {
    xstring animkey;
    if (!base.animctx.key) {
        animkey = animkeys().walk;
    }
 
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    }    

    if (!!animkey) {
        image_set_animation(animkey);
    }
}

const fproperty fproperties[] = {
    //{ tags().stored, xstring("*"),
    //    [] (figure &b, const xstring &name) {
    //        e_resource res = resource_type(name);
    //        return bvariant(b.stored_amount(res));
    //    }
    //},

    { tags().text, xstring("*"),
        [] (figure &b, const xstring &name) {
             int id = atoi(name.c_str());
             const auto &m = figure_static_params::get(b.type).meta;
             return bvariant(ui::str(m.text_id, id));
        }
    },

    { tags().figure, tags().name, [] (figure &f, const xstring &) { return bvariant(f.name.c_str()); }},
    { tags().figure, tags().class_name, [] (figure &f, const xstring &) { bstring64 clname("#", f.params().name); return bvariant(lang_text_from_key(clname)); }},
    { tags().figure, tags().city_name, [] (figure &f, const xstring &) { return bvariant(f.dcast()->empire_city().name()); }},
    { tags().figure, tags().action_tip, [] (figure &f, const xstring &) { return bvariant(f.action_tip()); }},
    { tags().figure, tags().home, [] (figure &f, const xstring &) { return bvariant(ui::str(41, f.home()->type)); }},
};

bvariant figure_impl::get_property(const xstring &domain, const xstring &name) const {
    static const xstring wildname("*");
    for (const auto &prop : fproperties) {
        if (prop.domain != domain) {
            continue;
        }

        if (prop.name == name || prop.name == wildname) {
            return prop.handler(base, name);
        }
    }

    return bvariant();
}

figure_impl *figures::create(e_figure_type e, figure &f) {
    for (FigureCtorIterator *s = FigureCtorIterator::tail; s; s = s->next) {
        auto impl = s->func(e, f);
        if (impl) {
            return impl;
        }
    }

    assert(false);
    return f.acquire_impl<figure_impl>();
}

void figure::draw_map_flag(vec2i pixel, int highlight, vec2i *coord_out) {
    painter ctx = game.painter();
    // base
    ctx.img_generic(main_image_id, pixel);
    // flag
    ctx.img_generic(cart_image_id, pixel + vec2i{ 0, -image_get(cart_image_id)->height });
    // flag number
    int number = 0;
    int id = resource_id;
    if (id >= MAP_FLAG_INVASION_MIN && id < MAP_FLAG_INVASION_MAX) {
        number = id - MAP_FLAG_INVASION_MIN + 1;
    } else if (id >= MAP_FLAG_FISHING_MIN && id < MAP_FLAG_FISHING_MAX) {
        number = id - MAP_FLAG_FISHING_MIN + 1;
    } else if (id >= MAP_FLAG_HERD_MIN && id < MAP_FLAG_HERD_MAX) {
        number = id - MAP_FLAG_HERD_MIN + 1;
    }

    if (number > 0) {
        text_draw_number_colored(number, '@', " ", pixel.x + 6, pixel.y + 7, FONT_SMALL_PLAIN, COLOR_WHITE);
    }
}


bool figure::has_cart() const {
    return (use_cart && cart_image_id != 0);
}

const animation_t &figure::anim(const xstring &key) {
    return params().animations[key];
}

vec2i figure::adjust_pixel_offset(const vec2i pixel) {
    // determining x/y offset on tile
    vec2i offset(0, 0);
    if (use_cross_country) {
        auto cc_offets = tile_pixel_coords();
        offset = cc_offets;
        offset.y -= missile_damage;
    } else {
        int dir = figure_image_normalize_direction(direction);
        int adjusted_progress = progress_on_tile;
        if (progress_on_tile >= 8) {
            adjusted_progress -= 15;
        }

        switch (dir) {
        case DIR_0_TOP_RIGHT:
            offset.x += 2 * adjusted_progress;
            offset.y -= adjusted_progress;
            break;
        case DIR_1_RIGHT:
            offset.x += 4 * adjusted_progress;
            offset.y = 0;
            break;
        case DIR_2_BOTTOM_RIGHT:
            offset.x += 2 * adjusted_progress;
            offset.y += adjusted_progress;
            break;
        case DIR_3_BOTTOM:
            offset.x = 0;
            offset.y += 2 * adjusted_progress;
            break;
        case DIR_4_BOTTOM_LEFT:
            offset.x -= 2 * adjusted_progress;
            offset.y += adjusted_progress;
            break;
        case DIR_5_LEFT:
            offset.x -= 4 * adjusted_progress;
            offset.y = 0;
            break;
        case DIR_6_TOP_LEFT:
            offset.x -= 2 * adjusted_progress;
            offset.y -= adjusted_progress;
            break;
        case DIR_7_TOP:
            offset.x = 0;
            offset.y -= 2 * adjusted_progress;
            break;
        }
        offset.y -= current_height;
    }

    if (!!game_features::gameplay_change_citizen_road_offset && id && type != FIGURE_BALLISTA) {
        // an attempt to not let people walk through each other
        offset += crowd_offsets[id % crowd_offsets_size];
    }

    return { pixel.x + offset.x + 29, pixel.y + offset.y + 15 + 8 };
}

void figure::draw_figure_main(painter &ctx, vec2i pixel, int highlight) {
    int x_correction = 0;
    int y_correction = 3;

    y_correction = dcast()->y_correction(y_correction);

    const image_t *img = image_get(main_image_id);
    auto& command = ImageDraw::create_subcommand(render_command_t::ert_sprite);
    command.image_id = main_image_id;
    command.pixel = pixel + vec2i{ x_correction, y_correction };
    command.mask = COLOR_MASK_NONE;
}

void figure::city_draw_figure(painter &ctx, int highlight) {
    // This is to update the sprite's direction when rotating the city view.
    // Unfortunately, because the only thing we have at the time of file loading is
    // the raw sprite image id, it doesn't work if we haven't performed at least a
    // single frame of figure action after loading a file (i.e. if paused instantly)
    figure_image_update(true);

    // if (coord_out != nullptr) {
    //     highlight = 0;
    //     *coord_out = cached_pos;
    // }

    if (cart_image_id) {
        switch (type) {
        case FIGURE_MAP_FLAG:
            draw_map_flag(main_cached_pos, highlight);
            break;

        default:
            dcast()->figure_draw(ctx, main_cached_pos, highlight);
            break;
        }
    } else {
        draw_figure_main(ctx, main_cached_pos, highlight);
        //if (!is_enemy_image && highlight) {
        //    ImageDraw::img_sprite(ctx, main_image_id, main_cached_pos, COLOR_MASK_LEGION_HIGHLIGHT);
        //}
    }

    is_main_drawn = true;
}

void figure::bind(io_buffer* iob) {
    figure* f = this;
    int tmpe;
    iob->bind(BIND_SIGNATURE_UINT8, &f->alternative_location_index);
    iob->bind(BIND_SIGNATURE_UINT8, &tmpe);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->is_enemy_image);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->flotsam_visible);

    //    f->sprite_image_id = buf->read_i16() + 18;
    f->main_image_id -= 18;
    iob->bind(BIND_SIGNATURE_UINT16, &f->main_image_id);
    f->main_image_id += 18;

    iob->bind(BIND_SIGNATURE_INT16, &f->animctx.frame);
    iob->bind(BIND_SIGNATURE_UINT16, &f->next_figure);
    
    if (f->next_figure >= MAX_FIGURES)
        f->next_figure = 0;

    iob->bind(BIND_SIGNATURE_UINT8, &f->type);
    iob->bind(BIND_SIGNATURE_UINT8, &f->resource_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->use_cross_country);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &f->state);
    iob->bind(BIND_SIGNATURE_UINT8, &f->faction_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->action_state_before_attack);
    iob->bind(BIND_SIGNATURE_INT8, &f->direction);
    iob->bind(BIND_SIGNATURE_INT8, &f->previous_tile_direction);
    iob->bind(BIND_SIGNATURE_INT8, &f->attack_direction);
    iob->bind(BIND_SIGNATURE_TILE2I, f->tile);
    iob->bind(BIND_SIGNATURE_UINT32, f->previous_tile);
    iob->bind(BIND_SIGNATURE_UINT16, &f->missile_damage);
    iob->bind(BIND_SIGNATURE_UINT16, &f->damage);
    iob->bind_u32(f->flags);
    iob->bind(BIND_SIGNATURE_UINT32, f->destination_tile);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &f->progress_on_tile);              // 9
    iob->bind(BIND_SIGNATURE_UINT32, f->source_tile);
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->formation_position_x.soldier);
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->formation_position_y.soldier);
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
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &f->destination_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &f->formation_id);       // formation: 10
    iob->bind(BIND_SIGNATURE_UINT8, &f->index_in_formation); // 3
    iob->bind(BIND_SIGNATURE_UINT8, &f->formation_at_rest);
    iob->bind____skip(1);  // iob->bind(BIND_SIGNATURE_UINT8, &f->migrant_num_people);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &f->min_max_seen);
    iob->bind(BIND_SIGNATURE_UINT8, &f->movement_ticks_watchdog);
    iob->bind(BIND_SIGNATURE_INT16, &f->leading_figure_id);
    iob->bind(BIND_SIGNATURE_UINT8, &f->attack_image_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &f->wait_ticks_missile);
    iob->bind(BIND_SIGNATURE_INT8, &f->cart_offset.x);
    iob->bind(BIND_SIGNATURE_INT8, &f->cart_offset.y);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->empire_city_id);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->trader_amount_bought);
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->name); // 6
    iob->bind(BIND_SIGNATURE_UINT8, &f->terrain_usage);
    iob->bind(BIND_SIGNATURE_UINT8, &f->allow_move_type);
    iob->bind(BIND_SIGNATURE_UINT16, &f->resource_amount_full); // 4772 >>>> 112 (resource amount! 2-bytes)
    iob->bind(BIND_SIGNATURE_UINT8, &f->height_adjusted_ticks);
    iob->bind(BIND_SIGNATURE_UINT8, &f->current_height);
    iob->bind(BIND_SIGNATURE_UINT8, &f->target_height);
    iob->bind(BIND_SIGNATURE_UINT8, &f->collecting_item_id);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->trade_ship_failed_dock_attempts);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->phrase_sequence_exact);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->phrase.id);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &f->phrase_sequence_city);
    iob->bind(BIND_SIGNATURE_INT8, &f->progress_inside);
    iob->bind____skip(1);  // iob->bind(BIND_SIGNATURE_UINT8, &f->trader_id);
    iob->bind____skip(1);  // iob->bind(BIND_SIGNATURE_UINT8, &f->wait_ticks_next_target);
    iob->bind(BIND_SIGNATURE_INT16, &f->target_figure_id);
    iob->bind(BIND_SIGNATURE_INT16, &f->targeted_by_figure_id);
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->created_sequence);
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->target_figure_created_sequence);
    iob->bind____skip(1); //    iob->bind(BIND_SIGNATURE_UINT8, &f->figures_sametile_num);
    iob->bind(BIND_SIGNATURE_UINT8, &f->num_attackers);
    iob->bind(BIND_SIGNATURE_INT16, &f->attacker_id1);
    iob->bind(BIND_SIGNATURE_INT16, &f->attacker_id2);
    iob->bind(BIND_SIGNATURE_INT16, &f->opponent_id);
    //        iob->bind____skip(239);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT16, &f->collecting_item_max);       
    iob->bind(BIND_SIGNATURE_UINT8, &f->routing_try_reroute_counter);                       // 269
    iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_UINT16, &f->phrase.group);                       // 269
    iob->bind(BIND_SIGNATURE_UINT16, &f->sender_building_id);                        // 0
    iob->bind____skip(4);
    iob->bind____skip(12);                                                  // FF FF FF FF FF ...
    iob->bind____skip(2);
    iob->bind____skip(14);                                                  // 00 00 00 00 00 00 00 ...
    iob->bind____skip(2);         // 200
    iob->bind____skip(115);
    iob->bind(BIND_SIGNATURE_UINT8, &f->draw_mode);     // 6
    static_assert(sizeof(figure::runtime_data) == 40, "runtime_data more then 40 bytes");
    iob->bind(BIND_SIGNATURE_RAW, &f->runtime_data, sizeof(figure::runtime_data)); // 40
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_RAW, f->name.data(), 32);

    f->cart_image_id -= 18;
    iob->bind(BIND_SIGNATURE_UINT16, &f->cart_image_id);
    f->cart_image_id += 18;

    iob->bind____skip(2);

    draw_mode = 0;
}