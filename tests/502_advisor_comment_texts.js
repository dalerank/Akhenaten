// OG window/advisor_comments.c: the comment text (group 61) and the advisor the comment window offers,
// chosen by advisor_comment_rules; and chief_advisor_button_row (which rows open no comment).
// Markers:
//   [test-marker] advisor_comments_people_ok
//   [test-marker] advisor_comments_food_ok
//   [test-marker] advisor_comments_religion_ok
//   [test-marker] advisor_comments_rest_ok

var t502_failed = false

var t502_base = {
    sentiment: 60, low_mood_cause: 0, migration_direction: 0, kingdom_soldiers: 0, enemies: 0, soldiers: 0,
    newcomers: 0, refused_immigrants_today: 0, room_in_houses: 10, migration_percentage: 100, no_immigration_cause: 0,
    unemployment_percentage: 0, workers_needed: 0, kingdom_supplies_grain: 0, food_supply_months: 3,
    food_stored_total: 300, food_needed_per_month: 100, population: 100, food_supply_percentage: 100, health: 50,
    god_mood0: 50, god_mood1: 50, god_mood2: 50, god_mood3: 50, god_mood4: 50, taxes_collected: 0,
    taxes_uncollected: 0, treasury: 1000, balance_last_year: 1000, crimes_this_month: 0, gold_stolen_this_month: 0,
    invasion_running: 0, troops_requested: 0, troops_away: 0, requests_waiting: 0, flood_quality: 50, flood_month: 2
}

function t502_set(overrides) {
    __test_advisor_state_clear()
    for (var k in t502_base) {
        __test_advisor_state_set(k, (overrides[k] !== undefined) ? overrides[k] : t502_base[k])
    }
}

function t502_expect(name, topic, overrides, text, advisor) {
    t502_set(overrides)
    var c = __advisor_comment(topic)
    if (c.text !== text || (advisor !== undefined && c.advisor !== advisor)) {
        __log_info_native('[test:502] ' + name + ': text=' + c.text + ' advisor=' + c.advisor + ', want ' + text + ' / ' + advisor)
        t502_failed = true
    }
}

function t502_expect_opens(name, topic, overrides, want) {
    t502_set(overrides)
    var got = !!__chief_advisor_row_opens_comment(topic)
    if (got !== want) {
        __log_info_native('[test:502] ' + name + ': opens=' + got + ', want ' + want)
        t502_failed = true
    }
}

function t502_mark(marker) {
    if (!t502_failed) {
        __log_marker(marker)
    }
}

function t502_people() {
    var S = ADVISOR_COMMENT_SENTIMENT
    t502_expect('low food', S, { sentiment: 30, low_mood_cause: 1 }, 38, ADVISOR_POPULATION)
    t502_expect('low jobs', S, { sentiment: 49, low_mood_cause: 2 }, 39, ADVISOR_LABOR)
    t502_expect('low taxes', S, { sentiment: 10, low_mood_cause: 3 }, 40, ADVISOR_FINANCIAL)
    t502_expect('fair', S, { sentiment: 60, low_mood_cause: 3 }, 42, ADVISOR_NONE)
    t502_expect('top', S, { sentiment: 100 }, -1)
    t502_expect_opens('top row', S, { sentiment: 100 }, false)
    t502_expect_opens('fair row', S, { sentiment: 99 }, true)

    var M = ADVISOR_COMMENT_MIGRATION
    t502_expect('stay jobs', M, { no_immigration_cause: 1 }, 71, ADVISOR_LABOR)
    t502_expect('stay food', M, { no_immigration_cause: 2 }, 72, ADVISOR_POPULATION)
    t502_expect('no housing', M, { room_in_houses: 0 }, 69, ADVISOR_POPULATION)
    t502_expect_opens('war row', M, { enemies: 2, kingdom_soldiers: 2 }, false)
    t502_expect_opens('war 3 row', M, { enemies: 3 }, true)

    var E = ADVISOR_COMMENT_EMPLOYMENT
    t502_expect('balanced', E, { unemployment_percentage: 5, workers_needed: 5 }, 93, ADVISOR_LABOR)
    t502_expect('u18', E, { unemployment_percentage: 18 }, 85)
    t502_expect('u17', E, { unemployment_percentage: 17 }, 86)
    t502_expect('u11', E, { unemployment_percentage: 11 }, 86)
    t502_expect('u10', E, { unemployment_percentage: 10 }, 87)
    t502_expect('u6', E, { unemployment_percentage: 6 }, 87)
    t502_expect('u1', E, { unemployment_percentage: 1, workers_needed: 6 }, 88)
    t502_expect('n21', E, { workers_needed: 21 }, 89)
    t502_expect('n11', E, { workers_needed: 11 }, 90)
    t502_expect('n6', E, { workers_needed: 6 }, 91)
    t502_mark('advisor_comments_people_ok')
}

