#pragma once

#include "core/vec2i.h"
#include "grid/point.h"
#include "figure/formation.h"
#include "figure/figure_type.h"
#include "core/archive.h"
#include "core/tokenum.h"

#include <array>

enum e_attack_faction {
    ATTACK_TYPE_ENEMIES = 0,
    ATTACK_TYPE_KINGDOME = 1,
    ATTACK_TYPE_NATIVES = 2,
    ATTACK_TYPE_MAX
};
using e_attack_faction_tokens_t = token_holder<e_attack_faction, ATTACK_TYPE_ENEMIES, ATTACK_TYPE_MAX>;
extern const e_attack_faction_tokens_t e_attack_faction_tokens;

// Spawn classification for Enhanced auto-resolve (not the same as mode).
enum e_invasion_spawn_kind : uint8_t {
    INVASION_KIND_FOREIGN = 0,
    INVASION_KIND_PHARAOH = 1,
    INVASION_KIND_KINGDOME = 2,
    INVASION_KIND_UPRISING = 3,
    INVASION_KIND_NATIVES = 4,
    INVASION_KIND_MAX
};
using e_invasion_spawn_kind_tokens_t = token_holder<e_invasion_spawn_kind, INVASION_KIND_FOREIGN, INVASION_KIND_MAX>;
extern const e_invasion_spawn_kind_tokens_t e_invasion_spawn_kind_tokens;

struct invasion_warning_t {
    bool in_use;
    bool handled;
    int invasion_path_id;
    int warning_years;
    vec2i pos;
    int image_id;
    int empire_object_id;
    int year_notified;
    int month_notified;
    int months_to_go;
    int invasion_id;
};

struct invasion_opts_t {
    e_attack_faction mode = ATTACK_TYPE_ENEMIES;
    e_enemy_type enemy_type = ENEMY_0_BARBARIAN;
    e_invasion_spawn_kind kind = INVASION_KIND_FOREIGN;
    int size = 0;
    int invasion_id = 0;
    // FORMATION_ATTACK_*; pak EVENT_ATTACK_TARGET_RANDOM(4) maps to FORMATION_ATTACK_RANDOM(5)
    e_formation_attack_type attack_type = FORMATION_ATTACK_RANDOM;
    tile2i invasion_point;
    uint8_t want_destroy = 0;
    // Optional resolve branches (JS tags → ONLY_VIA chain events). 0 = none.
    uint16_t on_completed_tag = 0;
    uint16_t on_refusal_tag = 0;
    uint16_t on_defeat_tag = 0;
    // E3c: sea invasion orchestration (transports + escort). Explicit flag or
    // invasion_point in invasion_points_sea / water — never auto land-empty→sea.
    bool via_sea = false;
    int8_t sea_point_index = -1; // -1 = pick random valid sea point
    // false: the caller posts the attack message (OG event path posts message 133 with event phrases).
    bool announce = true;
};

// Map pak/JS invasion_attack_target (EVENT_ATTACK_TARGET_*) → formation attack_type.
e_formation_attack_type formation_attack_from_event_target(int invasion_attack_target);

enum e_invasion_outcome : uint8_t {
    INVASION_OUTCOME_NONE = 0,       // active / unknown
    INVASION_OUTCOME_COMPLETED = 1,  // wipe / ok-only
    INVASION_OUTCOME_REFUSED = 2,    // destroy-goal + refusal tag
    INVASION_OUTCOME_DEFEAT = 3,
};

// Active mid-fight bind: fire chain tags after seen → wipe / destroy-goal.
struct invasion_bind_t {
    bool in_use = false;
    bool enemies_seen = false;
    uint8_t invasion_id = 0;
    uint16_t seq = 0; // last_internal_invasion_id at spawn
    uint16_t on_completed_tag = 0;
    uint16_t on_refusal_tag = 0;
    uint16_t on_defeat_tag = 0;
};

// Audit / debug / future UI — not gameplay source of truth.
struct invasion_history_entry_t {
    uint16_t seq = 0;
    int16_t year = 0; // years_since_start
    int8_t month = 0;
    uint8_t invasion_id = 0;
    uint8_t enemy_type = 0;
    uint8_t mode = 0;
    uint8_t attack_type = 0;
    uint16_t size = 0;
    int16_t tile_x = -1;
    int16_t tile_y = -1;
    uint8_t want_destroy = 0;
    uint8_t outcome = INVASION_OUTCOME_NONE;
};

struct enemy_properties_t {
    int percentage_type1;
    int percentage_type2;
    int percentage_type3;
    std::array<e_figure_type, 3> figure_types;
    xstring army_title;
    e_formation_layout layout;
};
ANK_CONFIG_STRUCT(enemy_properties_t, percentage_type1, percentage_type2, percentage_type3, figure_types, army_title, layout)

struct invasion_data_t {
    enum {
        MAX_ACTIVE_BINDS = 16,
        MAX_HISTORY = 64,
    };

    int last_internal_invasion_id;
    int min_invasion_amount;
    int max_invasion_amount;
    std::array<invasion_warning_t, 101> warnings;
    std::array<invasion_bind_t, MAX_ACTIVE_BINDS> binds;
    std::array<invasion_history_entry_t, MAX_HISTORY> history;
    int history_count = 0; // total ever written (may exceed MAX_HISTORY)
    int history_next = 0;  // next write index in ring

    void clear();
    void init();

    const enemy_properties_t &get_prop(e_enemy_type type);

    // After successful spawn: history row + optional bind from opts tags.
    void record_spawn(const invasion_opts_t &opts, tile2i tile, int size_after_clamp);
    void process_bind_resolutions(); // month tick: seen → wipe/refuse → fire_chain(tag)

    int history_entry_count() const;
    const invasion_history_entry_t *history_at(int index) const; // 0 = oldest retained
};
ANK_CONFIG_STRUCT(invasion_data_t, min_invasion_amount, max_invasion_amount)
extern invasion_data_t g_invasions;

extern const int LOCAL_UPRISING_NUM_ENEMIES[20];


bool scenario_invasion_exists_upcoming();
int city_own_warships();
bool scenario_invasion_city_undefended();

int scenario_invasion_count();

// Spawns kingdom army; on success writes difficulty-adjusted size back to `size`.
bool scenario_invasion_start_from_kingdome(int &size);

// Returns last_internal_invasion_id (seq) after successful spawn, or 0 on failure.
int scenario_invasion_start(invasion_opts_t opts);

void scenario_invasion_process();

int map_invasion_point(tile2i point);

// Adjusts opts.size in-place (difficulty clamp) before spawning.
tile2i scenario_start_invasion_impl(invasion_opts_t &opts);
tile2i scenario_start_sea_invasion_impl(invasion_opts_t &opts);

// OG invasion_land_point(INVASION_POINT_RANDOM): masks the current random1_7bit without advancing the RNG.
int scenario_invasion_land_point_index();
// OG invasion_sea_point: deterministic forward scan over invasion_points_sea, wrapping.
int scenario_invasion_sea_point_index(int start);
// OG invasion_start_sea landing roll; -1 (and no RNG step) when there are no disembark points.
int scenario_invasion_landing_index();

// Force bind/history outcome for a spawn seq (auto-resolve, cheats, etc.).
// COMPLETED → on_completed_tag; DEFEAT → on_defeat_tag; NONE → clear bind, no tags.
void invasion_force_outcome(uint16_t seq, e_invasion_outcome outcome);
