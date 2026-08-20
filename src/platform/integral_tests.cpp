#include "integral_tests.h"

#include "content/content.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "core/app.h"
#include "core/archive.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/variant.h"
#include "core/vec2i.h"
#include "core/xvalue.h"
#include "game/game_config.h"
#include "game/game_system.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/mujs.h"
#include "graphics/screenshot.h"
#include "platform/arguments.h"
#include "platform/version.hpp"

#include <SDL.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <thread>
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

    // ANK_ESID(esid(pcstr)) must hash the passed id, not the helper's own __func__.
    struct esid_probe {
        ANK_ESID(city_animals)
        static bstring64 create_herds() {
            return esid(__func__);
        }
    };
    expect_eq_str(esid_probe::create_herds(), "city_animals+create_herds",
                  "ANK_ESID esid(__func__) uses caller name, not esid");
}

void run_multi_es_handler_unit_tests() {
    // Parent fallback: windows tagged [es=advisor_window] resolve
    // missing exact handlers via advisor_window+event.
    const bstring64 show = js_helpers::es_hash_str("advisor_window", "show_advisor");
    const bstring64 close = js_helpers::es_hash_str("advisor_window", "close_advisors");
    const bstring64 overlay = js_helpers::es_hash_str("building_info_window", "show_overlay");
    const bstring64 mothball = js_helpers::es_hash_str("building_info_window", "mothball");

    expect_true(js_has_event_handlers(xstring(show.c_str())),
                "es_parent: advisor_window+show_advisor registered");
    expect_true(js_has_event_handlers(xstring(close.c_str())),
                "es_parent: advisor_window+close_advisors registered");
    expect_true(js_has_event_handlers(xstring(overlay.c_str())),
                "es_parent: building_info_window+show_overlay registered");
    expect_true(js_has_event_handlers(xstring(mothball.c_str())),
                "es_parent: building_info_window+mothball registered");
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

} // namespace

// ANK_CONFIG_PROPERTY must be at global scope: it opens namespace archive_helper and
// specializes ::archive_helper::get/set (not a nested anonymous one). See archive.h.
struct archive_property_roundtrip_t {
    xstring evolve_text;
    int count = 0;
};
ANK_CONFIG_PROPERTY(archive_property_roundtrip_t, evolve_text, count)

