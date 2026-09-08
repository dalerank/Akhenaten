#pragma once

#include "figure/figure.h"

enum e_locust_action {
    ACTION_120_LOCUST_CREATED = 120,
    ACTION_121_LOCUST_ROAMING = 121,
};

// Cleopatra swarm cloud. SprMain2 bmp "locust" g30–34 — non-8-dir strips.
// Farm blight stays in building_curse_farms; this is the visual swarm only.
class figure_locust : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LOCUST, figure_locust)
    figure_locust(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t default_swarm = 8;
        uint8_t max_amount = 16;
        uint16_t swarm_days = 48; // match building_curse_farms(big_curse)
        int8_t happiness_hit = -10; // Major Plagues; Bast malaria uses -5
        uint8_t float_height = 20;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint16_t days_left;
        uint8_t cloud_variant; // 0..4 → SprMain2 groups 30..34
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /* free roam over farms */ }
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual void update_day() override;
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

    // Spawn N cloud figures over farms (or map center). count<=0 → default.
    // Does NOT curse farms — caller runs building_curse_farms / apply_plague. Returns first id, or 0.
    static int spawn_swarm(int count = 0);

    // Farm blight + swarm + happiness + ambient. Messages left to caller.
    static void apply_plague(int swarm_count = 0);
};
ANK_CONFIG_STRUCT(figure_locust::static_params,
    default_swarm, max_amount, swarm_days, happiness_hit, float_height)
