#include "enemy_army.h"

#define MAX_ENEMY_ARMIES 125

#include "figure/formation.h"
#include "game/game_environment.h"
#include "grid/soldier_strength.h"

static enemy_army enemy_armies[MAX_ENEMY_ARMIES];

struct current_city_army_t {
    int enemy_formations;
    int enemy_strength;
    int legion_formations;
    int legion_strength;

    int days_since_roman_influence_calculation;
};

current_city_army_t g_city_army;

void enemy_armies_clear(void) {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].formation_id = 0;
        enemy_armies[i].layout = 0;
        enemy_armies[i].home.set(0, 0);
        enemy_armies[i].destination = tile2i::invalid;
        enemy_armies[i].destination_building_id = 0;
        enemy_armies[i].ignore_roman_soldiers = 0;
    }
    g_city_army.enemy_formations = 0;
    g_city_army.enemy_strength = 0;
    g_city_army.legion_formations = 0;
    g_city_army.legion_strength = 0;
    g_city_army.days_since_roman_influence_calculation = 0;
}

const enemy_army* enemy_army_get(int invasion_id) {
    return &enemy_armies[invasion_id];
}

enemy_army* enemy_army_get_editable(int invasion_id) {
    return &enemy_armies[invasion_id];
}

void enemy_armies_clear_ignore_roman_soldiers(void) {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].ignore_roman_soldiers = 0;
    }
}

void enemy_armies_clear_formations(void) {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].formation_id = 0;
        enemy_armies[i].num_legions = 0;
    }
}

void enemy_army_totals_clear(void) {
    g_city_army.legion_formations = 0;
    g_city_army.legion_strength = 0;
    g_city_army.enemy_formations = 0;
    g_city_army.enemy_strength = 0;
}

void enemy_army_totals_add_legion_formation(int strength) {
    g_city_army.legion_formations++;
    g_city_army.legion_strength += strength;
}

void enemy_army_totals_add_enemy_formation(int strength) {
    g_city_army.enemy_formations++;
    g_city_army.enemy_strength += strength;
}

int enemy_army_total_enemy_formations(void) {
    return g_city_army.enemy_formations;
}

void enemy_army_calculate_kingdome_influence(void) {
    g_city_army.days_since_roman_influence_calculation++;
    if (g_city_army.days_since_roman_influence_calculation > 4)
        g_city_army.days_since_roman_influence_calculation = 0;
    else
        return;
    map_soldier_strength_clear();

    for (int i = 1; i < MAX_FORMATIONS; i++) {
        const formation* m = formation_get(i);
        if (m->in_use != 1 || !m->batalion_id)
            continue;

        if (m->num_figures > 0)
            map_soldier_strength_add(m->home, 7, 1);

        if (m->num_figures > 3)
            map_soldier_strength_add(m->home, 6, 1);

        if (m->num_figures > 6)
            map_soldier_strength_add(m->home, 5, 1);

        if (m->num_figures > 9)
            map_soldier_strength_add(m->home, 4, 1);

        if (m->num_figures > 12)
            map_soldier_strength_add(m->home, 3, 1);

        if (m->num_figures > 15)
            map_soldier_strength_add(m->home, 2, 1);
    }
}

int enemy_army_is_stronger_than_legions() {
    return g_city_army.enemy_strength > 2 * g_city_army.legion_strength;
}

void enemy_armies_save_state(buffer* buf, buffer* totals_buf) {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].formation_id);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].home.x());
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].home.y());
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].layout);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_t2i(enemy_armies[i].destination);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        // buf->write_i32(enemy_armies[i].destination.y());
        buf->write_i32(0);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].destination_building_id);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].num_legions);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(enemy_armies[i].ignore_roman_soldiers);
    }
    totals_buf->write_i32(g_city_army.enemy_formations);
    totals_buf->write_i32(g_city_army.enemy_strength);
    totals_buf->write_i32(g_city_army.legion_formations);
    totals_buf->write_i32(g_city_army.legion_strength);
    totals_buf->write_i32(g_city_army.days_since_roman_influence_calculation);
}

void enemy_armies_load_state(buffer* buf, buffer* totals_buf) {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].formation_id = buf->read_i32();
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].home.set_x(buf->read_i32());
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].home.set_y(buf->read_i32());
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].layout = buf->read_i32();
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        buf->read_t2i(enemy_armies[i].destination);
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        // enemy_armies[i].destination_y = buf->read_i32();
        int tmp = buf->read_i32();
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].destination_building_id = buf->read_i32();
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].num_legions = buf->read_i32();
    }
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        enemy_armies[i].ignore_roman_soldiers = buf->read_i32();
    }
    g_city_army.enemy_formations = totals_buf->read_i32();
    g_city_army.enemy_strength = totals_buf->read_i32();
    g_city_army.legion_formations = totals_buf->read_i32();
    g_city_army.legion_strength = totals_buf->read_i32();
    g_city_army.days_since_roman_influence_calculation = totals_buf->read_i32();
}
