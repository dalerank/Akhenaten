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
    uint8_t buildings_to_destroy;  // 0 - unlimited
    uint8_t buildings_destroyed;
    uint16_t want_money;  // 0 - unlimited
    uint16_t grab_money;
    char reserved_[72];
};

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

    void calculate_kingdome_influence();
};

struct enemy_armies_t {   
    enum {
        MAX_ENEMY_ARMIES = 120,
    };

    void clear();

    std::array<enemy_army, MAX_ENEMY_ARMIES> data;
    const enemy_army& get(uint8_t invasion_id);
    void clear_formations(void);
};

extern enemy_armies_t g_enemy_armies;
extern enemy_army_in_city_t g_enemy_army_in_city;

enemy_army* enemy_army_get_editable(uint8_t invasion_id);

void enemy_armies_clear_ignore_pharaoh_soldiers();


int enemy_army_total_enemy_formations(void);

void enemy_army_totals_clear(void);

void enemy_army_totals_add_batalion_formation(int strength);

void enemy_army_totals_add_enemy_formation(int strength);

int enemy_army_is_stronger_than_batalions(void);
