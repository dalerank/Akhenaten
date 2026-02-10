log_info("akhenaten: building workshop started")

building_brewery {
  animations {
    preview { pack:PACK_GENERAL, id:116 },
    base { pack:PACK_GENERAL, id:116 },
    work { pack:PACK_GENERAL, id:116, max_frames: 12 }
    barley { pos:[28, -35], pack:PACK_GENERAL, id:208, max_frames: 12 }
  }
  input {
    resource : RESOURCE_BARLEY
  }
  output {
    resource : RESOURCE_BEER
  }

  overlay : OVERLAY_BREWERY
  water_amount_for_production : 50
  progress_max : 400,
  production_rate : 50,
  meta { help_id:96, text_id:122 }
  building_size : 2
  cost [ 15, 25, 50, 80, 120 ]
  desirability { value[-5], step[1], step_size[1], range[5] }
  laborers[12]
  fire_risk[4]
  damage_risk[2]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_pottery {
  animations {
    preview { pos[-1, -1], pack:PACK_GENERAL, id:125 }
    base { pos[-1, -1], pack:PACK_GENERAL, id:125 }
    work { pos[36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18, duration:12 }
    clay { pos[60, 30], pack:PACK_GENERAL, id:205, offset:9 }
  }

  input {
    resource : RESOURCE_CLAY
  }

  output {
    resource : RESOURCE_POTTERY
  }

  production_rate : 20
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  meta { help_id:1, text_id:126 }
  cost [ 12, 20, 30, 40, 50 ]
  desirability {
    value[-4]
    step[1]
    step_size[1]
    range[4]
  }
  laborers[12]
  fire_risk[4]
  damage_risk[3]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_weaver = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:122 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:122 },
    work : { pos : [19, -39], pack:PACK_GENERAL, id:122, offset:1, max_frames:12, duration:4 },
    flax : { pos : [45, 3], pack:PACK_GENERAL, id:206 },
  },
  input : {
    resource : RESOURCE_FLAX
  }
  output : {
    resource : RESOURCE_LINEN
  }
  building_size : 2,
  meta : { help_id:97, text_id:123 }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  cost: [ 16, 30, 50, 100, 150 ]
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
  laborers:[12], fire_risk:[4], damage_risk: [3]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_weaponsmith = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:123, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:123, offset:0 },
    work : { pos : [57, -16], pack:PACK_GENERAL, id:123, offset:1, max_frames:20, duration:5, can_reverse:true },
    copper : { pos : [93, 0], pack:PACK_GENERAL, id:203 },
  }

  input : {
    resource : RESOURCE_COPPER
  }
  output : {
    resource : RESOURCE_WEAPONS
  }
  labor_category : LABOR_CATEGORY_MILITARY
  meta : { help_id: 98, text_id: 124 }
  building_size: 2
  cost: [ 24, 40, 80, 120, 150 ]
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
  laborers:[12], fire_risk:[4], damage_risk: [2]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_jewels_workshop = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:119 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:119 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:119, offset:1, max_frames:9 },
  },
  input : {
    resource: RESOURCE_GEMS
  }
  output : {
    resource : RESOURCE_LUXURY_GOODS
  }
  building_size : 2,
  meta : { help_id:99, text_id:125 }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  cost: [ 18, 30, 50, 100, 200 ]
  desirability : { value:[-2], step:[1], step_size:[1], range: [2] }
  laborers:[12], fire_risk:[4], damage_risk: [0]
  material_reduction_per_nearby_workshop : 5
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_papyrus_maker = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:44 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:44 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:44, offset:1, max_frames:10, duration:4 },
    reeds : { pos : [35, 4], pack:PACK_GENERAL, id:206 },
  },
  input : {
    resource : RESOURCE_REEDS
  }
  output : {
    resource : RESOURCE_PAPYRUS
  }
  production_rate : 50,
  building_size : 2,
  meta : { help_id:1, text_id:190 }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  cost: [ 20, 30, 50, 100, 200 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[4], damage_risk: [2]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_bricks_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pos:[46, -20], pack:PACK_GENERAL, id:124, offset:1, max_frames:10, duration:5 },
    straw : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    clay : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  input : {
    resource : RESOURCE_CLAY
    resource_second : RESOURCE_STRAW
  }
  output : {
    resource : RESOURCE_BRICKS
  }
  progress_max : 400,
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  meta : { help_id:1, text_id:180 }
  cost: [ 12, 20, 30, 40, 50 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[2], damage_risk: [3]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_chariots_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pack:PACK_GENERAL, id:124 },
    timber : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    weapon : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  input : {
    resource : RESOURCE_TIMBER
    resource_second : RESOURCE_WEAPONS
  }
  output : {
    resource : RESOURCE_CHARIOTS
  }
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  cost: [ 50, 100, 150, 300, 500 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [6] }
  laborers:[30], fire_risk:[4], damage_risk: [3]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_lamp_workshop {
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:125 }
    base { id:125 }
    work { pos [36, -4], id:125, offset:1, max_frames:18 }
    clay { pos[65, 3], id:207 }
  }
  input {
    resource : RESOURCE_OIL
    resource_second : RESOURCE_TIMBER
  }
  output {
    resource : RESOURCE_LAMPS
  }
  production_rate : 20
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2
  cost [ 20, 30, 50, 100, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [4]
  damage_risk [3]
  flags {
    is_workshop: true
    is_industry: true
  }
}

building_paint_workshop {
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:125 }
    base { id:125 }
    work { pos [36, -4], id:125, offset:1, max_frames:18 }
    clay { pos [65, 3], id:207 }
  }

  input {
    resource : RESOURCE_OIL
  }
  output {
    resource : RESOURCE_PAINT
  }

  production_rate : 20
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  cost [ 20, 30, 50, 100, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [3]
  damage_risk [1]
  flags {
    is_workshop: true
    is_industry: true
  }
}