#pragma once

#include "figure_animal.h"

enum e_hyena_action : uint16_t {
    ACTION_8_HYENA_RECALCULATE = 8,
    ACTION_9_HYENA_CHASE_PREY = 9,
    ACTION_10_HYENA_MOVING = 10,
    ACTION_12_HYENA_INVESTIGATE = 12,
    ACTION_18_HYENA_EATING = 18,
    ACTION_19_HYENA_IDLE = 19,
    ACTION_20_HYENA_ATTACK = 20,
    ACTION_21_HYENA_SUCCESS_KILL = 21,
    ACTION_22_HYENA_RUN_TO_CARRION = 22,
    ACTION_23_HYENA_EAT_OTHER_FOOD = 23,
    ACTION_24_HYENA_CREATED = 24,
    ACTION_25_HYENA_LOOKING_FOR_ATTACK = 25,
    ACTION_26_HYENA_AT_REST = 26,
};

class figure_hyena : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_HYENA, figure_hyena)
    figure_hyena(figure *f) : figure_animal(f) {}

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
ANK_CONFIG_STRUCT(figure_hyena::static_params,
    max_hungry, max_hunting_distance, chase_speed_mult)

int figure_combat_get_target_for_hyena(tile2i tile, int max_distance);