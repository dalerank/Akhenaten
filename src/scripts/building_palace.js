log_info("akhenaten: building palace started")

building_village_palace {
  animations {
    preview { pack:PACK_GENERAL, id:47 },
    base { pack:PACK_GENERAL, id:47 },
    work { pos : [24, -20], pack:PACK_GENERAL, id:47, offset:1, max_frames:5, duration:5, can_reverse:true }
  }

  labor_category : LABOR_CATEGORY_GOVERNMENT
  planner_update_rule {
    unique_building : true
  }
  meta { help_id:77, text_id:105 }
  building_size : 4
  needs {
    groundwater : true
  }
  flags {
    is_palace: true
    is_administration: true
  }
  cost [ 100, 200, 300, 400, 500 ]
  desirability { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers[20]
  fire_risk[4]
  damage_risk [1]
}

building_town_palace {
  animations {
    preview { pack:PACK_GENERAL, id:39 },
    base { pack:PACK_GENERAL, id:39 },
    work { pos : [-1, -1], pack:PACK_GENERAL, id:39, offset:1, max_frames:12 }
  }

  labor_category : LABOR_CATEGORY_GOVERNMENT
  planner_update_rule {
    unique_building : true
  }

  meta { help_id:77, text_id:105 }
  building_size : 5

  needs {
    groundwater : true
  }

  flags {
    is_palace: true
    is_administration: true
  }

  cost [ 200, 300, 400, 500, 800 ]
  desirability { value:[8], step:[2], step_size:[-1], range: [6] }
  laborers[30]
  fire_risk[4]
  damage_risk[1]
}

building_city_palace {
  animations {
    preview { pack:PACK_GENERAL, id:18 },
    base { pack:PACK_GENERAL, id:18 },
    work { pos : [-1, -1], pack:PACK_GENERAL, id:18, offset:1, max_frames:12 }
  }

  labor_category : LABOR_CATEGORY_GOVERNMENT

  planner_update_rule {
    unique_building : true
  }

  meta { help_id:77, text_id:105 }
  building_size : 6

  needs {
    groundwater : true
  }

  flags {
    is_palace: true
    is_administration: true
  }

  cost [ 300, 400, 500, 800, 1000 ]
}

building_palace_base {
  tooltips [
    function() { return {
      label:  __loc(68, 135)
      value:  "" + city.unemployment_percentage + "%"
    }}

    function() { return {
      label:  __loc(68, 136)
      value:  "" + city.rating.culture
    }}

    function() { return {
      label:  __loc(68, 137)
      value:  "" + city.rating.prosperity
    }}

    function() { return {
      label:  __loc(68, 138)
      value:  "" + city.rating.monument
    }}

    function() { return {
      label:  __loc(68, 139)
      value:  "" + city.rating.kingdom
    }}
  ]
}

[es=building_palace_show_tooltip]
function on_building_palace_show_tooltip(ev) {
    var tooltip_lines = building_palace_base.tooltips
    if (!tooltip_lines || tooltip_lines.length === 0) {
      return
    }

    var width = 220
    var line_height = 14
    var height = tooltip_lines.length * line_height + 10
    var pos = {x: 0, y: 0}
    if (ev.mx < width + 20) {
        pos.x = ev.mx + 20
    } else {
        pos.x = ev.mx - width - 20
    }

    if (ev.my < 200) {
        pos.y = ev.my + 10
    } else if (ev.my + height - 32 > game.screen.h) {
        pos.y = game.screen.h - height
    } else {
        pos.y = ev.my - 32
    }

    log_info("akhenaten: building_palace_show_tooltip", ev)
    ui.begin_widget(pos)
    ui.fill_rect({x: 0, y: 0}, {w: width, h: height}, COLOR_TOOLTIP_FILL)
    ui.border({x: 0, y: 0}, {w: width, h: height}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)

    var label = {x: 5, y: 5}
    var value_x = 140
    for (var i = 0; i < tooltip_lines.length; i++) {
        var line = tooltip_lines[i]()
        var tlabel = label
        var tvalue = {x: value_x, y: label.y}
        ui.label_colored(line.label, tlabel, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT)
        ui.label_colored(line.value, tvalue, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT)

        label.y += line_height
    }
    ui.end_widget()
}