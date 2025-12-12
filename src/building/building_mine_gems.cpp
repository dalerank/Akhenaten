#include "building_mine_gems.h"

#include "building/building.h"
#include "grid/gems.h"
#include "grid/grid.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "game/resource.h"
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_gems);

int building_mine_gems::produce_uptick_per_day() const {
    if (base.num_workers <= 0) {
        return 0;
    }
    
    const auto &params = current_params();
    int divider = std::max<int>(1, params.production_divider);
    
    int production = base.num_workers / divider;
    return std::max<int>(1, production);
}

void building_mine_gems::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
        int resource = map_get_gems(t);
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
        map_gems_deplete(best_tile, delta_progress);
    }
}

void building_mine_gems::on_before_collapse() {
    building_mine::on_before_collapse();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

bool building_mine_gems::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceil((float)stored_amount(RESOURCE_GEMS) / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().gems);
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

