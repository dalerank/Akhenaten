// True large OG: size 2 like mudbrick large, 16×16 → 1104 blocks.

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_mudbrick_pyramid_og_complete({
        tag: '268',
        marker: 'true_og_large',
        type: BUILDING_LARGE_PYRAMID,
        total: 1104,
        nlayers: 4,
        sleep_ms: 50,
        candidates: [
            {x: cx - 10, y: cy - 10}, {x: cx, y: cy}, {x: 32, y: 32}, {x: 24, y: 24}
        ]
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('true_og_large', 1104)
}
