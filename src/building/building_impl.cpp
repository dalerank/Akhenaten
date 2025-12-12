#include "building_impl.h"

#include "building/building.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "city/city_warnings.h"
#include "grid/road_access.h"
#include "city/city.h"
#include "grid/image.h"
#include "grid/building.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "core/object_property.h"
#include "core/archive.h"
#include "grid/floodplain.h"
#include "building/destruction.h"

void building_impl::on_place(int orientation, int variant) {
    const auto &p = current_params();

    base.fire_proof = p.fire_proof;
    base.damage_proof = p.damage_proof;

    base.output_resource_second_rate = p.output_resource_second_rate;

    on_place_update_tiles(orientation, variant);
    update_graphic();
}

void building_impl::on_place_update_tiles(int orientation, int variant) {
    map_building_tiles_add(id(), tile(), base.size, base_img(), TERRAIN_BUILDING);
}

void building_impl::on_place_checks() {
    // check road access
    switch (type()) {
    case BUILDING_NONE:
    case BUILDING_CLEAR_LAND:
        return;
    }

    construction_warnings warnings;
    const bool has_road = map_has_road_access(tile(), size());
    warnings.add_if(!has_road, "#needs_road_access");

    const bool need_workers = (base.max_workers > 0 && g_city.labor.workers_needed >= 10);
    warnings.add_if(need_workers, "#city_needs_more_workers");
}

void building_impl::update_graphic() {
    base.minimap_anim = anim("minimap");
}

void building_impl::remove_dead_figures() {
    for (int i = 0; i < base.max_figures; i++) {
        figure *f = this->get_figure(i);
        if (f->state != FIGURE_STATE_ALIVE) {
            base.figure_ids[i] = 0;
        }
    }
}

void building_impl::update_day() {
    update_graphic();
    remove_dead_figures();
}

figure *building_impl::get_figure_in_slot(int slot) {
    return figure_get(get_figure_id(slot));
}

bool building_impl::has_figure_of_type(int i, e_figure_type _type) const { return base.has_figure_of_type(i, _type); }

figure *building_impl::create_figure_with_destination(e_figure_type _type, building *destination, e_figure_action created_action, e_building_slot slot) { return base.create_figure_with_destination(_type, destination, created_action, slot); }

figure *building_impl::create_roaming_figure(e_figure_type _type, e_figure_action created_action, e_building_slot slot) { return base.create_roaming_figure(_type, created_action, slot); }

figure *building_impl::create_figure_generic(e_figure_type _type, e_figure_action created_action, e_building_slot slot, int created_dir) { return base.create_figure_generic(_type, created_action, slot, created_dir); }

figure *building_impl::create_cartpusher(e_resource resource_id, int quantity, e_figure_action created_action, e_building_slot slot) { return base.create_cartpusher(resource_id, quantity, created_action, slot); }

figure *building_impl::get_figure(int slot) { return base.get_figure(slot); }

const figure *building_impl::get_figure(int slot) const { return base.get_figure(slot); }

building_id building_impl::id() const { return base.id; }

tile2i building_impl::tile() const { return base.tile; }

int building_impl::tilex() const { return base.tile.x(); }

int building_impl::tiley() const { return base.tile.y(); }

int building_impl::size() const { return base.size; }

e_building_type building_impl::type() const { return base.type; }

int building_impl::figure_spawn_timer() const { return base.figure_spawn_timer(); }

int building_impl::num_workers() const { return base.num_workers; }

bool building_impl::has_road_access() const { return base.has_road_access; }

short building_impl::distance_from_entry() const { return base.distance_from_entry; }

int building_impl::road_network() const { return base.road_network_id; }

bool building_impl::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (!base.anim.key) {
        int image_id = map_image_at(tile.grid_offset());
        building_draw_normal_anim(ctx, point, &base, tile, image_id, color_mask);
    } else {
        draw_normal_anim(ctx, point, tile, color_mask);
    }

    if (base.has_plague) {
        int skull_img = image_id_from_group(GROUP_PLAGUE_SKULL);

        auto &command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = skull_img;
        command.pixel = { point.x + 18, point.y - 32 };
        command.mask = color_mask;
    }

    return false;
}

bool building_impl::can_play_animation() const {
    return base.main()->num_workers > 0;
}

void building_impl::update_count() const {
    g_city.buildings.increase_count(base.type, base.num_workers > 0);
}

void building_impl::draw_normal_anim(painter &ctx, vec2i pixel, tile2i tile, color mask) {
    if (!can_play_animation()) {
        return;
    }

    draw_normal_anim(ctx, base.anim, pixel, tile, mask);
}

void building_impl::draw_normal_anim(painter &ctx, const animation_context &ranim, vec2i pixel, tile2i tile, color mask) {
    if (!ranim.valid()) {
        return;
    }

    vec2i pos = pixel + ranim.pos;
    auto &command = ImageDraw::create_subcommand(render_command_t::ert_generic);
    command.image_id = ranim.start_frame() + ranim.current_frame();
    command.pixel = pos;
    command.mask = mask;
    command.flags = ranim.flags;
}

