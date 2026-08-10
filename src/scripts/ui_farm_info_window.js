log_info("akhenaten: ui farm info window started")

function farm_info_window_format_progress_desc(b, farm) {
    var pct = __building_farm_progress_pct(farm.id)
    var fertility = __building_farm_fertility(farm.id)
    return __loc(b.meta_text_id, 2) + " " + pct + "% " + __loc(b.meta_text_id, 3) + " "
        + __loc(b.meta_text_id, 12) + " " + fertility + "% " + __loc(b.meta_text_id, 13)
}

function farm_info_window_workers_desc(window) {
    return window.workers_desc
        || (window.inner_panel && window.inner_panel.workers_desc)
}

[es=building_info_window]
info_window_farm {
    related_buildings [
        BUILDING_GRAIN_FARM, BUILDING_GRAIN_MEADOW_FARM,
        BUILDING_LETTUCE_FARM, BUILDING_LETTUCE_MEADOW_FARM,
        BUILDING_CHICKPEAS_FARM, BUILDING_CHICKPEAS_MEADOW_FARM,
        BUILDING_POMEGRANATES_FARM, BUILDING_POMEGRANATES_MEADOW_FARM,
        BUILDING_BARLEY_FARM, BUILDING_BARLEY_MEADOW_FARM,
        BUILDING_FLAX_FARM, BUILDING_FLAX_MEADOW_FARM,
        BUILDING_HENNA_FARM, BUILDING_HENNA_MEADOW_FARM,
        BUILDING_FIGS_FARM, BUILDING_FIGS_MEADOW_FARM
    ]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 19]}),
        resource      : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        progress_desc : text({ pos: [32, 40], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        labor_status  : text({ pos: [32, 66], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(26), multiline:true }),
        flood_info    : text({ pos: [32, 186], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        farm_state    : text({ pos: [32, 206], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        farm_desc     : text({ pos: [32, 226], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(26), multiline:true }),
        basin_info    : text({ pos: [32, 246], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(26), multiline:true }),
    })
}

[es=(info_window_farm, init)]
function info_window_farm_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var on_floodplain = terrain.is(b.tile, TERRAIN_FLOODPLAIN)
    if (window.warning_text) {
        window.warning_text.text = ""
    }
    var labor_reason = { group: gid, id: 0 }
    if (!b.num_workers) {
        labor_reason.id = 5
    } else if (!b.has_road_access) {
        labor_reason = { key: "#building_no_road_access" }
    } else if (__city_resource_is_mothballed(b.output_resource_id)) {
        labor_reason.id = 4
    } else if (b.curse_days_left > 4) {
        labor_reason.id = 11
    } else {
        labor_reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    }
    window.labor_status.text = __loc(labor_reason)

    var wdesc = farm_info_window_workers_desc(window)
    if (wdesc) {
        // Floodplain farms with no staff show Work Camp hint inside the employee panel.
        wdesc.text = (!b.num_workers && on_floodplain) ? __loc(177, 5) : ""
    }

    var farm = city.get_farm(window.bid)
    if (!farm) {
        window.farm_desc.text = ""
        window.farm_state.text = ""
        window.flood_info.text = ""
        window.basin_info.text = ""
        return
    }
    window.progress_desc.text = farm_info_window_format_progress_desc(b, farm)
    window.farm_desc.text = __loc(gid, 1)
    var irrigated = __building_farm_is_irrigated(farm.id)
    window.farm_state.text = __loc(177, irrigated ? 0 : 1)

    if (on_floodplain) {
        // During inundation the "next floods in …" line is not shown (water already up).
        if (floods_ui_show_water_bar()) {
            window.flood_info.text = ""
        } else {
            window.flood_info.text = __loc(177, 2) + " " + floods_ui_format_farm_flood_month()
        }
        if (game_features.get('gameplay_enhanced_flood_basins') === true
            && terrain.basin_sealed(b.tile)) {
            window.basin_info.text = __loc("#farm_in_flood_basin")
        } else {
            window.basin_info.text = ""
        }
    } else {
        var next_month = building_farm_next_harvest_month(b.id)
        window.flood_info.text = __loc(gid, 14) + " " + __loc(160, next_month)
        window.basin_info.text = ""
    }
}
