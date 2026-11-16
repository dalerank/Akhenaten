// OG window/advisor/chief.c: the chief advisor's row texts (group 61) and fonts from city values.
// Sentiment sentiment/10+21, labor thresholds 18/11/6/1 and 21/11/6/>0, food supply%*100/pop with
// 150/110/95/85/70, religion by god moods (texts 125-137), finance by collected vs uncollected taxes,
// thefts, military, requests and the Nile. City values come from __test_advisor_state_set overrides.
// Markers:
//   [test-marker] chief_rows_sentiment_ok
//   [test-marker] chief_rows_labor_ok
//   [test-marker] chief_rows_food_ok
//   [test-marker] chief_rows_religion_ok
//   [test-marker] chief_rows_finance_crime_ok
//   [test-marker] chief_rows_military_requests_nile_ok

var t501_failed = false

var t501_base = {
    sentiment: 60, low_mood_cause: 0, migration_direction: 0, kingdom_soldiers: 0, enemies: 0, soldiers: 0,
    newcomers: 0, refused_immigrants_today: 0, room_in_houses: 10, migration_percentage: 100, no_immigration_cause: 0,
    unemployment_percentage: 0, workers_needed: 0, kingdom_supplies_grain: 0, food_supply_months: 3,
    food_stored_total: 300, food_needed_per_month: 100, population: 100, food_supply_percentage: 100, health: 50,
    god_mood0: 50, god_mood1: 50, god_mood2: 50, god_mood3: 50, god_mood4: 50, taxes_collected: 0,
    taxes_uncollected: 0, treasury: 1000, balance_last_year: 1000, crimes_this_month: 0, gold_stolen_this_month: 0,
    invasion_running: 0, troops_requested: 0, troops_away: 0, requests_waiting: 0, flood_quality: 50, flood_month: 2
}

function t501_row(topic, overrides) {
    __test_advisor_state_clear()
    for (var k in t501_base) {
        __test_advisor_state_set(k, (overrides[k] !== undefined) ? overrides[k] : t501_base[k])
    }
    return __chief_advisor_row(topic)
}

function t501_expect(name, topic, overrides, want) {
    var row = t501_row(topic, overrides)
    for (var k in want) {
        if (row[k] !== want[k]) {
            __log_info_native('[test:501] ' + name + ': ' + k + '=' + row[k] + ', want ' + want[k])
            t501_failed = true
        }
    }
}

function t501_mark(marker) {
    if (!t501_failed) {
        __log_marker(marker)
    }
}

function t501_sentiment() {
    var S = ADVISOR_COMMENT_SENTIMENT
    t501_expect('loathed', S, { sentiment: 0 }, { text: 20, tone: ADVISOR_TONE_RED, cause_text: -1 })
    t501_expect('loathed cause', S, { sentiment: 0, low_mood_cause: 1 }, { text: 20, cause_text: 33 })
    t501_expect('s29', S, { sentiment: 29, low_mood_cause: 2 }, { text: 23, tone: ADVISOR_TONE_RED, cause_text: 33 })
    t501_expect('s45', S, { sentiment: 45 }, { text: 25, tone: ADVISOR_TONE_WHITE, cause_text: -1 })
    t501_expect('s50', S, { sentiment: 50, low_mood_cause: 3 }, { text: 26, tone: ADVISOR_TONE_GREEN, cause_text: -1 })
    t501_expect('s99', S, { sentiment: 99 }, { text: 30 })
    t501_expect('s100', S, { sentiment: 100 }, { text: 31, tone: ADVISOR_TONE_GREEN })
    t501_expect('war', ADVISOR_COMMENT_MIGRATION, { enemies: 4 }, { text: 43, tone: ADVISOR_TONE_RED })
    t501_expect('newcomers', ADVISOR_COMMENT_MIGRATION, { newcomers: 5, room_in_houses: 0 }, { text: 44, tone: ADVISOR_TONE_GREEN })
    t501_expect('no room', ADVISOR_COMMENT_MIGRATION, { room_in_houses: 0 }, { text: 45, tone: ADVISOR_TONE_RED })
    t501_expect('cause', ADVISOR_COMMENT_MIGRATION, { migration_percentage: 79, no_immigration_cause: 2 }, { text: 48 })
    t501_expect('immigrating', ADVISOR_COMMENT_MIGRATION, { migration_percentage: 80 }, { text: 44 })
    t501_mark('chief_rows_sentiment_ok')
}

