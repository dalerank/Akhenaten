log_info("akhenaten: ui artisans guild info window started")

// OG window_building_draw_artisans_guild: standard height, paint and clay stock on one row,
// state line below (no road / no workers / no paint / no clay / staffing).
[es=building_info_window]
artisans_guild_info_window {
    related_buildings [BUILDING_ARTISANS_GUILD]
    ui : baseui(workshop_info_window, {
        resource_icon : resource_icon({pos[32, 56], prop:"${building.first_material}" })
        resource_stored : text({pos[60, 60], size[170, 20], font:FONT_NORMAL_BLACK_ON_LIGHT })
        resource_icon_b : resource_icon({pos[230, 56], prop:"${building.second_material}" })
        resource_stored_b : text({pos[260, 60], size[190, 20], font:FONT_NORMAL_BLACK_ON_LIGHT })
    })
}

function artisans_guild_info_window_state_text(b) {
    if (!b.has_road_access) {
        return { key: "#building_no_road_access" }
    }
    var pct = b.worker_percentage
    var id
    if (b.num_workers < 1) {
        id = 2
    } else if (b.stored_resource(RESOURCE_PAINT) < 1) {
        id = 8
    } else if (b.stored_resource(RESOURCE_CLAY) < 1) {
        id = 9
    } else if (pct >= 100) {
        id = 3
    } else if (pct >= 75) {
        id = 4
    } else if (pct >= 50) {
        id = 5
    } else if (pct >= 25) {
        id = 6
    } else {
        id = 7
    }
    return { group: 312, id: id }
}

[es=(artisans_guild_info_window, init)]
function artisans_guild_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    window.mothball.enabled = game_features.gameui_building_mothball_button && b.max_workers && b.max_workers > 0
    window.mothball.tooltip = __loc(54, b.state == 1 ? 16 : 17)
    workshop_info_window_setup_advisors(window, b.type)

    window.ready_prod.text = ""
    window.warning_text.text = __loc(artisans_guild_info_window_state_text(b))
    window.resource_stored.text = __loc(312, 10) + " " + workshop_format_stored_amount(b.stored_resource(RESOURCE_PAINT))
    window.resource_stored_b.text = __loc(312, 11) + " " + workshop_format_stored_amount(b.stored_resource(RESOURCE_CLAY))
    window.workers_text.text = workshop_format_workers_text(b)
}
