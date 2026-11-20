// True complex OG: 20×20 → 1920 blocks + causeway annex.

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var px = cx - 10
    var py = cy - 10
    test_mudbrick_pyramid_og_complete({
        tag: '269',
        marker: 'true_og_complex',
        type: BUILDING_PYRAMID_COMPLEX,
        total: 1920,
        nlayers: 5,
        sleep_ms: 50,
        candidates: [
            {x: px, y: py}, {x: cx, y: cy}
        ],
        prepare: function () {
            test_prepare_pyramid_complex_causeway(px, py, 20, 12, 4)
            test_prepare_pyramid_complex_causeway(cx, cy, 20, 12, 4)
        }
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('true_og_complex', 1920)
}
