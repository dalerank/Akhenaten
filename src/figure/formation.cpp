#include "formation.h"

#include "city/city.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/enemy_army.h"
#include "figure/figure.h"
#include "figuretype/figure_enemy.h"
#include "figure/formation_enemy.h"
#include "figure/formation_herd.h"
#include "figure/formation_batalion.h"
#include "grid/grid.h"
#include "game/game_config.h"
#include "building/building_fort.h"
#include "sound/sound.h"
#include "js/js_game.h"

#include <string.h>

const e_formation_layout_tokens_t ANK_CONFIG_ENUM(e_formation_layout_tokens);
formation g_formations[250];

struct formation_data_t {
    int id_last_formation;
    int num_formations;
};

formation_data_t g_formation_data;

void formations_clear(void) {
    auto &data = g_formation_data;
    for (int i = 0; i < MAX_FORMATIONS; i++) {
        memset(&g_formations[i], 0, sizeof(formation));
        g_formations[i].id = i;
    }
    data.id_last_formation = 0;
    data.num_formations = 0;
}

void formation_clear(int formation_id) {
    memset(&g_formations[formation_id], 0, sizeof(formation));
    g_formations[formation_id].id = formation_id;
}

static int get_free_formation(int start_index) {
    for (int i = start_index; i < MAX_FORMATIONS; i++) {
        if (!g_formations[i].in_use) {
            return i;
        }
    }
    return 0;
}

static int formation_create(e_figure_type figure_type, e_formation_layout layout, int orientation, tile2i tile) {
    int formation_id = get_free_formation(10);
    if (!formation_id) {
        return 0;
    }

    formation* f = &g_formations[formation_id];
    f->faction_id = 0;
    f->tile = tile;
    f->destination = tile;
    f->in_use = 1;
    f->figure_type = figure_type;
    f->batalion_id = formation_id - 10;
    f->morale = 100;
    if (layout == FORMATION_ENEMY_DOUBLE_LINE) {
        if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
            f->layout = FORMATION_DOUBLE_LINE_1;
        else {
            f->layout = FORMATION_DOUBLE_LINE_2;
        }
    } else {
        f->layout = layout;
    }
    return formation_id;
}

int formation_create_herd(e_figure_type figure_type, tile2i tile, int num_animals) {
    int formation_id = formation_create(figure_type, FORMATION_HERD, 0, tile);
    if (!formation_id)
        return 0;

    formation* f = &g_formations[formation_id];
    f->is_herd = 1;
    f->wait_ticks = 24;
    f->max_figures = num_animals;
    return formation_id;
}

int formation_create_enemy(e_figure_type figure_type, tile2i tile, e_formation_layout layout, int orientation, e_enemy_type enemy_type, e_formation_attack_type attack_type, int invasion_id, int invasion_sequence) {
    int formation_id = formation_create(figure_type, layout, orientation, tile);
    if (!formation_id)
        return 0;

    formation* f = &g_formations[formation_id];
    f->attack_type = attack_type;
    f->orientation = orientation;
    f->enemy_type = enemy_type;
    f->invasion_id = invasion_id;
    f->invasion_sequence = invasion_sequence;
    return formation_id;
}

formation *formation_get_free(int start_index) {
    int formation_id = get_free_formation(start_index);
    return formation_get(formation_id);
}

formation* formation_get(int formation_id) {
    return &g_formations[formation_id];
}

void formation_toggle_empire_service(int formation_id) {
    g_formations[formation_id].empire_service = g_formations[formation_id].empire_service ? 0 : 1;
}

void formation_record_missile_fired(formation* m) {
    m->missile_fired = 6;
}

void formation_record_missile_attack(formation* m, int from_formation_id) {
    m->missile_attack_timeout = 6;
    m->missile_attack_formation_id = from_formation_id;
}

void formation_record_fight(formation* m) {
    m->recent_fight = 6;
}

int formation_grid_offset_for_invasion(int invasion_sequence) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = &g_formations[i];
        if (m->in_use == 1 && !m->batalion_id && !m->is_herd && m->invasion_sequence == invasion_sequence) {
            if (m->home.valid() )
                return m->home.grid_offset();
            else {
                return 0;
            }
        }
    }
    return 0;
}

