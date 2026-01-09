log_info("akhenaten: game started")

game {
    @monthly_autosave { get: __game_monthly_autosave, set: __game_set_monthly_autosave }
    @absolute_day { get: __game_absolute_day }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }
    @tooltips_mode { get: __game_tooltips_mode, set: __game_set_tooltips_mode }
    @warnings { get: __game_warnings, set: __game_set_warnings }
    @debug_properties { get: __game_debug_properties }
    @writing_video { get: __game_writing_video }
    
    screen {
        @w { get: __game_screen_width }
        @h { get: __game_screen_height }
        @is_fullscreen_only { get: __game_is_fullscreen_only }
    }
    
    toggle_writing_video: __game_toggle_writing_video
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    __property_setter: function(property, value) { __game_feature_set(property, value) }
    @gameui_hide_new_game_top_menu {}
    @gameui_empire_city_old_names {}
}