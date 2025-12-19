#include "formation_enemy.h"

#include "building/building.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/enemy_army.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_enemy.h"
#include "figure/route.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/queue.h"
#include "grid/routing/routing.h"
#include "grid/soldier_strength.h"
#include "grid/terrain.h"
#include "core/flat_map.h"
#include "js/js_game.h"
#include "grid/road_access.h"

using stage_attack_weight = std::array<int16_t, BUILDING_MAX>;
using stage_attack_rules = svector<uint16_t, BUILDING_MAX>;
using attacked_buildings = flat_map<building_id, bool, 32>;

struct enemy_attack_priority_t {
    stage_attack_rules food_chain;
    stage_attack_rules gold_stores;
    stage_attack_rules best_buildings;
    stage_attack_rules troops;
    stage_attack_rules simple;
    stage_attack_rules random;

    stage_attack_weight food_chain_w;
    stage_attack_weight gold_stores_w;
    stage_attack_weight best_buildings_w;
    stage_attack_weight troops_w;
    stage_attack_weight simple_w;
    stage_attack_weight random_w;

    struct attack_pairs {
        stage_attack_rules *rules;
        stage_attack_weight *weights;
    };

    std::array<attack_pairs, FORMATION_ATTACK_MAX> data = { {
        {&food_chain, &food_chain_w},
        {&gold_stores, &gold_stores_w},
        {&best_buildings, &best_buildings_w},
        {&troops, &troops_w},
        {&simple, &simple_w},
        {&random, &random_w }
    } };

    const stage_attack_weight &get_weights(e_formation_attack_type rule) {
        return *data[rule].weights;
    }
};
ANK_CONFIG_STRUCT(enemy_attack_priority_t,
    food_chain, gold_stores, best_buildings, troops, simple)

struct enemy_attack_rules_t {
    enemy_attack_priority_t priority;

    void archive_load(archive arch) {
        for (auto &it : priority.data) {
            std::fill(it.weights->begin(), it.weights->end(), 0);
            for (int i = 0; i < it.rules->size(); i++) {
                uint16_t btype = it.rules->at(i);
                it.weights->at(btype) = (it.rules->size() - i) + 1;
            }
        }
    }
};
ANK_CONFIG_STRUCT(enemy_attack_rules_t, priority)

enemy_attack_rules_t ANK_VARIABLE(enemy_attack_rules);

