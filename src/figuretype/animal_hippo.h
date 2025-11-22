#pragma once

#include "figure_animal.h"

enum e_hippo_action {
    ACTION_8_HIPPO_RECALCULATE = 8,
    ACTION_10_HIPPO_GOING = 10,
    ACTION_11_HIPPO_ATTACKING = 11,
    ACTION_15_HIPPO_TERRIFIED = 15,
    ACTION_16_HIPPO_CHASING = 16,
    ACTION_18_HIPPO_ROOSTING = 18,
    ACTION_19_HIPPO_IDLE = 19,
    ACTION_24_HIPPO_SPAWNED = 24,
    ACTION_196_HIPPO_AT_REST = 196
};

/**
 * @class figure_hippo
 * @brief Represents a hippopotamus animal figure in the game world.
 * 
 * This class implements the behavior of wild hippos that roam the map.
 * Hippos can wander, roost, eat in water areas, and are aggressive when attacked.
 * Unlike ostriches or antelopes, hippos will chase and attack hunters when threatened.
 * They use pathfinding to navigate around impassable terrain and can move on land and water.
 * 
 * Behavioral states include:
 * - Idle and roosting (resting/eating in water)
 * - Moving between locations (amphibious movement)
 * - Chasing attackers when hit by projectiles
 * - Attacking hunters who threatened them
 * 
 * Hippos can be hunted for resource RESOURCE_GAMEMEAT but are dangerous prey.
 */
class figure_hippo : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_HIPPO, figure_hippo)
    figure_hippo(figure *f) : figure_animal(f) {}
    virtual figure_hippo *dcast_hippo() override { return this; }

    struct runtime_data_t {
        int8_t applied_damage;
        int attacker_id;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void apply_damage(int hit_dmg, figure_id attacker_id) override;
    
    virtual void herd_moved() override;
    virtual void moveto(tile2i tile) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};