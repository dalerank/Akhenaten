log_info("akhenaten: ui zoo info window started")

function zoo_info_window_employment_text(b) {
  if (b.num_workers >= b.max_workers) {
    return b.houses_covered < 40 ? "#building_poor_worker_access" : ""
  }
  if (city.population <= 0) {
    return "#building_no_people_in_city"
  }
  if (b.houses_covered <= 0) {
    return "#building_no_workers_nearby"
  }
  if (b.houses_covered < 40) {
    return "#building_poor_worker_access"
  }
  return "#building_labor_could_shift"
}

[es=building_info_window]
info_window_zoo {
  related_buildings [BUILDING_ZOO]
  ui : baseui(building_info_window, {
    advice : text({pos: [36, 164], wrap:400, font : FONT_NORMAL_BLACK_ON_DARK, multiline:true }),
  })
}

[es=(info_window_zoo, init)]
function info_window_zoo_on_init(window) {
  var b = city.get_building(window.bid)
  var zoo = city.get_entertainment_building(window.bid)
  if (!b || !zoo) {
    return
  }

  // Animals present (juggler_visited) wins over empty-feed warnings so a just-fed zoo
  // is not shown as "needs meat" while cages are still occupied.
  var reason = "#zoo_info_empty_cages"
  if (b.has_road_access == false) {
    reason = "#building_no_road_access"
  } else if (b.num_workers <= 0) {
    reason = "#zoo_info_no_workers"
  } else if (zoo.juggler_visited) {
    reason = "#zoo_info_ok"
  } else if (b.stored_resource(RESOURCE_GAMEMEAT) <= 0) {
    reason = "#zoo_info_needs_meat"
  } else if (b.stored_resource(RESOURCE_STRAW) <= 0) {
    reason = "#zoo_info_needs_straw"
  }
  window.warning_text.text = __loc(reason)

  var emp = zoo_info_window_employment_text(b)
  window.workers_desc.text = emp ? __loc(emp) : ""

  window.advice.text = __loc("#zoo_info_game_meat") + " " + b.stored_resource(RESOURCE_GAMEMEAT)
    + "  " + __loc("#zoo_info_straw") + " " + b.stored_resource(RESOURCE_STRAW)
}
