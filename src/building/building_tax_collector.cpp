#include "building_tax_collector.h"

#include "building/building.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tax_collector_up);

void building_tax_collector::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &base.tax_income_or_storage);
}
