log_info("akhenaten: ui bandstand window")

[es=building_info_window]
info_window_bandstand {
    related_buildings [BUILDING_BANDSTAND]
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        title        : text({pos: [0, 16], text:"${building.name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel  : inner_panel({pos : [16, 116], size: [27, 8] }),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play2_text   : text({pos: [32, 182], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 122] }),
        workers_text : text({pos: [70, 130], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
        workers_desc : text({pos: [70, 126 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

[es=(info_window_bandstand, init)]
function info_window_bandstand_on_init(window) {
    var b = city.get_entertainment_building(window.bid)
    if (!b) {
        return
    }
    var gid = b.meta_text_id
    var d = b
    var reason = { group: gid, id: 1 }
    if (!b.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 6
    } else if (!d.num_shows) {
        reason.id = 2
    } else if (d.num_shows == 2) {
        reason.id = 3
    } else if (d.juggler_visited) {
        reason.id = 5
    } else if (d.musician_visited) {
        reason.id = 4
    }
    window.warning_text.text = __loc(reason.group, reason.id)

    if (d.juggler_visited > 0) {
        window.play_text.text = __loc(gid, 10) + " " + __loc(8, 44) + " " + d.juggler_visited
    } else {
        window.play_text.text = __loc(gid, 9)
    }

    if (d.musician_visited > 0) {
        window.play2_text.text = __loc(gid, 8) + " " + __loc(8, 44) + " " + d.musician_visited + "\n" + __loc(72, 7 + d.play_index)
    } else {
        window.play2_text.text = __loc(gid, 7)
    }
}
