#pragma once

#include "building/building.h"

class building_industry : public building_impl {
public:
    building_industry(building &b) : building_impl(b) {}
    virtual building_industry *dcast_industry() override { return this; }

    struct runtime_data_t {
        short ready_production;
        short progress;
        short progress_max;
        bool spawned_worker_this_month;
        uint8_t max_gatheres;
        int unk_b[10];
        uint8_t unk_c[13];
        uint8_t produce_multiplier;
        bool has_raw_materials;
        int unk_6[5];
        short reserved_id_13;
        int unk_40[40];
        int unk_12[10];
        e_figure_type processed_figure;
    };

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual void on_create(int orientation) override;
    virtual int progress() const { return runtime_data().progress; }
    virtual int progress_max() const { return runtime_data().progress_max; }
    virtual bool stored_amount(e_resource) const override;
    virtual void start_production() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;

    runtime_data_t &runtime_data() { return *(runtime_data_t *)data.data; }
    const runtime_data_t &runtime_data() const { return *(runtime_data_t *)data.data; }
};