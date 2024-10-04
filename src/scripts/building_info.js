log_info("akhenaten: building info started")

building_small_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 61, offset:1},
    {pack: PACK_GENERAL, id: 61, offset:5},
    {pack: PACK_EXPANSION, id: 37, offset:1},
    {pack: PACK_EXPANSION, id: 37, offset:5},
    {pack: PACK_TEMPLE_RA, id: 1, offset:27},
  ],
  window_info_height_id : 1,
  info_help_id:79,
  info_text_id:80,
  building_size : 1,
}

building_medium_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 8, offset:1},
    {pack: PACK_GENERAL, id: 8, offset:5},
    {pack: PACK_EXPANSION, id: 36, offset:1},
    {pack: PACK_EXPANSION, id: 36, offset:5},
  ],
  window_info_height_id : 1,
  info_help_id:79,
  info_text_id:80,
  building_size : 2,
}

building_large_statue = {
  variants : [
    {pack: PACK_GENERAL, id: 7, offset:1},
    {pack: PACK_GENERAL, id: 7, offset:5},
    {pack: PACK_EXPANSION, id: 35, offset:1},
    {pack: PACK_EXPANSION, id: 35, offset:5},
  ],
  window_info_height_id : 1,
  info_help_id:79,
  info_text_id:80,
  building_size : 3,
}

building_fort = {
  ghost : {
    main : [[-55, 20], [-55, -35], [-55, -35], [-60, -40]],
    ground : [[35, 65], [5, -70], [-200, -55], [-180, 46]],
    ground_check : [[3, -1], [4, -1], [4, 0], [3, 0],
                    [-1,-4], [0, -4], [0,-3], [-1,-3],
                    [-4, 0], [-3, 0], [-3,1], [-4, 1],
                    [0,  3], [1,  3], [1, 4], [0,  4]],
  },
  labor_category : LABOR_CATEGORY_MILITARY,
  fire_proof : 1,
  damage_proof : 1,
}

building_fort_charioteers = {
  animations : {
    base: {pack: PACK_GENERAL, id: 66},
    ground: {pack: PACK_GENERAL, id: 66, offset:1},
    picture: {pack: PACK_GENERAL, id: 66, offset:3, pos:[93, -21]},
  },
  labor_category : LABOR_CATEGORY_MILITARY,
  building_size : 3,
  window_info_height_id : 1,
  fire_proof : 1,
  damage_proof : 1,
}

building_fort_infantry = {
  animations : {
    base: {pack: PACK_GENERAL, id: 66},
    ground: {pack: PACK_GENERAL, id: 66, offset:1},
    picture: {pack: PACK_GENERAL, id: 66, offset:4, pos:[93, -21]},
  },
  labor_category : LABOR_CATEGORY_MILITARY,
  building_size : 3,
  window_info_height_id : 1,
  fire_proof : 1,
  damage_proof : 1,
}

building_fort_archers = {
  animations : {
    base: {pack: PACK_GENERAL, id: 66},
    ground: {pack: PACK_GENERAL, id: 66, offset:1},
    picture: {pack: PACK_GENERAL, id: 66, offset:2, pos:[93, -21]},
  },
  labor_category : LABOR_CATEGORY_MILITARY,
  building_size : 3,
  window_info_height_id : 1,
  fire_proof : 1,
  damage_proof : 1,
}

building_fort_ground = {
  labor_category : LABOR_CATEGORY_MILITARY,
  building_size : 4,
  fire_proof : 1,
  damage_proof : 1,
}

