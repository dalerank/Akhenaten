#pragma once

#include "figure_animal.h"

class figure_hippo : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HIPPO, figure_hippo)
    figure_hippo(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
};