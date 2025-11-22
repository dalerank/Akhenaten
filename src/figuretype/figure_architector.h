#pragma once

#include "figure/figure.h"

enum e_architector_action {
    ACTION_60_ENGINEER_CREATED = 60,
    ACTION_61_ENGINEER_ENTERING_EXITING = 61,
    ACTION_62_ENGINEER_ROAMING = 62,
    ACTION_63_ENGINEER_RETURNING = 63,
};

class figure_architector : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ARCHITECT, figure_architector)
    figure_architector(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int max_service_buildings;
    } FIGURE_STATIC_DATA_T;

    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DAMAGE; }
    virtual void on_action_changed(int saved_action) override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};
ANK_CONFIG_STRUCT(figure_architector::static_params,
    max_service_buildings)