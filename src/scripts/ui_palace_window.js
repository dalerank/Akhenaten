log_info("akhenaten: ui_palace_window.js loaded")

function palace_info_window_tax_level_text() {
    return __loc("#tax_rate_of") + " " + city.finance.tax_percentage + "%"
}

function palace_employment_text(palace) {
    if (palace.num_workers >= palace.max_workers) {
        return palace.houses_covered < 40 ? "#building_poor_worker_access" : ""
    }
    if (city.population <= 0) {
        return "#building_no_people_in_city"
    }
    if (palace.houses_covered <= 0) {
        return "#building_no_workers_nearby"
    }
    if (palace.houses_covered < 40) {
        return "#building_poor_worker_access"
    }
    return "#building_labor_could_shift"
}

function palace_visit_advisor_text() {
    var advisors = [
        { id: ADVISOR_LABOR, text_id: 71 },
        { id: ADVISOR_RATINGS, text_id: 74 }
    ]
    var available = null
    for (var i = 0; i < advisors.length; i++) {
        if (!city.is_advisor_available(advisors[i].id)) {
            continue
        }
        if (available) {
            return ""
        }
        available = advisors[i]
    }
    return available ? __loc(68, available.text_id) : ""
}

[es=building_info_window]
info_window_palace {
    related_buildings [BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE]
    first_advisor : ADVISOR_LABOR
    second_advisor : ADVISOR_RATINGS
    ui : baseui(building_info_window, {
        background    : outer_panel({size[29, 17]})
        resource_img  : resource_icon({pos[16, 36], resource:RESOURCE_GOLD})
        vaults_hold   : text({pos[44, 43], font: FONT_NORMAL_BLACK_ON_LIGHT })
        tax_level     : label({pos:[px(29) / 2 + 40, 46], textfn: palace_info_window_tax_level_text, font : FONT_NORMAL_BLACK_ON_LIGHT })
        dec_tax       : arrowdown({pos:[px(29) / 2 + 170, 38], onclick: function() { emit event_finance_change_tax{ value: -1 } } })
        inc_tax       : arrowup({pos:[px(29) / 2 + 193, 38], onclick: function() { emit event_finance_change_tax{ value: 1 } } })
        warning_text  : text({pos[32, 66], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        inner_panel   : inner_panel({pos[16, 136], size: [27, 4],
                                                                ui : {
                                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                                    workers_text : text({pos[50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                                    workers_desc : text({pos[50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                                }
                                                          })
        text_visit    : label({pos[90, 238], font: FONT_NORMAL_BLACK_ON_LIGHT, textfn: palace_visit_advisor_text })
    })
}

[es=(info_window_palace, init)]
function palace_info_window_init(window) {
    var palace = city.get_building(window.bid)

    window.vaults_hold.text = __loc("#palace_vaults_hold") + " " + palace.tax_income_or_storage + " " + __loc("#debens")

    if (palace.has_road_access == false) {
        window.warning_text.text = __loc("#building_no_road_access")
    } else {
        window.warning_text.text = ""
    }

    var emp = palace_employment_text(palace)
    window.workers_desc.text = emp ? __loc(emp) : ""
}
