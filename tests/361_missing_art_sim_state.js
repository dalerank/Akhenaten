// Simulation state must not depend on whether Pharaoh art is loaded. Rocks, dunes, gardens and plazas
// cluster tiles by "no image assigned yet" (OG: map_grids.images[offset] != 0), and a new house picks
// its variant key; without art a missing image id used to become 0 after adding an offset.
// Run without data (empty dir as the last positional arg) and with the Steam data dir: the hash of
// terrain, tile properties and "has image" plus the house keys must match the values below in both.

var __test361_ok = false

// Taken from a run with full Pharaoh + Cleopatra data; a run without data must give the same.
var TEST361_EXPECTED_HASH = 778355258
var TEST361_EXPECTED_KEYS = '_1,_1,_2,_2'

function test361_fail(msg) {
    __log_info_native('[test:361] FAIL: ' + msg)
    __test_signal_ready()
}

function test361_clear(x0, y0, x1, y1) {
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            var tile = { x: x, y: y }
            terrain.remove(tile, TERRAIN_WATER | TERRAIN_CANAL | TERRAIN_ROAD | TERRAIN_ROCK | TERRAIN_TREE
                | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_FLOODPLAIN | TERRAIN_RUBBLE | TERRAIN_GARDEN
                | TERRAIN_MEADOW | TERRAIN_MARSHLAND | TERRAIN_DUNE | TERRAIN_ORE | TERRAIN_ELEVATION
                | TERRAIN_ACCESS_RAMP)
            __map_image_set(tile, 0)
        }
    }
}

function test361_paint(x0, y0, w, h, mask) {
    for (var y = y0; y < y0 + h; y++) {
        for (var x = x0; x < x0 + w; x++) {
            terrain.add({ x: x, y: y }, mask)
        }
    }
}

function run_test() {
    __log_info_native('[test:361] missing art keeps sim state')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var x0 = cx - 12
    var y0 = cy - 12
    var x1 = cx + 12
    var y1 = cy + 12
    test361_clear(x0, y0, x1, y1)

    // Irregular blobs so 3x3, 2x2 and single sprites all get picked.
    test361_paint(x0, y0, 5, 4, TERRAIN_ROCK)
    test361_paint(x0 + 5, y0 + 1, 1, 2, TERRAIN_ROCK)
    test361_paint(x0 + 7, y0, 4, 3, TERRAIN_ORE | TERRAIN_ROCK)
    test361_paint(x0 + 12, y0, 6, 5, TERRAIN_DUNE)
    test361_paint(x0, y0 + 6, 5, 5, TERRAIN_GARDEN)
    test361_paint(x0 + 5, y0 + 6, 2, 1, TERRAIN_GARDEN)
    __test_tiles_update_all_rocks()
    __test_tiles_update_all_dunes()
    __test_gardens_update_all()

    for (var py = y0 + 13; py < y0 + 17; py++) {
        for (var px = x0; px < x0 + 5; px++) {
            terrain.add({ x: px, y: py }, TERRAIN_ROAD)
            __test_plaza_mark_tile(px, py)
        }
    }
    __test_plaza_update_all()

    var hash = __test_map_sim_state_hash(x0, y0, x1, y1)

    var keys = []
    for (var i = 0; i < 4; i++) {
        var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, x0 + 14 + i * 2, y0 + 14)
        var changed = bid && __test_house_change_to(bid, BUILDING_HOUSE_STURDY_HUT)
        keys.push(changed ? __test_house_image_key(bid) : '-')
    }
    var keys_str = keys.join(',')
    __log_info_native('[test:361] art=' + __test_pak_loaded('SprMain') + ' hash=' + hash + ' keys=' + keys_str)

    if (hash !== TEST361_EXPECTED_HASH) {
        return test361_fail('sim state hash ' + hash + ' != ' + TEST361_EXPECTED_HASH)
    }
    if (keys_str !== TEST361_EXPECTED_KEYS) {
        return test361_fail('house keys ' + keys_str + ' != ' + TEST361_EXPECTED_KEYS)
    }
    __log_marker('test361_state_ok')

    __test361_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test361_ok && __test_find_inlog('[test-marker] test361_state_ok')
}