void formation_kingdome_pause(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        if (g_formations[i].in_use == 1 && g_formations[i].figure_type == FIGURE_ENEMY_KINGDOME_INFANTRY)
            g_formations[i].wait_ticks = 20;
    }
}

void formation_kingdome_retreat(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        if (g_formations[i].in_use == 1 && g_formations[i].figure_type == FIGURE_ENEMY_KINGDOME_INFANTRY)
            g_formations[i].months_low_morale = 1;
    }
}

bool formation_has_low_morale(formation* m) {
    return m->months_low_morale || m->months_very_low_morale;
}

int formation_get_num_forts_cached() {
    return g_formation_data.num_formations;
}

void formation_calculate_legion_totals() {
    auto &data = g_formation_data;
    data.id_last_formation = 0;
    data.num_formations = 0;
    g_city.military.clear_infantry_batalions();
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use) {
            if (m->batalion_id) {
                data.id_last_formation = i;
                data.num_formations++;
                if (m->figure_type == FIGURE_STANDARD_BEARER)
                    g_city.military.add_infantry_batalion();
            }
            if (m->missile_attack_timeout <= 0 && m->figures[0] && !m->is_herd) {
                figure* f = figure_get(m->figures[0]);
                if (f->state == FIGURE_STATE_ALIVE)
                    formation_set_home(m, f->tile);
            }
        }
    }
}

int formation_get_num_forts() {
    int total = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        if (g_formations[i].in_use && g_formations[i].batalion_id)
            total++;
    }
    return total;
}

int formation_get_max_forts() {
    return MAX_BATALIONS + (!!game_features::gameplay_enable_extra_forts ? 4 : 0);
}

int formation_for_legion(int legion_index) {
    int index = 1;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        if (g_formations[i].in_use && g_formations[i].batalion_id) {
            if (index++ == legion_index)
                return i;
        }
    }
    return 0;
}

void formation_change_morale(formation* m, int amount) {
    int max_morale;
    if (m->figure_type == FIGURE_INFANTRY)
        max_morale = m->has_military_training ? 100 : 80;
    else if (m->figure_type == FIGURE_ENEMY_KINGDOME_INFANTRY)
        max_morale = 100;
    else if (m->figure_type == FIGURE_ARCHER|| m->figure_type == FIGURE_FCHARIOTEER)
        max_morale = m->has_military_training ? 80 : 60;
    else {
        switch (m->enemy_type) {
        case ENEMY_0_BARBARIAN:
        case ENEMY_1_ASSYRIAN:
        case ENEMY_2_CANAANITE:
        case ENEMY_3_EGYPTIAN:
        case ENEMY_4_HITTITE:
            max_morale = 80;
            break;
        case ENEMY_5_HYKSOS:
        case ENEMY_6_KUSHITE:
            max_morale = 90;
            break;
        default:
            max_morale = 70;
            break;
        }
    }
    m->morale = calc_bound(m->morale + amount, 0, max_morale);
}

void formation_update_morale_after_death(formation* m) {
    formation_calculate_figures();
    int pct_dead = calc_percentage<int>(1, m->num_figures);
    int morale;
    if (pct_dead < 8)
        morale = -5;
    else if (pct_dead < 10)
        morale = -7;
    else if (pct_dead < 14)
        morale = -10;
    else if (pct_dead < 20)
        morale = -12;
    else if (pct_dead < 30)
        morale = -15;
    else {
        morale = -20;
    }
    formation_change_morale(m, morale);
}

static void change_all_morale(int legion, int enemy) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = &g_formations[i];
        if (m->in_use && !m->is_herd) {
            if (m->batalion_id)
                formation_change_morale(m, legion);
            else {
                formation_change_morale(m, enemy);
            }
        }
    }
}

