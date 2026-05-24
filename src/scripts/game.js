log_info("akhenaten: game started")

game = extend(__game, {
    // -> pending_load_type
    // -> pending_save_type
    // -> pending_delete_type
    // -> mission_choice_open_scenario_id
    // -> debug_properties
    // -> debug_terrain_paint
    // -> paused

    mission_briefing_scenario_id : 0
    mission_briefing_is_review : false

    @absolute_day { get: __game_absolute_day }
    @simtime_year { get: __game_simtime_year }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }
    @writing_video { get: __game_writing_video }
    @debug_render_mode { get: __game_debug_render_mode, set: __game_set_debug_render_mode }
    @last_autosave { get: __game_get_last_autosave }
    @session_active { get: __game_session_active }
    @session_last_loaded_kind { get: __game_session_last_loaded_kind }
    @session_last_loaded_mission { get: __game_session_last_loaded_mission }
    @dynasty_name {
        get: function() { return game_features.gameopt_player_name },
        set: function(name) { game_features.gameopt_player_name = name }
    }
    @gods_enabled { get: __game_gods_enabled }
    @locale_year_before_ad { get: __game_locale_year_before_ad }

    toggle_writing_video: __game_toggle_writing_video
    save_screenshot: __game_save_screenshot

    languages {
        @count : { get: __game_languages_count }
        @current { get: __game_language_current, set: __game_language_set_current }

        get_caption : __game_language_caption
        get_id : __game_language_id
    }

    file_exists: __game_file_exists
    load_savegame: __game_load_savegame
    write_savegame: __game_write_savegame
    delete_savegame: __game_delete_savegame
    delete_map: __game_delete_map
    get_last_loaded_file: __game_get_last_loaded_file
    editor_load_scenario: __game_editor_load_scenario
    editor_write_scenario: __game_editor_write_scenario
    last_advisor: ADVISOR_NONE
})

screen = extend(__screen, {
    @is_fullscreen_only { get: __game_is_fullscreen_only }
})

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    __property_setter: function(property, value) { __game_feature_set(property, value) }

    @gameui_hide_new_game_top_menu {}
    @gameui_empire_city_old_names {}
    @gameopt_monthly_autosave {}
    @gameopt_tooltips_mode {}
    @gameopt_warnings {}
    @gameopt_gods_enabled {}
    @gameopt_victory_video {}
    @gameopt_pyramid_speedup {}
    @gameopt_fullscreen {}
    @gameopt_last_save_filename {  }
    @gameopt_last_player {  }
    @gameopt_player_name {  }
    @gameopt_sound_effects_enabled {}
    @gameopt_sound_effects_volume {}
    @gameopt_sound_music_enabled {}
    @gameopt_sound_music_volume {}
    @gameopt_sound_speech_enabled {}
    @gameopt_sound_speech_volume {}
    @gameopt_sound_city_enabled {}
    @gameopt_sound_city_volume {}
    @gameopt_game_speed {}
    @gameui_sidebar_info {}
    @gameopt_scroll_speed {}
    @gameopt_middle_mouse_camera_pan {}
    @gameopt_middle_mouse_pan_speed {}
    @gameopt_clouds_speed {}
    @gameplay_change_random_mine_or_pit_collapses_take_money {}
    @gameopt_display_size {}
    @gameplay_change_multiple_temple_complexes {}
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

[es=event_toggle_pause]
function event_toggle_pause_handler(ev) {
    game.paused = !game.paused
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