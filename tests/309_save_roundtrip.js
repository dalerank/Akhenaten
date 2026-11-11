// Save fidelity:
// 1) a running city written as .svx, loaded back and written again must give the same chunks;
// 2) every original Save/<player>/*.sav of the Pharaoh install, written back through the .sav schema
//    right after loading, must give the file's own bytes. Without a Save folder this part is skipped.
// 3) the city loaded from each of those files, through our own .svx round trip, must not change.
// Differing chunks are logged as "[roundtrip] ... diff <chunk>" with the first differing offsets.
// Chunks already known to differ in 2) and 3) are listed below: a new chunk fails the test, a listed
// chunk that no file shows any more is logged so the list can shrink.
// Markers:
//   [test-marker] save_roundtrip_ok
//   [test-marker] og_save_corpus_ok:<n> | og_save_corpus_skipped

var __t309_ticks = 2000

// OG bytes we do not write back yet: bind____skip fields, chunks rebuilt on load, file_version.
var __t309_known_og = [
    'bookmarks', 'building_burning_list_info', 'building_count_industry', 'building_extra_highest_id',
    'building_extra_highest_id_ever', 'building_list_large', 'buildings', 'city_data', 'city_data_extra',
    'city_sounds', 'empire_cities', 'empire_map_objects', 'empire_map_routes', 'figure_sequence', 'figures',
    'file_version', 'formations', 'formations_info', 'junk10d', 'junk14', 'junk16', 'junk17', 'junk18',
    'junk19', 'junk7a', 'junk8', 'scenario_events', 'scenario_events_extra', 'scenario_info',
    'scenario_map_name', 'tutorial_flags_struct'
]

// A city fresh from an OG file settles on its first load: house image_key is looked up from tile images
// that are only refreshed after post_load, and the tile caches are rebuilt.
var __t309_known_og_svx = ['bitfields_grid', 'buildings', 'edge_grid', 'image_grid']

// "|<path>=<chunks>|svx <path>=<chunks>..." -> chunks outside the known lists; marks the known ones seen.
function t309_unknown_chunks(diffs, seen) {
    var unknown = []
    var entries = diffs.split('|')
    for (var i = 0; i < entries.length; i++) {
        var eq = entries[i].lastIndexOf('=')
        if (eq < 0) {
            continue
        }
        var is_svx = entries[i].indexOf('svx ') == 0
        var known = is_svx ? __t309_known_og_svx : __t309_known_og
        var chunks = entries[i].substring(eq + 1).split(',')
        for (var c = 0; c < chunks.length; c++) {
            var key = (is_svx ? 'svx:' : '') + chunks[c]
            if (known.indexOf(chunks[c]) < 0) {
                unknown.push(key + ' in ' + entries[i].substring(0, eq))
            } else {
                seen[key] = true
            }
        }
    }
    return unknown
}

function t309_report_fixed(seen) {
    for (var i = 0; i < __t309_known_og.length; i++) {
        if (!seen[__t309_known_og[i]]) {
            __log_info_native('[test:309] known OG diff no longer seen, remove from list: ' + __t309_known_og[i])
        }
    }
    for (var i = 0; i < __t309_known_og_svx.length; i++) {
        if (!seen['svx:' + __t309_known_og_svx[i]]) {
            __log_info_native('[test:309] known OG->svx diff no longer seen, remove from list: ' + __t309_known_og_svx[i])
        }
    }
}

function t309_fail(msg) {
    __log_info_native('[test:309] FAIL: ' + msg)
}

function t309_build_city() {
    var types = [BUILDING_STORAGE_YARD, BUILDING_GRANARY, BUILDING_BAZAAR, BUILDING_FIREHOUSE, BUILDING_GRAIN_FARM]
    for (var i = 0; i < types.length; i++) {
        if (!test_building_place(types[i], -1, -1)) {
            __log_info_native('[test:309] place failed type=' + types[i])
        }
    }
}

function run_test() {
    __log_info_native('[test:309] save roundtrip')

    __test_crt_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        t309_fail('map load')
        __test_signal_ready()
        return
    }
    __test_set_treasury(100000)
    t309_build_city()
    __test_run_ticks(__t309_ticks)
    __test_process_events()

    var diff = __test_save_roundtrip('test_309_roundtrip.svx')
    if (diff === '') {
        __log_marker('save_roundtrip_ok')
    } else {
        t309_fail('svx roundtrip: ' + diff)
    }

    var corpus = __test_og_save_corpus()
    if (corpus == 'skip') {
        __log_marker('og_save_corpus_skipped')
    } else {
        var sep = corpus.indexOf(';')
        var n = corpus.substring(0, sep)
        var seen = {}
        var unknown = t309_unknown_chunks(corpus.substring(sep + 1), seen)
        if (unknown.length == 0) {
            t309_report_fixed(seen)
            __log_marker('og_save_corpus_ok:' + n)
        } else {
            for (var i = 0; i < unknown.length; i++) {
                t309_fail('new OG diff: ' + unknown[i])
            }
        }
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('save_roundtrip_ok')) {
        return false
    }
    return __test_find_inlog('og_save_corpus_ok') || __test_find_inlog('og_save_corpus_skipped')
}
