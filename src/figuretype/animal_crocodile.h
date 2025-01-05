#pragma once

#include "figure_animal.h"

class figure_crocodile : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CROCODILE, figure_crocodile)
    figure_crocodile(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
};