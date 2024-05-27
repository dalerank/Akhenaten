#include "figure/figure.h"

class figure_explosion : public figure_impl {
public:
    figure_explosion(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void cart_update_image() override {}
    virtual void update_animation() override;
};