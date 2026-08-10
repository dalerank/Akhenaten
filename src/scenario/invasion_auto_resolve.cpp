#include "invasion_auto_resolve.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/log.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "figure/formation.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "grid/figure.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "window/autoconfig_window.h"
#include "window/window_city.h"
#include "graphics/window.h"
#include "city/city_warnings.h"

#include <cstring>

invasion_auto_resolve_t g_invasion_auto_resolve;

// Test-only: >=0 overrides player_strength(); -1 = live count.
static int s_test_player_str_override = -1;

// Favour bookkeeping is global (favour_only). Only skip auto-resolve ±KR for the
// kingdom-army wave itself — not for a FOREIGN/PHARAOH wave still queued behind it.
static bool invasion_seq_is_kingdome_army(uint16_t seq) {
    if (!seq) {
        return false;
    }
    for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
        formation *m = formation_get(fi);
        if (!m || !m->in_use || m->own_batalion || m->is_herd) {
            continue;
        }
        if ((uint16_t)m->invasion_sequence != seq) {
            continue;
        }
        if (figure_is_kingdome_army(m->figure_type)) {
            return true;
        }
    }
    return false;
}

// Alive kingdom-army figures still on the map (any invasion seq).
static int count_alive_kingdome_army_figures() {
    int n = 0;
    for (figure *f : map_figures()) {
        if (f && f->is_alive() && figure_is_kingdome_army(f->type)) {
            ++n;
        }
    }
    return n;
}

static void despawn_sea_fleet_by_seq(uint16_t seq) {
    if (!seq) {
        return;
    }
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive()) {
            continue;
        }
        if (auto *t = smart_cast<figure_enemy_transport>(f)) {
            if ((uint16_t)t->invasion_sequence() == seq) {
                t->kill();
            }
            continue;
        }
        if (auto *w = smart_cast<figure_enemy_warship>(f)) {
            if ((uint16_t)w->invasion_sequence() == seq) {
                w->kill();
            }
        }
    }
}

void invasion_despawn_by_seq(uint16_t seq) {
    if (!seq) {
        return;
    }
    for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
        formation *m = formation_get(fi);
        if (!m || !m->in_use || m->own_batalion || m->is_herd) {
            continue;
        }
        if ((uint16_t)m->invasion_sequence != seq) {
            continue;
        }
        for (int fig = 0; fig < formation::max_figures_count; ++fig) {
            int fid = m->figures[fig];
            if (fid > 0) {
                figure *f = figure_get(fid);
                if (f && f->is_alive()) {
                    f->poof();
                }
            }
        }
        g_formations.clear(fi);
    }
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || !f->is_enemy() || f->formation_id <= 0) {
            continue;
        }
        formation *m = formation_get(f->formation_id);
        if (m && (uint16_t)m->invasion_sequence == seq) {
            f->poof();
        }
    }
    despawn_sea_fleet_by_seq(seq);
    g_formations.calculate_figures();
}

static void kill_own_batalions_pct(int kill_percentage) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m || !m->in_use || !m->own_batalion || m->in_distant_battle) {
            continue;
        }
        if (m->num_figures <= 0) {
            continue;
        }

        int soldiers_total = 0;
        for (int fig = 0; fig < m->num_figures; fig++) {
            if (m->figures[fig] > 0) {
                figure *f = figure_get(m->figures[fig]);
                if (f && !f->is_dead()) {
                    soldiers_total++;
                }
            }
        }
        int soldiers_to_kill = calc_adjust_with_percentage(soldiers_total, kill_percentage);
        for (int fig = 0; fig < m->num_figures; fig++) {
            if (m->figures[fig] <= 0 || soldiers_to_kill <= 0) {
                continue;
            }
            figure *f = figure_get(m->figures[fig]);
            if (f && !f->is_dead()) {
                soldiers_to_kill--;
                f->poof();
            }
        }
    }
    g_formations.calculate_figures();
}

static int distant_pct_loss(int player_str, int enemy_str) {
    if (player_str < enemy_str) {
        return 100;
    }
    int pct_advantage = calc_percentage<int>(player_str - enemy_str, player_str);
    if (pct_advantage < 10)
        return 70;
    if (pct_advantage < 25)
        return 50;
    if (pct_advantage < 50)
        return 25;
    if (pct_advantage < 75)
        return 15;
    if (pct_advantage < 100)
        return 10;
    if (pct_advantage < 150)
        return 5;
    return 0;
}

