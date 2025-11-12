#pragma once

#include "figure/figure.h"

enum e_entertainer_action {
    ACTION_13_ENTERTAINER_RETURNING_EMPTY = 13,
    ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED = 90,
    ACTION_91_ENTERTAINER_EXITING_SCHOOL = 91,
    ACTION_92_ENTERTAINER_GOING_TO_VENUE = 92,
    ACTION_93_ENTERTAINER_GOING_TO_RANDOM_ROAD = 93,
    ACTION_94_ENTERTAINER_ROAMING = 94,
    ACTION_95_ENTERTAINER_RETURNING = 95,
};

class figure_entertainer : public figure_impl {
public:
    figure_entertainer(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_shows() = 0;
    virtual svector<e_building_type, 4> allow_venue_types() const = 0;
    virtual building *current_destination();
    virtual void update_animation() override;

    int provide_entertainment(int shows, void (*callback)(building *, int));
     
    static int determine_venue_destination(tile2i tile, e_figure_type ftype, const svector<e_building_type, 4> &btypes);
    static int determine_closest_venue_destination(tile2i tile, const svector<e_building_type, 4> &btypes);
};