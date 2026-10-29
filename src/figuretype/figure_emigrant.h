#pragma once

#include "figure/figure.h"

struct event_create_emigrant {
    building_id bid;
    int num_people;
    pcstr src_location;
};

enum e_emigrant_action : uint16_t {
    ACTION_0_EMIGRANT_CREATED = 0,
    ACTION_1_EMIGRANT_EXITING = 1,
    ACTION_2_EMIGRANT_LEAVING = 2,
};

class figure_emigrant : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_EMIGRANT, figure_emigrant)
    figure_emigrant(figure *f) : figure_impl(f) {}
    virtual figure_emigrant *dcast_emigrant() override { return this; }

    struct runtime_data_t {
        uint8_t migrant_num_people;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual void update_animation() override;
    virtual void debug_show_properties() override;
    virtual void set_cart_offset(int direction) const override;
};
