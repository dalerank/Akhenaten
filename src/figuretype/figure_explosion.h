#include "figure/figure.h"

class figure_explosion : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_EXPLOSION, figure_explosion)
    figure_explosion(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void cart_image_update() override {}
    virtual void update_animation() override;
    virtual void main_image_update() override {}
};