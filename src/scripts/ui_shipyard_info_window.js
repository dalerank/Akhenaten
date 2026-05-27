log_info("akhenaten: ui_shipyard_info_window.js loaded")

[es=building_info_window]
shipyard_info_window {
    related_buildings [BUILDING_SHIPWRIGHT]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 18]}),
        warning_text  : text({pos: [28, 40], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel   : inner_panel({pos : [16, 150], size: [27, 5],
            ui : {
                workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
            }
        }),
        ready_prod    : text({pos: [30, 110], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        resource_icon : resource_icon({pos: [32, 130], resource: RESOURCE_TIMBER }),
        resource_stored : text({pos: [60, 130], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
    })
}

[es=(shipyard_info_window, init)]
function shipyard_info_window_on_init(window) {
    var shipyard = city.get_shipyard(window.bid)
    var gid = shipyard.meta_text_id
    var wood_stored = shipyard.stored_resource(RESOURCE_TIMBER)
    var progress = shipyard.progress
    var pct_done = Math.calc_percentage(progress, 400)

    window.warning_text.text = __loc(gid, 1)
    window.resource_stored.text = _format(__loc(gid, 7) + " {0}", wood_stored)
    window.ready_prod.text = __loc(gid, 2) + " " + pct_done + "% " + __loc(gid, 3)

    var reason = { group: gid, id: 0 }
    if (!shipyard.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (!__city_buildings_ships_requested()) {
        reason.id = 4
    } else if (shipyard.process_type != FIGURE_NONE) {
        if (wood_stored == 0) {
            reason.id = 8
        } else if (shipyard.reparing) {
            var left_repair = 100 - progress
            reason.id = wood_stored > left_repair ? 6 : 10
        } else {
            var left_building = 160 - progress
            reason.id = wood_stored > left_building ? 5 : 9
        }
    } else {
        reason.id = 4
    }

    window.workers_desc.text = __loc(reason.group, reason.id)
}
