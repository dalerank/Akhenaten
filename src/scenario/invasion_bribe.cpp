#include "invasion_bribe.h"

#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "core/log.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "figure/formation.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "grid/figure.h"
#include "js/js_game.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/scenario_invasion.h"

#include <algorithm>

namespace {

enum e_bribe_unit_class : uint8_t {
    BRIBE_INFANTRY = 0,
    BRIBE_ARCHER = 1,
    BRIBE_MOUNTED = 2,
    BRIBE_TRANSPORT = 3,
    BRIBE_WARSHIP = 4,
    BRIBE_UNKNOWN = 5,
};

constexpr int k_base_rate[] = { 20, 25, 80, 150, 200, 20 };
constexpr int k_diff_mult[] = { 5, 7, 10, 14, 20 };
constexpr int k_kingdom_penalty = 2;

// Standard 5-slot nation pack: [0]=ranged-or-melee, [1]=melee, [2]=transport, [3]=warship, [4]=chariot.
e_bribe_unit_class classify_pack5(e_figure_type base, e_figure_type t, bool slot0_archer) {
    const int slot = (int)t - (int)base;
    switch (slot) {
    case 0: return slot0_archer ? BRIBE_ARCHER : BRIBE_INFANTRY;
    case 1: return BRIBE_INFANTRY;
    case 2: return BRIBE_TRANSPORT;
    case 3: return BRIBE_WARSHIP;
    case 4: return BRIBE_MOUNTED;
    default: return BRIBE_UNKNOWN;
    }
}

e_bribe_unit_class classify_figure(e_figure_type t) {
    switch (t) {
    case FIGURE_ENEMY_TRANSPORT:
    case FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP:
    case FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP:
        return BRIBE_TRANSPORT;
    case FIGURE_ENEMY_WARSHIP:
    case FIGURE_ENEMY_EGYPTIAN_WARSHIP:
    case FIGURE_ENEMY_EGYPTIAN_GALERA:
        return BRIBE_WARSHIP;
    case FIGURE_ENEMY_EGYPTIAN_ARCHER:
    case FIGURE_ENEMY_KINGDOME_JAVELIN:
    case FIGURE_ENEMY_BARBARIAN_ARCHER:
        return BRIBE_ARCHER;
    case FIGURE_ENEMY_EGYPTIAN_CAMEL:
    case FIGURE_ENEMY_EGYPTIAN_ELEPHANT:
    case FIGURE_ENEMY_EGYPTIAN_CHARIOT:
    case FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER:
    case FIGURE_ENEMY_KINGDOME_MOUNTED:
        return BRIBE_MOUNTED;
    case FIGURE_ENEMY_BARBARIAN_SWORD:
        return BRIBE_INFANTRY;
    default:
        break;
    }

    if (t >= FIGURE_ENEMY_CANAANITE_ARCHER && t <= FIGURE_ENEMY_CANAANITE_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_CANAANITE_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_KUSHITE_SPEARMAN && t <= FIGURE_ENEMY_KUSHITE_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_KUSHITE_SPEARMAN, t, false);
    if (t >= FIGURE_ENEMY_HITTITE_ARCHER && t <= FIGURE_ENEMY_HITTITE_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_HITTITE_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_PERSIAN_ARCHER && t <= FIGURE_ENEMY_PERSIAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_PERSIAN_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_ASSYRIAN_ARCHER && t <= FIGURE_ENEMY_ASSYRIAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_ASSYRIAN_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_LIBIAN_ARCHER && t <= FIGURE_ENEMY_LIBIAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_LIBIAN_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_NUBIAN_ARCHER && t <= FIGURE_ENEMY_NUBIAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_NUBIAN_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_PHOENICIAN_SPEARMAN && t <= FIGURE_ENEMY_PHOENICIAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_PHOENICIAN_SPEARMAN, t, false);
    if (t >= FIGURE_ENEMY_ROMAN_ARCHER && t <= FIGURE_ENEMY_ROMAN_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_ROMAN_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_SEAPEOPLE_ARCHER && t <= FIGURE_ENEMY_SEAPEOPLE_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_SEAPEOPLE_ARCHER, t, true);
    if (t >= FIGURE_ENEMY_HYKSOS_ARCHER && t <= FIGURE_ENEMY_HYKSOS_CHARIOT)
        return classify_pack5(FIGURE_ENEMY_HYKSOS_ARCHER, t, true);

    if (t >= FIGURE_ENEMY_EGYPTIAN_SPEAR && t <= FIGURE_ENEMY_EGYPTIAN_AXE) {
        return BRIBE_INFANTRY;
    }
    if (t == FIGURE_ENEMY_KINGDOME_INFANTRY) {
        return BRIBE_INFANTRY;
    }
    return BRIBE_UNKNOWN;
}

int difficulty_mult() {
    const int d = (int)game.difficulty();
    if (d < DIFFICULTY_VERY_EASY || d > DIFFICULTY_VERY_HARD) {
        return k_diff_mult[DIFFICULTY_NORMAL];
    }
    return k_diff_mult[d];
}

bool formation_matches_seq(const formation *m, uint16_t seq) {
    return m && m->in_use && !m->own_batalion && !m->is_herd
        && (uint16_t)m->invasion_sequence == seq;
}

bool seq_has_kingdome_army(uint16_t seq) {
    for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
        formation *m = formation_get(fi);
        if (!formation_matches_seq(m, seq)) {
            continue;
        }
        if (figure_is_kingdome_army(m->figure_type)) {
            return true;
        }
    }
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || !figure_is_kingdome_army(f->type)) {
            continue;
        }
        if (f->formation_id > 0 && formation_matches_seq(formation_get(f->formation_id), seq)) {
            return true;
        }
    }
    return false;
}

