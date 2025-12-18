#pragma once

#include "core/buffer.h"
#include "grid/point.h"

struct enemy_army {
    int formation_id;
    uint8_t layout;
    tile2i home;
    tile2i destination;
    uint16_t destination_building_id;
    uint8_t num_batalions;
    bool ignore_pharaoh_soldiers;
};

struct enemy_armies_t {   
    enum {
        MAX_ENEMY_ARMIES = 125,
    };

    void clear();

    enemy_army data[MAX_ENEMY_ARMIES];
};

extern enemy_armies_t g_enemy_armies;

const enemy_army* enemy_army_get(int invasion_id);

enemy_army* enemy_army_get_editable(int invasion_id);

void enemy_armies_clear_ignore_pharaoh_soldiers();

void enemy_armies_clear_formations(void);

int enemy_army_total_enemy_formations(void);

void enemy_army_totals_clear(void);

void enemy_army_totals_add_batalion_formation(int strength);

void enemy_army_totals_add_enemy_formation(int strength);

void enemy_army_calculate_kingdome_influence();

int enemy_army_is_stronger_than_batalions(void);

void enemy_armies_save_state(buffer* buf, buffer* totals_buf);

void enemy_armies_load_state(buffer* buf, buffer* totals_buf);
