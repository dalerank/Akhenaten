// EE1/EE1b/EE4: building road access resolve/apply + allowlists (v1 single tile).
// Markers:
//   [test-marker] road_access_allowlist_ok
//   [test-marker] road_access_apply_clear_ok
//   [test-marker] road_access_road_parity_ok
//   [test-marker] road_access_booth_assume_ok
//   [test-marker] road_access_feature_ok

function run_test() {
    __log_info_native('[test:517] building road access ports')
    test_ensure_city_session('data/default.map')

    if (__test_building_type_hover_road_access(BUILDING_FIREHOUSE) != 1
        || __test_building_type_ghost_road_access(BUILDING_FIREHOUSE) != 1) {
        __log_info_native('[test:517] firehouse allowlist fail')
        __test_signal_ready()
        return
    }
    // EE1b: on-road venues get ghost + assume-occupied.
    if (__test_building_type_hover_road_access(BUILDING_BOOTH) != 1
        || __test_building_type_ghost_road_access(BUILDING_BOOTH) != 1
        || __test_building_type_ghost_assume_occupied(BUILDING_BOOTH) != 1) {
        __log_info_native('[test:517] booth ghost/assume fail')
        __test_signal_ready()
        return
    }
    if (__test_building_type_ghost_road_access(BUILDING_JUGGLER_SCHOOL) != 1
        || __test_building_type_ghost_assume_occupied(BUILDING_JUGGLER_SCHOOL) != 0) {
        __log_info_native('[test:517] juggler school ghost/assume fail')
        __test_signal_ready()
        return
    }
    if (__test_building_type_hover_road_access(BUILDING_HOUSE_CRUDE_HUT) != 0
        || __test_building_type_hover_road_access(BUILDING_GRANARY) != 0
        || __test_building_type_hover_road_access(BUILDING_PLAZA) != 0) {
        __log_info_native('[test:517] house/granary/plaza exclude fail')
        __test_signal_ready()
        return
    }
    __log_marker('road_access_allowlist_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = __test_building_create(BUILDING_FIREHOUSE, cx, cy)
    if (!bid) {
        __log_info_native('[test:517] create firehouse failed')
        __test_signal_ready()
        return
    }
    var b = city.get_building(bid)
    if (!b) {
        __log_info_native('[test:517] get_building failed')
        __test_signal_ready()
        return
    }

    __test_building_road_access_set_stale(bid)
    __test_check_kingdome_access()

    // On empty default.map there is usually no adjacent road → apply must clear stale fields.
    if (__test_building_road_access_fields_cleared(bid) == 1) {
        // cleared OK
    } else if (__test_building_road_access_match_preview(bid) != 1) {
        __log_info_native('[test:517] stored vs preview mismatch after commit (no road)')
        __test_signal_ready()
        return
    } else if (!b.has_road_access) {
        __log_info_native('[test:517] apply clear left stale network/distance')
        __test_signal_ready()
        return
    }
    __log_marker('road_access_apply_clear_ok')

    // Paint adjacent road, refresh network, commit — stored must match preview.
    var ft = __building_tile(bid)
    var fx = ft.x
    var fy = ft.y
    terrain.add({ x: fx + 1, y: fy }, TERRAIN_ROAD)
    terrain.add({ x: fx + 2, y: fy }, TERRAIN_ROAD)
    terrain.add({ x: fx + 1, y: fy + 1 }, TERRAIN_ROAD)
    __test_update_road_network()
    __test_check_kingdome_access()

    if (!b.has_road_access) {
        __log_info_native('[test:517] firehouse should have road access after painting road')
        __test_signal_ready()
        return
    }
    if (__test_building_road_access_match_preview(bid) != 1) {
        __log_info_native('[test:517] stored vs preview mismatch after road paint')
        __test_signal_ready()
        return
    }
    if (__test_building_road_access_tile(bid) < 0) {
        __log_info_native('[test:517] road_access tile invalid after paint')
        __test_signal_ready()
        return
    }
    __log_marker('road_access_road_parity_ok')

    // EE1b booth: place on venue roads; assume-preview must match stored after commit.
    var bx = cx + 10
    var by = cy - 14
    // Booth orientation 0: footprint .R/RR plus exterior stem (1,0) — see BOOTH_ROAD_POSITIONS / test 144.
    terrain.add({ x: bx + 0, y: by + 1 }, TERRAIN_ROAD)
    terrain.add({ x: bx + 1, y: by + 0 }, TERRAIN_ROAD)
    terrain.add({ x: bx + 1, y: by + 1 }, TERRAIN_ROAD)
    terrain.add({ x: bx + 1, y: by + 2 }, TERRAIN_ROAD)
    terrain.add({ x: bx + 2, y: by + 1 }, TERRAIN_ROAD)
    __test_update_road_network()

    var booth_id = test_building_place(BUILDING_BOOTH, bx, by)
    if (!booth_id || booth_id <= 0) {
        __log_info_native('[test:517] booth place failed (need venue roads; no force-create)')
        __test_signal_ready()
        return
    }
    __test_check_kingdome_access()
    var booth = city.get_building(booth_id)
    if (!booth) {
        __log_info_native('[test:517] get booth failed')
        __test_signal_ready()
        return
    }
    if (!booth.has_road_access) {
        __log_info_native('[test:517] booth should have road access after place')
        __test_signal_ready()
        return
    }
    if (__test_building_road_access_match_preview(booth_id) != 1) {
        __log_info_native('[test:517] booth stored vs assume-preview mismatch')
        __test_signal_ready()
        return
    }
    __log_marker('road_access_booth_assume_ok')

    game_features.set('gameui_show_building_road_access', true)
    if (!game_features.get('gameui_show_building_road_access')) {
        __log_info_native('[test:517] feature flag missing')
        __test_signal_ready()
        return
    }
    __log_marker('road_access_feature_ok')

    __log_info_native('[test:517] ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'road_access_allowlist_ok',
        'road_access_apply_clear_ok',
        'road_access_road_parity_ok',
        'road_access_booth_assume_ok',
        'road_access_feature_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:517] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
