#pragma once

#include "figure_animal.h"

enum e_crocodile_action : uint16_t {
    ACTION_9_CROCODILE_CHASE_PREY = 9,
    FIGURE_ACTION_10_CROCODILE_MOVING = 10,
    FIGURE_ACTION_11_CROCODILE_BACK_TO_RIVER = 11,
    FIGURE_ACTION_12_CROCODILE_INVESTIGATE = 12,
    FIGURE_ACTION_18_CROCODILE_EATING = 18,
    FIGURE_ACTION_19_CROCODILE_IDLE = 19,
    FIGURE_ACTION_20_CROCODILE_ATTACK = 20,
    FIGURE_ACTION_24_CROCODILE_CREATED = 24,
    FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK = 25,
};

class figure_crocodile : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CROCODILE, figure_crocodile)
    figure_crocodile(figure *f) : figure_impl(f) {}

    struct static_params : public figure_model {
        uint16_t max_hungry;
        uint16_t max_hunting_distance;
        virtual void archive_load(archive arch) override;
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