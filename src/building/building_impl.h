#pragma once

#include "building_fwd.h"
#include "building_planer_renderer.h"
#include "graphics/color.h"
#include "overlays/city_overlay_fwd.h"
#include "sound/sound_city.h"
#include "core/string.h"
#include "figure/figure_type.h"
#include "figure/action.h"
#include "building_static_params.h"

struct mouse;
struct object_info;
struct tooltip_context;
class io_buffer;
struct water_access_tiles;
class figure;
struct painter;
struct animation_context;

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
    virtual void on_post_load();
    virtual void spawn_figure() {}
    virtual void update_graphic();
    virtual void update_day();
    virtual void update_week() {}
    virtual void update_month() {}
    virtual void update_year() {}
    virtual void remove_dead_figures();
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask);
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) { return false; }
    virtual void draw_postrender_effects(painter &ctx, vec2i point, tile2i tile, color color_mask) { /*nothing*/ }
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual bool force_draw_top_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) { return false; }
    virtual e_overlay get_overlay() const { return current_params().overlay; }
    virtual bool need_road_access() const { return true; }
    virtual bool can_play_animation() const;
    virtual bool is_enemies_nearby() const;
    virtual void update_count() const;
    virtual void update_map_orientation(int orientation) {}
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_NONE; }
    virtual int animation_speed(int speed) const { return speed; }
    virtual int get_fire_risk(int value) const { return value; }
    virtual textid get_tooltip() const { return { 0, 0 }; }
    virtual int ready_production() const { return current_params().production_rate; }
    virtual void draw_normal_anim(painter &ctx, vec2i point, tile2i tile, color mask);
    virtual void draw_normal_anim(painter &ctx, const animation_context &ranim, vec2i point, tile2i tile, color mask);
    virtual void draw_tooltip(tooltip_context *c) const {};
    virtual void bind_dynamic(io_buffer *iob, size_t version);
    virtual bvariant get_property(const xstring &domain, const xstring &name) const;
    virtual bool add_resource(e_resource resource, int amount) { return false; }
    virtual int get_orientation() const;
    virtual void on_config_reload() {}
    virtual void set_water_access_tiles(const water_access_tiles &tiles) {}
    virtual void start_production() {}
    virtual void debug_draw_properties() {}

    virtual void remove_worker(figure_id fid) {}
    virtual void add_workers(figure_id fid) {}
    virtual bool is_deletable() const { return true; }

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
    ALLOW_SMART_CAST_BUILDING_I(dentist)
    ALLOW_SMART_CAST_BUILDING_I(mortuary)
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
    ALLOW_SMART_CAST_BUILDING_I(dancer_school)
    ALLOW_SMART_CAST_BUILDING_I(police_station)
    ALLOW_SMART_CAST_BUILDING_I(pyramid)
    ALLOW_SMART_CAST_BUILDING_I(small_stepped_pyramid)
    ALLOW_SMART_CAST_BUILDING_I(medium_stepped_pyramid)

    building_impl *next();
    building_impl *main();
    bool is_main() const;
    bool has_figure(int slot);
    bool is_valid() const;
    e_building_state state() const;
    void check_labor_problem();
    int worker_percentage() const;
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_figure_trigger(int min_houses, int slot = BUILDING_SLOT_SERVICE);
    bool common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action);
    int max_workers() const;
    int pct_workers() const;
    int get_figure_id(int i) const;
    int need_resource_amount(e_resource r) const;
    figure *get_figure_in_slot(int i);

    bool has_figure_of_type(int i, e_figure_type _type) const;
    figure *create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action, e_building_slot slot = BUILDING_SLOT_SERVICE);
    figure *create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot);
    figure *create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir);
    figure *create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action, e_building_slot slot);
    figure *get_figure(int slot);
    const figure *get_figure(int slot) const;

    building_id id() const;
    tile2i tile() const;
    int tilex() const;
    int tiley() const;

    int size() const;
    e_building_type type() const;

    int figure_spawn_timer() const;
    int num_workers() const;
    bool has_road_access() const;
    short distance_from_entry() const;
    int road_network() const;
    const animation_t &anim(const xstring &key) const { return current_params().animations[key]; }
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

    struct static_params : building_static_params {};
    inline const static_params &current_params() const { return (const static_params &)building_static_params::get(type()); }
    inline const static_params &current_params() { return (static_params &)building_static_params::get(type()); }

    void consume_resource(e_resource r, int16_t amount);
    void store_resource(e_resource r, int16_t amount);
    const resource_value &stored_first() const;
    resource_value &stored_first();

    building &base;
};

namespace archive_helper {
    template<>
    inline void reader<building_impl::static_params>(archive arch, building_impl::static_params &params) {
        building_static_params &bparams = (building_static_params &)params;
        archive_helper::reader(arch, bparams);
    }
}

// ANK_CONFIG_PROPERTY(building_impl::static_params,
//     type, labor_category, building_size, min_houses_coverage, production_rate,
//     progress_max, overlay, max_service, max_storage_amount,
//     laborers, fire_risk, damage_risk)