// Battalion position offsets for different formation types and orientations
// [layout][orientation][battalion_index * 2] = x_offset, [layout][orientation][battalion_index * 2 + 1] = y_offset
// Each array contains 40 values (20 battalions × 2 coordinates)
static const vec2i LAYOUT_ORIENTATION_OFFSETS[13][4][40]= {
      // [0] FORMATION_COLUMN - column formation
      {
       { {0, 0}, {-3, 0}, {3, 0}, {-8, 0}, {8, 0}, {-3, 8}, {3, 8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0}, {0, 0}, {0,  0}, {0, 0}, {0,  0},  {0, 0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0, -3}, {0, 3}, {0, -8}, {0, 8}, {8, -3},  {8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0, 0},  {0, 0}, {0, 0},  {0, 0}, {0, 0},   {0, 0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0}, {3, 0}, {-8, 0}, {8, 0}, {-3, -8}, {3, -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0}, {0, 0}, {0,  0}, {0, 0}, {0,  0},  {0, 0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0, -3}, {0, 3}, {0, -8}, {0, 8}, {-8, -3}, {-8, 3}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0, 0},  {0, 0}, {0, 0},  {0, 0}, {0,  0},  {0,  0}, {0, 0}, {0, 0}, {0, 0}},
     },
     // [1] FORMATION_DOUBLE_LINE_1 - double line formation (variant 1)
     {
       { {0,  0},  {-6, 0},  {6, 0}, {-6, 2},  {6,  2},  {-2,  4},  {4,  6},  {0, 0}, {0, 0}, {0, 0} ,
         {0,  0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},   {0,  0},  {0, 0}, {0, 0}, {0, 0} },
       { {0,  0},  {0,  -6}, {0, 6}, {2,  -6}, {2,  6},  {4,  -2},  {6,  4},  {0, 0}, {0, 0}, {0, 0} ,
         {0,  0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},   {0,  0},  {0, 0}, {0, 0}, {0, 0} },
       { {0,  0},  {-6, 0},  {6, 0}, {-6, -2}, {6,  -2}, {-4, -6},  {4,  -6}, {0, 0}, {0, 0}, {0, 0} ,
         {0,  0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},   {0,  0},  {0, 0}, {0, 0}, {0, 0} },
       { {0,  0},  {0,  -6}, {0, 6}, {-2, -6}, {-2, 6},  {-6, -4},  {-6, 4},  {0, 0}, {0, 0}, {0, 0} ,
         {0,  0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},   {0,  0},  {0, 0}, {0, 0}, {0, 0} },
     },
     {
       { {0, 0},  {-6, 0},  {6, 0}, {-6, 2},  {6,  2},  {-2, 4},  {4,  6},  {0, 0}, {0, 0}, {0, 0},
         {0, 0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0},  {0, -6},  {0, 6}, {2,  -6}, {2,  6},  {4,  -2}, {6,  4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0},  {-6, 0},  {6, 0}, {-6, -2}, {6,  -2}, {-4, -6}, {4,  -6}, {0, 0}, {0, 0}, {0, 0},
         {0, 0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0},  {0,  -6}, {0, 6}, {-2, -6}, {-2, 6},  {-6, -4}, {-6, 4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0},  {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [2] FORMATION_DOUBLE_LINE_2 - double line formation (variant 2)
     {
       { {0, 0}, {-6, 0},  {6, 0}, {-6, 2},  {6,  2},  {-2, 4},  {4,  6},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -6}, {0, 6}, {2,  -6}, {2,  6},  {4,  -2}, {6,  4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-6, 0},  {6, 0}, {-6, -2}, {6,  -2}, {-4, -6}, {4,  -6}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -6}, {0, 6}, {-2, -6}, {-2, 6},  {-6, -4}, {-6, 4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [3] FORMATION_SINGLE_LINE_1 - single line formation (variant 1)
     {
       { {0, 0}, {-6, 0},  {6, 0}, {-6, 2},  {6,  2}, {-2, 4},  {4,  6},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -6}, {0, 6}, {2,  -6}, {2,  6}, {4,  -2}, {6,  4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-6, 0},  {6, 0}, {-6, -2}, {6, -2}, {-4, -6}, {4,  -6}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0}, { 0,  0}, {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -6}, {0, 6}, {-2, -6}, {-2, 6}, {-6, -4}, {-6, 4},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [4] FORMATION_SINGLE_LINE_2 - single line formation (variant 2)
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [5] FORMATION_TORTOISE - tortoise formation
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [6] FORMATION_MOP_UP - mop-up formation
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [7] FORMATION_AT_REST - formation at rest
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [8] FORMATION_ENEMY_MOB - enemy mob formation
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [9] FORMATION_HERD - herd formation
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     },
     // [10] FORMATION_ENEMY_DOUBLE_LINE - enemy double line formation
     {
       { {0, 0}, {-4, 0},  {4, 0}, {-12, 0},   {12, 0},  {-4,  12},  {4,   12},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,   0},   {0,  0},  {0,   0},   {0,   0},   {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -4}, {0, 4}, {0,   -12}, {0,  12}, {12,  -4},  {12,  4},   {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,   0},   {0,  0},  {0,   0},   {0,   0},   {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-4, 0},  {4, 0}, {-12, 0},   {12, 0},  {-4,  -12}, {4,   -12}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,   0},   {0,  0},  {0,   0},   {0,   0},   {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -4}, {0, 4}, {0,   -12}, {0,  12}, {-12, -4},  {-12, 4},   {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,   0},   {0,  0},  {0,   0},   {0,   0},   {0, 0}, {0, 0}, {0, 0}},
     },
     // [11] FORMATION_ENEMY_WIDE_COLUMN - enemy wide column formation
     {
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, 8},  {3,  8},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {8,  -3}, {8,  3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {-3, 0},  {3, 0}, {-8, 0},  {8, 0}, {-3, -8}, {3,  -8}, {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
       { {0, 0}, {0,  -3}, {0, 3}, {0,  -8}, {0, 8}, {-8, -3}, {-8, 3},  {0, 0}, {0, 0}, {0, 0},
         {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0, 0}, {0,  0},  {0,  0},  {0, 0}, {0, 0}, {0, 0}},
     }
};

static void set_enemy_target_building(formation* m, attacked_buildings& attackd_buildings) {
    if (m->destination_building_id > 0) {
        building *current_target = building_get(m->destination_building_id);
        if (current_target && current_target->state == BUILDING_STATE_VALID) {
            building_id main_bid = current_target->main()->id;
            attackd_buildings.insert({ main_bid, true });
            return;
        }
        m->destination_building_id = 0;
    }

    e_formation_attack_type attack = m->attack_type;
    if (attack == FORMATION_ATTACK_RANDOM) {
        attack = (e_formation_attack_type)(random_byte() % FORMATION_ATTACK_RANDOM);
    }

    auto is_building_attacked = [&] (building* b) -> bool {
        if (!b) return false;
        building_id main_bid = b->main()->id;
        auto it = attackd_buildings.find(main_bid);
        return (it != attackd_buildings.end());
    };

    auto get_best_target = [&] (const stage_attack_weight& weights) {
        building *best_building = nullptr;
        int max_score = -9999;
        for (auto b = building_begin(); b != building_end(); ++b) {
            if (b->state != BUILDING_STATE_VALID || map_soldier_strength_get(b->tile)) {
                continue;
            }

            // Skip buildings that are already being attacked by other formations
            if (is_building_attacked(b)) {
                continue;
            }

            const int weight = weights[b->type];
            if (weight > 0) {
                int distance = calc_maximum_distance(m->home, b->tile);
                int score = weight - distance;
                if (score > max_score) {
                    best_building = b;
                    max_score = score;
                }
            }
        }

        return best_building;
    };

    auto get_closes_buildings = [&] () {
        building *best_building = nullptr;
        int min_distance = 9999;
        for (auto b = building_begin(); b != building_end(); ++b) {
            if (b->state != BUILDING_STATE_VALID || map_soldier_strength_get(b->tile)) {
                continue;
            }

            // Skip buildings that are already being attacked by other formations
            if (is_building_attacked(b)) {
                continue;
            }

            int distance = calc_maximum_distance(m->home, b->tile);
            if (distance < min_distance) {
                best_building = b;
                min_distance = distance;
            }
        }

        return best_building;
    };

    const auto &formation_attack_weights = enemy_attack_rules.priority.get_weights(attack);
    building* best_building = get_best_target(formation_attack_weights);

    if (!best_building) {
        // no target buildings left: take common attack priority
        best_building = get_best_target(enemy_attack_rules.priority.simple_w);
    }

    if (!best_building) {
        // no target building left: take closest for attack
        best_building = get_closes_buildings();
    }

    if (best_building) {
        attackd_buildings.insert({ best_building->id, true });
        m->set_destination_building(best_building->tile, best_building->id);
    }
}

static void set_native_target_building(formation* m) {
    tile2i meeting = city_buildings_main_native_meeting_center();
    building* min_building = 0;
    int min_distance = 10000;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        switch (b->type) {
        case BUILDING_RESERVER_MISSION_POST_80:
        case BUILDING_UNUSED_NATIVE_HUT_88:
        case BUILDING_UNUSED_NATIVE_CROPS_93:
        case BUILDING_UNUSED_NATIVE_MEETING_89:
        case BUILDING_STORAGE_YARD:
        case BUILDING_FORT_ARCHERS:
        case BUILDING_FORT_CHARIOTEERS:
        case BUILDING_FORT_INFANTRY:
        case BUILDING_ROADBLOCK:
            break;

        default: {
            int distance = calc_maximum_distance(meeting, b->tile);
            if (distance < min_distance) {
                min_building = b;
                min_distance = distance;
            }
        }
        }
    }

    if (min_building) {
        m->set_destination_building(min_building->tile, min_building->id);
    }
}