void invasion_auto_resolve_t::clear() {
    for (auto &p : queue) {
        p = {};
    }
    order = {};
    count = 0;
}

bool invasion_auto_resolve_t::is_seq_frozen(uint16_t seq) const {
    if (!seq || count <= 0) {
        return false;
    }
    for (int i = 0; i < count; ++i) {
        const auto &p = queue[order[i]];
        if (p.in_use && p.seq == seq) {
            return true;
        }
    }
    return false;
}

bool invasion_auto_resolve_t::is_formation_frozen(const formation *m) const {
    if (!m || !m->in_use || m->own_batalion || m->is_herd) {
        return false;
    }
    return is_seq_frozen((uint16_t)m->invasion_sequence);
}

const invasion_auto_resolve_pending_t *invasion_auto_resolve_t::head_pending() const {
    if (count <= 0) {
        return nullptr;
    }
    const auto &p = queue[order[0]];
    return p.in_use ? &p : nullptr;
}

invasion_auto_resolve_pending_t *invasion_auto_resolve_t::head_pending_mut() {
    if (count <= 0) {
        return nullptr;
    }
    auto &p = queue[order[0]];
    return p.in_use ? &p : nullptr;
}

int invasion_auto_resolve_t::player_strength() const {
    if (s_test_player_str_override >= 0) {
        return s_test_player_str_override;
    }
    int total = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m || !m->in_use || !m->own_batalion || m->in_distant_battle) {
            continue;
        }
        if (m->num_figures <= 0) {
            continue;
        }
        int str = m->num_figures;
        if (m->figure_type == FIGURE_STANDARD_BEARER) {
            str += m->num_figures / 2;
        }
        total += str;
    }
    return total;
}

int invasion_auto_resolve_t::enemy_strength_for_seq(uint16_t seq) const {
    int total = 0;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || !f->is_enemy() || f->formation_id <= 0) {
            continue;
        }
        formation *m = formation_get(f->formation_id);
        if (m && m->in_use && !m->own_batalion && (uint16_t)m->invasion_sequence == seq) {
            total++;
        }
    }
    if (total > 0) {
        return total;
    }
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m || !m->in_use || m->own_batalion || m->is_herd) {
            continue;
        }
        if ((uint16_t)m->invasion_sequence != seq) {
            continue;
        }
        total += m->num_figures;
    }
    return total;
}

void invasion_auto_resolve_t::force_outcome(uint16_t seq, e_invasion_outcome outcome) {
    invasion_force_outcome(seq, outcome);
}

static void remove_order_index(invasion_auto_resolve_t &ar, int slot_order) {
    if (slot_order < 0 || slot_order >= ar.count) {
        return;
    }
    uint8_t idx = ar.order[slot_order];
    ar.queue[idx] = {};
    for (int i = slot_order + 1; i < ar.count; ++i) {
        ar.order[i - 1] = ar.order[i];
    }
    ar.order[ar.count - 1] = 0;
    ar.count--;
}

static void show_quick_battle_window() {
    autoconfig_window::show("invasion_quick_battle_window");
}

static void close_quick_battle_ui_if_needed() {
    // Only pop back to city if the quick-battle modal is on top (don't yank advisor/empire).
    if (g_window_manager.window_is("invasion_quick_battle_window")) {
        window_city_show();
    }
}

void invasion_auto_resolve_t::sweep_vanished() {
    // Reentrancy: cancel_vanished / chain events must not nest another sweep via calculate_figures.
    if (sweeping || count <= 0) {
        return;
    }
    sweeping = true;
    for (int i = 0; i < count;) {
        auto &p = queue[order[i]];
        if (!p.in_use) {
            ++i;
            continue;
        }
        if (enemy_strength_for_seq(p.seq) <= 0) {
            cancel_vanished(p.seq);
            continue;
        }
        ++i;
    }
    sweeping = false;
}

void invasion_auto_resolve_t::on_after_load() {
    on_feature_maybe_changed();
    if (count <= 0) {
        return;
    }
    sweep_vanished();
    if (count > 0 && !!game_features::gameplay_enhanced_auto_resolve_invasions) {
        show_quick_battle_window();
    }
}