function t502_food() {
    var K = ADVISOR_COMMENT_FOOD_STOCKS
    t502_expect('empty', K, { food_supply_months: 0 }, 99, ADVISOR_POPULATION)
    t502_expect('low', K, { food_supply_months: 1, food_stored_total: 49 }, 100)
    t502_expect('enough', K, { food_supply_months: 1, food_stored_total: 50 }, 102)
    var F = ADVISOR_COMMENT_FOOD_CONSUMPTION
    t502_expect('151', F, { food_supply_percentage: 151 }, 217, ADVISOR_POPULATION)
    t502_expect('150', F, { food_supply_percentage: 150 }, 216)
    t502_expect('110', F, { food_supply_percentage: 110 }, 215)
    t502_expect('95', F, { food_supply_percentage: 95 }, 214)
    t502_expect('85', F, { food_supply_percentage: 85 }, 213)
    t502_expect('70', F, { food_supply_percentage: 70 }, 212)
    t502_expect('no pop', F, { population: 0 }, 212)
    t502_mark('advisor_comments_food_ok')
}

function t502_religion() {
    var R = ADVISOR_COMMENT_RELIGION
    t502_expect('appeased', R, {}, 146, ADVISOR_RELIGION)
    t502_expect('one happy', R, { god_mood0: 61 }, 147)
    t502_expect('60 not happy', R, { god_mood0: 60 }, 146)
    t502_expect('two happy', R, { god_mood0: 61, god_mood1: 61 }, 148)
    t502_expect('three happy', R, { god_mood0: 61, god_mood1: 61, god_mood2: 61 }, -1)
    t502_expect('one angry', R, { god_mood3: 39 }, 144)
    t502_expect('40 not angry', R, { god_mood3: 40 }, 146)
    t502_expect('one very angry', R, { god_mood3: 19 }, 145)
    t502_expect('two angry', R, { god_mood0: 39, god_mood3: 39 }, 142)
    t502_expect('three angry', R, { god_mood0: 39, god_mood1: 39, god_mood3: 39 }, 140)
    t502_expect('four angry', R, { god_mood0: 39, god_mood1: 39, god_mood2: 39, god_mood3: 39 }, 138)
    t502_expect('four very angry', R, { god_mood0: 10, god_mood1: 39, god_mood2: 39, god_mood3: 39 }, 139)
    t502_mark('advisor_comments_religion_ok')
}

function t502_rest() {
    t502_expect('health', ADVISOR_COMMENT_HEALTH, { health: 55 }, 119, ADVISOR_HEALTH)
    var M = ADVISOR_COMMENT_FINANCES
    t502_expect('uncollected', M, { taxes_collected: 99, taxes_uncollected: 100 }, 155, ADVISOR_FINANCIAL)
    t502_expect('rising', M, { taxes_collected: 100, taxes_uncollected: 100, treasury: 1001 }, 156)
    t502_expect('steady', M, {}, 157)
    t502_expect('falling', M, { treasury: 999 }, 158)
    var C = ADVISOR_COMMENT_CRIME
    t502_expect('no thefts', C, {}, 169, ADVISOR_FINANCIAL)
    t502_expect('1 theft', C, { crimes_this_month: 1 }, 168)
    t502_expect('2 thefts', C, { crimes_this_month: 2 }, 167)
    t502_expect('5 thefts', C, { crimes_this_month: 5 }, 166)
    t502_expect('10 thefts', C, { crimes_this_month: 10 }, 165)
    var W = ADVISOR_COMMENT_MILITARY
    t502_expect('kingdom soldiers', W, { kingdom_soldiers: 1 }, 181, ADVISOR_MILITARY)
    t502_expect('enemies', W, { enemies: 1 }, 180)
    t502_expect('invasion', W, { invasion_running: 1 }, 179)
    t502_expect('abroad', W, { troops_away: 1, troops_requested: 1 }, 183)
    t502_expect('requested', W, { troops_requested: 1 }, 182)
    t502_expect('watching', W, {}, 178)
    t502_expect('no forces', W, { soldiers: -1 }, 177)
    var K = ADVISOR_COMMENT_KINGDOM
    t502_expect('requests 0', K, {}, 191, ADVISOR_KINGDOM)
    t502_expect('requests 2', K, { requests_waiting: 2 }, 190)
    t502_expect('requests 3', K, { requests_waiting: 3 }, 189)
    t502_expect('requests 4', K, { requests_waiting: 4 }, 189)
    t502_expect('requests 5', K, { requests_waiting: 5 }, 188)
    t502_expect('nile 0', ADVISOR_COMMENT_NILOMETER, { flood_quality: 0 }, 198, ADVISOR_POPULATION)
    t502_expect('nile 50', ADVISOR_COMMENT_NILOMETER, { flood_quality: 50 }, 201)
    t502_mark('advisor_comments_rest_ok')
}

function run_test() {
    __log_info_native('[test:502] advisor comment texts')
    test_ensure_city_session('data/default.map')
    t502_people()
    t502_food()
    t502_religion()
    t502_rest()
    __test_advisor_state_clear()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] advisor_comments_people_ok')
        && __test_find_inlog('[test-marker] advisor_comments_food_ok')
        && __test_find_inlog('[test-marker] advisor_comments_religion_ok')
        && __test_find_inlog('[test-marker] advisor_comments_rest_ok')
}