void formation_enemy_approach_target(formation* m) {
    bool can_reach = map_routing_enemy_can_travel_over_land(m->home, m->destination, m->destination_building_id, 400);
    
    if (!can_reach) {
        can_reach = map_routing_noncitizen_can_travel_through_everything(m->home, m->destination);
    }

    if (!can_reach) {
        return;
    }

    tile2i dest;
    const bool found = map_routing_get_closest_tile_within_range(m->home, m->destination, 8, 20, dest);
    if (found) {
        formation_set_destination(m, dest);
    }
}

static void set_enemy_figures_to_initial(const formation* m) {
    for (auto& fid: m->figures) {
        figure* f = figure_get(fid);
        if (!f->is_alive()) {
            continue;
        }
            
        f->dcast()->formation_reset_to_initial(m);
    }
}

formation_destination formation_enemy_move_formation_to(const formation* m, tile2i tile) {
    tile2i base_offset = formation_layout_position(m->layout, 0);
    std::array<tile2i, 50> figure_offsets;
    figure_offsets[0] = tile2i(0, 0);
    for (int i = 1; i < m->num_figures; i++) {
        figure_offsets[i] = formation_layout_position(m->layout, i).sub(base_offset);
    }

    map_routing_enemy_can_travel_over_land(tile, tile2i(-1, -1), 0, 600);
    for (int r = 0; r <= 10; r++) {
        grid_area area = map_grid_get_area(tile, 1, r);

        tile2i ftile = map_grid_area_first(area.tmin, area.tmax, [m, &figure_offsets] (tile2i nt) {
            for (int fig = 0; fig < m->num_figures; fig++) {
                tile2i pr_tile = nt.shifted(figure_offsets[fig]);
                if (!pr_tile.valid()) {                   
                    return false;
                }

                if (map_terrain_is(pr_tile, TERRAIN_IMPASSABLE_ENEMY)) {
                    return false;
                }

                if (map_routing_distance(pr_tile) <= 0) {
                    return false;
                }

                figure_id tile_figure_id = map_figure_id_get(pr_tile);
                if (tile_figure_id && figure_get(tile_figure_id)->formation_id != m->id) {
                    return false;
                }
            }
            return true;
        });

        if (ftile.valid()) {
            return { true, ftile };
        }
    }
    return { false, tile2i::invalid };
}

