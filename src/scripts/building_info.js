log_info("akhenaten: building info started")

building_info = [
  // { type: "academy", help_id: 69, text_id: 86},
  { type: "library", help_id: 70, text_id: 87},
  { type: "marble_quarry", help_id:95, text_id:118},
  { help_id:93, type:"limestone_quarry", text_id:119},
  { help_id:94, type:"timber_yard", text_id:120},
  { help_id:92, type:"clay_pit", text_id:121},
  { help_id:92, type:"reed_farm", text_id:116},
  { help_id:92, type:"sandstone_quarry", text_id:194},
  { help_id:92, type:"granite_quarry", text_id:192},
  { help_id:92, type:"plainstone_quarry", text_id:118},
  { help_id:89, type:"barley_farm", text_id:181},
  { help_id:90, type:"flax_farm", text_id:115},
  { help_id:90, type:"grain_farm", text_id:112},
  { help_id:91, type:"lettuce_farm", text_id:113},
  { help_id:91, type:"pomegranades_farm", text_id:114},
  { help_id:90, type:"chickpeas_farm", text_id:182},
  { help_id:90, type:"figs_farm", text_id:183},
  { help_id:90, type:"henna_farm", text_id:306},
  { help_id:92, type:"bricklayers_guild", text_id:172},
]

building_small_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 61, offset:1},
    {pack: PACK_GENERAL, id: 61, offset:5},
    {pack: PACK_EXPANSION, id: 37, offset:1},
    {pack: PACK_EXPANSION, id: 37, offset:5},
    {pack: PACK_TEMPLE_RA, id: 1, offset:27},
  ]
}

building_medium_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 8, offset:1},
    {pack: PACK_GENERAL, id: 8, offset:5},
    {pack: PACK_EXPANSION, id: 36, offset:1},
    {pack: PACK_EXPANSION, id: 36, offset:5},
  ]
}

building_big_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 7, offset:1},
    {pack: PACK_GENERAL, id: 7, offset:5},
    {pack: PACK_EXPANSION, id: 35, offset:1},
    {pack: PACK_EXPANSION, id: 35, offset:5},
  ]
}

building_fort = {
  ghost : {
    main : [[-55, -35], [-55, -35], [-55, -35], [-60, -40]],
    ground : [[35, 35], [5, -70], [-200, -55], [-180, 46]],
    ground_check : [[3, -1], [4, -1], [4, 0], [3, 0],
                    [-1,-4], [0, -4], [0,-3], [-1,-3],
                    [-4, 0], [-3, 0], [-3,1], [-4, 1],
                    [0,  3], [1,  3], [1, 4], [0,  4]],
  },
  labor_category : LABOR_CATEGORY_MILITARY,
}

building_cattle_ranch = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_CATTLE_RANCH }
  },
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_granary = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_GRANARY_ANIM, max_frames:23 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_weaponsmith = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_WEAPONSMITH }
  },
  labor_category : LABOR_CATEGORY_MILITARY,
}

building_courthouse = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:62, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:62, },
    work : { pos : [80, -80], pack:PACK_GENERAL, id:62, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_guild_stonemasons = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_GUILD_STONEMASONS }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_bricklayers_guild = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_BRICKLAYERS_GUILD }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_dock = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_BUILDING_DOCK }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_personal_mansion = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_PERSONAL_MANSION }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_temple_osiris = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_OSIRIS }
  },
  labor_category : LABOR_CATEGORY_RELIGION,
}

building_temple_ra = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_RA }
  },
  labor_category : LABOR_CATEGORY_RELIGION,
}

building_temple_ptah = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_PTAH }
  },
  labor_category : LABOR_CATEGORY_RELIGION,
}

building_temple_seth = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_SETH }
  },
  labor_category : LABOR_CATEGORY_RELIGION,
}

building_temple_bast = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_BAST }
  },
  labor_category : LABOR_CATEGORY_RELIGION,
}

building_juggler_school = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_JUGGLER_SCHOOL }
  },
}

building_storage_yard = {
  animations : {
    work : { pos : [23, 27], anim_id : ANIM_STORAGE_YARD_WORK, max_frames:15 }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_bazaar = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_BAZAAR },
    work_fancy : { pos : [0, 0], anim_id : IMG_BAZAAR_FANCY }
  },
}

