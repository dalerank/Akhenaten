// The events[] invasions of Migdol (46), Tanis (47), Alexandria (48), Maritis (50) and Cleopatra's Alexandria (51)
// never ran: only a favour chain reaches the OG invasion cycle. They are raids started from mission JS now, each in
// the month of its OG event (a chained one `time.year` months after its parent fires) with the event's size,
// invader, point (9+ = sea point point - 9 with phrase_var warships, 1..8 = land point, the map exit without one)
// and attack target, firing its on_completed chain as it starts (OG scenario_events.c invasion_attack).
// Markers:
//   [test-marker] raids_migdol_ok
//   [test-marker] raids_tanis_ok
//   [test-marker] raids_alexandria_ok
//   [test-marker] raids_maritis_ok
//   [test-marker] raids_alexandria3_ok

var test640_failed = false
var test640_started = []

function test640_fail(msg) {
    test640_failed = true
    __log_info_native('[test:640] FAIL: ' + msg)
}

function test640_capture() {
    var start = city.start_foreign_army_invasion
    city.start_foreign_army_invasion = function(opts) {
        var seq = start(opts)
        test640_started.push({ opts: opts, seq: seq })
        return seq
    }
    return start
}

function test640_same(a, b) {
    return (a === undefined ? -1 : a) == (b === undefined ? -1 : b)
}

function test640_check(name, got, want) {
    var o = got.opts
    var sea = !!want.sea
    var what = name + ' raid ' + want.id + ' y' + want.y + 'm' + want.m
    if (o.invasion_id != want.id || o.enemy != want.enemy || o.size != want.size || !!o.via_sea != sea
        || o.invasion_attack_target != want.target) {
        test640_fail(what + ': id=' + o.invasion_id + ' enemy=' + o.enemy + ' size=' + o.size + ' sea=' + o.via_sea
            + ' target=' + o.invasion_attack_target)
        return false
    }
    if (sea && (o.sea_point != want.sea_point || o.warships != want.warships)) {
        test640_fail(what + ': sea_point=' + o.sea_point + ' warships=' + o.warships)
        return false
    }
    if (!sea && (!test640_same(o.tilex, want.tile[0]) || !test640_same(o.tiley, want.tile[1]))) {
        test640_fail(what + ': tile=' + o.tilex + ',' + o.tiley + ' want ' + want.tile)
        return false
    }
    if (!got.seq) {
        test640_fail(what + ': nothing spawned')
        return false
    }
    return true
}

// Runs the mission's monthly handler from y0m0 to the last raid; `refusals` call its request-cleared handler
// with a refused request in the given month (before that month's monthly pass).
function test640_mission(name, id, month_fn, cleared_fn, raids, refusals) {
    __game_load_mission(id, 1)
    __test_clear_enemy_formations()
    if (eval('typeof ' + month_fn) !== 'function' || (cleared_fn && eval('typeof ' + cleared_fn) !== 'function')) {
        test640_fail(name + ': ' + month_fn + (cleared_fn ? ' / ' + cleared_fn : '') + ' missing')
        return
    }
    var on_month = eval(month_fn)
    var on_cleared = cleared_fn ? eval(cleared_fn) : null
    var last = raids[raids.length - 1]
    var next = 0
    for (var y = 0; y <= last.y; y++) {
        for (var m = 0; m < 12 && (y < last.y || m <= last.m); m++) {
            __test_simtime_set(y, m)
            for (var r = 0; r < (refusals || []).length; r++) {
                if (refusals[r].y == y && refusals[r].m == m) {
                    on_cleared({ tag_id: refusals[r].tag, resource: 0, fulfilled: 0, was_overdue: 0 })
                }
            }
            test640_started = []
            var warships = __test_count_enemy_warships()
            var events = __test_events_count()
            on_month({ years_since_start: y, month: m, year: y, day: 0 })
            var due = []
            while (next < raids.length && raids[next].y == y && raids[next].m == m) {
                due.push(raids[next++])
            }
            if (test640_started.length != due.length) {
                test640_fail(name + ' y' + y + 'm' + m + ': ' + test640_started.length + ' raids started, want '
                    + due.length)
                return
            }
            var want_ships = 0
            var want_chain = 0
            for (var i = 0; i < due.length; i++) {
                if (!test640_check(name, test640_started[i], due[i])) {
                    return
                }
                want_ships += due[i].sea ? due[i].warships : 0
                want_chain += due[i].chain ? 1 : 0
            }
            if (__test_count_enemy_warships() - warships != want_ships) {
                test640_fail(name + ' y' + y + 'm' + m + ': warships +' + (__test_count_enemy_warships() - warships)
                    + ' want +' + want_ships)
                return
            }
            if (want_chain && __test_events_count() - events != want_chain) {
                test640_fail(name + ' y' + y + 'm' + m + ': chained events +' + (__test_events_count() - events))
                return
            }
        }
    }
    __log_marker('raids_' + name + '_ok')
}

