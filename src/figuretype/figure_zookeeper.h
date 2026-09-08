#pragma once

#include "figuretype/figure_entertainer.h"

class figure_zookeeper : public figure_entertainer {
public:
    FIGURE_METAINFO(FIGURE_ZOOKEEPER, figure_zookeeper)
    figure_zookeeper(figure *f) : figure_entertainer(f) {}

    virtual void on_create() override {}
    virtual void update_shows() override;
    virtual svector<e_building_type, 4> allow_venue_types() const override { return {BUILDING_ZOO}; }
    virtual int provide_service() override;
};
