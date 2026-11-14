// Each temple's priest runs on its god's config (figure_priest_osiris .. _bast): god sounds, overlay,
// walk animation and setup_phrase handler, keeps it after save -> load, and covers houses of its god only.
// Markers:
//   [test-marker] priest_god_configs_ok
//   [test-marker] priest_god_configs_roundtrip_ok

var __test712_ok = false
var __test712_roundtrip_ok = false

var __test712_gods = [
    { name: 'osiris', temple: BUILDING_TEMPLE_OSIRIS, overlay: OVERLAY_RELIGION_OSIRIS, spawn: building_temple_osiris_spawn_figure },
    { name: 'ra', temple: BUILDING_TEMPLE_RA, overlay: OVERLAY_RELIGION_RA, spawn: building_temple_ra_spawn_figure },
    { name: 'ptah', temple: BUILDING_TEMPLE_PTAH, overlay: OVERLAY_RELIGION_PTAH, spawn: building_temple_ptah_spawn_figure },
    { name: 'seth', temple: BUILDING_TEMPLE_SETH, overlay: OVERLAY_RELIGION_SETH, spawn: building_temple_seth_spawn_figure },
    { name: 'bast', temple: BUILDING_TEMPLE_BAST, overlay: OVERLAY_RELIGION_BAST, spawn: building_temple_bast_spawn_figure }
]

function test712_fail(msg) {
    __log_info_native('[test:712] FAIL: ' + msg)
}

function test712_place_temple(g, x, y) {
    for (var tries = 0; tries < 8; tries++) {
        var py = y + tries * 7
        var bid = test_building_place(g.temple, x, py)
        if (!bid) {
            continue
        }
        var zt = __building_tile(bid)
        for (var dx = 0; dx < 5; dx++) {
            terrain.add({ x: zt.x + dx, y: zt.y + 3 }, TERRAIN_ROAD)
        }
        return bid
    }
    return 0
}

function test712_spawn_priest(g) {
    var b = city.get_building(g.bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    for (var day = 0; day < 10; day++) {
        g.spawn({ bid: g.bid })
        var fid = __building_get_figure_id(g.bid, 0)
        if (fid) {
            return fid
        }
    }
    return 0
}

function test712_check_priest(g, when) {
    var f = city.get_figure(g.fid)
    if (!f || !f.valid || f.type != FIGURE_PRIEST) {
        test712_fail(when + ' ' + g.name + ': priest ' + g.fid + ' missing')
        return false
    }
    if (f.home_building_id != g.bid) {
        test712_fail(when + ' ' + g.name + ': home ' + f.home_building_id + ' want ' + g.bid)
        return false
    }

    var want_sound = 'priest_' + g.name + '_e01.wav'
    var sound = f.sound_path('god_love_festival')
    if (sound != want_sound) {
        test712_fail(when + ' ' + g.name + ': sound ' + sound + ' want ' + want_sound)
        return false
    }
    if (f.overlay != g.overlay) {
        test712_fail(when + ' ' + g.name + ': overlay ' + f.overlay + ' want ' + g.overlay)
        return false
    }

    f.setup_phrase()
    var phrase_sound = '' + f.phrase_sound
    if (phrase_sound.indexOf('priest_' + g.name + '_') != 0) {
        test712_fail(when + ' ' + g.name + ': setup_phrase gave ' + f.phrase_key + ' / ' + phrase_sound)
        return false
    }
    return true
}

function test712_check_coverage(g) {
    var t = __figure_get_tile(g.fid)
    var hut = 0
    var offsets = [[0, 1], [0, -1], [1, 0], [-1, 0], [1, 1], [-1, -1], [1, -1], [-1, 1]]
    for (var i = 0; i < offsets.length && !hut; i++) {
        hut = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, t.x + offsets[i][0], t.y + offsets[i][1])
    }
    if (!hut || __test_house_set_population(hut, 10) < 1) {
        test712_fail(g.name + ': house next to the priest failed')
        return false
    }

    __test_figure_provide_service(g.fid)
    var house = city.get_house(hut)
    for (var i = 0; i < __test712_gods.length; i++) {
        var other = __test712_gods[i]
        var cov = house['temple_' + other.name]
        var want = (other.name == g.name) ? 96 : 0
        if (cov != want) {
            test712_fail(g.name + ' priest: house temple_' + other.name + ' = ' + cov + ' want ' + want)
            return false
        }
    }
    return true
}

function test712_check_walk(g, when) {
    var key = __figure_get_anim_key(g.fid)
    if (key != 'walk') {
        test712_fail(when + ' ' + g.name + ': anim key ' + key)
        return false
    }
    return true
}

function test712_run() {
    var cx = ((__scenario_map.width / 2) | 0) - 18
    var cy = ((__scenario_map.height / 2) | 0) - 10

    for (var i = 0; i < __test712_gods.length; i++) {
        var g = __test712_gods[i]
        g.bid = test712_place_temple(g, cx + i * 8, cy)
        if (!g.bid) {
            test712_fail(g.name + ': temple not placed')
            return
        }
        __test_building_set_workers(g.bid, 8)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    for (var i = 0; i < __test712_gods.length; i++) {
        var g = __test712_gods[i]
        g.fid = test712_spawn_priest(g)
        if (!g.fid) {
            test712_fail(g.name + ': no priest spawned')
            return
        }
    }

    for (var i = 0; i < __test712_gods.length; i++) {
        var g = __test712_gods[i]
        if (!test712_check_priest(g, 'spawned')) {
            return
        }
    }

    __test_run_ticks(5)
    for (var i = 0; i < __test712_gods.length; i++) {
        if (!test712_check_walk(__test712_gods[i], 'spawned')) {
            return
        }
    }
    __test712_ok = true
    __log_marker('priest_god_configs_ok')

    var diff = __test_save_roundtrip('test_712_priests.svx')
    if (diff !== '') {
        test712_fail('save roundtrip ' + diff)
        return
    }

    __test_run_ticks(5)
    for (var i = 0; i < __test712_gods.length; i++) {
        var g = __test712_gods[i]
        if (!test712_check_priest(g, 'loaded') || !test712_check_walk(g, 'loaded') || !test712_check_coverage(g)) {
            return
        }
    }
    __test712_roundtrip_ok = true
    __log_marker('priest_god_configs_roundtrip_ok')
}

function run_test() {
    __log_info_native('[test:712] priest per-god configs')
    if (!test_reload_city_session('data/default.map')) {
        test712_fail('map load')
        __test_signal_ready()
        return
    }
    __test_set_treasury(100000)

    test712_run()

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __test712_ok
        && __test712_roundtrip_ok
        && __test_find_inlog('[test-marker] priest_god_configs_ok')
        && __test_find_inlog('[test-marker] priest_god_configs_roundtrip_ok')
}
