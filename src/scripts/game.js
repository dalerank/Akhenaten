log_info("akhenaten: game started")

game {
    __property_getter: function(property) { return __game_get_property(property) }

    @monthly_autosave { get: __game_get_monthly_autosave, set: __game_set_monthly_autosave }
    @absolute_day { get: __game_absolute_day }
    @simtime_year { get: __game_simtime_year }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }
    @debug_properties { get: __game_debug_properties }
    @writing_video { get: __game_writing_video }
    @debug_render_mode { get: __game_debug_render_mode, set: __game_set_debug_render_mode }
    @last_autosave { get: __game_get_last_autosave }
    @session_active { get: __game_session_active }
    @session_last_loaded_kind { get: __game_session_last_loaded_kind }
    @session_last_loaded_mission { get: __game_session_last_loaded_mission }
    @dynasty_name { get: __game_get_player_name, set: __game_set_player_name }
    @pending_load_type { }
    @pending_save_type { }
    @gods_enabled { get: __game_gods_enabled }

    screen {
        @w { get: __game_screen_width }
        @h { get: __game_screen_height }
        @is_fullscreen_only { get: __game_is_fullscreen_only }
    }

    toggle_writing_video: __game_toggle_writing_video
    make_screenshot: __game_make_screenshot

    languages {
        @count : { get: __game_languages_count }
        @current { get: __game_language_current, set: __game_language_set_current }

        get_caption : __game_language_caption
        get_id : __game_language_id
    }

    file_exists: __game_file_exists
    load_savegame: __game_load_savegame
    write_savegame: __game_write_savegame
    get_last_loaded_file: __game_get_last_loaded_file
    editor_load_scenario: __game_editor_load_scenario
    editor_write_scenario: __game_editor_write_scenario
}

scenario {
    has_animals: __scenario_has_animals
    flotsam_enabled: __scenario_flotsam_enabled
    @is_open_play { get: __scenario_is_open_play }
    building_allowed: __scenario_building_allowed
    kingdom_supplies_grain: __scenario_kingdom_supplies_grain
    @start_year { get: __scenario_start_year }
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    __property_setter: function(property, value) { __game_feature_set(property, value) }

    @gameui_hide_new_game_top_menu {}
    @gameui_empire_city_old_names {}
    @gameopt_last_save_filename {  }
    @gameopt_last_player {  }
    @gameopt_sound_effects_enabled {}
    @gameopt_sound_effects_volume {}
    @gameopt_sound_music_enabled {}
    @gameopt_sound_music_volume {}
    @gameopt_sound_speech_enabled {}
    @gameopt_sound_speech_volume {}
    @gameopt_sound_city_enabled {}
    @gameopt_sound_city_volume {}
    @gameopt_game_speed {}
    @gameopt_scroll_speed {}
    @gameopt_middle_mouse_camera_pan {}
    @gameopt_middle_mouse_pan_speed {}
    @gameopt_clouds_speed {}
    @count { get: __game_features_count }
}

game_features.name = __game_feature_name
game_features.text = __game_feature_text
game_features.get = __game_feature_get
game_features.set = __game_feature_set
game_features.count = __game_features_count

function calc_bound_scroll_speed(v, lo, hi) {
    if (v < lo) { return lo }
    if (v > hi) { return hi }
    return v
}

[es=event_change_scroll_speed]
function event_change_scroll_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_scroll_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_scroll_speed = s
}

[es=event_change_middle_mouse_pan_speed]
function event_change_middle_mouse_pan_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_middle_mouse_pan_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_middle_mouse_pan_speed = s
}

[es=event_change_clouds_speed]
function event_change_clouds_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_clouds_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_clouds_speed = s
}

[es=event_change_gamespeed]
function event_change_gamespeed_handler(ev) {
    function calc_bound_game_speed(v, lo, hi) {
        if (v < lo) { return lo }
        if (v > hi) { return hi }
        return v
    }

    var s = Math.round(game_features.gameopt_game_speed)
    if (ev.increase) {
        if (s >= 100) {
            if (s < 1000) { s += 100 }
        } else {
            s = calc_bound_game_speed(s + 10, 10, 100)
        }
    } else {
        if (s > 100) {
            s -= 100
        } else {
            s = calc_bound_game_speed(s - 10, 10, 100)
        }
    }
    game_features.gameopt_game_speed = s
}