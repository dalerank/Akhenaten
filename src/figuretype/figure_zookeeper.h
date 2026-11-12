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
    virtual short ferry_wait_action() const override { return ACTION_9_ENTERTAINER_WAIT_FOR_FERRY; }
    virtual short ferry_ride_action() const override { return ACTION_8_ENTERTAINER_ON_FERRY; }
};
