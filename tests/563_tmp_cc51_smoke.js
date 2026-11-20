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

    check("playable50", mission_is_playable(50))
    check("playable51", mission_is_playable(51))
    check("playable52", mission_is_playable(52))

    var cfg50 = get_mission_config(50)
    check("50.next51", cfg50.next_mission == 51)

    var cfg = get_mission_config(51)
    check("enable_events", !!cfg.enable_scenario_events)
    check("events43", cfg.events && cfg.events.length == 43)
    check("hide_cities", !!cfg.hide_pak_cities)
    check("cities19", cfg.cities && cfg.cities.length == 19)
    check("hide_routes", !!cfg.hide_pak_routes)
    check("routes13", cfg.empire_routes && cfg.empire_routes.length == 13)
    check("hide_objects", !!cfg.hide_pak_objects)
    check("ornaments8", cfg.empire_ornaments && cfg.empire_ornaments.length == 8)
    check("texts16", cfg.empire_texts && cfg.empire_texts.length == 16)
    check("next52", cfg.next_mission == 52)
    check("start_msg", cfg.start_message == "message_mission_cleopatra_alexandria")

    var by_name = {}
    for (var i = 0; i < cfg.cities.length; i++) {
        by_name[cfg.cities[i].name] = cfg.cities[i]
    }
    check("ours_alex", by_name["Alexandria"] && by_name["Alexandria"].type == EMPIRE_CITY_OURS)
    check("rome_weapons", by_name["Rome"] && by_name["Rome"].sells && by_name["Rome"].sells.indexOf(RESOURCE_WEAPONS) >= 0)
    check("rome_sea", by_name["Rome"] && by_name["Rome"].is_sea_trade == true)
    check("enkomi_marble", by_name["Enkomi"] && by_name["Enkomi"].sells && by_name["Enkomi"].sells.indexOf(RESOURCE_MARBLE) >= 0)
    check("migdol_r0", by_name["Migdol"] && by_name["Migdol"].route == 0)
    check("buhen_r0", by_name["Buhen"] && by_name["Buhen"].route == 0)
    check("kyrene_r0", by_name["Kyrene"] && by_name["Kyrene"].route == 0)
    check("byblos_display", by_name["Byblos"] && by_name["Byblos"].trade == false)

    var has_caes = false
    var has_maus = false
    var has_lib_mon = false
    var has_pharos = false
    var has_zoo = false
    var has_gold = false
    var has_lift = false
    var has_academy = false
    var has_warship = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_CAESAREUM) has_caes = true
        if (cfg.buildings[b] == BUILDING_MAUSOLEUM) has_maus = true
        if (cfg.buildings[b] == BUILDING_ALEXANDRIA_LIBRARY) has_lib_mon = true
        if (cfg.buildings[b] == BUILDING_PHAROS_LIGHTHOUSE) has_pharos = true
        if (cfg.buildings[b] == BUILDING_ZOO) has_zoo = true
        if (cfg.buildings[b] == BUILDING_GOLD_MINE) has_gold = true
        if (cfg.buildings[b] == BUILDING_WATER_LIFT) has_lift = true
        if (cfg.buildings[b] == BUILDING_MILITARY_ACADEMY) has_academy = true
        if (cfg.buildings[b] == BUILDING_WARSHIP_WHARF) has_warship = true
    }
    check("buildings_caesareum", has_caes)
    check("buildings_mausoleum", has_maus)
    check("no_library_mon", !has_lib_mon)
    check("no_pharos", !has_pharos)
    check("buildings_zoo", has_zoo)
    check("buildings_gold", has_gold)
    check("no_water_lift", !has_lift)
    check("no_academy", !has_academy)
    check("no_warship", !has_warship)

    check("burial5", cfg.burial_provisions && cfg.burial_provisions.length == 5)
    check("orn0_img", cfg.empire_ornaments[0].image == 13856)
    check("text_crete", cfg.empire_texts[0].name == "#crete")
    check("text_lebanon", cfg.empire_texts[15].name == "#lebanon")

    var cfg52 = get_mission_config(52)
    check("52.next_end", cfg52.next_mission == -1)

    __game_load_mission(51, 1)
    check("51.pop", __win_criteria.population.goal == 10000)
    check("51.mon", __win_criteria.monuments.goal == 24)
    check("51.year", scenario.start_year == -40)
    check("51.first", __scenario_monuments.first == 30)
    check("51.second", __scenario_monuments.second == 27)

    log_info("CC51 smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() {
    return __test_find_inlog("CC51 smoke fails=0")
}
