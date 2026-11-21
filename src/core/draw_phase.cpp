#include "core/draw_phase.h"

#include "core/log.h"

#include <algorithm>
#include <atomic>
#include <mutex>
#include <vector>

namespace {
    std::atomic<int> g_depth{0};
    thread_local int t_allowed = 0;
    std::mutex g_reported_mutex;
    std::vector<const char*> g_reported;
} // namespace

void draw_phase::enter() {
    g_depth.fetch_add(1, std::memory_order_relaxed);
}

void draw_phase::leave() {
    g_depth.fetch_sub(1, std::memory_order_relaxed);
}

bool draw_phase::active() {
    return g_depth.load(std::memory_order_relaxed) > 0 && t_allowed == 0;
}

void draw_phase::check_write(const char* where) {
    if (!active()) {
        return;
    }

    std::scoped_lock lock(g_reported_mutex);
    if (std::find(g_reported.begin(), g_reported.end(), where) != g_reported.end()) {
        return;
    }
    g_reported.push_back(where);
    logs::error("[draw-phase] %s writes the simulation during the draw", where);
}

draw_phase::allow_writes::allow_writes() {
    ++t_allowed;
}

draw_phase::allow_writes::~allow_writes() {
    --t_allowed;
}
