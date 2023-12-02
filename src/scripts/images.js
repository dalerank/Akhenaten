log_info("akhenaten: images started")

small_statue_images = [
	{pack: PACK_GENERAL, id: 61, offset:1},
	{pack: PACK_GENERAL, id: 61, offset:5},
	{pack: PACK_EXPANSION, id: 37, offset:1},
	{pack: PACK_EXPANSION, id: 37, offset:5},
]

medium_statue_images = [
	{pack: PACK_GENERAL, id: 8, offset:1},
	{pack: PACK_GENERAL, id: 8, offset:5},
	{pack: PACK_EXPANSION, id: 36, offset:1},
	{pack: PACK_EXPANSION, id: 36, offset:5},
]

big_statue_images = [
	{pack: PACK_GENERAL, id: 7, offset:1},
	{pack: PACK_GENERAL, id: 7, offset:5},
	{pack: PACK_EXPANSION, id: 35, offset:1},
	{pack: PACK_EXPANSION, id: 35, offset:5},
]

images = [
	{img: IMG_IMMIGRANT, pack: PACK_SPR_MAIN, id: 14},// 886
	//{img: IMG_IMMIGRANT_DEATH, pack: PACK_SPR_MAIN, id: 15} // 982
	{img: IMG_EMIGRANT, pack: PACK_SPR_MAIN, id: 2}, // 65
	//{img: IMG_EMIGRANT_DEATH, pack: PACK_SPR_MAIN, id: 3}, // 161
	{img: IMG_HOMELESS, pack: PACK_SPR_MAIN, id: 12}, // 782
	//{img: IMG_EMIGRANT, pack: PACK_SPR_MAIN, id: 13}, // 878
	{img: IMG_FISHIHG_WHARF_ANIM, pack: PACK_SPR_AMBIENT, id:47},  // 2551 + 15831
	{img: IMG_CARTPUSHER, pack: PACK_SPR_MAIN, id:43},
	{img: IMG_CARTPUSHER_DEATH, pack: PACK_SPR_MAIN, id:44},
	{img: IMG_FISHING_BOAT, pack:PACK_SPR_MAIN, id:133 }, 	// 7014
	//{img: IMG_FISHING_BOAT ???, pack:PACK_SPR_MAIN, id:133 }, 	// 7014
	{img: IMG_FISHING_BOAT_WORK, pack:PACK_SPR_MAIN, id:135 }, // 7046
	{img: IMG_FISHING_BOAT_DEATH, pack:PACK_SPR_MAIN, id:136 }, // 7118
	{img: IMG_FISHING_BOAT_IDLE, pack:PACK_SPR_MAIN, id:137 }, // 7129
	{img: IMG_FLOTSAM, pack:PACK_SPR_AMBIENT, id:0},  // 1 + 15831
	{img: IMG_LABOR_SEEKER, pack:PACK_SPR_MAIN, id:206},       // 9909
	{img: IMG_LABOR_SEEKER_DEATH, pack:PACK_SPR_MAIN, id:207}, // 10005
	{img: IMG_FISHING_POINT, pack:PACK_SPR_AMBIENT, id:8},
	{img: IMG_FISHING_POINT_BUBLES, pack:PACK_SPR_AMBIENT, id:11},
	{img: IMG_ENGINEER, pack:PACK_SPR_MAIN, id:4},  //  169
	{img: IMG_ENGINEER_DEATH, pack:PACK_SPR_MAIN, id:5}, // 265
	{img: IMG_WATER_SUPPLY, pack:PACK_GENERAL, id:69, offset:0},
	{img: IMG_WATER_SUPPLY_FANCY, pack:PACK_GENERAL, id:69, offset:2},
	{img: IMG_WELL, pack:PACK_GENERAL, id:23, offset:0},
	{img: IMG_WELL_FANCY, pack:PACK_GENERAL, id:23, offset:2},
	{img: IMG_EXPLOSION, pack:PACK_SPR_AMBIENT, id:12, offset:0},
	{img: IMG_CATTLE_RANCH, pack:PACK_GENERAL, id:105},
	{img: IMG_TAX_COLLECTOR, pack:PACK_SPR_MAIN, id:41},
	{img: IMG_BRICKS_WORKSHOP, pack:PACK_GENERAL, id:124},
	{img: IMG_RESOURCE_GAMEMEAT, pack:PACK_GENERAL, id:205},
	{img: IMG_RESOURCE_STRAW, pack:PACK_GENERAL, id:206},
	{img: IMG_RESOURCE_CLAY, pack:PACK_GENERAL, id:207},
	{img: IMG_RESOURCE_ICONS, pack:PACK_GENERAL, id:129},
	{img: IMG_OSTRICH_WALK, pack:PACK_SPR_MAIN, id:156}, // 7823 - 0
	{img: IMG_FIREMAN, pack:PACK_SPR_MAIN, id:6},  // 273
	{img: IMG_GOLD_MINE, pack:PACK_GENERAL, id:185},
	{img: ANIM_GOLD_MINE, pack:PACK_SPR_AMBIENT, id:48},
	{img: IMG_SANDSTONE_QUARRY, pack:PACK_GENERAL, id:197},
	{img: ANIM_SANDSTONE_QUARRY_1, pack:PACK_SPR_AMBIENT, id:49},
	{img: ANIM_SANDSTONE_QUARRY_2, pack:PACK_SPR_AMBIENT, id:49},
	{img: IMG_CARTPUSHER_CART, pack:PACK_SPR_MAIN, id:77},
	{img: IMG_SLED_SANDSTONE_SMALL, pack:PACK_SPR_MAIN, id:101},
	{img: IMG_SLED_STONE_SMALL, pack:PACK_SPR_MAIN, id:102},
	{img: IMG_SLED_GRANITE_SMALL, pack:PACK_SPR_MAIN, id:103},
	{img: IMG_SLED_LIMESTONE_SMALL, pack:PACK_GENERAL, id:104},
	{img: IMG_SLED_BRICKS, pack:PACK_SPR_MAIN, id:89},
	{img: IMG_JUGGLER_WALK, pack:PACK_SPR_MAIN, id:130},
	{img: IMG_PLAINSTONE_QUARRY, pack:PACK_GENERAL, id:187},
	{img: IMG_GRANARY, pack:PACK_GENERAL, id:99},
	{img: IMG_GRANARY_RESOURCES, pack:PACK_GENERAL, id:99, offset:2},
	{img: IMG_CART_COPPER, pack:PACK_SPR_MAIN, id:107},
	{img: IMG_COPPER_MINE, pack:PACK_GENERAL, id:196},
	{img: IMG_CONSERVATORY, pack:PACK_GENERAL, id:51},
	{img: IMG_PHYSICIAN, pack:PACK_GENERAL, id:70},
	{img: IMG_BARRACKS, pack:PACK_GENERAL, id:166},
	{img: IMG_SCRIBAL_SCHOOL, pack:PACK_GENERAL, id:42},
	{img: IMG_SCRIBER_WALK, pack:PACK_SPR_MAIN, id:199},
	{img: IMG_SCRIBER_DEATH, pack:PACK_SPR_MAIN, id:200},
	{img: IMG_TEACHER_WALK, pack:PACK_SPR_MAIN, id:201},
	{img: IMG_TEACHER_DEATH, pack:PACK_SPR_MAIN, id:202},
	{img: IMG_BANDSTAND_SN_S, pack:PACK_GENERAL, id:92},
	{img: IMG_BANDSTAND_SN_N, pack:PACK_GENERAL, id:92, offset:1},
	{img: IMG_BANDSTAND_WE_W, pack:PACK_GENERAL, id:92, offset:2},
	{img: IMG_BANDSTAND_WE_E, pack:PACK_GENERAL, id:92, offset:3},
	{img: IMG_BOOTH, pack:PACK_GENERAL, id:114},
	{img: IMG_BOOTH_SQUARE, pack:PACK_GENERAL, id:112},
	{img: IMG_BANDSTAND_SQUARE, pack:PACK_GENERAL, id:58},
	{img: IMG_MUSICIAN, pack:PACK_SPR_MAIN, id:191},
	{img: IMG_JUGGLER_SHOW, pack:PACK_SPR_AMBIENT, id:7, offset:-1},
	{img: IMG_MUSICIAN_SHOW_SN, pack:PACK_SPR_AMBIENT, id:10, offset:-1},
	{img: IMG_MUSICIAN_SHOW_WE, pack:PACK_SPR_AMBIENT, id:9, offset:-1},
	{img: IMG_CART_BARLEY, pack:PACK_SPR_MAIN, id:91},
	{img: IMG_SIDE_PANEL, pack:PACK_GENERAL, id:121, offset:0},
	{img: IMG_TOP_MENU_BACKGROUND, pack:PACK_GENERAL, id:121, offset:8},
	{img: IMG_EDITOR_SIDE_PANEL, pack:PACK_GENERAL, id:121, offset:0},
	{img: IMG_RESOURCE_PAPYRUS, pack:PACK_GENERAL, id:207, offset:0},
	{img: IMG_EMPIRE_ROUTE_HL_CLOSED, pack:PACK_GENERAL, id:149, offset:211},
	{img: IMG_EMPIRE_ROUTE_OPEN, pack:PACK_GENERAL, id:149, offset:201},
	{img: IMG_EMPIRE_ROUTE_HL_OPEN, pack:PACK_GENERAL, id:149, offset:186},
	{img: IMG_MINIMAP_BLACK, pack:PACK_GENERAL, id:149, offset:5},
	{img: IMG_MINIMAP_BRIGHT_TEAL, pack:PACK_GENERAL, id:149, offset:170},
	{img: IMG_MINIMAP_DARK_GREY, pack:PACK_GENERAL, id:149, offset:210},
	{img: IMG_MINIMAP_GREEN, pack:PACK_GENERAL, id:149, offset:160},
	{img: IMG_MINIMAP_DARK_RED, pack:PACK_GENERAL, id:149, offset:165},
	{img: IMG_MINIMAP_PURPLE, pack:PACK_GENERAL, id:149, offset:175},
	{img: IMG_MINIMAP_LIGHT_YELLOW, pack:PACK_GENERAL, id:149, offset:180},
	{img: IMG_MINIMAP_LILAC, pack:PACK_GENERAL, id:149, offset:195},
	{img: IMG_MINIMAP_SPENT_TEAL, pack:PACK_GENERAL, id:149, offset:200},
	{img: IMG_MINIMAP_COLOR, pack:PACK_GENERAL, id:149, offset:0},
	{img: IMG_TRADE_AMOUNT, pack:PACK_GENERAL, id:171, offset:0},
	{img: IMG_TRADER_CARAVAN, pack:PACK_SPR_AMBIENT, id:20, offset:0},
	{img: IMG_TRADER_CARAVAN_DONKEY, pack:PACK_SPR_MAIN, id:52, offset:0},
]

cart_offsets = [
  {x:17, y:-7},
  {x:22, y:-1},
  {x:17, y:7},
  {x:0, 	y:11},
  {x:-17, y:6},
  {x:-22, y:-1},
  {x:-17, y:-7},
  {x:0, y:-12}
]

sled_offsets = [
  {x:-17, y:9},
  {x:22, y:-1},
  {x:-15, y:-5},
  {x:0, 	y:11},
  {x:12, y:-2},
  {x:-22, y:-1},
  {x:17, y:7},
  {x:0, y:-12}
]
