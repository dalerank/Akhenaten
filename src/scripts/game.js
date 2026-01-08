log_info("akhenaten: game started")

game {
    @monthly_autosave { get: __game_monthly_autosave, set: __game_set_monthly_autosave }
    @absolute_day { get: __game_absolute_day }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }

    screen {
        @w { get: __game_screen_width }
        @h { get: __game_screen_height }
        @is_fullscreen_only { get: __game_is_fullscreen_only }
    }
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    @gameui_hide_new_game_top_menu {}
}