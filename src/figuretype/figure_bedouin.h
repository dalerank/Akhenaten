#pragma once

#include "core/svector.h"
#include "figuretype/figure_enemy_fast_sword.h"

class figure_bedouin : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_BEDOUIN, figure_bedouin)
    figure_bedouin(figure* f) : figure_enemy_fast_sword(f) {}

    struct runtime_data_t {
        uint8_t damage_action = 0;
        uint8_t move_counter = 0;
    } FIGURE_RUNTIME_DATA_T;

    struct static_params : public base_params_t, public figure_static_params {
        svector<uint8_t, 4> move_cycle;
    } FIGURE_STATIC_DATA_T;

    virtual void figure_action() override;
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
    virtual int enemy_walk_ticks() override;
    virtual void play_attack_sound() override;
};
ANK_CONFIG_STRUCT(figure_bedouin::static_params, interval_attack_delay, move_cycle)
