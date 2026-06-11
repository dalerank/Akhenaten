log_info("akhenaten: overlay health started")

[es=city_overlay]
overlay_health {
  id:OVERLAY_HEALTH
  title: "#overlay_health"
  walkers:[FIGURE_EMBALMER, FIGURE_HERBALIST, FIGURE_PHYSICIAN, FIGURE_DENTIST]
  buildings:[BUILDING_MORTUARY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_health, get_tooltip_for_building)]
function health_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    if (building.disease_days > 0) {
        city.overlay_tooltip = __loc("#health_diseased")
        return
    }

    var health = building.common_health
    if (health < 25) {
        city.overlay_tooltip = __loc("#health_risk_high")
    } else if (health < 50) {
        city.overlay_tooltip = __loc("#health_risk_some")
    } else if (health < 75) {
        city.overlay_tooltip = __loc("#health_risk_negligible")
    } else {
        city.overlay_tooltip = __loc("#health_risk_none")
    }
}

[es=(overlay_health, get_column_height)]
function health_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.disease_days > 0) {
        city.overlay_column_height = 10
        return
    }

    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = building.common_health / 10
}

[es=(overlay_health, get_column_color)]
function health_building_column_color(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_color = -1
        return
    }

    if (building.disease_days > 0) {
        city.overlay_column_color = 9
        return
    }

    city.overlay_column_color = -1
}

[es=(overlay_health, draw_custom_top)]
function health_draw_custom_top(ev) {
    if (game.debug_render_mode != e_debug_render_overlay_add) {
        return
    }

    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var pos = { x: ev.mpos.x + 15, y: ev.mpos.y + 15 }
    var house = city.get_house(ev.bid)
    if (house) {
        ui.text_abs_colored(building.common_health + "/" + house.health, pos, FONT_SMALL_OUTLINED, COLOR_LIGHT_BLUE)
    } else {
        ui.text_abs_colored("" + building.common_health, pos, FONT_SMALL_OUTLINED, COLOR_LIGHT_BLUE)
    }
}
