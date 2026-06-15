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
  meta : { help_id: 84, text_id: 175 }
  planer_update_rule : {
    relative_orientation: 1
  }

  needs : {
    water_access : true,
    shoreline : true
  }
  labor_category : LABOR_CATEGORY_MILITARY,
  min_houses_coverage : 100
  cost: [ 120, 150, 200, 300, 400 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[15], fire_risk:[1], damage_risk: [1]
}

[es=(building_warship_wharf, update_graphic)]
function building_warship_wharf_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var boat = building.get_figure(BUILDING_SLOT_BOAT)
    var moored = boat.valid && boat.action_state == ACTION_203_WARSHIP_MOORED
    building_wharf_update_graphic_moored(building, moored)
}
