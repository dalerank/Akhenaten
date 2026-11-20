// Industry Office (IO4): flag OFF; place office + workshops in/out radius;
// mothball via office API; papyrus drain disables management;
// storage/guild carve-out; apply_enhanced menu unlock.
// Markers:
//   [test-marker] industry_office_flag_off_ok
//   [test-marker] industry_office_menu_on_ok
//   [test-marker] industry_office_create_ok
//   [test-marker] industry_office_coverage_ok
//   [test-marker] industry_office_carveout_ok
//   [test-marker] industry_office_mothball_ok
//   [test-marker] industry_office_unmothball_ok
//   [test-marker] industry_office_no_papyrus_ok
//   [test-marker] industry_office_out_of_radius_ok

var __test070_ok = {
    flag: false,
    menu_on: false,
    create: false,
    coverage: false,
    carveout: false,
    mothball: false,
    unmothball: false,
    no_papyrus: false,
    out_radius: false
}

function run_test() {
    __log_info_native('[test:070] industry office')
    test_ensure_city_session('data/default.map')

    var prev = game_features.get('gameplay_enhanced_industry_office')
    function finish() {
        game_features.set('gameplay_enhanced_industry_office', prev)
        building_menu_ctrl.apply_enhanced_buildings()
        __test_signal_ready()
    }

    if (game_features.default('gameplay_enhanced_industry_office')) {
        __log_info_native('[test:070] flag default should be OFF')
        finish()
        return
    }
    if (building_menu_ctrl.is_enabled(BUILDING_INDUSTRY_OFFICE)) {
        __log_info_native('[test:070] menu should be disabled while flag OFF')
        finish()
        return
    }
    __log_marker('industry_office_flag_off_ok')
    __test070_ok.flag = true

    game_features.set('gameplay_enhanced_industry_office', true)
    building_menu_ctrl.apply_enhanced_buildings()
    if (!building_menu_ctrl.is_enabled(BUILDING_INDUSTRY_OFFICE)) {
        __log_info_native('[test:070] apply_enhanced should enable office menu')
        finish()
        return
    }
    __log_marker('industry_office_menu_on_ok')
    __test070_ok.menu_on = true

    __scenario_building_allow(BUILDING_INDUSTRY_OFFICE, true)
    __scenario_building_allow(BUILDING_POTTERY_WORKSHOP, true)
    __scenario_building_allow(BUILDING_BREWERY_WORKSHOP, true)
    __scenario_building_allow(BUILDING_WEAPONSMITH, true)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var office_id = __test_building_create(BUILDING_INDUSTRY_OFFICE, cx, cy)
    var pot_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, cx + 2, cy)
    var brew_id = __test_building_create(BUILDING_BREWERY_WORKSHOP, cx + 3, cy)
    var far_id = __test_building_create(BUILDING_WEAPONSMITH, cx + 40, cy)
    var yard_id = __test_building_create(BUILDING_STORAGE_YARD, cx, cy + 2)
    var guild_id = __test_building_create(BUILDING_ARTISANS_GUILD, cx + 2, cy + 2)
    if (!office_id || !pot_id || !brew_id || !far_id || !yard_id || !guild_id) {
        __log_info_native('[test:070] create failed office=' + office_id + ' pot=' + pot_id
            + ' brew=' + brew_id + ' far=' + far_id + ' yard=' + yard_id + ' guild=' + guild_id)
        finish()
        return
    }
    __log_marker('industry_office_create_ok')
    __test070_ok.create = true

    var office_b = city.get_building(office_id)
    var pot = city.get_building(pot_id)
    var brew = city.get_building(brew_id)
    var far = city.get_building(far_id)
    var office = city.get_industry_office(office_id)
    if (!office || !office_b || !pot || !brew || !far) {
        __log_info_native('[test:070] get_building failed')
        finish()
        return
    }

    // Stock papyrus via negative consume (same pattern as artisans guild tests).
    office_b.consume_resource(RESOURCE_PAPYRUS, -100)
    __test_building_set_workers(office_id, 10)
    office_b.has_road_access = true

    if (!office.is_management_active()) {
        __log_info_native('[test:070] office should be active with papyrus+workers stored='
            + office_b.stored_resource(RESOURCE_PAPYRUS) + ' workers=' + office_b.num_workers)
        finish()
        return
    }

    var managed = office.managed_ids()
    var has_pot = false
    var has_brew = false
    var has_far = false
    var has_yard = false
    var has_guild = false
    for (var i = 0; i < managed.length; i++) {
        if (managed[i] == pot_id) has_pot = true
        if (managed[i] == brew_id) has_brew = true
        if (managed[i] == far_id) has_far = true
        if (managed[i] == yard_id) has_yard = true
        if (managed[i] == guild_id) has_guild = true
    }
    if (!has_pot || !has_brew) {
        __log_info_native('[test:070] coverage missing nearby workshops count=' + managed.length)
        finish()
        return
    }
    if (has_far) {
        __log_info_native('[test:070] far weaponsmith should be outside radius')
        finish()
        return
    }
    __log_marker('industry_office_coverage_ok')
    __test070_ok.coverage = true

    if (has_yard || has_guild) {
        __log_info_native('[test:070] storage/guild must be carved out yard=' + has_yard
            + ' guild=' + has_guild)
        finish()
        return
    }
    __log_marker('industry_office_carveout_ok')
    __test070_ok.carveout = true

    var changed = office.mothball_all()
    if (changed < 2 || pot.state != 7 || brew.state != 7) {
        __log_info_native('[test:070] mothball_all failed changed=' + changed
            + ' pot.state=' + pot.state + ' brew.state=' + brew.state)
        finish()
        return
    }
    if (far.state == 7) {
        __log_info_native('[test:070] far building should stay valid')
        finish()
        return
    }
    __log_marker('industry_office_mothball_ok')
    __test070_ok.mothball = true
    __log_marker('industry_office_out_of_radius_ok')
    __test070_ok.out_radius = true

    // Mothballed buildings must remain listed so they can be resumed.
    managed = office.managed_ids()
    has_pot = false
    has_brew = false
    for (var j = 0; j < managed.length; j++) {
        if (managed[j] == pot_id) has_pot = true
        if (managed[j] == brew_id) has_brew = true
    }
    if (!has_pot || !has_brew) {
        __log_info_native('[test:070] mothballed workshops disappeared from managed list')
        finish()
        return
    }

    changed = office.unmothball_all()
    if (changed < 2 || pot.state != 1 || brew.state != 1) {
        __log_info_native('[test:070] unmothball_all failed changed=' + changed
            + ' pot.state=' + pot.state + ' brew.state=' + brew.state)
        finish()
        return
    }
    __log_marker('industry_office_unmothball_ok')
    __test070_ok.unmothball = true

    // Drain papyrus → inactive; mothball must no-op.
    office_b.consume_resource(RESOURCE_PAPYRUS, office_b.stored_resource(RESOURCE_PAPYRUS))
    if (office.is_management_active()) {
        __log_info_native('[test:070] office should be inactive without papyrus')
        finish()
        return
    }
    changed = office.mothball_all()
    if (changed != 0 || pot.state != 1) {
        __log_info_native('[test:070] mothball without papyrus should no-op changed=' + changed)
        finish()
        return
    }
    __log_marker('industry_office_no_papyrus_ok')
    __test070_ok.no_papyrus = true

    __log_info_native('[test:070] ok')
    finish()
}

function check_valid() {
    if (!__test070_ok.flag || !__test070_ok.menu_on || !__test070_ok.create
        || !__test070_ok.coverage || !__test070_ok.carveout || !__test070_ok.mothball
        || !__test070_ok.unmothball || !__test070_ok.no_papyrus || !__test070_ok.out_radius) {
        __log_info_native('[test:070] one or more phases failed')
        return false
    }
    var markers = [
        'industry_office_flag_off_ok',
        'industry_office_menu_on_ok',
        'industry_office_create_ok',
        'industry_office_coverage_ok',
        'industry_office_carveout_ok',
        'industry_office_mothball_ok',
        'industry_office_unmothball_ok',
        'industry_office_no_papyrus_ok',
        'industry_office_out_of_radius_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:070] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

run_test()
