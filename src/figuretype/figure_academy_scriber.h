#pragma once

#include "figure/figure.h"

class figure_academy_scriber : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ACADEMY_SCRIBER, figure_academy_scriber)
    figure_academy_scriber(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual int provide_service() override;
};

