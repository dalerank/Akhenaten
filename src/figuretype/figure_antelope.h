#pragma once

#include "figure_animal.h"

enum e_antelope_action {
    ACTION_8_ANTELOPE_RECALCULATE = 8,
    ACTION_10_ANTELOPE_GOING = 10,
    ACTION_15_ANTELOPE_TERRIFIED = 15,
    ACTION_16_ANTELOPE_FLEEING = 16,
    ACTION_18_ANTELOPE_ROOSTING = 18,
    ACTION_19_ANTELOPE_IDLE = 19,
    ACTION_24_ANTELOPE_SPAWNED = 24,
    ACTION_196_ANTELOPE_AT_REST = 196
};

/**
 * @class figure_antelope
 * @brief Represents an antelope animal figure in the game world.
 * 
 * This class implements the behavior of wild antelopes that roam the map.
 * Antelopes can wander, roost, eat, and flee when threatened or damaged by arrows.
 * They use pathfinding to navigate around impassable terrain and avoid obstacles.
 * 
 * Behavioral states include:
 * - Idle and roosting (resting/eating)
 * - Moving between locations
 * - Fleeing when hit by projectiles
 * - Terrified state when threatened
 * 
 * Antelopes can be hunted for resource RESOURCE_GAMEMEAT.
 */
class figure_antelope : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_ANTELOPE, figure_antelope)
    figure_antelope(figure *f) : figure_animal(f) {}
    virtual figure_antelope *dcast_antelope() override { return this; }

    struct runtime_data_t {
        int8_t applied_damage;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_ANTELOPE, "antelope"}; }
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;
    virtual void apply_damage(int hit_dmg, figure_id attacker_id) override;

    virtual void herd_moved() override;
    virtual void moveto(tile2i tile) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};