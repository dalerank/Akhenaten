#pragma once

#include "figure/figure.h"

enum e_carpenter_action : uint16_t {
    ACTION_0_CARPENTER_CREATED = 0,
    ACTION_1_CARPENTER_GOING = 1,
    ACTION_2_CARPENTER_WORK_GROUND = 2,
    ACTION_3_CARPENTER_WORK_VERT = 3,
    ACTION_4_CARPENTER_RETURN_HOME = 4,
    ACTION_5_CARPENTER_LOOKING_FOR_WORK_TILE = 5,
    ACTION_6_CARPENTER_RANDOM_TILE = 6,
    ACTION_7_CARPENTER_DESTROY = 7,
    ACTION_8_CARPENTER_CREATED_ROAMING = 8,
    ACTION_9_CARPENTER_GOING_TO_GARDEN = 9,

    ACTION_10_CARPENTER_MAX
};
using figure_carpenter_action_tokens_t = token_holder<e_carpenter_action, ACTION_0_CARPENTER_CREATED, ACTION_10_CARPENTER_MAX>;
extern const figure_carpenter_action_tokens_t figure_carpenter_action_tokens;

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
    virtual void update_animation() override;
};
