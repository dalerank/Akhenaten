#include "integral_tests.h"

#include "core/app.h"
#include "core/log.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "js/js.h"
#include "mujs/mujs.h"
#include "platform/version.hpp"

#include "cmrc/cmrc.hpp"
#include <SDL.h>
#include <string>
#include <string_view>

CMRC_DECLARE(akhenaten);

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <vector>

bool g_test_signal_ready = false;

namespace {

int failure_count;

void expect_true(bool ok, const char *expr) {
    if (!ok) {
        logs::error("[integraltests] FAIL: %s", expr);
        failure_count++;
    }
}

void run_integral_tests_impl() {
    expect_true(SDL_strlen("abc") == 3, "SDL_strlen sample");
    expect_true(SDL_strcmp("x", "x") == 0, "SDL_strcmp sample");

    vec2i a{10, 20};
    vec2i b = a + vec2i{5, 3};
    expect_true(b.x == 15 && b.y == 23, "vec2i addition");

    const xstring ver = get_version();
    expect_true(!ver.empty(), "get_version() non-empty");

    // Each mission_N_*.js must unlock advisors (regression guard for #501).
    // Static check until JS VM + scenario can be bootstrapped here; then this
    // should be replaced with: load mission, emit event_mission_start, assert
    // city.is_advisor_available(...) for the expected set.
    auto scripts_fs = cmrc::akhenaten::get_filesystem();
    int mission_scripts_found = 0;
    for (auto &&entry : scripts_fs.iterate_directory("src/scripts/")) {
        std::string name = entry.filename();
        if (name.rfind("mission_", 0) != 0 || name.find(".js") == std::string::npos) {
            continue;
        }
        if (name == "mission_debug.js") {
            continue;
        }
        bstring256 fs_path("src/scripts/", name.c_str());
        auto file = scripts_fs.open(fs_path.c_str());
        std::string_view body(file.begin(), file.size());
        const bool has_unlock = body.find("set_advisor_available(") != std::string_view::npos;
        bstring128 msg;
        msg.printf("%s calls set_advisor_available", name.c_str());
        expect_true(has_unlock, msg.c_str());
        mission_scripts_found++;
    }
    expect_true(mission_scripts_found >= 11, "found all 11 mission scripts (0..10)");
}

std::vector<std::filesystem::path> list_test_files() {
    namespace fs = std::filesystem;
    std::vector<fs::path> roots;
    std::error_code ec;
    roots.push_back(fs::current_path(ec) / "tests");
    if (char *base = SDL_GetBasePath()) {
        roots.emplace_back(fs::path(base) / ".." / "tests");
        SDL_free(base);
    }
    std::vector<fs::path> out;
    for (const auto &root : roots) {
        if (!fs::is_directory(root, ec)) {
            continue;
        }
        for (const auto &e : fs::directory_iterator(root, ec)) {
            if (!e.is_regular_file()) {
                continue;
            }
            const auto name = e.path().filename().string();
            if (name.empty() || name[0] == '_') {
                continue;
            }
            if (e.path().extension() != ".js") {
                continue;
            }
            out.push_back(e.path());
        }
        if (!out.empty()) {
            break; // first non-empty root wins
        }
    }
    std::sort(out.begin(), out.end());
    return out;
}

void pop_to(js_State *J, int baseline) {
    while (js_gettop(J) > baseline) {
        js_pop(J, 1);
    }
}

// Call a global function with 0 args, swallowing return value and resetting
// the sticky vm.have_error flag. Caller must have verified existence via
// js_vm_global_is_callable. Returns true on success.
bool call_global_void(js_State *J, const char *name) {
    int baseline = js_gettop(J);
    js_vm_reset_error();
    js_getglobal(J, name);
    js_pushnull(J); // `this` (functions don't use it)
    int ok = js_vm_trypcall(J, 0);
    pop_to(J, baseline);
    return ok != 0;
}

int run_js_tests() {
    constexpr int kMaxFramesPerTest = 600; // ~10s at 60fps

    js_State *J = js_vm_state();
    if (!J) {
        logs::error("[integraltests] JS VM not initialized");
        return 1;
    }

    const auto files = list_test_files();
    if (files.empty()) {
        logs::warn("[integraltests] no .js test files found under tests/");
        return 0;
    }

    int passed = 0;
    int failed = 0;
    for (const auto &f : files) {
        const std::string name = f.stem().string();
        logs::info("[integraltests] >> %s", name.c_str());

        const int load_baseline = js_gettop(J);
        js_vm_reset_error();
        if (!js_vm_load_file_and_exec(f.string().c_str())) {
            logs::error("[test:%s] FAIL: load error", name.c_str());
            pop_to(J, load_baseline);
            js_vm_reset_error();
            ++failed;
            continue;
        }
        pop_to(J, load_baseline); // discard top-level result residue

        // run_test
        if (!js_vm_global_is_callable(J, "run_test")) {
            logs::error("[test:%s] FAIL: missing run_test()", name.c_str());
            ++failed;
            continue;
        }
        g_test_signal_ready = false;
        if (!call_global_void(J, "run_test")) {
            logs::error("[test:%s] FAIL: run_test threw", name.c_str());
            ++failed;
            continue;
        }

        // Pump frames while the game runs as usual.
        int frames = 0;
        while (!g_test_signal_ready && frames < kMaxFramesPerTest && !g_app.quit) {
            g_app.pump_one_frame();
            ++frames;
        }
        if (!g_test_signal_ready) {
            logs::error("[test:%s] FAIL: timeout after %d frames (forgot __test_signal_ready?)",
                        name.c_str(), frames);
            ++failed;
            continue;
        }

        // check_valid -> bool
        if (!js_vm_global_is_callable(J, "check_valid")) {
            logs::error("[test:%s] FAIL: missing check_valid()", name.c_str());
            ++failed;
            continue;
        }
        const int cv_baseline = js_gettop(J);
        js_vm_reset_error();
        js_getglobal(J, "check_valid");
        js_pushnull(J); // `this`
        int cv_ok = js_vm_trypcall_keep_result(J, 0);
        bool result = false;
        if (cv_ok) {
            // Accept any truthy return: explicit boolean is normal, but
            // returning 1, "ok", an object, etc. should also count as PASS.
            result = (js_toboolean(J, -1) != 0);
        }
        pop_to(J, cv_baseline);

        if (!cv_ok) {
            logs::error("[test:%s] FAIL: check_valid threw", name.c_str());
            ++failed;
        } else if (result) {
            logs::info("[test:%s] PASS", name.c_str());
            ++passed;
        } else {
            logs::error("[test:%s] FAIL", name.c_str());
            ++failed;
        }
    }
    js_vm_reset_error();
    logs::info("[integraltests] %d passed, %d failed", passed, failed);
    return failed == 0 ? 0 : 1;
}

} // namespace

int run_integral_tests() {
    failure_count = 0;
    logs::info("[integraltests] start");

    run_integral_tests_impl();
    int js_rc = run_js_tests();

    if (failure_count == 0 && js_rc == 0) {
        logs::info("[integraltests] all checks passed");
        return 0;
    }

    logs::error("[integraltests] finished with %d C++ failure(s), JS rc=%d", failure_count, js_rc);
    return 1;
}
