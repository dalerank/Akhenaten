log_info("akhenaten: ui gatehouse info window")

[es=building_info_window]
info_window_gatehouse {
    related_buildings [BUILDING_MUD_GATEHOUSE, BUILDING_BRICK_GATEHOUSE, BUILDING_GATEHOUSE]
    ui : baseui(building_info_window, {
    })
}

[es=(info_window_gatehouse, init)]
function info_window_gatehouse_on_init(window) {
    var b = city.get_building(window.bid)
    if (!b) {
        return
    }
    window.workers_desc.text = __loc(b.meta_text_id, 1)
}
