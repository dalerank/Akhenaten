log_info("akhenaten: overlay disease started")

[es=city_overlay]
overlay_disease {
  id:OVERLAY_DISEASE
  title: "#overlay_disease"
  walkers:[FIGURE_PHYSICIAN, FIGURE_PLAGUED_CITIZEN]
  buildings:[BUILDING_PHYSICIAN, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_disease, get_tooltip_for_building)]
function disease_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    if (building.has_plague || building.disease_days > 0) {
        city.overlay_tooltip = "#health_diseased"
        return
    }

    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        return
    }

    var risk = 100 - building.common_health
    if (risk <= 0) {
        city.overlay_tooltip = "#health_risk_none"
    } else if (risk <= 25) {
        city.overlay_tooltip = "#health_risk_negligible"
    } else if (risk <= 50) {
        city.overlay_tooltip = "#health_risk_some"
    } else {
        city.overlay_tooltip = "#health_risk_high"
    }
}

[es=(overlay_disease, get_column_height)]
function disease_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.prev_part_building_id) {
        city.overlay_column_height = -1
        return
    }

    if (building.has_plague || building.disease_days > 0) {
        city.overlay_column_height = 10
        return
    }

    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    var risk = 100 - building.common_health
    var height = Math.floor(risk / 10)
    // height 0 still draws a column base — treat sub-10 risk as no column.
    city.overlay_column_height = height > 0 ? height : -1
}
