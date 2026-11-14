// OG construction_warnings.c, material part: a workshop with nothing to work on gets "needs X" and one hint
// (build the producer / set up a trade route / instruct the Overseer); the product in the yards is enough;
// two-input buildings name both inputs; service buildings point at the maker or the import of the product.
// The expected hint is worked out from the map's trade the same way OG does.
// Markers:
//   [test-marker] t541_weaver_ok
//   [test-marker] t541_product_stock_ok
//   [test-marker] t541_carpenters_ok
//   [test-marker] t541_brickworks_ok
//   [test-marker] t541_mortuary_ok
//   [test-marker] t541_senet_ok
//   [test-marker] t541_library_ok

var __t541_ok = false

var T541_ROUTE = '#setup_trade_route_to_import'
var T541_OVERSEER = '#overseer_of_commerce_to_import'
var T541_KEYS = ['#city_needs_more_workers', '#needs_road_access', '#no_troops_for_defense',
    '#building_needs_flax', '#build_flax_farm', '#building_needs_wood', '#build_wood_cutter',
    '#building_needs_clay_and_straw', '#building_needs_clay', '#building_needs_straw', '#build_clay_pit',
    '#build_grain_farm', '#import_clay_trade_route', '#import_clay_overseer', '#import_straw_trade_route',
    '#import_straw_overseer',
    '#building_needs_linen', '#build_weaver', '#build_weaver_or_import_linen', '#build_weaver_or_import_linen_route',
    '#import_flax_trade_route', '#import_flax_overseer',
    '#building_needs_beer', '#build_brewery', '#build_brewery_or_import_beer', '#build_brewery_or_import_beer_route',
    '#import_barley_trade_route', '#import_barley_overseer',
    '#needs_papyrus', '#build_papyrus_maker', '#build_papyrus_maker_or_import', '#build_papyrus_maker_or_import_route',
    '#import_reeds_trade_route', '#import_reeds_overseer',
    T541_ROUTE, T541_OVERSEER]

function t541_material_keys(shown) {
    var out = []
    for (var i = 0; i < shown.length; i++) {
        if (shown[i] != '#city_needs_more_workers' && shown[i] != '#needs_road_access') {
            out.push(shown[i])
        }
    }
    return out.sort().join(',')
}

function t541_shown() {
    var shown = []
    for (var i = 0; i < T541_KEYS.length; i++) {
        var n = __test_construction_warning_count(T541_KEYS[i])
        for (var k = 0; k < n; k++) {
            shown.push(T541_KEYS[i])
        }
    }
    return shown
}

function t541_imported(r) {
    return r.trade_status == TRADE_STATUS_IMPORT || r.trade_status == TRADE_STATUS_IMPORT_AS_NEEDED
}

function t541_hint_import(res, no_route, not_imported) {
    var r = city_resource_view(res)
    if (!r.can_import) {
        return [no_route]
    }
    return t541_imported(r) ? [] : [not_imported]
}

function t541_hint_raw(produce, build, res, no_route, not_imported) {
    if (produce && city_resource_view(produce).can_produce) {
        return [build]
    }
    return t541_hint_import(res, no_route, not_imported)
}

// cw.c:447-558 for a product without stock and without a raw producer.
function t541_finished_good(product, raw, build, no_route, not_imported, import_only, raw_no_route, raw_not_imported) {
    var p = city_resource_view(product)
    var w = city_resource_view(raw)
    if (w.count_total_industry > 0) {
        return []
    }
    if ((w.can_produce || w.could_import) && p.count_total_industry == 0) {
        if (!p.could_import) {
            return [build]
        }
        if (!p.can_import) {
            return [no_route]
        }
        var imported = import_only ? p.trade_status == TRADE_STATUS_IMPORT : t541_imported(p)
        return imported ? [] : [not_imported]
    }
    if (w.could_import && p.count_total_industry != 0) {
        return t541_hint_import(raw, raw_no_route, raw_not_imported)
    }
    return p.could_import ? t541_hint_import(product, T541_ROUTE, T541_OVERSEER) : []
}

