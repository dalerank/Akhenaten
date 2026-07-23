log_info("akhenaten: ui education window started")

function education_info_window_service_figure_type(building_type) {
    if (building_type == BUILDING_ACADEMY) {
        return FIGURE_ACADEMY_SCRIBER
    }
    if (building_type == BUILDING_LIBRARY) {
        return FIGURE_LIBRARIAN
    }
    return FIGURE_NONE
}

function education_info_window_has_service_figure(b) {
    var expected = education_info_window_service_figure_type(b.type)
    if (expected == FIGURE_NONE) {
        return false
    }
    var f = b.get_figure(BUILDING_SLOT_SERVICE)
    return f.valid && f.type == expected
}

[es=building_info_window]
info_window_education {
    related_buildings [BUILDING_ACADEMY, BUILDING_LIBRARY]
    ui : baseui(building_info_window, {
        background      : outer_panel({size: [29, 17]}),
        resource_icon   : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel     : inner_panel({pos : [16, 120], size: [27, 5],
            ui : {
                workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
            }
        }),
    })
}

[es=(info_window_education, init)]
function info_window_education_on_init(window) {
    var b = city.get_building(window.bid)
    var group = b.meta_text_id
    var papyrus_stored = b.stored_resource(RESOURCE_PAPYRUS)

    window.resource_icon.image = RESOURCE_PAPYRUS
    window.resource_stored.text = __loc(23, 77) + " " + papyrus_stored

    var reason = { group: group, id: 1 }
    if (education_info_window_has_service_figure(b)) {
        reason.id = 1
    } else if (b.has_road_access == false) {
        reason = { key: "#building_no_road_access" }
    } else if (b.num_workers <= 0) {
        reason.id = 2
    } else {
        reason.id = 3
    }

    window.warning_text.text = __loc(reason)
}
