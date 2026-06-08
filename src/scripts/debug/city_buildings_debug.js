log_info("akhenaten: city_buildings_debug")

function building_config_class_name(type) {
    var name = __building_static_config_name(type)
    if (!name || name.length === 0) {
        return null
    }
    if (name.indexOf("building_") === 0) {
        return name.substring(9)
    }
    if (name.indexOf("build_planner_") === 0) {
        return name.substring(14)
    }
    return name
}

function building_type_debug_label(type) {
    var name = building_config_class_name(type)
    return name ? name : ("type_" + type)
}

function city_buildings_debug_is_pickable(type) {
    var cfg = get_building_config_by_id(type)
    if (!cfg) {
        return false
    }
    return cfg.show_in_debug !== false
}

function city_buildings_debug_building_allowed(type, label) {
    var allowed = __scenario_building_allowed(type)
    var next = imgui.property_input(label, allowed)
    if (next != allowed) {
        city.use_building(type, next)
        emit event_building_menu_changed{ temp: true }
    }
}

function city_buildings_debug_match_filter(type, filter) {
    if (!filter || filter.length === 0) {
        return true
    }
    return building_config_class_name(type).toLowerCase().indexOf(filter.toLowerCase()) >= 0
}

function city_buildings_debug_count_pickable(filter) {
    var count = 0
    for (var t = BUILDING_NONE + 1; t < BUILDING_MAX; t++) {
        if (!city_buildings_debug_is_pickable(t)) {
            continue
        }
        if (city_buildings_debug_match_filter(t, filter)) {
            count++
        }
    }
    return count
}

function city_buildings_debug_stats() {
    var valid_count = 0
    for (var bid = 1; bid < MAX_BUILDINGS; bid++) {
        if (__building_is_valid(bid)) {
            valid_count++
        }
    }
    var total_slots = MAX_BUILDINGS - 1
    return {
        total_slots: total_slots,
        valid_buildings: valid_count,
        invalid_slots: total_slots - valid_count,
    }
}

function city_buildings_debug_type_counts() {
    var counts = {}
    for (var bid = 1; bid < MAX_BUILDINGS; bid++) {
        if (!__building_is_valid(bid)) {
            continue
        }
        var type = __building_type(bid)
        if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
            continue
        }
        if (!counts[type]) {
            counts[type] = 0
        }
        counts[type]++
    }
    return counts
}

[es=event_draw_debug_properties]
function city_buildings_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("City Buildings")) {
        return
    }

    var stats = city_buildings_debug_stats()
    imgui.begin_table("CityBuildings", 2, imgui.table_flags_debug_props())
    imgui.property_input("total_slots", stats.total_slots)
    imgui.property_input("valid_buildings", stats.valid_buildings)
    imgui.property_input("invalid_slots", stats.invalid_slots)
    imgui.end_table()

    if (imgui.tree_node_ex("Building Counts")) {
        var counts = city_buildings_debug_type_counts()
        var type_keys = Object.keys(counts)
        imgui.begin_table("CityBuildingCounts", 2, imgui.table_flags_debug_props())
        for (var i = 0; i < type_keys.length; i++) {
            var type_id = parseInt(type_keys[i])
            imgui.property_input(building_type_debug_label(type_id), counts[type_keys[i]])
        }
        imgui.end_table()
        imgui.tree_pop()
    }

    imgui.tree_pop()
}

var city_buildings_debug_filter = ""

[es=event_draw_debug_properties]
function city_buildings_debug_draw_allowed_buildings(ev) {
    var filtered_pickable = city_buildings_debug_count_pickable(city_buildings_debug_filter)
    if (!imgui.tree_node_ex2("AllowedBuildings", "Allowed Buildings (" + filtered_pickable + ")")) {
        return
    }

    imgui.text("Filter:")
    imgui.same_line()
    imgui.set_next_item_width(imgui.content_region_avail_x() - 100)
    city_buildings_debug_filter = imgui.input_text("##allowed_buildings_filter", city_buildings_debug_filter)
    imgui.same_line()
    if (imgui.button("Clear")) {
        city_buildings_debug_filter = ""
    }

    imgui.begin_table("AllowedBuildingsTable", 2, imgui.table_flags_debug_props())
    for (var t = BUILDING_NONE + 1; t < BUILDING_MAX; t++) {
        if (!city_buildings_debug_is_pickable(t)) {
            continue
        }
        if (!city_buildings_debug_match_filter(t, city_buildings_debug_filter)) {
            continue
        }
        city_buildings_debug_building_allowed(t, building_type_debug_label(t))
    }
    imgui.end_table()
    imgui.tree_pop()
}
