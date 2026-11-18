#include "integral_tests.h"

#include "content/content.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "core/app.h"
#include "core/archive.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/random.h"
#include "core/variant.h"
#include "core/vec2i.h"
#include "core/xvalue.h"
#include "game/game_config.h"
#include "io/gamestate/boilerplate.h"
#include "game/game_system.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/mujs.h"
#include "graphics/screenshot.h"
#include "platform/arguments.h"
#include "platform/child_process.h"
#include "platform/platform.h"
#include "platform/version.hpp"

#include <SDL.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
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

void expect_eq_str(pcstr got, pcstr expected, const char *expr) {
    if (strcmp(got, expected) != 0) {
        logs::error("[integraltests] FAIL: %s (got '%s', expected '%s')", expr, got, expected);
        failure_count++;
    }
}

namespace es_func_test {

static bstring128 g_es2str_from_init;
static bstring128 g_hash_from_init;
void init() {
    g_es2str_from_init = js_helpers::es2str(__func__).c_str();
    g_hash_from_init = js_helpers::es_hash_str("info_window_granary", __func__);
}

} // namespace es_func_test

namespace es_func_decay_test {

static bstring128 g_hash_from_init_via_pcstr;

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
        static bstring128 create_herds() {
            return esid(__func__);
        }
    };
    expect_eq_str(esid_probe::create_herds(), "city_animals+create_herds",
                  "ANK_ESID esid(__func__) uses caller name, not esid");
}

