#pragma once

class figure;
class building;
struct object_info;
struct painter;
struct animations_t;
struct formation;
struct animation_context;

#include "figure/figure_static_params.h"
#include "figure/figure_classes.h"
#include "overlays/city_overlay_fwd.h"
#include "core/vec2i.h"
#include "sound/sound_walker.h"
#include "figure/figure_phrase.h"
#include "figure/figure_common.h"
#include "empire/empire_city.h"
#include "building/building_type.h"
#include "city/constants.h"

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
    virtual void draw_main_sprite(painter &ctx, vec2i pixel, int highlight);
    virtual void before_poof() {}
    virtual void poof();
    virtual e_overlay get_overlay() const { return OVERLAY_NONE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const;
    virtual sound_key phrase_key() const { return "empty"; }
    virtual sound_key default_phrase_key() const;
    virtual int provide_service() { return 0; }
    virtual bool play_die_sound() { return false; }
    virtual void update_animation();
    virtual void update_day() {}
    virtual bool can_move_by_water() const;
    virtual void cart_image_update();
    virtual void set_cart_offset(int direction) const;
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
    virtual bool is_home(const building *b) const;
    virtual bool is_destination(const building *b) const;
    virtual empire_city_handle empire_city() const { return empire_city_handle{}; }
    virtual void formation_reset_to_initial(const formation *m) {}
    virtual void apply_damage(int hit_dmg, figure_id attaker_id);
    virtual void acquire_attack();

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
    ALLOW_SMART_CAST_FIGURE_I(enemy)
    ALLOW_SMART_CAST_FIGURE_I(fishing_boat)
    ALLOW_SMART_CAST_FIGURE_I(fishing_point)
    ALLOW_SMART_CAST_FIGURE_I(ferry_boat)
    ALLOW_SMART_CAST_FIGURE_I(caravan_donkey)
    ALLOW_SMART_CAST_FIGURE_I(trade_caravan)
    ALLOW_SMART_CAST_FIGURE_I(warship)
    ALLOW_SMART_CAST_FIGURE_I(transport_ship)
    ALLOW_SMART_CAST_FIGURE_I(stonemason)
    ALLOW_SMART_CAST_FIGURE_I(carpenter)
    ALLOW_SMART_CAST_FIGURE_I(enemy_archer)
    ALLOW_SMART_CAST_FIGURE_I(enemy_spearman)
    ALLOW_SMART_CAST_FIGURE_I(missile)
    ALLOW_SMART_CAST_FIGURE_I(fireman)
    ALLOW_SMART_CAST_FIGURE_I(festival_guy)
    ALLOW_SMART_CAST_FIGURE_I(ostrich)
    ALLOW_SMART_CAST_FIGURE_I(antelope)
    ALLOW_SMART_CAST_FIGURE_I(hippo)
    ALLOW_SMART_CAST_FIGURE_I(hyena)
    ALLOW_SMART_CAST_FIGURE_I(animal)
    ALLOW_SMART_CAST_FIGURE_I(ballista)
    ALLOW_SMART_CAST_FIGURE_I(market_buyer)
    ALLOW_SMART_CAST_FIGURE_I(bricklayer)

    building *home();
    e_figure_type type() const;
    int id();

    short action_state() const;
    template<typename ... Args>
    bool action_state(const Args... args) const {
        int states[] = {args...};
        return std::find(std::begin(states), std::end(states), this->action_state()) != std::end(states);
    }

    uint8_t direction() const;
    template<typename ... Args>
    bool direction(const Args... args) const {
        int states[] = { args... };
        return std::find(std::begin(states), std::end(states), this->direction()) != std::end(states);
    }

    const building *home() const;
    const animation_t &anim(const xstring &anim_key) const;
    animation_context &animation();
    const animation_context &animation() const;
    void advance_action(int action);
    void advance_action(int action, tile2i t);

    bool do_returnhome(e_terrain_usage terrainchoice, short next_action = -1);
    bool do_gotobuilding(building *dest, bool stop_at_road = true, e_terrain_usage terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = -1, short FAIL_ACTION = -1);
    bool do_enterbuilding(bool invisible, building *b, short next_action = -1, short fail_action = -1);
    bool do_exitbuilding(bool invisible, short next_action = -1, short fail_action = -1);
    bool do_roam(int terrainchoice, short next_action);
    bool do_goto(tile2i dest, int terrainchoice = TERRAIN_USAGE_ROADS, short next_action = -1, short fail_action = -1);
    tile2i tile() const;
    int tilex() const;
    int tiley() const;
    building *destination() const;
    void route_remove();
    void image_set_animation(const xstring &anim_key);
    void image_set_animation(const animation_t &anim);
    void follow_ticks(int num_ticks);
    bool has_destination(int _id = -1);
    void set_destination(building_id _id);
    void set_destination(building *b);
    void set_destination(building *b, tile2i t);
    void set_home(int _id);
    void set_home(building *b);
    void set_direction_to(building *b);
    bool is_alive() const;
    e_permission get_permission() const;

    struct static_params : figure_static_params {};
    const static_params &current_params() const;
    static_params &current_params();
    const static_params &params() const;
    static_params &params();

    void set_sled_offset(int direction);

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
GENERATE_SMART_CAST_FIGURE(ferry_boat)
GENERATE_SMART_CAST_FIGURE(soldier)
GENERATE_SMART_CAST_FIGURE(warship)
GENERATE_SMART_CAST_FIGURE(caravan_donkey)
GENERATE_SMART_CAST_FIGURE(trade_caravan)
GENERATE_SMART_CAST_FIGURE(transport_ship)
GENERATE_SMART_CAST_FIGURE(stonemason)
GENERATE_SMART_CAST_FIGURE(carpenter)
GENERATE_SMART_CAST_FIGURE(enemy)
GENERATE_SMART_CAST_FIGURE(enemy_archer)
GENERATE_SMART_CAST_FIGURE(enemy_spearman)
GENERATE_SMART_CAST_FIGURE(missile)
GENERATE_SMART_CAST_FIGURE(fireman)
GENERATE_SMART_CAST_FIGURE(festival_guy)
GENERATE_SMART_CAST_FIGURE(ostrich)
GENERATE_SMART_CAST_FIGURE(antelope)
GENERATE_SMART_CAST_FIGURE(hippo)
GENERATE_SMART_CAST_FIGURE(hyena)
GENERATE_SMART_CAST_FIGURE(animal)
GENERATE_SMART_CAST_FIGURE(ballista)
GENERATE_SMART_CAST_FIGURE(market_buyer)
GENERATE_SMART_CAST_FIGURE(bricklayer)

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

    template<typename F>
    static figure_impl *create(e_figure_type e, F &f) {
        if (e == TYPE) {
            return f.template acquire_impl<figure_type>();
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
