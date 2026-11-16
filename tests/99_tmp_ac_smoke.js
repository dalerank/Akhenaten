function run_test() {
    var fails = 0
    function check(name, cond) {
        if (!cond) { log_info("FAIL: " + name); fails = fails + 1 } else { log_info("ok: " + name) }
    }

    check("enable46", get_mission_config(46).enable_scenario_events == true)
    check("hide46", get_mission_config(46).hide_pak_cities == true)
    check("events46", get_mission_config(46).events && get_mission_config(46).events.length == 10)
    check("cities46", get_mission_config(46).cities && get_mission_config(46).cities.length == 22)
    check("routes46", get_mission_config(46).empire_routes && get_mission_config(46).empire_routes.length == 3)

    check("enable47", get_mission_config(47).enable_scenario_events == true)
    check("events47", get_mission_config(47).events && get_mission_config(47).events.length == 20)
    check("cities47", get_mission_config(47).cities && get_mission_config(47).cities.length == 25)
    check("routes47", get_mission_config(47).empire_routes && get_mission_config(47).empire_routes.length == 3)
    check("47.next", get_mission_config(47).next_mission == -1)

    __game_load_mission(46, 1)
    check("46.surv", __win_criteria.survival_time.years == 7)
    check("46.enkomi", !!empire.get_city("Enkomi"))
    check("46.timna", !!empire.get_city("Timna"))
    check("46.migdol", !!empire.get_city("Migdol"))

    __game_load_mission(47, 1)
    check("47.surv", __win_criteria.survival_time.years == 10)
    check("47.enkomi", !!empire.get_city("Enkomi"))
    check("47.athens", !!empire.get_city("Athens"))
    check("47.tanis", !!empire.get_city("Tanis"))
    check("47.no_spill", mission_end_compute_next_scenario_id(47) == -1)

    log_info("AC redefine smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() { return true }
