#include "enemy_army.h" 

#include "figure/formation.h"
#include "game/game_environment.h"
#include "grid/soldier_strength.h"
#include "city/city_figures.h"
#include "grid/enemy_strength.h"

struct enemy_army_in_city_t {
    int enemy_formations;
    int enemy_strength;
    int batlion_formations;
    int batalion_strength;

    int days_since_pharaoh_influence_calculation;

    void clear(void) {
        enemy_formations = 0;
        enemy_strength = 0;
        batlion_formations = 0;
        batalion_strength = 0;
        days_since_pharaoh_influence_calculation = 0;
    }
};

enemy_armies_t g_enemy_armies;
enemy_army_in_city_t g_enemy_army_in_city;

void enemy_armies_t::clear() {
    for (int i = 0; i < MAX_ENEMY_ARMIES; i++) {
        data[i].formation_id = 0;
        data[i].layout = 0;
        data[i].home.set(0, 0);
        data[i].destination = tile2i::invalid;
        data[i].destination_building_id = 0;
        data[i].ignore_pharaoh_soldiers = 0;
        data[i].buildings_to_destroy = 0;
        data[i].buildings_destroyed = 0;
    }

    g_enemy_army_in_city.clear();
}

const enemy_army& enemy_armies_t::get(uint8_t invasion_id) {
    return data[invasion_id];
}

enemy_army* enemy_army_get_editable(uint8_t invasion_id) {
    return &g_enemy_armies.data[invasion_id];
}

void enemy_armies_clear_ignore_pharaoh_soldiers() {
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].ignore_pharaoh_soldiers = 0;
    }
}

void enemy_armies_t::clear_formations() {
    uint8_t army_id = 0;
    for (auto &army: data) {
        army.army_id = army_id;
        army_id++;
        army.formation_id = 0;
        army.num_batalions = 0;
    }
}

void enemy_army_totals_clear(void) {
    g_enemy_army_in_city.batlion_formations = 0;
    g_enemy_army_in_city.batalion_strength = 0;
    g_enemy_army_in_city.enemy_formations = 0;
    g_enemy_army_in_city.enemy_strength = 0;
}

void enemy_army_totals_add_batalion_formation(int strength) {
    g_enemy_army_in_city.batlion_formations++;
    g_enemy_army_in_city.batalion_strength += strength;
}

void enemy_army_totals_add_enemy_formation(int strength) {
    g_enemy_army_in_city.enemy_formations++;
    g_enemy_army_in_city.enemy_strength += strength;
}

int enemy_army_total_enemy_formations() {
    return g_enemy_army_in_city.enemy_formations;
}

void enemy_army_calculate_kingdome_influence() {
    g_enemy_army_in_city.days_since_pharaoh_influence_calculation++;
    if (g_enemy_army_in_city.days_since_pharaoh_influence_calculation > 4)
        g_enemy_army_in_city.days_since_pharaoh_influence_calculation = 0;
    else
        return;

    map_soldier_strength_clear();
    map_enemy_strength_clear();

    for (int i = 1; i < MAX_FORMATIONS; i++) {
        const formation* m = formation_get(i);
        if (m->in_use != 1)
            continue;

        if (m->batalion_id && m->own_batalion) {
            // Own batalions
            int figures_num = 0;
            for (int fig = 0; fig < formation::max_figures_count; fig++) {
                if (m->figures[fig] > 0) {
                    figure *f = figure_get(m->figures[fig]);
                    figures_num++;
                    uint8_t radiuses[] = { 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2 };
                    if (f && f->state == FIGURE_STATE_ALIVE && f->is_enemy()) {
                        map_soldier_strength_add(f->tile, radiuses[figures_num], 1);
                    }
                }
            }
        } else if (m->invasion_id > 0) {
            int figures_num = 0;
            for (int fig = 0; fig < formation::max_figures_count; fig++) {
                if (m->figures[fig] > 0) {
                    figure* f = figure_get(m->figures[fig]);
                    figures_num++;
                    uint8_t radiuses[] = { 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2 };
                    if (f && f->state == FIGURE_STATE_ALIVE && f->is_enemy()) {
                        map_enemy_strength_add(f->tile, radiuses[figures_num], 1);
                    }
                }
            }
        }
    }
}

int enemy_army_is_stronger_than_batalions() {
    return g_enemy_army_in_city.enemy_strength > 2 * g_enemy_army_in_city.batalion_strength;
}

void enemy_armies_save_state(buffer* buf, buffer* totals_buf) {
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].formation_id);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].home.x());
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].home.y());
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].layout);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_t2i(g_enemy_armies.data[i].destination);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        // buf->write_i32(enemy_armies[i].destination.y());
        buf->write_i32(0);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].destination_building_id);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i32(g_enemy_armies.data[i].num_batalions);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->write_i8(g_enemy_armies.data[i].ignore_pharaoh_soldiers);
        buf->write_i16(g_enemy_armies.data[i].buildings_to_destroy);
        buf->write_i16(g_enemy_armies.data[i].buildings_destroyed);
    }
    totals_buf->write_i32(g_enemy_army_in_city.enemy_formations);
    totals_buf->write_i32(g_enemy_army_in_city.enemy_strength);
    totals_buf->write_i32(g_enemy_army_in_city.batlion_formations);
    totals_buf->write_i32(g_enemy_army_in_city.batalion_strength);
    totals_buf->write_i32(g_enemy_army_in_city.days_since_pharaoh_influence_calculation);
}

void enemy_armies_load_state(buffer* buf, buffer* totals_buf) {
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].formation_id = buf->read_i32();
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].home.set_x(buf->read_i32());
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].home.set_y(buf->read_i32());
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].layout = buf->read_i32();
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        buf->read_t2i(g_enemy_armies.data[i].destination);
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        // enemy_armies[i].destination_y = buf->read_i32();
        int tmp = buf->read_i32();
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].destination_building_id = buf->read_i32();
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].num_batalions = buf->read_i32();
    }
    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        g_enemy_armies.data[i].ignore_pharaoh_soldiers = buf->read_i8();
        g_enemy_armies.data[i].buildings_to_destroy = buf->read_i16();
        g_enemy_armies.data[i].buildings_destroyed = buf->read_i16();
    }
    g_enemy_army_in_city.enemy_formations = totals_buf->read_i32();
    g_enemy_army_in_city.enemy_strength = totals_buf->read_i32();
    g_enemy_army_in_city.batlion_formations = totals_buf->read_i32();
    g_enemy_army_in_city.batalion_strength = totals_buf->read_i32();
    g_enemy_army_in_city.days_since_pharaoh_influence_calculation = totals_buf->read_i32();
}
