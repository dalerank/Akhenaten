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
#include "figuretype/figure_soldier.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_enemy.h"
#include "figuretype/figure_enemy_transport.h"
#include "city/city_figures.h"
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
#include "scenario/invasion_auto_resolve.h"

// OG enemy_attack_priority / enemy_attack_fallback (figure_data.c:499-511): building types by priority,
// the first type in a list wins, distance only breaks ties within one type.
using stage_attack_rules = svector<uint16_t, 100>;

struct enemy_attack_priority_t {
    stage_attack_rules food_chain;
    stage_attack_rules gold_stores;
    stage_attack_rules best_buildings;
    stage_attack_rules troops;
    stage_attack_rules fallback;

    const stage_attack_rules& get(int kind) const {
        switch (kind) {
        case FORMATION_ATTACK_FOOD_CHAIN:
            return food_chain;
        case FORMATION_ATTACK_GOLD_STORES:
            return gold_stores;
        case FORMATION_ATTACK_BEST_BUILDINGS:
            return best_buildings;
        case FORMATION_ATTACK_TROOPS:
            return troops;
        default:
            return fallback;
        }
    }
};
ANK_CONFIG_STRUCT(enemy_attack_priority_t, food_chain, gold_stores, best_buildings, troops, fallback)

struct enemy_attack_rules_t {
    enemy_attack_priority_t priority;
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

// OG find_target_building (formation_enemy.c:185): reachable buildings without soldiers on them; a type earlier
// in the list wins, the closer building wins within the same type.
static void find_target_building(const formation* m, const stage_attack_rules& list, int& best_index,
  int& best_distance, building_id& best_id) {
    for (auto b = building_begin(); b != building_end(); ++b) {
        if (b->state != BUILDING_STATE_VALID || map_soldier_strength_get(b->tile) != 0
            || map_routing_distance(b->tile) <= 0) {
            continue;
        }
        for (int i = 0; i <= best_index && i < (int)list.size(); i++) {
            if (b->type != list[i]) {
                continue;
            }
            const int distance = calc_maximum_distance(m->home, b->tile);
            if (i < best_index) {
                best_index = i;
                best_distance = distance;
                best_id = b->id;
            } else if (distance < best_distance) {
                best_distance = distance;
                best_id = b->id;
            }
            break;
        }
    }
}

// OG formation_enemy_set_target_building (formation_enemy.c:215). RANDOM draws crt_rand on every call.
static bool set_enemy_target_building(formation* m) {
    int kind = m->attack_type;
    if (kind == FORMATION_ATTACK_RANDOM) {
        kind = anti_scum_random_15bit() & 3;
    }

    constexpr int list_length = 100;
    int best_index = list_length;
    int best_distance = 10000;
    building_id best_id = 0;
    // Fill the distance grid from the formation; tile2i(-2, -2) would be a real tile and stop the search there.
    map_routing_noncitizen_can_travel_through_everything(m->home, tile2i::invalid);
    find_target_building(m, enemy_attack_rules.priority.get(kind), best_index, best_distance, best_id);
    if (best_id <= 0) {
        find_target_building(m, enemy_attack_rules.priority.fallback, best_index, best_distance, best_id);
        if (best_id <= 0) {
            return false;
        }
    }

    building* b = building_get(best_id);
    if (b->type != BUILDING_STORAGE_YARD && b->type != BUILDING_STORAGE_YARD_UP) {
        m->set_destination_building(b->tile, best_id);
        return true;
    }
    // OG aims at the yard's first room, one tile right of the yard (id + 1 there).
    const building_id room = b->next_part_building_id > 0 ? b->next_part_building_id : best_id;
    m->set_destination_building(b->tile.shifted(1, 0), room);
    return true;
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

        tile2i ftile = map_grid_area_first(area, [m, &figure_offsets] (tile2i nt) {
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

// OG formation.c ENEMY_* constants (formation.h:99-139).
enum {
    ENEMY_FORMATION_GATHER_TICKS = 32,
    ENEMY_FORMATION_FLEE_CHECK_TICKS = 45,
    ENEMY_FORMATION_MAX_TICKS_WITHOUT_TARGET = 48,
    ENEMY_CYCLE_GATHER_REGROUP = 4,
    ENEMY_CYCLE_ADVANCE = 6,
    ENEMY_CYCLE_REGROUP = 4,
    ENEMY_CYCLE_HALT = 2,
    ENEMY_CYCLE_NO_TARGET_ADVANCE = 1,
    ENEMY_CYCLE_NO_TARGET_REGROUP = 12,
    ENEMY_CYCLE_NO_TARGET_HALT = 1,
    ENEMY_MOB_CYCLE_ADVANCE = 2,
    ENEMY_MOB_CYCLE_FRONT_REGROUP = 4,
    ENEMY_MOB_CYCLE_FRONT_HALT = 2,
    ENEMY_MOB_CYCLE_MIDDLE_REGROUP = 5,
    ENEMY_MOB_CYCLE_MIDDLE_HALT = 3,
    ENEMY_MOB_CYCLE_BACK_REGROUP = 6,
    ENEMY_MOB_CYCLE_BACK_HALT = 4,
    ENEMY_MOB_CYCLE_NO_TARGET_EXTRA_REGROUP = 6,
    ENEMY_SOLDIERS_NEAR_RADIUS = 16,
    ENEMY_SOLDIERS_FAR_RADIUS = 32,
};

enum e_enemy_target_found {
    ENEMY_TARGET_NONE = 0,
    ENEMY_TARGET_SOLDIERS_NEAR = 1,
    ENEMY_TARGET_SOLDIERS_FAR = 2,
};

// OG formation_enemy_update after the target (formation.c:620-719). OG calls the counters regroup/advance/halt:
// "advance" walks the formation to its spot around the army home, the regroup phase keeps the destination on
// the army target, so the army marches.
static void update_enemy_movement(formation* m, int target_found) {
    const enemy_army& army = g_enemy_armies.get(m->invasion_id);
    formation_state* state = &m->enemy_state;
    int& regroup = state->duration_regroup;
    int& advance = state->duration_advance;
    int& halt = state->duration_halt;

    bool hold_position = false;
    bool move_to_spot = false;
    bool follow_target = false;
    int target_formation_id = 0;
    if (m->missile_fired) {
        hold_position = true;
    } else if (m->missile_attack_timeout) {
        follow_target = true;
        target_formation_id = m->missile_attack_formation_id;
    } else if (m->wait_ticks < ENEMY_FORMATION_GATHER_TICKS) {
        move_to_spot = true;
        regroup = ENEMY_CYCLE_GATHER_REGROUP;
    } else if (army.ignore_pharaoh_soldiers) {
        move_to_spot = false;
    } else {
        int next_halt, next_regroup, next_advance;
        if (army.layout == FORMATION_ENEMY_MOB || army.layout == FORMATION_ENEMY12) {
            const int index = m->enemy_batalion_index;
            next_advance = ENEMY_MOB_CYCLE_ADVANCE;
            if (index == 0 || index == 1) {
                next_regroup = ENEMY_MOB_CYCLE_FRONT_REGROUP;
                next_halt = ENEMY_MOB_CYCLE_FRONT_HALT;
            } else if (index == 2 || index == 3) {
                next_regroup = ENEMY_MOB_CYCLE_MIDDLE_REGROUP;
                next_halt = ENEMY_MOB_CYCLE_MIDDLE_HALT;
            } else {
                next_regroup = ENEMY_MOB_CYCLE_BACK_REGROUP;
                next_halt = ENEMY_MOB_CYCLE_BACK_HALT;
            }
            if (target_found == ENEMY_TARGET_NONE) {
                next_regroup += ENEMY_MOB_CYCLE_NO_TARGET_EXTRA_REGROUP;
                next_halt--;
                next_advance = ENEMY_CYCLE_NO_TARGET_ADVANCE;
            }
        } else if (target_found == ENEMY_TARGET_NONE) {
            next_advance = ENEMY_CYCLE_NO_TARGET_ADVANCE;
            next_regroup = ENEMY_CYCLE_NO_TARGET_REGROUP;
            next_halt = ENEMY_CYCLE_NO_TARGET_HALT;
        } else {
            next_advance = ENEMY_CYCLE_ADVANCE;
            next_regroup = ENEMY_CYCLE_REGROUP;
            next_halt = ENEMY_CYCLE_HALT;
        }

        if (halt) {
            hold_position = true;
            regroup = 0;
            advance = 0;
            if (--halt <= 0) {
                advance = next_advance;
                set_enemy_figures_to_initial(m);
            }
        } else if (advance) {
            regroup = 0;
            halt = 0;
            move_to_spot = true;
            if (--advance <= 0) {
                regroup = next_regroup;
                set_enemy_figures_to_initial(m);
                move_to_spot = false;
            }
        } else {
            advance = 0;
            halt = 0;
            if (--regroup <= 0) {
                halt = next_halt;
                set_enemy_figures_to_initial(m);
                hold_position = true;
            }
        }
    }

    if (m->wait_ticks > ENEMY_FORMATION_FLEE_CHECK_TICKS) {
        formation_seth_kill_enemies();
    }

    if (hold_position) {
        formation_set_destination(m, m->home);
    } else if (follow_target) {
        if (target_formation_id <= 0) {
            formation_set_destination(m, army.destination);
        } else {
            const formation* target = formation_get(target_formation_id);
            if (target->num_figures > 0) {
                formation_set_destination(m, target->home);
            }
        }
    } else if (move_to_spot) {
        const vec2i offset = LAYOUT_ORIENTATION_OFFSETS[army.layout][m->orientation / 2][m->enemy_batalion_index];
        tile2i army_home = army.home;
        auto destination = formation_enemy_move_formation_to(m, army_home.shifted(offset));
        if (destination.valid) {
            formation_set_destination(m, destination.tile);
        }
    }
}

// OG formation_enemy_update for one enemy formation (formation.c:539-619). target_found lives across the loop
// like the OG local: the first formation of each invasion sets it, the others reuse it.
void formations_t::update_enemy_formation(formation* m, int* target_found) {
    enemy_army* army = enemy_army_get_editable(m->invasion_id);
    if (enemy_army_is_stronger_than_batalions()) {
        army->ignore_pharaoh_soldiers = true;
    }

    if (army->buildings_to_destroy > 0 && army->buildings_destroyed >= army->buildings_to_destroy) {
        // Still embarked: dismiss cargo instead of leave_city (glue would undo ACTION_156).
        if (m->is_halted) {
            for (figure *ship : map_figures()) {
                auto *t = smart_cast<figure_enemy_transport>(ship);
                if (t && t->is_alive() && t->transported_formation() == m->id) {
                    t->dismiss_cargo();
                    // Withdraw empty hull — do not leave an idle enemy transport.
                    t->poof();
                }
            }
            return;
        }

        for (figure_id fid : m->figures) {
            figure_enemy *f = figure_get(fid)->dcast_enemy();
            if (f && f->is_alive()) {
                f->leave_city();
                f->route_remove();
            }
        }
        return;
    }

    // Halted while embarked on an enemy transport — do not pick targets or march.
    if (m->is_halted) {
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

    if (m->has_low_morale()) {
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
        if (f->state == FIGURE_STATE_ALIVE) {
            m->home = f->tile;
        }
    }

    // Only the first formation of an invasion picks the army target; the others follow it.
    if (!army->formation_id) {
        army->formation_id = m->id;
        army->home = m->home;
        army->layout = m->layout;

        *target_found = ENEMY_TARGET_NONE;
        map_routing_enemy_can_travel_over_land(m->home, tile2i(-2, -2), 100000, 300);
        auto strength_tile = map_soldier_strength_get_max(m->home, ENEMY_SOLDIERS_NEAR_RADIUS);
        if (strength_tile.strength > 0) {
            *target_found = ENEMY_TARGET_SOLDIERS_NEAR;
        } else if (map_soldier_strength_get_max(m->home, ENEMY_SOLDIERS_FAR_RADIUS).strength > 0) {
            *target_found = ENEMY_TARGET_SOLDIERS_FAR;
        }

        if (!army->ignore_pharaoh_soldiers && *target_found == ENEMY_TARGET_SOLDIERS_NEAR) {
            army->destination = strength_tile.tile;
            army->destination_building_id = 0;
        } else {
            if (army->ignore_pharaoh_soldiers) {
                *target_found = ENEMY_TARGET_NONE;
            }
            if (set_enemy_target_building(m)) {
                m->ticks_without_target = 0;
            } else if (++m->ticks_without_target > ENEMY_FORMATION_MAX_TICKS_WITHOUT_TARGET) {
                m->months_low_morale = 1;
            }
            army->destination = m->destination;
            army->destination_building_id = m->destination_building_id;
        }
    }

    m->enemy_batalion_index = army->num_batalions++;
    m->wait_ticks++;
    m->set_destination_building(army->destination, army->destination_building_id);

    update_enemy_movement(m, *target_found);
}

void formations_t::enemy_update() {
    if (enemy_army_total_enemy_formations() <= 0) {
        enemy_armies_clear_ignore_pharaoh_soldiers();
    } else {
        g_enemy_army_in_city.calculate_kingdome_influence();
        g_enemy_armies.clear_formations();

        int target_found = ENEMY_TARGET_NONE;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
            formation *m = formation_get(i);
            if (m->in_use && !m->is_herd && !m->own_batalion) {
                if (g_invasion_auto_resolve.is_formation_frozen(m)) {
                    continue;
                }
                update_enemy_formation(m, &target_found);
            }
        }
    }
    set_native_target_building(formation_get(0));
}
