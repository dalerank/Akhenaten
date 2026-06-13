log_info("akhenaten: overlay fire started")

[es=city_overlay]
overlay_fire {
  id:OVERLAY_FIRE
  title: "#overlay_fire"
  walkers:[FIGURE_FIREMAN]
  buildings:[BUILDING_FIREHOUSE, BUILDING_BURNING_RUIN, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

var fire_highlight_buildings = [
    BUILDING_FIREHOUSE,
    BUILDING_BURNING_RUIN,
    BUILDING_FESTIVAL_SQUARE,
    BUILDING_ROADBLOCK
]

function fire_is_highlight_building(type) {
    for (var i = 0; i < fire_highlight_buildings.length; i++) {
        if (fire_highlight_buildings[i] == type) {
            return true
        }
    }
    return false
}

function fire_main_building(building) {
    return city.get_building(__building_main_id(building.id))
}

function fire_draw_firehouse_tooltip(mpos, firehouse) {
    var tooltip_lines = [
        { label: "This month:", value: "" + firehouse.buildings_served_this_month },
        { label: "This year:", value: "" + firehouse.buildings_served_this_year },
        { label: "Total served:", value: "" + firehouse.total_buildings_served },
        { label: "Months active:", value: "" + firehouse.months_active }
    ]

    var width = 220
    var line_height = 14
    var height = tooltip_lines.length * line_height + 10
    var pos = { x: 0, y: 0 }

    if (mpos.x < width + 20) {
        pos.x = mpos.x + 20
    } else {
        pos.x = mpos.x - width - 20
    }

    if (mpos.y < 200) {
        pos.y = mpos.y + 10
    } else if (mpos.y + height - 32 > screen.height) {
        pos.y = screen.height - height
    } else {
        pos.y = mpos.y - 32
    }

    ui.begin_widget(pos)
    ui.fill_rect({ x: 0, y: 0 }, { x: width, y: height }, COLOR_TOOLTIP_FILL)
    ui.border({ x: 0, y: 0 }, { x: width, y: height }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)

    var label_x = 5
    var value_x = 140
    var y_offset = 5
    for (var i = 0; i < tooltip_lines.length; i++) {
        var line = tooltip_lines[i]
        ui.label_colored(line.label, { x: label_x, y: y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT)
        ui.label_colored("\t" + line.value, { x: value_x, y: y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT)
        y_offset += line_height
    }

    ui.end_widget()
}

[es=(overlay_fire, get_tooltip_for_building)]
function fire_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var firehouse = city.get_firehouse(ev.bid)
    if (firehouse) {
        fire_draw_firehouse_tooltip(ev.mpos, firehouse)
        return
    }

    var main = fire_main_building(building)
    if (!main) {
        return
    }

    var risk = main.fire_risk
    if (risk <= 0) {
        city.overlay_tooltip = "#fire_risk_none"
    } else if (risk <= 200) {
        city.overlay_tooltip = "#fire_risk_negligible"
    } else if (risk <= 400) {
        city.overlay_tooltip = "#fire_risk_low"
    } else if (risk <= 600) {
        city.overlay_tooltip = "#fire_risk_some"
    } else if (risk <= 800) {
        city.overlay_tooltip = "#fire_risk_high"
    } else {
        city.overlay_tooltip = "#fire_risk_critical"
    }
}

[es=(overlay_fire, get_column_height)]
function fire_building_column_height(ev) {
    if (game_features.gameui_overlay_show_gray_buildings) {
        city.overlay_column_height = -1
        return
    }

    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.prev_part_building_id || building.fire_proof) {
        city.overlay_column_height = -1
        return
    }

    var house = city.get_house(ev.bid)
    if ((house && house.population <= 0)
        || building.type == BUILDING_GARDENS
        || building.type == BUILDING_BANDSTAND
        || building.type == BUILDING_BOOTH) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = building.fire_risk / 100
}

[es=(overlay_fire, show_building)]
function fire_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building) {
        city.overlay_show_building = 0
        return
    }

    if (fire_is_highlight_building(building.type)) {
        city.overlay_show_building = 1
        return
    }

    var percentage = Math.calc_percentage(building.fire_risk, 1000)
    city.overlay_show_building = percentage > 10 ? 1 : 0
}

[es=(overlay_fire, color_mask_building)]
function fire_color_mask_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building) {
        city.overlay_color_mask = -1
        return
    }

    if (fire_is_highlight_building(building.type)) {
        city.overlay_color_mask = -1
        return
    }

    var percentage = Math.calc_percentage(building.fire_risk, 1000)
    city.overlay_color_mask = Math.color_from_green_to_red(percentage)
}
