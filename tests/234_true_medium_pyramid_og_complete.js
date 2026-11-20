// Medium true OG: 12×12 → 552 blocks.

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '267',
        marker: 'true_og_medium',
        type: BUILDING_MEDIUM_PYRAMID,
        total: 552,
        nlayers: 3,
        sleep_ms: 100,
        candidates: [
            {x: cx - 6, y: cy - 6}, {x: cx, y: cy}, {x: 36, y: 36}, {x: 28, y: 28}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('true_og_medium', 552)
}
