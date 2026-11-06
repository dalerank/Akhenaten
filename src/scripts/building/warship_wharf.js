log_info("akhenaten: loading building_warship_wharf")

building_warship_wharf = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:28 },
    base : { pack:PACK_TERRAIN, id:28 },
    //work_n : { pos:[65, 0], pack:PACK_SPR_AMBIENT, id:47, offset:0, max_frames:24, duration:1 },
    work_w : { pos:[80, 7], pack:PACK_SPR_AMBIENT, id:47, offset:0, max_frames:24, duration:3 },
    work_s : { pos:[65, 7], pack:PACK_SPR_AMBIENT, id:56, offset:1, max_frames:20, duration:4 },
    work_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:46, offset:3, max_frames:24, duration:4 },
    wait_n : { pos:[85, 20], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    wait_w : { pos:[85, 7], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:3 },
    wait_s : { pos:[65, 22], pack:PACK_SPR_AMBIENT, id:55, offset:1, max_frames:25, duration:4 },
    wait_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:4 },
  },
  building_size : 3,
  meta : { text_id: 175, help_link:"message_building_warship_wharf" }
  info_sound : "Wavs/shipyrd_r.wav"
  planner_update_rule : {
    relative_orientation: 1
  }

  needs : {
    water_access : true,
    shoreline : true
  }
  labor_category : LABOR_CATEGORY_MILITARY,
  // OG spawn_wharf: generate_labor_seeker when houses_covered < 51.
  min_houses_coverage : 50
  cost: [ 120, 150, 200, 300, 400 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[15], fire_risk:[1], damage_risk: [1]
}

function building_warship_wharf_can_place(ev) {
    if (ev.state != CAN_PLACE) {
        city_planner.finalize_check_result = ev.state
        return
    }

    // OG CONSTRUCTION_PLACE_RULE_MAX_WARSHIP_WHARVES = 6
    if (city.count_active_buildings(BUILDING_WARSHIP_WHARF) >= 6) {
        city_planner.set_warning("#full_complement_of_warship_wharves")
        city_planner.finalize_check_result = CAN_NOT_PLACE
        return
    }

    // OG check_open_water_site: inland lakes without sea access are refused.
    if (!terrain.is_connected_to_open_water(ev.end)) {
        city_planner.set_warning("#inland_lake_has_no_sea_access")
        city_planner.finalize_check_result = CAN_NOT_PLACE
        return
    }

    city_planner.finalize_check_result = ev.state
}

[es=(building_warship_wharf, can_place)]
function building_warship_wharf_can_place_es(ev) {
    building_warship_wharf_can_place(ev)
}

[es=(building_warship_wharf, finalize_check)]
function building_warship_wharf_finalize_check_es(ev) {
    building_warship_wharf_can_place(ev)
}

[es=(building_warship_wharf, on_place_checks)]
function building_warship_wharf_on_place_checks(ev) {
    city.warnings.show_if_not(city.count_active_buildings(BUILDING_SHIPWRIGHT) > 0, "#warning_shipwright_needed")
}

[es=(building_warship_wharf, update_graphic)]
function building_warship_wharf_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var boat = building.get_figure(BUILDING_SLOT_BOAT)
    var moored = boat.valid && (boat.action_state == ACTION_8_WARSHIP_WAITING || boat.action_state == ACTION_20_WARSHIP_DOCKED)
    building_wharf_update_graphic_moored(building, moored)
}

[es=(building_warship_wharf, highlight_waypoints)]
function building_warship_wharf_highlight_waypoints(ev) {
    var building = city.get_building(ev.bid)
    __map_highlight_set(building.water_access_tile(0), HIGHLIGHT_GREEN)
    __map_highlight_set(building.water_access_tile(1), HIGHLIGHT_GREEN)
}
