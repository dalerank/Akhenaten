#pragma once

#include "figure/figure.h"

enum e_fireman_action {
    ACTION_0_FIREMAN_CREATED = 0,
    ACTION_1_FIREMAN_ENTERING_EXITING = 1,
    ACTION_2_FIREMAN_ROAMING = 2,
    ACTION_3_FIREMAN_RETURNING = 3,
    ACTION_4_FIREMAN_GOING_TO_FIRE = 4,
    ACTION_5_FIREMAN_AT_FIRE = 5,
    ACTION_6_FIREMAN_GOING_TO_ENEMY = 6,
    ACTION_7_FIREMAN_AT_ENEMY = 7,

    ACTION_8_FIREMAN_MAX
};
using figure_fireman_action_tokens_t = token_holder<e_fireman_action, ACTION_0_FIREMAN_CREATED, ACTION_8_FIREMAN_MAX>;
extern const figure_fireman_action_tokens_t figure_fireman_action_tokens;

class figure_fireman : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FIREMAN, figure_fireman)
    figure_fireman(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int fire_detection_distance;
    } FIGURE_STATIC_DATA_T;

    virtual figure_fireman *dcast_fireman() override { return this; }

    virtual void on_create() override;
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual int provide_service() override;
    virtual void update_animation() override;

    void extinguish_fire();
    bool fight_fire();
};
ANK_CONFIG_STRUCT(figure_fireman::static_params,
    fire_detection_distance)