void formation_seth_kill_enemies() {
    int to_kill = g_city.religion.spirit_of_seth_power();
    if (to_kill <= 0) {
        return;
    }

    int grid_offset = 0;
    for (int i = 1; i < MAX_FIGURES && to_kill > 0; i++) {
        figure* f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE)
            continue;

        if (f->is_enemy() && f->type != FIGURE_RIOTER) {
            f->kill();
            to_kill--;
            if (!grid_offset)
                grid_offset = f->tile.grid_offset();
        }
    }

    g_city.religion.spirit_of_seth_mark_used();
    messages::popup("message_spirit_of_seth", 0, grid_offset);
}

static void update_enemy_movement(formation* m, int roman_distance) {
    const enemy_army& army = g_enemy_armies.get(m->invasion_id);
    formation_state* state = &m->enemy_state;
    int regroup = 0;
    int halt = 0;
    int pursue_target = 0;
    int advance = 0;
    int target_formation_id = 0;
    if (m->missile_fired)
        halt = 1;
    else if (m->missile_attack_timeout) {
        pursue_target = 1;
        target_formation_id = m->missile_attack_formation_id;
    } else if (m->wait_ticks < 32) {
        regroup = 1;
        state->duration_advance = 4;
    } else if (army.ignore_pharaoh_soldiers) {
        halt = 0;
        regroup = 0;
        advance = 1;
    } else {
        int halt_duration, advance_duration, regroup_duration;
        if (army.layout == FORMATION_ENEMY_MOB || army.layout == FORMATION_ENEMY12) {
            switch (m->enemy_batalion_index) {
            case 0:
            case 1:
                regroup_duration = 2;
                advance_duration = 4;
                halt_duration = 2;
                break;
            case 2:
            case 3:
                regroup_duration = 2;
                advance_duration = 5;
                halt_duration = 3;
                break;
            default:
                regroup_duration = 2;
                advance_duration = 6;
                halt_duration = 4;
                break;
            }
            if (!roman_distance) {
                advance_duration += 6;
                halt_duration--;
                regroup_duration--;
            }
        } else {
            if (roman_distance) {
                regroup_duration = 6;
                advance_duration = 4;
                halt_duration = 2;
            } else {
                regroup_duration = 1;
                advance_duration = 12;
                halt_duration = 1;
            }
        }
        if (state->duration_halt) {
            state->duration_advance = 0;
            state->duration_regroup = 0;
            halt = 1;
            state->duration_halt--;
            if (state->duration_halt <= 0) {
                state->duration_regroup = regroup_duration;
                set_enemy_figures_to_initial(m);
                regroup = 0;
                halt = 1;
            }
        } else if (state->duration_regroup) {
            state->duration_advance = 0;
            state->duration_halt = 0;
            regroup = 1;
            state->duration_regroup--;
            if (state->duration_regroup <= 0) {
                state->duration_advance = advance_duration;
                set_enemy_figures_to_initial(m);
                advance = 1;
                regroup = 0;
            }
        } else {
            state->duration_regroup = 0;
            state->duration_halt = 0;
            advance = 1;
            state->duration_advance--;
            if (state->duration_advance <= 0) {
                state->duration_halt = halt_duration;
                set_enemy_figures_to_initial(m);
                halt = 1;
                advance = 0;
            }
        }
    }

    if (m->wait_ticks > 32) {
        formation_seth_kill_enemies();
    }

    if (halt) {
        formation_set_destination(m, m->home);
    } else if (pursue_target) {
        if (target_formation_id > 0) {
            const formation* target = formation_get(target_formation_id);
            if (target->num_figures > 0) {
                formation_set_destination(m, target->home);
            }

        } else {
            formation_set_destination(m, army.destination);
        }

    } else if (regroup) {
        int layout = army.layout;
        tile2i army_home = army.home;
        vec2i offset = LAYOUT_ORIENTATION_OFFSETS[layout][m->orientation / 2][2 * m->enemy_batalion_index];
        auto destination = formation_enemy_move_formation_to(m, army_home.shifted(offset));
        if (destination.valid) {
            formation_set_destination(m, destination.tile);
        }

    } else if (advance) {
        int layout = army.layout;
        tile2i army_destination = army.destination;
        vec2i offset = LAYOUT_ORIENTATION_OFFSETS[layout][m->orientation / 2][2 * m->enemy_batalion_index];
        auto destination = formation_enemy_move_formation_to(m, army_destination.shifted(offset));
        if (destination.valid) {
            formation_set_destination(m, destination.tile);
        }
    }
}

