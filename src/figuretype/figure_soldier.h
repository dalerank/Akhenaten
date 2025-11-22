#pragma once

#include "figure/figure.h"

enum e_soldier_action {
    ACTION_80_SOLDIER_AT_REST = 80,
    ACTION_81_SOLDIER_GOING_TO_FORT = 81,
    ACTION_82_SOLDIER_RETURNING_TO_BARRACKS = 82,
    ACTION_83_SOLDIER_GOING_TO_STANDARD = 83,
    ACTION_84_SOLDIER_AT_STANDARD = 84,
    ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY = 85,
    ACTION_86_SOLDIER_MOPPING_UP = 86,
    ACTION_87_SOLDIER_GOING_TO_DISTANT_BATTLE = 87,
    ACTION_88_SOLDIER_RETURNING_FROM_DISTANT_BATTLE = 88,
    ACTION_89_SOLDIER_AT_DISTANT_BATTLE = 89,
    ACTION_90_SOLDIER_ATTACK = 90,
    ACTION_90_SOLDIER_INITIAL = 91,
};

class figure_soldier : public figure_impl {
public:
    figure_soldier(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual figure_soldier *dcast_soldier() override { return this; }

    //virtual bool play_die_sound() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_PAVILION; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual void update_image(const formation *m, int &dir);
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_SOLDIER; }
    virtual bool play_die_sound() override;

    virtual bool is_attack() const { return action_state() == FIGURE_ACTION_150_ATTACK; }
    virtual void formation_reset_to_initial(const formation *m) override;
};

class figure_soldier_infantry : public figure_soldier {
public:
    FIGURE_METAINFO(FIGURE_INFANTRY, figure_soldier_infantry);
    figure_soldier_infantry(figure *f) : figure_soldier(f) {}

    virtual sound_key phrase_key() const override;
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