building_work_camp = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_WORKCAMP },
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_booth = {
  animations : {
    juggler : { pos : [35, 17], base_id : IMG_BOOTH, anim_id : IMG_JUGGLER_SHOW }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
}

building_apothecary = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_BUILDING_APOTHECARY }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
}

building_water_supply = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_WATER_SUPPLY }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
}

building_well = {
  animations : {
    preview : { pack: PACK_GENERAL, id:23, max_frames:1 },
    base : { pack: PACK_GENERAL, id:23, max_frames:1 },
    base_work : { pack: PACK_GENERAL, id:23, max_frames:1 },
    fancy : { pack: PACK_GENERAL, id:23, offset:2, max_frames:1 },
    fancy_work : { pack: PACK_GENERAL, id:23, offset:3, max_frames:1 }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
}

building_papyrus_maker = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:44 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:44 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:44, offset:1, max_frames:9 }
  },
  output_resource : RESOURCE_PAPYRUS,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_reed_gatherer = {
  animations : {
    work : { pos : [0, 0], anim_id : IMG_BUILDING_REED_GATHERER }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_wood_cutter = {
  // todo
}

building_small_mastaba = {
  // todo
}

building_tax_collector = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:63 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:63 },
    work : { pos : [0, 0], pack:PACK_GENERAL, id:63, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_tax_collector_up = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:64 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    work : { pos : [0, 0], pack:PACK_GENERAL, id:64, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_bandstand = {
  animations : {
    juggler : { pos : [35, 17], base_id : IMG_BOOTH, anim_id : IMG_JUGGLER_SHOW },
    musician_sn : { pos : [45, 7], base_id : IMG_BANDSTAND_SN_S, anim_id : IMG_MUSICIAN_SHOW_SN, max_frames : 12 },
    musician_we : { pos : [48, 4], base_id : IMG_BANDSTAND_SN_S, anim_id : IMG_MUSICIAN_SHOW_WE, max_frames : 12 }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
}

building_village_palace = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_VILLAGE_PALACE }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_clay_pit = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_CLAY_PIT }
  },
  output_resource : RESOURCE_CLAY,
  meta_id : "clay_pit",
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_brewery = {
  animations : {
    work : { pos : [-1, -1], base_id : ANIM_BREWERY_WORKSHOP, anim_id: ANIM_BREWERY_WORKSHOP, max_frames: 12 }
  }
}

building_mine_copper = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_COPPER,
  info_help_id:93, info_text_id:193,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_mine_gems = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_GEMS,
  meta_id : "gems_mine",
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_mine_gold = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_GOLD,
  info_help_id:93,
  info_text_id:162,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_pottery = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_POTTERY_WORKSHOP }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_physician = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_PHYSICIAN }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
}

building_firehouse = {
  animations : {
    work : { pos : [0, 0], anim_id: IMG_BUILDING_FIREHOUSE }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_architect_post = {
  animations : {
    preview : { pack:PACK_GENERAL, id:81 },
    base : { pack:PACK_GENERAL, id:81 },
    work : { pos : [20, -35], pack:PACK_GENERAL, id:81, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
}

building_conservatory = {
  animations : {
    work : { pos : [82, 18], anim_id: IMG_MUSICIAN_SHOW_SN }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
}

building_hunting_lodge = {
  animations : {
    preview : { pack:PACK_GENERAL, id:176},
    base : { pack:PACK_GENERAL, id:176},
    work : { pos:[20, -15], pack:PACK_GENERAL, id:176, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_scribal_school = {
  animations : {
    preview : { pack:PACK_GENERAL, id:42},
    base : { pack:PACK_GENERAL, id:42},
    work : { pos:[20, -15], pack:PACK_GENERAL, id:42, offset:1, max_frames:11 }
  },

  info_icon_res :[32, 106],
  info_text_res :[60, 110],
  info_help_id: 68, info_text_id: 85,

  papyrus_icon:[61, 14],
  labor_category : LABOR_CATEGORY_EDUCATION,
}
