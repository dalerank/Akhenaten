#pragma once

#include "figure/figure.h"

struct event_create_homeless { tile2i tile; int num_people; pcstr location; };

enum e_homeless_action {
    ACTION_6_HOMELESS_LEAVING = 6,
    ACTION_7_HOMELESS_CREATED = 7,
    ACTION_8_HOMELESS_GOING_TO_HOUSE = 8,
    ACTION_9_HOMELESS_ENTERING_HOUSE = 9,
    ACTION_10_HOMELESS_ENTERING_HOUSE = 10,
};

class figure_homeless : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HOMELESS, figure_homeless)
    figure_homeless(figure *f) : figure_impl(f) {}
    virtual figure_homeless *dcast_homeless() override { return this; }

    struct runtime_data_t {
        uint16_t adv_home_building_id;
        uint8_t migrant_num_people;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual void debug_draw() override;
    virtual bool is_home(const building *b) const override { 
        return (base.home_building_id > 0) && 
            (base.home_building_id == b->id || runtime_data().adv_home_building_id == b->id); 
    }

    virtual sound_key phrase_key() const override;

    int find_closest_house_with_room(tile2i tile);
};
