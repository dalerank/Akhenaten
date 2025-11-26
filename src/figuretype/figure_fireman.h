#pragma once

#include "figure/figure.h"

enum e_fireman_action {
    ACTION_70_FIREMAN_CREATED = 70,
    ACTION_71_FIREMAN_ENTERING_EXITING = 71,
    ACTION_72_FIREMAN_ROAMING = 72,
    ACTION_73_FIREMAN_RETURNING = 73,
    ACTION_74_FIREMAN_GOING_TO_FIRE = 74,
    ACTION_75_FIREMAN_AT_FIRE = 75,
    ACTION_76_FIREMAN_GOING_TO_ENEMY = 76,
    ACTION_77_FIREMAN_AT_ENEMY = 77,
};

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
    virtual e_overlay get_overlay() const override { return OVERLAY_WATER; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual void update_animation() override;

    void extinguish_fire();
    bool fight_fire();
};
ANK_CONFIG_STRUCT(figure_fireman::static_params,
    fire_detection_distance)
