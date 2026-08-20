#include "building_hunting_lodge.h"

#include "core/direction.h"
#include "city/object_info.h"
#include "city/city.h"
#include "city/city_animals.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "figure/figure.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_hunting_lodge);

void building_hunting_lodge::on_create(int orientation) {
    base.labor_category = current_params().labor_category;
}

int building_hunting_lodge::spawn_timer() {
    const auto &params = current_params();
    int pct_workers = worker_percentage();

    if (pct_workers >= 100) {
        return params.spawn_delay_100_percent.get();
    } else if (pct_workers >= 75) {
        return params.spawn_delay_75_percent.get();
    } else if (pct_workers >= 50) {
        return params.spawn_delay_50_percent.get();
    } else if (pct_workers >= 25) {
        return params.spawn_delay_25_percent.get();
    } else if (pct_workers >= 1) {
        return params.spawn_delay_default.get();
    } else {
        return -1;
    }
}

e_figure_type building_hunting_lodge::resolve_hunter_type() const {
    const e_figure_type override_type = current_params().hunter_type;
    if (override_type == FIGURE_OSTRICH_HUNTER || override_type == FIGURE_ANTELOPE_HUNTER
        || override_type == FIGURE_BIRDS_HUNTER) {
        return override_type;
    }
    return hunting_lodge_default_hunter_type();
}

int building_hunting_lodge::active_hunters_count() const {
    return base.get_figures_number(FIGURE_OSTRICH_HUNTER)
        + base.get_figures_number(FIGURE_ANTELOPE_HUNTER)
        + base.get_figures_number(FIGURE_BIRDS_HUNTER);
}

bool building_hunting_lodge::can_spawn_hunter() {
    if (stored_amount(RESOURCE_GAMEMEAT) >= 500) {
        return false;
    }

    const int max_hunters = current_params().max_hunters.get();
    if (max_hunters <= 0) {
        return false;
    }

    return active_hunters_count() < max_hunters;
}

void building_hunting_lodge::spawn_figure() {
    if (g_city.resource.is_mothballed(RESOURCE_GAMEMEAT)) {
        return;
    }

    check_labor_problem();

    if (!base.has_road_access) {
        return;
    }

    if (base.num_workers < base.max_workers) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
    }

    int spawn_delay = spawn_timer();
    if (spawn_delay == -1) { // no workers
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay < spawn_delay) {
        return;
    }

    if (can_spawn_hunter()) {
        base.figure_spawn_delay = 0;
        create_figure_generic(resolve_hunter_type(), ACTION_8_RECALCULATE, BUILDING_SLOT_HUNTER, DIR_4_BOTTOM_LEFT);
    }

    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
        base.figure_spawn_delay = 0;
    }
}
