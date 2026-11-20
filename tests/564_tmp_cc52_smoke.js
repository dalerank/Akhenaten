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

    check("playable52", mission_is_playable(52))

    var cfg = get_mission_config(52)
    check("enable_events", !!cfg.enable_scenario_events)
    check("events20", cfg.events && cfg.events.length == 20)
    check("hide_cities", !!cfg.hide_pak_cities)
    check("cities13", cfg.cities && cfg.cities.length == 13)
    check("hide_routes", !!cfg.hide_pak_routes)
    check("routes4", cfg.empire_routes && cfg.empire_routes.length == 4)
    check("hide_objects", !!cfg.hide_pak_objects)
    check("ornaments5", cfg.empire_ornaments && cfg.empire_ornaments.length == 5)
    check("texts16", cfg.empire_texts && cfg.empire_texts.length == 16)
    check("next_end", cfg.next_mission == -1)
    check("start_msg", cfg.start_message == "message_mission_actium")

    var by_name = {}
    for (var i = 0; i < cfg.cities.length; i++) {
        by_name[cfg.cities[i].name] = cfg.cities[i]
    }
    check("ours_actium", by_name["Actium"] && by_name["Actium"].type == EMPIRE_CITY_OURS)
    check("athens_trade", by_name["Athens"] && by_name["Athens"].is_sea_trade == true)
    check("alex_pharaoh", by_name["Alexandria"] && by_name["Alexandria"].type == EMPIRE_CITY_PHARAOH_TRADING)
    check("waset_r0", by_name["Waset"] && by_name["Waset"].route == 0)

    var has_warship = false
    var has_transport = false
    var has_granary = false
    var has_water = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_WARSHIP_WHARF) has_warship = true
        if (cfg.buildings[b] == BUILDING_TRANSPORT_WHARF) has_transport = true
        if (cfg.buildings[b] == BUILDING_GRANARY) has_granary = true
        if (cfg.buildings[b] == BUILDING_WATER_SUPPLY) has_water = true
    }
    check("temp_warship", has_warship)
    check("buildings_transport", has_transport)
    check("no_granary", !has_granary)
    check("no_water_supply", !has_water)

    check("orn0_img", cfg.empire_ornaments[0].image == 13856)
    check("text_crete", cfg.empire_texts[0].name == "#crete")
    check("text_lebanon", cfg.empire_texts[15].name == "#lebanon")

    var inv = 0
    for (var e = 0; e < cfg.events.length; e++) {
        if (cfg.events[e].type == EVENT_TYPE_INVASION) inv = inv + 1
    }
    check("invasions2", inv == 2)

    __game_load_mission(52, 1)
    check("52.pop", __win_criteria.population.goal == 1000)
    check("52.kingdom", __win_criteria.kingdom.goal == 50)
    check("52.survival", __win_criteria.survival_time.enabled == true && __win_criteria.survival_time.years == 6)
    check("52.mon_off", __win_criteria.monuments.enabled == false)
    check("52.year", scenario.start_year == -35)
    check("52.first", __scenario_monuments.first == 0)

    log_info("CC52 smoke fails=" + fails)
    __test_signal_ready()
}
function check_valid() {
    return __test_find_inlog("CC52 smoke fails=0")
}
