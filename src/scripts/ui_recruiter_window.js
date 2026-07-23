log_info("akhenaten: ui recruiter info window started")

function recruiter_info_window_text_tower_button() {
    var bid = city.object_info.bid
    return (__building_recruiter_get_priority(bid) == 0) ? "x" : ""
}

function recruiter_info_window_text_fort_button() {
    var bid = city.object_info.bid
    return (__building_recruiter_get_priority(bid) == 1) ? "x" : ""
}

[es=building_info_window]
info_window_recruiter {
    related_buildings [BUILDING_RECRUITER]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 20]}),
        warning_text  : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        icon_weapon   : resource_icon({pos:[24, 100], resource:RESOURCE_WEAPONS  }),
        storage_state : text({pos: [46, 104], text:"${8.10} ${building.first_material_stored}", font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        progress_desc : text({pos: [32, 104], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel   : inner_panel({pos : [16, 125], size: [27, 5],
                                                ui : {
                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                    workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                }
                                          }),
        priority_text : text({pos: [46, 210], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:50, id:21} }),
        tower_text    : text({pos: [74, 232], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:91, id:0} }),
        tower_button  : button({pos: [46, 228], size:[20, 20], font: FONT_NORMAL_BLACK_ON_DARK,
                                textfn: recruiter_info_window_text_tower_button,
                                onclick_event: "set_tower_priority" }),
        fort_text     : text({pos: [74, 252], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:89, id:0} }),
        fort_button   : button({pos: [46, 248], size:[20, 20], font: FONT_NORMAL_BLACK_ON_DARK,
                                textfn: recruiter_info_window_text_fort_button,
                                onclick_event: "set_fort_priority" }),
    })
}

[es=(info_window_recruiter, set_tower_priority)]
function handle_set_tower_priority() {
    __building_recruiter_set_priority(city.object_info.bid, 0)
}

[es=(info_window_recruiter, set_fort_priority)]
function handle_set_fort_priority() {
    __building_recruiter_set_priority(city.object_info.bid, 1)
}

[es=(info_window_recruiter, init)]
function info_window_recruiter_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var soldiers_requested = (__formation_batalion_recruits_needed() ? 1 : 0) + __building_barracks_has_tower_sentry_request()

    var reason = { group: gid, id: 0 }
    if (b.has_road_access == false) {
        reason = { key: "#building_no_road_access" }
    } else if (b.num_workers <= 0) {
        reason.id = 3
    } else if (!soldiers_requested) {
        reason.id = 4
    } else {
        var offset = (b.stored_resource(RESOURCE_WEAPONS) > 0) ? 4 : 0
        var workers_state = Math.approximate_value(b.worker_percentage / 100.0, [8, 7, 6, 5])
        window.workers_text.text = __loc(gid, workers_state + offset)
    }

    var warning_text = __loc(gid, 1)
    if (reason.id || reason.key) {
        warning_text += " " + __loc(reason)
    }
    window.warning_text.text = warning_text
}
