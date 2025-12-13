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

void building_clay_pit::spawn_figure() {
    if (base.destroy_reason == e_destroy_flooded) {
        return;
    }
    
    building_industry::spawn_figure();
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

