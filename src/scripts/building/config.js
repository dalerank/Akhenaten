log_info("akhenaten: building info started")

function get_building_config(name) {
    return __js_global(name)
}

function get_building_config_by_id(type) {
    return get_building_config(__building_static_config_name(type))
}
function building_is_unique_built(type) {
    var cfg = get_building_config_by_id(type)
    if (!cfg || !cfg.planner_update_rule || !cfg.planner_update_rule.unique_building) return false
    return __city_count_total_buildings(type) > 0
}

build_planner_clear_land {
  show_in_debug: false
  planner_update_rule {
    is_draggable : true
  }
}

building_burning_ruin = {
  animations : {
    base0 : { pack:PACK_TERRAIN, id:36, offset:0 },
    fire0 : { pack:PACK_TERRAIN, id:36, offset:1, max_frames:8, duration:2 },
    base1 : { pack:PACK_TERRAIN, id:36, offset:9 },
    fire1 : { pack:PACK_TERRAIN, id:36, offset:10, max_frames:8, duration:2 },
    base2 : { pack:PACK_TERRAIN, id:36, offset:18 },
    fire2 : { pack:PACK_TERRAIN, id:36, offset:19, max_frames:8, duration:2 },
    base3 : { pack:PACK_TERRAIN, id:36, offset:27 },
    fire3 : { pack:PACK_TERRAIN, id:36, offset:28, max_frames:8, duration:2 },
  },
  fire_animations : 4,
  building_size : 1,
  fire_proof : true,
  damage_proof : true,
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
}

