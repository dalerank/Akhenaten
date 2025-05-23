#include "figure/figure.h"

class figure_festival_guy : public figure_impl
{
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_GUY, figure_festival_guy)
    figure_festival_guy(figure* f) : figure_impl(f) {}

    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual void update_animation() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_FESTIVAL_GUY, "festival_guy" }; }
    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION; }
};