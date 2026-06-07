log_info("akhenaten: ui bricklayers guild info window started")

[es=building_info_window]
bricklayers_guild_info_window {
    related_buildings [BUILDING_BRICKLAYERS_GUILD]
    ui : baseui(workshop_info_window, {

    })
}

[es=(bricklayers_guild_info_window, init)]
function bricklayers_guild_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    window.mothball.enabled = game_features.gameui_building_mothball_button && b.max_workers && b.max_workers > 0
    window.mothball.tooltip = __loc(54, b.state == 1 ? 16 : 17)
    workshop_info_window_setup_advisors(window, b.type)
    var g = b.meta_text_id
    var reason = { group: g, id: 0 }
    if (!b.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (city.resources.bricks.mothballed) {
        reason.id = 4
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else if (b.first_material_stored < 100) {
        reason.id = 11
    } else {
        reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    }
    window.warning_text.text = __loc(reason.group, reason.id)
    window.workers_text.text = workshop_format_workers_text(b)
}
