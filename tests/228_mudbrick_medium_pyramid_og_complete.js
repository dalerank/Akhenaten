// Medium mudbrick OG: 12×12 → 552 blocks (3 rings × 6 courses).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '263',
        marker: 'mudbrick_og_medium',
        type: BUILDING_MEDIUM_MUDBRICK_PYRAMID,
        total: 552,
        nlayers: 3,
        sleep_ms: 100,
        candidates: [
            {x: cx - 6, y: cy - 6}, {x: cx, y: cy}, {x: 36, y: 36}, {x: 28, y: 28}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('mudbrick_og_medium', 552)
}
