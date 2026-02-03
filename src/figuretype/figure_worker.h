#pragma once

#include "figure/figure.h"

enum e_worker_action {
    ACTION_9_WORKER_CREATED = 9,
    ACTION_10_WORKER_GOING = 10,
    ACTION_11_WORKER_GOING_TO_PLACE = 11,
    ACTION_12_WORKER_LEVELING_GROUND = 12,
    ACTION_13_WORKER_BACK_FROM_WORKS = 13,
    ACTION_14_WORKER_CHECK_DESTINATION = 14,
    ACTION_15_REACHED_DESTINATION = 15
};

class figure_worker : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LABORER, figure_worker)
    
    figure_worker(figure *f) : figure_impl(f) {}
    virtual figure_worker *dcast_worker() override { return this; }

    virtual void on_create() override {}
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LABOR; }
    virtual figure_sound_t get_sound_reaction(pcstr key) const;

    tile2i monumen_tile4work(building *b);
};