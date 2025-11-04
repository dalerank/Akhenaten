log_info("akhenaten: game.js started")

game {
    [property]
    absolute_day { get: function() { return __game_absolute_day() } }

    [property]
    version { get: function() { return __game_version() } }

    screen {
        [property]
        w { get: function() { return __game_screen_width() } }

        [property]
        h { get: function() { return __game_screen_height() } }
    }
}