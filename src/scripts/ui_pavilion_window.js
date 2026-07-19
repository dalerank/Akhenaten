log_info("akhenaten: ui pavilion window")

[es=building_info_window]
info_window_pavilion {
    related_buildings [BUILDING_PAVILLION]
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        title        : text({pos: [0, 16], text:"${building.name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel  : inner_panel({pos : [16, 116], size: [27, 8] }),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play2_text   : text({pos: [32, 182], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play3_text   : text({pos: [32, 202], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 122] }),
        workers_text : text({pos: [70, 130], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
        workers_desc : text({pos: [70, 126 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

[es=(info_window_pavilion, init)]
function info_window_pavilion_on_init(window) {
    var b = city.get_entertainment_building(window.bid)
    if (!b) {
        return
    }
    var gid = b.meta_text_id
    var d = b
    var workers_group = gid
    var workers_id = 0

    if (!b.has_road_access) {
        workers_group = 69
        workers_id = 25
    } else if (b.num_workers <= 0) {
        workers_id = 10
    } else if (!d.num_shows) {
        workers_id = 2
    } else if (d.num_shows == 2) {
        workers_id = 3
    } else if (d.dancer_visited && d.juggler_visited && !d.musician_visited) {
        workers_id = 5
    } else if (d.dancer_visited && d.musician_visited && !d.juggler_visited) {
        workers_id = 4
    } else if (!d.dancer_visited && d.musician_visited && d.juggler_visited) {
        workers_id = 6
    } else if (d.juggler_visited && !d.dancer_visited && !d.musician_visited) {
        workers_id = 7
    } else if (d.musician_visited && (!d.dancer_visited || !d.juggler_visited)) {
        workers_id = 8
    } else if (d.musician_visited && !d.juggler_visited) {
        workers_id = 9
    }

    window.workers_desc.text = __loc(workers_group, workers_id)

    if (d.juggler_visited > 0) {
        window.play_text.text = __loc(gid, 12) + " " + __loc(8, 44) + " " + d.juggler_visited
    } else {
        window.play_text.text = __loc(gid, 11)
    }

    if (d.musician_visited > 0) {
        window.play2_text.text = __loc(gid, 14) + " " + __loc(8, 44) + " " + d.musician_visited + "\n" + __loc(72, 7 + d.play_index)
    } else {
        window.play2_text.text = __loc(gid, 13)
    }

    if (d.dancer_visited > 0) {
        window.play3_text.text = __loc(gid, 16) + " " + __loc(8, 44) + " " + d.dancer_visited
    } else {
        window.play3_text.text = __loc(gid, 15)
    }
}
