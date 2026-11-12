// Editor procedural map generation (CaesarIA midpoint-displacement port).
// The generator is seeded explicitly: the same seed gives the same map, and every seed gives a playable
// map (water, a road, entry and exit points).
// Markers:
//   [test-marker] editor_map_generate_ok

var TEST173_SEED = 173

function test173_fail(msg) {
    __log_info_native('[test:173] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:173] editor map generate')

    if (!game.init_editor()) {
        return test173_fail('init_editor failed')
    }

    var first = __test_editor_map_generate(TEST173_SEED)
    if (!first) {
        return test173_fail('editor_map_generate failed for seed ' + TEST173_SEED)
    }
    var again = __test_editor_map_generate(TEST173_SEED)
    if (again !== first) {
        return test173_fail('seed ' + TEST173_SEED + ' gave different maps: ' + first + ' vs ' + again)
    }

    var invalid = __test_editor_map_generate_invalid_count(1, 64)
    if (invalid) {
        return test173_fail(invalid + ' of 64 seeds gave a map without water, road or entry/exit')
    }

    __log_marker('editor_map_generate_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_map_generate_ok')
}
