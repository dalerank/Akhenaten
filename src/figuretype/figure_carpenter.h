#pragma once

#include "building/monument_pyramid_figure.h"
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

    struct static_params : public figure_static_params {
        uint16_t ghost_ticks = 10;
        uint16_t task_search_base = 30;
        uint16_t task_search_rand = 30;
        uint8_t guild_road_radius = 2;
        uint16_t mausoleum_head_start = 10;
        uint16_t mausoleum_work_ticks = 50;
        uint16_t pyramid_work_ticks = 30;
        uint16_t climb_ticks = 30;
        uint16_t statue_work_ticks = 100;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
        building_id ramp_part_bid;
        uint8_t serving_statue;
        uint8_t walk_mode;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;

    void assign_monument_task(building *monument);
    void assign_statue_task(building *statue);
    bool try_find_task();
};
ANK_CONFIG_STRUCT(figure_carpenter::static_params,
    ghost_ticks, task_search_base, task_search_rand, guild_road_radius,
    mausoleum_head_start, mausoleum_work_ticks, pyramid_work_ticks, climb_ticks, statue_work_ticks)