building_stonemason_guild = {
  animations : {
    preview : { pack:PACK_GENERAL, id:88 },
    base : { pack:PACK_GENERAL, id:88 },
    work : { pos:[73, -12], pack:PACK_GENERAL, id:88, offset:1, max_frames:12, duration:4 },
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  building_size: 2
  meta : { text_id: 173, help_link:"message_construction_guilds" }
  cost: [ 30, 50, 80, 100, 150 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[0], damage_risk: [1]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_guild: true
    is_industry: true
  }
}

building_bricklayers_guild = {
  animations : {
    preview : { pack:PACK_GENERAL, id:57 },
    base : { pack:PACK_GENERAL, id:57 },
    work : { pos : [75, -14], pack:PACK_GENERAL, id:57, offset:1, max_frames:12, duration:4 },
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  input : {
    resource : RESOURCE_BRICKS
  }
  min_houses_coverage : 100
  meta : { text_id:172, help_link:"message_construction_guilds" }
  building_size : 2
  cost: [ 20, 40, 80, 120, 200 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [4] }
  laborers:[10], fire_risk:[2], damage_risk: [2]
  max_workers : 1
  info_advisors [ADVISOR_LABOR]
  flags {
    is_guild: true
    is_industry: true
  }
}

building_carpenters_guild = {
  animations : {
    preview : { pack:PACK_GENERAL, id:91 },
    base : { pack:PACK_GENERAL, id:91 },
    work : { pos : [73, -12], pack:PACK_GENERAL, id:91, offset:1, max_frames:13, duration:4 },
  }
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  building_size : 2
  meta : { help_link:"message_construction_guilds" }
  cost : [ 10, 15, 30, 50, 100 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [4] }
  laborers:[8], fire_risk:[4], damage_risk: [2]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_guild: true
    is_industry: true
  }
}

building_military_academy = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    work : { pos : [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  },
  meta : { text_id: 135, help_link:"message_building_recruiter_academy" }
  building_size : 4,
  min_houses_coverage : 50
  cost : [ 240, 300, 500, 1000, 1500 ]
  desirability : { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers:[25], fire_risk:[4], damage_risk: [1]
  flags {
    is_military: true
  }
}

building_military_academy_adv = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    work : { pos : [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  },
  meta : { text_id: 135, help_link:"message_building_recruiter_academy" }
  building_size : 4,
  cost : [ 300, 500, 1000, 1500, 2000 ]
  desirability : { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers:[30], fire_risk:[4], damage_risk: [1]
  flags {
    is_military: true
  }
}

building_reed_gatherer {
  animations {
    preview { pos : [0, 0], pack:PACK_GENERAL, id:24 }
    base { pos : [0, 0], pack:PACK_GENERAL, id:24 }
    work { pos : [30, -17], pack:PACK_GENERAL, id:24, offset:1, max_frames:19, duration:4 }
    reeds { pos : [35, 4], pack:PACK_GENERAL, id:206 }
  }
  output {
    resource : RESOURCE_REEDS
  }
  flags {
    is_harvester: true
    is_industry: true
  }
  building_size : 2
  meta { text_id : 116, help_link:"message_building_woodcutter_and_reed_gatherer" }
  info_sound : "Wavs/reedfarm.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  min_houses_coverage : 100
  max_storage_amount : 200
  max_gatherers : 1
  cost [ 10, 20, 40, 80, 120 ]
  desirability { value[-2], step[1], step_size[1], range[2] }
  laborers[8]
  fire_risk[2]
  damage_risk[3]
}

building_wood_cutter {
  animations {
    preview { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    base { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    work { pos : [30, -17], pack:PACK_GENERAL, id:65, offset:1, max_frames:12, duration:4 }
  }
  overlay_anims {
    wood {
      pos : [65, 3]
      pack:PACK_GENERAL
      id:202
      resource : RESOURCE_TIMBER
      default_active : true
    }
  }
  output {
    resource : RESOURCE_TIMBER
  }
  flags {
    is_harvester: true
    is_industry: true
  }
  building_size : 2
  meta { text_id:120, help_link:"message_building_woodcutter_and_reed_gatherer" }
  info_sound : "Wavs/lumber.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  min_houses_coverage : 100
  max_gatherers : 1
  cost [ 10, 20, 40, 80, 140 ]
  desirability { value[-4], step[1], step_size[1], range[3] }
  laborers[8], fire_risk[4], damage_risk[3]
}

building_artisans_guild = {
  animations : {
    preview : { pack:PACK_EXPANSION, id:31 },
    base : { pack:PACK_EXPANSION, id:31 },
    work : { pos : [75, -14], pack:PACK_EXPANSION, id:31, offset:1, max_frames:12, duration:4 },
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  input : {
    resource : RESOURCE_PAINT
    resource_second : RESOURCE_CLAY
  }
  min_houses_coverage : 100
  meta : { text_id: 312, help_link:"message_construction_guilds" }
  building_size: 2
  cost: [ 30, 50, 80, 100, 150 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [4] }
  laborers:[15], fire_risk:[2], damage_risk: [2]
  max_workers : 1
  info_sound : "Wavs/eng_r.wav"
  info_advisors [ADVISOR_LABOR]
  flags {
    is_guild: true
    is_industry: true
  }
}

building_tax_collector = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:63 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:63 },
    work : { pos : [60, -45], pack:PACK_GENERAL, id:63, offset:1, max_frames:11 },
  }
  labor_category : LABOR_CATEGORY_GOVERNMENT
  meta : { text_id:106, help_link:"message_building_tax_collector" }
  info_sound : "Wavs/taxfarm.wav"
  building_size : 2
  min_houses_coverage : 50
  cost: [ 15, 20, 40, 70, 100 ]
  desirability : { value:[3], step:[1], step_size:[-1], range: [3] }
  laborers:[6], fire_risk:[4], damage_risk: [3]
  flags {
    is_tax_collector: true
    is_administration: true
  }
}

building_tax_collector_up = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:64 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    work : { pos : [10, 10], pack:PACK_GENERAL, id:64, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  meta : { text_id:120, help_link:"message_building_tax_collector" }
  info_sound : "Wavs/taxfarm.wav"
  building_size : 2
  cost: [ 15, 24, 40, 80, 100 ]
  desirability : { value:[3], step:[1], step_size:[-1], range: [3] }
  laborers:[8], fire_risk:[4], damage_risk: [3]
  flags {
    is_tax_collector: true
    is_administration: true
  }
}

building_recruiter = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:166 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:166 },
    work : { pos : [10, 10], pack:PACK_GENERAL, id:166, offset:1, max_frames:11 },
  }
  labor_category : LABOR_CATEGORY_MILITARY
  min_houses_coverage : 100
  meta : { text_id:136, help_link:"message_building_recruiter_academy" }
  info_sound : "Wavs/barracks.WAV"
  building_size : 3
  planner_update_rule : {
    unique_building : true
  }
  cost: [ 30, 50, 100, 200, 300 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [3] }
  laborers:[10], fire_risk:[4], damage_risk: [1]
  flags {
    is_military: true
  }
}

