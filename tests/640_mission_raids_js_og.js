// The events[] invasions of Migdol (46), Tanis (47), Alexandria (48), Maritis (50) and Cleopatra's Alexandria (51)
// never ran: only a favour chain reaches the OG invasion cycle. They are raids from mission JS that follow it
// (OG scenario_events.c scenario_event_process_invasion): from the event's date (a chained one `time.year` months
// after its parent attacks) the OG warning messages with the invader's phrases (the announcement, then the
// reminders at 24 / 12 / 6 / 1 months left), then the attack months_initial months later with the event's size,
// invader, point (9+ = sea point point - 9 with phrase_var warships, 1..8 = land point, the map exit without one),
// rolled from its location_fields like an OG reset, and target; the attack alert and its on_completed chain come
// with it (invasion_attack).
// Markers:
//   [test-marker] raids_migdol_ok
//   [test-marker] raids_tanis_ok
//   [test-marker] raids_alexandria_ok
//   [test-marker] raids_maritis_ok
//   [test-marker] raids_alexandria3_ok

var test640_failed = false
var test640_started = []
var test640_warned = []

function test640_fail(msg) {
    test640_failed = true
    __log_info_native('[test:640] FAIL: ' + msg)
}

function test640_capture() {
    var start = city.start_foreign_army_invasion
    city.start_foreign_army_invasion = function(opts) {
        var seq = start(opts)
        var n = __city_message_count()
        test640_started.push({ opts: opts, seq: seq, title: __city_message_eventmsg_title_id(n - 1),
            body: __city_message_eventmsg_body_id(n - 1) })
        return seq
    }
    var warn = __city_invasion_warning
    __city_invasion_warning = function(opts) {
        var before = __city_message_count()
        var slot = warn(opts)
        test640_warned.push({ opts: opts, slot: slot, posted: __city_message_count() - before,
            title: __city_message_eventmsg_title_id(__city_message_count() - 1) })
        return slot
    }
    return { start: start, warn: warn }
}

function test640_attacked(invader) {
    if (invader == EVENT_INVADER_EGYPT) {
        return PHRASE_eg_city_attacks_you_city_attacked_alert
    }
    if (invader == EVENT_INVADER_PHARAOH) {
        return PHRASE_pharaoh_attacks_you_city_attacked_alert
    }
    return PHRASE_foreign_army_attacks_you_city_attacked_alert
}

function test640_title(invader) {
    if (invader == EVENT_INVADER_EGYPT) {
        return PHRASE_eg_city_attacks_you_title
    }
    if (invader == EVENT_INVADER_PHARAOH) {
        return PHRASE_pharaoh_attacks_you_title
    }
    return PHRASE_foreign_army_attacks_you_title
}

// OG scenario_value_randomize: the values a location_fields roll can give.
function test640_candidates(l) {
    if (l[1] >= 0 && l[2] < 0) {
        return [l[1]]
    }
    if (l[1] < 0) {
        var out = []
        for (var v = l[2]; v < Math.max(l[3], l[2] + 1); v++) {
            out.push(v)
        }
        return out
    }
    return l[3] >= 0 ? [l[1], l[2], l[3]] : [l[1], l[2]]
}

// OG invasion_warning_for: the slot of `since` months after the date, -1 = none.
function test640_slot(since, months_initial) {
    var left = months_initial - since
    var reminders = [24, 12, 6, 1]
    for (var i = 0; i < reminders.length; i++) {
        if (reminders[i] == left) {
            return i + 1
        }
    }
    return (since == 0 && left > 1) ? 0 : -1
}

function test640_check_attack(name, config, got, want) {
    var o = got.opts
    var what = name + ' raid ' + want.id
    if (o.invasion_id != want.id || o.enemy != want.enemy || o.invader != want.invader || o.size != want.amount
        || o.invasion_attack_target != want.target) {
        test640_fail(what + ': id=' + o.invasion_id + ' enemy=' + o.enemy + ' invader=' + o.invader + ' size='
            + o.size + ' target=' + o.invasion_attack_target)
        return false
    }
    if (test640_candidates(want.loc).indexOf(o.location) < 0) {
        test640_fail(what + ': location ' + o.location + ' not in ' + test640_candidates(want.loc))
        return false
    }
    if (o.location >= 9) {
        if (!o.via_sea || o.sea_point != o.location - 9 || o.warships != want.warships) {
            test640_fail(what + ': sea=' + o.via_sea + ' sea_point=' + o.sea_point + ' warships=' + o.warships)
            return false
        }
    } else {
        var tile = mission_raid_land_tile(config, o.location)
        if (o.via_sea || o.tilex != tile[0] || o.tiley != tile[1]) {
            test640_fail(what + ': tile=' + o.tilex + ',' + o.tiley + ' want ' + tile)
            return false
        }
    }
    if (!got.seq) {
        test640_fail(what + ': nothing spawned')
        return false
    }
    if (got.title != test640_title(want.invader) || got.body != test640_attacked(want.invader)) {
        test640_fail(what + ': attack alert title=' + got.title + ' body=' + got.body)
        return false
    }
    return true
}

