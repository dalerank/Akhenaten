log_info("akhenaten: overlay labor started")

[es=city_overlay]
overlay_labor {
  id:OVERLAY_LABOR
  title: "#overlay_labor"
  walkers:[]
  buildings:[BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_RISK
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_labor, show_figure)]
function labor_show_figure(ev) {
    var fig = city.get_figure(ev.fid)
    if (!fig.valid) {
        city.overlay_show_figure = 0
        return
    }

    if (fig.type == FIGURE_LABOR_SEEKER) {
        var home = fig.home
        city.overlay_show_figure = (home && home.show_on_problem_overlay) ? 1 : 0
        return
    }

    city.overlay_show_figure = 0
}

[es=(overlay_labor, get_tooltip_for_building)]
function labor_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    var percentage = building.worker_percentage
    if (percentage <= 0) {
        city.overlay_tooltip = __loc(66, 52)
    } else if (percentage <= 20) {
        city.overlay_tooltip = __loc(66, 53)
    } else if (percentage <= 40) {
        city.overlay_tooltip = __loc(66, 54)
    } else if (percentage <= 60) {
        city.overlay_tooltip = __loc(66, 55)
    } else if (percentage <= 80) {
        city.overlay_tooltip = __loc(66, 56)
    } else {
        city.overlay_tooltip = __loc(66, 57)
    }
}

[es=(overlay_labor, get_column_height)]
function labor_building_column_height(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_column_height = -1
        return
    }

    if (!building.max_workers) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = 10 - Math.floor(building.worker_percentage / 10)
}

[es=(overlay_labor, show_building)]
function labor_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building) {
        city.overlay_show_building = 0
        return
    }

    if (building.type == BUILDING_WORK_CAMP) {
        city.overlay_show_building = 1
        return
    }

    if (building.valid) {
        if (building.show_on_problem_overlay) {
            city.overlay_show_building = 1
            return
        }

        if (building.max_workers > 0 && building.num_workers <= 0) {
            city.overlay_show_building = 1
            return
        }
    }

    city.overlay_show_building = 0
}
