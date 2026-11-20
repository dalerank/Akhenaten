// Drawing must not change simulation state: the same city run for the same ticks headless and with
// frames drawn between the ticks (incl. the figure-follow snapshot redraw) must hash the same, chunk
// by chunk, and no drawn frame may change a saved byte. A differing chunk is logged by name - that
// is the finding. Building sprite animations tick with the simulation: a drawn frame must not step
// a bazaar's animation, a tick must.

var __t334_ok = false
var __t334_ticks = 300
var __t334_step = 5
var __t334_frames = 2
var __t334_known = {}
var __t334_draw_diffs = {}

function t334_fail(msg) {
    __log_info_native('[test:334] FAIL: ' + msg)
    __test_signal_ready()
}

function t334_parse(hash) {
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

function t334_diff(a, b) {
    var names = []
    for (var k in a) {
        if (k != 'total' && a[k] != b[k]) {
            names.push(k)
        }
    }
    return names
}

function t334_setup() {
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
    t334_staff(shops)
    var seeker = __test_figure_create(FIGURE_LABOR_SEEKER, cx, cy)
    var other = __test_figure_create(FIGURE_LABOR_SEEKER, cx + 2, cy + 1)
    if (!seeker || !other) {
        return null
    }
    if (shops.length) {
        __test_camera_center_building(shops[0])
    }
    __test_process_events()
    return { seeker: seeker, shops: shops }
}

// No population: the labour update would empty the bazaar, and an unstaffed one does not animate.
function t334_staff(shops) {
    for (var i = 0; i < shops.length; i++) {
        __test_building_set_workers(shops[i], 20)
    }
}

// Over one drawn frame with a follow snapshot, then over ticks with no drawing: the bazaar's frame
// must not move in the first and must move in the second. Returns null when nothing animates.
function t334_anim_steps(shops) {
    for (var i = 0; i < shops.length; i++) {
        var tile = __building_tile(shops[i])
        var watcher = __test_figure_create(FIGURE_LABOR_SEEKER, tile.x, tile.y)
        if (!watcher || !__figure_follow_start(watcher)) {
            __log_info_native('[test:334] no figure to follow at shop ' + shops[i])
            continue
        }
        var before = __test_building_sprite_frame(shops[i])
        if (before <= 0) {
            continue
        }
        __test_draw_frames(1)
        var drawn = __test_building_sprite_frame(shops[i])
        t334_staff(shops)
        __test_run_ticks(1)
        var ticked = __test_building_sprite_frame(shops[i])
        __log_info_native('[test:334] shop ' + shops[i] + ' frame ' + before + ' drawn ' + drawn + ' ticked ' + ticked)
        return { drawn: drawn != before, ticked: ticked != drawn }
    }
    return null
}

// Draws n frames and records every chunk that the drawing alone changed.
function t334_draw(n) {
    __test_state_mark()
    __test_draw_frames(n)
    var changed = __test_state_diff('t334_draw')
    if (!changed) {
        return
    }
    var names = changed.split(',')
    for (var i = 0; i < names.length; i++) {
        __t334_draw_diffs[names[i]] = true
    }
}

function t334_run(drawn) {
    var s = t334_setup()
    if (!s) {
        return null
    }
    var out = { anim: null }
    if (drawn) {
        // Figures that have not ticked yet: only a drawing would give them a sprite.
        t334_draw(__t334_frames)
    }
    for (var t = 0; t < __t334_ticks; t += __t334_step) {
        for (var k = 0; k < __t334_step; k++) {
            t334_staff(s.shops)
            if (__test_run_ticks(1) != 1) {
                return null
            }
        }
        if (drawn) {
            t334_draw(__t334_frames)
        }
    }
    out.end = t334_parse(__test_state_hash())
    if (drawn) {
        out.anim = t334_anim_steps(s.shops)
        if (__figure_follow_enabled()) {
            __figure_follow_stop()
        }
    }
    return out
}

function t334_report(label, a, b) {
    if (a.total == b.total) {
        return []
    }
    var names = t334_diff(a, b)
    var unexpected = []
    for (var i = 0; i < names.length; i++) {
        var known = __t334_known[names[i]] === true
        __log_info_native('[test:334] ' + label + ' chunk differs' + (known ? ' (known)' : '') + ': '
            + names[i] + ' ' + a[names[i]] + ' ' + b[names[i]])
        if (known) {
            __log_marker('t334_known_differs:' + label + ':' + names[i])
        } else {
            unexpected.push(names[i])
        }
    }
    return unexpected
}

function run_test() {
    __log_info_native('[test:334] drawn frames vs headless ticks state hash')

    var headless = t334_run(false)
    if (!headless) {
        return t334_fail('headless pass setup')
    }
    var drawn = t334_run(true)
    if (!drawn) {
        return t334_fail('drawn pass setup')
    }

    __log_info_native('[test:334] end ' + headless.end.total + ' ' + drawn.end.total)
    var draw_diff = []
    for (var k in __t334_draw_diffs) {
        if (__t334_known[k] === true) {
            __log_marker('t334_known_differs:draw:' + k)
        } else {
            draw_diff.push(k)
        }
    }
    var end_diff = t334_report('end', headless.end, drawn.end)
    if (draw_diff.length || end_diff.length) {
        __log_marker('t334_differs:draw=' + draw_diff.join(',') + ':end=' + end_diff.join(','))
        return t334_fail('drawing changed ' + draw_diff.length + '+' + end_diff.length + ' chunks')
    }
    if (!drawn.anim) {
        __log_marker('t334_anim_skipped:no_animation')
    } else if (drawn.anim.drawn || !drawn.anim.ticked) {
        __log_marker('t334_anim_wrong:drawn=' + drawn.anim.drawn + ':ticked=' + drawn.anim.ticked)
        return t334_fail('the bazaar animation must step with ticks only')
    }

    __log_marker('t334_render_headless_equal')
    __t334_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t334_ok && __test_find_inlog('[test-marker] t334_render_headless_equal')
}
