#include "figure_enemy_fast_sword.h"

#include "core/profiler.h"
#include "city/city.h"

figure_barbarian_sword::static_params barbarian_sword_m;

void figure_enemy_fast_sword::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyFastSword");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
    g_city.figures_add_enemy();
    base.terrain_usage = TERRAIN_USAGE_ENEMY;
    //int formationx = formation_layout_position_x(m->layout, index_in_formation);
    //int formationy = formation_layout_position_y(m->layout, index_in_formation);

    switch (action_state()) {
    case FIGURE_ACTION_148_FLEEING:
        base.destination_tile = base.source_tile;

        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_151_ENEMY_INITIAL:
        enemy_initial(m);
        break;

    case FIGURE_ACTION_152_ENEMY_WAITING:
        base.map_figure_update(); // ???? WTF
        break;

    case FIGURE_ACTION_153_ENEMY_MARCHING:
        enemy_marching(m);
        break;

    case FIGURE_ACTION_154_ENEMY_FIGHTING:
        enemy_fighting(m);
        break;
    }
}

void figure_enemy_fast_sword::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == FIGURE_ACTION_154_ENEMY_FIGHTING) {
        animkey = animkeys().attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == FIGURE_ACTION_153_ENEMY_MARCHING) {
        animkey = animkeys().walk;
        base.anim.frame = 0;
    }

    image_set_animation(animkey);
}
