// Large stepped OG: 16×16 → 720 blocks (4 rings × 6 courses).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '272',
        marker: 'stepped_og_large',
        type: BUILDING_LARGE_STEPPED_PYRAMID,
        total: 720,
        nlayers: 4,
        sleep_ms: 30,
        candidates: [
            {x: cx - 8, y: cy - 8}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('stepped_og_large', 720)
}