void formation_update_monthly_morale_deployed() {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* f = &g_formations[i];
        if (f->in_use != 1 || f->is_herd)
            continue;

        if (f->batalion_id) {
            if (!f->is_at_fort && !f->in_distant_battle) {
                if (f->morale <= 20 && !f->months_low_morale && !f->months_very_low_morale)
                    change_all_morale(-10, 10);

                if (f->morale <= 10)
                    f->months_very_low_morale++;
                else if (f->morale <= 20)
                    f->months_low_morale++;
            }
        } else { // enemy
            if (f->morale <= 20 && !f->months_low_morale && !f->months_very_low_morale)
                change_all_morale(10, -10);

            if (f->morale <= 10)
                f->months_very_low_morale++;
            else if (f->morale <= 20)
                f->months_low_morale++;
        }
    }
}

void formation_update_monthly_morale_at_rest(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = &g_formations[i];
        if (m->in_use != 1 || m->is_herd)
            continue;

        if (m->batalion_id) {
            if (m->is_at_fort) {
                m->months_from_home = 0;
                m->months_very_low_morale = 0;
                m->months_low_morale = 0;
                formation_change_morale(m, 5);
                formation_batalion_restore_layout(m);
            } else if (!m->recent_fight) {
                m->months_from_home++;
                if (m->months_from_home > 3) {
                    if (m->months_from_home > 100)
                        m->months_from_home = 100;

                    formation_change_morale(m, -5);
                }
            }
        } else {
            formation_change_morale(m, 0);
        }
    }
}

void formation_decrease_monthly_counters(formation* m) {
    if (m->batalion_id) {
        if (m->cursed_by_seth)
            m->cursed_by_seth--;
    }
    if (m->missile_fired)
        m->missile_fired--;

    if (m->missile_attack_timeout)
        m->missile_attack_timeout--;

    if (m->recent_fight)
        m->recent_fight--;
}

void formation_clear_monthly_counters(formation* m) {
    m->missile_fired = 0;
    m->missile_attack_timeout = 0;
    m->recent_fight = 0;
}

void formation_set_destination(formation* m, tile2i tile) {
    m->destination = tile;
}

void formation::set_destination_building(tile2i tile, int building_id) {
    destination = tile;
    destination_building_id = building_id;
}

void formation_set_home(formation* m, tile2i tile) {
    m->home = tile;
}

void formation_clear_figures(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* f = &g_formations[i];
        for (int fig = 0; fig < formation::max_figures_count; fig++) {
            f->figures[fig] = 0;
        }
        f->num_figures = 0;
        f->is_at_fort = 1;
        f->total_damage = 0;
        f->max_total_damage = 0;
    }
}

int formation_add_figure(int formation_id, int figure_id, int deployed, int damage, int max_damage) {
    formation* f = &g_formations[formation_id];
    f->num_figures++;
    f->total_damage += damage;
    f->max_total_damage += max_damage;
    if (deployed)
        f->is_at_fort = 0;

    for (int fig = 0; fig < formation::max_figures_count; fig++) {
        if (!f->figures[fig]) {
            f->figures[fig] = figure_id;
            return fig;
        }
    }

    return 0; // shouldn't happen
}

void formation_move_herds_away(tile2i tile) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* f = &g_formations[i];
        if (f->in_use != 1 || f->batalion_id || !f->is_herd || f->num_figures <= 0)
            continue;

        if (calc_maximum_distance(tile, f->home) <= 6) {
            g_formations[i].wait_ticks = 50;
            g_formations[i].herd_direction = calc_general_direction(tile, f->home);
        }
    }
}

void formation_calculate_figures(void) {
    formation_clear_figures();
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE)
            continue;

        if (f->type == FIGURE_RIOTER)
            continue;

        // const bool soldier = !!::smart_cast<figure_soldier>(f);
        if (f->formation_id == 0 /* !soldier && !f->is_enemy() && !f->is_herd() */) {
            continue;
        }
        
        const int max_damage = f->max_damage();
        int index = formation_add_figure(f->formation_id, i, f->formation_at_rest != 1, f->damage, max_damage);
        f->index_in_formation = index;
    }

    enemy_army_totals_clear();
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && !m->is_herd) {
            if (m->batalion_id == 0) {
                continue;
            }

            if (m->own_batalion && m->num_figures > 0) {
                int was_halted = m->is_halted;
                m->is_halted = 1;
                for (int fig = 0; fig < m->num_figures; fig++) {
                    int figure_id = m->figures[fig];
                    if (figure_id && figure_get(figure_id)->direction != DIR_8_NONE)
                        m->is_halted = 0;
                }
                int total_strength = m->num_figures;
                if (m->figure_type == FIGURE_STANDARD_BEARER)
                    total_strength += m->num_figures / 2;

                enemy_army_totals_add_batalion_formation(total_strength);
                if (m->figure_type == FIGURE_STANDARD_BEARER) {
                    if (!was_halted && m->is_halted)
                        g_sound.play_effect(SOUND_EFFECT_FORMATION_SHIELD);
                }

            }

            // enemy
            if (!m->own_batalion) {
                if (m->num_figures <= 0) {
                    formation_clear(m->id);
                } else {
                    enemy_army_totals_add_enemy_formation(m->num_figures);
                }
            }
        }
    }

    g_city.military.update_totals();
}

