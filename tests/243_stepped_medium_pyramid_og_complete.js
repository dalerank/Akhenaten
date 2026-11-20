// Medium stepped OG: 12×12 → 336 blocks (3 rings × 6 courses).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '271',
        marker: 'stepped_og_medium',
        type: BUILDING_MEDIUM_STEPPED_PYRAMID,
        total: 336,
        nlayers: 3,
        sleep_ms: 50,
        candidates: [
            {x: cx - 6, y: cy - 6}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('stepped_og_medium', 336)
}
