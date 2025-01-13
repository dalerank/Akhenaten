#pragma once

#include "figure/figure.h"

class figure_standard_bearer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_STANDARD_BEARER, figure_standard_bearer)
    figure_standard_bearer(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_draw(painter &ctx, vec2i pixel, int hightlight, vec2i *coord_out) override;
    virtual void before_poof() override;
    virtual void main_update_image() override;
    virtual void update_animation() override;
    virtual void on_config_reload() override;
    virtual void on_update_home() override;
    virtual void on_post_load() override;

    void setup_flag_animation();
};