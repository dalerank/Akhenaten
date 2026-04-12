log_info("akhenaten: sidebar extra started")

sidebar_window_extra {
  ui {
    background        : inner_panel({pos[0, 480], size[10, 19]})

    speed_header      : text({pos[11, 485], text:"${loc.sidebar_speed_header}", font:FONT_NORMAL_WHITE_ON_DARK})
    speed_current     : text({pos[65, 480 + 28], font:FONT_NORMAL_WHITE_ON_DARK})
    dec_speed         : arrowdown({pos[11, 470 + 30], tiny:false})
    inc_speed         : arrowup({pos[35, 470 + 30], tiny:false})

    unemp_header      : text({pos[11, 480 + 50], text:[68, 135], font:FONT_NORMAL_WHITE_ON_DARK})
    unemp_current     : text({pos[11, 480 + 70], font:FONT_NORMAL_WHITE_ON_DARK})

    population_header : text({pos[11, 480 + 90], font:FONT_NORMAL_WHITE_ON_DARK})
    population_current: text({pos[11, 480 + 110]})

    culture_header    : text({pos[11, 480 + 130], font:FONT_NORMAL_WHITE_ON_DARK})
    culture_current   : text({pos[11, 480 + 150]})

    prosperity_header : text({pos[11, 480 + 170], font:FONT_NORMAL_WHITE_ON_DARK})
    prosperity_current: text({pos[11, 480 + 190]})

    monument_header   : text({pos[11, 480 + 210], font:FONT_NORMAL_WHITE_ON_DARK})
    monument_current  : text({pos[11, 480 + 230]})

    kingdom_header    : text({pos[11, 480 + 250], font:FONT_NORMAL_WHITE_ON_DARK})
    kingdom_current   : text({pos[11, 480 + 270]})
  }
}

function sidebar_extra_mission_target(winningRaw) {
    if (scenario.is_open_play) {
        return 0
    }
    return winningRaw
}

function sidebar_extra_objective_row(headerEl, currentEl, headerGroup, headerId, current, targetRaw) {
    var t = sidebar_extra_mission_target(targetRaw)
    headerEl.text = __loc(headerGroup, headerId)
    var met = (t <= 0) || (current >= t)
    currentEl.font = met ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW
    currentEl.text = current + " (" + t + ")"
}

[es=(sidebar_window_extra, ui_draw_foreground)]
function sidebar_window_extra_ui_draw_foreground(window) {
    window.speed_current.text = game.game_speed + "%"
    window.unemp_current.text = city.labor.unemployment_percentage + "% (" + city.workers_diff + ")"

    sidebar_extra_objective_row(window.population_header, window.population_current, 53, 6, city.population, city.winning.population)
    sidebar_extra_objective_row(window.culture_header, window.culture_current, 53, 1, city.rating.culture, city.winning.culture)
    sidebar_extra_objective_row(window.prosperity_header, window.prosperity_current, 53, 2, city.rating.prosperity, city.rating.winning.prosperity)
    sidebar_extra_objective_row(window.monument_header, window.monument_current, 53, 3, city.rating.monument, city.winning.monument)
    sidebar_extra_objective_row(window.kingdom_header, window.kingdom_current, 53, 4, city.rating.kingdom, city.winning.kingdom)
}
