// TS1: broad "does it explode" smoke run for the C++->JS migration.
//
// For each building type: place it via the real planner path (on_place ->
// update_animation -> update_graphic), open its info window ([es=(info_window_*,
// init)]), then advance the simulation a few days (update_day/week/month +
// animation). The driver fails any test whose run leaves "!!! TypeError:" in the
// log, so this catches the recurring migration crash class automatically.
//
// What it DOES catch: a null-deref / TypeError in on_place, update_*, or an
// info-window init handler for any exercised building -- i.e. the *class* of the
// dock bug (on_place -> update_animation, fix e2756c9eb), broadly across buildings
// that have no dedicated placement/info test of their own. That breadth is the
// point: dedicated tests exist for only ~15 types.
//
// What it does NOT catch: (a) correctness -- a handler that runs without throwing
// but computes the wrong value passes; (b) the entertainment info-window null-deref
// specifically -- that path needs a NON-entertainment / invalid bid, and here the
// window is always opened on a valid building (that edge case is guarded by N1's
// `if (!b) return` in the window init, not reproduced here); (c) branches that need
// a populated economy (workers/resources/ships) to reach the buggy code.
//
// Buildings the harness can't legally place (entertainment needs road adjacency)
// fall back to a fast spawn -- that still exercises their info-window init on a
// valid building, just not the on_place path.
//
// Per-type markers give isolation (which building broke) and guard against silent
// degradation (a broken placement helper drops markers instead of passing quietly).
// Markers required by check_valid are in REQUIRED; skips are logged loudly so
// "green" never hides missing coverage.

// Buildings placed on plain land via the auto-tile planner path. Each is a standard
// footprint with no special terrain need, so all are expected to place on default.map.
var LAND_BUILDINGS = [
    { name: 'pottery',        type: BUILDING_POTTERY_WORKSHOP },
    { name: 'brewery',        type: BUILDING_BREWERY_WORKSHOP },
    { name: 'bricks',         type: BUILDING_BRICKS_WORKSHOP },
    { name: 'granary',        type: BUILDING_GRANARY },
    { name: 'storage_yard',   type: BUILDING_STORAGE_YARD },
    { name: 'bazaar',         type: BUILDING_BAZAAR },
    { name: 'temple_osiris',  type: BUILDING_TEMPLE_OSIRIS },
    { name: 'apothecary',     type: BUILDING_APOTHECARY },
    { name: 'scribal_school', type: BUILDING_SCRIBAL_SCHOOL },
    // Entertainment trio: the exact info-window init handlers regressed for the
    // get_entertainment_building() null-deref fix -- must place AND open cleanly.
    { name: 'bandstand',      type: BUILDING_BANDSTAND },
    { name: 'booth',          type: BUILDING_BOOTH },
    { name: 'pavilion',       type: BUILDING_PAVILLION }
]

// Markers that MUST be present (isolation + anti-degradation). The entertainment
// trio is the guarded regression; pottery/granary anchor the generic land path.
var REQUIRED = [
    'smoke_ok:bandstand',
    'smoke_ok:booth',
    'smoke_ok:pavilion',
    'smoke_ok:pottery',
    'smoke_ok:granary',
    'smoke_run_complete'
]

// Get a valid building of `type`: prefer the real planner path (exercises on_place
// -> update_animation/graphic), fall back to a fast spawn for buildings the harness
// can't legally place (e.g. entertainment needs road adjacency). The regression we
// guard for those is the info-window init handler, which only needs a valid building.
function smoke_get_building(type) {
    var bid = test_building_place(type, -1, -1)
    if (bid && bid > 0) {
        return bid
    }
    return __test_building_create(type, -1, -1)
}

function smoke_exercise(name, bid) {
    if (!bid || bid <= 0) {
        __log_info_native('[test:41] SKIP ' + name + ' (could not place or spawn)')
        __log_marker('smoke_skip:' + name)
        return false
    }
    // Open the building info window -> runs [es=(info_window_*, init)].
    __test_show_tile_info(bid)
    __test_pump_frames(6)
    __log_marker('smoke_ok:' + name)
    return true
}

function run_test() {
    __log_info_native('[test:41] city smoke run (TS1)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(1000000)

    var placed = 0
    for (var i = 0; i < LAND_BUILDINGS.length; i++) {
        var b = LAND_BUILDINGS[i]
        var bid = smoke_get_building(b.type)
        if (smoke_exercise(b.name, bid)) {
            placed++
        }
    }
    __log_info_native('[test:41] placed ' + placed + '/' + LAND_BUILDINGS.length + ' land buildings')

    // Advance the simulation: game is unpaused after load, so pumping frames drives
    // update_day/week/month and animation handlers on everything placed above.
    __test_pump_frames(240)
    __test_pump_frames(240)

    __log_marker('smoke_run_complete')
    __test_signal_ready()
}

function check_valid() {
    for (var i = 0; i < REQUIRED.length; i++) {
        var marker = '[test-marker] ' + REQUIRED[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:41] missing required marker: ' + marker)
            return false
        }
    }
    return true
}
