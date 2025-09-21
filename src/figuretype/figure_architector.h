#pragma once

#include "figure/figure.h"

class figure_architector : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ARCHITECT, figure_architector)
    figure_architector(figure *f) : figure_impl(f) {}

    struct static_params : public figures::model_t<figure_architector> {
        int max_service_buildings;
        virtual void archive_load(archive arch) override;
    } FIGURE_STATIC_DATA_T;

    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_ARCHITECT, "engineer"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DAMAGE; }
    virtual void on_action_changed(int saved_action) override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};