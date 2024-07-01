log_info("akhenaten: ui config started")

function px(i) { return i * 16 }
function sw(v) { return game.screen.w + v}
function sh(v) { return game.screen.h + v}
function mbutton(i) { return [sw(0) / 2 - 128, sh(0) / 2 - 100 + 40 * i] }

top_menu_bar = {
	offset : [10, 6],
	item_height : 20,
	background: IMG_TOP_MENU_BACKGROUND,
	spacing : 32,
	offset_funds_basic : 540,
	offset_population_basic : 400,
	offset_date_basic : 150,
	offset_rotate_basic : 200,

	headers : {
		file 					: { type: "menu_header", text: {group:7, id:0} },
		options				: { type: "menu_header", text: {group:2, id:0} },
		help		   		: { type: "menu_header", text: {group:3, id:0} },
		advisors  		: { type: "menu_header", text: {group:4, id:0} },
		debug		   		: { type: "menu_header", text: "Debug" },
		debug_render  : { type: "menu_header", text: "Render" },
	},

	file : {
		new_game      : { type: "menu_item", text: {group:1, id:1} },
		replay_map    : { type: "menu_item", text: {group:1, id:2} },
		load_game	    : { type: "menu_item", text: {group:1, id:3} },
		save_game	    : { type: "menu_item", text: {group:1, id:4} },
		delete_game	  : { type: "menu_item", text: {group:1, id:6} },
		exit_game	    : { type: "menu_item", text: {group:1, id:5} },
	},

	options : {
		display_options: { type: "menu_item", text: {group:2, id:1} },
		sound_options  : { type: "menu_item", text: {group:2, id:2} },
		speed_options  : { type: "menu_item", text: {group:2, id:3} },
		difficulty_options: { type: "menu_item", text: {group:2, id:6} },
		autosave_options: { type: "menu_item", text: {group:19, id:51} },
		hotkeys_options : { type: "menu_item", text: "Hotkeys options" },
		enhanced_options: { type: "menu_item", text: "Enhanced options" },
	},

	help : {
		help: { type: "menu_item", text: {group:3, id:1} },
		mouse: { type: "menu_item", text: {group:3, id:2} },
		warnings: { type: "menu_item", text: {group:3, id:5} },
		about: { type: "menu_item", text: {group:3, id:7} },
	},

	advisors : {
		advisor_labor 	 :  { type: "menu_item", text:{group: 4, id: ADVISOR_LABOR}, parameter: ADVISOR_LABOR},
    advisor_military :  { type: "menu_item", text:{group: 4, id: ADVISOR_MILITARY}, parameter: ADVISOR_MILITARY},
    advisor_imperial :  { type: "menu_item", text:{group: 4, id: ADVISOR_IMPERIAL}, parameter: ADVISOR_IMPERIAL},
    advisor_ratings  :  { type: "menu_item", text:{group: 4, id: ADVISOR_RATINGS}, parameter: ADVISOR_RATINGS},
    advisor_trade    :  { type: "menu_item", text:{group: 4, id: ADVISOR_TRADE}, parameter: ADVISOR_TRADE},
    advisor_population: { type: "menu_item", text:{group: 4, id: ADVISOR_POPULATION}, parameter: ADVISOR_POPULATION},
    advisor_health   :  { type: "menu_item", text:{group: 4, id: ADVISOR_HEALTH}, parameter: ADVISOR_HEALTH},
    advisor_education:  { type: "menu_item", text:{group: 4, id: ADVISOR_EDUCATION}, parameter: ADVISOR_EDUCATION},
    advisor_entertainment:  { type: "menu_item", text:{group: 4, id: ADVISOR_ENTERTAINMENT}, parameter: ADVISOR_ENTERTAINMENT},
    advisor_religion :  { type: "menu_item", text:{group: 4, id: ADVISOR_RELIGION}, parameter: ADVISOR_RELIGION},
    advisor_financial:  { type: "menu_item", text:{group: 4, id: ADVISOR_FINANCIAL}, parameter: ADVISOR_FINANCIAL},
    advisor_chief    :  { type: "menu_item", text:{group: 4, id: ADVISOR_CHIEF}, parameter: ADVISOR_CHIEF},
	},

	debug : {
		pages 				: { type : "menu_item", text: "", parameter: 0},
		game_time 		: { type : "menu_item", text: "", parameter: 1},
		build_planner : { type : "menu_item", text: "", parameter: 2},
		religion 			: { type : "menu_item", text: "", parameter: 3},
		tutorial 			: { type : "menu_item", text: "", parameter: 4},
		floods 				: { type : "menu_item", text: "", parameter: 5},
		camera 				: { type : "menu_item", text: "", parameter: 6},
		tile_cache 		: { type : "menu_item", text: "", parameter: 7},
		migration 		: { type : "menu_item", text: "", parameter: 8},
 		sentiment 		: { type : "menu_item", text: "", parameter: 9},
 		sound_channels: { type : "menu_item", text: "", parameter: 10},
	},

	debug_render : {
    building 			: { type : "menu_item", text:"", parameter:1},
    tilesize 			: { type : "menu_item", text:"", parameter:2},
    roads 				: { type : "menu_item", text:"", parameter:3},
    routing_dist 	: { type : "menu_item", text:"", parameter:4},
    routing_grid 	: { type : "menu_item", text:"", parameter:5},
    moisture 			: { type : "menu_item", text:"", parameter:6},
    grass_level 	: { type : "menu_item", text:"", parameter:7},
    grass_soil_depletion: { type : "menu_item", text:"", parameter:8},
    grass_flood_order		: { type : "menu_item", text:"", parameter:9},
    grass_flood_flags		: { type : "menu_item", text:"", parameter:10},
    labor 			  : { type : "menu_item", text:"", parameter:11},
    sprite_frames : { type : "menu_item", text:"", parameter:12},
    terrain_bits 	: { type : "menu_item", text:"", parameter:13},
    image 			  : { type : "menu_item", text:"", parameter:14},
    image_alt 		: { type : "menu_item", text:"", parameter:15},
    marshland 		: { type : "menu_item", text:"", parameter:16},
    terrain_type 	: { type : "menu_item", text:"", parameter:17},
    tile_pos 			: { type : "menu_item", text:"", parameter:20},
    floodplain_shore: { type : "menu_item", text:"", parameter:21},
    tile_toph 		: { type : "menu_item", text:"", parameter:22},
    monuments 		: { type : "menu_item", text:"", parameter:23},
    figures 			: { type : "menu_item", text:"", parameter:24},
    height 			  : { type : "menu_item", text:"", parameter:25},
    marshland_depl: { type : "menu_item", text:"", parameter:26},
    damage_fire 	: { type : "menu_item", text:"", parameter:27},
    desirability 	: { type : "menu_item", text:"", parameter:28},
	}
}

