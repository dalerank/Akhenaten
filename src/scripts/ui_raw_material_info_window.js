log_info("akhenaten: raw material info window started")

raw_material_info_window {
    ui : baseui(building_info_window, {
        resource_img  : resource_icon({ pos:[14, 14], prop:"${building.output_resource}" }),
        progress_desc : text({ pos:[32, 44], text:"${text.2} ${industry.progress} % ${text.3}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_desc  : text({ pos:[32, 66], text:"${text.1}", font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        inner_panel   : inner_panel({ pos:[16, 130], size:[27, 5],
            ui : {
                workers_img  : image({ pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({ pos:[50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK }),
                workers_desc : text({ pos:[50, 32], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
            }
        }),
    })
}

[es=building_info_window]
info_window_raw_material {
    related_buildings [
        BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_WOOD_CUTTERS, BUILDING_CLAY_PIT,
        BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_REED_GATHERER,
        BUILDING_GRANITE_QUARRY, BUILDING_COPPER_MINE, BUILDING_SANDSTONE_QUARRY
    ]
    ui : baseui(raw_material_info_window, {
    })
}

function info_window_raw_material_common_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 10 }

    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else {
        reason.id = approximate_value(b.worker_percentage / 100.0, [9, 8, 7, 6])
    }

    var wdesc = window.workers_desc || (window.inner_panel && window.inner_panel.workers_desc)
    if (wdesc) wdesc.text = __loc(reason.group, reason.id)
}

[es=info_window_raw_material_init]
function info_window_raw_material_on_init(window) {
    info_window_raw_material_common_init(window)
}
