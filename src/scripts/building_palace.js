log_info("akhenaten: building palace started")

building_palace_base {
    tooltips [
      "${68.135}\t${city.unemployment_percentage}%",
      "${68.136}\t${rating.culture}",
      "${68.137}\t${rating.prosperity}",
      "${68.138}\t${rating.monument}",
      "${68.139}\t${rating.kingdom}"
    ]
  }
  
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
    tooltips : building_palace_base.tooltips
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
    tooltip_lines : building_palace_base.tooltips
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
    tooltip_lines : building_palace_base.tooltips
  }
  