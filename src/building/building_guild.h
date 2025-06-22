#pragma once

#include "building/building.h"

class building_guild : public building_impl {
public:
    building_guild(building &b) : building_impl(b) {}
    virtual building_guild *dcast_guild() override { return this; }

    struct runtime_data_t {
        uint16_t progress; // Progress of the building's construction or upgrade
        uint16_t progress_max;
        uint8_t max_workers;
    } BUILDING_RUNTIME_DATA(runtime_data_t);

    virtual void on_create(int orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;

    virtual int progress() const { return runtime_data().progress; }
    virtual int progress_max() const { return runtime_data().progress_max; }

    bool has_resources() const;
};