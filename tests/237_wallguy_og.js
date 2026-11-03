// FIG_WALLGUY / FIGURE_TOWER_SENTRY: OG wall/setup flags, home kill, off-wall death,
// towers-only recruiter spawn (not gatehouses), going-to-tower survives open ground.
// Markers:
//   [test-marker] wallguy_params_ok
//   [test-marker] wallguy_towers_only_ok
//   [test-marker] wallguy_spawn_ok
//   [test-marker] wallguy_home_poof_ok
//   [test-marker] wallguy_offwall_poof_ok
//   [test-marker] wallguy_going_survives_ok

var ACTION_170_TOWER_SENTRY_AT_REST = 170
var ACTION_174_TOWER_SENTRY_GOING_TO_TOWER = 174

var __test237_ok = false

function test237_fail(msg) {
    __log_info_native('[test:237] ' + msg)
    __test_signal_ready()
}

function test237_find_sentry() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_TOWER_SENTRY && __test_figure_is_alive(i) == 1) {
            return i
        }
    }
    return 0
}

function run_test() {
    __log_info_native('[test:237] wallguy / tower sentry OG')

    if (__test_figure_type_max_roam(FIGURE_TOWER_SENTRY) != 800) {
        return test237_fail('max_roam want 800 got ' + __test_figure_type_max_roam(FIGURE_TOWER_SENTRY))
    }
    // figure_category_armed = 2
    if (__test_figure_type_category(FIGURE_TOWER_SENTRY) != 2) {
        return test237_fail('category want armed(2) got ' + __test_figure_type_category(FIGURE_TOWER_SENTRY))
    }
    __log_marker('wallguy_params_ok')

    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_TOWER_SENTRY)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var rid = __test_building_create(BUILDING_RECRUITER, cx - 8, cy)
    var gate = __test_building_create(BUILDING_MUD_GATEHOUSE, cx + 8, cy)
    if (!rid || !gate) {
        return test237_fail('create recruiter/gate failed rid=' + rid + ' gate=' + gate)
    }
    __test_building_force_road_access(rid)
    __test_building_force_road_access(gate)
    __test_building_set_workers(gate, 10)

    __test_barracks_request_tower_sentry()
    if (__test_recruiter_create_tower_sentry(rid) != 0) {
        return test237_fail('gatehouse must not receive a tower sentry')
    }
    __log_marker('wallguy_towers_only_ok')

    var tower = __test_building_create(BUILDING_MUD_TOWER, cx, cy)
    if (!tower) {
        return test237_fail('tower create failed')
    }
    __test_building_force_road_access(tower)
    __test_building_set_workers(tower, 10)
    __test_make_wall(cx, cy)

    __test_barracks_request_tower_sentry()
    if (__test_recruiter_create_tower_sentry(rid) != 1) {
        return test237_fail('tower sentry spawn failed')
    }
    var fid = test237_find_sentry()
    if (!fid) {
        return test237_fail('no sentry after spawn')
    }
    if (__test_figure_get_action(fid) != ACTION_174_TOWER_SENTRY_GOING_TO_TOWER) {
        return test237_fail('spawn action want 174 got ' + __test_figure_get_action(fid))
    }
    __log_marker('wallguy_spawn_ok')

    city.figures.remove_figures(FIGURE_TOWER_SENTRY)
    var orphan = test_figure_create(FIGURE_TOWER_SENTRY, cx, cy)
    if (!orphan) {
        return test237_fail('orphan create failed')
    }
    __test_figure_set_home(orphan, tower)
    __test_figure_set_action(orphan, ACTION_170_TOWER_SENTRY_AT_REST)
    __test_figure_action_perform(orphan)
    if (__test_figure_is_alive(orphan) == 1) {
        return test237_fail('should poof when tower does not own walker')
    }
    __log_marker('wallguy_home_poof_ok')

    city.figures.remove_figures(FIGURE_TOWER_SENTRY)
    var offwall = test_figure_create(FIGURE_TOWER_SENTRY, cx + 2, cy + 2)
    if (!offwall) {
        return test237_fail('offwall create failed')
    }
    __test_figure_set_home(offwall, tower)
    __test_building_set_figure_slot(tower, 0, offwall)
    __test_figure_set_action(offwall, ACTION_170_TOWER_SENTRY_AT_REST)
    __test_figure_action_perform(offwall)
    if (__test_figure_is_alive(offwall) == 1) {
        return test237_fail('should poof when standing off the wall')
    }
    __log_marker('wallguy_offwall_poof_ok')

    city.figures.remove_figures(FIGURE_TOWER_SENTRY)
    var going = test_figure_create(FIGURE_TOWER_SENTRY, cx + 3, cy + 3)
    if (!going) {
        return test237_fail('going create failed')
    }
    __test_figure_set_home(going, tower)
    __test_building_set_figure_slot(tower, 0, going)
    __test_figure_set_action(going, ACTION_174_TOWER_SENTRY_GOING_TO_TOWER)
    __test_figure_action_perform(going)
    if (__test_figure_is_alive(going) != 1) {
        return test237_fail('going-to-tower must survive open ground')
    }
    __log_marker('wallguy_going_survives_ok')

    __test237_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test237_ok
        && __test_find_inlog('[test-marker] wallguy_params_ok')
        && __test_find_inlog('[test-marker] wallguy_towers_only_ok')
        && __test_find_inlog('[test-marker] wallguy_spawn_ok')
        && __test_find_inlog('[test-marker] wallguy_home_poof_ok')
        && __test_find_inlog('[test-marker] wallguy_offwall_poof_ok')
        && __test_find_inlog('[test-marker] wallguy_going_survives_ok')
}
