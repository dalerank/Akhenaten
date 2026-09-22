#include "building_tax_collector.h"

#include "building/building.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "game/game_config.h"
#include "figuretype/figure_cartpusher.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector_up);

void building_tax_collector::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &base.tax_income_or_storage);
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
        figure *f = create_cartpusher(RESOURCE_GOLD, may_send, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
        base.deben_storage -= may_send;
        f->sender_building_id = base.id;
    }
}
