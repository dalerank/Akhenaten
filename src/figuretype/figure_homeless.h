#pragma once

#include "figure/figure.h"

struct event_create_homeless { tile2i tile; int num_people; pcstr location; };

enum e_homeless_action {
    ACTION_0_HOMELESS_CREATED = 0,
    ACTION_1_HOMELESS_GOING_TO_HOUSE = 1,
    ACTION_2_HOMELESS_ENTERING_HOUSE = 2,
    ACTION_3_HOMELESS_LEAVING = 3,

    // Pharaoh .sav action ids (OG 0x0048A720)
    LEGACY_HOMELESS_CREATED = 8,
    LEGACY_HOMELESS_GOING_TO_HOUSE = 9,
    LEGACY_HOMELESS_ENTERING_HOUSE = 10,
    LEGACY_HOMELESS_LEAVING = 11,
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
    virtual void debug_draw(painter &ctx) override;
    virtual bool is_home(const building *b) const override {
        return (base.home_building_id > 0) &&
            (base.home_building_id == b->id || runtime_data().adv_home_building_id == b->id);
    }

    int find_closest_house_with_room(tile2i tile);
    bool go_to_house(int house_id);
};
