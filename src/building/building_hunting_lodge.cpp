#include "building_hunting_lodge.h"

#include "building/model.h"
#include "core/direction.h"
#include "city/object_info.h"
#include "city/city.h"
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

buildings::model_t<building_hunting_lodge> hunting_lodge_m;

void building_hunting_lodge::on_create(int orientation) {
    base.labor_category = hunting_lodge_m.labor_category;
}


int building_hunting_lodge::spawn_timer() {
    int pct_workers = worker_percentage();
    if (pct_workers >= 100) {
        return 1;
    } else if (pct_workers >= 75) {
        return 5;
    } else if (pct_workers >= 50) {
        return 10;
    } else if (pct_workers >= 25) {
        return 15;
    } else if (pct_workers >= 1) {
        return 30;
    } else {
        return -1;
    }
}


bool building_hunting_lodge::can_spawn_ostrich_hunter() { // no cache because fuck the system (also I can't find the memory offset for this)
    if (has_figure_of_type(BUILDING_SLOT_HUNTER, FIGURE_OSTRICH_HUNTER)) {
        return false;
    }

    return (base.stored_amount_first < 500);
}

void building_hunting_lodge::spawn_figure() {
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

    if (can_spawn_ostrich_hunter()) {
        base.figure_spawn_delay = 10;
        figure* f = create_figure_generic(FIGURE_OSTRICH_HUNTER, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
        base.set_figure(BUILDING_SLOT_HUNTER, f);
    }

    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
        base.figure_spawn_delay = 10;
    }
}

bool building_hunting_lodge::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim("gamemeat");
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

void building_hunting_lodge::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_hunting_lodge::can_play_animation() const {
    return (worker_percentage() > 50);
}
