log_info("akhenaten: ui workshops info window started")

function workshop_format_stored_amount(amount) {
    amount = amount || 0
    return amount + " " + __loc(8, amount == 1 ? 10 : 11)
}

function workshop_format_workers_text(b) {
    var employee = __loc(8, b.num_workers == 1 ? 12 : 13)
    return b.num_workers + " " + employee + " (" + b.max_workers + " " + __loc(69, 0)
}

function workshop_info_window_open_industry() {
    var b = city.get_building(city.object_info.bid)
    show_trade_resource_settings_window(b.output_resource_id)
}

function workshop_info_window_show_advisor(slot) {
    var b = city.get_building(city.object_info.bid)
    var cfg = get_building_config_by_id(b.type)
    var advisors = (cfg && cfg.info_advisors) ? cfg.info_advisors : []
    if (slot < 0 || slot >= advisors.length) {
        return
    }
    var advisor = advisors[slot]
    if (advisor && city.is_advisor_available(advisor)) {
        window_advisors_show_advisor(advisor)
    }
}

function workshop_info_window_show_advisor_0() { workshop_info_window_show_advisor(0) }
function workshop_info_window_show_advisor_1() { workshop_info_window_show_advisor(1) }
function workshop_info_window_show_advisor_2() { workshop_info_window_show_advisor(2) }

function workshop_info_window_setup_advisors(window, building_type) {
    var cfg = get_building_config_by_id(building_type)
    var advisors = (cfg && cfg.info_advisors) ? cfg.info_advisors : []
    var slots = ["advisor_btn_0", "advisor_btn_1", "advisor_btn_2"]
    for (var i = 0; i < slots.length; i++) {
        var btn = window[slots[i]]
        if (!btn) {
            continue
        }
        var advisor = (i < advisors.length) ? advisors[i] : ADVISOR_NONE
        var show = advisor && city.is_advisor_available(advisor)
        btn.enabled = !!show
        var tid = get_image({pack:PACK_GENERAL, id:106, offset:!!show ? (advisor - 1) * 3 : 0}).tid
        log_info("akhenaten: workshop_info_window_setup_advisors " + slots[i] + " " + advisor + " " + show + " " + tid)
        btn.image = tid
    }
}

function workshop_info_window_status_reason(b) {
    var reason = { group: b.meta_text_id, id: 0 }
    if (!b.has_road_access) {
        return { group: 69, id: 25 }
    } else if (__city_resource_is_mothballed(b.output_resource_id)) {
        reason.id = 4
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else if (b.first_material_stored < 100) {
        reason.id = 11
    } else {
        reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    }
    return reason
}

[es=building_info_window]
workshop_info_window {
    related_buildings [BUILDING_BREWERY_WORKSHOP, BUILDING_POTTERY_WORKSHOP
                       BUILDING_PAPYRUS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP, BUILDING_CATTLE_RANCH
                       BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP, BUILDING_WEAPONSMITH, BUILDING_JEWELS_WORKSHOP]
    ui {
        background    : outer_panel({size[29, 16] }),
        title         : text({pos[0, 12], size[px(29), 20], text:"${building.name}", font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        produce_icon  : resource_icon({pos[10, 10], prop:"${building.output_resource}" })
        ready_prod    : text({pos[32, 40], size[px(27), 20], text:"${text.2} ${industry.progress}% ${text.3}", font : FONT_NORMAL_BLACK_ON_LIGHT })
        resource_icon : resource_icon({pos[32, 56], prop:"${building.first_material}" })
        resource_stored : text({pos[60, 60], size[px(27), 20], font:FONT_NORMAL_BLACK_ON_LIGHT })
        warning_text  : text({pos[32, 86], size[px(27), 60], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        workers_panel : inner_panel({pos[16, 136], size[27, 4] })
        workers_img   : image({pos[40, 148], pack:PACK_GENERAL, id:134, offset:14}) 
        workers_text  : text({pos[60, 158], font: FONT_NORMAL_BLACK_ON_DARK })

        button_help   : help_button({})
        advisor_btn_0 : image_button({margin{left:40, bottom:-40}, size[28, 28], enabled:false, onclick: workshop_info_window_show_advisor_0 })
        advisor_btn_1 : image_button({margin{left:65, bottom:-40}, size[28, 28], enabled:false, onclick: workshop_info_window_show_advisor_1 })
        advisor_btn_2 : image_button({margin{left:96, bottom:-40}, size[28, 28], enabled:false, onclick: workshop_info_window_show_advisor_2 })

        industry_button : button({
                                margin{right:-120, bottom:-40}, size[23, 23]
                                text:"i"
                                onclick: workshop_info_window_open_industry
                               })
        mothball      : button({
                                margin{right:-90, bottom:-40}, size[23, 23]
                                textfn: building_info_window_text_mothball
                                onclick: building_info_window_toggle_mothball
                               })
        button_close  : close_button({})
    }
}

[es=(workshop_info_window, init)]
function workshop_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    window.mothball.enabled = game_features.gameui_building_mothball_button && b.max_workers && b.max_workers > 0
    window.mothball.tooltip = __loc(54, b.state == 1 ? 16 : 17)

    workshop_info_window_setup_advisors(window, b.type)
    var reason = workshop_info_window_status_reason(b)
    window.warning_text.text = __loc(reason.group, reason.id)
    window.resource_stored.text = __loc(b.meta_text_id, 12) + " " + workshop_format_stored_amount(b.first_material_stored)
    window.workers_text.text = workshop_format_workers_text(b)
}
