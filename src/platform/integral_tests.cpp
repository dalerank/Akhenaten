#include "integral_tests.h"

#include "content/content.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "core/app.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/vec2i.h"
#include "js/js.h"
#include "js/js_game.h"
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

void expect_eq_str(const bstring64 &got, pcstr expected, const char *expr) {
    if (got != expected) {
        logs::error("[integraltests] FAIL: %s (got '%s', expected '%s')", expr, got.c_str(), expected);
        failure_count++;
    }
}

namespace es_func_test {

static bstring64 g_es2str_from_init;
static bstring64 g_hash_from_init;
void init() {
    g_es2str_from_init = js_helpers::es2str(__func__);
    g_hash_from_init = js_helpers::es_hash_str("info_window_granary", __func__);
}

} // namespace es_func_test

namespace es_func_decay_test {

static bstring64 g_hash_from_init_via_pcstr;

static void record_sub_event(pcstr sub_event) {
    g_hash_from_init_via_pcstr = js_helpers::es_hash_str("info_window_granary", sub_event);
}

void init() {
    record_sub_event(__func__);
}

} // namespace es_func_decay_test

void run_es_hash_unit_tests() {
    expect_eq_str(js_helpers::es_hash_str("b", "a"), "a+b", "es_hash_str sorts parts");
    expect_eq_str(js_helpers::es_hash_str("init", "main_menu_screen"), "init+main_menu_screen",
                  "es_hash_str init+section");
    expect_eq_str(js_helpers::es_hash_str("file_dialog_load", "init"), "file_dialog_load+init",
                  "es_hash_str file_dialog_load+init");
    expect_eq_str(js_helpers::es_hash_str("info_window_granary", "init"), "info_window_granary+init",
                  "es_hash_str granary info window");

    es_func_test::init();
    expect_eq_str(es_func_test::g_es2str_from_init, "init", "es2str(__func__) in init()");
    expect_eq_str(es_func_test::g_hash_from_init, "info_window_granary+init",
                  "es_hash_str(section, __func__) in init()");

    es_func_decay_test::init();
    expect_eq_str(es_func_decay_test::g_hash_from_init_via_pcstr, "info_window_granary+init",
                  "es_hash_str(__func__) after decay to pcstr in init()");

    const xstring section = "window_mission_won";
    expect_eq_str(js_helpers::es_hash_str(section, "init"), "init+window_mission_won",
                  "es_hash_str with xstring section");
}

// Regression: bstring::cat() previously used snprintf(_data, _size, "%s%s", _data, s),
// which aliased source and destination buffers — undefined behavior per C11
// §7.21.6.5/2. MSVC/UCRT tolerated it, glibc dropped the prefix and broke
// es_hash_str on Linux. These tests pin the contract explicitly so a future
// rewrite cannot silently regress.
void run_bstring_cat_unit_tests() {
    {
        bstring64 b;
        b.cat("a");
        b.cat("+");
        b.cat("b");
        expect_eq_str(b, "a+b", "bstring::cat chained 3 calls");
    }

    {
        bstring64 b;
        b.cat("init");
        b.cat("+");
        b.cat("main_menu_screen");
        expect_eq_str(b, "init+main_menu_screen", "bstring::cat chained long strings");
    }

    {
        bstring64 b = "init+";
        // Direct self-aliasing: pass our own buffer as the source.
        // Must not lose the prefix.
        b.cat(b.c_str());
        expect_eq_str(b, "init+init+", "bstring::cat self-aliasing");
    }

    {
        bstring64 b = "abc";
        b.cat("d", "e");
        expect_eq_str(b, "abcde", "bstring::cat 2-arg overload");
    }

    {
        bstring64 b = "abc";
        b.cat("d", "e", "f");
        expect_eq_str(b, "abcdef", "bstring::cat 3-arg overload");
    }

    {
        bstring64 b = "abc";
        b.cat("d", "e", "f", "g");
        expect_eq_str(b, "abcdefg", "bstring::cat 4-arg overload");
    }

    {
        bstring64 b = "abc";
        b.cat("d", "e", "f", "g", "h");
        expect_eq_str(b, "abcdefgh", "bstring::cat 5-arg overload");
    }

    {
        // Overflow guard: should not write past the buffer.
        bstring<8> b = "1234567";
        b.cat("XYZ");
        expect_true(b.len() < 8, "bstring::cat respects capacity");
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

    run_bstring_cat_unit_tests();
    run_es_hash_unit_tests();
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

    logs::info("[integraltests] %d test file(s)", (int)found_tests.size());
    for (const auto &p : found_tests) {
        logs::info("[integraltests]   - %s", p.c_str());
    }

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
        logs::flush();

        g_app.quit = false;
        SDL_FlushEvent(SDL_USEREVENT);

        const int load_baseline = js_gettop(J);
        js_vm_reset_error();
        logs::info("[test:%s] loading script", name.c_str());
        if (!js_vm_load_file_and_exec(name.c_str())) {
            logs::error("[test:%s] FAIL: load error", name.c_str());
            pop_to(J, load_baseline);
            js_vm_reset_error();
            ++failed;
            continue;
        }
        pop_to(J, load_baseline); // discard top-level result residue
        logs::info("[test:%s] script loaded", name.c_str());

        // run_test
        if (!js_vm_global_is_callable(J, "run_test")) {
            logs::error("[test:%s] FAIL: missing run_test()", name.c_str());
            ++failed;
            continue;
        }
        g_test_signal_ready = false;
        logs::info("[test:%s] calling run_test()", name.c_str());
        if (!call_global_void(J, "run_test")) {
            logs::error("[test:%s] FAIL: run_test threw", name.c_str());
            ++failed;
            continue;
        }
        logs::info("[test:%s] run_test() returned, signal_ready=%d", name.c_str(), g_test_signal_ready ? 1 : 0);

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
        logs::info("[test:%s] finished after %d frame(s)", name.c_str(), frames);

        // check_valid -> bool
        if (!js_vm_global_is_callable(J, "check_valid")) {
            logs::error("[test:%s] FAIL: missing check_valid()", name.c_str());
            ++failed;
            continue;
        }
        const int cv_baseline = js_gettop(J);
        js_vm_reset_error();
        logs::info("[test:%s] calling check_valid() (log=%s)", name.c_str(), logs::output_path());
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
        logs::flush();

        if (!cv_ok) {
            logs::error("[test:%s] FAIL: check_valid threw", name.c_str());
            ++failed;
        } else if (result) {
            logs::info("[test:%s] PASS", name.c_str());
            ++passed;
        } else {
            logs::error("[test:%s] FAIL (check_valid returned false)", name.c_str());
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
