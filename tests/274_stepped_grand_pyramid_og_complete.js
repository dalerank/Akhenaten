// Grand stepped OG: 20×20 → 1320 blocks (5 rings × 6 courses) + east-only causeway.

function run_test() {
    test_ensure_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var px = cx - 10
    var py = cy - 10
    test_mudbrick_pyramid_og_complete({
        tag: '274',
        marker: 'stepped_og_grand',
        type: BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX,
        total: 1320,
        nlayers: 5,
        sleep_ms: 30,
        candidates: [
            {x: px, y: py}, {x: cx, y: cy}
        ],
        prepare: function () {
            // Grand accepts east water only (dir=1). gap=12 for visible causeway.
            test_prepare_pyramid_complex_causeway(px, py, 20, 12, 4, 1)
            test_prepare_pyramid_complex_causeway(cx, cy, 20, 12, 4, 1)
        }
    })
}

function check_valid() {
    return test_mudbrick_pyramid_og_complete_valid('stepped_og_grand', 1320)
}
