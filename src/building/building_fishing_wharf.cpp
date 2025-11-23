#include "building_fishing_wharf.h"

#include "city/city.h"
#include "grid/water.h"
#include "grid/building.h"
#include "city/buildings.h"
#include "city/city_warnings.h"
#include "game/game_config.h"
#include "figuretype/figure_fishing_boat.h"
#include "core/random.h"
#include "grid/image.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "construction/build_planner.h"
#include "js/js_game.h"
#include "dev/debug.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fishing_wharf);

declare_console_command_p(killfishboats) {
    figure_valid_do([] (figure &f) { f.poof(); }, make_array(FIGURE_FISHING_BOAT));
}

int building_fishing_wharf::preview::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto result = map_shore_determine_orientation(end, params.building_size, true);
    planer.draw_as_constructing = result.match;
    return 1;
}

void building_fishing_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    int img_id = base_img();
    map_water_add_building(id(), tile(), size(), img_id + orientation_rel);
}

void building_fishing_wharf::update_count() const {
    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_fishing_boat();
        }
    }

    g_city.buildings.increase_industry_count(RESOURCE_FISH, num_workers() > 0);
}

void building_fishing_wharf::update_day() {
    building_wharf::update_day();

    auto boat = ::smart_cast<figure_fishing_boat>(get_figure_in_slot(BUILDING_SLOT_BOAT));
    if (!boat) {
        base.set_figure(BUILDING_SLOT_BOAT, 0);
    }
}

void building_fishing_wharf::update_month() {
    building_wharf::update_month();

    map_water_update_docking_points(base, get_orientation(), 1);
}

void building_fishing_wharf::update_graphic() {
    building_impl::update_graphic();

    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }
    
    figure *f = base.get_figure(BUILDING_SLOT_BOAT);
    if (!f->is_valid()) {
        set_animation(animkeys().none);
        return;
    }

    int image_warf = map_image_at(tile());
    int image_warf_base = base_img();
    const bool has_cart = base.get_figure_id(BUILDING_SLOT_CARTPUSHER);
    xstring animkey;
    if (f->action_state != ACTION_194_FISHING_BOAT_AT_WHARF) {
        if (image_warf == image_warf_base) animkey = animkeys().wait_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().wait_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().wait_s;
        else animkey = animkeys().wait_e;
    } else {
        if (has_cart) animkey = animkeys().none;
        else if (image_warf == image_warf_base) animkey = animkeys().work_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().work_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().work_s;
        else animkey = animkeys().work_e;
    }

    set_animation(animkey);
}

void building_fishing_wharf::spawn_figure() {
    check_labor_problem();

    auto &d = runtime_data();
    if (has_road_access()) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            ; // nothing
        } else {
            base.figure_spawn_delay++;
            int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
            if (!boat_id && base.figure_spawn_delay > spawn_delay) {
                base.figure_spawn_delay = 0;


                int dock_tile = d.dock_tiles[0];
                if (!!game_features::gameplay_fishing_wharf_spawn_boats && dock_tile > 0) {
                    tile2i dtile(dock_tile);
                    figure* f = figure_create(FIGURE_FISHING_BOAT, dtile, DIR_4_BOTTOM_LEFT);
                    f->action_state = ACTION_190_FISHING_BOAT_CREATED;
                    f->set_home(id());
                    base.set_figure(BUILDING_SLOT_BOAT, f);
                    random_generate_next();
                    f->wait_ticks = random_short() % 30; // ok                   
                }
            }
        }
    }

    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
        d.has_fish = (base.stored_amount_first > 0);
    }
}

void building_fishing_wharf::on_place_checks() {
    building_impl::on_place_checks();

    construction_warnings warnings;
    const bool has_shipyard = g_city.buildings.has_working_shipyard();
    warnings.add_if(!has_shipyard, "#warning_shipwright_needed");
}

void building_fishing_wharf::on_undo() {
    base.set_figure(BUILDING_SLOT_BOAT, 0);
}

void building_fishing_wharf::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_fishing_wharf::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    auto &anim_wharf = base.anim;
    auto &d = runtime_data();
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.start_frame() + (d.docker_anim_frame / anim_wharf.frame_duration) * 4;

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = img_id;
        command.pixel = point + anim_wharf.pos;
        command.mask = color_mask;
        command.flags = ImgFlag_InternalOffset;
    }

    return true;
}

void building_fishing_wharf::highlight_waypoints() {
    building_impl::highlight_waypoints();

    const auto &d = runtime_data();
    map_highlight_set(d.dock_tiles[0], ehighligth_green);
    map_highlight_set(d.dock_tiles[1], ehighligth_green);
}

void building_fishing_wharf::bind_dynamic(io_buffer *iob, size_t version) {
    building_wharf::bind_dynamic(iob, version);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.has_fish);
}