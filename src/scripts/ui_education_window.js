log_info("akhenaten: ui education window started")

[es=building_info_window]
info_window_education {
    first_advisor    : ADVISOR_EDUCATION
    related_buildings [BUILDING_ACADEMY, BUILDING_LIBRARY]
    ui : baseui(building_info_window, {
        background      : outer_panel({size: [29, 17]}),
        warning_text    : text({ pos: [20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        resource_icon   : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel     : inner_panel({pos : [16, 120], size: [27, 5],
            ui : {
                workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
            }
        }),
        workers_desc : text({pos: [66, 152], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

[es=(info_window_education, init)]
function info_window_education_on_init(window) {
    __log_marker("window_show:info_window_education")
    var b = city.get_building(window.bid)

    window.warning_text.text = "#library_info"
    window.resource_icon.image = RESOURCE_PAPYRUS

    var papyrus_stored = b.stored_resource(RESOURCE_PAPYRUS)
    window.resource_stored.text = fmt("#sheets_of_papyrus ${n}", { n: papyrus_stored })

    var reason = "#library_info_ok"
    if (b.has_road_access == false) {
        reason = "#building_no_road_access"
    } else if (b.num_workers <= 0 || papyrus_stored <= 0) {
        reason = "#library_info_idle"
    }
    window.workers_desc.text = reason
}
