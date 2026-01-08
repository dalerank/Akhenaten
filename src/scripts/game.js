log_info("akhenaten: game started")

game {
    @absolute_day { get: __game_absolute_day }
    @version { get: __game_version }

    screen {
        @w { get: __game_screen_width }
        @h { get: __game_screen_height }
        @is_fullscreen_only { get: __game_is_fullscreen_only }
    }

    @difficulty { get: __game_difficulty }
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    @gameui_hide_new_game_top_menu {}
}