void building_impl::bind_dynamic(io_buffer *iob, size_t version) {
    assert(base.output.resource == current_params().output.resource);
}

const auto& get_properties() {
    static const svector<bproperty, 16> bproperties = {
        { tags().stored, xstring("*"),
            [] (building &b, const xstring &name) {
                e_resource res = resource_type(name);
                return bvariant(b.stored_amount(res));
            }
        },

        { tags().text, xstring("*"),
            [] (building &b, const xstring &name) {
                 int id = atoi(name.c_str());
                 const auto &m = building_static_params::get(b.type).meta;
                 return bvariant(ui::str(m.text_id, id));
            }
        },

        { tags().building, tags().name, [] (building &b, const xstring &) { return bvariant(b.cls_name()); }},
        { tags().building, tags().num_workers, [] (building &b, const xstring &) { return bvariant(b.num_workers); }},
        { tags().model, tags().laborers, [] (building &b, const xstring &) { return bvariant(b.max_workers); }},
        { tags().building, tags().output_resource, [] (building &b, const xstring &) { return bvariant(resource_name(b.output.resource)); }},
        { tags().building, tags().second_output_resource, [] (building &b, const xstring &) { return bvariant(resource_name(b.output.resource_second)); }},
        { tags().building, tags().first_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.input.resource)); }},
        { tags().building, tags().first_material_stored, [] (building &b, const xstring &) { return bvariant(b.stored_first().value); }},
        { tags().building, tags().second_material, [] (building &b, const xstring &) { return bvariant(resource_name(b.input.resource_second)); }},
        { tags().building, tags().second_material_stored, [] (building &b, const xstring &) { return bvariant(b.stored_second().value); }},
        { tags().farm, tags().fertility, [] (building &b, const xstring &) { return bvariant(map_get_fertility_for_farm(b.tile.grid_offset())); }},
    };
    return bproperties;
}

void building_impl::consume_resource(e_resource r, int16_t amount) { 
    base.consume_resource(r, amount); 
}

void building_impl::store_resource(e_resource r, int16_t amount) {
    base.store_resource(r, amount);
}

const resource_value& building_impl::stored_first() const {
    return base.stored_first();
}

resource_value &building_impl::stored_first() {
    return base.stored_first();
}

bvariant building_impl::get_property(const xstring &domain, const xstring &name) const {
    // Try to get property from static_params first
    // auto result = archive_helper::get(current_params(), name, domain == tags().building);
    // if (result) {
    //     return result.value();
    // }
    
    // Then try properties from get_properties()
    static const xstring wildname("*");
    for (const auto &prop : get_properties()) {
        if (prop.domain != domain) {
            continue;
        }

        if (prop.name == name || prop.name == wildname) {
            return prop.handler(base, name);
        }
    }

    return bvariant();
}

int building_impl::get_orientation() const {
    return base.orientation;
}

building_impl *building_impl::next() { return base.next()->dcast(); }
building_impl *building_impl::main() { return base.main()->dcast(); }
bool building_impl::is_main() const { return base.is_main(); }
bool building_impl::has_figure(int slot) { return base.has_figure(slot); }
bool building_impl::is_valid() const { return base.is_valid(); }
e_building_state building_impl::state() const { return base.state; }
void building_impl::check_labor_problem() { base.check_labor_problem(); }
int building_impl::worker_percentage() const { return base.worker_percentage(); }
void building_impl::common_spawn_labor_seeker(int min_houses) { base.common_spawn_labor_seeker(min_houses); }
bool building_impl::common_spawn_figure_trigger(int min_houses, int slot) { return base.common_spawn_figure_trigger(min_houses, slot); }
bool building_impl::common_spawn_roamer(e_figure_type type, int min_houses, e_figure_action created_action) { return base.common_spawn_roamer(type, min_houses, created_action); }
int building_impl::max_workers() const { return base.max_workers; }
int building_impl::pct_workers() const { return calc_percentage<int>(num_workers(), max_workers()); }
int building_impl::get_figure_id(int i) const { return base.get_figure_id(i); }
int building_impl::need_resource_amount(e_resource r) const { return base.need_resource_amount(r); }

void building_impl::destroy_by_poof(bool clouds) {
    building_destroy_by_poof(&base, clouds);
}

void building_impl::highlight_waypoints() { // highlight the 4 routing tiles for roams from this building
    map_clear_highlights();
    if (has_road_access()) {
        map_highlight_set(base.road_access, ehighligth_red);
    }

    int hx, hy;
    hx = tilex();
    hy = tiley() - 8;
    map_grid_bound(&hx, &hy);
    tile2i road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex() + 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex();
    hy = tiley() + 8;
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }

    hx = tilex() - 8;
    hy = tiley();
    map_grid_bound(&hx, &hy);
    road_tile = map_closest_road_within_radius(tile2i(hx, hy), 1, 6);
    if (road_tile.valid()) {
        map_highlight_set(road_tile, ehighligth_blue);
    }
}

void building_impl::on_tick(bool refresh_only) {
    if (!base.anim.valid()) {
        return;
    }

    base.anim.update(refresh_only);
}