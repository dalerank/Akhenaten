log_info("akhenaten: game_features_debug")

var game_features_debug_filter = ""

function game_features_debug_match_ci(str, substr) {
    if (!substr || substr.length === 0) {
        return true
    }
    if (!str || str.length === 0) {
        return false
    }
    return str.toLowerCase().indexOf(substr.toLowerCase()) >= 0
}

function game_features_debug_matches(name, filter) {
    if (!filter || filter.length === 0) {
        return true
    }
    if (game_features_debug_match_ci(name, filter)) {
        return true
    }
    var text = game_features.text(name)
    if (text && game_features_debug_match_ci(text, filter)) {
        return true
    }
    return false
}

function game_features_debug_draw_filter() {
    imgui.text("Filter:")
    imgui.same_line()
    imgui.set_next_item_width(imgui.content_region_avail_x() - 100)
    game_features_debug_filter = imgui.input_text("##filter", game_features_debug_filter)
    imgui.same_line()
    if (imgui.button("Clear")) {
        game_features_debug_filter = ""
    }
}

function game_features_debug_count_by_type(type_id) {
    var count = 0
    var n = game_features.count
    for (var i = 0; i < n; i++) {
        var name = game_features.name(i)
        if (game_features.type(name) === type_id) {
            count++
        }
    }
    return count
}

function game_features_debug_count_filtered(type_id, filter) {
    var count = 0
    var n = game_features.count
    for (var i = 0; i < n; i++) {
        var name = game_features.name(i)
        if (game_features.type(name) !== type_id) {
            continue
        }
        if (!game_features_debug_matches(name, filter)) {
            continue
        }
        count++
    }
    return count
}

function game_features_debug_count_filtered_all(filter) {
    var count = 0
    var n = game_features.count
    for (var i = 0; i < n; i++) {
        var name = game_features.name(i)
        if (game_features_debug_matches(name, filter)) {
            count++
        }
    }
    return count
}

[es=event_draw_debug_properties]
function game_features_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Game Features")) {
        return
    }

    game_features_debug_draw_filter()

    var total_count = game_features.count
    var bool_count = game_features_debug_count_by_type(setting_bool)
    var string_count = game_features_debug_count_by_type(setting_string)
    var float_count = game_features_debug_count_by_type(setting_float)
    var vec2i_count = game_features_debug_count_by_type(setting_vec2i)

    imgui.begin_table("GameFeatures", 2, imgui.table_flags_debug_props())
    imgui.property_input("total_features", total_count)
    imgui.property_input("bool_features", bool_count)
    imgui.property_input("string_features", string_count)
    if (float_count > 0) {
        imgui.property_input("float_features", float_count)
    }
    if (vec2i_count > 0) {
        imgui.property_input("vec2i_features", vec2i_count)
    }
    imgui.end_table()

    var filtered_bool_count = game_features_debug_count_filtered(setting_bool, game_features_debug_filter)
    var filtered_string_count = game_features_debug_count_filtered(setting_string, game_features_debug_filter)

    if (imgui.tree_node_ex2("Bool Features", "Bool Features (" + filtered_bool_count + ")")) {
        imgui.begin_table("BoolFeatures", 2, imgui.table_flags_debug_props())
        var n = game_features.count
        for (var i = 0; i < n; i++) {
            var name = game_features.name(i)
            if (game_features.type(name) !== setting_bool) {
                continue
            }
            if (!game_features_debug_matches(name, game_features_debug_filter)) {
                continue
            }
            __debug_feature_bool(name)
        }
        imgui.end_table()
        imgui.tree_pop()
    }

    if (imgui.tree_node_ex2("String Features", "String Features (" + filtered_string_count + ")")) {
        imgui.begin_table("StringFeatures", 2, imgui.table_flags_debug_props())
        n = game_features.count
        for (i = 0; i < n; i++) {
            name = game_features.name(i)
            if (game_features.type(name) !== setting_string) {
                continue
            }
            if (!game_features_debug_matches(name, game_features_debug_filter)) {
                continue
            }
            imgui.property_input(name, game_features.get(name))
        }
        imgui.end_table()
        imgui.tree_pop()
    }

    var filtered_total = game_features_debug_count_filtered_all(game_features_debug_filter)
    if (imgui.tree_node_ex2("All Features (Detailed)", "All Features (Detailed) (" + filtered_total + ")")) {
        n = game_features.count
        for (i = 0; i < n; i++) {
            name = game_features.name(i)
            if (!game_features_debug_matches(name, game_features_debug_filter)) {
                continue
            }

            if (!imgui.tree_node_ex(name)) {
                continue
            }

            imgui.begin_table(name, 2, imgui.table_flags_debug_props())
            imgui.property_input("name", name)
            var feature_text = game_features.text(name)
            if (feature_text && feature_text.length > 0) {
                imgui.property_input("text", feature_text)
            }

            var default_value = game_features.default(name)
            if (default_value !== null && default_value !== undefined) {
                imgui.property_input("default", default_value)
            }

            var feature_type = game_features.type(name)
            if (feature_type === setting_bool) {
                __debug_feature_bool(name, "current_value")
            } else if (feature_type === setting_string) {
                imgui.property_input("current_value", game_features.get(name))
            }

            imgui.property_input("type", game_features.type_name(feature_type))
            imgui.end_table()
            imgui.tree_pop()
        }
        imgui.tree_pop()
    }

    imgui.tree_pop()
}
