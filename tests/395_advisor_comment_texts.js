// OG window/advisor_comments.c: the comment text (group 61) and the advisor the comment window offers,
// chosen by advisor_comment_rules; and chief_advisor_button_row (which rows open no comment).
// Markers:
//   [test-marker] advisor_comments_people_ok
//   [test-marker] advisor_comments_food_ok
//   [test-marker] advisor_comments_religion_ok
//   [test-marker] advisor_comments_rest_ok

var t395_failed = false

var t395_base = {
    sentiment: 60, low_mood_cause: 0, migration_direction: 0, kingdom_soldiers: 0, enemies: 0, soldiers: 0,
    newcomers: 0, refused_immigrants_today: 0, room_in_houses: 10, migration_percentage: 100, no_immigration_cause: 0,
    unemployment_percentage: 0, workers_needed: 0, kingdom_supplies_grain: 0, food_supply_months: 3,
    food_stored_total: 300, food_needed_per_month: 100, population: 100, food_supply_percentage: 100, health: 50,
    god_mood0: 50, god_mood1: 50, god_mood2: 50, god_mood3: 50, god_mood4: 50, taxes_collected: 0,
    taxes_uncollected: 0, treasury: 1000, balance_last_year: 1000, crimes_this_month: 0, gold_stolen_this_month: 0,
    invasion_running: 0, troops_requested: 0, troops_away: 0, requests_waiting: 0, flood_quality: 50, flood_month: 2
}

function t395_set(overrides) {
    __test_advisor_state_clear()
    for (var k in t395_base) {
        __test_advisor_state_set(k, (overrides[k] !== undefined) ? overrides[k] : t395_base[k])
    }
}

function t395_expect(name, topic, overrides, text, advisor) {
    t395_set(overrides)
    var c = __advisor_comment(topic)
    if (c.text !== text || (advisor !== undefined && c.advisor !== advisor)) {
        __log_info_native('[test:395] ' + name + ': text=' + c.text + ' advisor=' + c.advisor + ', want ' + text + ' / ' + advisor)
        t395_failed = true
    }
}

function t395_expect_opens(name, topic, overrides, want) {
    t395_set(overrides)
    var got = !!__chief_advisor_row_opens_comment(topic)
    if (got !== want) {
        __log_info_native('[test:395] ' + name + ': opens=' + got + ', want ' + want)
        t395_failed = true
    }
}

function t395_mark(marker) {
    if (!t395_failed) {
        __log_marker(marker)
    }
}

function t395_people() {
    var S = ADVISOR_COMMENT_SENTIMENT
    t395_expect('low food', S, { sentiment: 30, low_mood_cause: 1 }, 38, ADVISOR_POPULATION)
    t395_expect('low jobs', S, { sentiment: 49, low_mood_cause: 2 }, 39, ADVISOR_LABOR)
    t395_expect('low taxes', S, { sentiment: 10, low_mood_cause: 3 }, 40, ADVISOR_FINANCIAL)
    t395_expect('fair', S, { sentiment: 60, low_mood_cause: 3 }, 42, ADVISOR_NONE)
    t395_expect('top', S, { sentiment: 100 }, -1)
    t395_expect_opens('top row', S, { sentiment: 100 }, false)
    t395_expect_opens('fair row', S, { sentiment: 99 }, true)

    var M = ADVISOR_COMMENT_MIGRATION
    t395_expect('stay jobs', M, { no_immigration_cause: 1 }, 71, ADVISOR_LABOR)
    t395_expect('stay food', M, { no_immigration_cause: 2 }, 72, ADVISOR_POPULATION)
    t395_expect('no housing', M, { room_in_houses: 0 }, 69, ADVISOR_POPULATION)
    t395_expect_opens('war row', M, { enemies: 2, kingdom_soldiers: 2 }, false)
    t395_expect_opens('war 3 row', M, { enemies: 3 }, true)

    var E = ADVISOR_COMMENT_EMPLOYMENT
    t395_expect('balanced', E, { unemployment_percentage: 5, workers_needed: 5 }, 93, ADVISOR_LABOR)
    t395_expect('u18', E, { unemployment_percentage: 18 }, 85)
    t395_expect('u17', E, { unemployment_percentage: 17 }, 86)
    t395_expect('u11', E, { unemployment_percentage: 11 }, 86)
    t395_expect('u10', E, { unemployment_percentage: 10 }, 87)
    t395_expect('u6', E, { unemployment_percentage: 6 }, 87)
    t395_expect('u1', E, { unemployment_percentage: 1, workers_needed: 6 }, 88)
    t395_expect('n21', E, { workers_needed: 21 }, 89)
    t395_expect('n11', E, { workers_needed: 11 }, 90)
    t395_expect('n6', E, { workers_needed: 6 }, 91)
    t395_mark('advisor_comments_people_ok')
}

