// V1: static validator for every enemy nation config in enemies.js.
//
// Two invariants, checked per nation (13 total):
//   1. percentage_type1 + type2 + type3 == 100  (a contingent share that goes
//      nowhere means part of the army never spawns — this was bug F1, where
//      canaanite/kushite/nubian/phoenician/seapeople had percentage_type3 > 0
//      while figure_types[2] == FIGURE_NONE).
//   2. every non-NONE figure_types[i] resolves to a registered enemy class
//      (__test_enemy_figure_registered). An unregistered type falls through to
//      figure_impl (dcast_enemy == null) and assert(false) in debug — this was
//      bug F2 (enemy chariots without a FIGURE_METAINFO class).
//   3. a nonzero percentage_type[i] must have a real (non-NONE) figure_types[i]
//      (the F1 shape check, stated directly).
//
// Reads the config objects straight from the JS globals defined in enemies.js,
// so it fails fast at CI time instead of crashing inside a specific mission's
// invasion. Related: tests/39 (chariot registration), REMAKE_TODO.md V1.
//
// Markers:
//   [test-marker] enemy_config_control_ok
//   [test-marker] enemy_config_all_valid

var ENEMY_NATIONS = [
    { name: 'barbarian',  cfg: enemy_barbarian },
    { name: 'assyrian',   cfg: enemy_assyrian },
    { name: 'canaanite',  cfg: enemy_canaanite },
    { name: 'egyptian',   cfg: enemy_egyptian },
    { name: 'hittite',    cfg: enemy_hittite },
    { name: 'hyksos',     cfg: enemy_hyksos },
    { name: 'kushite',    cfg: enemy_kushite },
    { name: 'libian',     cfg: enemy_libian },
    { name: 'nubian',     cfg: enemy_nubian },
    { name: 'persian',    cfg: enemy_persian },
    { name: 'phoenician', cfg: enemy_phoenician },
    { name: 'roman',      cfg: enemy_roman },
    { name: 'seapeople',  cfg: enemy_seapeople }
]

function fail(msg) {
    __log_info_native('[test:42] ' + msg)
    __test_signal_ready()
}

function validate_nation(entry) {
    var cfg = entry.cfg
    if (!cfg) {
        __log_info_native('[test:42] missing enemy config: ' + entry.name)
        return false
    }

    var pct = [cfg.percentage_type1, cfg.percentage_type2, cfg.percentage_type3]
    var sum = pct[0] + pct[1] + pct[2]
    if (sum !== 100) {
        __log_info_native('[test:42] ' + entry.name + ': percentages sum to ' + sum + ', expected 100')
        return false
    }

    var types = cfg.figure_types
    if (!types || types.length !== 3) {
        __log_info_native('[test:42] ' + entry.name + ': figure_types must have 3 entries')
        return false
    }

    for (var i = 0; i < 3; i++) {
        var is_none = (types[i] === FIGURE_NONE)

        // F1: a contingent with a share must have a real figure type to spawn.
        if (pct[i] > 0 && is_none) {
            __log_info_native('[test:42] ' + entry.name + ': percentage_type' + (i + 1) +
                              ' = ' + pct[i] + ' but figure_types[' + i + '] is FIGURE_NONE')
            return false
        }

        // F2: any declared figure type must resolve to a registered enemy class.
        if (!is_none && !__test_enemy_figure_registered(types[i])) {
            __log_info_native('[test:42] ' + entry.name + ': figure_types[' + i + '] = ' +
                              types[i] + ' is not a registered enemy class')
            return false
        }
    }

    return true
}

function run_test() {
    __log_info_native('[test:42] enemy config validation (V1)')
    test_ensure_city_session('data/default.map')

    // Positive control: a long-registered enemy class must report true, so a
    // failure below is a real config gap, not a broken harness.
    if (!__test_enemy_figure_registered(FIGURE_ENEMY_BARBARIAN_SWORD)) {
        fail('control failed: FIGURE_ENEMY_BARBARIAN_SWORD not registered')
        return
    }
    __log_marker('enemy_config_control_ok')

    for (var i = 0; i < ENEMY_NATIONS.length; i++) {
        if (!validate_nation(ENEMY_NATIONS[i])) {
            __test_signal_ready()
            return
        }
    }
    __log_marker('enemy_config_all_valid')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['enemy_config_control_ok', 'enemy_config_all_valid']
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:42] missing marker: ' + marker)
            return false
        }
    }
    return true
}
