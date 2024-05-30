log_info("akhenaten: images started")

images = [
	// spr main
	{img: IMG_SLED_BRICKS, pack:PACK_SPR_MAIN, id:89},
	{img: IMG_SLED_SANDSTONE_SMALL, pack:PACK_SPR_MAIN, id:101},
	{img: IMG_SLED_STONE_SMALL, pack:PACK_SPR_MAIN, id:102},
	{img: IMG_SLED_GRANITE_SMALL, pack:PACK_SPR_MAIN, id:103},
	{img: IMG_SLED_LIMESTONE_SMALL, pack:PACK_GENERAL, id:104},
	{img: ANIM_DOCKER_WALK, pack:PACK_SPR_MAIN, id:43}, // 10005
	{img: ANIM_OSTRICH_HUNTER_WALK, pack:PACK_SPR_MAIN, id:45}, // 2657
	{img: ANIM_OSTRICH_HUNTER_DEATH, pack:PACK_SPR_MAIN, id:46}, // 2657
	{img: ANIM_OSTRICH_HUNTER_HUNT, pack:PACK_SPR_MAIN, id:47}, // 2753
	{img: ANIM_OSTRICH_HUNTER_FIGHT, pack:PACK_SPR_MAIN, id:48}, // 2761
	{img: ANIM_OSTRICH_HUNTER_UNPACK, pack:PACK_SPR_MAIN, id:49}, // 2857
	{img: ANIM_OSTRICH_HUNTER_PACK, pack:PACK_SPR_MAIN, id:50}, // 3049
	{img: ANIM_OSTRICH_HUNTER_MOVE_PACK, pack:PACK_SPR_MAIN, id:51}, // 3193

	// spr ambient
	{img: IMG_FISHING_POINT, pack:PACK_SPR_AMBIENT, id:8},
	{img: IMG_EXPLOSION, pack:PACK_SPR_AMBIENT, id:12, offset:0},
	{img: IMG_FISHING_POINT_BUBLES, pack:PACK_SPR_AMBIENT, id:11},
	{img: ANIM_SANDSTONE_QUARRY_2, pack:PACK_SPR_AMBIENT, id:49},

	// icon resources
	{img: IMG_RESOURCE_ICONS, pack:PACK_GENERAL, id:129},

	{img: IMG_JUGGLER_SHOW, pack:PACK_SPR_AMBIENT, id:7, offset:-1},
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
	{img: IMG_TRADER_CARAVAN_DEATH, pack:PACK_SPR_AMBIENT, id:21, offset:0},
	{img: IMG_TRADER_CARAVAN_DONKEY, pack:PACK_SPR_MAIN, id:52, offset:0},
	{img: IMG_TRADER_CARAVAN_DONKEY_DEATH, pack:PACK_SPR_MAIN, id:53, offset:0},
	{img: IMG_HOUSE_HUT, pack:PACK_GENERAL, id:26, offset:0},
	{img: IMG_HOUSE_SHANTY, pack:PACK_GENERAL, id:27, offset:0},
	{img: IMG_HOUSE_COTTAGE, pack:PACK_GENERAL, id:28, offset:0},
	{img: IMG_HOUSE_HOMESTEAD, pack:PACK_GENERAL, id:29, offset:0},
	{img: IMG_HOUSE_APARTMENT, pack:PACK_GENERAL, id:30, offset:0},
	{img: IMG_BRICKLAYER_WALK, pack:PACK_SPR_MAIN, id:109},
	{img: IMG_BRICKLAYER_DEATH, pack:PACK_SPR_MAIN, id:110},
	{img: IMG_BRICKLAYER_WORK, pack:PACK_SPR_MAIN, id:111},
	{img: IMG_BRICKLAYER_IDLE, pack:PACK_SPR_MAIN, id:112},
	{img: IMG_MONUMENT_ENTER, pack:PACK_GENERAL, id:114},
	{img: IMG_SLED_PULLER, pack:PACK_SPR_MAIN, id:121},
	{img: IMG_BIGSLED_EMPTY, pack:PACK_SPR_MAIN, id:166},
	{img: IMG_BIGSLED_STONE, pack:PACK_SPR_MAIN, id:167},
	{img: IMG_BIGSLED_SANDSTONE, pack:PACK_SPR_MAIN, id:168},
	{img: IMG_BIGSLED_GRANITE, pack:PACK_SPR_MAIN, id:169},
	{img: IMG_BIGSLED_LIMESTONE, pack:PACK_SPR_MAIN, id:170},
	{img: IMG_BIGSLED_CLAY, pack:PACK_SPR_MAIN, id:171},
	{img: IMG_BIGSLED_BRICKS, pack:PACK_SPR_MAIN, id:172},
	{img: IMG_SMALL_MASTABA_BRICKS, pack:PACK_MASTABA, id:1, offset:0},
	{img: IMG_ADVISOR_ICONS, pack:PACK_GENERAL, id:128, offset:0},
	{img: IMG_ADVISOR_BACKGROUND, pack:PACK_UNLOADED, id:2, offset:0},
	{img: IMG_PRIEST_OSIRIS, pack:PACK_SPR_MAIN, id:197, offset:0},
	{img: IMG_PRIEST_OSIRIS_DEATH, pack:PACK_SPR_MAIN, id:198, offset:0},
	{img: IMG_PRIEST_RA, pack:PACK_SPR_MAIN, id:210, offset:0},
	{img: IMG_PRIEST_RA_DEATH, pack:PACK_SPR_MAIN, id:211, offset:0},
	{img: IMG_PRIEST_PTAH, pack:PACK_SPR_MAIN, id:187, offset:0},
	{img: IMG_PRIEST_PTAH_DEATH, pack:PACK_SPR_MAIN, id:188, offset:0},
	{img: IMG_PRIEST_SETH, pack:PACK_SPR_MAIN, id:193, offset:0},
	{img: IMG_PRIEST_SETH_DEATH, pack:PACK_SPR_MAIN, id:194, offset:0},
	{img: IMG_PRIEST_BAST, pack:PACK_SPR_MAIN, id:208, offset:0},
	{img: IMG_PRIEST_BAST_DEATH, pack:PACK_SPR_MAIN, id:209, offset:0},
	{img: IMG_TERRAIN_FLOODPLAIN, pack:PACK_TERRAIN, id:31, offset:0},
	{img: ANIM_MARKET_BUYER_WALK, pack:PACK_SPR_MAIN, id:16, offset:0},
	{img: ANIM_MARKET_BUYER_DEATH, pack:PACK_SPR_MAIN, id:17, offset:0},
	{img: ANIM_MARKET_LADY_WALK, pack:PACK_SPR_MAIN, id:18, offset:0},
	{img: ANIM_MARKET_LADY_DEATH, pack:PACK_SPR_MAIN, id:19, offset:0},
	{img: ANIM_DELIVERY_BOY_WALK, pack:PACK_SPR_MAIN, id:9, offset:0},
	{img: ANIM_DELIVERY_BOY_DEATH, pack:PACK_SPR_MAIN, id:10, offset:0},
	{img: ANIM_TRADER_SHIP_WALK, pack:PACK_SPR_MAIN, id:40, offset:0},
	{img: ANIM_TRADER_SHIP_DEATH, pack:PACK_SPR_MAIN, id:41, offset:0},
	{img: ANIM_TRADER_SHIP_IDLE, pack:PACK_SPR_MAIN, id:42, offset:0},
	{img: ANIM_DOCTOR_WALK, pack:PACK_SPR_MAIN, id:71, offset:0},
	{img: ANIM_DOCTOR_DEATH, pack:PACK_SPR_MAIN, id:72, offset:0},
	{img: ANIM_HERBALIST_WALK, pack:PACK_SPR_MAIN, id:180, offset:0},
	{img: ANIM_HERBALIST_DEATH, pack:PACK_SPR_MAIN, id:181, offset:0},
	{img: ANIM_DANCER_WALK, pack:PACK_SPR_MAIN, id:128, offset:0},
	{img: ANIM_DANCER_DEATH, pack:PACK_SPR_MAIN, id:129, offset:0},
]

cart_images = [
	{resource: RESOURCE_NONE, pack:PACK_SPR_MAIN, id:77 },
	{resource: RESOURCE_BARLEY, pack:PACK_SPR_MAIN, id:91 },
	{resource: RESOURCE_COPPER, pack:PACK_SPR_MAIN, id:107 },
	{resource: RESOURCE_BEER, pack:PACK_SPR_MAIN, id:92 },
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
