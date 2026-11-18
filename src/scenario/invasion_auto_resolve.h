#pragma once

#include "scenario/scenario_invasion.h"

#include <array>
#include <cstdint>

struct figure;
struct formation;

enum {
    INVASION_AUTO_RESOLVE_GRACE_DAYS = 8,
    INVASION_AUTO_RESOLVE_MAX_PENDING = 8,
};

struct invasion_auto_resolve_pending_t {
    bool in_use = false;
    uint16_t seq = 0;
    uint8_t invasion_id = 0;
    int16_t days_left = 0;
    // false until first day tick after enqueue — skips that tick so grace is a full 8 days.
    bool grace_armed = false;
};

struct invasion_auto_resolve_t {
    std::array<invasion_auto_resolve_pending_t, INVASION_AUTO_RESOLVE_MAX_PENDING> queue;
    uint8_t count = 0;
    std::array<uint8_t, INVASION_AUTO_RESOLVE_MAX_PENDING> order = {}; // indices in FIFO order
    bool sweeping = false;  // reentrancy guard for sweep_vanished
    bool resolving = false; // reentrancy guard for try_resolve_now

    void clear();
    void update_day();
    void on_feature_maybe_changed();

    // After successful spawn of in-scope wave (land formations present).
    void maybe_enqueue(const invasion_opts_t &opts, uint16_t seq);

    bool is_seq_frozen(uint16_t seq) const;
    bool is_formation_frozen(const formation *m) const;
    bool has_pending() const { return count > 0; }

    const invasion_auto_resolve_pending_t *head_pending() const;
    invasion_auto_resolve_pending_t *head_pending_mut();

    // Resolves the queue head only (seq must be 0 or head.seq).
    bool try_resolve_now(uint16_t seq); // 0 = head
    bool try_resolve_head();
    // Drop pending for vanished army: clear bind with NONE (no fight tags / no fake COMPLETED).
    void cancel_vanished(uint16_t seq);
    void cancel_all(bool resume_manual);

    int player_strength() const;
    int enemy_strength_for_seq(uint16_t seq) const;

    void force_outcome(uint16_t seq, e_invasion_outcome outcome);

    // Drop pending waves whose army is already gone (bribe / clear / script).
    void sweep_vanished();

    // After save load: honor feature flag, sweep ghosts, reopen UI if still pending.
    void on_after_load();
};

extern invasion_auto_resolve_t g_invasion_auto_resolve;

// True if this figure (or its formation) belongs to a frozen pending wave.
bool invasion_auto_resolve_figure_immune(const figure *f);
// True if tile/figure belongs to a pending frozen invasion wave (for order targeting).
bool invasion_auto_resolve_target_blocked(tile2i tile);

// Shared despawn for auto-resolve / bribe / cheats (land formations + sea fleet).
void invasion_despawn_by_seq(uint16_t seq);
