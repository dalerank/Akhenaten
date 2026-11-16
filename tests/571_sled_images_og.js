// OG figure_sled_action / figure_sled_puller_action images, enemy.c missile skip of FIGURE_SLED,
// Figure_model category 0 for the sled, building_info.c draw_walker_info (no sled portrait,
// a laborer with a partner reads as a sled puller).

var ACTION_17_LABORER_TO_PYRAMID = 17

var t571_ok = false

function t571_fail(msg) {
    __log_info_native('[test:571] FAIL: ' + msg)
    __test_signal_ready()
}

function t571_sled_for(lab, bid, resource) {
    __pyramid_spawn_sled_train(lab, bid)
    var sled = __pyramid_train_member(lab, 6)
    __test_figure_set_resource(sled, resource)
    return sled
}

function run_test() {
    __log_info_native('[test:571] sled images OG')
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, cx - 4, cy - 4) || test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, 40, 40)
    if (!bid) {
        return t571_fail('place pyramid')
    }
    var tile = __building_tile(bid)
    var lab = __test_figure_create(FIGURE_LABORER, tile.x + 12, tile.y + 8)
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)

    var cases = [
        [RESOURCE_STONE, 'stone', 'stone_ramp'],
        [RESOURCE_LIMESTONE, 'limestone', 'limestone_ramp'],
        [RESOURCE_GRANITE, 'granite', 'granite_ramp'],
        [RESOURCE_MARBLE, 'marble', 'marble_ramp'],
        [RESOURCE_SANDSTONE, 'sandstone', 'sandstone_ramp'],
        [RESOURCE_BRICKS, 'bricks', 'bricks_ramp'],
        [RESOURCE_COPPER, 'copper', 'bricks_ramp'],
        [RESOURCE_LAMPS, 'lamps', 'bricks_ramp'],
        [RESOURCE_CLAY, 'bricks', 'bricks_ramp'],
        [RESOURCE_NONE, 'bricks', 'bricks_ramp']
    ]
    var sled = 0
    for (var i = 0; i < cases.length; i++) {
        sled = t571_sled_for(lab, bid, cases[i][0])
        if (!sled) {
            return t571_fail('no sled for resource ' + cases[i][0])
        }
        __test_sled_set_on_ramp(sled, 0)
        var ground = __test_figure_anim_key(sled)
        __test_sled_set_on_ramp(sled, 1)
        var ramp = __test_figure_anim_key(sled)
        if (ground != cases[i][1] || ramp != cases[i][2]) {
            return t571_fail('resource ' + cases[i][0] + ' got ' + ground + '/' + ramp + ' want ' + cases[i][1] + '/' + cases[i][2])
        }
        __test_figure_kill(sled)
        for (var p = 1; p <= 5; p++) {
            var m = __pyramid_train_member(lab, p)
            if (m) {
                __test_figure_kill(m)
            }
        }
    }
    __log_marker('t571_sled_images_ok')

    sled = t571_sled_for(lab, bid, RESOURCE_BRICKS)
    for (var k = 1; k <= 5; k++) {
        var puller = __pyramid_train_member(lab, k)
        __test_figure_update_animation(puller)
        var want = (k % 2 == 1) ? 'front' : 'pulling'
        if (__test_figure_anim_key(puller) != want) {
            return t571_fail('puller ' + k + ' anim ' + __test_figure_anim_key(puller) + ' want ' + want)
        }
    }
    __log_marker('t571_pullers_alternate_ok')

    if (__test_figure_type_category(FIGURE_SLED) != 0) {
        return t571_fail('sled category want 0 got ' + __test_figure_type_category(FIGURE_SLED))
    }
    var ltile = __figure_get_tile(lab)
    var stile = { x: ltile.x + 6, y: ltile.y }
    var lone_sled = test_figure_create(FIGURE_SLED, stile.x, stile.y)
    var archer = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, stile.x + 1, stile.y)
    if (!archer) {
        return t571_fail('create enemy archer')
    }
    var target = __test_enemy_missile_target(archer, 20)
    if (!lone_sled || target == lone_sled || !target) {
        return t571_fail('enemy missile target ' + target + ' (sled ' + lone_sled + ')')
    }
    __test_figure_kill(archer)
    // Melee: a hostile figure picks no fight with a category-0 sled, but does with a citizen.
    var mummy = test_figure_create(FIGURE_MUMMY, stile.x, stile.y)
    if (!mummy || __test_figure_combat_attack_at(mummy, stile.x, stile.y)) {
        return t571_fail('hostile fought the sled in melee')
    }
    var citizen = test_figure_create(FIGURE_IMMIGRANT, stile.x, stile.y + 1)
    if (!citizen || !__test_figure_combat_attack_at(mummy, stile.x, stile.y + 1)) {
        return t571_fail('control: hostile should fight a citizen')
    }
    __test_figure_kill(mummy)
    __log_marker('t571_enemy_skips_sled_ok')

    var sf = city.get_figure(sled)
    if (!sf.params.no_portrait) {
        return t571_fail('sled must have no portrait')
    }
    var lf = city.get_figure(lab)
    __test_figure_set_leading(lab, 0)
    var plain = lf.class_name
    __test_figure_set_leading(lab, sled)
    var pulling = lf.class_name
    var puller_name = city.get_figure(__pyramid_train_member(lab, 1)).class_name
    if (plain == pulling || pulling != puller_name) {
        return t571_fail('laborer with a partner reads "' + pulling + '", alone "' + plain + '"')
    }
    __log_marker('t571_info_ok')

    t571_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t571_ok
        && __test_find_inlog('[test-marker] t571_sled_images_ok')
        && __test_find_inlog('[test-marker] t571_pullers_alternate_ok')
        && __test_find_inlog('[test-marker] t571_enemy_skips_sled_ok')
        && __test_find_inlog('[test-marker] t571_info_ok')
}
