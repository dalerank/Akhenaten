// OG docker: 4-load haul, storageyard_import_loads, ferry state ids.
// Markers:
//   [test-marker] docker_og_haul_ok
//   [test-marker] docker_og_import_loads_ok
//   [test-marker] docker_og_ferry_ids_ok

var __test234_haul_ok = false
var __test234_loads_ok = false
var __test234_ferry_ok = false

function test234_fail(msg) {
    __log_info_native('[test:234] ' + msg)
}

function test234_check_haul() {
    var prev = game_features.get('gameplay_change_dock_double_haul')
    game_features.set('gameplay_change_dock_double_haul', false)
    var og = __test_docker_haul_amount()
    game_features.set('gameplay_change_dock_double_haul', true)
    var doubled = __test_docker_haul_amount()
    game_features.set('gameplay_change_dock_double_haul', prev)
    if (og != 400 || doubled != 800) {
        test234_fail('haul want 400/800 got ' + og + '/' + doubled)
        return false
    }
    return true
}

function test234_check_import_loads() {
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard) {
        test234_fail('storage yard create failed')
        return false
    }

    var r = RESOURCE_POTTERY
    if (!__test_storage_yard_set_state(yard, r, STORAGE_STATE_ACCEPT)) {
        test234_fail('set accept failed')
        return false
    }
    var stored = __test_yards_stored(r)
    __test_city_set_trade(r, TRADE_STATUS_IMPORT, 10000)

    var loads = __test_docker_import_loads(yard, r, 400)
    if (loads != 4) {
        test234_fail('empty yard, 400 offered: want 4 loads got ' + loads)
        return false
    }

    __test_city_set_trade(r, TRADE_STATUS_IMPORT, stored + 200)
    loads = __test_docker_import_loads(yard, r, 400)
    if (loads != 2) {
        test234_fail('stock limit +200: want 2 loads got ' + loads)
        return false
    }

    // 350 in one room: only whole loads count, so that room adds nothing (7 free rooms = 28 loads).
    __test_city_set_trade(r, TRADE_STATUS_IMPORT, 10000)
    __test_storage_yard_add_resource(yard, r, 350)
    loads = __test_docker_import_loads(yard, r, 3200)
    if (loads != 28) {
        test234_fail('partial room: want 28 loads got ' + loads)
        return false
    }

    if (!__test_storage_yard_set_state(yard, r, STORAGE_STATE_REFUSE)) {
        test234_fail('set refuse failed')
        return false
    }
    loads = __test_docker_import_loads(yard, r, 400)
    if (loads != 0) {
        test234_fail('refusing yard: want 0 loads got ' + loads)
        return false
    }
    return true
}

// The ferry sets wait/ride/reroute ids on its passengers. Docker 6/7 are import states, so the docker
// gets its own 11/10 and OG's reroute 8 (= docker idle in OG) maps to our idle 0.
function test234_check_ferry_ids() {
    var docker = test_figure_create(FIGURE_DOCKER)
    var cart = test_figure_create(FIGURE_CART_PUSHER)
    if (!docker || !cart) {
        test234_fail('figure create failed docker=' + docker + ' cart=' + cart)
        return false
    }
    var got_docker = [0, 1, 2].map(function (k) { return __test_figure_ferry_action(docker, k) }).join(',')
    var got_cart = [0, 1, 2].map(function (k) { return __test_figure_ferry_action(cart, k) }).join(',')
    city.figures.remove_figures(FIGURE_DOCKER)
    city.figures.remove_figures(FIGURE_CART_PUSHER)
    if (got_docker != '11,10,0') {
        test234_fail('docker ferry ids want 11,10,0 got ' + got_docker)
        return false
    }
    if (got_cart != '7,6,8') {
        test234_fail('cartpusher ferry ids want 7,6,8 got ' + got_cart)
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:234] docker og')
    test_reload_city_session('data/default.map')

    if (test234_check_haul()) {
        __log_marker('docker_og_haul_ok')
        __test234_haul_ok = true
    }
    if (test234_check_import_loads()) {
        __log_marker('docker_og_import_loads_ok')
        __test234_loads_ok = true
    }

    if (test234_check_ferry_ids()) {
        __log_marker('docker_og_ferry_ids_ok')
        __test234_ferry_ok = true
    }

    __test_signal_ready()
}

function check_valid() {
    return __test234_haul_ok && __test234_loads_ok && __test234_ferry_ok
}
