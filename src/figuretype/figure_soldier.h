#pragma once

#include "figure/figure.h"

enum e_soldier_action {
    ACTION_0_SOLDIER_AT_REST = 0,
    ACTION_1_SOLDIER_GOING_TO_FORT = 1,
    ACTION_2_SOLDIER_RETURNING_TO_BARRACKS = 2,
    ACTION_3_SOLDIER_GOING_TO_STANDARD = 3,
    ACTION_4_SOLDIER_AT_STANDARD = 4,
    ACTION_5_SOLDIER_GOING_TO_MILITARY_ACADEMY = 5,
    ACTION_6_SOLDIER_MOPPING_UP = 6,
    ACTION_7_SOLDIER_GOING_TO_DISTANT_BATTLE = 7,
    ACTION_8_SOLDIER_RETURNING_FROM_DISTANT_BATTLE = 8,
    ACTION_9_SOLDIER_AT_DISTANT_BATTLE = 9,
    ACTION_10_SOLDIER_ATTACK = 10,
    ACTION_11_SOLDIER_INITIAL = 11,
    // OG 0x13 / 0x14: charge rush + look-for-targets after arrival.
    ACTION_12_SOLDIER_CHARGING = 12,
    ACTION_13_SOLDIER_CHARGE_LOOK = 13,
};

class figure_soldier : public figure_impl {
public:
    figure_soldier(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void acquire_attack() override;
    virtual figure_soldier *dcast_soldier() override { return this; }

    virtual void before_poof() override;
    virtual void update_image(const formation *m, int &dir);
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_SOLDIER; }
    virtual bool play_die_sound() override;
    virtual void formation_reset_to_initial(const formation *m) override;

    virtual void going_to_standard();
    virtual void start_charging();
    virtual void send_to_distant_battle();
    virtual void goback_to_fort();

    bool is_charging() const { return action_state() == ACTION_12_SOLDIER_CHARGING; }
};

class figure_soldier_infantry : public figure_soldier {
public:
    FIGURE_METAINFO(FIGURE_INFANTRY, figure_soldier_infantry);
    figure_soldier_infantry(figure *f) : figure_soldier(f) {}

    virtual void update_image(const formation *m, int &dir) override;
};

class figure_soldier_archer : public figure_soldier {
public:
    FIGURE_METAINFO(FIGURE_ARCHER, figure_soldier_archer)
    figure_soldier_archer(figure *f) : figure_soldier(f) {}

    virtual void update_image(const formation *m, int &dir) override;
};

class figure_soldier_charioteer : public figure_soldier {
public:
    FIGURE_METAINFO(FIGURE_FCHARIOTEER, figure_soldier_charioteer)
    figure_soldier_charioteer(figure *f) : figure_soldier(f) {}

    virtual void update_image(const formation *m, int &dir) override;
};
