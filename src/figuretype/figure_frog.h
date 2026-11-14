#pragma once

#include "figure/figure.h"

enum e_frog_action {
    ACTION_120_FROG_CREATED = 120,
    ACTION_121_FROG_GOING_TO_HOUSE = 121,
    ACTION_122_FROG_ENTERING_HOUSE = 122,
};

// OG city_disasters.c city_frogs_* + figure/animals_wild.c figure_frog_action.
class figure_frog : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FROG, figure_frog)
    figure_frog(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t house_chance;
        uint8_t people_percent;
        uint16_t max_start_delay;
        uint8_t road_radius;
        uint8_t move_chance;
        uint16_t ticks_per_amount;
        uint8_t happiness_loss;
        uint8_t ptah_curse_amount;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        building_id house_id;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override {}
    virtual void update_animation() override;
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

    // OG city_frogs_start.
    static void start_plague(int amount);
    static bool find_water(building& house, tile2i& out);
    static figure* create_at(building& house, tile2i water);
    static void infest_house(building &b);
};
ANK_CONFIG_STRUCT(figure_frog::static_params, house_chance, people_percent, max_start_delay, road_radius, move_chance,
  ticks_per_amount, happiness_loss, ptah_curse_amount)
