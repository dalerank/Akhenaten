#include "integral_tests.h"

#include "core/log.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "platform/version.hpp"

#include "cmrc/cmrc.hpp"
#include <SDL.h>
#include <string>
#include <string_view>

CMRC_DECLARE(akhenaten);

namespace {

int failure_count;

void expect_true(bool ok, const char *expr)
{
    if (!ok) {
        logs::error("[integraltests] FAIL: %s", expr);
        failure_count++;
    }
}

void run_integral_tests_impl()
{
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

} // namespace

int run_integral_tests()
{
    failure_count = 0;
    logs::info("[integraltests] start");

    run_integral_tests_impl();

    if (failure_count == 0) {
        logs::info("[integraltests] all checks passed");
        return 0;
    }

    logs::error("[integraltests] finished with %d failure(s)", failure_count);
    return 1;
}
