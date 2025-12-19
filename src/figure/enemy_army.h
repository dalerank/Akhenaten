#pragma once

#include "core/buffer.h"
#include "grid/point.h"
#include <array>

struct enemy_army {
    uint8_t army_id;
    uint8_t formation_id;
    uint8_t layout;
    tile2i home;
    tile2i destination;
    uint16_t destination_building_id;
    uint8_t num_batalions;
    bool ignore_pharaoh_soldiers;
    uint16_t buildings_to_destroy;  // 0 - unlimited
    uint16_t buildings_destroyed;
};

struct enemy_armies_t {   
    enum {
        MAX_ENEMY_ARMIES = 125,
    };

    void clear();

    std::array<enemy_army, MAX_ENEMY_ARMIES> data;
    const enemy_army& get(uint8_t invasion_id);
    void clear_formations(void);
};

extern enemy_armies_t g_enemy_armies;


enemy_army* enemy_army_get_editable(int invasion_id);

void enemy_armies_clear_ignore_pharaoh_soldiers();


int enemy_army_total_enemy_formations(void);

void enemy_army_totals_clear(void);

void enemy_army_totals_add_batalion_formation(int strength);

void enemy_army_totals_add_enemy_formation(int strength);

void enemy_army_calculate_kingdome_influence();

int enemy_army_is_stronger_than_batalions(void);

void enemy_armies_save_state(buffer* buf, buffer* totals_buf);

void enemy_armies_load_state(buffer* buf, buffer* totals_buf);
