#pragma once

#include "figure/figure.h"

class figure_drunkard : public figure_impl {
public:
    enum {
        ACTION_9_DRUNKARD_GOTO_SENET_HOUSE = 9,
        ACTION_10_DRUNKARD_WOMIT = 10,
        ACTION_11_DRUNKARD_RETURN_HOME = 11,
        ACTION_12_DRUNKARD_CREATED_SOBER = 12,
        ACTION_13_DRUNKARD_ENTER_SENET_HOUSE = 13,
        ACTION_14_DRUNKARD_CREATED = 14,
    };

    FIGURE_METAINFO(FIGURE_DRUNKARD, figure_drunkard)
    figure_drunkard(figure *f) : figure_impl(f) {}

    struct static_params : public figure_model {
        uint16_t womit_delay;
        uint16_t walk_delay;
        virtual void archive_load(archive arch) override;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short moved_ticks;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_REED_GATHERER, "reed"}; }
    virtual void update_animation() override;
};