building_festival_square = {
  animations : {
    base : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
    square : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
  },
  building_size : 5,
  meta : { text_id: 188, help_link:"message_building_festival_square" }
  info_sound : "Wavs/prefecture.wav"
  fire_proof : true,
  damage_proof : true,
  planner_update_rule : {
    unique_building : true
  }
  cost : [ 100, 250, 500, 1000, 1500 ]
  desirability : { value:[16], step:[2], step_size:[-3], range: [5] }
  flags {
    is_religion: true
  }
}

building_roadblock = {
  animations : {
    preview : { pack:PACK_GENERAL, id:98 },
    base : { pack:PACK_GENERAL, id:98 },
    minimap: {pack:PACK_GENERAL, id:149, offset:5},
  },
  building_size : 1,
  fire_proof : true,
  damage_proof : true,
  meta : { text_id: 155, help_link:"message_building_roadblock" }
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  cost : [1, 2, 5, 10, 20 ]
  flags {
    no_road_access: true
  }
}

building_brick_tower = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:98 },
    base : { pack:PACK_TERRAIN, id:98 },
  },
  building_size : 2,
  fire_proof : true,
  labor_category : LABOR_CATEGORY_MILITARY,
  min_houses_coverage : 50
  meta : { help_link:"message_building_defensive_structures" }
  cost : [ 50, 100, 150, 300, 500 ]
  desirability : { value:[16], step:[2], step_size:[-3], range: [5] }
  laborers:[20], fire_risk:[0], damage_risk: [4]
  flags {
    is_wall: true
    is_tower: true
  }
}

building_clay_tower = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:98 },
    base : { pack:PACK_TERRAIN, id:98 },
  },
  building_size : 2,
  fire_proof : true,
  labor_category : LABOR_CATEGORY_MILITARY,
  min_houses_coverage : 50
  meta : { help_link:"message_building_defensive_structures" }
  cost : [ 50, 80, 100, 150, 300 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [6] }
  laborers:[20], fire_risk:[4], damage_risk: [4]
  flags {
    is_wall: true
    is_defense: true
  }
}

building_mud_tower = {
  animations : {
    preview : { pack:PACK_GENERAL, id:135 },
    base : { pack:PACK_GENERAL, id:135 },
  }
  building_size : 2
  fire_proof : true
  meta : { text_id: 159, help_link:"message_building_defensive_structures" }
  labor_category : LABOR_CATEGORY_MILITARY
  min_houses_coverage : 50
  cost: [ 30, 50, 100, 150, 200 ]
  desirability : { value:[-8], step:[1], step_size:[2], range: [3] }
  laborers:[6], fire_risk:[0], damage_risk: [3]
  flags {
    is_wall: true
    is_defense: true
  }
}

building_ferry {
  animations {
    preview { pack:PACK_TERRAIN, id:23 }
    base { pack:PACK_TERRAIN, id:23 }
    work { pack:PACK_TERRAIN, id:23 }
    top { pack:PACK_TERRAIN, id:23 }
    minimap {pack:PACK_GENERAL, id:149, offset:210}
  }
  building_size : 2
  needs {
    water_access : true,
    shoreline : true
  }
  planner_update_rule {
    ferries : true
    relative_orientation: 1
  }
  flags {
    is_water_crossing: true
    is_infrastructure: true
  }
  fire_proof : true,
  meta { text_id: 91, help_link:"message_game_concept_water_crossings" }
  labor_category : LABOR_CATEGORY_GOVERNMENT
  cost [8, 15, 30, 50, 100 ]
  desirability { value[-5], step[2], step_size[2], range[4] }
  laborers[5]
  fire_risk[0]
  damage_risk[2]
}