void invasion_auto_resolve_t::maybe_enqueue(const invasion_opts_t &opts, uint16_t seq) {
    if (!game_features::gameplay_enhanced_auto_resolve_invasions) {
        return;
    }
    if (!seq) {
        return;
    }

    switch (opts.kind) {
    case INVASION_KIND_FOREIGN:
    case INVASION_KIND_PHARAOH:
    case INVASION_KIND_KINGDOME:
        break;
    default:
        return;
    }

    // Queue full: leave this wave on the map as manual combat (no surprise resolve).
    if (count >= INVASION_AUTO_RESOLVE_MAX_PENDING) {
        logs::warn("invasion auto-resolve: pending queue full — seq=%u fights manually", seq);
        events::emit(event_city_warning{ "#warning_auto_resolve_queue_full" });
        return;
    }

    int slot = -1;
    for (int i = 0; i < INVASION_AUTO_RESOLVE_MAX_PENDING; ++i) {
        if (!queue[i].in_use) {
            slot = i;
            break;
        }
    }
    if (slot < 0) {
        return;
    }

    auto &p = queue[slot];
    p.in_use = true;
    p.seq = seq;
    p.invasion_id = (uint8_t)opts.invasion_id;
    p.days_left = INVASION_AUTO_RESOLVE_GRACE_DAYS;
    p.grace_armed = false; // first day tick arms without decrement
    order[count++] = (uint8_t)slot;

    logs::info("akhenaten: auto-resolve enqueue seq=%u invasion_id=%u days=%d",
               seq, (unsigned)p.invasion_id, (int)p.days_left);

    events::emit(event_message{ true, "message_invasion_quick_battle", seq, 0, SOURCE_LOCATION });
    // Always focus quick-battle (head). Reopen if player closed Wait and another wave arrives.
    show_quick_battle_window();
}

bool invasion_auto_resolve_t::try_resolve_head() {
    auto *p = head_pending_mut();
    if (!p) {
        return false;
    }
    return try_resolve_now(p->seq);
}

bool invasion_auto_resolve_t::try_resolve_now(uint16_t seq) {
    if (resolving) {
        return false;
    }

    auto *head = head_pending_mut();
    if (!head) {
        return false;
    }
    // Head-only: resolving a queued wave would still kill all city troops.
    if (seq && seq != head->seq) {
        logs::warn("akhenaten: auto-resolve refused non-head seq=%u (head=%u)", seq, head->seq);
        return false;
    }
    seq = head->seq;

    resolving = true;

    g_formations.calculate_figures();
    const int enemy_str = enemy_strength_for_seq(seq);
    // Army already gone (bribe / script) — abort without fake win/KR.
    if (enemy_str <= 0) {
        cancel_vanished(seq);
        resolving = false;
        return false;
    }

    const int player_str = player_strength();
    const bool won = player_str >= enemy_str;
    const int pct_loss = distant_pct_loss(player_str, enemy_str);

    logs::info("akhenaten: auto-resolve seq=%u player=%d enemy=%d won=%d loss=%d%%",
               seq, player_str, enemy_str, (int)won, pct_loss);

    kill_own_batalions_pct(pct_loss);

    // Kingdom army (55–57): do not apply enhanced ±KR. Favour skips all KR; Caesar wrath
    // win gets OG respect via finish_army_defeated after despawn (avoids +25 then +10).
    // FOREIGN/PHARAOH keep the enhanced ±25/±10.
    const bool kingdom_seq = invasion_seq_is_kingdome_army(seq);
    const bool favour_wave = kingdom_seq && g_city.kingdome.invasion.favour_only != 0;
    const bool caesar_win = kingdom_seq && won && !favour_wave;

    if (!kingdom_seq) {
        if (won) {
            g_city.kingdome.change(25);
        } else {
            g_city.kingdome.change(-10);
        }
    }

    if (won) {
        invasion_force_outcome(seq, INVASION_OUTCOME_COMPLETED);
        events::emit(event_message{ true, "message_invasion_auto_resolve_win", seq, 0, SOURCE_LOCATION });
    } else {
        invasion_force_outcome(seq, INVASION_OUTCOME_DEFEAT);
        events::emit(event_message{ true, "message_invasion_auto_resolve_lose", seq, 0, SOURCE_LOCATION });
    }

    // Pop pending before despawn: calculate_figures→sweep must not cancel_vanished this wave again.
    remove_order_index(*this, 0);

    // Kingdom bookkeeping is a single global slot. Zero size before poof so this wave's
    // despawn does not tally as combat kills; after despawn, restore a slot if another
    // kingdom army is still on the map (accumulated favour/Caesar waves).
    const uint8_t saved_favour = g_city.kingdome.invasion.favour_only;
    const uint8_t saved_cheated = g_city.kingdome.invasion.cheated;
    const int32_t saved_duration = g_city.kingdome.invasion.duration_day_countdown;
    if (kingdom_seq) {
        g_city.kingdome.invasion.size = 0;
        g_city.kingdome.invasion.soldiers_killed = 0;
    }

    invasion_despawn_by_seq(seq);

    if (kingdom_seq) {
        const int left = count_alive_kingdome_army_figures();
        if (left > 0) {
            g_city.kingdome.invasion.size = left;
            g_city.kingdome.invasion.soldiers_killed = 0;
            g_city.kingdome.invasion.favour_only = saved_favour;
            g_city.kingdome.invasion.cheated = saved_cheated;
            g_city.kingdome.invasion.duration_day_countdown = saved_duration;
        } else {
            g_city.kingdome.invasion.favour_only = 0;
            g_city.kingdome.invasion.cheated = 0;
            g_city.kingdome.invasion.duration_day_countdown = 0;
            if (caesar_win) {
                g_city.kingdome.finish_army_defeated();
            }
        }
    }

    if (count > 0) {
        show_quick_battle_window();
    } else {
        close_quick_battle_ui_if_needed();
    }

    resolving = false;
    return true;
}

