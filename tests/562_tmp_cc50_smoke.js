function run_test() {
    var fails = 0
    function check(name, cond) {
        if (!cond) {
            log_info("FAIL: " + name)
            fails = fails + 1
        } else {
            log_info("ok: " + name)
        }
    }

    check("playable49", mission_is_playable(49))
    check("playable50", mission_is_playable(50))

    var cfg49 = get_mission_config(49)
    check("49.next50", cfg49.next_mission == 50)

    var cfg = get_mission_config(50)
    check("enable_events", !!cfg.enable_scenario_events)
    check("events25", cfg.events && cfg.events.length == 25)
    check("hide_cities", !!cfg.hide_pak_cities)
    check("cities7", cfg.cities && cfg.cities.length == 7)
    check("hide_routes", !!cfg.hide_pak_routes)
    check("routes6", cfg.empire_routes && cfg.empire_routes.length == 6)
    check("hide_objects", !!cfg.hide_pak_objects)
    check("ornaments5", cfg.empire_ornaments && cfg.empire_ornaments.length == 5)
    check("texts16", cfg.empire_texts && cfg.empire_texts.length == 16)
    check("next51", cfg.next_mission == 51)
    check("start_msg", cfg.start_message == "message_mission_maritis")

    var by_name = {}
    for (var i = 0; i < cfg.cities.length; i++) {
        by_name[cfg.cities[i].name] = cfg.cities[i]
    }
    check("ours_maritis", by_name["Maritis"] && by_name["Maritis"].type == EMPIRE_CITY_OURS)
    check("alex_pharaoh", by_name["Alexandria"] && by_name["Alexandria"].type == EMPIRE_CITY_PHARAOH)
    check("alex_no_trade", by_name["Alexandria"] && by_name["Alexandria"].trade == false)
    check("gaza_display", by_name["Gaza"] && by_name["Gaza"].trade == false)
    check("tyre_sea", by_name["Tyre"] && by_name["Tyre"].is_sea_trade == true)
    check("migdol_weapons", by_name["Migdol"] && by_name["Migdol"].sells && by_name["Migdol"].sells.indexOf(RESOURCE_WEAPONS) >= 0)

    var inv = 0
    var fired = 0
    for (var e = 0; e < cfg.events.length; e++) {
        if (cfg.events[e].type == EVENT_TYPE_INVASION) inv = inv + 1
        if (cfg.events[e].event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED) fired = fired + 1
    }
    check("invasions_from_js", inv == 0)
    check("already_fired4", fired == 4)

    var has_fort = false
    var has_zoo = false
    var has_lib = false
    var has_pharos = false
    var has_caesareum = false
    var has_maus = false
    var has_warship = false
    var has_recruiter = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_FORT_INFANTRY) has_fort = true
        if (cfg.buildings[b] == BUILDING_ZOO) has_zoo = true
        if (cfg.buildings[b] == BUILDING_ALEXANDRIA_LIBRARY) has_lib = true
        if (cfg.buildings[b] == BUILDING_PHAROS_LIGHTHOUSE) has_pharos = true
        if (cfg.buildings[b] == BUILDING_CAESAREUM) has_caesareum = true
        if (cfg.buildings[b] == BUILDING_MAUSOLEUM) has_maus = true
        if (cfg.buildings[b] == BUILDING_WARSHIP_WHARF) has_warship = true
        if (cfg.buildings[b] == BUILDING_RECRUITER) has_recruiter = true
    }
    check("buildings_fort", has_fort)
    check("buildings_zoo", has_zoo)
    check("no_library", !has_lib)
    check("no_pharos", !has_pharos)
    check("no_caesareum", !has_caesareum)
    check("no_mausoleum", !has_maus)
    check("no_warship", !has_warship)
    check("no_recruiter", !has_recruiter)

    check("orn0_img", cfg.empire_ornaments[0].image == 13856)
    check("text_crete", cfg.empire_texts[0].name == "#crete")
    check("text_greece_neg", cfg.empire_texts[4].name == "#greece" && cfg.empire_texts[4].pos && cfg.empire_texts[4].pos[0] == -10)
    check("text_lebanon", cfg.empire_texts[15].name == "#lebanon")

    __game_load_mission(50, 1)
    check("50.pop", __win_criteria.population.goal == 1000)
    check("50.mon_off", __win_criteria.monuments.enabled == false)
    check("50.survival", __win_criteria.survival_time.enabled == true && __win_criteria.survival_time.years == 7)
    check("50.year", scenario.start_year == -50)
    check("50.first", __scenario_monuments.first == 0)
    check("50.second", __scenario_monuments.second == 0)
    check("50.alt_predator", scenario.alt_predator_type == true)

    log_info("CC50 smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() {
    return __test_find_inlog("CC50 smoke fails=0")
}