static void update_enemy_formation(formation* m, int* pharaoh_batalion_distance, attacked_buildings& attackd_buildings) {
    enemy_army* army = enemy_army_get_editable(m->invasion_id);
    if (enemy_army_is_stronger_than_batalions()) {
        const auto figure = figure_get<figure_enemy>(m->figure_type);
        army->ignore_pharaoh_soldiers = figure && figure->ignore_pharaoh_soldiers();
    }

    // Проверяем, нужно ли врагам уходить из города
    if (army->buildings_to_destroy > 0 && army->buildings_destroyed >= army->buildings_to_destroy) {
        for (figure_id fid : m->figures) {
            figure* f = figure_get(fid);
            if (f->is_alive() && f->action_state != FIGURE_ACTION_149_CORPSE && 
                f->action_state != FIGURE_ACTION_148_FLEEING && 
                f->action_state != ACTION_156_ENEMY_LEAVING) {
                f->action_state = ACTION_156_ENEMY_LEAVING;
                f->route_remove();
                f->destination_tile = g_city.map.closest_exit_tile_within_radius();
            }
        }
        return;
    }

    formation_decrease_monthly_counters(m);
    if (g_city.figures.soldiers <= 0) {
        formation_clear_monthly_counters(m);
    }

    for (figure_id fid : m->figures) {
        figure* f = figure_get(fid);
        if (f->in_attack()) {
            figure* opponent = figure_get(f->opponent_id);
            if (!opponent->is_dead() && ::smart_cast<figure_soldier>(opponent)) {
                formation_record_fight(m);
            }
        }
    }

    if (formation_has_low_morale(m)) {
        for (figure_id fid : m->figures) {
            figure* f = figure_get(fid);
            if (!f->in_attack() && f->action_state != FIGURE_ACTION_149_CORPSE && f->action_state != FIGURE_ACTION_148_FLEEING) {
                f->action_state = FIGURE_ACTION_148_FLEEING;
                f->route_remove();
            }
        }
        return;
    }

    if (m->figures[0] > 0) {
        figure* f = figure_get(m->figures[0]);
        if (f->state == FIGURE_STATE_ALIVE)
            formation_set_home(m, f->tile);
    }

    if (!army->formation_id) {
        army->formation_id = m->id;
        army->home = m->home;
        army->layout = m->layout;

        *pharaoh_batalion_distance = 0;
        map_routing_enemy_can_travel_over_land(m->home, tile2i(-2, -2), 100000, 300);
   
        auto strength_tile = map_soldier_strength_get_max(m->home, 16);
        if (strength_tile.strength > 0) {
            *pharaoh_batalion_distance = 1;
        } else {
            strength_tile = map_soldier_strength_get_max(m->home, 32);
            if (strength_tile.strength > 0) {
                *pharaoh_batalion_distance = 2;
            }
        }
        
        if (army->ignore_pharaoh_soldiers) {
            *pharaoh_batalion_distance = 0;
        }

        if (*pharaoh_batalion_distance == 1) {
            army->destination = strength_tile.tile;
            army->destination_building_id = 0;
        } else {
            set_enemy_target_building(m, attackd_buildings);
            formation_enemy_approach_target(m);

            army->destination = m->destination;
            army->destination_building_id = m->destination_building_id;
        }
    }

    m->enemy_batalion_index = army->num_batalions++;
    m->wait_ticks++;

    if (m->destination_building_id == 0) {
        set_enemy_target_building(m, attackd_buildings);
        formation_enemy_approach_target(m);

        army->destination = m->destination;
        army->destination_building_id = m->destination_building_id;
    }

    //m->set_destination_building(army->destination, army->destination_building_id);
    update_enemy_movement(m, *pharaoh_batalion_distance);
}

void formation_enemy_update(void) {
    if (enemy_army_total_enemy_formations() <= 0) {
        enemy_armies_clear_ignore_pharaoh_soldiers();
    } else {
        enemy_army_calculate_kingdome_influence();
        g_enemy_armies.clear_formations();
        
        attacked_buildings attackd_buildings;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
            formation* m = formation_get(i);
            if (m->in_use && !m->is_herd && !m->own_batalion && m->destination_building_id > 0) {
                building* target = building_get(m->destination_building_id);
                if (target && target->state == BUILDING_STATE_VALID) {
                    building_id bid = target->main()->id;
                    auto result = attackd_buildings.insert({ bid, true });
                    if (!result.second) {
                        m->destination_building_id = 0;
                    }
                } else {
                    m->destination_building_id = 0;
                }
            }
        }
        
        int pharaoh_batalion_distance = 0;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
            formation* m = formation_get(i);
            if (m->in_use && !m->is_herd && !m->own_batalion) {
                update_enemy_formation(m, &pharaoh_batalion_distance, attackd_buildings);
            }
        }
    }
    set_native_target_building(formation_get(0));
}
