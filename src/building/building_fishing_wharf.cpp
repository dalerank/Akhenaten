#include "building_fishing_wharf.h"

#include "city/city.h"
#include "grid/water.h"
#include "grid/building.h"
#include "city/buildings.h"
#include "game/game_config.h"
#include "figuretype/figure_fishing_boat.h"
#include "figuretype/figure_cartpusher.h"
#include "building/building_temple_complex.h"
#include "core/random.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "js/js_game.h"
#include "dev/debug.h"

BUILDING_RUNTIME_DATA_IMPL(building_fishing_wharf)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fishing_wharf);

declare_console_command_p(killfishboats) {
    figure_valid_do([] (figure &f) { f.poof(); }, make_array(FIGURE_FISHING_BOAT));
}

namespace {

bool temple_complex_osiris_has_oracle() {
    const building_id complex_id = g_city.buildings.temple_complex_id(BUILDING_TEMPLE_COMPLEX_OSIRIS);
    if (!complex_id) {
        return false;
    }
    building *complex_b = building_get(complex_id);
    auto *complex = complex_b ? complex_b->dcast_temple_complex() : nullptr;
    return complex && complex->has_upgrade(etc_upgrade_oracle);
}

} // namespace

void building_fishing_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = g_camera.relative_orientation(orientation);
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

void building_fishing_wharf::spawn_figure() {
    check_labor_problem();

    int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
    if (boat_id) {
        figure *boat = figure_get(boat_id);
        if (!boat->is_valid() || boat->type != FIGURE_FISHING_BOAT) {
            base.set_figure(BUILDING_SLOT_BOAT, 0);
            boat_id = 0;
        }
    }

    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    if (!!game_features::gameplay_fishing_wharf_spawn_boats) {
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay != -1) {
            base.figure_spawn_delay++;
            if (!boat_id && base.figure_spawn_delay > spawn_delay) {
                base.figure_spawn_delay = 0;

                tile2i dtile = get_water_access_tiles().point_a;
                if (dtile.valid() && map_terrain_is(dtile, TERRAIN_WATER)) {
                    figure* f = figure_create(FIGURE_FISHING_BOAT, dtile, DIR_4_BOTTOM_LEFT);
                    if (f) {
                        f->action_state = ACTION_0_FISHING_BOAT_CREATED;
                        f->set_home(id());
                        base.set_figure(BUILDING_SLOT_BOAT, f);
                        random_generate_next();
                        f->wait_ticks = random_short() % 30;
                    }
                }
            }
        }
    }

    if (!!game_features::gameplay_change_fishing_boat_remake) {
        common_spawn_goods_output_cartpusher();
        return;
    }

    if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return;
    }
    if (base.figure_spawn_delay == 0) {
        return;
    }

    base.figure_spawn_delay = 0;
    runtime_data().fish_caught = 0;

    int amount = 100;
    if (temple_complex_osiris_has_oracle()) {
        amount <<= 1;
    }

    figure *cart = create_cartpusher(RESOURCE_FISH, amount, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
    if (cart) {
        produced_resources(RESOURCE_FISH, cart->get_carrying_amount());
    }
}

void building_fishing_wharf::on_undo() {
    base.set_figure(BUILDING_SLOT_BOAT, 0);
}

void building_fishing_wharf::update_map_orientation(int orientation) {
    int image_offset = g_camera.relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_fishing_wharf::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    auto &anim_wharf = base.anim;
    auto &d = runtime_data();
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.start_frame() + (d.docker_anim_frame / anim_wharf.frame_duration) * 4;

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = img_id;
        command.pixel = point + anim_wharf.pos;
        command.mask = color_mask;
        command.flags = ImgFlag_InternalOffset;
    }

    return true;
}

void building_fishing_wharf::bind_dynamic(io_buffer *iob, size_t version) {
    building_wharf::bind_dynamic(iob, version);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.fish_caught);
    iob->bind(BIND_SIGNATURE_UINT8, &d.no_fishing_points_warning_shown);
}
