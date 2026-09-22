log_info("akhenaten: building palace started")

building_palace_base {
  tooltips [
    function() { return {
      label:  __loc("#TR_PALACE_TOOLTIP_UNEMPLOYMENT")
      value:  "" + city.labor.unemployment_percentage + "%"
    }}

    function() { return {
      label:  __loc("#TR_PALACE_TOOLTIP_CULTURE_RATING")
      value:  "" + city.rating.culture
    }}

    function() { return {
      label:  __loc("#TR_PALACE_TOOLTIP_PROSPERITY_RATING")
      value:  "" + city.rating.prosperity
    }}

    function() { return {
      label:  __loc("#TR_PALACE_TOOLTIP_MONUMENT_RATING")
      value:  "" + city.rating.monument
    }}

    function() { return {
      label:  __loc("#TR_PALACE_TOOLTIP_KINGDOM_RATING")
      value:  "" + city.rating.kingdom
    }}
  ]
}

function building_palace_show_tooltip(ev) {
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
    } else if (ev.my + height - 32 > screen.height) {
        pos.y = screen.height - height
    } else {
        pos.y = ev.my - 32
    }

    ui.begin_widget(pos)
    ui.fill_rect({x: 0, y: 0}, {x: width, y: height}, COLOR_TOOLTIP_FILL)
    ui.border({x: 0, y: 0}, {x: width, y: height}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)

    var label = {x: 5, y: 5}
    var value_x = 180
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
