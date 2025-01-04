#pragma once

#include "figure/figure.h"
#include "window/window_figure_info.h"

class figure_warship : public figure_impl {
public:
    enum e_order {
        e_order_none = 0,
        e_order_goto_wharf,
        e_order_engage_nearby,
        e_order_hold_position,
        e_order_seek_and_destroy,
        e_order_repair
    };

    FIGURE_METAINFO(FIGURE_WARSHIP, figure_warship)
    figure_warship(figure *f) : figure_impl(f) {}
    virtual figure_warship *dcast_warship() override { return this; }

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_WARSHIP, "warship" }; }
    virtual sound_key phrase_key() const override { return {}; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override { return {}; }
    virtual void update_animation() override;
};

struct figure_warship_info_window : public figure_info_window_t<figure_warship_info_window> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_warship>();
    }
};