building_shipyard = {
  animations : {
    preview : { pack: PACK_TERRAIN, id:26, max_frames:1 },
    base : { pack: PACK_TERRAIN, id:26, max_frames:1 },
    wood : { pos : [55, 20], pack:PACK_GENERAL, id:202 },
    work_warship : { pos : [70, 20], pack:PACK_SPR_AMBIENT, id:52, max_frames: 12, duration:4 },
    work_fishing_boat : { pos : [70, 20], pack:PACK_SPR_AMBIENT, id:54, max_frames: 11, duration:4 },
    work_transport : { pos : [70, 20], pack:PACK_SPR_AMBIENT, id:54, max_frames: 11, duration:4 },
  }
  transport_progress_cost : 400
  warship_progress_cost : 400
  fishingboat_progress_cost : 100
  input : {
    resource : RESOURCE_TIMBER
  }
  building_size : 3
  planner_update_rule : {
    relative_orientation: 1
  }
  meta : { text_id: 100, help_link:"message_building_whipwright" }
  info_sound : "Wavs/shipyrd.wav"
  needs : {
    water_access : true
    shoreline : true
  }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  min_houses_coverage : 50
  cost : [ 70, 100, 150, 200, 300 ]
  desirability : { value:[-12], step:[2], step_size:[2], range: [6] }
  laborers:[20], fire_risk:[4], damage_risk: [1]
  flags {
    is_industry: true
  }
}

building_plaza {
  animations {
    preview { pack:PACK_GENERAL, id:168 },
    base { pack:PACK_GENERAL, id:168 },
  },
  planner_update_rule {
    is_draggable : true
  }

  fire_proof : true
  damage_proof : true
  meta { text_id : 137, help_link:"message_building_garden_plaze_statue" }
  info_sound : "Wavs/FANFARE1.wav"
  building_size : 1
  cost [ 3, 5, 10, 15, 20 ]
  desirability { value[4], step[1], step_size[-2], range[2] }
  flags {
    is_beautification: true
  }
}

building_garden {
  animations {
    preview { pack:PACK_GENERAL, id:59 }
    base { pack:PACK_GENERAL, id:59 }
  }

  variants1 {
    _1 { pack:PACK_GENERAL, id:59, offset:0 }
    _2 { pack:PACK_GENERAL, id:59, offset:1 }
    _3 { pack:PACK_GENERAL, id:59, offset:2 }
    _4 { pack:PACK_GENERAL, id:59, offset:3 }
  }

  variants2 {
    _1 { pack:PACK_GENERAL, id:59, offset:4 }
    _2 { pack:PACK_GENERAL, id:59, offset:5 }
    _3 { pack:PACK_GENERAL, id:59, offset:6 }
  }

  variants3 {
    _1 { pack:PACK_GENERAL, id:59, offset:7 }
  }

  planner_update_rule : {
    is_draggable : true
  }

  fire_proof : true
  damage_proof : true
  meta { text_id:79, help_link:"message_building_garden_plaze_statue" }
  info_sound : "Wavs/park1.wav"
  building_size : 1
  cost [ 3, 5, 10, 15, 20 ]
  desirability { value[3], step[1], step_size[-1], range[3] }
  flags {
    is_beautification: true
    no_road_access: true
  }
}

building_road {
  show_in_debug: false
  animations {
    preview { pack:PACK_TERRAIN, id:33 }
    base { pack:PACK_TERRAIN, id:33 }
  }

  building_size : 1
  cost [ 1, 2, 5, 10, 15 ]
  planner_update_rule {
    is_draggable : true
  }
  flags {
    no_road_access: true
  }
}

building_irrigation_ditch {
  animations {
    preview { pack:PACK_TERRAIN, id:33 }
    base { pack:PACK_TERRAIN, id:33 }
    set_begin { pack:PACK_TERRAIN, id:9 }
  }

  building_size : 1
  planner_update_rule {
    is_draggable : true
  }

  needs {
    canals : false
  }

  cost [ 2, 4, 7, 10, 15 ]
  canal_irrigation_value_multiplier : 2
  flags {
    no_road_access: true
  }
}

building_sandstone_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:197 },
    base { pack:PACK_GENERAL, id:197 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_SANDSTONE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:162, help_link:"message_building_stone_quarries" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }
  flags {
    is_extractor: true
    is_industry: true
  }
  cost [ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[1]
}