function t501_labor() {
    var L = ADVISOR_COMMENT_EMPLOYMENT
    t501_expect('u18', L, { unemployment_percentage: 18 }, { text: 76, tone: ADVISOR_TONE_RED, number: 18, number_kind: CHIEF_NUMBER_PERCENT })
    t501_expect('u17', L, { unemployment_percentage: 17 }, { text: 77, tone: ADVISOR_TONE_WHITE })
    t501_expect('u11', L, { unemployment_percentage: 11 }, { text: 77 })
    t501_expect('u10', L, { unemployment_percentage: 10 }, { text: 78, tone: ADVISOR_TONE_GREEN })
    t501_expect('u6', L, { unemployment_percentage: 6 }, { text: 78 })
    t501_expect('u5 n6', L, { unemployment_percentage: 5, workers_needed: 6 }, { text: 79, number: 5, number_kind: CHIEF_NUMBER_PERCENT })
    t501_expect('u5 n5', L, { unemployment_percentage: 5, workers_needed: 5 }, { text: 84, number_kind: CHIEF_NUMBER_NONE })
    t501_expect('n21', L, { workers_needed: 21 }, { text: 80, tone: ADVISOR_TONE_RED, number: 21, number_kind: CHIEF_NUMBER_PLAIN, suffix_group: 8, suffix_text: 13 })
    t501_expect('n20', L, { workers_needed: 20 }, { text: 81, tone: ADVISOR_TONE_WHITE })
    t501_expect('n11', L, { workers_needed: 11 }, { text: 81 })
    t501_expect('n10', L, { workers_needed: 10 }, { text: 82, tone: ADVISOR_TONE_GREEN })
    t501_expect('n6', L, { workers_needed: 6 }, { text: 82 })
    t501_expect('n0', L, { workers_needed: 0 }, { text: 84 })
    t501_expect('health 0', ADVISOR_COMMENT_HEALTH, { health: 0 }, { text: 103, tone: ADVISOR_TONE_RED })
    t501_expect('health 19', ADVISOR_COMMENT_HEALTH, { health: 19 }, { text: 104, tone: ADVISOR_TONE_RED })
    t501_expect('health 20', ADVISOR_COMMENT_HEALTH, { health: 20 }, { text: 105, tone: ADVISOR_TONE_WHITE })
    t501_expect('health 30', ADVISOR_COMMENT_HEALTH, { health: 30 }, { text: 106, tone: ADVISOR_TONE_GREEN })
    t501_expect('health 100', ADVISOR_COMMENT_HEALTH, { health: 100 }, { text: 113 })
    t501_mark('chief_rows_labor_ok')
}

