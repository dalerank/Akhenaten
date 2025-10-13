#pragma once

#include "figure/figure.h"

enum e_carpenter_action : uint16_t {
    FIGURE_ACTION_10_CARPENTER_CREATED = 10,
    FIGURE_ACTION_11_CARPENTER_GOING = 11,
    FIGURE_ACTION_14_CARPENTER_WORK_GROUND = 14,
    FIGURE_ACTION_15_CARPENTER_WORK_VERT = 15,
    FIGURE_ACTION_16_CARPENTER_RETURN_HOME = 16,
    FIGURE_ACTION_17_CARPENTER_LOOKING_FOR_WORK_TILE = 17,
    FIGURE_ACTION_18_CARPENTER_RANDOM_TILE = 18,
    FIGURE_ACTION_20_CARPENTER_DESTROY = 20,
    FIGURE_ACTION_30_CARPENTER_CREATED_ROAMING = 30,
    FIGURE_ACTION_31_CARPENTER_GOING_TO_GARDEN = 31,
};

class figure_carpenter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CARPENTER, figure_carpenter)
    figure_carpenter(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    //virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_CARPENTER, "carpenter" }; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    //virtual bool is_common_roaming() override { return false; }
    //virtual sound_key phrase_key() const override;
};