building_marble_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:197 },
    base { pack:PACK_GENERAL, id:197 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16 }
  }
  meta { text_id:118, help_link:"message_building_stone_quarries" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  cost[ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[1]

  flags {
    is_extractor: true
    is_industry: true
  }
}

building_stone_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:187 },
    base { pack:PACK_GENERAL, id:187 },
    work { pos : [84, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 6, duration:3, internal_offset:true }
    work_2 { pos : [44, 20], pack:PACK_SPR_AMBIENT, id:49, offset:7, max_frames: 6, duration:3, internal_offset:true }
  }
  output {
    resource : RESOURCE_STONE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:118, help_link:"message_building_stone_quarries" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }

  flags {
    is_extractor: true
    is_industry: true
  }

  cost [ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[2]
}

building_granite_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:38 },
    base { pack:PACK_GENERAL, id:38 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_GRANITE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:162, help_link:"message_building_stone_quarries" }
  info_sound : "Wavs/marble.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }
  flags {
    is_extractor: true
    is_industry: true
  }
  cost [ 20, 40, 80, 150, 200 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[1]
}

building_limestone_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:170 },
    base { pack:PACK_GENERAL, id:170 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_LIMESTONE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:162, help_link:"message_building_stone_quarries" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }
  cost [ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[2]

  flags {
    is_extractor: true
    is_industry: true
  }
}

building_clay_gatehouse = {
  animations : {
    preview : { pack:PACK_GENERAL, id:218 },
    base_n : { pack:PACK_GENERAL, id:218 },
    base_second_n : { pack:PACK_GENERAL, id:219 },
    base_cover_n : { pack:PACK_GENERAL, id:220 },

    base_w : { pack:PACK_GENERAL, id:218, offset:1 }
    base_second_w : { pack:PACK_GENERAL, id:219, offset:1 }
    base_cover_w : { pack:PACK_GENERAL, id:220, offset:1 }
  }
  
  ghost : {
      main_view_offset : [[-55, 20], [-55, -35], [-55, -35], [-60, -40]]
      part_view_offset : [[35, 65], [5, -70], [-200, -55], [-180, 46]]
  }

  building_size : 1
  meta : { text_id:90, help_link:"message_building_defensive_structures" }
  cost : [ 60, 90, 150, 250, 300 ]
  desirability : { value:[-5], step:[1], step_size:[1], range: [5] }
  laborers:[9], fire_risk:[0], damage_risk: [2]
  flags {
    is_wall: true
    is_gatehouse: true
  }
}

building_brick_gatehouse = {
  animations : {
    preview : { pack:PACK_GENERAL, id:218 },
    base_n : { pack:PACK_GENERAL, id:218 },
    base_second_n : { pack:PACK_GENERAL, id:219 },
    base_cover_n : { pack:PACK_GENERAL, id:220 },

    base_w : { pack:PACK_GENERAL, id:218, offset:1 },
    base_second_w : { pack:PACK_GENERAL, id:219, offset:1 },
    base_cover_w : { pack:PACK_GENERAL, id:220, offset:1 },
  }
  
  ghost : {
      main_view_offset : [[-55, 20], [-55, -35], [-55, -35], [-60, -40]]
      part_view_offset : [[35, 65], [5, -70], [-200, -55], [-180, 46]]
  }

  building_size : 1
  meta : { text_id:90, help_link:"message_building_defensive_structures" }
  cost : [ 60, 90, 150, 250, 300 ]
  desirability : { value:[-7], step:[1], step_size:[1], range: [6] }
  laborers:[9], fire_risk:[0], damage_risk: [2]
  flags {
    is_defense: true
    is_wall: true
  }
}

building_tower_gatehouse = {
   animations : {
    preview : { pack:PACK_GENERAL, id:213 },
    base : { pack:PACK_GENERAL, id:213 },
    base_osiris : { pack:PACK_GENERAL, id:213 },
    base_ra : { pack:PACK_GENERAL, id:214 },
    base_ptah : { pack:PACK_GENERAL, id:215 },
    base_seth : { pack:PACK_GENERAL, id:216 },
    base_bast : { pack:PACK_GENERAL, id:217 },
  }

  info_title_id:"#tower_gatehouse"
  building_size : 2
  meta : { text_id:90, help_link:"message_building_defensive_structures" }
  cost : [ 200, 300, 400, 500, 600 ]
  desirability : { value:[4], step:[1], step_size:[1], range: [3] }
  laborers:[6], fire_risk:[0], damage_risk: [2]
  flags {
    is_defense: true
    is_wall: true
  }
}

