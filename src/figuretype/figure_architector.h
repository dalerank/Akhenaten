#pragma once

#include "figure/figure.h"

enum e_architector_action {
    ACTION_0_ENGINEER_NONE = 0,
    ACTION_1_ENGINEER_CREATED = 1,
    ACTION_2_ENGINEER_ENTERING_EXITING = 2,
    ACTION_3_ENGINEER_ROAMING = 3,
    ACTION_4_ENGINEER_RETURNING = 4,

    ACTION_64_ENGINEER_MAX
};
using figure_architector_action_tokens_t = token_holder<e_architector_action, ACTION_0_ENGINEER_NONE, ACTION_64_ENGINEER_MAX>;
extern const figure_architector_action_tokens_t figure_architector_action_tokens;

class figure_architector : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ARCHITECT, figure_architector)
    figure_architector(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int max_service_buildings;
        int effect_radius;
        int risk_reduction_strength;
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
    max_service_buildings, effect_radius, risk_reduction_strength)