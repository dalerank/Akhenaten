#include "figure/figure.h"

enum e_fishing_point_action {
   ACTION_196_FISHPOINT_BUBLES = 196,
   ACTION_197_FISHPOINT_JUMP = 197,
};

class figure_fishing_point : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FISHING_POINT, figure_fishing_point)
    figure_fishing_point(figure *f) : figure_impl(f) {}

    virtual figure_fishing_point *dcast_fishing_point() override { return this; }

    struct runtime_data_t {
        short offset;
        short max_step;
        short current_step;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override;
    virtual void main_image_update() override;
    static figure *create(tile2i tile);
};

class figure_fishing_spot : public figure_fishing_point {
public:
    FIGURE_METAINFO(FIGURE_FISHING_SPOT, figure_fishing_spot)
    figure_fishing_spot(figure *f) : figure_fishing_point(f) {}
};