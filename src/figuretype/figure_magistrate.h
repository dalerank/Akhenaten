#pragma once

#include "figuretype/figure_law_walker.h"

class figure_magistrate : public figure_law_walker {
public:
    FIGURE_METAINFO(FIGURE_MAGISTRATE, figure_magistrate)
    figure_magistrate(figure* f) : figure_law_walker(f) {}

    struct static_params : public figure_static_params {
        int home_road_radius;
        int crime_reduction;
    } FIGURE_STATIC_DATA_T;

    virtual int provide_service() override;

protected:
    virtual int home_road_radius() const override { return current_params().home_road_radius; }
};
ANK_CONFIG_STRUCT(figure_magistrate::static_params, home_road_radius, crime_reduction)
