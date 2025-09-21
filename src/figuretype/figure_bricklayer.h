#pragma once

#include "figure/figure.h"

class figure_bricklayer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BRICKLAYER, figure_bricklayer)
    figure_bricklayer(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        short idle_wait_count;
        building_id destination_bid;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_BRICKLAYER, "brick"}; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    //virtual bool is_common_roaming() override { return false; }
    //virtual sound_key phrase_key() const override;
};