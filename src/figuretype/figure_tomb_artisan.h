#pragma once

#include "figure/figure.h"

enum e_tomb_artisan_action {
    ACTION_10_TOMB_ARTISAN_CREATED = 10,
    ACTION_11_TOMB_ARTISAN_GOING = 11,
    ACTION_14_TOMB_ARTISAN_WORK = 14,
    ACTION_16_TOMB_ARTISAN_RETURN_HOME = 16,
    ACTION_20_TOMB_ARTISAN_DESTROY = 20,
};

class figure_tomb_artisan : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TOMB_ARTISAN, figure_tomb_artisan)
    figure_tomb_artisan(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        building_id destination_bid;
        uint8_t delivered_materials = 0; // clay+paint handed to monument on WORK
        uint8_t delivered_phase = 0xff;  // re-deliver if tomb phase advances while on-site
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
};
