// The editor draws the city flat pass, whose water animation queues new frames instead of writing the image grid
// from the draw workers; the editor must store that queue each frame like the city view does, otherwise its water
// freezes and stale frames land in the next map.
// Markers:
//   [test-marker] editor_water_frames_applied_ok | editor_water_frames_skipped:no_art

function test317_fail(msg) {
    __log_info_native('[test:317] FAIL: ' + msg)
}

function run_test() {
    __log_info_native('[test:317] editor water frames')
    if (!game.init_editor() || !game.editor_is_active()) {
        test317_fail('editor did not start')
        __test_signal_ready()
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var first = 0
    for (var dy = -3; dy <= 3; dy++) {
        for (var dx = -3; dx <= 3; dx++) {
            terrain.add({ x: cx + dx, y: cy + dy }, TERRAIN_WATER)
            first = __test_set_water_image(cx + dx, cy + dy)
        }
    }
    if (!first) {
        __log_marker('editor_water_frames_skipped:no_art')
        __test_signal_ready()
        return
    }
    // The camera keeps its place from the previous session; only visible water tiles animate.
    __camera_go_to_bookmark_tile({ x: cx, y: cy })

    // Water frames step on a 60 ms clock; under load a frame can take longer, so wait up to ~3 s for a step.
    var max_pending = 0
    var advanced = false
    for (var i = 0; i < 150 && !advanced; i++) {
        __test_pump_frames(1)
        __test_sleep_ms(20)
        max_pending = Math.max(max_pending, __test_pending_water_frames())
        advanced = __test_map_image_at(cx, cy) != first
    }
    __test_pump_frames(1)
    max_pending = Math.max(max_pending, __test_pending_water_frames())

    var pending = __test_pending_water_frames()
    if (pending == 0 && advanced) {
        __log_marker('editor_water_frames_applied_ok')
    } else {
        test317_fail('editor water: queue now ' + pending + ' (max ' + max_pending + '), tile image advanced=' + advanced)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('editor_water_frames_applied_ok') || __test_find_inlog('editor_water_frames_skipped:no_art')
}
