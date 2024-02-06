log_info("akhenaten: building info started")

building_info = [
  { type: "school_scribe", help_id: 68, text_id: 85},
  // { type: "academy", help_id: 69, text_id: 86},
  { type: "library", help_id: 70, text_id: 87},
  { type: "marble_quarry", help_id:95, text_id:118},
  { help_id:93, type:"limestone_quarry", text_id:119},
  { help_id:93, type:"gold_mine", text_id:162},
  { help_id:93, type:"copper_mine", text_id:193},
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

building_courthouse = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_COURTHOUSE }
  }
}

building_personal_mansion = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_PERSONAL_MANSION }
  }
}

building_temple_osiris = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_OSIRIS }
  }
}

building_temple_ra = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_RA }
  }
}

building_temple_ptah = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_PTAH }
  }
}

building_temple_seth = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_SETH }
  }
}

building_temple_bast = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_TEMPLE_BAST }
  }
}

building_booth = {
  animations : {
    juggler : { pos : [35, 17], base_id : IMG_BOOTH, anim_id : IMG_JUGGLER_SHOW }
  }
}

building_bandstand = {
  animations : {
    juggler : { pos : [35, 17], base_id : IMG_BOOTH, anim_id : IMG_JUGGLER_SHOW },
    musician_sn : { pos : [45, 7], base_id : IMG_BANDSTAND_SN_S, anim_id : IMG_MUSICIAN_SHOW_SN, max_frames : 12 },
    musician_we : { pos : [48, 4], base_id : IMG_BANDSTAND_SN_S, anim_id : IMG_MUSICIAN_SHOW_WE, max_frames : 12 }
  }
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

building_copper_mine = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_COPPER,
  meta_id : "copper_mine",
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_gems_mine = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_GEMS,
  meta_id : "gems_mine",
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_gold_mine = {
  animations : {
    work : { pos : [54, 15], anim_id: ANIM_GOLD_MINE, max_frames: 16 }
  },
  output_resource : RESOURCE_GOLD,
  meta_id : "gold_mine",
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

building_conservatory = {
  animations : {
    work : { pos : [82, 18], anim_id: IMG_MUSICIAN_SHOW_SN }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
}

building_hunting_lodge = {
  animations : {
    work : { pos : [-1, -1], anim_id: IMG_HUNTING_LODGE }
  },
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_scribal_school = {
  papyrus_icon : {x: 61, y: 14},

  info : {
    icon_res : {x: 32, y: 106},
    text_res : {x: 60, y: 110},
  }
}
