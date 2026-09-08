#pragma once

#include "figure/figure.h"

class figure_scriber : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SCRIBER, figure_scriber)
    figure_scriber(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual int provide_service() override;
};