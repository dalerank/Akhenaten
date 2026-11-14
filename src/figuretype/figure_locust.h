#pragma once

#include "figure/figure.h"

enum e_locust_action {
    ACTION_120_LOCUST_CREATED = 120,
    ACTION_121_LOCUST_GOING_TO_FIELD = 121,
    ACTION_122_LOCUST_EATING = 122,
    ACTION_123_LOCUST_FLYING_OFF = 123,
};

// OG city/locusts.c + figure/plagues.c figure_locust_action. SprMain2 bmp "locust" g30–34 — non-8-dir strips.
class figure_locust : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LOCUST, figure_locust)
    figure_locust(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int32_t countdown_after_plague;
        int32_t countdown_fly_off;
        uint8_t months_before_flood;
        uint8_t locusts_per_farm;
        uint8_t square_side;
        uint16_t max_start_delay;
        uint8_t happiness_loss;
        uint8_t float_height;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        building_id farm_id;
        uint8_t cloud_variant; // 0..4 → SprMain2 groups 30..34
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override {}
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

    // OG city_locusts_start: the swarm waits for the flood.
    static void start_plague();
    // OG city_locusts_update, after the month is advanced (month may be 12).
    static void update_month(int month);
};
ANK_CONFIG_STRUCT(figure_locust::static_params, countdown_after_plague, countdown_fly_off, months_before_flood,
  locusts_per_farm, square_side, max_start_delay, happiness_loss, float_height)
