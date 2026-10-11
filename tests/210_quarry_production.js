// Quarry deposit beside rock, same halo as map_*_init (radius 2, value 65000).
// 8 workers -> uptick max(1, workers/2) = 4. update_day starts progress at 1,
// then 8 production ticks add 32 and deplete the footprint by 32.
// Markers:
//   [test-marker] quarry_production_ok

var __test210_ok = false

function __test210_footprint_sum(x, y, get_deposit) {
    var sum = 0
    var iy
    var ix
    for (iy = 0; iy < 2; iy++) {
        for (ix = 0; ix < 2; ix++) {
            sum += get_deposit({ x: x + ix, y: y + iy })
        }
    }
    return sum
}

function __test210_place(label, type, resource, x, y) {
    var bid = test_building_place(type, x, y)
    if (!bid) {
        bid = __test_building_create(type, x, y)
    }
    if (!bid) {
        __log_info_native('[test:210] ' + label + ' place/create failed')
        return 0
    }

    var b = city.get_building(bid)
    if (!b || b.output_resource_id != resource) {
        __log_info_native('[test:210] ' + label + ' output mismatch: ' + (b ? b.output_resource_id : 'no building'))
        return 0
    }

    __test_building_set_workers(bid, 8)
    __test_building_update_day(bid)
    if (__building_industry_progress(bid) != 1) {
        __log_info_native('[test:210] ' + label + ' progress after update_day=' + __building_industry_progress(bid))
        return 0
    }

    return bid
}

function run_test() {
    __log_info_native('[test:210] quarry production depletes the deposit')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var spots = [
        [cx, cy],
        [cx + 8, cy],
        [cx, cy + 8],
        [cx + 8, cy + 8]
    ]
    var i
    for (i = 0; i < spots.length; i++) {
        terrain.add({ x: spots[i][0] + 2, y: spots[i][1] }, TERRAIN_ROCK)
        terrain.add({ x: spots[i][0] + 2, y: spots[i][1] + 1 }, TERRAIN_ROCK)
    }
    __test_map_quarry_deposits_init()

    var sandstone = __test210_place('sandstone', BUILDING_SANDSTONE_QUARRY, RESOURCE_SANDSTONE, cx, cy)
    var stone = __test210_place('stone', BUILDING_STONE_QUARRY, RESOURCE_STONE, cx + 8, cy)
    var limestone = __test210_place('limestone', BUILDING_LIMESTONE_QUARRY, RESOURCE_LIMESTONE, cx, cy + 8)
    var granite = __test210_place('granite', BUILDING_GRANITE_QUARRY, RESOURCE_GRANITE, cx + 8, cy + 8)
    if (!sandstone || !stone || !limestone || !granite) {
        __test_signal_ready()
        return
    }

    var sand_before = __test210_footprint_sum(cx, cy, __map_get_sandstone)
    var stone_before = __test210_footprint_sum(cx + 8, cy, __map_get_stone)
    var lime_before = __test210_footprint_sum(cx, cy + 8, __map_get_limestone)
    var granite_before = __test210_footprint_sum(cx + 8, cy + 8, __map_get_granite)
    if (sand_before <= 0 || stone_before <= 0 || lime_before <= 0 || granite_before <= 0) {
        __log_info_native('[test:210] missing deposit sand=' + sand_before + ' stone=' + stone_before
            + ' lime=' + lime_before + ' granite=' + granite_before)
        __test_signal_ready()
        return
    }

    for (i = 0; i < 8; i++) {
        __test_city_industry_update_production()
    }

    var failed = false
    if (__building_industry_progress(sandstone) != 33 || __test210_footprint_sum(cx, cy, __map_get_sandstone) != sand_before - 32) {
        __log_info_native('[test:210] sandstone progress=' + __building_industry_progress(sandstone)
            + ' deposit=' + __test210_footprint_sum(cx, cy, __map_get_sandstone) + ' before=' + sand_before)
        failed = true
    }
    if (__building_industry_progress(stone) != 33 || __test210_footprint_sum(cx + 8, cy, __map_get_stone) != stone_before - 32) {
        __log_info_native('[test:210] stone progress=' + __building_industry_progress(stone)
            + ' deposit=' + __test210_footprint_sum(cx + 8, cy, __map_get_stone) + ' before=' + stone_before)
        failed = true
    }
    if (__building_industry_progress(limestone) != 33 || __test210_footprint_sum(cx, cy + 8, __map_get_limestone) != lime_before - 32) {
        __log_info_native('[test:210] limestone progress=' + __building_industry_progress(limestone)
            + ' deposit=' + __test210_footprint_sum(cx, cy + 8, __map_get_limestone) + ' before=' + lime_before)
        failed = true
    }
    if (__building_industry_progress(granite) != 33 || __test210_footprint_sum(cx + 8, cy + 8, __map_get_granite) != granite_before - 32) {
        __log_info_native('[test:210] granite progress=' + __building_industry_progress(granite)
            + ' deposit=' + __test210_footprint_sum(cx + 8, cy + 8, __map_get_granite) + ' before=' + granite_before)
        failed = true
    }
    if (failed) {
        __test_signal_ready()
        return
    }

    __log_marker('quarry_production_ok')
    __test210_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test210_ok && __test_find_inlog('[test-marker] quarry_production_ok')
}
