// Carpenter terrain on the way to a monument, as in the original (FIGURE_ACTION_CARPENTER_GO_TO_SITE):
// PREFER_ROADS by default, ROADS_OR_MONUMENT (TERRAIN_USAGE_ANY here) for the sun temple, caesareum,
// library, lighthouse and mausoleum. A missing config key once reset the default to ANY.

var __test295_ok = false

function check_terrain(type, want, label) {
    var got = __building_static_guild_worker_terrain(type)
    if (got != want) {
        __log_marker('carpenter_terrain_fail:' + label + ':want=' + want + ':got=' + got)
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:295] carpenter terrain og')

    var prefer_roads = [
        [BUILDING_SMALL_MUDBRICK_PYRAMID, 'small_mudbrick_pyramid'],
        [BUILDING_SMALL_STEPPED_PYRAMID, 'small_stepped_pyramid'],
        [BUILDING_SMALL_MASTABA, 'small_mastaba'],
        [BUILDING_SPHINX, 'sphinx']
    ]
    var roads_or_monument = [
        [BUILDING_SUN_TEMPLE, 'sun_temple'],
        [BUILDING_CAESAREUM, 'caesareum'],
        [BUILDING_ALEXANDRIA_LIBRARY, 'alexandria_library'],
        [BUILDING_PHAROS_LIGHTHOUSE, 'pharos_lighthouse'],
        [BUILDING_MAUSOLEUM, 'mausoleum']
    ]

    var ok = true
    for (var i = 0; i < prefer_roads.length; i++) {
        ok = check_terrain(prefer_roads[i][0], TERRAIN_USAGE_PREFER_ROADS, prefer_roads[i][1]) && ok
    }
    for (var j = 0; j < roads_or_monument.length; j++) {
        ok = check_terrain(roads_or_monument[j][0], TERRAIN_USAGE_ANY, roads_or_monument[j][1]) && ok
    }

    if (ok) {
        __log_marker('carpenter_terrain_ok')
        __test295_ok = true
    }
    __test_signal_ready()
}

function check_valid() {
    return __test295_ok && __test_find_inlog('[test-marker] carpenter_terrain_ok')
}
