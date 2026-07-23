log_info("akhenaten: ui farm info window started")

function farm_info_window_format_progress_desc(b, farm) {
    var pct = __building_farm_progress_pct(farm.id)
    var fertility = __building_farm_fertility(farm.id)
    return __loc(b.meta_text_id, 2) + " " + pct + "% " + __loc(b.meta_text_id, 3) + " "
        + __loc(b.meta_text_id, 12) + " " + fertility + "% " + __loc(b.meta_text_id, 13)
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
        background    : outer_panel({size: [29, 18]}),
        resource      : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        workers_desc  : text({ pos: [70, 116], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(23) }),
        farm_desc     : text({ pos: [32, 40], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(26), multiline:true }),
        farm_state    : text({ pos: [32, 186], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        flood_info    : text({ pos: [32, 206], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_desc : text({ pos: [32, 226], font: FONT_NORMAL_BLACK_ON_LIGHT }),
    })
}

[es=(info_window_farm, init)]
function info_window_farm_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var reason = { group: gid, id: 0 }
    if (!b.num_workers) {
        reason = { group: 177, id: 5 }
    } else {
        if (!b.has_road_access) {
            reason = { key: "#building_no_road_access" }
        } else if (__city_resource_is_mothballed(b.output_resource_id)) {
            reason.id = 4
        } else if (b.curse_days_left > 4) {
            reason.id = 11
        } else {
            reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
        }
    }
    window.workers_desc.text = __loc(reason)

    var farm = city.get_farm(window.bid)
    window.progress_desc.text = farm_info_window_format_progress_desc(b, farm)

    if (farm.is_floodplain) {
        var month_id = 8 // TODO: fetch flood info
        window.flood_info.text = __loc(177, 2) + " " + __loc(160, month_id)
        var is_not_irrigated = 0 // TODO: fetch irrigation info
        window.farm_state.text = __loc(177, is_not_irrigated)
        window.farm_desc.text = __loc(gid, 1)
    } else {
        window.farm_state.text = __loc(gid, 1)
    }
}
