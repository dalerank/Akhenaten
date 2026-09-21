#include "building_mine_copper.h"

#include "building/building.h"
#include "city/city_resource.h"
#include "game/game_events.h"
#include "figure/figure.h"
#include "js/js_game.h"
#include "grid/copper.h"
#include "grid/grid.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "game/resource.h"
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_copper);

void building_mine_copper::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area, [&] (tile2i t) {
        int resource = map_get_copper(t);
        if (resource > 0 && resource > best_resource) {
            best_tile = t;
            best_resource = resource;
        }
    });

    if (best_resource <= 0) {
        return;
    }

    building_industry::update_production();
    int delta_progress = d.progress - current_progress;

    if (delta_progress > 0) {
        map_copper_deplete(best_tile, delta_progress);
    }
}

void building_mine_copper::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    // Check if production is finished and add resources to storage
    auto &d = runtime_data();
    if (d.progress >= d.progress_max) {
        production_finished();
    }

    common_spawn_goods_output_cartpusher();
}

void building_mine_copper::production_finished() {
    if (stored_amount(RESOURCE_COPPER) >= base.max_storage_amount(RESOURCE_COPPER)) {
        return;
    }

    auto &d = runtime_data();
    if (d.progress >= d.progress_max) {
        store_resource(RESOURCE_COPPER, ready_production());

        d.progress = 0;
        //d.has_raw_materials = false;
    }
}

bool building_mine_copper::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceil((float)stored_amount(RESOURCE_COPPER) / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().copper);
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