void run_multi_es_handler_unit_tests() {
    // Parent fallback: windows tagged [es=advisor_window] resolve
    // missing exact handlers via advisor_window+event.
    const bstring128 show = js_helpers::es_hash_str("advisor_window", "show_advisor");
    const bstring128 close = js_helpers::es_hash_str("advisor_window", "close_advisors");
    const bstring128 overlay = js_helpers::es_hash_str("building_info_window", "show_overlay");
    const bstring128 mothball = js_helpers::es_hash_str("building_info_window", "mothball");

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

void run_bvariant_unit_tests() {
    {
        const bvariant v;
        expect_true(v.is_empty() && v.value_type() == bvariant::etype_none, "bvariant default is empty");
        expect_true(v.is_null(), "bvariant default is null");
        expect_true(!v.to_bool(), "bvariant default to_bool is false");
        expect_eq_str(v.to_str(), "none", "bvariant default to_str");
        expect_eq_str(v.debug_str(), "none", "bvariant default debug_str");
    }

    {
        int marker = 0;
        expect_true(bvariant(true).value_type() == bvariant::etype_bool, "bvariant(bool) type");
        expect_true(bvariant(int32_t(-5)).value_type() == bvariant::etype_int32, "bvariant(int32) type");
        expect_true(bvariant(uint32_t(5)).value_type() == bvariant::etype_uint32, "bvariant(uint32) type");
        expect_true(bvariant(uint64_t(5)).value_type() == bvariant::etype_uint64, "bvariant(uint64) type");
        expect_true(bvariant(1.5f).value_type() == bvariant::etype_float, "bvariant(float) type");
        expect_true(bvariant((void*)&marker).value_type() == bvariant::etype_ptr, "bvariant(ptr) type");
        expect_true(bvariant(xstring("a")).value_type() == bvariant::etype_str, "bvariant(xstring) type");
        expect_true(bvariant(uint16_t(5)).value_type() == bvariant::etype_u16, "bvariant(uint16) type");
        expect_true(bvariant(vec2i{1, 2}).value_type() == bvariant::etype_vec2i, "bvariant(vec2i) type");
        expect_true(bvariant(tile2i(3, 4)).value_type() == bvariant::etype_tile2i, "bvariant(tile2i) type");
        expect_true(bvariant(grid_area(tile2i(1, 2), tile2i(3, 4))).value_type() == bvariant::etype_grid_area,
          "bvariant(grid_area) type");
    }

    {
        expect_true(bvariant(int8_t(-3)).is_int32() && bvariant(int8_t(-3)).as_int32() == -3,
          "bvariant(int8) widens to int32");
        expect_true(bvariant(int16_t(-300)).is_int32() && bvariant(int16_t(-300)).as_int32() == -300,
          "bvariant(int16) widens to int32");
        expect_true(bvariant(uint8_t(200)).is_uint32() && bvariant(uint8_t(200)).as_uint32() == 200,
          "bvariant(uint8) widens to uint32");
        expect_true(bvariant("abc").is_str() && bvariant("abc").as_str() == "abc", "bvariant(pcstr) is a string");
        expect_true(bvariant(cstring("xyz")).is_str() && bvariant(cstring("xyz")).as_str() == "xyz",
          "bvariant(cstring) is a string");
    }

    {
        int marker = 0;
        expect_true(bvariant(true).as_bool(), "bvariant as_bool");
        expect_true(bvariant(uint16_t(65535)).as_u16() == 65535, "bvariant as_u16");
        expect_true(bvariant(int32_t(-7)).as_int32() == -7, "bvariant as_int32");
        expect_true(bvariant(uint32_t(4000000000u)).as_uint32() == 4000000000u, "bvariant as_uint32");
        expect_true(bvariant(uint64_t(1) << 40).as_uint64() == (uint64_t(1) << 40), "bvariant as_uint64");
        expect_true(bvariant(2.25f).as_float() == 2.25f, "bvariant as_float");
        expect_true(bvariant((void*)&marker).as_ptr() == &marker, "bvariant as_ptr");
        expect_true(bvariant(vec2i{7, -8}).as_vec2i() == vec2i(7, -8), "bvariant as_vec2i");
        expect_true(bvariant(tile2i(9, 10)).as_tile2i() == tile2i(9, 10), "bvariant as_tile2i");
        const grid_area a = bvariant(grid_area(tile2i(1, 2), tile2i(3, 4))).as_grid_area();
        expect_true(a.tmin_x == 1 && a.tmin_y == 2 && a.tmax_x == 3 && a.tmax_y == 4, "bvariant as_grid_area");
    }

    {
        bvariant v(int32_t(3));
        expect_true(!v.is_bool() && !v.is_u16() && !v.is_uint32() && !v.is_uint64() && !v.is_float() && !v.is_ptr()
                      && !v.is_str() && !v.is_vec2i() && !v.is_tile2i() && !v.is_grid_area() && !v.is_empty(),
          "bvariant is_* matches only the held type");
        expect_true(v.int32_or_def(9) == 3 && v.uint32_or_def(9) == 9 && v.bool_or_def(true) && v.uint64_or_def(9) == 9
                      && v.float_or_def(9.f) == 9.f,
          "bvariant *_or_def returns the value only for the held type");
        expect_true(v.str_or_def(xstring("d")) == "d" && v.vec2i_or_def(vec2i{1, 1}) == vec2i(1, 1)
                      && v.tile2i_or_def(tile2i(2, 2)) == tile2i(2, 2) && v.grid_area_or_def(grid_area()).tmax_x == 0,
          "bvariant *_or_def returns the default for other types");
    }

    {
        bvariant a(xstring("copy"));
        bvariant b(a);
        expect_true(b.is_str() && b.as_str() == "copy", "bvariant copy constructor");
        bvariant c(int32_t(1));
        c = a;
        expect_true(c.is_str() && c.as_str() == "copy", "bvariant copy assignment changes type");
        const bvariant &self = c;
        c = self;
        expect_true(c.is_str() && c.as_str() == "copy", "bvariant self assignment");
        a = int32_t(2);
        expect_true(b.as_str() == "copy" && a.as_int32() == 2, "bvariant copies are independent");
    }

    {
        bvariant v;
        v = true;
        expect_true(v.is_bool() && v.as_bool(), "bvariant operator=(bool)");
        v = uint16_t(4);
        expect_true(v.is_u16() && v.as_u16() == 4, "bvariant operator=(uint16)");
        v = int32_t(-4);
        expect_true(v.is_int32() && v.as_int32() == -4, "bvariant operator=(int32)");
        v = uint32_t(4);
        expect_true(v.is_uint32() && v.as_uint32() == 4, "bvariant operator=(uint32)");
        v = uint64_t(4);
        expect_true(v.is_uint64() && v.as_uint64() == 4, "bvariant operator=(uint64)");
        v = 0.5f;
        expect_true(v.is_float() && v.as_float() == 0.5f, "bvariant operator=(float)");
        v = (void*)nullptr;
        expect_true(v.is_ptr() && v.as_ptr() == nullptr, "bvariant operator=(ptr)");
        v = xstring("s");
        expect_true(v.is_str() && v.as_str() == "s", "bvariant operator=(xstring)");
        v = vec2i{5, 6};
        expect_true(v.is_vec2i() && v.as_vec2i() == vec2i(5, 6), "bvariant operator=(vec2i)");
        v = tile2i(5, 6);
        expect_true(v.is_tile2i() && v.as_tile2i() == tile2i(5, 6), "bvariant operator=(tile2i)");
        v = grid_area(tile2i(1, 1), tile2i(2, 2));
        expect_true(v.is_grid_area() && v.as_grid_area().tmax_y == 2, "bvariant operator=(grid_area)");
    }

    {
        bvariant v;
        expect_true(&v.as_bool(false) == &v && v.is_bool() && !v.as_bool(), "bvariant as_bool setter");
        expect_true(&v.as_u16(9) == &v && v.as_u16() == 9, "bvariant as_u16 setter");
        expect_true(&v.as_int32(-9) == &v && v.as_int32() == -9, "bvariant as_int32 setter");
        expect_true(&v.as_uint32(9) == &v && v.as_uint32() == 9, "bvariant as_uint32 setter");
        expect_true(&v.as_uint64(9) == &v && v.as_uint64() == 9, "bvariant as_uint64 setter");
        expect_true(&v.as_float(9.5f) == &v && v.as_float() == 9.5f, "bvariant as_float setter");
        expect_true(&v.as_ptr(&v) == &v && v.as_ptr() == &v, "bvariant as_ptr setter");
        expect_true(&v.as_str(xstring("t")) == &v && v.as_str() == "t", "bvariant as_str setter");
        expect_true(&v.as_vec2i(vec2i{1, 2}) == &v && v.as_vec2i() == vec2i(1, 2), "bvariant as_vec2i setter");
        expect_true(&v.as_tile2i(tile2i(1, 2)) == &v && v.as_tile2i() == tile2i(1, 2), "bvariant as_tile2i setter");
        expect_true(&v.as_grid_area(grid_area()) == &v && v.is_grid_area(), "bvariant as_grid_area setter");
    }

    {
        expect_true(bvariant() == bvariant(), "bvariant empty == empty");
        expect_true(bvariant(int32_t(1)) == bvariant(int32_t(1)), "bvariant int32 equal");
        expect_true(!(bvariant(int32_t(1)) == bvariant(int32_t(2))), "bvariant int32 not equal");
        expect_true(!(bvariant(int32_t(1)) == bvariant(uint32_t(1))), "bvariant different types not equal");
        expect_true(!(bvariant() == bvariant(int32_t(0))), "bvariant empty != int32 0");
        expect_true(bvariant(1.0f) == bvariant(1.0f + 1e-7f), "bvariant float equal within tolerance");
        expect_true(!(bvariant(1.0f) == bvariant(1.001f)), "bvariant float not equal outside tolerance");
        expect_true(bvariant(xstring("q")) == bvariant("q"), "bvariant string equal");
        expect_true(!(bvariant(xstring("q")) == bvariant("r")), "bvariant string not equal");
        expect_true(bvariant(true) == bvariant(true) && !(bvariant(true) == bvariant(false)), "bvariant bool equality");
        expect_true(bvariant(uint16_t(3)) == bvariant(uint16_t(3)), "bvariant u16 equal");
        expect_true(bvariant(uint64_t(3)) == bvariant(uint64_t(3)), "bvariant uint64 equal");
        expect_true(bvariant(vec2i{1, 2}) == bvariant(vec2i{1, 2}) && !(bvariant(vec2i{1, 2}) == bvariant(vec2i{2, 1})),
          "bvariant vec2i equality");
        expect_true(
          bvariant(tile2i(1, 2)) == bvariant(tile2i(1, 2)) && !(bvariant(tile2i(1, 2)) == bvariant(tile2i(2, 1))),
          "bvariant tile2i equality");
        const grid_area a(tile2i(1, 2), tile2i(3, 4));
        const grid_area b(tile2i(1, 2), tile2i(3, 5));
        expect_true(bvariant(a) == bvariant(a) && !(bvariant(a) == bvariant(b)), "bvariant grid_area equality");
        int x = 0, y = 0;
        expect_true(bvariant((void*)&x) == bvariant((void*)&x) && !(bvariant((void*)&x) == bvariant((void*)&y)),
          "bvariant ptr equality");
    }

    {
        int marker = 0;
        expect_true(bvariant(xstring("")).is_null() && !bvariant(xstring("a")).is_null(), "bvariant is_null string");
        expect_true(bvariant(int32_t(0)).is_null() && !bvariant(int32_t(1)).is_null(), "bvariant is_null int32");
        expect_true(bvariant(uint32_t(0)).is_null() && !bvariant(uint32_t(1)).is_null(), "bvariant is_null uint32");
        expect_true(bvariant(uint64_t(0)).is_null() && !bvariant(uint64_t(1)).is_null(), "bvariant is_null uint64");
        expect_true(bvariant((void*)nullptr).is_null() && !bvariant((void*)&marker).is_null(), "bvariant is_null ptr");
        expect_true(!bvariant(false).is_null() && !bvariant(0.f).is_null() && !bvariant(uint16_t(0)).is_null(),
          "bvariant is_null is false for bool, float and u16");
    }

    {
        expect_true(bvariant(true).to_bool() && !bvariant(false).to_bool(), "bvariant to_bool bool");
        expect_true(bvariant(int32_t(-1)).to_bool() && !bvariant(int32_t(0)).to_bool(), "bvariant to_bool int32");
        expect_true(bvariant(uint32_t(2)).to_bool() && !bvariant(uint32_t(0)).to_bool(), "bvariant to_bool uint32");
        expect_true(bvariant(uint64_t(2)).to_bool() && !bvariant(uint64_t(0)).to_bool(), "bvariant to_bool uint64");
        expect_true(bvariant(uint16_t(2)).to_bool() && !bvariant(uint16_t(0)).to_bool(), "bvariant to_bool u16");
        expect_true(bvariant(0.5f).to_bool() && !bvariant(0.f).to_bool(), "bvariant to_bool float");
    }

    {
        expect_eq_str(bvariant(true).to_str(), "true", "bvariant to_str bool");
        expect_eq_str(bvariant(uint16_t(7)).to_str(), "7", "bvariant to_str u16");
        expect_eq_str(bvariant(int32_t(-7)).to_str(), "-7", "bvariant to_str int32");
        expect_eq_str(bvariant(uint32_t(4000000000u)).to_str(), "4000000000", "bvariant to_str uint32");
        expect_eq_str(bvariant(uint64_t(1) << 40).to_str(), "1099511627776", "bvariant to_str uint64");
        expect_eq_str(bvariant(1.5f).to_str(), "1.500000", "bvariant to_str float");
        expect_eq_str(bvariant(xstring("txt")).to_str(), "txt", "bvariant to_str string");
        expect_eq_str(bvariant(vec2i{3, -4}).to_str(), "3,-4", "bvariant to_str vec2i");
        expect_eq_str(bvariant(tile2i(5, 6)).to_str(), "5,6", "bvariant to_str tile2i");
        expect_eq_str(bvariant(grid_area(tile2i(1, 2), tile2i(3, 4))).to_str(), "1,2,3,4", "bvariant to_str grid_area");
    }

    {
        expect_eq_str(bvariant(false).debug_str(), "bool[FALSE]", "bvariant debug_str bool");
        expect_eq_str(bvariant(uint16_t(7)).debug_str(), "u16[7]", "bvariant debug_str u16");
        expect_eq_str(bvariant(int32_t(-7)).debug_str(), "int32[-7]", "bvariant debug_str int32");
        expect_eq_str(bvariant(uint32_t(7)).debug_str(), "uint32[7]", "bvariant debug_str uint32");
        expect_eq_str(bvariant(uint64_t(7)).debug_str(), "uint64[7]", "bvariant debug_str uint64");
        expect_eq_str(bvariant(1.5f).debug_str(), "float[1.500000]", "bvariant debug_str float");
        expect_eq_str(bvariant(xstring("txt")).debug_str(), "str[txt]", "bvariant debug_str string");
        expect_eq_str(bvariant(vec2i{3, -4}).debug_str(), "vec2i[3,-4]", "bvariant debug_str vec2i");
        expect_eq_str(bvariant(tile2i(5, 6)).debug_str(), "tile2i[5,6]", "bvariant debug_str tile2i");
        expect_eq_str(bvariant(grid_area(tile2i(1, 2), tile2i(3, 4))).debug_str(), "grid_area[1,2,3,4]",
          "bvariant debug_str grid_area");
    }

    {
        const uint8_t types[] = {bvariant::etype_bool, bvariant::etype_int32, bvariant::etype_uint32,
          bvariant::etype_uint64, bvariant::etype_float, bvariant::etype_ptr, bvariant::etype_str, bvariant::etype_u16,
          bvariant::etype_vec2i, bvariant::etype_tile2i, bvariant::etype_grid_area};
        for (uint8_t type : types) {
            bvariant v;
            v.acquire(type);
            expect_true(v.value_type() == type && !v.is_empty(), "bvariant acquire sets the type");
            v.release();
            expect_true(v.is_empty(), "bvariant release empties it");
        }
        bvariant v;
        v.acquire(bvariant::etype_int32);
        expect_true(v.as_int32() == 0, "bvariant acquire value-initializes");
        v.release();
        v.acquire(bvariant::etype_str);
        expect_true(v.as_str().empty(), "bvariant acquire string is empty");
    }

    {
        bvariant_map m = {{"name", "box"}, {"flag", true}, {"count", 3}, {"big", uint64_t(5)}, {"ratio", 0.25f},
          {"pos", vec2i{1, 2}}, {"tile", tile2i(3, 4)}, {"id", uint32_t(9)}};
        expect_true(m.values.size() == 8, "bvariant_map initializer list keeps every entry");
        expect_true(m.values[0].first == "name" && m.values[7].first == "id", "bvariant_map keeps insertion order");
        expect_true(m.s("name") == "box" && m.bool_or_def("flag", false) && m.i32("count") == 3 && m.u64("big") == 5
                      && m.f("ratio") == 0.25f && m.u32("id") == 9,
          "bvariant_map typed getters");
        expect_true(
          m.vec2i_or_def("pos", vec2i{0, 0}) == vec2i(1, 2) && m.tile2i_or_def("tile", tile2i(0, 0)) == tile2i(3, 4),
          "bvariant_map vec2i/tile2i getters");
        expect_true(m.i32("missing", -1) == -1 && m.s("missing", xstring("d")) == "d" && m.f("name", 7.f) == 7.f
                      && m.u32("count", 8) == 8 && m.u64("count", 8) == 8 && !m.bool_or_def("count", false)
                      && m.vec2i_or_def("count", vec2i{4, 4}) == vec2i(4, 4)
                      && m.tile2i_or_def("count", tile2i(4, 4)) == tile2i(4, 4),
          "bvariant_map getters fall back to the default for missing or other-typed keys");
        expect_true(m.n("flag") == 1.f && m.n("count") == 3.f && m.n("big") == 5.f && m.n("ratio") == 0.25f
                      && m.n("id") == 9.f && m.n("name") == 0.f && m.n("missing") == 0.f,
          "bvariant_map n converts numbers");
        expect_true(m.value_type("pos") == bvariant::etype_vec2i && m.value_type("missing") == bvariant::etype_none,
          "bvariant_map value_type");
        expect_true(m.value("missing").is_empty() && &m.value("missing") == &m.def(),
          "bvariant_map missing value is def");

        const bvariant_map& cm = m;
        expect_true(cm["count"].as_int32() == 3 && cm["missing"].is_empty(), "bvariant_map const operator[]");
        expect_true(m.values.size() == 8, "bvariant_map const operator[] does not insert");

        m["count"] = int32_t(4);
        expect_true(m.i32("count") == 4 && m.values.size() == 8, "bvariant_map operator[] updates in place");
        m["extra"] = xstring("x");
        expect_true(m.values.size() == 9 && m.values.back().first == "extra" && m.s("extra") == "x",
          "bvariant_map operator[] appends a missing key");

        expect_true(m.find("pos") != m.end() && m.find("pos")->second.is_vec2i() && m.find("nope") == m.end(),
          "bvariant_map find");
        expect_true(cm.find("tile") != cm.end() && cm.find("nope") == cm.cend(), "bvariant_map const find");

        int iterated = 0;
        for (const auto& p : cm) {
            iterated += p.second.is_empty() ? 0 : 1;
        }
        expect_true(iterated == 9, "bvariant_map iteration visits every entry");

        bvariant_map copy(m);
        expect_true(copy.values.size() == 9 && copy.s("extra") == "x" && copy.i32("count") == 4, "bvariant_map copy");
        copy["count"] = int32_t(5);
        expect_true(m.i32("count") == 4, "bvariant_map copy is independent");

        bvariant_map assigned;
        assigned = m;
        expect_true(assigned.values.size() == 9 && assigned.s("name") == "box", "bvariant_map copy assignment");

        bvariant_map moved(std::move(copy));
        expect_true(moved.values.size() == 9 && moved.i32("count") == 5, "bvariant_map move constructor");

        bvariant_map move_assigned;
        move_assigned = std::move(moved);
        expect_true(move_assigned.values.size() == 9 && move_assigned.i32("count") == 5,
          "bvariant_map move assignment");
    }

    {
        bvariant_map::scoped pooled;
        expect_true(pooled->values.empty(), "bvariant_map pooled map starts empty");
        (*pooled)["k"] = int32_t(1);
        expect_true(pooled->i32("k") == 1, "bvariant_map pooled map is usable");
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
    run_bvariant_unit_tests();
    run_xvalue_unit_tests();
}

hvector<xstring, 16> list_test_files() {
    hvector<xstring, 16> found_tests = list_integral_test_files();

    logs::info("[integraltests] %d test file(s)", (int)found_tests.size());
    for (const auto &p : found_tests) {
        logs::info("[integraltests]   - %s", p.c_str());
    }

    const xstring only = g_args.get_integraltest_only().tolower();
    if (only.empty()) {
        return found_tests;
    }

    // Tests whose name starts with NAME ("99_tmp" -> every 99_tmp_*, "06" -> 06_* but not 106_*);
    // only when none does, every test whose name contains NAME.
    auto stem_of = [](const xstring& p) {
        std::string stem = p.c_str();
        const size_t slash = stem.find_last_of("/\\");
        if (slash != std::string::npos) {
            stem = stem.substr(slash + 1);
        }
        const size_t dot = stem.rfind('.');
        if (dot != std::string::npos) {
            stem = stem.substr(0, dot);
        }
        std::transform(stem.begin(), stem.end(), stem.begin(), [](unsigned char c) { return (char)std::tolower(c); });
        return stem;
    };

    hvector<xstring, 16> by_prefix;
    hvector<xstring, 16> by_substring;
    for (const auto& p : found_tests) {
        const std::string stem = stem_of(p);
        if (stem.rfind(only.c_str(), 0) == 0) {
            by_prefix.push_back(p);
        } else if (stem.find(only.c_str()) != std::string::npos) {
            by_substring.push_back(p);
        }
    }

    if (!by_prefix.empty()) {
        return by_prefix;
    }
    if (!by_substring.empty()) {
        return by_substring;
    }

    logs::error("[integraltests] cant find '%s' in tests", only.c_str());
    return {};
}

void pop_to(js_State *J, int baseline) {
    while (J->gettop() > baseline) {
        js_pop(J, 1);
    }
}

// Call a global function with 0 args, swallowing return value and resetting
// the sticky vm.have_error flag. Caller must have verified existence via
// js_vm_global_is_callable. Returns true on success.
bool call_global_void(js_State *J, const char *name) {
    int baseline = J->gettop();
    js_vm_reset_error();
    js_getglobal(J, name);
    js_pushnull(J); // `this` (functions don't use it)
    int ok = js_vm_trypcall(J, 0);
    pop_to(J, baseline);
    return ok != 0;
}

// Global function declarations are non-configurable, so they cannot be deleted; overwrite instead.
static void clear_global(js_State* J, const char* name) {
    js_pushnull(J);
    js_setglobal(J, name);
}

static constexpr int kMaxFramesPerTest = 600;

static std::string test_stem(const xstring& name) {
    std::string stem = name.c_str();
    const size_t slash = stem.find_last_of("/\\");
    if (slash != std::string::npos) {
        stem = stem.substr(slash + 1);
    }
    const size_t dot = stem.rfind('.');
    if (dot != std::string::npos) {
        stem = stem.substr(0, dot);
    }
    return stem;
}

static void write_test_result(const xstring& name, const std::string& reason, Uint32 ms) {
    std::error_code ec;
    const std::filesystem::path dir = std::filesystem::path(platform.user_directory()) / "results";
    std::filesystem::create_directories(dir, ec);
    std::ofstream out(dir / (test_stem(name) + ".result"), std::ios::binary | std::ios::trunc);
    if (!out) {
        logs::error("[integraltests] cannot write result file for %s", name.c_str());
        return;
    }
    out << "test=" << name.c_str() << "\n";
    out << "status=" << (reason.empty() ? "PASS" : "FAIL") << "\n";
    out << "ms=" << ms << "\n";
    if (!reason.empty()) {
        out << "reason=" << reason << "\n";
        for (const std::string& line : test_log_lines_with({"FAIL", "error:"}, 20)) {
            out << "log=" << line << "\n";
        }
    }
}

static std::string run_one_test(const xstring& name, const game_features::snapshot_t& features_at_start) {
    logs::info("[integraltests] >> %s", name.c_str());
    logs::flush();
    test_log_mark_test_start();

    // Fresh map/UI for every test — leftover city/editor/events otherwise bleed.
    test_reset_session_between_tests();
    // crt_rand is not part of the session reset, so without this a test inherits the previous one's stream.
    anti_scum_srand(1);

    g_app.quit = false;
    SDL_FlushEvent(SDL_USEREVENT);

    game_features::restore(features_at_start);
    game_features::gameopt_ironwill.set(false);
    // A test may rebuild the VM (disabling a mod does), which frees the previous js_State.
    js_State* J = js_vm_state();
    // Otherwise a test without run_test()/check_valid() would run the previous test's.
    clear_global(J, "run_test");
    clear_global(J, "check_valid");
    const int stale = js_vm_force_idle_stack();
    if (stale > 0) {
        logs::info("[test:%s] cleared %d stale MuJS stack slot(s) before test", name.c_str(), stale);
    }

    const int load_baseline = J->gettop();
    js_vm_reset_error();
    logs::info("[test:%s] loading script", name.c_str());
    if (!js_vm_load_file_and_exec(name.c_str())) {
        logs::error("[test:%s] FAIL: load error", name.c_str());
        pop_to(J, load_baseline);
        js_vm_reset_error();
        return "load error";
    }
    js_vm_sync({});           // run include() queued while loading the test script
    pop_to(J, load_baseline); // discard top-level result residue
    logs::info("[test:%s] script loaded", name.c_str());
    const uint32_t vm_generation = js_vm_generation();

    // run_test
    if (!js_vm_global_is_callable(J, "run_test")) {
        logs::error("[test:%s] FAIL: missing run_test()", name.c_str());
        return "missing run_test()";
    }
    g_test_signal_ready = false;
    logs::info("[test:%s] calling run_test()", name.c_str());
    if (!call_global_void(J, "run_test")) {
        logs::error("[test:%s] FAIL: run_test threw", name.c_str());
        return "run_test threw";
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
        if (const char* slash = std::strrchr(leaf, '/')) {
            leaf = slash + 1;
        }
        if (const char* bslash = std::strrchr(leaf, '\\')) {
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
        logs::error("[test:%s] FAIL: timeout after %d frames (forgot __test_signal_ready?)", name.c_str(), frames);
        return "timeout, no __test_signal_ready";
    }
    logs::info("[test:%s] finished after %d frame(s)", name.c_str(), frames);

    if (test_log_contains("!!! TypeError:")) {
        logs::error("[test:%s] FAIL: !!! TypeError: found in log", name.c_str());
        return "TypeError in log";
    }

    if (test_log_contains("[record-overflow]")) {
        logs::error("[test:%s] FAIL: a building record overflowed its save slot (see [record-overflow])", name.c_str());
        return "building record overflow";
    }

    if (test_log_contains("[stub-record]")) {
        logs::error("[test:%s] FAIL: record 0 of buildings or figures was written (see [stub-record])", name.c_str());
        return "stub record written";
    }

    if (js_vm_generation() != vm_generation) {
        // The rebuilt VM no longer has this test's globals; load the file again for check_valid().
        J = js_vm_state();
        logs::info("[test:%s] VM was rebuilt during the test, reloading the script", name.c_str());
        js_vm_reset_error();
        const int reload_baseline = J->gettop();
        js_vm_load_file_and_exec(name.c_str());
        js_vm_sync({});
        pop_to(J, reload_baseline);
    }

    // check_valid -> bool
    if (!js_vm_global_is_callable(J, "check_valid")) {
        logs::error("[test:%s] FAIL: missing check_valid()", name.c_str());
        return "missing check_valid()";
    }
    const int cv_baseline = J->gettop();
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

    std::string reason;
    if (!cv_ok) {
        logs::error("[test:%s] FAIL: check_valid threw", name.c_str());
        reason = "check_valid threw";
    } else if (!result) {
        logs::error("[test:%s] FAIL (check_valid returned false)", name.c_str());
        reason = "check_valid returned false";
    }

    // MuJS value stack must be idle-empty between tests (catches hot-reload leaks).
    const int leaked = js_vm_force_idle_stack();
    if (leaked > 0) {
        logs::error("[test:%s] FAIL: MuJS stack not idle after test (leaked %d slot(s))", name.c_str(), leaked);
        reason = "MuJS stack not idle after test";
    }
    return reason;
}

int run_js_tests() {
    if (!js_vm_state()) {
        logs::error("[integraltests] JS VM not initialized");
        return 1;
    }

    auto files = list_test_files();
    const xstring shard = g_args.get_str("integraltest_shard");
    if (!shard.empty()) {
        int index = -1;
        int count = 0;
        if (std::sscanf(shard.c_str(), "%d/%d", &index, &count) != 2 || count < 1 || index < 0 || index >= count) {
            logs::error("[integraltests] bad --integraltest-shard %s, expected I/N with 0 <= I < N", shard.c_str());
            return 1;
        }
        hvector<xstring, 16> mine;
        for (int i = 0; i < (int)files.size(); ++i) {
            if (i % count == index) {
                mine.push_back(files[i]);
            }
        }
        files = mine;
        logs::info("[integraltests] shard %d/%d: %d test(s)", index, count, (int)files.size());
        if (files.empty()) {
            logs::info("[integraltests] 0 passed, 0 failed");
            return 0;
        }
    }
    if (files.empty()) {
        if (!g_args.get_integraltest_only().empty()) {
            // user asked for a specific test that doesn't exist — that's a hard failure
            return 1;
        }
        logs::error("[integraltests] no .js test files found under tests/");
        return 0;
    }

    GamestateIO::set_replay_autosave(false);
    game_features::gameopt_monthly_autosave.set(false);
    const game_features::snapshot_t features_at_start = game_features::snapshot();

    int passed = 0;
    int failed = 0;
    for (const auto& name : files) {
        const Uint32 started = SDL_GetTicks();
        const std::string reason = run_one_test(name, features_at_start);
        const Uint32 ms = SDL_GetTicks() - started;
        if (reason.empty()) {
            logs::info("[test:%s] PASS", name.c_str());
            ++passed;
        } else {
            ++failed;
        }
        write_test_result(name, reason, ms);
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

hvector<xstring, 16> list_integral_test_files() {
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
    return found_tests;
}

int run_integral_tests() {
    failure_count = 0;
    logs::info("[integraltests] start");

    run_integral_tests_impl();
    int js_rc = run_js_tests();

    const xstring& baseline = g_args.get_str("config_keys_baseline");
    if (!baseline.empty()) {
        failure_count += archive_check::check_baseline(baseline.c_str(), g_args.is("config_keys_update", false));
    }

    if (failure_count == 0 && js_rc == 0) {
        logs::info("[integraltests] all checks passed");
        return 0;
    }

    logs::error("[integraltests] finished with %d C++ failure(s), JS rc=%d", failure_count, js_rc);
    return 1;
}

namespace {

    struct parallel_result {
        std::string test;
        std::string shard;
        std::string status;
        std::string reason;
        std::vector<std::string> log;
        long ms = 0;
    };

    std::string read_text(const std::filesystem::path& path) {
        std::ifstream in(path, std::ios::binary);
        return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }

    std::vector<std::string> split_lines(const std::string& text) {
        std::vector<std::string> lines;
        size_t start = 0;
        while (start < text.size()) {
            size_t end = text.find('\n', start);
            if (end == std::string::npos) {
                end = text.size();
            }
            std::string line = text.substr(start, end - start);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            lines.push_back(line);
            start = end + 1;
        }
        return lines;
    }

    parallel_result read_result(const std::filesystem::path& path, const std::string& shard) {
        parallel_result r;
        r.shard = shard;
        for (const std::string& line : split_lines(read_text(path))) {
            const size_t eq = line.find('=');
            if (eq == std::string::npos) {
                continue;
            }
            const std::string key = line.substr(0, eq);
            const std::string value = line.substr(eq + 1);
            if (key == "test") {
                r.test = value;
            } else if (key == "status") {
                r.status = value;
            } else if (key == "reason") {
                r.reason = value;
            } else if (key == "ms") {
                r.ms = std::atol(value.c_str());
            } else if (key == "log") {
                r.log.push_back(value);
            }
        }
        return r;
    }

    std::vector<std::string> shard_problems(const std::filesystem::path& log_path, const std::string& shard, int rc) {
        std::vector<std::string> problems;
        std::error_code ec;
        if (!std::filesystem::exists(log_path, ec)) {
            problems.push_back(shard + ": no log, rc=" + std::to_string(rc));
            return problems;
        }
        bool summary = false;
        for (const std::string& line : split_lines(read_text(log_path))) {
            if (line.find("[integraltests] ") != std::string::npos && line.find(" passed, ") != std::string::npos) {
                summary = true;
            }
            if (line.find("[config-keys] FAIL") != std::string::npos
                || line.find("[integraltests] finished with") != std::string::npos
                || line.find("[integraltests] FAIL") != std::string::npos) {
                problems.push_back(shard + ": " + line);
            }
        }
        if (!summary) {
            problems.push_back(shard + ": no suite summary in the log (crashed or killed), rc=" + std::to_string(rc));
        } else if (rc != 0 && problems.empty()) {
            problems.push_back(shard + ": exit code " + std::to_string(rc));
        }
        return problems;
    }

} // namespace

int integral_tests_parallel_jobs() {
    if (!g_args.is_integral_tests() || !g_args.get_str("integraltest_shard").empty()) {
        return 0;
    }
    const xstring& value = g_args.get_str("integraltest_jobs");
    const int jobs = value.empty() ? 0 : std::atoi(value.c_str());
    return jobs > 1 ? jobs : 0;
}

int run_integral_tests_parallel(int argc, char** argv, int jobs) {
    namespace fs = std::filesystem;
    if (g_args.is("config_keys_update", false)) {
        logs::error("[integraltests] --config-keys-update needs the whole suite in "
                    "one process, drop --integraltest-jobs");
        return 1;
    }

    std::error_code ec;
    const fs::path base = fs::absolute(fs::path(platform.user_directory()), ec);
    std::vector<std::string> args_common;
    for (int i = 0; i < argc; ++i) {
        const std::string arg = argv[i] ? argv[i] : "";
        if ((arg == "--integraltest-jobs" || arg == "--user-dir") && i + 1 < argc) {
            ++i;
            continue;
        }
        args_common.push_back(arg);
    }

    const Uint32 started = SDL_GetTicks();
    std::vector<child_process> children(jobs);
    std::vector<std::string> names(jobs);
    for (int i = 0; i < jobs; ++i) {
        names[i] = "shard-" + std::to_string(i);
        const fs::path dir = base / names[i];
        fs::remove_all(dir, ec);
        fs::create_directories(dir, ec);
        std::vector<std::string> args = args_common;
        args.push_back("--integraltest-shard");
        args.push_back(std::to_string(i) + "/" + std::to_string(jobs));
        args.push_back("--user-dir");
        args.push_back(dir.generic_string());
        if (!child_process_start(args, children[i])) {
            logs::error("[integraltests] cannot start %s", names[i].c_str());
        }
    }

    std::vector<int> rcs(jobs);
    for (int i = 0; i < jobs; ++i) {
        rcs[i] = child_process_wait(children[i]);
    }
    const double wall = (SDL_GetTicks() - started) / 1000.0;

    std::vector<parallel_result> results;
    std::vector<std::string> problems;
    for (int i = 0; i < jobs; ++i) {
        const fs::path dir = base / names[i];
        std::vector<fs::path> files;
        for (const auto& entry : fs::directory_iterator(dir / "results", ec)) {
            if (entry.path().extension() == ".result") {
                files.push_back(entry.path());
            }
        }
        std::sort(files.begin(), files.end());
        for (const fs::path& file : files) {
            results.push_back(read_result(file, names[i]));
        }
        for (const std::string& p : shard_problems(dir / "akhenaten-log.txt", names[i], rcs[i])) {
            problems.push_back(p);
        }
    }

    std::vector<const parallel_result*> failed;
    std::vector<const parallel_result*> slowest;
    long total_ms = 0;
    for (const parallel_result& r : results) {
        total_ms += r.ms;
        slowest.push_back(&r);
        if (r.status != "PASS") {
            failed.push_back(&r);
        }
    }
    const int passed = (int)(results.size() - failed.size());
    std::sort(slowest.begin(), slowest.end(),
      [](const parallel_result* a, const parallel_result* b) { return a->ms > b->ms; });

    std::string text;
    char line[1024];
    for (const parallel_result* r : failed) {
        std::snprintf(line, sizeof(line), "FAIL %s (%s, %ld ms): %s\n", r->test.c_str(), r->shard.c_str(), r->ms,
          r->reason.c_str());
        text += line;
        for (const std::string& l : r->log) {
            text += "     " + l + "\n";
        }
    }
    text += "\nslowest:\n";
    for (size_t i = 0; i < slowest.size() && i < 15; ++i) {
        std::snprintf(line, sizeof(line), "  %7ld ms  %s\n", slowest[i]->ms, slowest[i]->test.c_str());
        text += line;
    }
    text += "\n";
    for (const std::string& p : problems) {
        text += "PROBLEM " + p + "\n";
    }
    std::snprintf(line, sizeof(line),
      "[integraltests] %d passed, %d failed, %d problem(s), test "
      "time %.1f s in %d shard(s), wall %.1f s\n",
      passed, (int)failed.size(), (int)problems.size(), total_ms / 1000.0, jobs, wall);
    text += line;

    std::string md = "## Integral tests\n\n";
    std::snprintf(line, sizeof(line),
      "**%d passed, %d failed, %d problem(s)** (%d tests, %.1f s of "
      "test time in %d shard(s))\n\n",
      passed, (int)failed.size(), (int)problems.size(), (int)results.size(), total_ms / 1000.0, jobs);
    md += line;
    if (!failed.empty()) {
        md += "| Test | Reason |\n|------|--------|\n";
        for (const parallel_result* r : failed) {
            md += "| " + r->test + " | " + r->reason + " |\n";
        }
        md += "\n";
    }
    for (const std::string& p : problems) {
        md += "- " + p + "\n";
    }

    std::ofstream(base / "summary.txt", std::ios::binary | std::ios::trunc) << text;
    std::ofstream(base / "summary.md", std::ios::binary | std::ios::trunc) << md;
    std::ofstream(base / "counts.txt", std::ios::binary | std::ios::trunc)
      << "passed=" << passed << "\nfailed=" << failed.size() + problems.size() << "\n";

    for (const std::string& l : split_lines(text)) {
        logs::info("%s", l.c_str());
    }

    return failed.empty() && problems.empty() && !results.empty() ? 0 : 1;
}
