#pragma once

#include "figure/figure.h"

class figure_teacher : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TEACHER, figure_teacher)
    figure_teacher(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual int provide_service() override;
};