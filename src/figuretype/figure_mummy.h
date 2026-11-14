#pragma once

#include "figure/figure.h"

enum e_mummy_action : uint16_t {
    ACTION_0_MUMMY_CREATED = 0,
    ACTION_1_MUMMY_ROAMING = 1,

    ACTION_2_MUMMY_MAX
};
using e_mummy_action_tokens_t = token_holder<e_mummy_action, ACTION_0_MUMMY_CREATED, ACTION_2_MUMMY_MAX>;
extern const e_mummy_action_tokens_t e_mummy_action_tokens;

// OG city_disasters.c city_mummies_start + figure/plagues.c figure_mummy_action.
class figure_mummy : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MUMMY, figure_mummy)
    figure_mummy(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t road_radius;
        uint8_t roam_min;
        uint8_t roam_spread;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t step;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override {}
    virtual void update_animation() override;
    virtual void acquire_attack() override;

    static bool is_source_building(building& b);
    // OG city_mummies_start: one mummy from a random source building; amount caps the risen ones.
    static figure* start_plague(int amount);
};
ANK_CONFIG_STRUCT(figure_mummy::static_params, road_radius, roam_min, roam_spread)
