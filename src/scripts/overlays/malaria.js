log_info("akhenaten: overlay malaria (active) started")

[es=city_overlay]
overlay_malaria {
  id:OVERLAY_MALARIA
  title: "#overlay_malaria"
  walkers:[FIGURE_HERBALIST]
  buildings:[BUILDING_APOTHECARY, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

function malaria_is_active_case(building) {
    // No separate malaria-infection flag yet: treat plague in a malaria-risk
    // building as an active malaria case (≠ OVERLAY_INFECTED_HOUSING / disease).
    if (!building || (!building.has_plague && building.disease_days <= 0)) {
        return false
    }
    return building.malaria_risk > 0
}

[es=(overlay_malaria, get_tooltip_for_building)]
function malaria_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    // Active-malaria overlay: tooltip only for active cases.
    // Risk-level strings belong to OVERLAY_MALARIA_RISK.
    if (malaria_is_active_case(building)) {
        city.overlay_tooltip = "#health_diseased"
    }
}

[es=(overlay_malaria, get_column_height)]
function malaria_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (building.prev_part_building_id) {
        city.overlay_column_height = -1
        return
    }

    if (malaria_is_active_case(building)) {
        city.overlay_column_height = 10
        return
    }

    city.overlay_column_height = -1
}

[es=(overlay_malaria, show_building)]
function malaria_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_show_building = 0
        return
    }

    if (building.type == BUILDING_APOTHECARY || building.type == BUILDING_WATER_SUPPLY
        || building.type == BUILDING_ROADBLOCK) {
        city.overlay_show_building = 1
        return
    }

    city.overlay_show_building = malaria_is_active_case(building) ? 1 : 0
}