function t541_check(label, type, expected) {
    __test_construction_warnings_reset()
    var bid = test_building_place(type, -1, -1)
    __test_process_events()
    if (!bid) {
        __log_info_native('[test:541] FAIL ' + label + ': placement')
        return false
    }
    var shown = t541_material_keys(t541_shown())
    var want = expected.slice().sort().join(',')
    if (shown != want) {
        __log_info_native('[test:541] FAIL ' + label + ': shown [' + shown + '] want [' + want + ']')
        return false
    }
    __log_marker('t541_' + label + '_ok')
    return true
}

function t541_run() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000000)

    var weaver = ['#building_needs_flax'].concat(
        t541_hint_raw(RESOURCE_FLAX, '#build_flax_farm', RESOURCE_FLAX, T541_ROUTE, T541_OVERSEER))
    if (!t541_check('weaver', BUILDING_WEAVER_WORKSHOP, weaver)) {
        return false
    }

    __test_city_set_yards_stored(RESOURCE_LINEN, 100)
    if (!t541_check('product_stock', BUILDING_WEAVER_WORKSHOP, [])) {
        return false
    }
    __test_city_set_yards_stored(RESOURCE_LINEN, 0)

    var wood = ['#building_needs_wood'].concat(
        t541_hint_raw(RESOURCE_TIMBER, '#build_wood_cutter', RESOURCE_TIMBER, T541_ROUTE, T541_OVERSEER))
    if (!t541_check('carpenters', BUILDING_CARPENTERS_GUILD, wood)) {
        return false
    }

    var bricks = ['#building_needs_clay_and_straw']
        .concat(t541_hint_raw(RESOURCE_CLAY, '#build_clay_pit', RESOURCE_CLAY, '#import_clay_trade_route',
            '#import_clay_overseer'))
        .concat(t541_hint_raw(RESOURCE_GRAIN, '#build_grain_farm', RESOURCE_STRAW, '#import_straw_trade_route',
            '#import_straw_overseer'))
    if (!t541_check('brickworks', BUILDING_BRICKS_WORKSHOP, bricks)) {
        return false
    }

    var linen = ['#building_needs_linen'].concat(t541_finished_good(RESOURCE_LINEN,
        RESOURCE_FLAX, '#build_weaver', '#build_weaver_or_import_linen_route', '#build_weaver_or_import_linen', false,
        '#import_flax_trade_route', '#import_flax_overseer'))
    if (!t541_check('mortuary', BUILDING_MORTUARY, linen)) {
        return false
    }

    var beer = ['#building_needs_beer'].concat(t541_finished_good(RESOURCE_BEER, RESOURCE_BARLEY, '#build_brewery',
        '#build_brewery_or_import_beer_route', '#build_brewery_or_import_beer', false,
        '#import_barley_trade_route', '#import_barley_overseer'))
    if (!t541_check('senet', BUILDING_SENET_HOUSE, beer)) {
        return false
    }

    var papyrus = ['#needs_papyrus'].concat(t541_finished_good(RESOURCE_PAPYRUS, RESOURCE_REEDS,
        '#build_papyrus_maker', '#build_papyrus_maker_or_import_route', '#build_papyrus_maker_or_import', true,
        '#import_reeds_trade_route', '#import_reeds_overseer'))
    if (!t541_check('library', BUILDING_LIBRARY, papyrus)) {
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:541] construction warnings, materials')
    __t541_ok = t541_run()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['weaver', 'product_stock', 'carpenters', 'brickworks', 'mortuary', 'senet', 'library']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] t541_' + markers[i] + '_ok')) {
            __log_info_native('[test:541] missing marker: t541_' + markers[i])
            return false
        }
    }
    return __t541_ok
}
