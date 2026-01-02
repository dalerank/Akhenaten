log_info("akhenaten: game started")

game {
    @absolute_day { get: __game_absolute_day }
    @version { get: __game_version }

    screen {
        @w { get: __game_screen_width }
        @h { get: __game_screen_height }
    }

    @difficulty { get: __game_difficulty }
}