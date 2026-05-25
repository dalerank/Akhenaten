#include "integral_tests.h"

#include "content/content.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "core/app.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/vec2i.h"
#include "js/js.h"
#include "mujs/mujs.h"
#include "platform/arguments.h"
#include "platform/version.hpp"

#include <SDL.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>

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
}

hvector<xstring, 16> list_test_files() {
    hvector<xstring, 16> found_tests;
    auto add_tests_from_folder = [&](pcstr root) {
        vfs::dir_look_entries(root, [&](pcstr e, bool is_folder) {
            if (is_folder || !e) {
                return;
            }
            // Skip files whose basename starts with '_' (disabled tests). `e`
            // here is the full path returned by the directory iterator, so we
            // need to look past the last path separator.
            pcstr basename = e;
            for (pcstr p = e; *p; ++p) {
                if (*p == '/' || *p == '\\') {
                    basename = p + 1;
                }
            }
            if (*basename == '_') {
                return;
            }
            // vfs::file_has_extension expects the extension without the dot.
            if (!vfs::file_has_extension(e, "js")) {
                return;
            }
            vfs::path path = e;
            found_tests.push_back(path.tolower().c_str());
        });
    };

    add_tests_from_folder("tests");
    add_tests_from_folder("../tests");

    std::sort(found_tests.begin(), found_tests.end(), [](const xstring &a, const xstring &b) {
        return a < b;
    });

    const xstring only = g_args.get_integraltest_only().tolower();
    if (only.empty()) {
        return found_tests;
    }

    for (const auto& p : found_tests) {
        vfs::path strp = p.c_str();
        const bool found = strp.strstr(only.c_str()) != nullptr;
        if (found) {
            const xstring stem = p;
            found_tests.clear();
            found_tests.push_back(p);
            break;
        }
    }

    if (!found_tests.empty()) {
        return found_tests;
    }

    logs::error("[integraltests] cant find '%s' in tests", only.c_str());
    return {};
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
        if (!g_args.get_integraltest_only().empty()) {
            // user asked for a specific test that doesn't exist — that's a hard failure
            return 1;
        }
        logs::error("[integraltests] no .js test files found under tests/");
        return 0;
    }

    int passed = 0;
    int failed = 0;
    for (const auto &name : files) {
        logs::info("[integraltests] >> %s", name.c_str());

        g_app.quit = false;
        SDL_FlushEvent(SDL_USEREVENT);

        const int load_baseline = js_gettop(J);
        js_vm_reset_error();
        if (!js_vm_load_file_and_exec(name.c_str())) {
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
