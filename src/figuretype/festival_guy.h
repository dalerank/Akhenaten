#include "figure/figure.h"

class figure_festival_guy : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_PRIEST, figure_festival_guy)
    figure_festival_guy(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
};