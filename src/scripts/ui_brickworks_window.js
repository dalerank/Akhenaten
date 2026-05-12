log_info("akhenaten: ui brickworks info window started")

[es=building_info_window]
brickworks_info_window {
    related_buildings [BUILDING_BRICKS_WORKSHOP]
    ui : baseui(workshop_info_window, {
        background    : outer_panel({size[29, 18] })
        warning_text  : text({pos[32, 58], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })

        resource_icon : resource_icon({pos[32, 205], prop:"${building.first_material}" })
        resource_stored : text({pos[55, 210], size[px(27), 20], text:"${text.13} ${building.first_material_stored}", font:FONT_NORMAL_BLACK_ON_LIGHT })

        resource_icon_b : resource_icon({pos: [32, 225], prop:"${building.second_material}" })
        resource_stored_b : text({pos[55, 230], size[px(27), 20], text:"${text.14} ${building.second_material_stored}", font:FONT_NORMAL_BLACK_ON_LIGHT })
    })
}

[es=(brickworks_info_window, init)]
function brickworks_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 0 }
    if (!b.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (b.is_output_resource_mothballed) {
        reason.id = 4
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else if (b.stored_clay < 100 || b.stored_straw < 100) {
        reason.id = 11
    } else {
        reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    }
    window.workers_desc.text = __loc(reason.group, reason.id)

    if (b.stored_clay <= 0 || b.stored_straw <= 0) {
        window.warning_text.text = __loc(b.meta_text_id, 11)
    } else {
        window.warning_text.text = __loc(b.meta_text_id, 1)
    }
}
