// Small true OG: 8×8 → 216 blocks (same totals as mudbrick @ 0x005F5C40).

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '266',
        marker: 'true_og_complete',
        type: BUILDING_SMALL_PYRAMID,
        total: 216,
        nlayers: 2,
        sleep_ms: 100,
        candidates: [
            {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('true_og_complete', 216)
}
