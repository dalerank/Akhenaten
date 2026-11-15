log_info("akhenaten: overlay infected_housing started")

[es=city_overlay]
overlay_infected_housing {
  id:OVERLAY_INFECTED_HOUSING
  title: "#overlay_infected_housing"
  walkers:[FIGURE_PHYSICIAN, FIGURE_HERBALIST]
  buildings:[BUILDING_PHYSICIAN, BUILDING_APOTHECARY, BUILDING_MORTUARY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_infected_housing, get_tooltip_for_building)]
function infected_housing_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    if (building.has_plague || building.disease_days > 0) {
        city.overlay_tooltip = "#health_diseased"
    }
}

[es=(overlay_infected_housing, get_column_height)]
function infected_housing_building_column_height(ev) {
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

    city.overlay_column_height = -1
}

[es=(overlay_infected_housing, show_building)]
function infected_housing_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_show_building = 0
        return
    }

    if (building.type == BUILDING_PHYSICIAN || building.type == BUILDING_APOTHECARY
        || building.type == BUILDING_MORTUARY || building.type == BUILDING_ROADBLOCK) {
        city.overlay_show_building = 1
        return
    }

    city.overlay_show_building = (building.has_plague || building.disease_days > 0) ? 1 : 0
}