main_menu_window = {
	ui : {
		background    : { type:"background", pack:PACK_UNLOADED, id:14, offset:0 },
		continue_game : { type:"large_button", pos:mbutton(0), size:[256, 25], text:{group: 13, id: 5}},
		select_player : { type:"large_button", pos:mbutton(1), size:[256, 25], text:{group: 30, id: 0}},
		show_records  : { type:"large_button", pos:mbutton(2), size:[256, 25], text:{group: 30, id: 5}},
		show_config   : { type:"large_button", pos:mbutton(3), size:[256, 25], text:{group: 2,  id: 0}},
		quit_game     : { type:"large_button", pos:mbutton(4), size:[256, 25], text:{group: 30, id: 4}},
		discord 			: { type:"image_button", pos:[sw(-100), sh(-50)], size:[48, 48], icon_texture:"!discord", scale:0.75 },
		patreon 			: { type:"image_button", pos:[sw(-50), sh(-50)], size:[48, 48], icon_texture:":patreon_48.png", scale:0.75 },
		version_number: { type:"text", pos:[18, sh(-30)], text: game.version, font: FONT_SMALL_PLAIN, color: 0xffb3b3b3}
	}
}

advisor_rating_window = {
  ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:3, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text: {group: 53, id: 0},	pos:[60, 17] },
		population_label : { type : "label", text : "",	pos  : {x: 300, y:20} },
		background_image : { type : "image", image : IMG_ADVISOR_BACKGROUND, pos : {x:60, y:38}	},
	},
	column_offset : {x: 30, y:-11}
}

