log_info("akhenaten: ui abu simbel info window")

[es=building_info_window]
info_window_abu_simbel {
    related_buildings [BUILDING_ABU_SIMBEL]
    ui {
        background     : outer_panel({size: [29, 16]}),
        title          : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text   : text({pos: [32, 56], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_text  : text({pos: [32, 136], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help    : help_button({}),
        button_close   : close_button({}),
    }
}

// OG guild_text: the stonemasons it reads belong to the Caesareum report, so they are always 0 here
// and only the guild's own state counts.
function info_window_abu_simbel_guild_text(mon) {
    if (mon.has_free_spot(FIGURE_STONEMASON)) {
        if (!city.count_total_buildings(BUILDING_STONEMASONS_GUILD)) { return 14 }
        if (!city.count_active_buildings(BUILDING_STONEMASONS_GUILD)) { return 18 }
    }
    if (mon.has_free_spot(FIGURE_CARPENTER)) {
        if (!city.count_total_buildings(BUILDING_CARPENTERS_GUILD)) { return 16 }
        if (!city.count_active_buildings(BUILDING_CARPENTERS_GUILD)) { return 20 }
    }
    return 0
}

// The main record's phase is the stage; MONUMENT_FINISHED (-1) once all phases_total stages are done.
function info_window_abu_simbel_stage(mon) {
    var phase = mon.phase()
    var total = mon.phases_total()
    return (phase === -1 || phase >= total) ? total : Math.max(phase, 0)
}

// OG window_building_draw_abu_simbel status line.
function info_window_abu_simbel_status_text(mon, part) {
    if (__map_citizen_grid(mon.access_point()) < 0 || part.distance_from_entry == 0) {
        return 149
    }
    var guild = info_window_abu_simbel_guild_text(mon)
    if (guild) {
        return guild
    }
    return info_window_abu_simbel_stage(mon) < mon.phases_total() ? 141 : 142
}

[es=(info_window_abu_simbel, init)]
function info_window_abu_simbel_on_init(window) {
    var mon = city.get_monument(window.bid)
    var part = city.get_building(window.bid)
    if (!mon || !part) {
        return
    }

    window.warning_text.text = __loc(178, info_window_abu_simbel_status_text(mon, part))

    var total = mon.phases_total()
    var pct = Math.floor(info_window_abu_simbel_stage(mon) * 100 / total)
    if (pct >= 100) {
        window.progress_text.text = ""
        return
    }
    var line = __loc(178, 61).split("[monument_name]").join(__loc(178, 82))
    window.progress_text.text = line.split("[percent_complete]").join(pct + "%")
}
