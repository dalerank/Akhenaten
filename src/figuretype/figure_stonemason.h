#pragma once

#include "building/monument_pyramid_figure.h"
#include "figure/figure.h"

enum e_stonemason_action : uint16_t {
    ACTION_0_MASON_CREATED = 0,
    ACTION_1_MASON_GOING = 1,
    ACTION_2_MASON_GOING_TO_PLACE = 2,
    ACTION_3_MASON_WAITING_RESOURCES = 3,
    ACTION_4_MASON_WORK_GROUND = 4,
    ACTION_5_MASON_WORK_WALL = 5,
    ACTION_6_MASON_RETURN_HOME = 6,
    ACTION_7_MASON_LOOKING_FOR_WORK_TILE = 7,
    ACTION_8_MASON_RANDOM_TILE = 8,
    ACTION_9_MASON_WORK_OBELISK = 9,
    ACTION_10_MASON_DESTROY = 10,
    ACTION_11_MASON_CREATED_ROAMING = 11,
    ACTION_12_MASON_GOING_TO_STATUE = 12,
    ACTION_13_MASON_WORK_STATUE_GROUND = 13,
    ACTION_14_MASON_WORK_STATUE_WALL = 14,

    // OG pyramid climb / casing path (bricklayer-analogue).
    ACTION_16_MASON_CLIMB_RAMP = 16,
    ACTION_17_MASON_FIND_PART = 17,
    ACTION_18_MASON_WALK_TO_PART = 18,
    ACTION_19_MASON_WAIT_FOR_BLOCK = 19,
    ACTION_20_MASON_NEXT_CASING = 20,
    ACTION_21_MASON_PYRAMID_WORK = 21,

    ACTION_22_MASON_MAX
};
using figure_stonemason_action_tokens_t = token_holder<e_stonemason_action, ACTION_0_MASON_CREATED, ACTION_22_MASON_MAX>;
extern const figure_stonemason_action_tokens_t figure_stonemason_action_tokens;

class figure_stonemason : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_STONEMASON, figure_stonemason)
    figure_stonemason(figure *f) : figure_impl(f) {}
    virtual figure_stonemason *dcast_stonemason() override { return this; }

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
        building_id part_bid;
        uint8_t walk_mode;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
};
