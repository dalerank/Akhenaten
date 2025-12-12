#pragma once

#include "building/building.h"

class building_industry : public building_impl {
public:
    building_industry(building &b) : building_impl(b) {}
    virtual building_industry *dcast_industry() override { return this; }

    struct runtime_data_t : public no_copy_assignment {
        short progress;
        short progress_max;
        bool spawned_worker_this_month;
        uint8_t max_gatheres;
        uint8_t water_stored;
        uint8_t unk_b[9];
        uint8_t unk_c[13];
        uint8_t produce_multiplier;
        //bool has_raw_materials;
        uint8_t unk_6[5];
        short reserved_id_13;
        uint8_t unk_40[40];
        uint8_t unk_12[10];
        e_figure_type processed_figure;
    } BUILDING_RUNTIME_DATA_T;

    virtual int produce_uptick_per_day() const { return base.num_workers; }

    virtual void update_preproduction() { /*do nothing*/ }
    virtual void update_production();
    virtual void production_started() { /*do nothing*/ }
    virtual void production_finished() { /*do nothing*/ }
    
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual void on_create(int orientation) override;
    virtual int progress() const { return runtime_data().progress; }
    virtual int progress_max() const { return runtime_data().progress_max; }
    virtual int stored_amount(e_resource) const override;
    virtual void start_production() override;
    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual void update_day() override;
    virtual bool can_play_animation() const override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;

    virtual void debug_draw_properties() override;
};