static void update_direction(int formation_id, int first_figure_direction) {
    formation* f = &g_formations[formation_id];
    if (f->unknown_fired) {
        f->unknown_fired--;
    } else if (f->missile_fired) {
        f->direction = first_figure_direction;
    } else if (f->layout == FORMATION_DOUBLE_LINE_1 || f->layout == FORMATION_SINGLE_LINE_1) {
        if (f->home.y() < f->prev.home.y())
            f->direction = DIR_0_TOP_RIGHT;
        else if (f->home.y() > f->prev.home.y())
            f->direction = DIR_4_BOTTOM_LEFT;

    } else if (f->layout == FORMATION_DOUBLE_LINE_2 || f->layout == FORMATION_SINGLE_LINE_2) {
        if (f->home.x() < f->prev.home.x())
            f->direction = DIR_6_TOP_LEFT;
        else if (f->home.x() > f->prev.home.x())
            f->direction = DIR_2_BOTTOM_RIGHT;

    } else if (f->layout == FORMATION_TORTOISE || f->layout == FORMATION_COLUMN) {
        int dx = (f->home.x() < f->prev.home.x()) ? (f->prev.home.x() - f->home.x()) : (f->home.x() - f->prev.home.x());
        int dy = (f->home.y() < f->prev.home.y()) ? (f->prev.home.y() - f->home.y()) : (f->home.y() - f->prev.home.y());
        if (dx > dy) {
            if (f->home.x() < f->prev.home.x())
                f->direction = DIR_6_TOP_LEFT;
            else if (f->home.x() > f->prev.home.x())
                f->direction = DIR_2_BOTTOM_RIGHT;

        } else {
            if (f->home.y() < f->prev.home.y())
                f->direction = DIR_0_TOP_RIGHT;
            else if (f->home.y() > f->prev.home.y())
                f->direction = DIR_4_BOTTOM_LEFT;
        }
    }
    f->prev.home = f->home;
}

static void update_directions(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = &g_formations[i];
        if (m->in_use && !m->is_herd)
            update_direction(m->id, figure_get(m->figures[0])->direction);
    }
}

static void set_legion_max_figures(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        if (g_formations[i].in_use && g_formations[i].batalion_id)
            g_formations[i].max_figures = 16;
    }
}

void formation_update_all(bool second_time) {
    OZZY_PROFILER_SECTION("Game/Update/Formations");
    formation_calculate_legion_totals();
    formation_calculate_figures();
    update_directions();
    formation_batalion_decrease_damage();
    if (!second_time) {
        formation_update_monthly_morale_deployed();
    }

    set_legion_max_figures();
    formation_batalion_update();
    formation_enemy_update();
    formation_herd_update();
}

