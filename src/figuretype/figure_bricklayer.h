#pragma once

#include "building/monument_pyramid_figure.h"
#include "figure/figure.h"

enum e_bricklayer_action : uint16_t {
    ACTION_0_BRICKLAYER_ROAM = 0,
    ACTION_1_BRICKLAYER_GO_TO_SITE = 1,
    ACTION_2_BRICKLAYER_WORK = 2,
    ACTION_3_BRICKLAYER_RETURN_HOME = 3,
    ACTION_4_BRICKLAYER_CLIMB_RAMP = 4,
    ACTION_5_BRICKLAYER_FIND_PART = 5,
    ACTION_6_BRICKLAYER_GO_TO_GUILD_ROAD = 6,
    ACTION_7_BRICKLAYER_WALK_TO_PART = 7,
    ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK = 8,

    ACTION_9_BRICKLAYER_MAX
};
using figure_bricklayer_action_tokens_t = token_holder<e_bricklayer_action, ACTION_0_BRICKLAYER_ROAM, ACTION_9_BRICKLAYER_MAX>;
extern const figure_bricklayer_action_tokens_t figure_bricklayer_action_tokens;

class figure_bricklayer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BRICKLAYER, figure_bricklayer)
    figure_bricklayer(figure *f) : figure_impl(f) {}
    virtual figure_bricklayer *dcast_bricklayer() override { return this; }

    struct static_params : public figure_static_params {
        uint16_t ghost_ticks = 10;
        uint16_t task_search_base = 30;
        uint16_t task_search_rand = 30;
        uint8_t guild_road_radius = 2;
        uint16_t climb_ticks = 30;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        building_id destination_bid;
        building_id part_bid;
        uint8_t serving_statue;
        uint8_t walk_mode;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;

    void assign_monument_task(building_id part_id);
    void assign_statue_task(building *statue);
    bool try_find_task();
};
ANK_CONFIG_STRUCT(figure_bricklayer::static_params,
    ghost_ticks, task_search_base, task_search_rand, guild_road_radius, climb_ticks)
