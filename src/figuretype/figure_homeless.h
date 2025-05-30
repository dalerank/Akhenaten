#pragma once

#include "figure/figure.h"

struct event_create_homeless { tile2i tile; int num_people; pcstr location; };

class figure_homeless : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HOMELESS, figure_homeless)
    figure_homeless(figure *f) : figure_impl(f) {}

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual figure_phrase_t phrase() const override { return {FIGURE_HOMELESS, "homeless"}; }

    int find_closest_house_with_room(tile2i tile);
};
