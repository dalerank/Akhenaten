// OG city/food_supply.c city_resource_food_supply_percentage: harvests (floodplain x48, meadow x64) / 10,
// ranches at 80%, plus hunting, fishing and imports, times 100 over the consumption percentage (25, 20 blessed).
// Markers:
//   [test-marker] food_supply_formula_ok
//   [test-marker] food_supply_farm_produce_ok
//   [test-marker] food_supply_live_ok

var t500_failed = false

function t500_expect(what, got, want) {
    if (got !== want) {
        __log_info_native('[test:500] ' + what + ': got ' + got + ', want ' + want)
        t500_failed = true
    }
}

function t500_formula() {
    t500_expect('empty', __test_food_supply_percentage_of(0, 0, 0, 0, 0, 0, 25), 0)
    t500_expect('floodplain', __test_food_supply_percentage_of(10, 0, 0, 0, 0, 0, 25), 192)
    t500_expect('meadow', __test_food_supply_percentage_of(0, 10, 0, 0, 0, 0, 25), 256)
    t500_expect('ranch 80%', __test_food_supply_percentage_of(0, 0, 40, 0, 0, 0, 25), 128)
    t500_expect('imports blessed', __test_food_supply_percentage_of(0, 0, 0, 0, 0, 100, 20), 500)
    t500_expect('hunting+fishing', __test_food_supply_percentage_of(0, 0, 0, 30, 20, 0, 25), 200)
    // 3*48/10 = 14.4, +1 hunting = 15.4 -> 15 before the percentage.
    t500_expect('truncation', __test_food_supply_percentage_of(3, 0, 0, 1, 0, 0, 25), 60)
    if (!t500_failed) {
        __log_marker('food_supply_formula_ok')
    }
}

function t500_farm_produce() {
    var ok = !t500_failed
    t500_expect('farm 99 fert', __test_food_supply_farm_produce(99, 10, false), 16)
    t500_expect('farm blessed', __test_food_supply_farm_produce(99, 10, true), 32)
    t500_expect('farm min 1', __test_food_supply_farm_produce(0, 10, false), 1)
    t500_expect('farm 50 fert', __test_food_supply_farm_produce(50, 10, false), 8)
    if (ok && !t500_failed) {
        __log_marker('food_supply_farm_produce_ok')
    }
}

function t500_live() {
    test_ensure_city_session('data/default.map')
    var before = __test_food_supply_sources()
    if (before.ranch_food !== 0 || before.meadow_produce !== 0 || before.floodplain_produce !== 0) {
        __log_info_native('[test:500] fresh map has food sources ' + before.ranch_food + '/' + before.meadow_produce)
        t500_failed = true
        return
    }
    t500_expect('consumption', before.consumption_percentage, 25)
    t500_expect('empty city', __city_food_supply_percentage(), (before.import_food + before.hunting_food + before.fishing_food) * 4)

    var ranch_id = __test_building_create(BUILDING_CATTLE_RANCH, -1, -1)
    if (!ranch_id) {
        __log_info_native('[test:500] cattle ranch not created')
        t500_failed = true
        return
    }
    var ranch = city.get_building(ranch_id)
    var idle = __test_food_supply_sources()
    t500_expect('idle ranch', idle.ranch_food, 0)

    ranch.num_workers = ranch.max_workers
    ranch.progress = 10
    var s = __test_food_supply_sources()
    t500_expect('working ranch', s.ranch_food, ((ranch.max_workers * 16) / 4) | 0)
    var want = __test_food_supply_percentage_of(s.floodplain_produce, s.meadow_produce, s.ranch_food,
        s.hunting_food, s.fishing_food, s.import_food, s.consumption_percentage)
    t500_expect('live percentage', __city_food_supply_percentage(), want)
    if (s.ranch_food <= 0) {
        __log_info_native('[test:500] ranch gives no food, max_workers=' + ranch.max_workers)
        t500_failed = true
    }
    if (!t500_failed) {
        __log_marker('food_supply_live_ok')
    }
}

function run_test() {
    __log_info_native('[test:500] food supply percentage')
    t500_formula()
    t500_farm_produce()
    t500_live()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] food_supply_formula_ok')
        && __test_find_inlog('[test-marker] food_supply_farm_produce_ok')
        && __test_find_inlog('[test-marker] food_supply_live_ok')
}