io_buffer* iob_formations = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < MAX_FORMATIONS; i++) {
        formation* f = &g_formations[i];
        f->id = i;                                   // 10
        iob->bind_bool(f->in_use); // 1
        iob->bind_u8(f->faction_id);
        iob->bind_u8(f->batalion_id);
        iob->bind_bool(f->is_at_fort);
        iob->bind_u16((uint16_t&)f->figure_type); // 69
        iob->bind(BIND_SIGNATURE_INT16, &f->building_id);

        for (int fig = 0; fig < formation::max_figures_count; fig++) {
            iob->bind(BIND_SIGNATURE_INT16, &f->figures[fig]);
        }

        iob->bind(BIND_SIGNATURE_UINT8, &f->num_figures); // --> 3
        iob->bind(BIND_SIGNATURE_UINT8, &f->max_figures); // 7
        iob->bind(BIND_SIGNATURE_INT16, &f->layout);      // 9
        iob->bind(BIND_SIGNATURE_INT16, &f->morale);      // 100

        iob->bind(BIND_SIGNATURE_TILE2I, f->home);        // 44
        iob->bind(BIND_SIGNATURE_TILE2I, f->standard_tile);    //
        iob->bind(BIND_SIGNATURE_TILE2I, f->tile);             // 44
        iob->bind(BIND_SIGNATURE_TILE2I, f->destination); // 49
        
        iob->bind(BIND_SIGNATURE_INT16, &f->destination_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &f->standard_figure_id);
        iob->bind_u8(f->batalion_id);
        iob->bind_bool(f->own_batalion);
        iob->bind(BIND_SIGNATURE_UINT8, &f->attack_type);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &f->batalion_recruit_type);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &f->has_military_training);
        iob->bind____skip(1);

        iob->bind____skip(2);                                  //     vv 6 hp per ostich?
        iob->bind(BIND_SIGNATURE_INT16, &f->total_damage);     // --> 18
        iob->bind(BIND_SIGNATURE_INT16, &f->max_total_damage); // 50
        iob->bind(BIND_SIGNATURE_INT8, &f->recent_fight);
        iob->bind____skip(1);
        iob->bind____skip(2);
        iob->bind(BIND_SIGNATURE_INT16, &f->wait_ticks); // --> 8 --> 0 ??????
        iob->bind____skip(4);
        //            iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_advance);
        //            iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_regroup);
        //            iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_halt);
        //            iob->bind(BIND_SIGNATURE_INT16, &f->enemy_legion_index);
        f->enemy_state.duration_advance = 0;
        f->enemy_state.duration_regroup = 0;
        f->enemy_state.duration_halt = 0;
        f->enemy_legion_index = 0;

        iob->bind(BIND_SIGNATURE_UINT8, &f->is_halted);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_fired);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_attack_timeout);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_attack_formation_id);
        iob->bind(BIND_SIGNATURE_INT16, &f->prev.layout);
        iob->bind(BIND_SIGNATURE_INT16, &f->cursed_by_seth);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_low_morale);
        f->months_very_low_morale = 0;
        iob->bind(BIND_SIGNATURE_UINT8, &f->empire_service);
        iob->bind(BIND_SIGNATURE_UINT8, &f->in_distant_battle);
        iob->bind(BIND_SIGNATURE_UINT8, &f->is_herd); // 2
        iob->bind(BIND_SIGNATURE_UINT8, &f->enemy_type);
        iob->bind(BIND_SIGNATURE_UINT8, &f->direction);
        iob->bind(BIND_SIGNATURE_TILE2I, f->prev.home);
        iob->bind(BIND_SIGNATURE_UINT8, &f->unknown_fired);
        iob->bind(BIND_SIGNATURE_UINT8, &f->orientation);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_from_home);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_very_low_morale);
        iob->bind(BIND_SIGNATURE_UINT8, &f->invasion_id);
        // iob->bind(BIND_SIGNATURE_UINT8, &f->herd_wolf_spawn_delay);                      // --> 4
        iob->bind(BIND_SIGNATURE_UINT8, &f->herd_ostrich_spawn_delay); // --> 4
        iob->bind(BIND_SIGNATURE_UINT8, &f->herd_direction);           // 6
        iob->bind(BIND_SIGNATURE_UINT8, &f->failed_creation_count);           // 6
        iob->bind____skip(5);
        iob->bind____skip(17);
        iob->bind(BIND_SIGNATURE_INT16, &f->invasion_sequence);

        if (!f->home.valid() && f->is_herd) {
            memset(f, 0, sizeof(formation));
        }
    }
});
io_buffer* iob_formations_info = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_formation_data;
    int tmp;
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &data.id_last_formation);
    iob->bind(BIND_SIGNATURE_INT32, &data.num_formations);
});