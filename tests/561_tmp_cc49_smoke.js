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

    check("playable48", mission_is_playable(48))
    check("playable49", mission_is_playable(49))

    var cfg48 = get_mission_config(48)
    check("48.next49", cfg48.next_mission == 49)

    var cfg = get_mission_config(49)
    check("enable_events", !!cfg.enable_scenario_events)
    check("events45", cfg.events && cfg.events.length == 45)
    check("hide_cities", !!cfg.hide_pak_cities)
    check("cities18", cfg.cities && cfg.cities.length == 18)
    check("hide_routes", !!cfg.hide_pak_routes)
    check("routes14", cfg.empire_routes && cfg.empire_routes.length == 14)
    check("hide_objects", !!cfg.hide_pak_objects)
    check("ornaments8", cfg.empire_ornaments && cfg.empire_ornaments.length == 8)
    check("texts16", cfg.empire_texts && cfg.empire_texts.length == 16)
    check("next50", cfg.next_mission == 50)
    check("start_msg", cfg.start_message == "message_mission_ptolemy_alexandria")

    var by_name = {}
    for (var i = 0; i < cfg.cities.length; i++) {
        by_name[cfg.cities[i].name] = cfg.cities[i]
    }
    check("ours_alex", by_name["Alexandria"] && by_name["Alexandria"].type == EMPIRE_CITY_OURS)
    check("enkomi_marble", by_name["Enkomi"] && by_name["Enkomi"].sells && by_name["Enkomi"].sells.indexOf(RESOURCE_MARBLE) >= 0)
    check("enkomi_sea", by_name["Enkomi"] && by_name["Enkomi"].is_sea_trade == true)
    check("knossos_r0", by_name["Knossos"] && by_name["Knossos"].trade == false && by_name["Knossos"].route == 0)
    check("migdol_r0", by_name["Migdol"] && by_name["Migdol"].route == 0)
    check("waset_r0", by_name["Waset"] && by_name["Waset"].route == 0)
    check("on_r14", by_name["On"] && by_name["On"].trade == false && by_name["On"].route == 14)
    check("bahariya_trade", by_name["Bahariya Oasis"] && by_name["Bahariya Oasis"].trade != false)

    var has_lib = false
    var has_pharos = false
    var has_zoo = false
    var has_gold = false
    var has_chariot = false
    var has_senet = false
    var has_lift = false
    var has_academy = false
    var has_warship = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_ALEXANDRIA_LIBRARY) has_lib = true
        if (cfg.buildings[b] == BUILDING_PHAROS_LIGHTHOUSE) has_pharos = true
        if (cfg.buildings[b] == BUILDING_ZOO) has_zoo = true
        if (cfg.buildings[b] == BUILDING_GOLD_MINE) has_gold = true
        if (cfg.buildings[b] == BUILDING_CHARIOTS_WORKSHOP) has_chariot = true
        if (cfg.buildings[b] == BUILDING_SENET_HOUSE) has_senet = true
        if (cfg.buildings[b] == BUILDING_WATER_LIFT) has_lift = true
        if (cfg.buildings[b] == BUILDING_MILITARY_ACADEMY) has_academy = true
        if (cfg.buildings[b] == BUILDING_WARSHIP_WHARF) has_warship = true
    }
    check("buildings_library", has_lib)
    check("buildings_pharos", has_pharos)
    check("buildings_zoo", has_zoo)
    check("buildings_gold", has_gold)
    check("buildings_chariot", has_chariot)
    check("buildings_senet", has_senet)
    check("no_water_lift", !has_lift)
    check("no_academy", !has_academy)
    check("no_warship", !has_warship)

    check("orn0_img", cfg.empire_ornaments[0].image == 13856)
    check("text_crete", cfg.empire_texts[0].name == "#crete")
    check("text_lebanon", cfg.empire_texts[15].name == "#lebanon")

    __game_load_mission(49, 1)
    check("49.pop", __win_criteria.population.goal == 7000)
    check("49.mon", __win_criteria.monuments.goal == 28)
    check("49.year", scenario.start_year == -305)
    check("49.first", __scenario_monuments.first == 29)
    check("49.second", __scenario_monuments.second == 28)

    log_info("CC49 smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() {
    return __test_find_inlog("CC49 smoke fails=0")
}
