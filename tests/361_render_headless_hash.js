// Drawing must not change simulation state: the same city run for the same ticks headless and with
// frames drawn between the ticks (incl. the figure-follow snapshot redraw) must hash the same, chunk
// by chunk. A differing chunk is logged by name - that is the finding. The old building animation
// frame in the sprite grid is stepped by the draw as in OG and is left out of the hash; instead one
// drawn frame with a follow snapshot must step it exactly once.

var __t361_ok = false
var __t361_ticks = 300
var __t361_step = 5
var __t361_frames = 2
// Written by the draw but owned by other work in progress (sound view counters, audit item 5):
// logged, not failed, until that lands. Remove a name here once its chunk matches.
var __t361_known = { city_sounds: true }

function t361_fail(msg) {
    __log_info_native('[test:361] FAIL: ' + msg)
    __test_signal_ready()
}

function t361_parse(hash) {
    var out = {}
    var parts = hash.split(';')
    for (var i = 0; i < parts.length; i++) {
        var kv = parts[i].split('=')
        if (kv.length == 2) {
            out[kv[0]] = kv[1]
        }
    }
    return out
}

function t361_diff(a, b) {
    var names = []
    for (var k in a) {
        if (k != 'total' && a[k] != b[k]) {
            names.push(k)
        }
    }
    return names
}

function t361_setup() {
    __test_crt_srand(1)
    __test_libc_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        return null
    }
    __test_process_events()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var shops = []
    var types = [BUILDING_BAZAAR]
    for (var i = 0; i < types.length; i++) {
        var bid = test_building_place(types[i], -1, -1)
        if (bid) {
            shops.push(bid)
        }
    }
    t361_staff(shops)
    var seeker = __test_figure_create(FIGURE_LABOR_SEEKER, cx, cy)
    var other = __test_figure_create(FIGURE_LABOR_SEEKER, cx + 2, cy + 1)
    if (!seeker || !other) {
        return null
    }
    // Without art no animation is valid, and the draw-side image update would have nothing to do.
    __test_figure_set_force_valid_animation(seeker, 1)
    __test_figure_set_force_valid_animation(other, 1)
    if (shops.length) {
        __test_camera_center_building(shops[0])
    }
    __test_process_events()
    return { seeker: seeker, shops: shops }
}

// No population: the labour update would empty the bazaar, and an unstaffed one does not animate.
function t361_staff(shops) {
    for (var i = 0; i < shops.length; i++) {
        __test_building_set_workers(shops[i], 20)
    }
}

// Returns the frame step of the first animating bazaar over one drawn frame with a snapshot, or -1.
function t361_anim_step(shops) {
    for (var i = 0; i < shops.length; i++) {
        var tile = __building_tile(shops[i])
        var watcher = __test_figure_create(FIGURE_LABOR_SEEKER, tile.x, tile.y)
        if (!watcher || !__figure_follow_start(watcher)) {
            __log_info_native('[test:361] no figure to follow at shop ' + shops[i])
            continue
        }
        var before = __test_building_sprite_frame(shops[i])
        __test_draw_frames(1)
        var after = __test_building_sprite_frame(shops[i])
        if (before > 0 || after > 0) {
            __log_info_native('[test:361] shop ' + shops[i] + ' frame ' + before + ' -> ' + after)
            return after >= before ? after - before : 1
        }
    }
    return -1
}

function t361_run(drawn) {
    var s = t361_setup()
    if (!s) {
        return null
    }
    var out = { anim_step: -1 }
    if (drawn) {
        // Figures that have not ticked yet: only a drawing would give them a sprite.
        __test_state_mark()
        __test_draw_frames(__t361_frames)
        __test_state_diff('t361_setup_draw')
    }
    out.start = t361_parse(__test_state_hash_drawn())
    for (var t = 0; t < __t361_ticks; t += __t361_step) {
        for (var k = 0; k < __t361_step; k++) {
            t361_staff(s.shops)
            if (__test_run_ticks(1) != 1) {
                return null
            }
        }
        if (drawn) {
            __test_draw_frames(__t361_frames)
        }
    }
    out.end = t361_parse(__test_state_hash_drawn())
    if (drawn) {
        out.anim_step = t361_anim_step(s.shops)
        if (__figure_follow_enabled()) {
            __figure_follow_stop()
        }
    }
    return out
}

function t361_report(label, a, b) {
    if (a.total == b.total) {
        return []
    }
    var names = t361_diff(a, b)
    var unexpected = []
    for (var i = 0; i < names.length; i++) {
        var known = __t361_known[names[i]] === true
        __log_info_native('[test:361] ' + label + ' chunk differs' + (known ? ' (known)' : '') + ': '
            + names[i] + ' ' + a[names[i]] + ' ' + b[names[i]])
        if (known) {
            __log_marker('t361_known_differs:' + label + ':' + names[i])
        } else {
            unexpected.push(names[i])
        }
    }
    return unexpected
}

function run_test() {
    __log_info_native('[test:361] drawn frames vs headless ticks state hash')

    var headless = t361_run(false)
    if (!headless) {
        return t361_fail('headless pass setup')
    }
    var drawn = t361_run(true)
    if (!drawn) {
        return t361_fail('drawn pass setup')
    }

    __log_info_native('[test:361] start ' + headless.start.total + ' ' + drawn.start.total
        + ' end ' + headless.end.total + ' ' + drawn.end.total + ' anim_step ' + drawn.anim_step)
    var start_diff = t361_report('start', headless.start, drawn.start)
    var end_diff = t361_report('end', headless.end, drawn.end)
    if (start_diff.length || end_diff.length) {
        __log_marker('t361_differs:start=' + start_diff.join(',') + ':end=' + end_diff.join(','))
        return t361_fail('drawing changed ' + start_diff.length + '+' + end_diff.length + ' chunks')
    }
    if (drawn.anim_step < 0) {
        __log_marker('t361_anim_step_skipped:no_animation')
    } else if (drawn.anim_step != 1) {
        __log_marker('t361_anim_step_wrong:' + drawn.anim_step)
        return t361_fail('one drawn frame stepped the building animation ' + drawn.anim_step + ' times')
    }

    __log_marker('t361_render_headless_equal')
    __t361_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t361_ok && __test_find_inlog('[test-marker] t361_render_headless_equal')
}
