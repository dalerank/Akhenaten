#include "building_tax_collector.h"

#include "building/building.h"
#include "core/object_property.h"
#include "city/object_info.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "city/city_finance.h"
#include "graphics/window.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "widget/city/ornaments.h"
#include "figuretype/figure_tax_collector.h"
#include "figuretype/figure_cartpusher.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector_up);

void building_tax_collector::spawn_figure() {
    if (!has_road_access()) {
        return;
    }

    check_labor_problem();
    if (has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_TAX_COLLECTOR)) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    int pct_workers = worker_percentage();
    int spawn_delay;
    if (pct_workers >= 100) {
        spawn_delay = 0;
    } else if (pct_workers >= 75) {
        spawn_delay = 1;
    } else if (pct_workers >= 50) {
        spawn_delay = 3;
    } else if (pct_workers >= 25) {
        spawn_delay = 7;
    } else if (pct_workers >= 1) {
        spawn_delay = 15;
    } else {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;
        create_roaming_figure(FIGURE_TAX_COLLECTOR, (e_figure_action)ACTION_40_TAX_COLLECTOR_CREATED, BUILDING_SLOT_SERVICE);
    }
}

void building_tax_collector::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, &d.tax_income_or_storage);
}

void building_tax_collector::update_month() {
    if (!game_features::gameplay_change_new_tax_collection_system) {
        return;
    }

    if (base.has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return;
    }

    if (base.has_road_access && base.deben_storage > 100) {
        int may_send = std::min<int>((base.deben_storage / 100) * 100, 400);
        figure *f = base.create_cartpusher(RESOURCE_GOLD, may_send, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
        base.deben_storage -= may_send;
        f->sender_building_id = base.id;
    }
}

void building_tax_collector::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bvariant building_tax_collector::get_property(const xstring &domain, const xstring &name) const {
    auto &d = runtime_data();
    if (domain == tags().building && name == tags().tax_income_or_storage) {
        return bvariant(d.tax_income_or_storage);
    }

    return building_impl::get_property(domain, name);
}