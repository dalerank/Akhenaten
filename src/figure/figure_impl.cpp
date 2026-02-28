#include "figure/figure_impl.h"

#include "figure/figure.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "figure/figure_names.h"
#include "figure/cart_images.h"
#include "graphics/animkeys.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/ui.h"
#include "grid/terrain.h"
#include "core/object_property.h"
#include "core/profiler.h"

#include "dev/debug.h"

std::array<vec2i, 8> ANK_VARIABLE(cartpusher_sled_offsets);
std::array<vec2i, 8> ANK_VARIABLE(cartpusher_cart_offsets);

static int cart_image_offset_from_amount(int amount) {
    return ((amount > 100) & 1) + ((amount > 200) & 1);
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

void figure_impl::on_create() {
    assert(base.tile.x() < GRID_LENGTH && base.tile.y() < GRID_LENGTH);
}

void figure_impl::on_post_load() {
    on_change_terrain(0, base.terrain_type);

    if (base.name.len() < 4) {
        base.name = figure_name_get(base.type);
    }
}

void figure_impl::set_cart_offset(int direction) const {
    base.cart_offset = cartpusher_cart_offsets[direction];
}

void figure_impl::set_sled_offset(int direction) {
    base.cart_offset = cartpusher_sled_offsets[direction];
}

void figure_impl::cart_image_update() {
    if (!base.use_cart) {
        return;
    }

    OZZY_PROFILER_FUNCTION();
    base.cart_image_id = 0;

    switch (base.resource_id) {
    case RESOURCE_STONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_GRANITE:
    case RESOURCE_SANDSTONE:
    case RESOURCE_BRICKS:
        if (base.resource_amount_full > 0) {
            image_desc imgd = resource2sled(base.resource_id);
            base.cart_image_id = imgd.tid();
        } else {
            image_desc imgd = resource2sled(RESOURCE_NONE);
            base.cart_image_id = imgd.tid();
        }
        break;

    case RESOURCE_BARLEY:
    case RESOURCE_COPPER:
    case RESOURCE_BEER:
    case RESOURCE_PAPYRUS:
    case RESOURCE_REEDS:
    case RESOURCE_GOLD:
    case RESOURCE_GEMS:
    case RESOURCE_FLAX:
    case RESOURCE_TIMBER:
        base.cart_image_id = resource2cart(RESOURCE_NONE).tid();
        if (base.resource_amount_full > 0) {
            base.cart_image_id = resource2cart(base.resource_id).tid();
            int amount_offset = cart_image_offset_from_amount(base.resource_amount_full);
            base.cart_image_id += 8 * amount_offset;
        }
        break;

    default:
        base.cart_image_id = resource2cart(RESOURCE_NONE).tid();
        if (base.resource_amount_full > 0) {
            int amount_offset = cart_image_offset_from_amount(base.resource_amount_full);
            base.cart_image_id += 8 + 24 * (base.resource_id - 1) + 8 * amount_offset;
        }
    }
    int dir = base.figure_image_normalize_direction(base.direction < 8 ? base.direction : base.previous_tile_direction);

    switch (base.resource_id) {
    case RESOURCE_GRANITE:
    case RESOURCE_STONE:
    case RESOURCE_SANDSTONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_BRICKS:
        if (base.cart_image_id) {
            base.cart_image_id += dir;
            set_sled_offset(dir);
        }
        break;

    default:
        if (base.cart_image_id) {
            base.cart_image_id += dir;
            set_cart_offset(dir);
        }
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
    OZZY_PROFILER_FUNCTION();
    if (base.state == FIGURE_STATE_DYING) {
        base.main_image_id = base.animctx.start_frame() + base.animctx.current_frame();
    } else {
        base.main_image_id = base.animctx.start_frame() + base.figure_image_direction() + 8 * base.animctx.current_frame();
    }
}

void figure_impl::kill() {
    base.kill();
}

void figure_impl::acquire_attack() {
}

void figure_impl::advance_action(int action, tile2i t) {
    advance_action(action);
    base.destination_tile = t;
}

void figure_impl::draw_main_sprite(painter &ctx, vec2i pixel, int highlight) {
    base.draw_main_sprite(ctx, base.main_cached_pos, highlight);
}

void figure_impl::poof() {
    base.poof();
}

void figure_impl::set_destination(building *b, tile2i t) {
    base.set_destination(b);
    base.destination_tile = t;
}

metainfo figure_impl::get_info() const {
    return params().meta;
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

static const fproperty fproperties[] = {
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

building *figure_impl::home() {
    return base.home();
}

e_figure_type figure_impl::type() const {
    return base.type;
}

int figure_impl::id() {
    return base.id;
}

short figure_impl::action_state() const {
    return base.action_state;
}

uint8_t figure_impl::direction() const {
    return base.direction;
}

const building *figure_impl::home() const {
    return base.home();
}

const animation_t &figure_impl::anim(const xstring &anim_key) const {
    return base.anim(anim_key);
}

animation_context &figure_impl::animation() {
    return base.animctx;
}

const animation_context &figure_impl::animation() const {
    return base.animctx;
}

void figure_impl::advance_action(int action) {
    int saved_action = action;
    base.advance_action(action);
    on_action_changed(saved_action);
}

bool figure_impl::do_returnhome(e_terrain_usage terrainchoice, short next_action) {
    return base.do_returnhome(terrainchoice, next_action);
}

bool figure_impl::do_gotobuilding(building *dest, bool stop_at_road, e_terrain_usage terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    return base.do_gotobuilding(dest, stop_at_road, terrainchoice, NEXT_ACTION, FAIL_ACTION);
}

bool figure_impl::do_enterbuilding(bool invisible, building *b, short next_action, short fail_action) {
    return base.do_enterbuilding(invisible, b, next_action, fail_action);
}

bool figure_impl::do_exitbuilding(bool invisible, short next_action, short fail_action) {
    return base.do_exitbuilding(invisible, next_action, fail_action);
}

bool figure_impl::do_roam(int terrainchoice, short next_action) {
    return base.do_roam(terrainchoice, next_action);
}

bool figure_impl::do_goto(tile2i dest, int terrainchoice, short next_action, short fail_action) {
    return base.do_goto(dest, terrainchoice, next_action, fail_action);
}

tile2i figure_impl::tile() const {
    return base.tile;
}

int figure_impl::tilex() const {
    return base.tile.x();
}

int figure_impl::tiley() const {
    return base.tile.y();
}

building *figure_impl::destination() const {
    return base.destination();
}

void figure_impl::route_remove() {
    base.route_remove();
}

void figure_impl::image_set_animation(const animation_t &anim) {
    base.image_set_animation(anim);
}

void figure_impl::image_set_animation(const xstring &anim_key) {
    image_set_animation(anim(anim_key));
}

void figure_impl::follow_ticks(int num_ticks) {
    base.follow_ticks(num_ticks);
}

bool figure_impl::has_destination(int _id) {
    return base.has_destination(_id);
}

void figure_impl::set_destination(building_id _id) {
    base.set_destination(_id);
}

void figure_impl::set_destination(building *b) {
    base.set_destination(b);
}

void figure_impl::set_home(int _id) {
    base.set_home(_id);
}

void figure_impl::set_home(building *b) {
    base.set_home(b);
}

void figure_impl::set_direction_to(building *b) {
    base.set_direction_to(b);
}

bool figure_impl::is_alive() const {
    return base.is_alive();
}

e_permission figure_impl::get_permission() const {
    return current_params().permission;
}

bool figure_impl::is_home(const building *b) const {
    return base.home_building_id > 0 && base.home_building_id == (b ? b->id : 0);
}

bool figure_impl::is_destination(const building *b) const {
    return base.destination_building_id > 0 && base.destination_building_id == (b ? b->id : 0);
}

void figure_impl::apply_damage(int hit_dmg, figure_id attaker_id) {
    base.damage += hit_dmg;
}

const figure_impl::static_params &figure_impl::current_params() const {
    return (const static_params &)figure_static_params::get(type());
}

figure_impl::static_params &figure_impl::current_params() {
    return (static_params &)figure_static_params::get(type());
}

const figure_impl::static_params &figure_impl::params() const {
    return (const static_params &)figure_static_params::get(type());
}

figure_impl::static_params &figure_impl::params() {
    return (static_params &)figure_static_params::get(type());
}