advisor_religion_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		title : { type : "text", pos: [60, 12], text: {group:59, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:9, pos:[10, 10] },
		nogods_text : { type : "text", pos: [60, 256], text: {group:59, id:43}, wrap:520, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },

		temple_header: { type : "text", pos: [180, 32], text: {group:59, id:5}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		complex_header: { type : "text", pos: [170, 46], text: {group:59, id:2}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		tempe_header: { type : "text", pos: [250, 46], text: {group:59, id:1}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		shrine_header: { type : "text", pos: [320, 46], text: {group:28, id:150}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		months_header: { type : "text", pos: [390, 18], text: {group:59, id:6}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		since_header: { type : "text", pos: [400, 32], text: {group:59, id:8}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		fest_header: { type : "text", pos: [390, 46], text: {group:59, id:7}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		mood_header: { type : "text", pos: [460, 46], text: {group:59, id:3}, font : FONT_NORMAL_BLACK_ON_LIGHT },

		inner_panel : { type : "inner_panel", pos:[32, 60], size:[36, 13] },

		god_0_name: { type : "text", pos: [40, 66]},
		god_0_known: { type : "text", pos: [100, 66]},
		god_0_complex: { type : "text", pos: [200, 66]},
		god_0_temple: { type : "text", pos: [265, 66]},
		god_0_shrine: { type : "text", pos: [330, 66]},
		god_0_fest: { type : "text", pos: [390, 66]},
		god_0_mood: { type : "text", pos: [460, 66]},
		god_0_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 63], enabled:false },
		god_0_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 63], enabled:false },
		god_0_desc: { type : "text", pos: [40, 86], font : FONT_NORMAL_BLACK_ON_DARK },
		god_1_name: { type : "text", pos: [40, 106]},
		god_1_complex: { type : "text", pos: [200, 106]},
		god_1_temple: { type : "text", pos: [265, 106]},
		god_1_shrine: { type : "text", pos: [330, 106]},
		god_1_fest: { type : "text", pos: [390, 106]},
		god_1_mood: { type : "text", pos: [460, 106]},
		god_1_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 103], enabled:false },
		god_1_angle: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 103], enabled:false },
		god_1_known: { type : "text", pos: [40, 106]},
		god_1_desc: { type : "text", pos: [100, 126], font : FONT_NORMAL_BLACK_ON_DARK },
		god_2_name: { type : "text", pos: [40, 146]},
		god_2_complex: { type : "text", pos: [200, 146]},
		god_2_temple: { type : "text", pos: [265, 146]},
		god_2_shrine: { type : "text", pos: [330, 146]},
		god_2_fest: { type : "text", pos: [390, 146]},
		god_2_mood: { type : "text", pos: [460, 146]},
		god_2_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 143], enabled:false },
		god_2_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 143], enabled:false },
		god_2_known: { type : "text", pos: [40, 146]},
		god_2_desc: { type : "text", pos: [100, 166], font : FONT_NORMAL_BLACK_ON_DARK },
		god_3_name: { type : "text", pos: [40, 186]},
		god_3_known: { type : "text", pos: [100, 186]},
		god_3_complex: { type : "text", pos: [200, 186]},
		god_3_temple: { type : "text", pos: [265, 186]},
		god_3_shrine: { type : "text", pos: [330, 186]},
		god_3_fest: { type : "text", pos: [390, 186]},
		god_3_mood: { type : "text", pos: [460, 186]},
		god_3_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 183], enabled:false },
		god_3_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 183], enabled:false },
		god_3_desc: { type : "text", pos: [100, 206], font : FONT_NORMAL_BLACK_ON_DARK },
		god_4_name: { type : "text", pos: [40, 226]},
		god_4_comlex: { type : "text", pos: [200, 226]},
		god_4_temple: { type : "text", pos: [265, 226]},
		god_4_shrine: { type : "text", pos: [330, 226]},
		god_4_fest: { type : "text", pos: [390, 226]},
		god_4_mood: { type : "text", pos: [460, 226]},
		god_4_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 223], enabled:false },
		god_4_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 223], enabled:false },
		god_4_known: { type : "text", pos: [100, 226]},
		god_4_desc: { type : "text", pos: [100, 246], font : FONT_NORMAL_BLACK_ON_DARK },

		advice_text : { type : "text", pos: [60, 273], wrap:512, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		fest_inner_panel : { type : "inner_panel", pos:[48, 252 + 68], size:[34, 6] },
		fest_icon : { type : "image", pack:PACK_UNLOADED, id:21, offset:15, pos:[460, 255 + 68] },
		fest_months_last : { type : "label", pos:[112, 260 + 68], font:FONT_NORMAL_WHITE_ON_DARK},
	}
}

advisor_trade_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:4, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#trade_overseer", pos:[60, 17]},
		hint_label : { type : "label", font : FONT_NORMAL_BLACK_ON_DARK, text:"#trade_overseer_hint", pos:[60, 40]},
		inner_panel : { type : "inner_panel", pos:[17, 60], size:[36, 21] },
		scrollbar : { type: "scrollbar", pos:[590, 52], size:[-1, 336] },
		show_prices : { type:"generic_button", pos:[48, 396], size:[200, 24], text:"#trade_overseer_prices", tooltip:"#trade_overseer_prices_hint" },
		goto_mempire : { type:"generic_button", pos:[368, 396], size:[200, 24], text:"#trade_overseer_goto_empire", tooltip:"#trade_overseer_goto_empire_hint" },
	}
}

