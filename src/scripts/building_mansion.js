log_info("akhenaten: building mansion started")

building_personal_mansion {
    animations {
      preview { pack:PACK_GENERAL, id:85 }
      base { pack:PACK_GENERAL, id:85 }
      work { pos[30, -70], pack:PACK_GENERAL, id:85, offset:1, max_frames:12, duration:3 }
    }
    labor_category : LABOR_CATEGORY_GOVERNMENT
    min_houses_coverage : 50
    building_size : 3
    meta { help_id:78, text_id:103 }
    planner_update_rule {
      unique_building : true
    }
    cost [ 30, 50, 100, 200, 400 ]
    desirability { value[12], step[2], step_size[-2], range[4] }
    laborers[0], fire_risk[4], damage_risk[1]
    flags {
      is_administration: true
    }
  }
  
  building_village_mansion {
    animations {
      preview { pack:PACK_GENERAL, id:85 }
      base { pack:PACK_GENERAL, id:85 }
      work { pos[-1, -1], pack:PACK_GENERAL, id:85, offset:1, max_frames:12 }
    }
    labor_category : LABOR_CATEGORY_GOVERNMENT
    min_houses_coverage : 50
    building_size : 4
    meta { help_id:78, text_id:103 }
    planner_update_rule {
      unique_building : true
    }
    cost[ 80,  100, 150, 200, 400 ]
    desirability { value[12], step[2], step_size[-2], range[4] }
    laborers[0], fire_risk[4], damage_risk[1]
    flags {
      is_administration: true
    }
  }
  
  building_family_mansion {
    animations {
      preview { pack:PACK_GENERAL, id:86 }
      base { pack:PACK_GENERAL, id:86 }
      work { pos[-1, -1], pack:PACK_GENERAL, id:86, offset:1, max_frames:12 }
    }
    labor_category : LABOR_CATEGORY_GOVERNMENT
    min_houses_coverage : 50
    building_size : 4
    meta { help_id:78, text_id:103 }
    planner_update_rule {
      unique_building : true
    }
    cost[ 80, 120, 150, 200, 300 ]
    desirability { value[20], step[2], step_size[-3], range[5] }
    laborers[0], fire_risk[4], damage_risk[1]
    flags {
      is_administration: true
    }
  }
  
  building_dynasty_mansion {
    animations {
      preview { pack:PACK_GENERAL, id:87 }
      base { pack:PACK_GENERAL, id:87 }
      work { pos[-1, -1], pack:PACK_GENERAL, id:87, offset:1, max_frames:12 }
    }
    labor_category : LABOR_CATEGORY_GOVERNMENT
    building_size : 4
    planner_update_rule {
      unique_building : true
    }
  
    min_houses_coverage : 50
    cost [ 140, 200, 300, 400, 500 ]
    desirability { value[28], step[2], step_size[-4], range[6] }
    laborers[0], fire_risk[4], damage_risk[1]
    flags {
      is_administration: true
    }
  }
  