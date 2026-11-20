#include "core/main_thread.h"

#include "core/log.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>

namespace {
    std::thread::id g_main_thread_id = std::this_thread::get_id();
    std::mutex g_reported_mutex;
    std::vector<const char*> g_reported;
} // namespace

void main_thread::set() {
    g_main_thread_id = std::this_thread::get_id();
}

bool main_thread::is() {
    return std::this_thread::get_id() == g_main_thread_id;
}

void main_thread::check(const char* where) {
    if (is()) {
        return;
    }

    std::scoped_lock lock(g_reported_mutex);
    if (std::find(g_reported.begin(), g_reported.end(), where) != g_reported.end()) {
        return;
    }
    g_reported.push_back(where);
    logs::error("[render] %s called off the main thread", where);
}

void main_thread::reset_reports() {
    std::scoped_lock lock(g_reported_mutex);
    g_reported.clear();
}