// Runs the mission's monthly handler from y0m0 to the last attack; `refusals` call its request-cleared handler
// with a refused request at the start of the given month. Each raid `want` gives its event date [y, m].
function test640_mission(name, id, month_fn, cleared_fn, raids, refusals) {
    __game_load_mission(id, 1)
    __test_clear_enemy_formations()
    if (eval('typeof ' + month_fn) !== 'function' || (cleared_fn && eval('typeof ' + cleared_fn) !== 'function')) {
        test640_fail(name + ': ' + month_fn + (cleared_fn ? ' / ' + cleared_fn : '') + ' missing')
        return
    }
    var config = get_mission_config(id)
    var on_month = eval(month_fn)
    var on_cleared = cleared_fn ? eval(cleared_fn) : null
    var last = 0
    for (var r = 0; r < raids.length; r++) {
        raids[r].date_abs = raids[r].date[0] * 12 + raids[r].date[1]
        raids[r].attack_abs = raids[r].date_abs + raids[r].mi
        last = Math.max(last, raids[r].attack_abs)
    }
    for (var abs = 0; abs <= last; abs++) {
        var y = (abs / 12) | 0
        var m = abs % 12
        __test_simtime_set(y, m)
        for (var f = 0; f < (refusals || []).length; f++) {
            if (refusals[f].y == y && refusals[f].m == m) {
                on_cleared({ tag_id: refusals[f].tag, resource: 0, fulfilled: 0, was_overdue: 0 })
            }
        }
        test640_started = []
        test640_warned = []
        var warships = __test_count_enemy_warships()
        var events = __test_events_count()
        on_month({ years_since_start: y, month: m, year: y, day: 0 })
        var when = name + ' y' + y + 'm' + m
        var attacks = []
        var warnings = []
        for (var i = 0; i < raids.length; i++) {
            var w = raids[i]
            if (abs == w.attack_abs) {
                attacks.push(w)
            } else if (abs >= w.date_abs && abs < w.attack_abs) {
                var slot = test640_slot(abs - w.date_abs, w.mi)
                if (slot >= 0) {
                    warnings.push({ raid: w, slot: slot })
                }
            }
        }
        var posted = 0
        for (var k = 0; k < test640_warned.length; k++) {
            posted += test640_warned[k].slot >= 0 ? 1 : 0
        }
        if (posted != warnings.length) {
            test640_fail(when + ': ' + posted + ' warnings, want ' + warnings.length)
            return
        }
        for (var j = 0, p = 0; j < test640_warned.length; j++) {
            var got = test640_warned[j]
            if (got.slot < 0) {
                continue
            }
            var ww = warnings[p++]
            if (got.slot != ww.slot || got.opts.invasion_id != ww.raid.id || got.posted != 1
                || got.title != test640_title(ww.raid.invader)) {
                test640_fail(when + ': warning raid ' + got.opts.invasion_id + ' slot ' + got.slot + ' posted '
                    + got.posted + ' title ' + got.title + ', want raid ' + ww.raid.id + ' slot ' + ww.slot)
                return
            }
        }
        if (test640_started.length != attacks.length) {
            test640_fail(when + ': ' + test640_started.length + ' attacks, want ' + attacks.length)
            return
        }
        var want_ships = 0
        var want_chain = 0
        for (var a = 0; a < attacks.length; a++) {
            if (!test640_check_attack(name, config, test640_started[a], attacks[a])) {
                return
            }
            want_ships += test640_started[a].opts.via_sea ? attacks[a].warships : 0
            want_chain += attacks[a].chain ? 1 : 0
        }
        if (__test_count_enemy_warships() - warships != want_ships) {
            test640_fail(when + ': warships +' + (__test_count_enemy_warships() - warships) + ' want +' + want_ships)
            return
        }
        if (__test_events_count() - events != want_chain) {
            test640_fail(when + ': chained events +' + (__test_events_count() - events) + ' want +' + want_chain)
            return
        }
    }
    __log_marker('raids_' + name + '_ok')
}

