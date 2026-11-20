// Original Pharaoh .sav through the converter (src/io/og_save):
// 1) the reader on a synthetic v160 image: values read back, truncated / wrong version / wrong schema /
//    trailing bytes are refused (runs without Pharaoh data);
// 2) every OG save of tests/fixtures/og_saves and of the install's Save/<player>/ loads on top of its mission;
//    the loaded city matches what the reader saw in the OG records (treasury, population, buildings in use),
//    figures are not carried over yet, and the converted city survives an .svx save -> load -> save round trip
//    unchanged; the v147 fixture (a pre-Cleopatra file) is refused;
// 3) the Rostja fixture has the values below (anchors taken from the reader, so a reader change shows up).
// Markers:
//   [test-marker] og_reader_synthetic_ok
//   [test-marker] og_save_corpus_ok:<n>

var __t387_anchor = {
    file: 'og_saves/m018_rostja_v160.sav',
    summary: '160,18490,4100,679,341',
}

function t387_fail(msg) {
    __log_info_native('[test:387] FAIL: ' + msg)
}

function t387_fields(summary) {
    var parts = summary.split(',')
    return {
        treasury: parseInt(parts[1]),
        population: parseInt(parts[2]),
        buildings: parseInt(parts[3]),
        figures: parseInt(parts[4]),
    }
}

function t387_check_file(path) {
    var og = __test_og_read_summary(path)
    var refused = og.indexOf('error:save version') == 0
    if (path.indexOf('/og_saves/v147_') >= 0 && !refused) {
        t387_fail(path + ' a v147 save was read: ' + og)
        return false
    }
    if (refused) {
        __log_info_native('[test:387] skip ' + path + ': ' + og)
        return true
    }
    if (og.indexOf('error:') == 0) {
        t387_fail(path + ' reader: ' + og)
        return false
    }
    if (!__test_og_load(path)) {
        t387_fail(path + ' load failed')
        return false
    }
    var want = t387_fields(og)
    var got = t387_fields(__test_city_og_summary())
    __log_info_native('[test:387] ' + path + ' og=' + og + ' city=' + __test_city_og_summary())
    var ok = true
    if (got.treasury != want.treasury) {
        t387_fail(path + ' treasury ' + got.treasury + ' want ' + want.treasury)
        ok = false
    }
    if (got.population != want.population) {
        t387_fail(path + ' population ' + got.population + ' want ' + want.population)
        ok = false
    }
    if (got.buildings != want.buildings) {
        t387_fail(path + ' buildings in use ' + got.buildings + ' want ' + want.buildings)
        ok = false
    }
    if (got.figures != 0) {
        t387_fail(path + ' figures ' + got.figures + ', none are converted yet')
        ok = false
    }
    if (path.indexOf(__t387_anchor.file) >= 0 && __t387_anchor.summary !== null && og != __t387_anchor.summary) {
        t387_fail(path + ' reader summary ' + og + ' want ' + __t387_anchor.summary)
        ok = false
    }

    // The first .svx load settles a converted city (shore bits on the map edge, a few river image cells), as it
    // does for a .map start; from then on the city must survive a save -> load -> save unchanged.
    var settle = __test_save_roundtrip('test_490_og_roundtrip.svx')
    if (settle !== '') {
        __log_info_native('[test:387] ' + path + ' first svx load settles: ' + settle)
    }
    var diff = __test_save_roundtrip('test_490_og_roundtrip.svx')
    if (diff !== '') {
        t387_fail(path + ' svx roundtrip: ' + diff)
        ok = false
    }
    return ok
}

function run_test() {
    var synthetic = __test_og_reader_synthetic()
    if (synthetic === '') {
        __log_marker('og_reader_synthetic_ok')
    } else {
        t387_fail('synthetic reader: ' + synthetic)
    }

    var list = __test_og_save_files()
    if (list === '') {
        t387_fail('no OG saves found, tests/fixtures/og_saves is missing')
    } else {
        var files = list.split('|')
        var ok = true
        for (var i = 0; i < files.length; i++) {
            ok = t387_check_file(files[i]) && ok
        }
        if (ok) {
            __log_marker('og_save_corpus_ok:' + files.length)
        }
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('og_reader_synthetic_ok')) {
        return false
    }
    return __test_find_inlog('og_save_corpus_ok')
}
