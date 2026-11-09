// Every house type takes LABOR_CATEGORY_HOUSE from houses.js (a misspelled key once left them at 0).

var __test294_ok = false

function run_test() {
    __log_info_native('[test:294] house labor category')

    var houses = [
        BUILDING_HOUSE_CRUDE_HUT, BUILDING_HOUSE_STURDY_HUT, BUILDING_HOUSE_MEAGER_SHANTY,
        BUILDING_HOUSE_COMMON_SHANTY, BUILDING_HOUSE_ROUGH_COTTAGE, BUILDING_HOUSE_ORDINARY_COTTAGE,
        BUILDING_HOUSE_MODEST_HOMESTEAD, BUILDING_HOUSE_SPACIOUS_HOMESTEAD, BUILDING_HOUSE_MODEST_APARTMENT,
        BUILDING_HOUSE_SPACIOUS_APARTMENT, BUILDING_HOUSE_COMMON_RESIDENCE, BUILDING_HOUSE_SPACIOUS_RESIDENCE,
        BUILDING_HOUSE_ELEGANT_RESIDENCE, BUILDING_HOUSE_FANCY_RESIDENCE, BUILDING_HOUSE_COMMON_MANOR,
        BUILDING_HOUSE_SPACIOUS_MANOR, BUILDING_HOUSE_ELEGANT_MANOR, BUILDING_HOUSE_STATELY_MANOR,
        BUILDING_HOUSE_MODEST_ESTATE, BUILDING_HOUSE_PALATIAL_ESTATE
    ]

    for (var i = 0; i < houses.length; i++) {
        var cat = __building_static_labor_category(houses[i])
        if (cat != LABOR_CATEGORY_HOUSE) {
            __log_marker('house_labor_category_fail:' + houses[i] + ':' + cat)
            __test_signal_ready()
            return
        }
    }

    __log_marker('house_labor_category_ok')
    __test294_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test294_ok && __test_find_inlog('[test-marker] house_labor_category_ok')
}