function run_test() {
    __log_info_native('[test:640] mission raids for the OG events[] invasions')
    var start = test640_capture()

    var exit46 = [71, 16]
    test640_mission('migdol', 46, 'mission46_raids', null, [
        { y: 1, m: 4, id: 6, enemy: ENEMY_8_NUBIAN, size: 4, tile: exit46, target: EVENT_ATTACK_TARGET_TROOPS },
        { y: 2, m: 8, id: 7, enemy: ENEMY_8_NUBIAN, size: 8, tile: exit46, target: EVENT_ATTACK_TARGET_TROOPS,
            chain: true },
        { y: 4, m: 3, id: 8, enemy: ENEMY_8_NUBIAN, size: 15, tile: exit46, target: EVENT_ATTACK_TARGET_FOOD },
        { y: 5, m: 3, id: 9, enemy: ENEMY_8_NUBIAN, size: 25, tile: exit46,
            target: EVENT_ATTACK_TARGET_BEST_BUILDINGS }
    ])

    test640_mission('tanis', 47, 'mission47_raids', null, [
        { y: 4, m: 0, id: 0, enemy: ENEMY_11_ROMAN, size: 0, sea: true, sea_point: 0, warships: 3,
            target: EVENT_ATTACK_TARGET_TROOPS },
        { y: 6, m: 2, id: 5, enemy: ENEMY_11_ROMAN, size: 16, sea: true, sea_point: 2, warships: 5,
            target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
        { y: 6, m: 6, id: 20, enemy: ENEMY_11_ROMAN, size: 0, sea: true, sea_point: 0, warships: 3,
            target: EVENT_ATTACK_TARGET_TROOPS },
        { y: 8, m: 2, id: 12, enemy: ENEMY_11_ROMAN, size: 12, sea: true, sea_point: 2, warships: 4,
            target: EVENT_ATTACK_TARGET_RANDOM }
    ])

    test640_mission('alexandria', 48, 'mission48_raids', 'mission48_on_request_cleared', [
        { y: 3, m: 2, id: 4, enemy: ENEMY_10_PHOENICIAN, size: 7, sea: true, sea_point: 0, warships: 3,
            target: EVENT_ATTACK_TARGET_RANDOM, chain: true },
        { y: 8, m: 8, id: 11, enemy: ENEMY_10_PHOENICIAN, size: 0, sea: true, sea_point: 3, warships: 3,
            target: EVENT_ATTACK_TARGET_TROOPS },
        { y: 9, m: 1, id: 26, enemy: ENEMY_3_EGYPTIAN, size: 20, tile: [208, 102],
            target: EVENT_ATTACK_TARGET_BEST_BUILDINGS, chain: true }
    ], [{ y: 8, m: 9, tag: 1023 }])

    var exit50 = [106, 100]
    test640_mission('maritis', 50, 'mission50_raids', 'mission50_on_request_cleared', [
        { y: 2, m: 7, id: 3, enemy: ENEMY_3_EGYPTIAN, size: 30, tile: exit50, target: EVENT_ATTACK_TARGET_TROOPS },
        { y: 2, m: 8, id: 4, enemy: ENEMY_3_EGYPTIAN, size: 25, tile: exit50, target: EVENT_ATTACK_TARGET_TROOPS,
            chain: true },
        { y: 5, m: 3, id: 13, enemy: ENEMY_3_EGYPTIAN, size: 26, tile: exit50, target: EVENT_ATTACK_TARGET_RANDOM,
            chain: true }
    ], [{ y: 5, m: 1, tag: 1009 }])

    test640_mission('alexandria3', 51, 'mission51_raids', 'mission51_on_request_cleared', [
        { y: 5, m: 0, id: 39, enemy: ENEMY_9_PERSIAN, size: 0, sea: true, sea_point: 0, warships: 2,
            target: EVENT_ATTACK_TARGET_RANDOM },
        { y: 6, m: 0, id: 39, enemy: ENEMY_9_PERSIAN, size: 0, sea: true, sea_point: 0, warships: 2,
            target: EVENT_ATTACK_TARGET_RANDOM }
    ], [{ y: 4, m: 6, tag: 1005 }, { y: 5, m: 6, tag: 1005 }, { y: 5, m: 7, tag: 4242 }])

    city.start_foreign_army_invasion = start
    __test_signal_ready()
}

function check_valid() {
    var markers = ['raids_migdol_ok', 'raids_tanis_ok', 'raids_alexandria_ok', 'raids_maritis_ok', 'raids_alexandria3_ok']
    if (test640_failed) {
        return false
    }
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:640] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
