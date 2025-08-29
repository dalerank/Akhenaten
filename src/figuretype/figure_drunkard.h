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

    struct static_params : public figures::model_t<figure_drunkard> {
        virtual void load(archive arch) override;
    };

    short ticks_moved = 0;

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_REED_GATHERER, "reed"}; }
    virtual void update_animation() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};
