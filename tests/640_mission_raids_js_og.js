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
    if (invader == EVENT_INVADER_BEDUINS) {
        return PHRASE_bedouin_attacks_you_city_attacked_alert
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
    if (invader == EVENT_INVADER_BEDUINS) {
        return PHRASE_bedouin_attacks_you_title
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
        // No fighting happens here, so armies would pile up into the formation limit over the decades.
        __test_clear_enemy_formations()
        for (var f = 0; f < (refusals || []).length; f++) {
            if (refusals[f].y == y && refusals[f].m == m) {
                on_cleared({ tag_id: refusals[f].tag, resource: 0, fulfilled: refusals[f].ok ? 1 : 0, was_overdue: 0 })
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
        warnings.sort(function(a, b) { return a.raid.id - b.raid.id })
        attacks.sort(function(a, b) { return a.id - b.id })
        test640_warned.sort(function(a, b) { return a.opts.invasion_id - b.opts.invasion_id })
        test640_started.sort(function(a, b) { return a.opts.invasion_id - b.opts.invasion_id })
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
            if (attacks[a].chain < 0) {
                want_chain = -1000
            }
            want_chain += attacks[a].chain === true ? 1 : (attacks[a].chain || 0)
        }
        if (__test_count_enemy_warships() - warships != want_ships) {
            test640_fail(when + ': warships +' + (__test_count_enemy_warships() - warships) + ' want +' + want_ships)
            return
        }
        if (want_chain >= 0 && __test_events_count() - events != want_chain) {
            test640_fail(when + ': chained events +' + (__test_events_count() - events) + ' want +' + want_chain)
            return
        }
    }
    __log_marker('raids_' + name + '_ok')
}

// Rows [y, m, months_initial, id, invader, enemy, amount, location_fields, warships, target, chain]: the event
// date of each raid's first cycle; chain = events its on_completed adds (-1 = not counted).
function test640_rows(rows) {
    var out = []
    for (var i = 0; i < rows.length; i++) {
        var r = rows[i]
        out.push({ date: [r[0], r[1]], mi: r[2], id: r[3], invader: r[4], enemy: r[5], amount: r[6], loc: r[7],
            warships: r[8], target: r[9], chain: r[10] || 0 })
    }
    return out
}

// The older JS raids moved onto the shared cycle, with the OG events' fields.
function test640_older_missions() {
    var E = EVENT_INVADER_ENEMY
    var B = EVENT_INVADER_BEDUINS
    var T = { food: EVENT_ATTACK_TARGET_FOOD, vaults: EVENT_ATTACK_TARGET_VAULTS,
        best: EVENT_ATTACK_TARGET_BEST_BUILDINGS, troops: EVENT_ATTACK_TARGET_TROOPS, random: EVENT_ATTACK_TARGET_RANDOM }
    test640_mission('timna', 5, 'mission5_raids', null, test640_rows([
        [2, 7, 12, 4, B, ENEMY_7_LIBIAN, 9, [2, 2, -1, -1], 0, T.random],
        [3, 9, 9, 8, B, ENEMY_7_LIBIAN, 16, [1, 1, -1, -1], 0, T.vaults],
        [5, 0, 7, 9, B, ENEMY_7_LIBIAN, 24, [3, -1, 1, 4], 0, T.vaults]
    ]))
    test640_mission('behdet', 6, 'mission6_raids', null, test640_rows([
        [5, 1, 18, 9, E, ENEMY_6_KUSHITE, 5, [9, 9, -1, -1], 2, T.random],
        [15, 0, 16, 13, E, ENEMY_6_KUSHITE, 16, [9, 9, -1, -1], 3, T.troops, 2],
        [19, 4, 16, 18, E, ENEMY_6_KUSHITE, 4, [9, 9, -1, -1], 2, T.best]
    ]))
    test640_mission('abydos', 7, 'mission7_raids', null, test640_rows([
        [14, 9, 16, 13, E, ENEMY_6_KUSHITE, 3, [9, 9, -1, -1], 1, T.random]
    ]))
    test640_mission('selima', 8, 'mission8_raids', null, test640_rows([
        [2, 4, 12, 5, E, ENEMY_5_HYKSOS, 9, [2, 2, -1, -1], 0, T.troops, 2],
        [7, 0, 4, 25, E, ENEMY_5_HYKSOS, 22, [2, 2, -1, -1], 0, T.troops, -1]
    ]))
    test640_mission('serabit', 11, 'mission11_raids', null, test640_rows([
        [1, 10, 24, 6, E, ENEMY_7_LIBIAN, 8, [4, 4, -1, -1], 0, T.vaults],
        [2, 4, 0, 5, B, ENEMY_7_LIBIAN, 16, [1, -1, 1, 4], 0, T.random],
        [3, 3, 12, 8, E, ENEMY_7_LIBIAN, 12, [3, 3, -1, -1], 0, T.best],
        [4, 8, 24, 9, E, ENEMY_7_LIBIAN, 20, [4, 4, -1, -1], 0, T.food],
        [6, 0, 24, 12, E, ENEMY_7_LIBIAN, 28, [1, 1, -1, -1], 0, T.vaults],
        [8, 6, 18, 14, E, ENEMY_7_LIBIAN, 28, [2, 2, -1, -1], 0, T.random],
        [10, 1, 24, 15, E, ENEMY_7_LIBIAN, 32, [3, -1, 3, 4], 0, T.best]
    ]))
    test640_mission('meidum', 12, 'mission12_raids', null, test640_rows([
        [7, 6, 12, 70, E, ENEMY_5_HYKSOS, 17, [1, 1, -1, -1], 0, T.random]
    ]))
    var H = ENEMY_5_HYKSOS
    test640_mission('north_dahshur', 15, 'mission15_raids', 'mission15_on_request_cleared', test640_rows([
        [3, 11, 18, 7, E, H, 5, [1, -1, 1, 2], 0, T.food],
        [5, 3, 30, 30, E, H, 12, [1, -1, 1, 2], 0, T.best],
        [6, 8, 2, 6, B, ENEMY_7_LIBIAN, 10, [2, -1, 1, 3], 0, T.random],
        // i=7 attacks y5m5 and chains i=8 43 months on, which chains i=9 56 months after its attack, and so on.
        [9, 0, 24, 8, E, H, 6, [1, -1, 1, 2], 0, T.best],
        [15, 8, 24, 9, E, H, 6, [1, -1, 1, 2], 0, T.food],
        [20, 7, 24, 10, E, H, 11, [1, -1, 1, 2], 0, T.vaults],
        [21, 3, 24, 8, E, H, 6, [1, -1, 1, 2], 0, T.best]
    ]), [{ y: 2, m: 3, tag: 4102 }])
    var HT = ENEMY_4_HITTITE
    test640_mission('iunet', 16, 'mission16_raids', 'mission16_on_request_cleared', test640_rows([
        [2, 7, 9, 3, E, HT, 0, [9, 9, -1, -1], 1, T.random],
        [4, 0, 9, 8, E, HT, 10, [9, 9, -1, -1], 2, T.random],
        [5, 10, 9, 12, E, HT, 20, [9, 9, -1, -1], 4, T.random],
        [8, 0, 12, 13, E, HT, 32, [9, 9, -1, -1], 5, T.food],
        [10, 8, 2, 16, EVENT_INVADER_EGYPT, ENEMY_3_EGYPTIAN, 24, [10, 10, -1, -1], 6, T.food],
        [16, 10, 18, 17, E, HT, 48, [9, 9, -1, -1], 8, T.food, -1]
    ]), [{ y: 10, m: 6, tag: 2014 }])
    test640_mission('rostja', 18, 'mission18_raids', 'mission18_on_request_cleared', test640_rows([
        [5, 7, 10, 26, E, H, 6, [4, -1, 1, 8], 0, T.best],
        [7, 9, 6, 29, E, H, 11, [5, -1, 1, 8], 0, T.vaults],
        [9, 7, 9, 35, E, H, 9, [7, -1, 1, 8], 0, T.food, 1],
        [26, 10, 2, 37, E, H, 10, [3, -1, 1, 8], 0, T.food, -1]
    ]), [{ y: 7, m: 1, tag: 2027 }, { y: 9, m: 0, tag: 2030 }])
    var L = ENEMY_7_LIBIAN
    test640_mission('bahariya', 19, 'mission19_raids', null, test640_rows([
        [5, 9, 0, 0, E, H, 8, [1, 1, -1, -1], 0, T.random, 0],
        [7, 4, 2, 1, E, H, 16, [1, 1, -1, -1], 0, T.food, 2],
        [8, 10, 2, 3, B, L, 16, [8, 8, -1, -1], 0, T.food, 0],
        [9, 2, 12, 4, E, H, 32, [3, 3, -1, -1], 0, T.vaults, 2],
        [11, 6, 2, 5, E, H, 64, [2, 2, -1, -1], 0, T.best, 0],
        [12, 3, 2, 7, B, L, 32, [7, 7, -1, -1], 0, T.food, 0],
        [14, 0, 2, 9, B, L, 64, [7, -1, 6, 8], 0, T.food, 0],
        [17, 4, 2, 11, E, H, 80, [1, -1, 1, 4], 0, T.troops, 0],
        [17, 9, 2, 12, B, L, 32, [7, -1, 4, 8], 0, T.food, 0],
        [21, 2, 2, 13, E, H, 96, [1, -1, 1, 4], 0, T.vaults, 0],
        [22, 1, 2, 14, E, H, 48, [3, -1, 1, 4], 0, T.best, 0],
        [22, 6, 2, 15, B, L, 32, [5, -1, 4, 8], 0, T.food, 0],
        [26, 3, 2, 17, E, H, 80, [3, -1, 1, 4], 0, T.troops, 0],
        [26, 10, 2, 18, E, H, 48, [2, -1, 1, 4], 0, T.food, 0],
        [27, 3, 2, 19, B, L, 32, [5, -1, 4, 8], 0, T.food, 0],
        [31, 1, 2, 21, E, H, 64, [3, -1, 1, 4], 0, T.vaults, 0],
        [31, 4, 2, 22, E, H, 96, [3, -1, 1, 4], 0, T.best, 0],
        [31, 10, 2, 23, B, L, 48, [4, -1, 4, 8], 0, T.food, 0],
        [46, 5, 6, 24, E, H, 64, [2, -1, 1, 4], 0, T.food, 0],
        [2, 0, 12, 26, E, H, 8, [2, -1, 1, 8], 0, T.best, -1],
        [6, 4, 2, 41, E, H, 16, [1, 1, -1, -1], 0, T.food, 2]
    ]))
    test640_mission('dunqul', 21, 'mission21_raids', null, test640_rows([
        [1, 0, 6, 11, B, L, 5, [8, 8, -1, -1], 0, T.random],
        [3, 0, 3, 12, B, L, 12, [4, -1, 1, 8], 0, T.random, 2],
        [4, 4, 12, 14, E, HT, 43, [3, -1, 3, 6], 0, T.random, 2]
    ]))
    test640_mission('sawu', 29, 'mission29_raids', null, test640_rows([
        [4, 10, 8, 23, B, L, 9, [3, 3, -1, -1], 0, T.random],
        [12, 0, 12, 24, E, L, 5, [9, 9, -1, -1], 2, T.troops],
        [20, 0, 8, 25, B, L, 8, [1, -1, 1, 2], 0, T.random],
        [23, 11, 12, 26, E, L, 8, [9, 9, -1, -1], 2, T.food],
        [30, 0, 8, 27, B, L, 9, [1, -1, 1, 2], 0, T.random],
        [45, 4, 12, 28, E, L, 9, [9, 9, -1, -1], 2, T.troops]
    ]))
    var K = ENEMY_6_KUSHITE
    test640_mission('heh', 30, 'mission30_raids', null, test640_rows([
        [6, 11, 6, 18, E, K, 16, [10, 10, -1, -1], 2, T.random],
        [8, 4, 9, 20, E, K, 38, [9, 9, -1, -1], 6, T.random],
        [10, 0, 9, 21, E, K, 40, [9, 9, -1, -1], 4, T.random],
        [12, 6, 9, 22, E, K, 40, [1, -1, 1, 3], 0, T.random],
        [13, 3, 0, 23, E, K, 20, [9, 9, -1, -1], 2, T.random],
        [14, 0, 6, 28, E, K, 16, [6, -1, 1, 8], 0, T.random],
        [16, 0, 9, 24, E, K, 60, [9, 9, -1, -1], 6, T.random],
        [19, 6, 12, 25, E, K, 40, [2, -1, 1, 8], 0, T.random],
        [21, 0, 3, 27, E, K, 24, [8, 8, -1, -1], 0, T.random],
        [40, 0, 12, 29, E, K, 72, [3, -1, 1, 8], 0, T.random],
        [50, 7, 12, 30, E, K, 72, [9, 9, -1, -1], 6, T.random],
        [60, 10, 12, 31, E, K, 72, [9, 9, -1, -1], 7, T.random]
    ]))
    var C = ENEMY_2_CANAANITE
    test640_mission('byblos', 34, 'mission34_raids', null, test640_rows([
        [2, 0, 6, 0, E, C, 28, [3, -1, 1, 4], 0, T.best],
        [6, 4, 2, 5, E, C, 64, [5, -1, 5, 8], 0, T.food],
        [12, 3, 6, 24, B, L, 96, [1, -1, 1, 8], 0, T.food],
        [16, 0, 6, 29, E, C, 125, [11, -1, 9, 13], 12, T.random],
        [22, 8, 18, 33, E, C, 119, [3, -1, 1, 8], 0, T.vaults],
        [28, 8, 6, 37, E, C, 141, [12, -1, 9, 13], 12, T.food]
    ]))
    test640_mission('sumur', 41, 'mission41_raids', 'mission41_on_request_cleared', test640_rows([
        [5, 2, 10, 11, E, C, 42, [2, -1, 1, 3], 0, T.random],
        [12, 3, 7, 31, E, C, 33, [5, 5, -1, -1], 0, T.best]
    ]), [{ y: 5, m: 2, tag: 2009 }])
    test640_mission('qadesh', 42, 'mission42_raids', null, test640_rows([
        [1, 4, 12, 1, E, C, 50, [1, -1, 1, 3], 0, T.troops],
        [2, 4, 0, 19, E, C, 30, [4, -1, 4, 5], 0, T.troops],
        [2, 6, 0, 22, E, C, 35, [1, -1, 1, 5], 0, T.random]
    ]))
    test640_mission('abu_simbel', 43, 'mission43_raids', 'mission43_on_request_cleared', test640_rows([
        [5, 10, 6, 12, E, ENEMY_6_KUSHITE, 25, [2, -1, 1, 3], 0, T.random],
        [8, 1, 9, 20, E, ENEMY_6_KUSHITE, 27, [3, 3, -1, -1], 0, T.troops, -1]
    ]), [{ y: 5, m: 9, tag: 2010 }])
    var A = ENEMY_1_ASSYRIAN
    test640_mission('pi_yer', 45, 'mission45_raids', 'mission45_on_request_cleared', test640_rows([
        [1, 4, 8, 4, E, A, 17, [9, 9, -1, -1], 3, T.best],
        [2, 1, 2, 9, E, A, 13, [1, 1, -1, -1], 0, T.food],
        [9, 5, 6, 39, E, A, 27, [9, 9, -1, -1], 3, T.random],
        [13, 10, 12, 29, EVENT_INVADER_PHARAOH, ENEMY_3_EGYPTIAN, 12, [2, 2, -1, -1], 0, T.best]
    ]), [{ y: 1, m: 3, tag: 2005 }, { y: 8, m: 6, tag: 2037 }, { y: 13, m: 6, tag: 2027 }])
    test640_mission('actium', 52, 'mission52_raids', null, test640_rows([
        [4, 4, 4, 12, E, ENEMY_9_PERSIAN, 19, [9, -1, 9, 11], 5, T.troops],
        [4, 10, 1, 17, E, ENEMY_9_PERSIAN, 40, [9, -1, 9, 11], 4, T.troops, 1]
    ]))
    test640_mission('rowarty', 36, 'mission36_raids', 'mission36_on_request_cleared', test640_rows([
        [2, 8, 5, 8, E, A, 38, [9, -1, 9, 13], 5, T.vaults, -1],
        [3, 1, 6, 0, E, A, 20, [11, -1, 9, 13], 2, T.food],
        [5, 8, 6, 1, E, A, 35, [11, -1, 9, 15], 6, T.random],
        [7, 1, 6, 5, E, A, 44, [10, -1, 9, 13], 8, T.food],
        [45, 10, 6, 11, E, A, 56, [12, -1, 9, 13], 6, T.random],
        [53, 1, 6, 56, E, A, 72, [10, -1, 9, 16], 12, T.random]
    ]), [{ y: 52, m: 4, tag: 54 }])
    var EG = EVENT_INVADER_EGYPT
    test640_mission('waset', 24, 'mission24_raids', 'mission24_on_request_cleared', test640_rows([
        [5, 2, 2, 7, EG, ENEMY_3_EGYPTIAN, 6, [9, 9, -1, -1], 1, T.vaults],
        [11, 8, 3, 21, EG, ENEMY_3_EGYPTIAN, 4, [9, 9, -1, -1], 1, T.vaults]
    ]), [{ y: 4, m: 10, tag: 2004 }, { y: 11, m: 4, tag: 2018 }])
    var G = ENEMY_3_EGYPTIAN
    test640_mission('kebet', 25, 'mission25_raids', 'mission25_on_request_cleared', test640_rows([
        [2, 4, 6, 24, EG, G, 17, [1, 1, -1, -1], 0, T.best],
        [5, 1, 6, 25, EG, G, 33, [1, 1, -1, -1], 0, T.best],
        [7, 9, 6, 26, EG, G, 55, [3, 3, -1, -1], 0, T.random],
        [10, 0, 6, 27, EG, G, 70, [2, -1, 1, 3], 0, T.random],
        [10, 6, 0, 28, EG, G, 0, [9, 9, -1, -1], 5, T.food],
        [11, 4, 6, 19, EG, G, 60, [1, 1, -1, -1], 0, T.best],
        [11, 10, 0, 20, EG, G, 60, [8, 8, -1, -1], 0, T.best]
    ]), [{ y: 11, m: 2, tag: 2015 }])
    test640_mission('itjtawy', 27, 'mission27_raids', 'mission27_on_request_cleared', test640_rows([
        [3, 3, 5, 3, EG, G, 8, [2, -1, 1, 5], 0, T.random, 2],
        [6, 2, 8, 22, EG, G, 9, [2, -1, 1, 5], 0, T.random, 2],
        [7, 7, 6, 76, EG, G, 6, [1, -1, 1, 5], 0, T.food, 2]
    ]), [{ y: 2, m: 10, tag: 2000 }, { y: 5, m: 7, tag: 2017 }, { y: 7, m: 4, tag: 2070 }])
    test640_mission('iken', 28, 'mission28_raids', 'mission28_on_request_cleared', test640_rows([
        [1, 8, 9, 18, E, HT, 32, [9, 9, -1, -1], 5, T.random],
        [2, 6, 6, 5, EG, G, 64, [4, 4, -1, -1], 0, T.best],
        [2, 8, 6, 6, B, L, 12, [3, 3, -1, -1], 0, T.random],
        [2, 8, 12, 19, E, HT, 64, [2, -1, 1, 3], 0, T.food],
        [3, 11, 12, 21, E, HT, 72, [3, 3, -1, -1], 0, T.troops],
        [5, 8, 9, 22, E, HT, 24, [9, 9, -1, -1], 6, T.food],
        [6, 7, 4, 23, E, HT, 96, [3, 3, -1, -1], 0, T.random, -1],
        [10, 7, 4, 7, E, HT, 12, [9, 9, -1, -1], 2, T.random],
        [12, 9, 6, 36, B, L, 64, [7, -1, 1, 8], 0, T.random],
        [15, 3, 6, 37, B, L, 64, [2, -1, 1, 8], 0, T.random],
        [20, 10, 4, 38, B, L, 64, [7, -1, 1, 8], 0, T.random],
        [23, 7, 6, 39, B, L, 96, [6, -1, 1, 8], 0, T.random],
        [27, 0, 4, 40, B, L, 96, [4, -1, 1, 8], 0, T.random]
    ]), [{ y: 1, m: 2, tag: 2016 }, { y: 2, m: 0, tag: 2003 }])
    test640_mission('khmun', 32, 'mission32_raids', 'mission32_on_request_cleared', test640_rows([
        [3, 1, 9, 4, E, H, 16, [1, 1, -1, -1], 0, T.best, -1],
        [5, 8, 3, 10, E, H, 32, [2, 2, -1, -1], 0, T.best, -1],
        [7, 10, 6, 18, E, H, 29, [2, 2, -1, -1], 0, T.random],
        [9, 2, 6, 19, E, H, 39, [2, 2, -1, -1], 0, T.random]
    ]), [{ y: 2, m: 1, tag: 2002 }, { y: 5, m: 3, tag: 1008 }, { y: 6, m: 11, tag: 1017, ok: true }])
    test640_mission('thinis', 23, 'mission23_raids', 'mission23_on_request_cleared', test640_rows([
        [5, 0, 5, 61, E, ENEMY_6_KUSHITE, 21, [3, -1, 3, 4], 0, T.random],
        [6, 2, 4, 19, EG, G, 38, [1, 1, -1, -1], 0, T.random, -1],
        [7, 0, 10, 20, E, ENEMY_6_KUSHITE, 24, [10, 10, -1, -1], 1, T.random, -1],
        [10, 9, 4, 38, E, ENEMY_6_KUSHITE, 29, [10, 10, -1, -1], 2, T.random],
        [11, 2, 4, 43, EG, G, 33, [9, 9, -1, -1], 4, T.random, -1],
        [14, 7, 2, 51, EG, G, 72, [9, 9, -1, -1], 5, T.random],
        [14, 10, 2, 52, E, ENEMY_6_KUSHITE, 48, [13, 13, -1, -1], 3, T.random, -1]
    ]), [{ y: 6, m: 1, tag: 2007 }, { y: 10, m: 8, tag: 1035, ok: true }, { y: 14, m: 6, tag: 2046 }])
    test640_mission('buhen', 13, 'mission13_raids', null, test640_rows([
        [6, 5, 24, 9, E, ENEMY_6_KUSHITE, 8, [1, 1, -1, -1], 0, T.best],
        [10, 6, 24, 14, E, ENEMY_6_KUSHITE, 16, [2, 2, -1, -1], 0, T.best],
        [12, 8, 24, 16, E, ENEMY_6_KUSHITE, 16, [3, 3, -1, -1], 0, T.random],
        [13, 3, 24, 17, E, ENEMY_6_KUSHITE, 24, [2, 2, -1, -1], 0, T.random],
        [15, 5, 24, 18, E, ENEMY_6_KUSHITE, 24, [1, 1, -1, -1], 0, T.vaults],
        [17, 1, 24, 19, E, ENEMY_6_KUSHITE, 32, [3, 3, -1, -1], 0, T.food],
        [18, 1, 24, 20, E, ENEMY_6_KUSHITE, 32, [2, 2, -1, -1], 0, T.best],
        [20, 8, 18, 21, E, ENEMY_6_KUSHITE, 36, [2, -1, 1, 3], 0, T.random]
    ]))
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

    test640_older_missions()

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
