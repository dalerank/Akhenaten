#pragma once

#include "figure_animal.h"

enum e_crocodile_action : uint16_t {
    ACTION_9_CROCODILE_CHASE_PREY = 9,
    ACTION_10_CROCODILE_MOVING = 10,
    ACTION_11_CROCODILE_BACK_TO_RIVER = 11,
    ACTION_12_CROCODILE_INVESTIGATE = 12,
    ACTION_18_CROCODILE_EATING = 18,
    ACTION_19_CROCODILE_IDLE = 19,
    ACTION_20_CROCODILE_ATTACK = 20,
    ACTION_21_CROCODILE_SUCCESS_KILL = 21,
    ACTION_24_CROCODILE_CREATED = 24,
    ACTION_25_CROCODILE_LOOKING_FOR_ATTACK = 25,
    ACTION_26_CROCODILE_GOING_TO_RIVER = 26,
    ACTION_27_CROCODILE_IDLE_FULL = 27,
};

class figure_crocodile : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CROCODILE, figure_crocodile)
    figure_crocodile(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint16_t max_hungry;
        uint16_t max_hunting_distance;
        uint8_t chase_speed_mult;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short hungry;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
    virtual void update_day() override;
};
ANK_CONFIG_STRUCT(figure_crocodile::static_params, 
    max_hungry, max_hunting_distance, chase_speed_mult)