building_mud_gatehouse = {
  animations : {
    preview : { pack:PACK_GENERAL, id:218 },
    base_n : { pack:PACK_GENERAL, id:218 },
    base_second_n : { pack:PACK_GENERAL, id:219 },
    base_cover_n : { pack:PACK_GENERAL, id:220 },

    base_w : { pack:PACK_GENERAL, id:218, offset:1 },
    base_second_w : { pack:PACK_GENERAL, id:219, offset:1 },
    base_cover_w : { pack:PACK_GENERAL, id:220, offset:1 },
  }

  ghost : {
      main_view_offset : [[0, 0], [0, 2], [-28, -14], [0, 0], [0, 0], [-28, -15], [-28, -15]]
      part_view_offset : [[28, -15], [28, 15], [0, 0], [28, -15], [28, -15], [-0, -2], [0, -2]]
  }

  building_size : 1
  meta : { text_id:90, help_link:"message_building_defensive_structures" }
  cost : [ 50, 70, 100, 150, 200 ]
  desirability : { value:[-6], step:[1], step_size:[2], range: [6] }
  laborers:[3], fire_risk:[0], damage_risk: [3]
  flags {
    is_defense: true
    is_wall: true
  }
}

// Decorative composite gatehouse (original type 202): 2x2 special wall + 1x2 gate + 2x2 special wall (5x2).
building_decorative_gatehouse = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:318 },
    wall_left_0_0 : { pack:PACK_TERRAIN, id:314 },
    wall_left_1_0 : { pack:PACK_TERRAIN, id:315 },
    gate_0_0 : { pack:PACK_TERRAIN, id:318 },
    wall_right_0_0 : { pack:PACK_TERRAIN, id:316 },
    wall_right_1_0 : { pack:PACK_TERRAIN, id:317 },
    wall_left_0_1 : { pack:PACK_TERRAIN, id:324 },
    wall_left_1_1 : { pack:PACK_TERRAIN, id:325 },
    gate_0_1 : { pack:PACK_TERRAIN, id:319 },
    wall_right_0_1 : { pack:PACK_TERRAIN, id:326 },
    wall_right_1_1 : { pack:PACK_TERRAIN, id:327 },
  }

  building_size : 5
  meta : { text_id:90, help_link:"message_building_defensive_structures" }
  cost : [ 100, 150, 200, 300, 400 ]
  desirability : { value:[-6], step:[1], step_size:[2], range: [6] }
  laborers:[3], fire_risk:[0], damage_risk: [3]
  flags {
    is_defense: true
    is_wall: true
    is_gatehouse: true
  }
}

building_brick_wall = {
  animations : {
    preview : { pack:PACK_GENERAL, id:138, offset:27 },
    base : { pack:PACK_GENERAL, id:138 },
  }
  building_size : 1
  planner_update_rule : {
    is_draggable : true
  }
  cost : [ 7, 12, 25, 40, 70 ]
  desirability : { value:[-3], step:[3], step_size:[3], range:[3] }
  laborers : [0]
  fire_risk : [0]
  damage_risk : [0]
  flags {
    is_wall: true
    is_defense: true
  }
}

building_mud_wall = {
  animations : {
    preview : { pack:PACK_GENERAL, id:138, offset:27 },
    base : { pack:PACK_GENERAL, id:138 },
  }
  building_size : 1
  planner_update_rule : {
    is_draggable : true
  }
  cost : [ 7, 12, 25, 40, 70 ]
  desirability : {
    value : [-3]
    step : [3]
    step_size : [3]
    range : [3]
  }
  flags {
    is_wall: true
    is_defense: true
  }
}

building_police_station = {
  animations {
    preview { pack:PACK_GENERAL, id:64 },
    base { pack:PACK_GENERAL, id:64 },
    work { pos[20, -40], pack:PACK_GENERAL, id:64, offset:1, max_frames:12 },
    resources {pack:PACK_GENERAL, id:99, offset:2},
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  min_houses_coverage : 50
  meta : { text_id: 88, help_link:"message_building_police_station" }
  building_size : 1
  cost [ 6, 12, 25, 40, 60 ]
  desirability { value[-2], step[1], step_size[1], range[2] }
  laborers [6]
  fire_risk [2]
  damage_risk [2]
  weapon_spot_pos [20, -20]
  flags {
    is_infrastructure: true
  }
}