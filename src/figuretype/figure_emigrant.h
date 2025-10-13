#pragma once

#include "figure/figure.h"

struct event_create_emigrant {
    building_id bid;
    int num_people;
    pcstr src_location;
};

enum e_emigrant_action : uint16_t {
    FIGURE_ACTION_2_EMIGRANT_ARRIVING = 2,
    FIGURE_ACTION_4_EMIGRANT_CREATED = 4,
    FIGURE_ACTION_5_EMIGRANT_EXITING_HOUSE = 5,
    FIGURE_ACTION_6_EMIGRANT_LEAVING = 6,
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
    virtual figure_phrase_t phrase() const override { return {FIGURE_EMIGRANT, "emigrant"}; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual void debug_show_properties() override;
    virtual sound_key phrase_key() const override;
};