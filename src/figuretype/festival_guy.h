#include "figure/figure.h"

enum e_festival_guy_action {
    ACTION_10_FESTIVAL_GUY_CREATED = 10,
    ACTION_11_FESTIVAL_GUY_GOTO_SQUARE = 11,
    ACTION_12_FESTIVAL_GUY_DANCE = 12,
    ACTION_13_FESTIVAL_GUY_GOTO_HOME = 13,
};

class figure_festival_guy : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_GUY, figure_festival_guy)
    figure_festival_guy(figure* f) : figure_impl(f) {}
    virtual figure_festival_guy* dcast_festival_guy() override { return this; }

    struct runtime_data_t {
        int8_t festival_remaining_dances;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual void update_animation() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION; }

    virtual sound_key phrase_key() const override;
};