namespace {

struct xvalue_test_a_t {
    int value = 42;
};

struct xvalue_test_b_t {
    int value = 7;
};

struct xvalue_test_find_t {
    int value = 0;
};

struct xvalue_test_threaded_t {
    int value = 0;
};

void run_xvalue_unit_tests() {
    {
        auto &a1 = xvalue<xvalue_test_a_t>::ref();
        auto &a2 = xvalue<xvalue_test_a_t>::ref();
        expect_true(&a1 == &a2, "xvalue ref returns same instance");
        expect_true(a1.value == 42, "xvalue default constructed");
        a1.value = 100;
        expect_true(a2.value == 100, "xvalue mutation visible via second ref");
    }

    {
        auto &a = xvalue<xvalue_test_a_t>::ref();
        auto &b = xvalue<xvalue_test_b_t>::ref();
        expect_true(static_cast<void *>(&a) != static_cast<void *>(&b), "xvalue different types are distinct");
        expect_true(b.value == 7, "xvalue second type default constructed");
        a.value = 111;
        b.value = 222;
        expect_true(xvalue<xvalue_test_a_t>::ref().value == 111, "xvalue type A persists");
        expect_true(xvalue<xvalue_test_b_t>::ref().value == 222, "xvalue type B persists");
    }

    {
        expect_true(xvalue<xvalue_test_find_t>::find() == nullptr, "xvalue find before ref is null");
        auto &inst = xvalue<xvalue_test_find_t>::ref();
        auto *found = xvalue<xvalue_test_find_t>::find();
        expect_true(found != nullptr, "xvalue find after ref is non-null");
        expect_true(found == &inst, "xvalue find matches ref");
        inst.value = 55;
        expect_true(found->value == 55, "xvalue find points at live instance");
    }

    {
        constexpr int k_threads = 8;
        std::vector<xvalue_test_threaded_t *> ptrs(k_threads, nullptr);
        std::vector<std::thread> threads;
        threads.reserve(k_threads);
        for (int i = 0; i < k_threads; ++i) {
            threads.emplace_back([&ptrs, i]() {
                ptrs[i] = &xvalue<xvalue_test_threaded_t>::ref();
            });
        }
        for (auto &t : threads) {
            t.join();
        }

        bool all_same = ptrs[0] != nullptr;
        for (int i = 1; i < k_threads; ++i) {
            if (ptrs[i] != ptrs[0]) {
                all_same = false;
                break;
            }
        }
        expect_true(all_same, "xvalue concurrent ref yields same instance");

        auto *found = xvalue<xvalue_test_threaded_t>::find();
        expect_true(found != nullptr && found == ptrs[0], "xvalue find matches concurrent ref instance");
    }
}

void run_archive_property_unit_tests() {
    {
        const xstring src = "#cannot_evolve_cause_low_desirability";
        const xstring got = ::archive_helper::coerce<xstring>(bvariant(src));
        expect_true(got == src, "coerce<xstring> preserves string bvariant");
    }

    {
        const xstring got = ::archive_helper::coerce<xstring>(bvariant(42));
        expect_true(got.empty(), "coerce<xstring> from int yields empty");
    }

    {
        const xstring got = ::archive_helper::coerce<xstring>(bvariant());
        expect_true(got.empty(), "coerce<xstring> from empty bvariant yields empty");
    }

    {
        archive_property_roundtrip_t data;
        const bool ok = ::archive_helper::set(data, "evolve_text", bvariant(xstring("#house_upgrade_inprogress")), true);
        expect_true(ok, "archive_helper::set xstring evolve_text");
        expect_true(data.evolve_text == "#house_upgrade_inprogress", "xstring field stored after set");

        auto opt = ::archive_helper::get(data, xstring("evolve_text"), true);
        expect_true(opt.has_value(), "archive_helper::get xstring has value");
        expect_true(opt.has_value() && opt->is_str() && opt->as_str() == "#house_upgrade_inprogress",
                    "archive_helper::get xstring roundtrip");
    }

    {
        archive_property_roundtrip_t data;
        data.evolve_text = "#keep_me";
        const bool ok = ::archive_helper::set(data, "evolve_text", bvariant(xstring("")), true);
        expect_true(ok, "archive_helper::set empty xstring");
        expect_true(data.evolve_text.empty(), "xstring field cleared");
    }

    {
        archive_property_roundtrip_t data;
        expect_true(::archive_helper::set(data, "count", bvariant(7), true), "archive_helper::set int still works");
        expect_true(data.count == 7, "int field stored after set");
    }

    {
        const vec2i got = ::archive_helper::coerce<vec2i>(bvariant(vec2i{3, 4}));
        expect_true(got.x == 3 && got.y == 4, "coerce<vec2i> preserves value");
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
    run_multi_es_handler_unit_tests();
    run_archive_property_unit_tests();
    run_xvalue_unit_tests();
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
        return std::strcmp(a.c_str(), b.c_str()) < 0;
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
            const xstring stem = p; // copy before clear() invalidates `p`
            found_tests.clear();
            found_tests.push_back(stem);
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

        // Fresh map/UI for every test — leftover city/editor/events otherwise bleed.
        test_reset_session_between_tests();

        g_app.quit = false;
        SDL_FlushEvent(SDL_USEREVENT);

        game_features::gameopt_ironwill.set(false);
        const int stale = js_vm_force_idle_stack();
        if (stale > 0) {
            logs::info("[test:%s] cleared %d stale MuJS stack slot(s) before test", name.c_str(), stale);
        }

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
        js_vm_sync({}); // run include() queued while loading the test script
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

        // Fresh framebuffer, then end-of-test display shot (skipped under --no-resource).
        g_app.pump_one_frame();
        {
            pcstr leaf = name.c_str();
            if (const char *slash = std::strrchr(leaf, '/')) {
                leaf = slash + 1;
            }
            if (const char *bslash = std::strrchr(leaf, '\\')) {
                leaf = bslash + 1;
            }
            size_t stem_len = std::strlen(leaf);
            if (stem_len > 3 && std::strcmp(leaf + stem_len - 3, ".js") == 0) {
                stem_len -= 3;
            }
            bstring256 shot_name;
            shot_name.printf("end_");
            shot_name.ncat(leaf, stem_len);
            graphics_save_screenshot_as(SCREENSHOT_DISPLAY, shot_name.c_str());
        }

        if (!g_test_signal_ready) {
            logs::error("[test:%s] FAIL: timeout after %d frames (forgot __test_signal_ready?)",
                        name.c_str(), frames);
            ++failed;
            continue;
        }
        logs::info("[test:%s] finished after %d frame(s)", name.c_str(), frames);

        if (test_log_contains("!!! TypeError:")) {
            logs::error("[test:%s] FAIL: !!! TypeError: found in log", name.c_str());
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

        bool ok_result = false;
        if (!cv_ok) {
            logs::error("[test:%s] FAIL: check_valid threw", name.c_str());
        } else if (!result) {
            logs::error("[test:%s] FAIL (check_valid returned false)", name.c_str());
        } else {
            ok_result = true;
        }

        // MuJS value stack must be idle-empty between tests (catches hot-reload leaks).
        const int leaked = js_vm_force_idle_stack();
        if (leaked > 0) {
            logs::error("[test:%s] FAIL: MuJS stack not idle after test (leaked %d slot(s))", name.c_str(),
                        leaked);
            ok_result = false;
        }

        if (ok_result) {
            logs::info("[test:%s] PASS", name.c_str());
            ++passed;
        } else {
            ++failed;
        }
    }
    js_vm_reset_error();
    const int final_leak = js_vm_force_idle_stack();
    if (final_leak > 0) {
        logs::error("[integraltests] FAIL: MuJS stack not idle after suite (leaked %d)", final_leak);
        ++failed;
    }
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
