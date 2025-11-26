#pragma once

#include "figure/figure.h"

enum e_carpenter_action : uint16_t {
    ACTION_10_CARPENTER_CREATED = 10,
    ACTION_11_CARPENTER_GOING = 11,
    ACTION_14_CARPENTER_WORK_GROUND = 14,
    ACTION_15_CARPENTER_WORK_VERT = 15,
    ACTION_16_CARPENTER_RETURN_HOME = 16,
    ACTION_17_CARPENTER_LOOKING_FOR_WORK_TILE = 17,
    ACTION_18_CARPENTER_RANDOM_TILE = 18,
    ACTION_20_CARPENTER_DESTROY = 20,
    ACTION_30_CARPENTER_CREATED_ROAMING = 30,
    ACTION_31_CARPENTER_GOING_TO_GARDEN = 31,
};

class figure_carpenter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CARPENTER, figure_carpenter)
    figure_carpenter(figure *f) : figure_impl(f) {}
    virtual figure_carpenter *dcast_carpenter() override { return this; }

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