#include "figure/figure.h"

class figure_fishing_point : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FISHING_POINT, figure_fishing_point)
    figure_fishing_point(figure *f) : figure_impl(f) {}

    virtual figure_fishing_point *dcast_fishing_point() override { return this; }

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override;
    virtual void main_update_image() override;
    static figure *create(tile2i tile);
};