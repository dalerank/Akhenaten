#pragma once

#include "building/building.h"

class building_tax_collector : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_TAX_COLLECTOR, building_tax_collector, building_impl)

    virtual building_tax_collector *dcast_tax_collector() override { return this; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int16_t deben_storage() const { return base.deben_storage; }
    int16_t tax_storage() const { return base.tax_income_or_storage; }
};

class building_tax_collector_up : public building_tax_collector {
public:
    BUILDING_METAINFO(BUILDING_TAX_COLLECTOR_UPGRADED, building_tax_collector_up, building_tax_collector)
};