function run_test() {
    __log_info_native('[test:640] mission raids for the OG events[] invasions')
    var saved = test640_capture()
    var E = EVENT_INVADER_ENEMY

    test640_mission('migdol', 46, 'mission46_raids', null, [
        { date: [1, 4], mi: 1, id: 6, invader: E, enemy: ENEMY_8_NUBIAN, amount: 4, loc: [1, 1, -1, -1],
            target: EVENT_ATTACK_TARGET_TROOPS },
        { date: [2, 8], mi: 4, id: 7, invader: E, enemy: ENEMY_8_NUBIAN, amount: 8, loc: [1, -1, 1, 2],
            target: EVENT_ATTACK_TARGET_TROOPS, chain: true },
        { date: [4, 3], mi: 4, id: 8, invader: E, enemy: ENEMY_8_NUBIAN, amount: 15, loc: [2, -1, 2, 3],
            target: EVENT_ATTACK_TARGET_FOOD },
        { date: [5, 3], mi: 5, id: 9, invader: E, enemy: ENEMY_8_NUBIAN, amount: 25, loc: [4, -1, 4, 5],
            target: EVENT_ATTACK_TARGET_BEST_BUILDINGS }
    ])

    test640_mission('tanis', 47, 'mission47_raids', null, [
        { date: [4, 0], mi: 2, id: 0, invader: E, enemy: ENEMY_11_ROMAN, amount: 0, loc: [9, -1, 9, 10], warships: 3,
            target: EVENT_ATTACK_TARGET_TROOPS },
        { date: [6, 2], mi: 8, id: 5, invader: E, enemy: ENEMY_11_ROMAN, amount: 16, loc: [11, 11, -1, -1],
            warships: 5, target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
        // i=5 attacks y6m10 and chains the i=0 copy 4 months on.
        { date: [7, 2], mi: 2, id: 20, invader: E, enemy: ENEMY_11_ROMAN, amount: 0, loc: [9, -1, 9, 10], warships: 3,
            target: EVENT_ATTACK_TARGET_TROOPS },
        { date: [8, 2], mi: 10, id: 12, invader: E, enemy: ENEMY_11_ROMAN, amount: 12, loc: [11, -1, 10, 12],
            warships: 4, target: EVENT_ATTACK_TARGET_RANDOM }
    ])

    test640_mission('alexandria', 48, 'mission48_raids', 'mission48_on_request_cleared', [
        { date: [3, 2], mi: 8, id: 4, invader: E, enemy: ENEMY_10_PHOENICIAN, amount: 7, loc: [9, -1, 9, 11],
            warships: 3, target: EVENT_ATTACK_TARGET_RANDOM, chain: true },
        { date: [8, 8], mi: 6, id: 11, invader: E, enemy: ENEMY_10_PHOENICIAN, amount: 0, loc: [12, -1, 12, 13],
            warships: 3, target: EVENT_ATTACK_TARGET_TROOPS },
        { date: [9, 1], mi: 6, id: 26, invader: EVENT_INVADER_PHARAOH, enemy: ENEMY_3_EGYPTIAN, amount: 20,
            loc: [1, -1, 1, 3], target: EVENT_ATTACK_TARGET_BEST_BUILDINGS, chain: true }
    ], [{ y: 8, m: 9, tag: 1023 }])

    test640_mission('maritis', 50, 'mission50_raids', 'mission50_on_request_cleared', [
        { date: [2, 7], mi: 6, id: 3, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 30,
            loc: [3, -1, 1, 5], target: EVENT_ATTACK_TARGET_TROOPS },
        // i=3 attacks y3m1 and chains i=4 a month on.
        { date: [3, 2], mi: 6, id: 4, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 25,
            loc: [3, -1, 1, 5], target: EVENT_ATTACK_TARGET_TROOPS, chain: true },
        { date: [5, 3], mi: 6, id: 13, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 26,
            loc: [2, -1, 1, 5], target: EVENT_ATTACK_TARGET_RANDOM, chain: true }
    ], [{ y: 5, m: 1, tag: 1009 }])

    test640_mission('alexandria3', 51, 'mission51_raids', 'mission51_on_request_cleared', [
        { date: [5, 0], mi: 12, id: 39, invader: E, enemy: ENEMY_9_PERSIAN, amount: 0, loc: [9, -1, 9, 10],
            warships: 2, target: EVENT_ATTACK_TARGET_RANDOM },
        { date: [6, 7], mi: 12, id: 39, invader: E, enemy: ENEMY_9_PERSIAN, amount: 0, loc: [9, -1, 9, 10],
            warships: 2, target: EVENT_ATTACK_TARGET_RANDOM }
    ], [{ y: 4, m: 6, tag: 1005 }, { y: 6, m: 1, tag: 1005 }, { y: 6, m: 2, tag: 4242 }])

    city.start_foreign_army_invasion = saved.start
    __city_invasion_warning = saved.warn
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
