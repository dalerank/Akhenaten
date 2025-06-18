#pragma once

#include "figure/figure.h"

class figure_ostrich_hunter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH_HUNTER, figure_ostrich_hunter)
    figure_ostrich_hunter(figure *f) : figure_impl(f) {}

    struct static_params : public figure_model {
        virtual void archive_load(archive arch) override;

        int max_hunting_distance;
    };

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    //virtual void poof() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_OSTRICH_HUNTER, "oshunter"}; }
    virtual sound_key phrase_key() const override;
    virtual figure_sound_t get_sound_reaction(pcstr key) const;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
};