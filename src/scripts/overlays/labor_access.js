log_info("akhenaten: overlay labor_access started")

[es=city_overlay]
overlay_labor_access {
  id:OVERLAY_LABOR_ACCESS
  title: "#overlay_labor_access"
  walkers:[FIGURE_LABOR_SEEKER]
  buildings:[BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

function labor_access_houses_coverage_percentage(building) {
    var min_coverage = building.params.min_houses_coverage
    if (!min_coverage) {
        return 100
    }
    return Math.calc_percentage(building.houses_covered, min_coverage)
}

[es=(overlay_labor_access, show_figure)]
function labor_access_show_figure(ev) {
    var fig = city.get_figure(ev.fid)
    if (!fig.valid || fig.type != FIGURE_LABOR_SEEKER) {
        city.overlay_show_figure = 0
        return
    }

    var home = fig.home
    city.overlay_show_figure = (home && home.show_on_problem_overlay) ? 1 : 0
}

[es=(overlay_labor_access, get_tooltip_for_building)]
function labor_access_building_tooltip(ev) {
    city.overlay_tooltip = "#labor_access_tooltip"
}

[es=(overlay_labor_access, get_column_height)]
function labor_access_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid || city.get_house(ev.bid)) {
        city.overlay_column_height = -1
        return
    }

    if (!building.params.min_houses_coverage) {
        city.overlay_column_height = -1
        return
    }

    var percentage = labor_access_houses_coverage_percentage(building)
    var height = Math.floor(percentage / 10)
    if (height < 0) {
        height = 0
    } else if (height > 10) {
        height = 10
    }
    city.overlay_column_height = height
}

[es=(overlay_labor_access, show_building)]
function labor_access_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building || city.get_house(ev.bid)) {
        city.overlay_show_building = 0
        return
    }

    if (!building.params.min_houses_coverage) {
        city.overlay_show_building = 0
        return
    }

    if (building.valid) {
        city.overlay_show_building = labor_access_houses_coverage_percentage(building) < 50 ? 1 : 0
        return
    }

    city.overlay_show_building = 0
}
