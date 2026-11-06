// Medium bent OG: 12×12 → 444 blocks (main 276 + casing 168; half-layers on courses 1–2).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '276',
        marker: 'bent_og_medium',
        type: BUILDING_MEDIUM_BENT_PYRAMID,
        total: 444,
        nlayers: 12,
        sleep_ms: 100,
        candidates: [
            {x: cx - 6, y: cy - 6}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('bent_og_medium', 444)
}
