#include "js/test/js_test_common.h"
#include "city/city_problems.h"
#include "core/bstring.h"
#include "core/xstring.h"

namespace {

    xstring weights_string(const city_problem_weights& w) {
        bstring128 s;
        for (uint8_t v : w.weights) {
            s.append_fmt("%d,", v);
        }
        s.append_fmt("%d,%d", w.total, w.none ? 1 : 0);
        return xstring(s.c_str());
    }

} // namespace

// Args: health, food months, invasion running, has defenders, favour army sent, workers allocated, workers needed,
// lowest god mood, kingdom rating, population, unemployed, average entertainment. Returns "w0,..,w7,total,none" and
// keeps the weights for __test_city_problem_pick / _next.
static xstring __test_city_problem_weights(js_State* J) {
    city_problem_inputs in;
    in.health = J->to<int>(1);
    in.food_supply_months = J->to<int>(2);
    in.invasion_running = J->to<int>(3) != 0;
    in.has_defenders = J->to<int>(4) != 0;
    in.favour_army_sent = J->to<int>(5) != 0;
    in.workers_allocated = J->to<int>(6);
    in.workers_needed = J->to<int>(7);
    in.lowest_god_mood = J->to<int>(8);
    in.kingdom_rating = J->to<int>(9);
    in.population = J->to<int>(10);
    in.workers_unemployed = J->to<int>(11);
    in.average_entertainment = J->to<int>(12);
    city_problem_last_weights() = city_problem_compute_weights(in);
    return weights_string(city_problem_last_weights());
}
ANK_FUNCTION_RAW(__test_city_problem_weights)

static int __test_city_problem_pick(int random7) {
    return city_problem_pick(city_problem_last_weights(), random7);
}
ANK_FUNCTION_1(__test_city_problem_pick)

static int __test_city_problem_next(int phrase) {
    return city_problem_next(phrase);
}
ANK_FUNCTION_1(__test_city_problem_next)

static bool __test_city_problem_other_loaded(int phrase) {
    return city_problem_other_loaded(phrase);
}
ANK_FUNCTION_1(__test_city_problem_other_loaded)
