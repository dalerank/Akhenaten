log_info("akhenaten: ui well info window started")

[es=building_info_window]
well_info_window {
    related_buildings [BUILDING_WELL]
    ui : {
        background : outer_panel({size: [29, 14]}),
        title      : text({pos: [0, 12], size: [px(28), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align: "center", text: "${loc.well_info_title}"}),
        text       : text({pos: [32, 56], wrap: px(27), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline: true}),
    }
}

[es=(well_info_window, init)]
function well_info_window_on_init(window) {
    var well = city.get_well(window.bid)
    var well_necessity = well.necessity_status(2)
    var text_key = ""
    if (well_necessity == WELL_NECESSARY) {
        text_key = "#well_info_necessary"
    } else if (well_necessity == WELL_UNNECESSARY_FOUNTAIN) {
        text_key = "#well_info_unneeded_fountain"
    } else if (well_necessity == WELL_UNNECESSARY_NO_HOUSES) {
        text_key = "#well_info_unneeded_no_houses"
    }

    if (text_key) {
        window.text.text = __loc(text_key)
    }
}
