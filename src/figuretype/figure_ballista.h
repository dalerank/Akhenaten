#pragma once

#include "figure/figure.h"
#include "core/archive.h"

// OG military.c figure_ballista_action (FIG_BALLISTA).
// Remake keeps action ids 180/181 (spawn already uses them); OG READY=8 / FIRING=9.
enum e_ballista_action {
    ACTION_180_BALLISTA_CREATED = 180, // OG FIGURE_ACTION_BALLISTA_READY
    ACTION_181_BALLISTA_FIRING = 181,  // OG FIGURE_ACTION_BALLISTA_FIRING
};

struct ballista_rules_t {
    int16_t search_ticks = 20;
    int16_t aim_ticks = 10;
    int16_t reload_ticks = 23;
};
ANK_CONFIG_STRUCT(ballista_rules_t, search_ticks, aim_ticks, reload_ticks)

extern ballista_rules_t ballista_rules;

class figure_ballista : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BALLISTA, figure_ballista)
    figure_ballista(figure *f) : figure_impl(f) {}
    virtual figure_ballista *dcast_ballista() override { return this; }

    struct runtime_data_t {
        uint8_t shooting;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};
