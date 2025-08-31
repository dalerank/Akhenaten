#pragma once

#include "figure_animal.h"

enum e_crocodile_action : uint16_t {
    FIGURE_ACTION_10_CROCODILE_MOVING = 10,
    FIGURE_ACTION_19_CROCODILE_EATING = 18,
    FIGURE_ACTION_19_CROCODILE_IDLE = 19,
    FIGURE_ACTION_19_CROCODILE_ATTACK = 20,
    FIGURE_ACTION_24_CROCODILE_CREATED = 24,
    FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK = 25,
    FIGURE_ACTION_150_CROCODILE_ATTACK = 150,
};

class figure_crocodile : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CROCODILE, figure_crocodile)
    figure_crocodile(figure *f) : figure_impl(f) {}

    struct static_params : public figure_model {
        uint16_t max_hungry;
        virtual void archive_load(archive arch) override;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
};