void invasion_auto_resolve_t::cancel_vanished(uint16_t seq) {
    for (int i = 0; i < count; ++i) {
        if (queue[order[i]].seq != seq) {
            continue;
        }
        // Army gone: clear bind with NONE so month-tick cannot fake COMPLETED.
        invasion_force_outcome(seq, INVASION_OUTCOME_NONE);
        // Empty hulls/escorts would otherwise linger after land troops vanished.
        despawn_sea_fleet_by_seq(seq);
        remove_order_index(*this, i);
        if (count <= 0) {
            close_quick_battle_ui_if_needed();
        } else if (i == 0) {
            show_quick_battle_window();
        }
        return;
    }
}

void invasion_auto_resolve_t::cancel_all(bool /*resume_manual*/) {
    // Flag OFF / abort: unfreeze only — leave binds for normal combat resolution.
    const bool had = count > 0;
    clear();
    if (had) {
        close_quick_battle_ui_if_needed();
    }
}

void invasion_auto_resolve_t::on_feature_maybe_changed() {
    if (!!game_features::gameplay_enhanced_auto_resolve_invasions) {
        return;
    }
    if (count > 0) {
        logs::info("akhenaten: auto-resolve flag OFF — cancelling %d pending", (int)count);
        cancel_all(true);
    }
}

void invasion_auto_resolve_t::update_day() {
    on_feature_maybe_changed();
    if (count <= 0) {
        return;
    }

    sweep_vanished();

    if (count <= 0) {
        return;
    }

    // Only the head grace timer runs — queued waves keep full 8 days until they become head
    // (avoids cascade resolve of B on the same day A expires).
    auto *head = head_pending_mut();
    if (!head) {
        return;
    }
    if (!head->grace_armed) {
        // First tick as head (or after enqueue): arm only — never resolve on the arm tick
        // (also protects corrupt saves with days_left==0).
        head->grace_armed = true;
        return;
    }
    if (head->days_left > 0) {
        head->days_left--;
    }
    if (head->days_left <= 0) {
        try_resolve_head();
        // New head after timer resolve: arm same day (match sweep promotion path).
        head = head_pending_mut();
        if (head && !head->grace_armed) {
            head->grace_armed = true;
        }
    }
}

bool invasion_auto_resolve_figure_immune(const figure *f) {
    if (!f || !g_invasion_auto_resolve.has_pending()) {
        return false;
    }
    if (f->formation_id > 0) {
        return g_invasion_auto_resolve.is_formation_frozen(formation_get(f->formation_id));
    }
    // Sea hulls store seq in runtime_data (no formation_id on the ship).
    figure *mut = const_cast<figure *>(f);
    if (auto *t = smart_cast<figure_enemy_transport>(mut)) {
        return g_invasion_auto_resolve.is_seq_frozen((uint16_t)t->invasion_sequence());
    }
    if (auto *w = smart_cast<figure_enemy_warship>(mut)) {
        return g_invasion_auto_resolve.is_seq_frozen((uint16_t)w->invasion_sequence());
    }
    return false;
}

bool invasion_auto_resolve_target_blocked(tile2i tile) {
    if (!g_invasion_auto_resolve.has_pending() || !tile.valid()) {
        return false;
    }
    int fid = map_figure_id_get(tile);
    int guard = 0;
    while (fid > 0 && ++guard < MAX_FIGURES) {
        figure *f = figure_get(fid);
        if (invasion_auto_resolve_figure_immune(f)) {
            return true;
        }
        fid = f->next_figure;
    }
    return false;
}

