#pragma once

#include "building/building.h"

class building_tax_collector : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_TAX_COLLECTOR, building_tax_collector, building_impl)

    virtual building_tax_collector *dcast_tax_collector() override { return this; }

    struct runtime_data_t {
        int16_t tax_income_or_storage;
    } BUILDING_RUNTIME_DATA_T;

    struct static_params : public building_model {
        uint16_t max_deben_storage;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_TAX_INCOME; }
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_TAX_COLLECTOR; }
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int16_t deben_storage() const { return base.deben_storage; }
    int16_t tax_storage() const { return runtime_data().tax_income_or_storage; }
};
ANK_CONFIG_STRUCT(building_tax_collector::static_params, max_deben_storage)

class building_tax_collector_up : public building_tax_collector {
public:
    BUILDING_METAINFO(BUILDING_TAX_COLLECTOR_UPGRADED, building_tax_collector_up, building_tax_collector)
};