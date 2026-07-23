log_info("akhenaten: ui booth window")

[es=building_info_window]
info_window_booth {
    related_buildings [BUILDING_BOOTH]
    ui : baseui(building_info_window, {
        background   : outer_panel({pos: [0, 0], size: [29, 16]}),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        inner_panel  : inner_panel({pos : [16, 110], size: [27, 6],
                                        ui : {
                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                            workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                            workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                        }
                                  }),
    })
}

[es=(info_window_booth, init)]
function info_window_booth_on_init(window) {
    var b = city.get_entertainment_building(window.bid)
    if (!b) {
        return
    }
    var gid = b.meta_text_id
    var reason = { group: gid, id: 1 }
    if (!b.has_road_access) {
        reason = { key: "#building_no_road_access" }
    } else if (b.num_workers <= 0) {
        reason.id = 4
    } else if (!b.num_shows) {
        reason.id = 2
    } else if (b.juggler_visited) {
        reason.id = 3
    }
    window.warning_text.text = __loc(reason)

    if (b.juggler_visited > 0) {
        window.play_text.text = __loc(gid, 6) + " " + __loc(8, 44) + " " + b.juggler_visited
    } else {
        window.play_text.text = __loc(gid, 5)
    }
}
