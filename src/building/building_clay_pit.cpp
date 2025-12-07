#include "building_clay_pit.h"

#include "building/building.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "city/city_resource.h"
#include "widget/city/ornaments.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "grid/clay.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "sound/sound.h"
#include "city/city_maintenance.h"
#include "building/construction/clear.h"
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_clay_pit);

int building_clay_pit::get_fire_risk(int value) const {
    if (!!game_features::gameplay_change_fire_risk_clay_pit_reduced) {
        return value / 2;
    }

    return value;
}

void building_clay_pit::on_before_flooded() {
    base.destroy_reason = e_destroy_flooded;
    base.num_workers = 0;
    auto &d = runtime_data();
    d.progress = 0;

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

int building_clay_pit::stored_amount(e_resource r) const {
    if (r == RESOURCE_CLAY || r == base.output.resource) {
        return base.stored_amount_first;
    }
    return building_industry::stored_amount(r);
}

void building_clay_pit::spawn_figure() {
    if (base.destroy_reason == e_destroy_flooded) {
        return;
    }
    
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
            
    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
    }
}

void building_clay_pit::production_finished() {
    if (stored_amount(RESOURCE_CLAY) >= base.max_storage_amount(RESOURCE_CLAY)) {
        return;
    }

    auto &d = runtime_data();
    if (d.progress >= d.progress_max) {
        base.stored_amount_first += ready_production();

        d.progress = 0;
        d.has_raw_materials = false;
    }
}

void building_clay_pit::update_production() {
    if (base.destroy_reason == e_destroy_flooded) {
        return;
    }

    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_clay = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
        int clay = map_get_clay(t);
        if (clay > 0 && clay > best_clay) {
            best_tile = t;
            best_clay = clay;
        }
    });

    if (best_clay <= 0) {
        return;
    }
    
    building_industry::update_production();
    int delta_progress = d.progress - current_progress;
    if (delta_progress > 0) {
        map_clay_deplete(best_tile, delta_progress);
    }
}

void building_clay_pit::update_graphic() {
    if (base.destroy_reason == e_destroy_flooded) {
        set_animation("flooded");
        return;
    }

    building_industry::update_graphic();
}

bool building_clay_pit::is_deletable() const {
    if (base.destroy_reason == e_destroy_flooded) {
        return false;
    }

    return true;
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    if (base.destroy_reason == e_destroy_flooded) {
        return true;
    }

    int amount = ceil((float)stored_amount(RESOURCE_CLAY) / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().clay);
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

