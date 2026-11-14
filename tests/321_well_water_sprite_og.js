// Well water sprite, OG building_animation_offset + map_houses_water_in_radius (#716 #717):
// frame 1 (water in the basin) is drawn while some house within 2 tiles has no water_supply,
// even after the lots fill up; no houses or all houses supplied -> the plain well.
// With art, base_work/fancy_work pos must land where OG draw_sized_anim puts frame 1:
// base sprite offset x, base sprite offset y - base height + 30.

var __test321_ok = false

function test321_fail(msg) {
    __log_info_native('[test:321] FAIL: ' + msg)
    __test_signal_ready()
}

function test321_day(bid) {
    __test_building_update_day(bid)
    return city.get_well(bid)
}

function test321_pos_matches_og(anim_key, base_offset) {
    var base = get_image({ pack: PACK_GENERAL, id: 23, offset: base_offset })
    if (!base || base.height <= 0) {
        return 'skip'
    }
    var a = building_well.animations[anim_key]
    var px = (a.pos.x !== undefined) ? a.pos.x : a.pos[0]
    var py = (a.pos.y !== undefined) ? a.pos.y : a.pos[1]
    var ox = base.animation_offset_x
    var oy = base.animation_offset_y - base.height + 30
    if (px != ox || py != oy) {
        return anim_key + ' pos=' + px + ',' + py + ' og=' + ox + ',' + oy
    }
    return 'ok'
}

function run_test() {
    __log_info_native('[test:321] well water sprite follows houses without water')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx, y: cy }, TERRAIN_GROUNDWATER)
    var bid = test_building_place(BUILDING_WELL, cx, cy)
    if (!bid) {
        return test321_fail('well place failed')
    }

    var well = test321_day(bid)
    if (well.play_animation || __test_building_anim_key(bid) != '') {
        return test321_fail('no houses: water sprite shown, key=' + __test_building_anim_key(bid))
    }
    __log_marker('test321_no_houses_plain')

    var h_out = __test_building_create(BUILDING_HOUSE_VACANT_LOT, cx + 3, cy)
    well = test321_day(bid)
    if (well.play_animation) {
        return test321_fail('house outside radius 2 must not fill the well')
    }

    var h1 = __test_building_create(BUILDING_HOUSE_VACANT_LOT, cx + 1, cy)
    var h2 = __test_building_create(BUILDING_HOUSE_VACANT_LOT, cx, cy + 2)
    if (!h_out || !h1 || !h2) {
        return test321_fail('house create failed')
    }
    well = test321_day(bid)
    if (!well.play_animation || __test_building_anim_key(bid) != 'base_work') {
        return test321_fail('lots without water: key=' + __test_building_anim_key(bid))
    }
    __log_marker('test321_lots_water_sprite')

    __test_house_add_population(h1, 5)
    __test_house_add_population(h2, 5)
    for (var d = 0; d < 5; d++) {
        __test_building_update_day(h1)
        __test_building_update_day(h2)
        well = test321_day(bid)
        if (!well.play_animation || __test_building_anim_key(bid) != 'base_work') {
            return test321_fail('populated houses day ' + d + ': key=' + __test_building_anim_key(bid))
        }
    }
    __log_marker('test321_populated_water_sprite')

    well.set_fancy(true)
    building_well_update_graphic({ bid: bid })
    if (__test_building_anim_key(bid) != 'fancy_work') {
        return test321_fail('fancy well key=' + __test_building_anim_key(bid))
    }
    well.set_fancy(false)
    __log_marker('test321_fancy_water_sprite')

    __test_house_set_water_supply(h1, 1)
    well = test321_day(bid)
    if (!well.play_animation) {
        return test321_fail('one house still without water must keep the water sprite')
    }
    __test_house_set_water_supply(h2, 1)
    well = test321_day(bid)
    if (well.play_animation || __test_building_anim_key(bid) != '') {
        return test321_fail('all houses supplied: key=' + __test_building_anim_key(bid))
    }
    __log_marker('test321_supplied_plain')

    var base_pos = test321_pos_matches_og('base_work', 0)
    var fancy_pos = test321_pos_matches_og('fancy_work', 2)
    if (base_pos == 'skip' || fancy_pos == 'skip') {
        __log_marker('test321_pos_art_skipped:no_resource')
    } else if (base_pos != 'ok' || fancy_pos != 'ok') {
        return test321_fail(base_pos + ' ' + fancy_pos)
    } else {
        __log_marker('test321_pos_og')
    }

    __test321_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test321_ok
        && __test_find_inlog('[test-marker] test321_no_houses_plain')
        && __test_find_inlog('[test-marker] test321_lots_water_sprite')
        && __test_find_inlog('[test-marker] test321_populated_water_sprite')
        && __test_find_inlog('[test-marker] test321_fancy_water_sprite')
        && __test_find_inlog('[test-marker] test321_supplied_plain')
}
