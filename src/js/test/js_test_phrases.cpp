#include "js/test/js_test_common.h"
#include "city/city.h"
#include "city/city_problems.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "figure/figure.h"
#include "figure/figure_phrase.h"

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

// Puts the city into a state with no problem at all: every OG weight is calm.
static void __test_city_problem_calm() {
    g_city.health.value = 100;
    g_city.resource.food_supply_months = 12;
    for (auto& category : g_city.labor.categories) {
        category.workers_allocated = 0;
        category.workers_needed = 0;
    }
    for (auto& god : g_city.religion.gods) {
        god.mood = 100;
    }
    g_city.kingdome.rating = 100;
    g_city.population.current = 0;
    g_city.labor.workers_unemployed = 0;
    g_city.labor.unemployment_percentage = 0;
    g_city.labor.workers_needed = 0;
    g_city.avg_coverage.average_entertainment = 100;
    g_city.sentiment.value = 100;
}
ANK_FUNCTION(__test_city_problem_calm)

static void __test_city_problem_set(xstring key, int value) {
    if (key == "health") {
        g_city.health.value = value;
    } else if (key == "food_months") {
        g_city.resource.food_supply_months = (uint8_t)value;
    } else if (key == "kingdom") {
        g_city.kingdome.rating = (uint8_t)value;
    } else if (key == "entertainment") {
        g_city.avg_coverage.average_entertainment = value;
    } else if (key == "sentiment") {
        g_city.sentiment.value = value;
    } else if (key == "low_mood_cause") {
        g_city.sentiment.low_mood_cause = value;
    } else if (key == "unemployment_percentage") {
        g_city.labor.unemployment_percentage = (int8_t)value;
    } else if (key == "workers_needed") {
        g_city.labor.workers_needed = value;
    } else if (key == "god_mood") {
        for (auto& god : g_city.religion.gods) {
            god.mood = (uint8_t)value;
        }
    }
}
ANK_FUNCTION_2(__test_city_problem_set)

static void __test_figure_set_phrase_state(int fid, int action, int min_max_seen) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    f->action_state = (short)action;
    f->min_max_seen = (uint8_t)min_max_seen;
}
ANK_FUNCTION_3(__test_figure_set_phrase_state)

// Runs the OG phrase choice; returns "group:phrase:file".
static xstring __test_figure_phrase(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return {};
    }
    f->dcast()->setup_phrase();
    bstring128 s;
    s.printf("%d:%d:%s", f->phrase_group, f->phrase_id, f->phrase_sound.c_str());
    return xstring(s.c_str());
}
ANK_FUNCTION_1(__test_figure_phrase)

static void __test_figure_set_phrase(int fid, int group, int phrase) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    f->phrase_group = (uint8_t)group;
    f->phrase_id = (int8_t)phrase;
    figure_phrase_apply(*f);
}
ANK_FUNCTION_3(__test_figure_set_phrase)

// The figure's current phrase without choosing a new one: "group:phrase:file".
static xstring __test_figure_phrase_now(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return {};
    }
    bstring128 s;
    s.printf("%d:%d:%s", f->phrase_group, f->phrase_id, f->phrase_sound.c_str());
    return xstring(s.c_str());
}
ANK_FUNCTION_1(__test_figure_phrase_now)
