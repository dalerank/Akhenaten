log_info("akhenaten: building menu ctrl started")

var building_menu_ctrl = {
    enabled: {}
    visible: {}
}

building_menu_ctrl.is_submenu = function(type) {
    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id == type) return true
    }
    return false
}

building_menu_ctrl.set_all = function(en) {
    building_menu_ctrl.enabled = {}
    building_menu_ctrl.visible = {}
    for (var i = 0; i < building_menu.length; i++) {
        var group = building_menu[i]
        building_menu_ctrl.enabled[group.id] = en
        for (var j = 0; j < group.items.length; j++) {
            building_menu_ctrl.enabled[group.items[j]] = en
        }
    }
}

building_menu_ctrl.set_visible = function(type, vis) {
    building_menu_ctrl.visible[type] = vis
}

building_menu_ctrl.is_visible = function(type) {
    var v = building_menu_ctrl.visible[type]
    return (v === undefined || v === null) ? true : v
}

building_menu_ctrl.is_enabled = function(type) {
    var e = building_menu_ctrl.enabled[type]
    return (e !== undefined && e !== null) ? e : false
}

building_menu_ctrl.use_building = function(type, en) {
    building_menu_ctrl.enabled[type] = en
    __scenario_building_allow(type, en)

    if (en && !building_menu_ctrl.is_submenu(type)) {
        if (__building_static_flag(type, "is_farm"))
            building_menu_ctrl.use_building(BUILDING_MENU_FARMS)
        if (__building_static_flag(type, "is_extractor") || __building_static_flag(type, "is_harvester")) {
            building_menu_ctrl.use_building(BUILDING_MENU_RAW_MATERIALS)
            building_menu_ctrl.use_building(BUILDING_MENU_INDUSTRY)
        }
        if (__building_static_flag(type, "is_workshop"))
            building_menu_ctrl.use_building(BUILDING_MENU_INDUSTRY)
        if (__building_static_flag(type, "is_fort"))
            building_menu_ctrl.use_building(BUILDING_MENU_FORTS)
        if (__building_static_flag(type, "is_defense"))
            building_menu_ctrl.use_building(BUILDING_MENU_DEFENSES)
        if (__building_static_flag(type, "is_shrine"))
            building_menu_ctrl.use_building(BUILDING_MENU_SHRINES)
        if (__building_static_flag(type, "is_temple"))
            building_menu_ctrl.use_building(BUILDING_MENU_TEMPLES)
        if (__building_static_flag(type, "is_temple_complex"))
            building_menu_ctrl.use_building(BUILDING_MENU_TEMPLE_COMPLEX)
        if (__building_static_flag(type, "is_guild"))
            building_menu_ctrl.use_building(BUILDING_MENU_CONSTURCTION_GUILDS)
        if (__building_static_flag(type, "is_beautification"))
            building_menu_ctrl.use_building(BUILDING_MENU_BEAUTIFICATION)
        if (__building_static_flag(type, "is_water_crossing"))
            building_menu_ctrl.use_building(BUILDING_MENU_WATER_CROSSINGS)
        if (__building_static_flag(type, "is_monument"))
            building_menu_ctrl.use_building(BUILDING_MENU_MONUMENTS)
        if (__building_static_flag(type, "is_education"))
            building_menu_ctrl.use_building(BUILDING_MENU_EDUCATION)
    }
}

building_menu_ctrl.count_items = function(submenu) {
    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id != submenu) continue
        var group = building_menu[i]
        var count = 0
        for (var j = 0; j < group.items.length; j++) {
            var item_type = group.items[j]
            if (building_menu_ctrl.is_submenu(item_type)) {
                count += (building_menu_ctrl.count_items(item_type) > 0) ? 1 : 0
            } else {
                count += building_menu_ctrl.is_enabled(item_type) ? 1 : 0
            }
        }
        return count
    }
    return 0
}

building_menu_ctrl.next_index = function(submenu, current) {
    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id != submenu) continue
        var group = building_menu[i]
        for (var j = current + 1; j < group.items.length; j++) {
            if (building_menu_ctrl.is_enabled(group.items[j])) return j
        }
        return 0
    }
    return 0
}

building_menu_ctrl.item_type = function(submenu, index) {
    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id != submenu) continue
        var group = building_menu[i]
        return (index >= 0 && index < group.items.length) ? group.items[index] : 0
    }
    return 0
}

building_menu_ctrl.disable_resources = function() {
    var disable_if = function(type, resource) {
        if (!__city_can_produce_resource(resource)) {
            building_menu_ctrl.use_building(type, false)
        }
    }
    disable_if(BUILDING_BARLEY_FARM, RESOURCE_BARLEY)
    disable_if(BUILDING_FLAX_FARM, RESOURCE_FLAX)
    disable_if(BUILDING_GRAIN_FARM, RESOURCE_GRAIN)
    disable_if(BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE)
    disable_if(BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES)
    disable_if(BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS)
    disable_if(BUILDING_FIGS_FARM, RESOURCE_FIGS)
    disable_if(BUILDING_HENNA_FARM, RESOURCE_HENNA)
    disable_if(BUILDING_HUNTING_LODGE, RESOURCE_GAMEMEAT)
    disable_if(BUILDING_FISHING_WHARF, RESOURCE_FISH)
    disable_if(BUILDING_CLAY_PIT, RESOURCE_CLAY)
    disable_if(BUILDING_WOOD_CUTTERS, RESOURCE_TIMBER)
    disable_if(BUILDING_REED_GATHERER, RESOURCE_REEDS)
    disable_if(BUILDING_STONE_QUARRY, RESOURCE_STONE)
    disable_if(BUILDING_LIMESTONE_QUARRY, RESOURCE_LIMESTONE)
    disable_if(BUILDING_GRANITE_QUARRY, RESOURCE_GRANITE)
    disable_if(BUILDING_SANDSTONE_QUARRY, RESOURCE_SANDSTONE)
    disable_if(BUILDING_COPPER_MINE, RESOURCE_COPPER)
    disable_if(BUILDING_GEMSTONE_MINE, RESOURCE_GEMS)
}

