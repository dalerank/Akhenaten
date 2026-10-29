log_info("akhenaten: ui ferry info window started")

[es=building_info_window]
info_window_ferry {
    related_buildings [BUILDING_FERRY]
    ui : baseui(building_info_window, {
        background : outer_panel({size: [29, 18]}),
        warning_text : text({ pos[20, 46], wrap:px(27), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel : inner_panel({
            pos[16, 140], size[27, 5]
            ui {
                workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos[20, 10] })
                workers_text : text({pos[50, 16], text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", font: FONT_NORMAL_BLACK_ON_DARK})
                workers_desc : text({pos[50, 32], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) })
            }
        })
    })
}

[es=(info_window_ferry, init)]
function info_window_ferry_on_init(window) {
    var b = city.get_building(window.bid)
    if (!b) {
        return
    }

    var gid = b.meta_text_id
    var partner_id = __ferry_partner_id(b.id)
    var reason_id = 0

    if (!partner_id) {
        reason_id = 1
    } else {
        var partner = city.get_building(partner_id)
        if (!partner) {
            reason_id = 1
        } else if (!b.has_road_access || !partner.has_road_access) {
            reason_id = 2
        } else if (b.num_workers <= 0 || partner.num_workers <= 0) {
            reason_id = 3
        }
    }

    if (reason_id) {
        window.warning_text.text = __loc(gid, reason_id)
    } else {
        window.warning_text.text = __loc("#ferry_landing_ok")
    }

    building_info_window_setup_advisors(window)
}