advisor_chief_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:11, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#chief_overseer",	pos:[60, 17]},
		inner_panel : { type : "inner_panel", pos:[17, 60], size:[38, 17] },

		// sentiment
		sentiment_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 67] },
		sentiment_label : { type : "label", pos:[44, 66], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_sentiment"},
		sentiment_info : { type : "label", pos:[185, 66], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// migration
		migration_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 87] },
		migration_label : { type : "label", pos:[44, 86], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_migration"},
		migration_info : { type : "label", pos:[185, 86], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// workers
		workers_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 107] },
		workers_label : { type : "label", pos:[44, 106], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_workers"},
		workers_info : { type : "label", pos:[185, 106], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food stocks
		foodstocks_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 127] },
		foodstocks_label : { type : "label", pos:[44, 126], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodstocks"},
		foodstocks_info : { type : "label", pos:[185, 126], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food consumption
		foodconsumption_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 147] },
		foodconsumption_label : { type : "label", pos:[44, 146], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodconsumption"},
		foodconsumption_info : { type : "label", pos:[185, 146], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// health
		health_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 167] },
		health_label : { type : "label", pos:[44, 166], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_health"},
		health_info : { type : "label", pos:[185, 166], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// religion
		religion_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 187] },
		religion_label : { type : "label", pos:[44, 186], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_religion"},
		religion_info : { type : "label", pos:[185, 186], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// finance
		finance_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 207] },
		finance_label : { type : "label", pos:[44, 206], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_finance"},
		finance_info : { type : "label", pos:[185, 206], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// crime
		crime_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 227] },
		crime_label : { type : "label", pos:[44, 226], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_crime"},
		crime_info : { type : "label", pos:[185, 226], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// military
		military_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 247] },
		military_label : { type : "label", pos:[44, 246], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_military"},
		military_info : { type : "label", pos:[185, 246], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// kingdom
		kingdom_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 267] },
		kingdom_label : { type : "label", pos:[44, 266], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_kingdom"},
		kingdom_info : { type : "label", pos:[185, 266], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// nilometr
		nilometr_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 287] },
		nilometr_label : { type : "label", pos:[44, 286], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_nilometr"},
		nilometr_info : { type : "label", pos:[185, 286], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
		nilometr_info2 : { type : "label", pos:[185, 306], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
	}
}

mission_briefing_window = {
	ui : {
		outer_panel : { type : "outer_panel",	pos:[16, 32], size : {w:38, h:27} },
		title 		  : { type : "text", pos:[32, 48], font : FONT_LARGE_BLACK_ON_LIGHT },
		subtitle 		: { type : "text",	pos:[32, 78], font : FONT_NORMAL_BLACK_ON_LIGHT },
		objectives_panel : { type : "inner_panel", pos:[32, 96], size: {w:36, h:6} },
		objectives_label : { type : "label", text : {group:62, id:10}, pos : {x:48, y:104},	font : FONT_NORMAL_WHITE_ON_DARK },
		tocity_label : { type : "label", text : {group:62, id:7},	pos : {x:416, y:433}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		goal_0 : { type : "label", pos:[32  + 16, 90  + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_1 : { type : "label", pos:[288 + 16, 90  + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false },
		goal_2 : { type : "label", pos:[32  + 16, 112 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_3 : { type : "label", pos:[288 + 16, 112 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false },
		goal_4 : { type : "label", pos:[32  + 16, 134 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_5 : { type : "label", pos:[288 + 16, 134 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false },
		goal_immediate : { type : "label", pos : {x:32 + 16, y:134 + 32},	body : {w:31, h:1},	font : FONT_NORMAL_YELLOW, enabled: false },
		description_panel : { type : "inner_panel", pos : {x:32, y:200}, size: {w:33, h:14} },
		difficulty_label : { type : "label", pos:[105, 433], font : FONT_NORMAL_BLACK_ON_LIGHT },
	}
}

granary_info_window = {
	resource_text_group : 23,
	ui : {
		background : { type : "outer_panel",	pos: [0, 0], size: [29, 17] },
		title 		 : { type : "text", text: "#granary_info_title", pos: [0, 12], size: [28 * 16, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 40], wrap:28 * 16, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		storing    : { type : "text", pos: [34, 40], font : FONT_NORMAL_BLACK_ON_LIGHT },
		free_space : { type : "text", pos: [220, 40], font : FONT_NORMAL_BLACK_ON_LIGHT },
		food0_icon : { type : "resource_icon", pos: [34, 68] },
		food0_text : { type : "text", pos: [68, 75], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food1_icon : { type : "resource_icon", pos: [240, 68] },
		food1_text : { type : "text", pos: [274, 75], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food2_icon : { type : "resource_icon", pos: [34, 92] },
		food2_text : { type : "text", pos: [68, 99], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food3_icon : { type : "resource_icon", pos: [240, 92] },
		food3_text : { type : "text", pos: [274, 99], font: FONT_NORMAL_BLACK_ON_LIGHT },
		workers_panel : { type : "inner_panel", pos : [16, 142], size: [27, 5] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 142 + 6] },
		workers_text : { type : "text", pos: [70, 142 + 12], font: FONT_NORMAL_BLACK_ON_DARK },
		workers_desc : { type : "text", pos: [70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK },
	}
}

bazaar_info_window = {
	ui : {
		background : { type : "outer_panel",	pos: [0, 0], size: [29, 16]},
		title 		 : { type : "text", text: "#bazaar_info_title", pos: [0, 10], size: [16 * 29, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 56], wrap:16 * 16, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		food0_icon : { type : "resource_icon", pos: [32, 85] },
		food0_text : { type : "text", pos: [64, 90], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food1_icon : { type : "resource_icon", pos: [142, 85] },
		food1_text : { type : "text", pos: [174, 90], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food2_icon : { type : "resource_icon", pos: [252, 85] },
		food2_text : { type : "text", pos: [284, 90], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food3_icon : { type : "resource_icon", pos: [362, 85] },
		food3_text : { type : "text", pos: [394, 90], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good0_icon : { type : "resource_icon", pos: [32, 110] },
		good0_text : { type : "text", pos: [64, 114], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good1_icon : { type : "resource_icon", pos: [142, 110] },
		good1_text : { type : "text", pos: [174, 114], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good2_icon : { type : "resource_icon", pos: [252, 110] },
		good2_text : { type : "text", pos: [284, 114], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good3_icon : { type : "resource_icon", pos: [362, 110] },
		good3_text : { type : "text", pos: [394, 114], font: FONT_NORMAL_BLACK_ON_LIGHT },
		workers_panel : { type : "inner_panel", pos : [16, 136], size: [27, 4] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 142 + 6] },
		workers_text : { type : "text", pos: [70, 142 + 12], font: FONT_NORMAL_BLACK_ON_DARK },
		workers_desc : { type : "text", pos: [70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK },

		orders : { type:"generic_button", pos:[80, 0], size:[280, 25], text:{group: 98, id: 5}},
	}
}

workshop_info_window = {
	ui : {
		background : { type : "outer_panel", pos: [0, 0], size: [-1, -1] },
		title 		 : { type : "text", pos: [0, 12], size: [-1, 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		produce_icon : { type : "resource_icon", pos: [10, 10] },
		ready_prod : { type : "text", pos: [38, 40], size: [-1, 20], font : FONT_NORMAL_BLACK_ON_LIGHT },
		resource_icon : { type : "resource_icon", pos: [32, 56] },
		resource_stored : { type : "text", pos: [60, 60], size: [-1, 20], font : FONT_NORMAL_BLACK_ON_LIGHT },
		warning_text : { type : "text", pos: [32, 86], wrap:-1, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		workers_panel : { type : "inner_panel", pos : [16, 136], size: [-1, 4] },
	}
}

well_info_window = {
	ui : {
		background : { type : "outer_panel", pos: [0, 0], size: [29, 14] },
		title 		 : { type : "text", pos: [0, 12], size: [px(28), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center", text: "#well_info_title"},
		text : { type : "text", pos: [32, 56], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
	}
}

empire_window = {
	trade_column_spacing : 106,
	trade_row_spacing : 20,
	info_y_traded : -3,
	trade_button_offset_x : 0,
	info_y_sells : 30,
	info_y_buys : 52,
	info_y_footer_1 : 78,
	info_y_city_name : 120,
	info_y_city_desc : 28,
	text_group_old_names : 195,
	text_group_new_names : 21,
	trade_resource_size : 18,
	trade_resource_offset : 3,
	sell_res_group : 47,
	trade_button_offset_y : 10,
}

minimap_window = {
	terrain_canal : {pack:PACK_GENERAL, id:151},
	terrain_water : {pack:PACK_GENERAL, id:142},
}
