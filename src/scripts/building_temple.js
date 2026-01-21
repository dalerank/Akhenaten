log_info("akhenaten: building temple started")

building_temple_osiris {
    animations {
      preview { pack:PACK_GENERAL, id:25 }
      base { pack:PACK_GENERAL, id:25 }
      work { pos[80, -125], pack:PACK_GENERAL, id:25, offset:1, max_frames:8 }
    }
  
    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    building_size : 3
    meta { help_id: 67, text_id: 92 }
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
    }
  }
  
  building_temple_ra {
    animations {
      preview { pack:PACK_GENERAL, id:21 }
      base { pack:PACK_GENERAL, id:21 }
      work { pos[80, -123], pack:PACK_GENERAL, id:21, offset:1, max_frames:11 }
    }
  
    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    building_size : 3
    meta  { help_id: 67, text_id: 93 }
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
    }
  }
  
  building_temple_ptah {
    animations : {
      preview : { pack:PACK_GENERAL, id:20 },
      base : { pack:PACK_GENERAL, id:20 },
      work : { pos : [70, -103], pack:PACK_GENERAL, id:20, offset:1, max_frames:11 },
    }
  
    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    building_size : 3
    meta { help_id: 67, text_id: 94 }
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
    }
  }
  
  building_temple_seth {
    animations {
      preview { pack:PACK_GENERAL, id:19 }
      base { pack:PACK_GENERAL, id:19 }
      work { pos[70, -133], pack:PACK_GENERAL, id:19, offset:1, max_frames:11 }
    }
  
    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    building_size : 3
    meta { help_id: 67, text_id: 95 }
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
    }
  }
  
  building_temple_bast {
    animations {
      preview { pack:PACK_GENERAL, id:76 }
      base { pack:PACK_GENERAL, id:76 }
      work { pos[85, -115], pack:PACK_GENERAL, id:76, offset:1, max_frames:11 }
    }
  
    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    building_size : 3
    meta { help_id: 67, text_id: 96 }
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
    }
  }