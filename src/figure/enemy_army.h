#pragma once

#include "core/buffer.h"
#include "grid/point.h"

struct enemy_army {
    int formation_id;
    int layout;
    tile2i home;
    int destination_x;
    int destination_y;
    int destination_building_id;
    int num_legions;
    int ignore_roman_soldiers;
};

void enemy_armies_clear(void);

const enemy_army* enemy_army_get(int invasion_id);

enemy_army* enemy_army_get_editable(int invasion_id);

void enemy_armies_clear_ignore_roman_soldiers(void);

void enemy_armies_clear_formations(void);

int enemy_army_total_enemy_formations(void);

void enemy_army_totals_clear(void);

void enemy_army_totals_add_legion_formation(int strength);

void enemy_army_totals_add_enemy_formation(int strength);

void enemy_army_calculate_kingdome_influence();

int enemy_army_is_stronger_than_legions(void);

void enemy_armies_save_state(buffer* buf, buffer* totals_buf);

void enemy_armies_load_state(buffer* buf, buffer* totals_buf);
