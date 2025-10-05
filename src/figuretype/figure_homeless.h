#pragma once

#include "figure/figure.h"

struct event_create_homeless { tile2i tile; int num_people; pcstr location; };

class figure_homeless : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HOMELESS, figure_homeless)
    figure_homeless(figure *f) : figure_impl(f) {}
    virtual figure_homeless *dcast_homeless() override { return this; }

    struct static_params : public figure_model {
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint16_t adv_home_building_id;
        uint8_t migrant_num_people;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual figure_phrase_t phrase() const override { return {FIGURE_HOMELESS, "homeless"}; }
    virtual void debug_draw() override;
    virtual bool is_home(const building *b) const override { 
        return (base.home_building_id > 0) && 
            (base.home_building_id == b->id || runtime_data().adv_home_building_id == b->id); 
    }

    int find_closest_house_with_room(tile2i tile);
};