function t395_food() {
    var K = ADVISOR_COMMENT_FOOD_STOCKS
    t395_expect('empty', K, { food_supply_months: 0 }, 99, ADVISOR_POPULATION)
    t395_expect('low', K, { food_supply_months: 1, food_stored_total: 49 }, 100)
    t395_expect('enough', K, { food_supply_months: 1, food_stored_total: 50 }, 102)
    var F = ADVISOR_COMMENT_FOOD_CONSUMPTION
    t395_expect('151', F, { food_supply_percentage: 151 }, 217, ADVISOR_POPULATION)
    t395_expect('150', F, { food_supply_percentage: 150 }, 216)
    t395_expect('110', F, { food_supply_percentage: 110 }, 215)
    t395_expect('95', F, { food_supply_percentage: 95 }, 214)
    t395_expect('85', F, { food_supply_percentage: 85 }, 213)
    t395_expect('70', F, { food_supply_percentage: 70 }, 212)
    t395_expect('no pop', F, { population: 0 }, 212)
    t395_mark('advisor_comments_food_ok')
}

function t395_religion() {
    var R = ADVISOR_COMMENT_RELIGION
    t395_expect('appeased', R, {}, 146, ADVISOR_RELIGION)
    t395_expect('one happy', R, { god_mood0: 61 }, 147)
    t395_expect('60 not happy', R, { god_mood0: 60 }, 146)
    t395_expect('two happy', R, { god_mood0: 61, god_mood1: 61 }, 148)
    t395_expect('three happy', R, { god_mood0: 61, god_mood1: 61, god_mood2: 61 }, -1)
    t395_expect('one angry', R, { god_mood3: 39 }, 144)
    t395_expect('40 not angry', R, { god_mood3: 40 }, 146)
    t395_expect('one very angry', R, { god_mood3: 19 }, 145)
    t395_expect('two angry', R, { god_mood0: 39, god_mood3: 39 }, 142)
    t395_expect('three angry', R, { god_mood0: 39, god_mood1: 39, god_mood3: 39 }, 140)
    t395_expect('four angry', R, { god_mood0: 39, god_mood1: 39, god_mood2: 39, god_mood3: 39 }, 138)
    t395_expect('four very angry', R, { god_mood0: 10, god_mood1: 39, god_mood2: 39, god_mood3: 39 }, 139)
    t395_mark('advisor_comments_religion_ok')
}

function t395_rest() {
    t395_expect('health', ADVISOR_COMMENT_HEALTH, { health: 55 }, 119, ADVISOR_HEALTH)
    var M = ADVISOR_COMMENT_FINANCES
    t395_expect('uncollected', M, { taxes_collected: 99, taxes_uncollected: 100 }, 155, ADVISOR_FINANCIAL)
    t395_expect('rising', M, { taxes_collected: 100, taxes_uncollected: 100, treasury: 1001 }, 156)
    t395_expect('steady', M, {}, 157)
    t395_expect('falling', M, { treasury: 999 }, 158)
    var C = ADVISOR_COMMENT_CRIME
    t395_expect('no thefts', C, {}, 169, ADVISOR_FINANCIAL)
    t395_expect('1 theft', C, { crimes_this_month: 1 }, 168)
    t395_expect('2 thefts', C, { crimes_this_month: 2 }, 167)
    t395_expect('5 thefts', C, { crimes_this_month: 5 }, 166)
    t395_expect('10 thefts', C, { crimes_this_month: 10 }, 165)
    var W = ADVISOR_COMMENT_MILITARY
    t395_expect('kingdom soldiers', W, { kingdom_soldiers: 1 }, 181, ADVISOR_MILITARY)
    t395_expect('enemies', W, { enemies: 1 }, 180)
    t395_expect('invasion', W, { invasion_running: 1 }, 179)
    t395_expect('abroad', W, { troops_away: 1, troops_requested: 1 }, 183)
    t395_expect('requested', W, { troops_requested: 1 }, 182)
    t395_expect('watching', W, {}, 178)
    t395_expect('no forces', W, { soldiers: -1 }, 177)
    var K = ADVISOR_COMMENT_KINGDOM
    t395_expect('requests 0', K, {}, 191, ADVISOR_KINGDOM)
    t395_expect('requests 2', K, { requests_waiting: 2 }, 190)
    t395_expect('requests 3', K, { requests_waiting: 3 }, 189)
    t395_expect('requests 4', K, { requests_waiting: 4 }, 189)
    t395_expect('requests 5', K, { requests_waiting: 5 }, 188)
    t395_expect('nile 0', ADVISOR_COMMENT_NILOMETER, { flood_quality: 0 }, 198, ADVISOR_POPULATION)
    t395_expect('nile 50', ADVISOR_COMMENT_NILOMETER, { flood_quality: 50 }, 201)
    t395_mark('advisor_comments_rest_ok')
}

function run_test() {
    __log_info_native('[test:395] advisor comment texts')
    test_ensure_city_session('data/default.map')
    t395_people()
    t395_food()
    t395_religion()
    t395_rest()
    __test_advisor_state_clear()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] advisor_comments_people_ok')
        && __test_find_inlog('[test-marker] advisor_comments_food_ok')
        && __test_find_inlog('[test-marker] advisor_comments_religion_ok')
        && __test_find_inlog('[test-marker] advisor_comments_rest_ok')
}
