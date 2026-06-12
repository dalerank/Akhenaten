log_info("akhenaten: overlay damage started")

[es=city_overlay]
overlay_damage {
  id:OVERLAY_DAMAGE
  title: "#overlay_damage"
  walkers:[FIGURE_ARCHITECT]
  buildings:[BUILDING_ARCHITECT_POST, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_damage, get_tooltip_for_building)]
function damage_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var risk = building.collapse_risk
    if (risk <= 0) {
        city.overlay_tooltip = "#damage_risk_perfect"
    } else if (risk <= 40) {
        city.overlay_tooltip = "#damage_risk_negligible"
    } else if (risk <= 80) {
        city.overlay_tooltip = "#damage_risk_low"
    } else if (risk <= 120) {
        city.overlay_tooltip = "#damage_risk_some"
    } else if (risk <= 160) {
        city.overlay_tooltip = "#damage_risk_many"
    } else {
        city.overlay_tooltip = "#damage_risk_critical"
    }
}

[es=(overlay_damage, get_column_height)]
function damage_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.prev_part_building_id) {
        city.overlay_column_height = -1
        return
    }

    if (building.collapse_risk <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = building.collapse_risk / 100
}

[es=(overlay_damage, draw_custom_top)]
function damage_draw_custom_top(ev) {
    if (game.debug_render_mode != e_debug_render_overlay_add) {
        return
    }

    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var pos = { x: ev.mpos.x + 15, y: ev.mpos.y + 15 }
    ui.text_abs_colored("" + building.collapse_risk, pos, FONT_SMALL_OUTLINED, COLOR_LIGHT_BLUE)
}
