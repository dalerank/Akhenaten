#pragma once

#include "figure/figure.h"

class figure_javelin : public figure_impl {
public:
    figure_javelin(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
};