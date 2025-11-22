#pragma once

#include "figure/figure.h"

enum e_bricklayer_action{
    ACTION_10_BRICKLAYER_CREATED = 10,
    ACTION_11_BRICKLAYER_GOING = 11,
    ACTION_12_BRICKLAYER_GOING_TO_PLACE = 12,
    ACTION_13_BRICKLAYER_WAITING_RESOURCES = 13,
    ACTION_14_BRICKLAYER_LAY_BRICKS = 14,
    ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE = 15,
    ACTION_16_BRICKLAYER_RETURN_HOME = 16,
    ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT = 17,
    ACTION_18_BRICKLAYER_RANDOM_TILE = 18,
    ACTION_20_BRICKLAYER_DESTROY = 20,
    ACTION_30_BRICKLAYER_CREATED_ROAMING = 30,
    ACTION_31_BRICKLAYER_GOING_TO_STATUE = 31,
    ACTION_14_BRICKLAYER_WORK_STATUE = 32,
};

class figure_bricklayer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BRICKLAYER, figure_bricklayer)
    figure_bricklayer(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    //virtual bool is_common_roaming() override { return false; }
    virtual sound_key phrase_key() const override;
};