// OG house tax_bonus: model tax × house_tax_bonus_percentage (110) when flag set.
// Markers:
//   [test-marker] tax_bonus_base_ok
//   [test-marker] tax_bonus_110_ok

function run_test() {
    __log_info_native('[test:249] house tax_bonus OG 110%')
    test_ensure_city_session('data/default.map')

    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!hid || __test_house_set_population(hid, 100) < 1) {
        __log_info_native('[test:249] house setup failed hid=' + hid)
        __test_signal_ready()
        return
    }

    var house = city.get_house(hid)
    if (!house) {
        __log_info_native('[test:249] city.get_house failed')
        __test_signal_ready()
        return
    }

    house.tax_coverage = 50
    house.tax_bonus = 0
    city.finance.tax_percentage = 10

    var treasury0 = city.finance.treasury | 0
    __city_finance_collect_monthly_taxes()
    var gained0 = (city.finance.treasury | 0) - treasury0
    if (gained0 <= 0) {
        __log_info_native('[test:249] expected tax income without bonus, got ' + gained0)
        __test_signal_ready()
        return
    }
    __log_marker('tax_bonus_base_ok')

    house.tax_bonus = 1
    var treasury1 = city.finance.treasury | 0
    __city_finance_collect_monthly_taxes()
    var gained1 = (city.finance.treasury | 0) - treasury1

    var expect = Math.floor(gained0 * (city.taxes.house_tax_bonus_percentage | 0) / 100)
    if (gained1 !== expect) {
        __log_info_native('[test:249] bonus want ' + expect + ' got ' + gained1 + ' (base ' + gained0 + ')')
        __test_signal_ready()
        return
    }
    __log_marker('tax_bonus_110_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] tax_bonus_base_ok')
        && __test_find_inlog('[test-marker] tax_bonus_110_ok')
}
