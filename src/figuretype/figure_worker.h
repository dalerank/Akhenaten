#pragma once

#include "building/monument_pyramid_figure.h"
#include "figure/figure.h"

enum e_worker_action {
    ACTION_9_WORKER_CREATED = 9,
    ACTION_10_WORKER_GOING = 10,
    ACTION_11_WORKER_GOING_TO_PLACE = 11,
    ACTION_12_WORKER_LEVELING_GROUND = 12,
    ACTION_13_WORKER_BACK_FROM_WORKS = 13,
    ACTION_14_WORKER_CHECK_DESTINATION = 14,
    ACTION_15_REACHED_DESTINATION = 15,
    ACTION_16_WORKER_TO_YARD = 16,
    ACTION_17_WORKER_TO_MASON = 17,
    ACTION_18_WORKER_DELIVER_BLOCK = 18,
    // OG laborer ramp climb → layer walk to waiting mason.
    ACTION_19_WORKER_CLIMB_RAMP = 19,
    ACTION_20_WORKER_TO_MASON_ON_LAYER = 20,
    ACTION_21_WORKER_WALK_TO_MASON = 21,
};

class figure_worker : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LABORER, figure_worker)

    figure_worker(figure *f) : figure_impl(f) {}
    virtual figure_worker *dcast_worker() override { return this; }

    struct runtime_data_t {
        figure_id mason_fid;
        uint8_t delivering_block;
        uint8_t walk_mode;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void poof() override;

    tile2i monumen_tile4work(building *b);
    void assign_brick_delivery(building *monument, figure_id mason_fid);

private:
    bool uses_ramp_climb(building *monument) const;
    tile2i ramp_entry_tile(building *monument) const;
};
