#include "integral_tests.h"

#include "core/log.h"
#include "core/vec2i.h"
#include "platform/version.hpp"

#include <SDL.h>

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
