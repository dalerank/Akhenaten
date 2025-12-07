#include "building_clay_pit.h"

#include "building/building.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "widget/city/ornaments.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_clay_pit);

int building_clay_pit::get_fire_risk(int value) const {
    if (!!game_features::gameplay_change_fire_risk_clay_pit_reduced) {
        return value / 2;
    }

    return value;
}

void building_clay_pit::on_before_flooded() {
    building_industry::on_before_flooded();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

