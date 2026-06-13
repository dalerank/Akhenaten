log_info("akhenaten: overlay malaria_risk started")

[es=city_overlay]
overlay_malaria_risk {
  id:OVERLAY_MALARIA_RISK
  title: "#overlay_malaria_risk"
  walkers:[FIGURE_HERBALIST]
  buildings:[BUILDING_APOTHECARY, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_malaria_risk, get_tooltip_for_building)]
function malaria_risk_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var risk = building.malaria_risk
    if (risk <= 0) {
        city.overlay_tooltip = "#malaria_risk_negligible"
    } else if (risk <= 20) {
        city.overlay_tooltip = "#malaria_risk_some"
    } else if (risk <= 40) {
        city.overlay_tooltip = "#malaria_risk_present"
    } else if (risk <= 60) {
        city.overlay_tooltip = "#malaria_risk_imminent"
    } else {
        city.overlay_tooltip = "#malaria_risk_critical"
    }
}

[es=(overlay_malaria_risk, get_column_height)]
function malaria_risk_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.prev_part_building_id) {
        city.overlay_column_height = -1
        return
    }

    if (building.malaria_risk <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(building.malaria_risk / 10)
}

[es=(overlay_malaria_risk, draw_custom_top)]
function malaria_risk_draw_custom_top(ev) {
    if (game.debug_render_mode != e_debug_render_overlay_add) {
        return
    }

    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var grid_risk = __malaria_risk_at_tile(ev.tile.x, ev.tile.y)
    if (grid_risk <= 0 && building.malaria_risk <= 0) {
        return
    }

    var text
    if (grid_risk > 0 && building.malaria_risk > 0) {
        text = "g:" + grid_risk + " b:" + building.malaria_risk
    } else if (grid_risk > 0) {
        text = "g:" + grid_risk
    } else {
        text = "b:" + building.malaria_risk
    }

    var color = building.malaria_risk < 30 ? COLOR_LIGHT_GREEN
              : building.malaria_risk < 60 ? COLOR_YELLOW
              : COLOR_LIGHT_RED
    var pos = { x: ev.mpos.x + 15, y: ev.mpos.y + 15 }
    ui.text_abs_colored(text, pos, FONT_SMALL_OUTLINED, color)
}