function t501_food() {
    var F = ADVISOR_COMMENT_FOOD_CONSUMPTION
    t501_expect('151', F, { food_supply_percentage: 151 }, { text: 13, tone: ADVISOR_TONE_GREEN })
    t501_expect('150', F, { food_supply_percentage: 150 }, { text: 14 })
    t501_expect('111', F, { food_supply_percentage: 111 }, { text: 14 })
    t501_expect('110', F, { food_supply_percentage: 110 }, { text: 15 })
    t501_expect('96', F, { food_supply_percentage: 96 }, { text: 15 })
    t501_expect('95', F, { food_supply_percentage: 95 }, { text: 16, tone: ADVISOR_TONE_GREEN })
    t501_expect('86', F, { food_supply_percentage: 86 }, { text: 16 })
    t501_expect('85', F, { food_supply_percentage: 85 }, { text: 17, tone: ADVISOR_TONE_WHITE })
    t501_expect('71', F, { food_supply_percentage: 71 }, { text: 17 })
    t501_expect('70', F, { food_supply_percentage: 70 }, { text: 18, tone: ADVISOR_TONE_RED })
    t501_expect('per pop', F, { food_supply_percentage: 1600, population: 1000 }, { text: 13 })
    t501_expect('per pop short', F, { food_supply_percentage: 700, population: 1000 }, { text: 18 })
    t501_expect('no pop', F, { food_supply_percentage: 500, population: 0 }, { text: 18, tone: ADVISOR_TONE_RED })
    var K = ADVISOR_COMMENT_FOOD_STOCKS
    t501_expect('grain', K, { kingdom_supplies_grain: 1, food_supply_months: 0 }, { text: 94 })
    t501_expect('empty', K, { food_supply_months: 0 }, { text: 95, tone: ADVISOR_TONE_RED })
    t501_expect('low', K, { food_supply_months: 2, food_stored_total: 40 }, { text: 96, tone: ADVISOR_TONE_WHITE })
    t501_expect('months', K, { food_supply_months: 2, food_stored_total: 50 }, { text: 98, number: 2, suffix_group: 8, suffix_text: 5 })
    t501_mark('chief_rows_food_ok')
}

function t501_religion() {
    var R = ADVISOR_COMMENT_RELIGION
    t501_expect('appeased', R, {}, { text: 133, tone: ADVISOR_TONE_GREEN })
    t501_expect('one happy', R, { god_mood0: 71 }, { text: 134 })
    t501_expect('70 not happy', R, { god_mood0: 70 }, { text: 133 })
    t501_expect('two happy', R, { god_mood0: 71, god_mood1: 80 }, { text: 135 })
    t501_expect('three happy', R, { god_mood0: 71, god_mood1: 80, god_mood2: 90 }, { text: 136 })
    t501_expect('four happy', R, { god_mood0: 71, god_mood1: 80, god_mood2: 90, god_mood3: 99 }, { text: 137 })
    t501_expect('one angry', R, { god_mood2: 29 }, { text: 131, tone: ADVISOR_TONE_GREEN })
    t501_expect('30 not angry', R, { god_mood2: 30 }, { text: 133 })
    t501_expect('one very angry', R, { god_mood2: 19 }, { text: 132, tone: ADVISOR_TONE_WHITE })
    t501_expect('two angry', R, { god_mood0: 25, god_mood1: 25 }, { text: 129 })
    t501_expect('three angry', R, { god_mood0: 25, god_mood1: 25, god_mood4: 25 }, { text: 127 })
    t501_expect('three very angry', R, { god_mood0: 25, god_mood1: 5, god_mood4: 25 }, { text: 128 })
    t501_expect('four angry', R, { god_mood0: 25, god_mood1: 25, god_mood3: 25, god_mood4: 25 }, { text: 125 })
    t501_expect('five very angry', R, { god_mood0: 0, god_mood1: 25, god_mood2: 25, god_mood3: 25, god_mood4: 25 }, { text: 126 })
    t501_mark('chief_rows_religion_ok')
}