bool history_mode_blocked(uint16_t seq) {
    for (int i = 0; i < invasion_data_t::MAX_HISTORY; ++i) {
        const auto &h = g_invasions.history[i];
        if (h.seq != seq || h.seq == 0) {
            continue;
        }
        if (h.mode == ATTACK_TYPE_NATIVES || h.mode == ATTACK_TYPE_KINGDOME) {
            return true;
        }
        return false;
    }
    return false;
}

int count_alive_for_seq(uint16_t seq) {
    int n = 0;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive()) {
            continue;
        }
        if (f->formation_id > 0) {
            if (formation_matches_seq(formation_get(f->formation_id), seq)) {
                ++n;
                continue;
            }
        }
        if (auto *t = smart_cast<figure_enemy_transport>(f)) {
            if ((uint16_t)t->invasion_sequence() == seq) {
                ++n;
            }
            continue;
        }
        if (auto *w = smart_cast<figure_enemy_warship>(f)) {
            if ((uint16_t)w->invasion_sequence() == seq) {
                ++n;
            }
        }
    }
    return n;
}

bool figure_belongs_to_seq(figure *f, uint16_t seq) {
    if (!f || !f->is_alive()) {
        return false;
    }
    if (f->formation_id > 0 && formation_matches_seq(formation_get(f->formation_id), seq)) {
        return true;
    }
    if (auto *t = smart_cast<figure_enemy_transport>(f)) {
        return (uint16_t)t->invasion_sequence() == seq;
    }
    if (auto *w = smart_cast<figure_enemy_warship>(f)) {
        return (uint16_t)w->invasion_sequence() == seq;
    }
    return false;
}

int compute_cost(uint16_t seq) {
    int units_cost = 0;
    for (figure *f : map_figures()) {
        if (!figure_belongs_to_seq(f, seq)) {
            continue;
        }
        units_cost += k_base_rate[classify_figure(f->type)];
    }
    if (units_cost <= 0) {
        return 0;
    }
    return units_cost * difficulty_mult();
}

int clamp_bribe_cost(int cost_raw) {
    if (cost_raw <= 0) {
        return 0;
    }
    // Soft cap so a single bribe cannot dwarf a city treasury / uint16 expense lines.
    return std::min(cost_raw, 60000);
}

void pay_bribe_deben(int cost) {
    // Debit treasury in full. Saturate disasters uint16 so a full line never blocks bribe
    // and never wraps the advisor value.
    g_city.finance.treasury -= cost;
    uint16_t &disasters = g_city.finance.this_year.expenses.disasters;
    const int sum = (int)disasters + cost;
    disasters = (uint16_t)std::min(sum, 65535);
    finance_system::calculate_totals(g_city.finance);
}

uint16_t resolve_seq(uint16_t seq) {
    if (seq) {
        return seq;
    }
    const auto *head = g_invasion_auto_resolve.head_pending();
    return head ? head->seq : 0;
}

} // namespace

bool invasion_bribe_feature_on() {
    return game_features::gameplay_enhanced_invasion_bribe.to_bool();
}

bool invasion_bribe_allowed(uint16_t seq) {
    if (!invasion_bribe_feature_on()) {
        return false;
    }
    seq = resolve_seq(seq);
    if (!seq) {
        return false;
    }
    if (seq_has_kingdome_army(seq) || history_mode_blocked(seq)) {
        return false;
    }
    return count_alive_for_seq(seq) > 0;
}

int invasion_bribe_cost(uint16_t seq) {
    if (!invasion_bribe_feature_on()) {
        return 0;
    }
    seq = resolve_seq(seq);
    if (!seq || !invasion_bribe_allowed(seq)) {
        return 0;
    }
    return clamp_bribe_cost(compute_cost(seq));
}

int invasion_bribe_try(uint16_t seq) {
    if (!invasion_bribe_feature_on()) {
        return 0;
    }
    seq = resolve_seq(seq);
    if (!seq || !invasion_bribe_allowed(seq)) {
        return 0;
    }

    const int cost = clamp_bribe_cost(compute_cost(seq));
    if (cost <= 0) {
        return 0;
    }
    if (g_city.finance.treasury < cost) {
        return 0;
    }

    pay_bribe_deben(cost);
    g_city.kingdome.change(-k_kingdom_penalty);

    // Clear bind / auto-resolve pending before despawn so month-tick cannot fake COMPLETED
    // and calculate_figures→sweep does not double-handle this seq.
    if (g_invasion_auto_resolve.is_seq_frozen(seq)) {
        g_invasion_auto_resolve.cancel_vanished(seq);
    } else {
        invasion_force_outcome(seq, INVASION_OUTCOME_NONE);
    }

    invasion_despawn_by_seq(seq);

    events::emit(event_message{ true, "message_invasion_bribe_withdraw", seq, 0, SOURCE_LOCATION });
    logs::info("akhenaten: invasion bribe seq=%u cost=%d", seq, cost);
    return 1;
}

// --- JS / tests ---

int __invasion_bribe_feature_on() {
    return invasion_bribe_feature_on() ? 1 : 0;
}
ANK_FUNCTION(__invasion_bribe_feature_on)

int __invasion_bribe_allowed(int seq) {
    return invasion_bribe_allowed((uint16_t)seq) ? 1 : 0;
}
ANK_FUNCTION_1(__invasion_bribe_allowed)

int __invasion_bribe_cost(int seq) {
    return invasion_bribe_cost((uint16_t)seq);
}
ANK_FUNCTION_1(__invasion_bribe_cost)

int __invasion_bribe_try(int seq) {
    return invasion_bribe_try((uint16_t)seq);
}
ANK_FUNCTION_1(__invasion_bribe_try)
