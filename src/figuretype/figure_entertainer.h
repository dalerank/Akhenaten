#pragma once

#include "figure/figure.h"

enum e_entertainer_action : uint16_t {
    ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED = 0,
    ACTION_1_ENTERTAINER_EXITING_SCHOOL = 1,
    ACTION_2_ENTERTAINER_GOING_TO_VENUE = 2,
    ACTION_3_ENTERTAINER_GOING_TO_RANDOM_ROAD = 3,
    ACTION_4_ENTERTAINER_ROAMING = 4,
    ACTION_5_ENTERTAINER_RETURNING = 5,
    ACTION_6_ENTERTAINER_GOING_TO_SQUARE = 6,
    ACTION_7_ENTERTAINER_RETURNING_EMPTY = 7,

    ACTION_8_ENTERTAINER_MAX
};
using e_entertainer_action_tokens_t = token_holder<e_entertainer_action, ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED, ACTION_8_ENTERTAINER_MAX>;
extern const e_entertainer_action_tokens_t e_entertainer_action_tokens;

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