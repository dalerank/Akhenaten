log_info("akhenaten: game started")

game {
    __property_getter: function(property) { return __game_get_property(property) }

    @monthly_autosave { set: __game_set_monthly_autosave }
    @absolute_day { get: __game_absolute_day }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }
    @tooltips_mode { get: __game_tooltips_mode, set: __game_set_tooltips_mode }
    @warnings { get: __game_warnings, set: __game_set_warnings }
    @debug_properties { get: __game_debug_properties }
    @writing_video { get: __game_writing_video }
    @debug_render_mode { get: __game_debug_render_mode, set: __game_set_debug_render_mode }
    @game_speed { set: __game_set_game_speed }
    @scroll_speed { set: __game_set_scroll_speed }
    @last_autosave { get: __game_get_last_autosave }
    @session_active { get: __game_session_active }
    @dynasty_name { get: __game_get_player_name, set: __game_set_player_name }

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
}

scenario {
    has_animals: __scenario_has_animals
    flotsam_enabled: __scenario_flotsam_enabled
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    __property_setter: function(property, value) { __game_feature_set(property, value) }
    @gameui_hide_new_game_top_menu {}
    @gameui_empire_city_old_names {}
    @gameopt_last_save_filename {  }
    @gameopt_last_player {  }
    @count { get: __game_features_count }
}

game_features.name = function(index) {
    return __game_feature_name(index)
}

game_features.get = function(index) {
    return __game_feature_by_idx(index)
}

game_features.text = function(index) {
    return __game_feature_text(index)
}