// --- JS / tests ---

int __invasion_auto_resolve_pending_count() {
    return g_invasion_auto_resolve.count;
}
ANK_FUNCTION(__invasion_auto_resolve_pending_count)

int __invasion_auto_resolve_head_days_left() {
    const auto *h = g_invasion_auto_resolve.head_pending();
    return h ? h->days_left : -1;
}
ANK_FUNCTION(__invasion_auto_resolve_head_days_left)

int __invasion_auto_resolve_head_seq() {
    const auto *h = g_invasion_auto_resolve.head_pending();
    return h ? (int)h->seq : 0;
}
ANK_FUNCTION(__invasion_auto_resolve_head_seq)

int __invasion_auto_resolve_head_invasion_id() {
    const auto *h = g_invasion_auto_resolve.head_pending();
    return h ? (int)h->invasion_id : 0;
}
ANK_FUNCTION(__invasion_auto_resolve_head_invasion_id)

int __invasion_auto_resolve_test_set_player_strength(int value) {
    s_test_player_str_override = value;
    return s_test_player_str_override;
}
ANK_FUNCTION_1(__invasion_auto_resolve_test_set_player_strength)

int __invasion_auto_resolve_player_strength() {
    return g_invasion_auto_resolve.player_strength();
}
ANK_FUNCTION(__invasion_auto_resolve_player_strength)

int __invasion_auto_resolve_enemy_strength() {
    const auto *h = g_invasion_auto_resolve.head_pending();
    return h ? g_invasion_auto_resolve.enemy_strength_for_seq(h->seq) : 0;
}
ANK_FUNCTION(__invasion_auto_resolve_enemy_strength)

int __invasion_auto_resolve_try_now() {
    return g_invasion_auto_resolve.try_resolve_head() ? 1 : 0;
}
ANK_FUNCTION(__invasion_auto_resolve_try_now)

void __invasion_auto_resolve_update_day() {
    g_invasion_auto_resolve.update_day();
}
ANK_FUNCTION(__invasion_auto_resolve_update_day)

int __invasion_auto_resolve_is_frozen(int invasion_id) {
    // Test helper: any pending wave with this invasion_id.
    if (!g_invasion_auto_resolve.has_pending()) {
        return 0;
    }
    for (int i = 0; i < g_invasion_auto_resolve.count; ++i) {
        const auto &p = g_invasion_auto_resolve.queue[g_invasion_auto_resolve.order[i]];
        if (p.in_use && p.invasion_id == (uint8_t)invasion_id) {
            return 1;
        }
    }
    return 0;
}
ANK_FUNCTION_1(__invasion_auto_resolve_is_frozen)

int __invasion_auto_resolve_is_seq_frozen(int seq) {
    return g_invasion_auto_resolve.is_seq_frozen((uint16_t)seq) ? 1 : 0;
}
ANK_FUNCTION_1(__invasion_auto_resolve_is_seq_frozen)

void __invasion_auto_resolve_show_window() {
    if (g_invasion_auto_resolve.has_pending()) {
        show_quick_battle_window();
    }
}
ANK_FUNCTION(__invasion_auto_resolve_show_window)

void __invasion_auto_resolve_sweep() {
    g_invasion_auto_resolve.sweep_vanished();
}
ANK_FUNCTION(__invasion_auto_resolve_sweep)

io_buffer *iob_invasion_auto_resolve = new io_buffer([](io_buffer *iob, size_t version) {
    auto &ar = g_invasion_auto_resolve;
    iob->bind_u8(ar.count);
    uint8_t head_unused = 0;
    iob->bind_u8(head_unused); // was ar.head; keep layout
    for (int i = 0; i < INVASION_AUTO_RESOLVE_MAX_PENDING; ++i) {
        iob->bind_u8(ar.order[i]);
    }
    for (auto &p : ar.queue) {
        iob->bind_bool(p.in_use);
        iob->bind_u16(p.seq);
        iob->bind_u8(p.invasion_id);
        iob->bind_i16(p.days_left);
        iob->bind_bool(p.grace_armed); // was flag_snapshot; same layout
        iob->bind____skip(1);
    }
    iob->bind____skip(6);
}, [](size_t version) {
    // saves older than v177 have no pending auto-resolve queue
    g_invasion_auto_resolve = {};
});
