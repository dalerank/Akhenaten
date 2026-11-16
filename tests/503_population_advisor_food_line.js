// OG window/advisor/population.c draw_migration_panel: "food for about N people" and the outlook text
// (group 55: 36/39/42/45/48/51 by food supply%*100/pop over 70/85/95/110/150, +1 shrinking, +2 growing).
// Markers:
//   [test-marker] population_food_line_ok

var t503_failed = false

function t503_expect(name, overrides, people, text) {
    __test_advisor_state_clear()
    __test_advisor_state_set('population', 100)
    __test_advisor_state_set('migration_percentage', 0)
    for (var k in overrides) {
        __test_advisor_state_set(k, overrides[k])
    }
    var food = __population_advisor_food()
    if (food.people !== people || food.text !== text) {
        __log_info_native('[test:503] ' + name + ': people=' + food.people + ' text=' + food.text + ', want ' + people + ' / ' + text)
        t503_failed = true
    }
}

function run_test() {
    __log_info_native('[test:503] population advisor food line')
    test_ensure_city_session('data/default.map')
    t503_expect('plenty', { food_supply_percentage: 151 }, 151, 51)
    t503_expect('plenty shrinking', { food_supply_percentage: 151, migration_percentage: -5 }, 151, 52)
    t503_expect('plenty growing', { food_supply_percentage: 151, migration_percentage: 5 }, 151, 53)
    t503_expect('enough', { food_supply_percentage: 111 }, 111, 48)
    t503_expect('just enough', { food_supply_percentage: 96 }, 96, 45)
    t503_expect('a little short', { food_supply_percentage: 86 }, 86, 42)
    t503_expect('short', { food_supply_percentage: 71 }, 71, 39)
    t503_expect('far short', { food_supply_percentage: 70 }, 70, 36)
    t503_expect('no people', { food_supply_percentage: 500, population: 0 }, 500, 36)

    __test_advisor_state_clear()
    var line = advisor_population_food_supply_line()
    if (typeof line !== 'string' || line.length === 0) {
        __log_info_native('[test:503] empty food line')
        t503_failed = true
    }
    if (!t503_failed) {
        __log_marker('population_food_line_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] population_food_line_ok')
}
