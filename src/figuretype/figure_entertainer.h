#pragma once

#include "figure/figure.h"

class figure_entertainer : public figure_impl {
public:
    figure_entertainer(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_shows() = 0;
    virtual svector<e_building_type, 4> allow_venue_types() const = 0;
    virtual void update_image();
    virtual building *current_destination();

    int provide_entertainment(int shows, void (*callback)(building *, int));
    static void bandstand_coverage(building *b, int shows);
    static void senet_coverage(building *b, int shows);
     
    static int determine_venue_destination(tile2i tile, const svector<e_building_type, 4> &btypes);
    static int determine_closest_venue_destination(tile2i tile, const svector<e_building_type, 4> &btypes);
};