function t501_finance_crime() {
    var M = ADVISOR_COMMENT_FINANCES
    t501_expect('uncollected', M, { taxes_collected: 50, taxes_uncollected: 100 }, { text: 151, tone: ADVISOR_TONE_WHITE, number_kind: CHIEF_NUMBER_NONE })
    t501_expect('collected', M, { taxes_collected: 100, taxes_uncollected: 100, treasury: 1500 }, { text: 152, tone: ADVISOR_TONE_GREEN, number: 500, number_kind: CHIEF_NUMBER_MONEY })
    t501_expect('fallen', M, { treasury: 700 }, { text: 154, tone: ADVISOR_TONE_WHITE, number: 300 })
    t501_expect('same', M, {}, { text: 153, tone: ADVISOR_TONE_GREEN })
    var C = ADVISOR_COMMENT_CRIME
    t501_expect('no thefts', C, {}, { text: 163, number_kind: CHIEF_NUMBER_NONE })
    t501_expect('1 theft', C, { crimes_this_month: 1, gold_stolen_this_month: 40 }, { text: 162, number: 40, suffix_group: 61, suffix_text: 164 })
    t501_expect('2 thefts', C, { crimes_this_month: 2 }, { text: 161, tone: ADVISOR_TONE_GREEN })
    t501_expect('4 thefts', C, { crimes_this_month: 4 }, { text: 161 })
    t501_expect('5 thefts', C, { crimes_this_month: 5 }, { text: 160, tone: ADVISOR_TONE_WHITE })
    t501_expect('9 thefts', C, { crimes_this_month: 9 }, { text: 160 })
    t501_expect('10 thefts', C, { crimes_this_month: 10 }, { text: 159, tone: ADVISOR_TONE_RED })
    t501_mark('chief_rows_finance_crime_ok')
}

function t501_military_requests_nile() {
    var W = ADVISOR_COMMENT_MILITARY
    t501_expect('kingdom soldiers', W, { kingdom_soldiers: 2, enemies: 3 }, { text: 174, tone: ADVISOR_TONE_RED })
    t501_expect('enemies', W, { enemies: 3, invasion_running: 1 }, { text: 173 })
    t501_expect('invasion', W, { invasion_running: 1, troops_away: 1 }, { text: 172 })
    t501_expect('troops away', W, { troops_away: 1, troops_requested: 1 }, { text: 176, tone: ADVISOR_TONE_GREEN })
    t501_expect('troops requested', W, { troops_requested: 1 }, { text: 175 })
    t501_expect('quiet', W, {}, { text: 171 })
    t501_expect('no companies', W, { soldiers: -1 }, { text: 170 })
    var K = ADVISOR_COMMENT_KINGDOM
    t501_expect('requests 0', K, {}, { text: 187 })
    t501_expect('requests 1', K, { requests_waiting: 1 }, { text: 186 })
    t501_expect('requests 2', K, { requests_waiting: 2 }, { text: 186 })
    t501_expect('requests 3', K, { requests_waiting: 3 }, { text: 185 })
    t501_expect('requests 4', K, { requests_waiting: 4 }, { text: 185 })
    t501_expect('requests 5', K, { requests_waiting: 5 }, { text: 184 })
    t501_expect('requests 9', K, { requests_waiting: 9 }, { text: 184 })
    var N = ADVISOR_COMMENT_NILOMETER
    t501_expect('flood fail', N, { flood_quality: 0 }, { text: 192, tone: ADVISOR_TONE_RED, second_text: -1 })
    t501_expect('flood poor', N, { flood_quality: 1, flood_month: 3 }, { text: 193, tone: ADVISOR_TONE_WHITE, second_text: 207 })
    t501_expect('flood 20', N, { flood_quality: 20 }, { text: 193 })
    t501_expect('flood 21', N, { flood_quality: 21, flood_month: 0 }, { text: 194, tone: ADVISOR_TONE_GREEN, second_text: 204 })
    t501_expect('flood perfect', N, { flood_quality: 100 }, { text: 197 })
    t501_mark('chief_rows_military_requests_nile_ok')
}

function run_test() {
    __log_info_native('[test:501] chief advisor rows')
    test_ensure_city_session('data/default.map')
    t501_sentiment()
    t501_labor()
    t501_food()
    t501_religion()
    t501_finance_crime()
    t501_military_requests_nile()
    __test_advisor_state_clear()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] chief_rows_sentiment_ok')
        && __test_find_inlog('[test-marker] chief_rows_labor_ok')
        && __test_find_inlog('[test-marker] chief_rows_food_ok')
        && __test_find_inlog('[test-marker] chief_rows_religion_ok')
        && __test_find_inlog('[test-marker] chief_rows_finance_crime_ok')
        && __test_find_inlog('[test-marker] chief_rows_military_requests_nile_ok')
}
