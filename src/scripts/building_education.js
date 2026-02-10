log_info("akhenaten: building education started")

building_scribal_school = {
  animations : {
    preview : { pack:PACK_GENERAL, id:42},
    base : { pack:PACK_GENERAL, id:42},
    work : { pos:[2, -25], pack:PACK_GENERAL, id:42, offset:1, max_frames:11, duration:4, can_reverse:true },
    papyrus : { pos:[61, 14], pack:PACK_GENERAL, id:207, offset:0},
  }
  input : {
    resource : RESOURCE_PAPYRUS
  }
  meta : { help_id: 68, text_id: 85 }
  min_houses_coverage : 50
  building_size : 2
  labor_category : LABOR_CATEGORY_EDUCATION
  cost : [ 30, 50, 70, 100, 150 ]
  desirability : { value:[4], step:[1], step_size:[-1], range:[4] }
  laborers:[10], fire_risk:[6], damage_risk: [2]
  max_service: 75
}

building_library {
  animations {
    preview { pos[0, 0], pack:PACK_GENERAL, id:43 }
    base { pos[0, 0], pack:PACK_GENERAL, id:43 }
    work { pos[33, -38], pack:PACK_GENERAL, id:43, offset:1, max_frames:12 }
  }

  min_houses_coverage : 50
  meta { help_id: 70, text_id: 87 }
  labor_category : LABOR_CATEGORY_EDUCATION
  building_size : 3
  cost [ 90, 140, 200, 300, 400 ]
  desirability { value[8], step[2], step_size[-2], range[6] }
  laborers[20]
  fire_risk[6]
  damage_risk[1]
  max_service: 800
}


building_academy {
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:44 }
    base { id:4 }
    work { pos [36, -4], id:4, offset:1, max_frames:18 }
  }

  overlay : OVERLAY_EDUCATION
  labor_category : LABOR_CATEGORY_EDUCATION
  building_size : 2
  cost [ 200, 250, 300, 400, 500 ]
  desirability { value[-3], step[1], step_size[1], range[3] }
  laborers [20]
  fire_risk [4]
  damage_risk [1]
  max_service: 100
}