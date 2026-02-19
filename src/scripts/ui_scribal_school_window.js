log_info("akhenaten: scribal school window started")

[es=building_info_window]
scribal_school_info_window {
    related_buildings [BUILDING_SCRIBAL_SCHOOL]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 17]}),
        resource_icon  : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel    : inner_panel({pos : [16, 120], size: [27, 5],
            ui : {
                workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
            }
        }),
    })
}

[es=scribal_school_info_window_init]
function scribal_school_info_window_init(window) {
    var b = city.get_building(window.bid)
    var group = b.meta_text_id

    window.warning_text.text = __loc(group, 1)
    window.resource_icon.image = RESOURCE_PAPYRUS

    var papyrus_stored = b.stored_resource(RESOURCE_PAPYRUS)
    window.resource_stored.text = __loc(23, 77) + " " + papyrus_stored

    var reason = { group: group, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0 || papyrus_stored <= 0) {
        reason.id = 2
    } else {
        reason.id = 3
    }

    window.inner_panel.workers_desc.text = __loc(reason.group, reason.id)
}
