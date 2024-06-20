#pragma once

#include "animal.h"

class figure_hippo : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HIPPO, figure_hippo)
    figure_hippo(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_animation() override;
};