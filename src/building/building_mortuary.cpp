#include "building_mortuary.h"

#include "building/building_house.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mortuary);

void building_mortuary::spawn_figure() {
    if (base.stored_amount(RESOURCE_LINEN) < 100) {
        return;
    }

    if (common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_SERVICE)) {
        const short spent = std::min<short>(base.stored_amount(RESOURCE_LINEN), 20);
        base.stored_amount_first -= spent;

        create_roaming_figure(FIGURE_EMBALMER, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}

bool building_mortuary::can_play_animation() const {
    if (base.stored_amount(RESOURCE_LINEN) < 100) {
        return false;
    }

    return building_impl::can_play_animation();
}

void building_mortuary::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_mortuary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return false;
}

void building_mortuary::update_count() const {
    g_city.health.add_mortuary_workers(num_workers());
}

