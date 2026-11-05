#pragma once

#include "figure/figure.h"

enum e_carpenter_action : uint16_t {
    ACTION_0_CARPENTER_ROAM = 0,
    ACTION_1_CARPENTER_GO_TO_SITE = 1,
    ACTION_2_CARPENTER_WORK = 2,
    ACTION_3_CARPENTER_RETURN = 3,
    ACTION_4_CARPENTER_CLIMB_RAMP = 4,
    ACTION_5_CARPENTER_GO_TO_GUILD_ROAD = 5,

    ACTION_6_CARPENTER_MAX
};
using figure_carpenter_action_tokens_t = token_holder<e_carpenter_action, ACTION_0_CARPENTER_ROAM, ACTION_6_CARPENTER_MAX>;
extern const figure_carpenter_action_tokens_t figure_carpenter_action_tokens;

class figure_carpenter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CARPENTER, figure_carpenter)
    figure_carpenter(figure *f) : figure_impl(f) {}
    virtual figure_carpenter *dcast_carpenter() override { return this; }

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
        uint8_t serving_statue;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;

    void assign_monument_task(building *monument);
    void assign_statue_task(building *statue);
    bool try_find_task();
};
