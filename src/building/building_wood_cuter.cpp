#include "building_wood_cuter.h"

#include "figure/figure.h"
#include "core/random.h"
#include "js/js_game.h"
#include "building_raw_material.h"
#include "widget/city/ornaments.h"
#include "grid/routing/routing.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/terrain.h"
#include "game/game_events.h"
#include "city/city_resource.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_wood_cutter);

void building_wood_cutter::on_create(int orientation) {
    runtime_data().max_gatheres = current_params().max_gatherers;
}

void building_wood_cutter::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_UINT8, &d.max_gatheres);
}

bool building_wood_cutter::can_spawn_lumberjack(int max_gatherers_per_building, int carry_per_person) {
    bool resource_reachable = map_routing_citizen_found_terrain(base.road_access, nullptr, TERRAIN_TREE);

    if (!resource_reachable) {
        return false;
    }

    int gatherers_this_yard = base.get_figures_number(FIGURE_LUMBERJACK);

    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
        && gatherers_this_yard + (base.stored_amount() / carry_per_person) < (max_loads - gatherers_this_yard)) {
        return true;
    }

    return false;
}

void building_wood_cutter::spawn_figure() {
    check_labor_problem();
    if (has_road_access()) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            return;
        }

        base.figure_spawn_delay++;
        if (base.figure_spawn_delay > spawn_delay) {
            base.figure_spawn_delay = 0;

            const bool can_spawn = can_spawn_lumberjack(runtime_data().max_gatheres, 50);
            if (can_spawn) {
                auto f = create_figure_generic(FIGURE_LUMBERJACK, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
                random_generate_next();
                f->wait_ticks = random_short() % 30; // ok
            }
        }
    }

    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
    }
}

bool building_wood_cutter::can_play_animation() const {
    if (base.stored_amount() >= current_params().max_storage_amount) {
        return false;
    }

    return building_industry::can_play_animation();
}

bool building_wood_cutter::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &eanim = anim(animkeys().wood);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = eanim.first_img() + amount;
        command.pixel = point + eanim.pos;
        command.mask = color_mask;
    }

    return true;
}