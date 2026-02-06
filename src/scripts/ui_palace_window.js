log_info("akhenaten: ui_palace_window.js loaded")

[es=building_info_window]
info_window_palace {
    related_buildings [BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE]
    ui : baseui(building_info_window, {
        background    : outer_panel({size[29, 18]})
        resource_img  : resource_icon({pos[16, 16], resource:RESOURCE_GOLD})
        inner_panel   : inner_panel({pos[16, 170], size: [27, 4],
                                                                ui : {
                                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                                    workers_text : text({pos[50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                                    workers_desc : text({pos[50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                                }
                                                          })
        vaults_hold   : text({pos[44, 44], text:"${text.2} ${building.tax_income_or_storage} Db", font: FONT_NORMAL_BLACK_ON_LIGHT })
        warning_desc  : text({pos[32, 66], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        text_visit    : text({pos[90, 252], font: FONT_NORMAL_BLACK_ON_LIGHT, text:"#visit_rating_advisor" })
        visit_advisor : image_button({pos[52, 246], size[28, 28], pack:PACK_GENERAL, id:106,
                                      onclick: function() { __window_advisors_show_advisor(ADVISOR_RATINGS) } })
    })
}

[es=info_window_palace_init]
function palace_info_window_init_workers_desc(window) {
    var palace = city.get_building(window.bid)
    var reason = { group: city.object_info.group, id: 0 }

    if (palace.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (palace.num_workers <= 0) {
        reason.id = 10
    } else {
        reason.id = approximate_value(palace.worker_percentage / 100.0, [9, 8, 7, 6, 5])
    }

    log_info("akhenaten: palace_info_window_init_workers_desc: " + reason.group + " " + reason.id)
    window.workers_desc.text = __loc(reason.group, reason.id)
}