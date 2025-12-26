log_info("akhenaten: game.js started")

game {
    [property]
    absolute_day { get: __game_absolute_day }

    [property]
    version { get: __game_version }

    screen {
        [property]
        w { get: __game_screen_width }

        [property]
        h { get: __game_screen_height }
    }

    [property]
    difficulty { get: __game_difficulty }
}

player {
    [property]
    name { get: __city_player_name }

    [property]
    salary_rank { get: __player_salary_rank }

    [property]
    salary_amount { get: __player_salary_amount }
}