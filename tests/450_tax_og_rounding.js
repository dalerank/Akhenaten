// OG city_finance_collect_monthly_taxes: the city takes calc(calc(units, tax_rate), share) where share is
// the system tax_percentage table (OG 50 on every difficulty; only the per-difficulty house model differs).
// A mission tax_percentage overrides the table; the obsolete house_tax_multipliers is ignored. The house
// keeps its tax income as share * tax_rate * units in 1/10000 deben, which survives a save round trip.
// Markers:
//   [test-marker] tax_og_difficulty_ok
//   [test-marker] tax_og_mission_override_ok
//   [test-marker] tax_og_old_key_ignored_ok
//   [test-marker] tax_og_house_income_ok
//   [test-marker] tax_og_house_income_saveload_ok

function tax_og_apply(units, rate, share) {
    var a = ((units * rate) / 100) | 0
    return ((a * share) / 100) | 0
}

function tax_og_gained() {
    var treasury0 = city.finance.treasury | 0
    __city_finance_collect_monthly_taxes()
    return (city.finance.treasury | 0) - treasury0
}

function run_test() {
    __log_info_native('[test:450] OG tax rounding, no difficulty multiplier')
    test_ensure_city_session('data/default.map')

    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    var pop = hid ? __test_house_set_population(hid, 370) : 0
    if (!hid || pop < 1) {
        __log_info_native('[test:450] house setup failed hid=' + hid)
        __test_signal_ready()
        return
    }

    var house = city.get_house(hid)
    house.tax_coverage = 50
    house.tax_bonus = 0
    city.finance.tax_percentage = 7
    var difficulty0 = game.difficulty | 0
    __test_scenario_meta_tax('tax_percentage', -1)
    __test_scenario_meta_tax('house_tax_multipliers', -1)

    function finish() {
        __test_scenario_meta_tax('tax_percentage', -1)
        __test_scenario_meta_tax('house_tax_multipliers', -1)
        while ((game.difficulty | 0) > difficulty0) {
            __game_decrease_difficulty()
        }
        while ((game.difficulty | 0) < difficulty0) {
            __game_increase_difficulty()
        }
        __test_signal_ready()
    }

    if (finance_tax_rules.tax_percentage.length !== 5 || finance_tax_rules.house_tax_income_unit !== 10000) {
        __log_info_native('[test:450] system tax config is not the OG default')
        finish()
        return
    }

    for (var i = 0; i < 5; i++) {
        __game_decrease_difficulty()
    }

    var bad = 0
    for (var d = 0; d < 5; d++) {
        var units = __test_house_tax_units(hid)
        var model_units = pop * __test_house_model_value(hid, 'tax_multiplier')
        var gained = tax_og_gained()
        var want = tax_og_apply(units, 7, 50)
        __log_info_native('[test:450] difficulty=' + game.difficulty + ' units=' + units + '/' + model_units + ' gained=' + gained + ' want=' + want)
        if (finance_tax_rules.tax_percentage[d] !== 50 || units <= 0 || units !== model_units || gained !== want) {
            bad++
        }
        __game_increase_difficulty()
    }
    if (bad) {
        finish()
        return
    }
    __log_marker('tax_og_difficulty_ok')

    var units = __test_house_tax_units(hid)
    __test_scenario_meta_tax('tax_percentage', 80)
    var overridden = tax_og_gained()
    __test_scenario_meta_tax('tax_percentage', -1)
    if (overridden !== tax_og_apply(units, 7, 80)) {
        __log_info_native('[test:450] mission tax_percentage 80 want ' + tax_og_apply(units, 7, 80) + ' got ' + overridden)
        finish()
        return
    }
    __log_marker('tax_og_mission_override_ok')

    __test_scenario_meta_tax('house_tax_multipliers', 300)
    var old_key_units = __test_house_tax_units(hid)
    var old_key_gained = tax_og_gained()
    __test_scenario_meta_tax('house_tax_multipliers', -1)
    if (old_key_units !== units || old_key_gained !== tax_og_apply(units, 7, 50)) {
        __log_info_native('[test:450] house_tax_multipliers applied: units ' + old_key_units + ' gained ' + old_key_gained)
        finish()
        return
    }
    __log_marker('tax_og_old_key_ignored_ok')

    house.tax_income = 0
    __city_finance_collect_monthly_taxes()
    var want_income = 50 * 7 * units
    if ((house.tax_income | 0) !== want_income) {
        __log_info_native('[test:450] house tax_income want ' + want_income + ' got ' + house.tax_income)
        finish()
        return
    }
    __log_marker('tax_og_house_income_ok')

    // Not a multiple of 50 * rate, so the legacy int16 units could not restore it.
    var odd_income = want_income + 123
    house.tax_income = odd_income
    // The diff is not checked: a test-made house gains hsize on load.
    __test_save_roundtrip('test_450_tax_income.svx')
    var reloaded = city.get_house(hid)
    if (!reloaded || (reloaded.tax_income | 0) !== odd_income) {
        __log_info_native('[test:450] save roundtrip tax_income=' + (reloaded ? reloaded.tax_income : 'none'))
        finish()
        return
    }
    __log_marker('tax_og_house_income_saveload_ok')
    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] tax_og_difficulty_ok')
        && __test_find_inlog('[test-marker] tax_og_mission_override_ok')
        && __test_find_inlog('[test-marker] tax_og_old_key_ignored_ok')
        && __test_find_inlog('[test-marker] tax_og_house_income_ok')
        && __test_find_inlog('[test-marker] tax_og_house_income_saveload_ok')
}
