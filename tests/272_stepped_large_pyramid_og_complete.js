// Large stepped OG: remake 20×20 → 1320 blocks (5 rings × 6 courses).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '272',
        marker: 'stepped_og_large',
        type: BUILDING_LARGE_STEPPED_PYRAMID,
        total: 1320,
        nlayers: 5,
        sleep_ms: 30,
        candidates: [
            {x: cx - 10, y: cy - 10}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('stepped_og_large', 1320)
}
