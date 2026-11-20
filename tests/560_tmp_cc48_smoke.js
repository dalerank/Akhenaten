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

    var cfg = get_mission_config(48)
    check("playable48", mission_is_playable(48))
    check("enable_events", !!cfg.enable_scenario_events)
    check("events40", cfg.events && cfg.events.length == 40)
    check("hide_cities", !!cfg.hide_pak_cities)
    check("cities19", cfg.cities && cfg.cities.length == 19)
    check("hide_routes", !!cfg.hide_pak_routes)
    check("routes13", cfg.empire_routes && cfg.empire_routes.length == 13)
    check("hide_objects", !!cfg.hide_pak_objects)
    check("ornaments8", cfg.empire_ornaments && cfg.empire_ornaments.length == 8)
    check("texts16", cfg.empire_texts && cfg.empire_texts.length == 16)

    var by_name = {}
    for (var i = 0; i < cfg.cities.length; i++) {
        by_name[cfg.cities[i].name] = cfg.cities[i]
    }
    check("ours_alex", by_name["Alexandria"] && by_name["Alexandria"].type == EMPIRE_CITY_OURS)
    check("byblos_open", by_name["Byblos"] && by_name["Byblos"].is_open == true)
    check("byblos_oil", by_name["Byblos"].sells && by_name["Byblos"].sells.indexOf(RESOURCE_OIL) >= 0)
    check("knossos_r0", by_name["Knossos"] && by_name["Knossos"].trade == false && by_name["Knossos"].route == 0)
    check("bubastis_r0", by_name["Bubastis"] && by_name["Bubastis"].route == 0)
    check("tyre_r0", by_name["Tyre"] && by_name["Tyre"].route == 0)
    check("migdol_r0", by_name["Migdol"] && by_name["Migdol"].route == 0)
    check("waset_r0", by_name["Waset"] && by_name["Waset"].route == 0)
    check("on_r14", by_name["On"] && by_name["On"].trade == false && by_name["On"].route == 14)
    check("bahariya_r6", by_name["Bahariya Oasis"] && by_name["Bahariya Oasis"].route == 6)

    check("orn0_img", cfg.empire_ornaments[0].image == 13856)
    check("text_crete", cfg.empire_texts[0].name == "#crete")
    check("text_lebanon", cfg.empire_texts[15].name == "#lebanon")

    var by_route = {}
    for (var r = 0; r < cfg.empire_routes.length; r++) {
        by_route[cfg.empire_routes[r].route] = cfg.empire_routes[r]
    }
    check("route1_sea", by_route[1] && by_route[1].type == 2)
    check("route14_on", !!by_route[14])
    check("no_orphan15", !by_route[15])

    check("next49", cfg.next_mission == 49)
    check("start_msg", cfg.start_message == "message_mission_alexandria_2")

    var has_maus = false
    var has_lib = false
    var has_pharos = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_MAUSOLEUM) has_maus = true
        if (cfg.buildings[b] == BUILDING_ALEXANDRIA_LIBRARY) has_lib = true
        if (cfg.buildings[b] == BUILDING_PHAROS_LIGHTHOUSE) has_pharos = true
    }
    check("buildings_mausoleum", has_maus)
    check("no_library_mon", !has_lib)
    check("no_pharos", !has_pharos)

    __game_load_mission(48, 1)
    check("48.pop", __win_criteria.population.goal == 4000)
    check("48.mon", __win_criteria.monuments.enabled == true && __win_criteria.monuments.goal == 14)
    check("48.year", scenario.start_year == -331)
    check("48.first", __scenario_monuments.first == 25)
    check("48.second", __scenario_monuments.second == 0)
    check("maus_weight", MONUMENT_WEIGHTS[BUILDING_MAUSOLEUM] == 5)
    check("maus_covers_goal", monument_rating_from_points(MONUMENT_WEIGHTS[BUILDING_MAUSOLEUM], false) >= 14)

    log_info("CC48 smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() {
    return __test_find_inlog("CC48 smoke fails=0")
}