building_menu_ctrl.enable_correct_palace_tier = function() {
    var rank = __scenario_player_rank()
    if (rank < 6) {
        building_menu_ctrl.use_building(BUILDING_TOWN_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_CITY_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_FAMILY_MANSION, false)
        building_menu_ctrl.use_building(BUILDING_DYNASTY_MANSION, false)
    } else if (rank < 8) {
        building_menu_ctrl.use_building(BUILDING_VILLAGE_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_CITY_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_PERSONAL_MANSION, false)
        building_menu_ctrl.use_building(BUILDING_DYNASTY_MANSION, false)
    } else {
        building_menu_ctrl.use_building(BUILDING_VILLAGE_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_TOWN_PALACE, false)
        building_menu_ctrl.use_building(BUILDING_PERSONAL_MANSION, false)
        building_menu_ctrl.use_building(BUILDING_FAMILY_MANSION, false)
    }
}

building_menu_ctrl.update_temple_complexes = function() {
    if (__gameplay_multiple_temple_complexes()) {
        return
    }

    var has_complex = __city_has_temple_complex()
    var complex_id = __city_temple_complex_id()
    var types_count = __city_temple_complex_types_count()

    if (has_complex) {
        for (var i = 0; i < types_count; i++) {
            building_menu_ctrl.set_visible(__city_temple_complex_type_at(i), false)
        }

        var has_altar = __city_temple_complex_has_upgrade(complex_id, 1)
        var altar_count = __city_temple_complex_allowed_altar_count(complex_id)
        for (var i = 0; i < altar_count; i++) {
            building_menu_ctrl.set_visible(__city_temple_complex_allowed_altar_at(complex_id, i), !has_altar)
        }

        var has_oracle = __city_temple_complex_has_upgrade(complex_id, 2)
        var oracle_count = __city_temple_complex_allowed_oracle_count(complex_id)
        for (var i = 0; i < oracle_count; i++) {
            building_menu_ctrl.set_visible(__city_temple_complex_allowed_oracle_at(complex_id, i), !has_oracle)
        }

        if (has_altar && has_oracle) {
            building_menu_ctrl.use_building(BUILDING_MENU_TEMPLE_COMPLEX, false)
        }
    } else {
        for (var i = 0; i < types_count; i++) {
            building_menu_ctrl.set_visible(__city_temple_complex_type_at(i), true)
        }

        var max_type = __building_type_max()
        for (var t = 0; t < max_type; t++) {
            var cfg = get_building_config_by_id(t)
            if (cfg && cfg.needs && (cfg.needs.altar || cfg.needs.oracle)) {
                building_menu_ctrl.set_visible(t, false)
            }
        }
    }
}

building_menu_ctrl.update_gods_available = function(god, available) {
    var god_buildings = [
        [BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS],
        [BUILDING_TEMPLE_RA,     BUILDING_SHRINE_RA],
        [BUILDING_TEMPLE_PTAH,   BUILDING_SHRINE_PTAH],
        [BUILDING_TEMPLE_SETH,   BUILDING_SHRINE_SETH],
        [BUILDING_TEMPLE_BAST,   BUILDING_SHRINE_BAST],
    ]
    if (god >= 0 && god < god_buildings.length) {
        var buildings = god_buildings[god]
        for (var i = 0; i < buildings.length; i++) {
            building_menu_ctrl.use_building(buildings[i], available)
        }
    }
}

building_menu_ctrl.update = function(stage) {
    if (stage == "disable_all") {
        building_menu_ctrl.set_all(false)
    } else if (stage == "stage_normal") {
        building_menu_ctrl.set_all(false)
        var max_type = __building_type_max()
        for (var i = 0; i < max_type; i++) {
            if (__scenario_building_allowed(i)) {
                building_menu_ctrl.use_building(i, true)
            }
        }
        building_menu_ctrl.disable_resources()
        building_menu_ctrl.enable_correct_palace_tier()
        building_menu_ctrl.update_temple_complexes()
    } else if (stage == "enable_all") {
        building_menu_ctrl.set_all(true)
    }

    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id == BUILDING_MENU_DEFAULT) {
            var group = building_menu[i]
            for (var j = 0; j < group.items.length; j++) {
                building_menu_ctrl.use_building(group.items[j], true)
            }
            break
        }
    }

    emit event_building_menu_changed{ temp: true }
}

[es=event_building_menu_update]
function building_menu_ctrl_on_update(ev) {
    building_menu_ctrl.update(ev.stage)
}

[es=event_religion_god_status_update]
function building_menu_ctrl_on_god_status(ev) {
    building_menu_ctrl.update_gods_available(ev.god, ev.status != 0)
}

[es=event_use_building]
function building_menu_ctrl_on_use_building(ev) {
    building_menu_ctrl.use_building(ev.type, ev.en)
}
