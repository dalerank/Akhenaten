#pragma once

#include "figuretype/figure_entertainer.h"

class figure_zookeeper : public figure_entertainer {
public:
    FIGURE_METAINFO(FIGURE_ZOOKEEPER, figure_zookeeper)
    figure_zookeeper(figure* f) : figure_entertainer(f) {}

    struct static_params : public figure_static_params {
        int home_road_radius;
        int venue_walk_ticks;
        int ferry_wait_ticks;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void acquire_attack() override;
    virtual void update_shows() override {}
    virtual svector<e_building_type, 4> allow_venue_types() const override { return {BUILDING_ZOO}; }
    virtual int provide_service() override;
    virtual short ferry_wait_action() const override { return ACTION_9_ENTERTAINER_WAIT_FOR_FERRY; }
    virtual short ferry_ride_action() const override { return ACTION_8_ENTERTAINER_ON_FERRY; }

    tile2i home_road() const;
    building* find_venue();
};
ANK_CONFIG_STRUCT(figure_zookeeper::static_params, home_road_radius, venue_walk_ticks, ferry_wait_ticks)
