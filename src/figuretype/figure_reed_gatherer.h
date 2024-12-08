#pragma once

#include "figure/figure.h"

class figure_reed_gatherer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_REED_GATHERER, figure_reed_gatherer)
    figure_reed_gatherer(figure *f) : figure_impl(f) {}

    struct static_params : public figures::model_t<figure_reed_gatherer> {
        int max_amount;

        virtual void load(archive arch) override;
    };

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_REED_GATHERER, "reed"}; }
    virtual void update_animation() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};