building_house_crude_hut = {
  animations : {
    preview: {pack: PACK_GENERAL, id: 36},
    base: {pack: PACK_GENERAL, id: 36},
    house: {pack: PACK_GENERAL, id: 26},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  is_draggable : true,
  window_info_height_id : 5,
}

building_house_sturdy_hut = {
  animations : {
    house: {pack: PACK_GENERAL, id: 26, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_meager_shanty = {
  animations : {
    house: {pack: PACK_GENERAL, id: 27, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_common_shanty = {
  animations : {
    house: {pack: PACK_GENERAL, id: 27, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_rough_cottage = {
  animations : {
    house: {pack: PACK_GENERAL, id: 28, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_ordinary_cottage = {
  animations : {
    house: {pack: PACK_GENERAL, id: 28, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_modest_homestead = {
  animations : {
    house: {pack: PACK_GENERAL, id: 29, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_spacious_homestead = {
  animations : {
    house: {pack: PACK_GENERAL, id: 29, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_modest_apartment = {
  animations : {
    house: {pack: PACK_GENERAL, id: 30, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_spacious_apartment = {
  animations : {
    house: {pack: PACK_GENERAL, id: 30, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_common_residence = {
  animations : {
    house: {pack: PACK_GENERAL, id: 31, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_spacious_residence = {
  animations : {
    house: {pack: PACK_GENERAL, id: 31, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_elegant_residence = {
  animations : {
    house: {pack: PACK_GENERAL, id: 32, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_fancy_residence = {
  animations : {
    house: {pack: PACK_GENERAL, id: 32, offset:2},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 2,
  window_info_height_id : 5,
}

building_house_common_manor = {
  animations : {
    house: {pack: PACK_GENERAL, id: 33, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}

building_house_spacious_manor = {
  animations : {
    house: {pack: PACK_GENERAL, id: 33, offset:1},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}

building_house_elegant_manor = {
  animations : {
    house: {pack: PACK_GENERAL, id: 34, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}
building_house_stately_manor = {
  animations : {
    house: {pack: PACK_GENERAL, id: 34, offset:1},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}

building_house_modest_estate = {
  animations : {
    house: {pack: PACK_GENERAL, id: 35, offset:0},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}

building_house_palatial_estate = {
  animations : {
    house: {pack: PACK_GENERAL, id: 35, offset:1},
    minimap: {pack: PACK_GENERAL, id:148},
  },
  building_size : 1,
  num_types : 1,
  window_info_height_id : 5,
}

building_cattle_ranch = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:105, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:105, offset:0 },
    work : { pos : [0, 0], pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_MEAT,
  building_size : 3,
  info_help_id:1,
  info_text_id:117,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_grain = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:0 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_GRAIN,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:90,
  info_text_id:112,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_chickpeas = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:0 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_CHICKPEAS,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:90,
  info_text_id:182,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_lettuce = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:15 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_LETTUCE,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:91,
  info_text_id:113,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_pomegranates = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:20 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_POMEGRANATES,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:91,
  info_text_id:114,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_barley = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:0 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_BARLEY,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:89,
  info_text_id:181,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_flax = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37, offset:5 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_FLAX,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:90,
  info_text_id:115,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_farm_henna = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_HENNA,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:90,
  info_text_id:306,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_burning_ruin = {
  animations : {
    base : { pack:PACK_GENERAL, id:105, offset:0 },
  },
  building_size : 1,
  fire_proof : true,
  damage_proof : true,
}

building_farm_figs = {
  animations : {
    preview : { pack:PACK_GENERAL, id:105, },
    base : { pack:PACK_GENERAL, id:105, offset:0 },
    work : { pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    farm_house : { pack:PACK_GENERAL, id:225 },
    tiling: { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 },
    seeding: { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 },
    harvesting: { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6},
    farmland: { pack:PACK_GENERAL, id:37 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_FIGS,
  building_size : 3,
  fire_proof : true,
  damage_proof : true,
  info_help_id:90,
  info_text_id:183,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_granary = {
  animations : {
    preview : { pack:PACK_GENERAL, id:99 },
    base : { pack:PACK_GENERAL, id:99 },
    work : { pack:PACK_SPR_AMBIENT, id:47, max_frames:23 },
    resources : {pack:PACK_GENERAL, id:99, offset:2},
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  window_info_height_id : 1,
  info_text_id: 98,
  info_help_id: 3,
  building_size : 4,
}

building_shrine_osiris = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:75, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:75, offset:0 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  window_info_height_id : 4,
  info_help_id: 67,
  info_text_id: 0,
  building_size : 1,
}

building_shrine_ra = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:74, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:74, offset:0 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  window_info_height_id : 4,
  info_help_id: 67,
  info_text_id: 2,
  building_size : 1,
}

building_shrine_ptah = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:73, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:73, offset:0 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  window_info_height_id : 4,
  info_help_id: 67,
  info_text_id: 4,
  building_size : 1,
}

building_shrine_seth = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:72, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:72, offset:0 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  window_info_height_id : 4,
  info_help_id: 67,
  info_text_id: 6,
  building_size : 1,
}

building_shrine_bast = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:71, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:71, offset:0 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  window_info_height_id : 4,
  info_help_id: 67,
  info_text_id: 8,
  building_size : 1,
}

building_weaponsmith = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:123, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:123, offset:0 },
    work : { pos : [57, -16], pack:PACK_GENERAL, id:123, offset:1, max_frames:20, duration:5, can_reverse:true },
    copper : { pos : [93, 0], pack:PACK_GENERAL, id:203 }
  },
  output_resource : RESOURCE_WEAPONS,
  labor_category : LABOR_CATEGORY_MILITARY,
  window_info_height_id : 1,
  info_help_id:98,
  info_text_id:124,
  building_size : 2,
}

building_courthouse = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:62, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:62, },
    work : { pos : [80, -80], pack:PACK_GENERAL, id:62, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  building_size : 3,
  info_text_id:176,
  info_help_id:75,
}

building_guild_stonemasons = {
  animations : {
    preview : { pack:PACK_GENERAL, id:88 },
    base : { pack:PACK_GENERAL, id:88 },
    work : { pos : [-1, -1], pack:PACK_GENERAL, id:88, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  building_size : 2,
}

building_bricklayers_guild = {
  animations : {
    preview : { pos : [-1, -1], pack:PACK_GENERAL, id:57 },
    base : { pos : [-1, -1], pack:PACK_GENERAL, id:57 },
    work : { pos : [75, -14], pack:PACK_GENERAL, id:57, offset:1, max_frames:12, duration:4 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  info_help_id:92,
  info_text_id:172,
  building_size : 2,
}

building_carpenters_guild = {
  animations : {
    preview : { pack:PACK_GENERAL, id:91 },
    base : { pack:PACK_GENERAL, id:91 },
    work : { pos : [-1, -1], pack:PACK_GENERAL, id:91, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  building_size : 2,
}

building_dock = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:49 },
    base : { pack:PACK_TERRAIN, id:49 },
    work_n : { pos:[125, -47], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    work_w : { pos:[100, -7], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:8 },
    work_s : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
    work_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:4 }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 3,
  fire_proof : true,
  window_info_height_id : 1,
}

building_personal_mansion = {
  animations : {
    preview : { pack:PACK_GENERAL, id:85 },
    base : { pack:PACK_GENERAL, id:85 },
    work : { pack:PACK_GENERAL, id:85, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  building_size : 3,
  unique_building : true,
  window_info_height_id : 1,
}

building_village_mansion = {
  animations : {
    preview : { pack:PACK_GENERAL, id:47 },
    base : { pack:PACK_GENERAL, id:47 },
    work : { pos : [-1, -1], pack:PACK_GENERAL, id:47, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  building_size : 4,
  unique_building : true,
  window_info_height_id : 1,
}

building_dynasty_mansion = {
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  building_size : 4,
  unique_building : true,
  window_info_height_id : 1,
}

building_temple_osiris = {
  animations : {
    preview : { pack:PACK_GENERAL, id:25 },
    base : { pack:PACK_GENERAL, id:25 },
    work : { pos : [80, -125], pack:PACK_GENERAL, id:25, offset:1, max_frames:8 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  building_size : 3,
  info_help_id: 67,
  info_text_id: 92,
  window_info_height_id : 1,
}

building_temple_ra = {
  animations : {
    preview : { pack:PACK_GENERAL, id:21 },
    base : { pack:PACK_GENERAL, id:21 },
    work : { pos : [80, -123], pack:PACK_GENERAL, id:21, offset:1, max_frames:11 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  building_size : 3,
  info_help_id: 67,
  info_text_id: 93,
  window_info_height_id : 1,
}

building_temple_ptah = {
  animations : {
    preview : { pack:PACK_GENERAL, id:20 },
    base : { pack:PACK_GENERAL, id:20 },
    work : { pos : [70, -103], pack:PACK_GENERAL, id:20, offset:1, max_frames:11 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  building_size : 3,
  info_help_id: 67,
  info_text_id: 94,
  window_info_height_id : 1,
}

building_temple_seth = {
  animations : {
    preview : { pack:PACK_GENERAL, id:19 },
    base : { pack:PACK_GENERAL, id:19 },
    work : { pos : [70, -133], pack:PACK_GENERAL, id:19, offset:1, max_frames:11 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  building_size : 3,
  info_help_id: 67,
  info_text_id: 95,
  window_info_height_id : 1,
}

building_temple_bast = {
  animations : {
    preview : { pack:PACK_GENERAL, id:76 },
    base : { pack:PACK_GENERAL, id:76 },
    work : { pos : [85, -115], pack:PACK_GENERAL, id:76, offset:1, max_frames:11 },
  },
  labor_category : LABOR_CATEGORY_RELIGION,
  building_size : 3,
  info_help_id: 67,
  info_text_id: 96,
  window_info_height_id : 1,
}

building_library = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:43 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:43 },
    work : { pos : [33, -38], pack:PACK_GENERAL, id:43, offset:1, max_frames:12 }
  },
  window_info_height_id : 1,
  info_help_id: 70,
  info_text_id: 87,
  building_size : 3,
}

building_military_academy = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:173 },
    work : { pos : [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  },
  window_info_height_id : 1,
  building_size : 4,
}

building_juggler_school = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:46 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:46 },
    work : { pos : [33, -38], pack:PACK_GENERAL, id:46, offset:1, max_frames:12, duration:3 }
  },
  window_info_height_id : 1,
  info_help_id:75,
  info_text_id:77,
  building_size : 2,
}

building_dancer_school = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:52, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:52, },
    work : { pos : [104, 0], pack:PACK_SPR_AMBIENT, id:6, offset:0, max_frames:35 }
  },
  building_size : 4,
  info_help_id:75,
  info_text_id:76,
  window_info_height_id : 1,
}

building_storage_yard = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:82, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:82, },
    cover : { pos : [-5, -42], pack:PACK_GENERAL, id:82, offset:17 },
    work : { pos : [20, 25], pack:PACK_SPR_AMBIENT, id:51, offset:1, max_frames:14, duration:3 }
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  info_help_id : 4,
  info_text_id:99,
  building_size : 3,
}

building_storage_room = {
  animations : {
  },
  building_size : 3,
  fire_proof : true,
}

building_bazaar = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:22, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:22, },
    base_work : { pos : [0, 0], pack:PACK_GENERAL, id:22, offset:0 },
    fancy : { pos : [0, 0], pack:PACK_GENERAL, id:22, offset:12 },
    fancy_work : { pos : [0, 0], pack:PACK_GENERAL, id:22, offset:13 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  building_size : 2,
  window_info_height_id : 1,
  info_help_id: 2,
  info_text_id: 97,
}

building_work_camp = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:77 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:77 },
    work : { pos : [ 25, -12], pack:PACK_GENERAL, id:77, offset:1, max_frames:19, can_reverse:true, duration:3 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  info_help_id: 81,
  info_text_id: 179,
  building_size : 2,
}

building_booth = {
  animations : {
    booth : { pack:PACK_GENERAL, id:114 },
    square : { pack:PACK_GENERAL, id:112 },
    juggler : { pos : [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
  window_info_height_id : 2,
  info_help_id:71,
  info_text_id:72,
  building_size : 2,
}

building_apothecary = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:68 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:68 },
    work : { pos : [25, -35], pack:PACK_GENERAL, id:68, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  max_serve_clients : 100,
  window_info_height_id : 1,
  info_help_id:63,
  info_text_id:81,
  building_size : 1,
}

building_water_supply = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:69 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:69, offset:0 },
    base_work : { pos : [42, 10], pack:PACK_GENERAL, id:69, offset:1, max_frames:1 },
    fancy : { pos : [0, 0], pack:PACK_GENERAL, id:69, offset:2 },
    fancy_work : { pos : [10, 0], pack:PACK_GENERAL, id:69, offset:3, max_frames:1 }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  fire_proof : true,
  info_help_id:61,
  info_text_id:108,
  building_size : 2,
}

building_well = {
  animations : {
    preview : { pack: PACK_GENERAL, id:23, max_frames:1 },
    base : { pack: PACK_GENERAL, id:23, max_frames:1 },
    base_work : { pack: PACK_GENERAL, id:23, max_frames:1 },
    fancy : { pack: PACK_GENERAL, id:23, offset:2, max_frames:1 },
    fancy_work : { pack: PACK_GENERAL, id:23, offset:3, max_frames:1 },
    minimap: {pack:PACK_GENERAL, id:151},
  },
  window_info_height_id : 4,
  fire_proof : true,
  building_size : 1,
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
}

building_papyrus_maker = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:44 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:44 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:44, offset:1, max_frames:9 },
    reed : { pos : [35, 4], pack:PACK_GENERAL, id:206 },
  },
  output_resource : RESOURCE_PAPYRUS,
  production_rate : 50,
  building_size : 2,
  info_help_id:1,
  info_text_id:190,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_weaver = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:122 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:122 },
    work : { pos : [19, -39], pack:PACK_GENERAL, id:122, offset:1, max_frames:9 },
    flax : { pos : [45, 3], pack:PACK_GENERAL, id:206 },
  },
  output_resource : RESOURCE_LINEN,
  building_size : 2,
  window_info_height_id : 1,
  info_help_id:97,
  info_text_id:123,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_jewels_workshop = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:119 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:119 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:119, offset:1, max_frames:9 },
  },
  output_resource : RESOURCE_LUXURY_GOODS,
  building_size : 2,
  window_info_height_id : 1,
  info_help_id:99,
  info_text_id:125,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_reed_gatherer = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:24 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:24 },
    work : { pos : [30, -17], pack:PACK_GENERAL, id:24, offset:1, max_frames:19 }
  },
  output_resource : RESOURCE_REEDS,
  building_size : 2,
  window_info_height_id : 1,
  info_help_id:92,
  info_text_id:116,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_wood_cutter = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:23 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:23 },
    work : { pos : [30, -17], pack:PACK_GENERAL, id:23, offset:1, max_frames:19 },
    wood : { pos : [65, 3], pack:PACK_GENERAL, id:202 },
  },
  output_resource : RESOURCE_TIMBER,
  building_size : 2,
  window_info_height_id : 1,
  info_help_id:94,
  info_text_id:120,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_small_mastaba = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_MASTABA, id:2, offset:7 },
    base : { pos : [0, 0], pack:PACK_MASTABA, id:2, offset:7 },
  },
  building_size : 2,
  // todo
}

building_small_mastaba_part_side = building_small_mastaba
building_small_mastaba_part_wall = building_small_mastaba
building_small_mastaba_part_entrance = building_small_mastaba

building_tax_collector = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:63 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:63 },
    work : { pos : [60, -45], pack:PACK_GENERAL, id:63, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  window_info_height_id : 1,
  info_help_id:76,
  info_text_id:120,
  building_size : 2,
}

building_tax_collector_up = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:64 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    work : { pos : [10, 10], pack:PACK_GENERAL, id:64, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  window_info_height_id : 1,
  info_help_id:76,
  info_text_id:120,
  building_size : 2,
}

building_recruiter = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:166 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:166 },
    work : { pos : [10, 10], pack:PACK_GENERAL, id:166, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_MILITARY,
  window_info_height_id : 3,
  info_help_id:37,
  info_text_id:136,
  building_size : 3,
}

building_bandstand = {
  animations : {
    booth : { pos:[0, 0], pack:PACK_GENERAL, id:114 },
    square : { pos:[0, 0], pack:PACK_GENERAL, id:58 },
    juggler : { pos : [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
    stand_sn_s : { pack:PACK_GENERAL, id:92, offset:0},
    stand_sn_n : { pack:PACK_GENERAL, id:92, offset:1},
    stand_we_w: { pack:PACK_GENERAL, id:92, offset:2},
    stand_we_e: {pack:PACK_GENERAL, id:92, offset:3},
    musician_sn : { pos : [45, 7], pack:PACK_SPR_AMBIENT, id:10, max_frames : 11 },
    musician_we : { pos : [48, 4], pack:PACK_SPR_AMBIENT, id:9, max_frames : 11 }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
  window_info_height_id : 3,
  info_help_id:72,
  info_text_id:71,
  building_size : 3,
}

building_pavilion = {
  animations : {
    base : { pos:[0, 0], pack:PACK_GENERAL, id:48 },
    square : { pos:[0, 0], pack:PACK_GENERAL, id:50 },
    stand_sn_s : { pack:PACK_GENERAL, id:92, offset:0},
    stand_sn_n : { pack:PACK_GENERAL, id:92, offset:1},
    stand_sn_e : { pack:PACK_GENERAL, id:92, offset:2},
    juggler : { pos : [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
    dancer : { pos : [65, 0], pack:PACK_SPR_AMBIENT, id:6, offset:0, max_frames:35 },
    musician_sn : { pos : [50, 0], pack:PACK_SPR_AMBIENT, id:9, max_frames : 11 },
    musician_we : { pos : [48, 4], pack:PACK_SPR_AMBIENT, id:10, max_frames : 11 },
    booth : { pos:[0, 0], pack:PACK_GENERAL, id:114 },
  },
  preview_dir_0 : { stand:[-30, 15], stand_b:[90, 45], stand_e:[60, 60], booth:[-60, 30] },
  preview_dir_1 : { stand:[30, 45], stand_b:[0, 0], stand_e:[-30, 15], booth:[30, 75] },
  preview_dir_2 : { stand:[0, 30], stand_b:[0, 90], stand_e:[-30, 75], booth:[90, 45], stand_b_img:2, stand_e_img:2 },
  preview_dir_3 : { stand:[-60, 60], stand_b:[90, 45], stand_e:[60, 30], booth:[0, 90], stand_b_img:2, stand_e_img:2 },
  preview_dir_4 : { stand:[0, 60], stand_b:[-60, 30], stand_e:[-90, 45], booth:[0, 90] },
  preview_dir_5 : { stand:[-60, 30], stand_b:[30, 75], stand_e:[0, 90], booth:[-90, 45] },
  preview_dir_6 : { stand:[-90, 45], stand_b:[30, 15], stand_e:[0, 0], booth:[-30, 75], stand_b_img : 2, stand_e_img : 2 },
  preview_dir_7 : { stand:[-30, 15], stand_b:[-60, 60], stand_e:[-90, 45], booth:[60, 30], stand_b_img : 2, stand_e_img : 2 },

  place_dir_0 : [
    {type: BUILDING_GARDENS, offset:[1, 2]},
    {type: BUILDING_GARDENS, offset:[3, 2]},
    {type: BUILDING_PAVILLION, offset:[0, 0]},
    {type: BUILDING_BANDSTAND, offset:[3, 0], main:true},
    {type: BUILDING_BANDSTAND, offset:[3, 1], main:false},
    {type: BUILDING_BOOTH, offset:[0, 2], main:false}
  ],

  place_dir_1 : [
    {type: BUILDING_GARDENS, offset:[2, 2]},
    {type: BUILDING_GARDENS, offset:[0, 2]},
    {type: BUILDING_PAVILLION, offset:[2, 0]},
    {type: BUILDING_BANDSTAND, offset:[0, 0], main:true},
    {type: BUILDING_BANDSTAND, offset:[0, 1], main:false},
    {type: BUILDING_BOOTH, offset:[3, 2], main:false}
  ],

  place_dir_2 : [
    {type: BUILDING_GARDENS, offset:[3, 0]},
    {type: BUILDING_GARDENS, offset:[3, 3]},
    {type: BUILDING_PAVILLION, offset:[1, 0]},
    {type: BUILDING_BANDSTAND, offset:[1, 3], main:true},
    {type: BUILDING_BANDSTAND, offset:[2, 3], main:false},
    {type: BUILDING_BOOTH, offset:[3, 1], main:false}
  ],

  place_dir_3 : [
    {type: BUILDING_GARDENS, offset:[3, 3]},
    {type: BUILDING_GARDENS, offset:[1, 0]},
    {type: BUILDING_PAVILLION, offset:[1, 2]},
    {type: BUILDING_BANDSTAND, offset:[2, 0], main:true},
    {type: BUILDING_BANDSTAND, offset:[3, 0], main:false},
    {type: BUILDING_BOOTH, offset:[3, 2], main:false}
  ],

  place_dir_4 : [
    {type: BUILDING_GARDENS, offset:[3, 3]},
    {type: BUILDING_GARDENS, offset:[0, 3]},
    {type: BUILDING_PAVILLION, offset:[2, 1]},
    {type: BUILDING_BANDSTAND, offset:[0, 1], main:true},
    {type: BUILDING_BANDSTAND, offset:[0, 2], main:false},
    {type: BUILDING_BOOTH, offset:[2, 3], main:false}
  ],

  place_dir_5 : [
    {type: BUILDING_GARDENS, offset:[1, 3]},
    {type: BUILDING_GARDENS, offset:[3, 3]},
    {type: BUILDING_PAVILLION, offset:[0, 1]},
    {type: BUILDING_BANDSTAND, offset:[3, 1], main:true},
    {type: BUILDING_BANDSTAND, offset:[3, 2], main:false},
    {type: BUILDING_BOOTH, offset:[0, 3], main:false}
  ],

  place_dir_6 : [
    {type: BUILDING_GARDENS, offset:[2, 0]},
    {type: BUILDING_GARDENS, offset:[2, 2]},
    {type: BUILDING_PAVILLION, offset:[0, 2]},
    {type: BUILDING_BANDSTAND, offset:[0, 0], main:false},
    {type: BUILDING_BANDSTAND, offset:[1, 0], main:true},
    {type: BUILDING_BOOTH, offset:[2, 3], main:false}
  ],

  place_dir_7 : [
    {type: BUILDING_GARDENS, offset:[0, 3]},
    {type: BUILDING_GARDENS, offset:[2, 1]},
    {type: BUILDING_PAVILLION, offset:[0, 0]},
    {type: BUILDING_BANDSTAND, offset:[1, 3], main:false},
    {type: BUILDING_BANDSTAND, offset:[2, 3], main:true},
    {type: BUILDING_BOOTH, offset:[2, 0], main:false}
  ],
  building_size : 4,
  window_info_height_id : 2,
}

building_festival_square = {
  animations : {
    base : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
    square : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
  },
  building_size : 5,
  window_info_height_id: 1,
  info_help_id: 366,
  info_text_id: 188,
  unique_building : true,
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
  window_info_height_id : 1,
  info_help_id: 358,
  info_text_id: 155,
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_brick_tower = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:98 },
    base : { pack:PACK_TERRAIN, id:98 },
  },
  building_size : 2,
  fire_proof : true,
  window_info_height_id : 1,
  labor_category : LABOR_CATEGORY_MILITARY,
}

building_mud_tower = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:135 },
    base : { pack:PACK_TERRAIN, id:135 },
  },
  building_size : 2,
  fire_proof : true,
  window_info_height_id : 1,
  labor_category : LABOR_CATEGORY_MILITARY,
}

building_ferry = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:23 },
    base : { pack:PACK_TERRAIN, id:23 },
    work : { pack:PACK_TERRAIN, id:23 },
    minimap: {pack:PACK_GENERAL, id:149, offset:210}
  },
  building_size : 2,
  fire_proof : true,
  planer_relative_orientation: 1,
  labor_category : LABOR_CATEGORY_GOVERNMENT,
}

building_transport_wharf = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:17 },
    base : { pack:PACK_TERRAIN, id:17 },
    // work : { pack:PACK_TERRAIN, id:18, offset:1 }
  },
  building_size : 2,
  fire_proof : 1,
  window_info_height_id: 1,
  planer_relative_orientation: 1,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_warship_wharf = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:28 },
    base : { pack:PACK_TERRAIN, id:28 },
    // work : { pack:PACK_TERRAIN, id:18, offset:1 }
  },
  building_size : 3,
  fire_proof : 1,
  window_info_height_id: 1,
  planer_relative_orientation: 1,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_fishing_wharf = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:18 },
    base : { pack:PACK_TERRAIN, id:18 },
    work_n : { pos:[65, 0], pack:PACK_SPR_AMBIENT, id:46, offset:0, max_frames:24, duration:1 },
    work_w : { pos:[80, 7], pack:PACK_SPR_AMBIENT, id:46, offset:0, max_frames:24, duration:3 },
    work_s : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:46, offset:2, max_frames:24, duration:4 },
    work_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:46, offset:3, max_frames:24, duration:4 },
    wait_n : { pos:[85, 20], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    wait_w : { pos:[85, 7], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:3 },
    wait_s : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
    wait_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:4 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  output_resource : RESOURCE_FISH,
  building_size : 2,
  window_info_height_id: 1,
  planer_relative_orientation: 1,
  info_help_id: 84,
  info_text_id: 102,
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
}

building_shipyard = {
  animations : {
    preview : { pack: PACK_TERRAIN, id:26, max_frames:1 },
    base : { pack: PACK_TERRAIN, id:26, max_frames:1 },
    work : { pos : [70, 20], pack:PACK_SPR_AMBIENT, id:54, max_frames: 11 },
    wood : { pos : [65, 3], pack:PACK_GENERAL, id:202 }
  },
  building_size : 3,
  window_info_height_id : 1,
  planer_relative_orientation: 1,
  info_help_id: 82,
  info_text_id: 100,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_dentist = {
  animations : {
    preview : { pack:PACK_GENERAL, id:67 },
    base : { pack:PACK_GENERAL, id:67 },
    work : { pack:PACK_GENERAL, id:67, offset:1, max_frames:12 }
  },
  building_size : 1,
  info_help_id:65,
  info_text_id:84,
  window_info_height_id : 1,
}

building_mortuary = {
  animations : {
    preview : { pack:PACK_GENERAL, id:175 },
    base : { pack:PACK_GENERAL, id:175 },
    work : { pack:PACK_GENERAL, id:175, offset:1, max_frames:12 }
  },
  max_serve_clients : 1000,
  building_size : 2,
  info_help_id:66,
  info_text_id:82,
  window_info_height_id : 1,
}

building_plaza = {
  animations : {
    preview : { pack:PACK_GENERAL, id:168 },
    base : { pack:PACK_GENERAL, id:168 },
  },
  is_draggable : true,
  fire_proof : true,
  damage_proof : true,
  info_help_id:80,
  info_text_id:137,
  building_size : 1,
}

building_garden = {
  animations : {
    preview : { pack:PACK_GENERAL, id:59 },
    base : { pack:PACK_GENERAL, id:59 },
  },
  is_draggable : true,
  fire_proof : true,
  damage_proof : true,
  info_help_id:80,
  info_text_id:79,
  building_size : 1,
}

building_village_palace = {
  animations : {
    preview : { pack:PACK_GENERAL, id:47 },
    base : { pack:PACK_GENERAL, id:47 },
    work : { pos : [24, -20], pack:PACK_GENERAL, id:47, offset:1, max_frames:5, duration:5, can_reverse:true }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  window_info_height_id : 2,
  unique_building : true,
  info_help_id:77,
  info_text_id:105,
  building_size : 4,
}

building_town_palace = {
  animations : {
    preview : { pack:PACK_GENERAL, id:39 },
    base : { pack:PACK_GENERAL, id:39 },
    work : { pos : [-1, -1], pack:PACK_GENERAL, id:39, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  window_info_height_id : 2,
  unique_building : true,
  info_help_id:77,
  info_text_id:105,
  building_size : 5,
}

building_road = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:33 },
    base : { pack:PACK_TERRAIN, id:33 },
  },
  building_size : 1,
  is_draggable : true,
}

building_city_palace = {
  animations : {
    preview : { pack:PACK_GENERAL, id:18 },
    base : { pack:PACK_GENERAL, id:18 },
    work : { pos : [-1, -1], pack:PACK_GENERAL, id:18, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  unique_building : true,
  info_help_id:77,
  info_text_id:105,
  building_size : 6,
}

building_clay_pit = {
  animations : {
    preview : { pos : [-1, -1], pack:PACK_GENERAL, id:40 },
    base : { pos : [-1, -1], pack:PACK_GENERAL, id:40 },
    work : { pos : [18, -20], pack:PACK_GENERAL, id:40, offset:1, max_frames:23, duration:2 }
  },
  output_resource : RESOURCE_CLAY,
  building_size : 2,
  production_rate : 50,
  info_help_id:92,
  info_text_id:121,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_brewery = {
  animations : {
    preview : { pack:PACK_GENERAL, id:116 },
    base : { pack:PACK_GENERAL, id:116 },
    work : { pack:PACK_GENERAL, id:116, max_frames: 12 },
    barley : { pos:[28, -35], pack:PACK_GENERAL, id:208, max_frames: 12 }
  },
  output_resource : RESOURCE_BEER,
  window_info_height_id : 1,
  production_rate : 20,
  info_help_id:96,
  info_text_id:122,
  building_size : 2,
}

building_mine_copper = {
  animations : {
    preview : { pack:PACK_GENERAL, id:196 },
    base : { pack:PACK_GENERAL, id:196 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2 }
  },
  output_resource : RESOURCE_COPPER,
  window_info_height_id : 1,
  info_help_id:93,
  info_text_id:193,
  building_size : 2,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_mine_gems = {
  animations : {
    preview : { pack:PACK_GENERAL, id:188 },
    base : { pack:PACK_GENERAL, id:188 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2 }
  },
  output_resource : RESOURCE_GEMS,
  building_size : 2,
  info_help_id:93,
  info_text_id:163,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_sandstone_quarry = {
  animations : {
    preview : { pack:PACK_GENERAL, id:197 },
    base : { pack:PACK_GENERAL, id:197 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16 }
  },
  output_resource : RESOURCE_SANDSTONE,
  building_size : 2,
  info_help_id:93,
  info_text_id:162,
  //help_id:92, type:"sandstone_quarry", text_id:194
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_marble_quarry = {
  animations : {
    preview : { pack:PACK_GENERAL, id:197 },
    base : { pack:PACK_GENERAL, id:197 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16 }
  },
  info_help_id:95,
  info_text_id:118,
}

building_stone_quarry = {
  animations : {
    preview : { pack:PACK_GENERAL, id:187 },
    base : { pack:PACK_GENERAL, id:187 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16 }
  },
  output_resource : RESOURCE_STONE,
  building_size : 2,
  info_help_id:93,
  info_text_id:162,
  //info_help_id:92, info_text_id:118
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_granite_quarry = {
  animations : {
    preview : { pack:PACK_GENERAL, id:38 },
    base : { pack:PACK_GENERAL, id:38 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16 }
  },
  output_resource : RESOURCE_GRANITE,
  building_size : 2,
  info_help_id:93,
  info_text_id:162,
  //help_id:92, text_id:192
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_limestone_quarry = {
  animations : {
    preview : { pack:PACK_GENERAL, id:170 },
    base : { pack:PACK_GENERAL, id:170 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  },
  output_resource : RESOURCE_LIMESTONE,
  building_size : 2,
  info_help_id:93,
  info_text_id:162,
  //help_id:93, text_id:119}
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_mine_gold = {
  animations : {
    preview : { pack:PACK_GENERAL, id:185 },
    base : { pack:PACK_GENERAL, id:185 },
    work : { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2 }
  },
  output_resource : RESOURCE_GOLD,
  building_size : 2,
  info_help_id:93,
  info_text_id:162,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
}

building_brick_gatehouse = {
  animations : {
    preview : { pack:PACK_GENERAL, id:161 },
    base : { pack:PACK_GENERAL, id:161 },
  },
  building_size : 2,
}

building_mud_gatehouse = {
  animations : {
    preview : { pack:PACK_GENERAL, id:220 },
    base : { pack:PACK_GENERAL, id:220 },
  },
  building_size : 2,
  window_info_height_id : 1,
}

building_vacant_lot = {
  animations : {
    preview : { pack:PACK_GENERAL, id:36 },
    base : { pack:PACK_GENERAL, id:36 },
  },
  info_help_id:128,
  info_text_id:-1,
  building_size : 1,
}

building_senet_house = {
  animations : {
    preview : { pack:PACK_GENERAL, id:17 },
    base : { pack:PACK_GENERAL, id:17 },
  },
  damage_proof : true,
  window_info_height_id : 2,
  building_size : 4,
}

building_bullfight_school = {
  animations : {
    preview : { pack:PACK_GENERAL, id:17 },
    base : { pack:PACK_GENERAL, id:17 },
  },
  damage_proof : true,
  window_info_height_id : 1,
  info_help_id:75,
  info_text_id:78,
  building_size : 4,
}

building_bricks_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pack:PACK_GENERAL, id:124 },
    straw : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    clay : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  info_help_id:1,
  info_text_id:180,
  window_info_height_id : 1,
}

building_chariots_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pack:PACK_GENERAL, id:124 },
    timber : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    weapon : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  window_info_height_id : 1,
}

building_pottery = {
  animations : {
    preview : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    base : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    work : { pos : [36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18, duration:3 },
    clay : { pos:[55, 30], pack:PACK_GENERAL, id:207 },
  },
  output_resource : RESOURCE_POTTERY,
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  info_help_id:1,
  info_text_id:126,
  window_info_height_id : 1,
}

building_lamp_workshop = {
  animations : {
    preview : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    base : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    work : { pos : [36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18 },
    clay : { pos:[65, 3], pack:PACK_GENERAL, id:207 },
  },
  output_resource : RESOURCE_LAMPS,
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  window_info_height_id : 1,
}

building_paint_workshop = {
  animations : {
    preview : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    base : { pos : [-1, -1], pack:PACK_GENERAL, id:125 },
    work : { pos : [36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18 },
    clay : { pos:[65, 3], pack:PACK_GENERAL, id:207 },
  },
  output_resource : RESOURCE_PAINT,
  production_rate : 20,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  window_info_height_id : 1,
}

building_academy = {
  animations : {
    preview : { pack:PACK_GENERAL, id:44 },
    base : { pack:PACK_GENERAL, id:4 },
    work : { pos : [36, -4], pack:PACK_GENERAL, id:4, offset:1, max_frames:18 },
  },
  labor_category : LABOR_CATEGORY_EDUCATION,
  building_size : 2,
  window_info_height_id : 1,
}

building_physician = {
  animations : {
    preview : { pack:PACK_GENERAL, id:70 },
    base : { pack:PACK_GENERAL, id:70 },
    work : { pos : [60, -60], pack:PACK_GENERAL, id:70, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  building_size : 2,
}

building_water_lift = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_TERRAIN, id:50 },
    base : { pos : [0, 0], pack:PACK_TERRAIN, id:50 },
    work : { pos : [0, 0], pack:PACK_TERRAIN, id:50, offset:1, max_frames:12 },
    minimap : {pack:PACK_GENERAL, id:151}
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  window_info_height_id : 1,
  fire_proof : 1,
  building_size : 2,
}


building_firehouse = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:78 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:78 },
    work : { pos : [25, -30], pack:PACK_GENERAL, id:78, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  window_info_height_id : 1,
  info_help_id: 355,
  info_text_id: 164,
  building_size : 1,
}

building_police_station = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    work : { pos : [0, 0], pack:PACK_GENERAL, id:64, offset:1, max_frames:12 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  window_info_height_id : 1,
  building_size : 1,
}

building_architect_post = {
  animations : {
    preview : { pack:PACK_GENERAL, id:81 },
    base : { pack:PACK_GENERAL, id:81 },
    work : { pos : [20, -35], pack:PACK_GENERAL, id:81, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE,
  building_size : 1,
  info_help_id: 81,
  info_text_id: 104,
  window_info_height_id : 1,
}

building_conservatory = {
  animations : {
    preview : { pack:PACK_GENERAL, id:51 },
    base : { pack:PACK_GENERAL, id:51 },
    work : { pos : [82, 18], pack:PACK_SPR_AMBIENT, id:10, max_frames:11, duration:4 }
  },
  labor_category : LABOR_CATEGORY_ENTERTAINMENT,
  window_info_height_id : 1,
  info_help_id:75,
  info_text_id:75,
  building_size : 3,
}

building_hunting_lodge = {
  animations : {
    preview : { pack:PACK_GENERAL, id:176},
    base : { pack:PACK_GENERAL, id:176},
    work : { pos:[20, -15], pack:PACK_GENERAL, id:176, offset:1, max_frames:18, duration:3 },
    gamemeat : { pos:[61, 14], pack:PACK_GENERAL, id:205 },
    minimap: {pack:PACK_GENERAL, id:149, offset:160},
  },
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
  output_resource : RESOURCE_GAMEMEAT,
  window_info_height_id : 1,
  info_help_id:90,
  info_text_id:154,
  building_size : 2,
}

building_scribal_school = {
  animations : {
    preview : { pack:PACK_GENERAL, id:42},
    base : { pack:PACK_GENERAL, id:42},
    work : { pos:[2, -25], pack:PACK_GENERAL, id:42, offset:1, max_frames:11, duration:4, can_reverse:true }
  },

  info_icon_res :[32, 106],
  info_text_res :[60, 110],
  info_help_id: 68, info_text_id: 85,
  window_info_height_id : 1,

  papyrus_icon:[61, 14],
  building_size : 2,
  labor_category : LABOR_CATEGORY_EDUCATION,
}
