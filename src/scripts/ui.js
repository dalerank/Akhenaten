log_info("akhenaten: ui config started")

function px(i) { return i * 16 }
function sw(v) { return game.screen.w + v}
function sh(v) { return game.screen.h + v}
function mbutton(i) { return [sw(0) / 2 - 128, sh(0) / 2 - 100 + 40 * i] }

function __baseui(base, ext) {
    var newui = {};

    for (var key in base.ui) { newui[key] = base.ui[key] }
    for (var key in ext) { newui[key] = ext[key]}

    return newui;
}

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
 		properties		: { type : "menu_item", text: "", parameter: 11},
 		show_console  : { type : "menu_item", text: "", parameter: 12},
 		make_screenshot : { type : "menu_item", text: "", parameter: 13},
 		make_full_screenshot : { type : "menu_item", text: "", parameter: 14},
 		write_video   : { type : "menu_item", text: "", parameter: 15},
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
		fest_months_last : { type : "label", pos:[112, 328], font:FONT_NORMAL_WHITE_ON_DARK},
		planed_festival : { type : "text", pos: [102, 284 + 68], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" },
		hold_festival_btn : { type:"generic_button", pos:[102, 278 + 68], size:[300, 24] },
		festival_advice : { type : "text", pos: [56, 305 + 68], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true },
	}
}

advisor_trade_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:4, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#trade_overseer", pos:[60, 17]},
		hint_label : { type : "label", font : FONT_NORMAL_BLACK_ON_DARK, text:"#trade_overseer_hint", pos:[60, 40]},
		inner_panel : { type : "inner_panel", pos:[17, 60], size:[36, 21] },
		scrollbar : { type: "scrollbar", pos:[594, 60], size:[-1, 336] },
		show_prices : { type:"generic_button", pos:[48, 396], size:[200, 24], text:"#trade_overseer_prices", tooltip:"#trade_overseer_prices_hint" },
		goto_mempire : { type:"generic_button", pos:[368, 396], size:[200, 24], text:"#trade_overseer_goto_empire", tooltip:"#trade_overseer_goto_empire_hint" },
	}
}

advisor_imperial_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:2, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, pos:[60, 17]},
		rating_label : { type : "label", font : FONT_NORMAL_BLACK_ON_DARK, pos:[460, 24]},
		rating_advice : { type : "label", font : FONT_NORMAL_BLACK_ON_DARK, pos:[60, 46], wrap: 500, multiline:true},
		inner_panel : { type : "inner_panel", pos:[32, 90], size:[36, 14] },

		bottom_panel : { type : "inner_panel", pos:[64, 324], size:[32, 6] },
		send_gift : { type:"generic_button", font : FONT_NORMAL_WHITE_ON_DARK, pos:[320, 367], size:[250, 20], text:{group:52, id:49} },
		donate_to_city : { type:"generic_button", font : FONT_NORMAL_WHITE_ON_DARK, pos:[320, 341], size:[250, 20], text:{group:52, id:2} },
		player_rank : { type : "label", font : FONT_NORMAL_WHITE_ON_DARK, pos:[72, 338]},
		personal_savings : { type : "label", font : FONT_NORMAL_WHITE_ON_DARK, pos:[72, 372]},
		salary_rank : { type:"generic_button", font : FONT_NORMAL_WHITE_ON_DARK, pos:[70, 393], size:[500, 24] },
	},
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
	pos: [(sw(0) - px(38))/2, (sh(0) - px(27))/2],
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
		description_text : { type : "text", pos: [40, 216], size:[px(36), px(10)], wrap:px(34), font : FONT_NORMAL_WHITE_ON_DARK, link_font:FONT_NORMAL_YELLOW, rich:true, clip_area:true },
		difficulty_label : { type : "label", pos:[105, 433], size:[31, 14], font : FONT_NORMAL_BLACK_ON_LIGHT },
		back 			: { type:"image_button", pos:[26, 428], size:[31, 20], pack:PACK_GENERAL, id:90, offset:8 },
		start_mission : { type:"image_button", pos:[516, 430], size:[27, 27], pack:PACK_GENERAL, id:90, offset:0 },
		dec_difficulty : { type:"image_button", pos:[65, 428], size:[17, 17], pack:PACK_GENERAL, id:212, offset:0 },
		inc_difficulty : { type:"image_button", pos:[65 + 18, 428], size:[17, 17], pack:PACK_GENERAL, id:212, offset:3 },
	}
}

roadblock_info_window = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 : { type : "text", pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

orders_window_granary = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 : { type : "text", pos: [0, 12], size: [px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		orders_panel : { type : "inner_panel", pos : [16, 42], size: [27, 10] },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		empty_all : { type:"generic_button", pos:[80, -1], size:[300, 24], margin:{bottom:-64} },
		accept_none : { type:"generic_button", pos:[80, -1], size:[300, 24], text:{group:99, id:7}, margin:{bottom:-38} },
	}
}

granary_info_window = {
	resource_text_group : 23,
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 : { type : "text", text: "#granary_info_title", pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 40], wrap:px(28), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
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
		orders : { type:"generic_button", pos:[100, -1], size:[270, 25], text:{group: 98, id: 5}},
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		mothball : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

info_window_vacant_lot = {
	help_id : 128,
	ui : {
		background : { type : "outer_panel",	size: [29, 23] }, // pos/size setup from code
		title 		 : { type : "text", pos: [0, 12], size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		inner_panel : { type : "inner_panel", pos : [16, 40], size: [27, 13] },
		describe 	 : { type : "text", pos: [36, 114], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(25) },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

info_window_house = {
	resource_text_group : 23,
	help_id : 56,
	ui : {
		background : { type : "outer_panel",	size: [29, 23] }, // pos/size setup from code
		title 		 : { type : "text", pos: [0, 12], size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		evolve_reason : { type : "text", pos: [32, 40], font : FONT_NORMAL_BLACK_ON_LIGHT, rich:true, wrap:px(28), scroll:false },
		food0_icon : { type : "resource_icon", pos: [32, 95] },
		food0_text : { type : "text", pos: [64, 100], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food1_icon : { type : "resource_icon", pos: [142, 95] },
		food1_text : { type : "text", pos: [174, 100], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food2_icon : { type : "resource_icon", pos: [252, 95] },
		food2_text : { type : "text", pos: [284, 100], font: FONT_NORMAL_BLACK_ON_LIGHT },
		food3_icon : { type : "resource_icon", pos: [362, 95] },
		food3_text : { type : "text", pos: [394, 100], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good0_icon : { type : "resource_icon", pos: [32, 120] },
		good0_text : { type : "text", pos: [64, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good1_icon : { type : "resource_icon", pos: [142, 120] },
		good1_text : { type : "text", pos: [174, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good2_icon : { type : "resource_icon", pos: [252, 120] },
		good2_text : { type : "text", pos: [284, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good3_icon : { type : "resource_icon", pos: [362, 120] },
		good3_text : { type : "text", pos: [394, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		tenants_panel : { type : "inner_panel", pos : [16, 148], size: [27, 10] },
		people_icon : { type : "image", pos: [34, 154], pack:PACK_GENERAL, id:134, offset:13, },
		people_text : { type : "text", pos: [64, 164], font: FONT_NORMAL_BLACK_ON_DARK, },
		tax_info : { type : "text", pos: [36, 194], font: FONT_NORMAL_BLACK_ON_DARK, },
		happiness_info : { type : "text", pos: [36, 214], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) },
		additional_info : { type : "text", pos: [36, 234], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

hold_festival_window = {
	pos : [(sw(0) - px(34)) / 2 - 50, (sh(0) - px(20)) / 2 - 100],
	ui : {
		background : { type : "outer_panel",	pos: [48, 48], size: [34, 20]},
		title 		 : { type : "text", pos: [48, 60], size: [544, -1], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		god0 			 : { type : "image_button", pos:[100 * 0 + 70, 96], pack:PACK_UNLOADED, id:21, offset:16 + 0, offset_pressed:5, offset_focused:5, border:true },
		god1 			 : { type : "image_button", pos:[100 * 1 + 70, 96], pack:PACK_UNLOADED, id:21, offset:16 + 1, offset_pressed:5, offset_focused:5, border:true },
		god2 			 : { type : "image_button", pos:[100 * 2 + 70, 96], pack:PACK_UNLOADED, id:21, offset:16 + 2, offset_pressed:5, offset_focused:5, border:true },
		god3 			 : { type : "image_button", pos:[100 * 3 + 70, 96], pack:PACK_UNLOADED, id:21, offset:16 + 3, offset_pressed:5, offset_focused:5, border:true },
		god4 			 : { type : "image_button", pos:[100 * 4 + 70, 96], pack:PACK_UNLOADED, id:21, offset:16 + 4, offset_pressed:5, offset_focused:5, border:true },
		small_festival : { type:"generic_button", pos:[102, 216], size:[430, 26], rich:true},
		middle_festival : { type:"generic_button", pos:[102, 246], size:[430, 26], rich:true},
		large_festival : { type:"generic_button", pos:[102, 276], size:[430, 26], rich:true},
		button_ok  : { type : "image_button", pos:[400, 317], size:[39, 26], pack:PACK_GENERAL, id:96, offset:0 },
		button_cancel  : { type : "image_button", pos:[358, 317], size:[39, 26], pack:PACK_GENERAL, id:96, offset:4 },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:0 },
		festival_type : { type : "text", pos: [220, 327], size: [544, -1] },
	}
}

empty_info_window = {
	ui : {
		//background : { type : "outer_panel",	pos: [48, 48], size: [34, 20]},
	}
}

figure_info_window = {
	ui : {
		background 		 : { type : "outer_panel",	pos: [0, 0], size: [29, 22]},
		inner_panel 	 : { type : "inner_panel", pos : [16, 40], size: [27, 13] },
		border 				 : { type : "border", border:0, pos : [24, 102], size: [px(26), 138] },
		bigimage    	 : { type : "image", pos: [28, 112], pack:PACK_UNLOADED, id:25 },
		name 					 : { type : "text", pos: [90, 108], font : FONT_LARGE_BLACK_ON_DARK },
		type 					 : { type : "text", pos: [92, 139], font : FONT_NORMAL_BLACK_ON_DARK },
		phrase				 : { type : "text", pos: [90, 160], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(25), multiline:true },
		button_figure0 : { type : "image_button", pos:[60 * 0 + 27, 45], size:[52, 52], border:true },
		button_figure1 : { type : "image_button", pos:[60 * 1 + 27, 45], size:[52, 52], border:true },
		button_figure2 : { type : "image_button", pos:[60 * 2 + 27, 45], size:[52, 52], border:true },
		button_figure3 : { type : "image_button", pos:[60 * 3 + 27, 45], size:[52, 52], border:true },
		button_figure4 : { type : "image_button", pos:[60 * 4 + 27, 45], size:[52, 52], border:true },
		button_figure5 : { type : "image_button", pos:[60 * 5 + 27, 45], size:[52, 52], border:true },
		button_figure6 : { type : "image_button", pos:[60 * 6 + 27, 45], size:[52, 52], border:true },
		button_help  	 : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close   : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_path 		 : { type : "generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		show_overlay   : { type : "generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

info_window_figure_enemy = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 22]},
	}
}

terrain_info_window = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 20]},
		title 		 	: { type : "text", pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		describe 		: { type : "text", pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) },
		button_help : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close: { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

temple_info_window = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 18]},
		title 		 	: { type : "text", pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		inner_panel : { type : "inner_panel", pos : [16, 56], size: [27, 4] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 70] },
		workers_text : { type : "text", pos: [70, 74], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 74 + 16], font: FONT_NORMAL_BLACK_ON_DARK },
		button_help : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close: { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay: { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		god_image 	: { type : "image", pos: [190, 134] },
		mothball 		: { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

building_info_window = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 	: { type : "text", pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		inner_panel : { type : "inner_panel", pos : [16, 100], size: [27, 5] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 110] },
		workers_text : { type : "text", pos: [70, 116], font: FONT_NORMAL_BLACK_ON_DARK},
		workers_desc : { type : "text", pos: [70, 116 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) },
		first_advisor  : { type : "image_button", pos:[40, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		second_advisor : { type : "image_button", pos:[64, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		third_advisor : { type : "image_button", pos:[96, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		mothball : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

info_window_fishing_wharf = {
	ui : __baseui(building_info_window, {
		resource_img : { type : "resource_icon", pos: [32, 186] },
		storage_desc : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
	})
}

info_window_farm = {
	ui : __baseui(building_info_window, {
		resource : { type : "resource_icon", pos:[10, 10] },
		progress_desc : { type : "text", pos: [32, 44], font: FONT_NORMAL_BLACK_ON_LIGHT },
		farm_desc : { type : "text", pos: [32, 64], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true },
		farm_state : { type : "text", pos: [32, 186], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true },
		flood_info : { type : "text", pos: [32, 206], font: FONT_NORMAL_BLACK_ON_LIGHT },
	})
}

raw_material_info_window = {
	ui : __baseui(building_info_window, {
		resource_img : { type : "resource_icon", pos: [10, 10] },
		progress_desc : { type : "text", pos: [32, 44], font: FONT_NORMAL_BLACK_ON_LIGHT },
		mine_desc : { type : "text", pos: [32, 176], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true },
		inner_panel : { type : "inner_panel", pos : [16, 106], size: [27, 4] },
	})
}

info_window_garden = {
	ui : {
		background 	  : { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 	  : { type : "text", pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		describe  		: { type : "text", pos: [32, 66], text: "#gardens_describe", wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		button_help   : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

info_window_palace = {
	ui : __baseui(building_info_window, {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 18]},
		resource_img : { type : "resource_icon", pos: [16, 16] },
		inner_panel : { type : "inner_panel", pos : [16, 100], size: [27, 6] },
		vaults_hold : { type : "text", pos: [44, 54], font: FONT_NORMAL_BLACK_ON_LIGHT },
		text_visit : { type : "text", pos: [90, 252], font: FONT_NORMAL_BLACK_ON_LIGHT, text:"#visit_rating_advisor" },
		visit_advisor  : { type : "image_button", pos:[52, 246], size:[28, 28], pack:PACK_GENERAL, id:106 },
	})
}

entertainment_info_window = {
	ui : {
		background 	: { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 	: { type : "text", pos: [0, 12], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 46], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		inner_panel : { type : "inner_panel", pos : [16, 116], size: [27, 4] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 126] },
		workers_text : { type : "text", pos: [70, 134], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 136 + 20], font: FONT_NORMAL_BLACK_ON_DARK },
		first_advisor  : { type : "image_button", pos:[42, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		second_advisor : { type : "image_button", pos:[64, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		third_advisor : { type : "image_button", pos:[96, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		mothball : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

info_window_health = {
	ui : __baseui(building_info_window, {})
}

legion_info_window = {

}

taxcollector_info_window = {
	ui : {
		background 	 : { type : "outer_panel",	pos: [0, 0], size: [29, 17]},
		title 		 	 : { type : "text", pos: [0, 12], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		deben_icon   : { type : "resource_icon", pos: [16, 46] },
		tax_level 	 : { type : "label", pos:[px(29) / 2 + 50, 46], font : FONT_NORMAL_BLACK_ON_LIGHT },
		dec_tax 	   : { type : "arrow_button", pos:[px(29) / 2 + 170, 38], size:[17, 17], down:true},
		inc_tax 		 : { type : "arrow_button", pos:[px(29) / 2 + 193, 38], size:[17, 17], down:false},
		money_text 	 : { type : "text", pos: [44, 44], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		warning_text : { type : "text", pos: [28, 72], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		inner_panel  : { type : "inner_panel", pos : [16, 136], size: [27, 5] },
		workers_img  : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 146] },
		workers_text : { type : "text", pos: [70, 154], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 156 + 20], font: FONT_NORMAL_BLACK_ON_DARK },
		first_advisor : { type : "image_button", pos:[42, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		second_advisor: { type : "image_button", pos:[64, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		third_advisor : { type : "image_button", pos:[96, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		mothball 		 : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

bazaar_info_window = {
	ui : {
		background : { type : "outer_panel",	pos: [0, 0], size: [29, 16]},
		title 		 : { type : "text", text: "#bazaar_info_title", pos: [0, 10], size: [16 * 29, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 36], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
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
		workers_text : { type : "text", pos: [70, 142 + 12], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK },
		orders : { type:"generic_button", pos:[100, 0], size:[270, 25], text:{group: 98, id: 5}},
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		show_overlay : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
		mothball : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
	}
}

festival_square_info_window = {
	ui : {
		background : { type : "outer_panel",	pos: [0, 0], size: [29, 16]},
		title 		 : { type : "text", text: "#festival_square_info_title", pos: [0, 10], size: [px(29), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning		 : { type : "text", pos: [32, 36], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		workers_panel : { type : "inner_panel", pos : [16, 96], size: [27, 7] },
		fest_months_last : { type : "text", pos:[32, 112], size: [px(25), 20], font:FONT_NORMAL_WHITE_ON_DARK, align:"center"},
		hold_festival : { type:"generic_button", pos:[60, 134], size:[px(22), 25], font:FONT_NORMAL_WHITE_ON_DARK, text:{group: 58, id: 16}},
		planed_festival : { type : "text", pos: [102, 134], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" },
		festival_advice : { type : "text", pos: [36, 164], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

workshop_info_window = {
	ui : {
		background : { type : "outer_panel", pos: [0, 0], size: [29, 16] },
		title 		 : { type : "text", pos: [0, 12], size: [px(27), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		produce_icon : { type : "resource_icon", pos: [10, 10] },
		workers_panel : { type : "inner_panel", pos : [16, 96], size: [27, 4] },
		workers_text : { type : "text", pos: [70, 102 + 12], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 102 + 26], font: FONT_NORMAL_BLACK_ON_DARK },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 102 + 6] },
		ready_prod : { type : "text", pos: [38, 40], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT },
		resource_icon : { type : "resource_icon", pos: [32, 56] },
		resource_stored : { type : "text", pos: [60, 60], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT },
		warning_text : { type : "text", pos: [32, 168], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
	}
}

well_info_window = {
	ui : {
		background : { type : "outer_panel", pos: [0, 0], size: [29, 14] },
		title 		 : { type : "text", pos: [0, 12], size: [px(28), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center", text: "#well_info_title"},
		text : { type : "text", pos: [32, 56], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
	}
}

info_window_storageyard = {
	ui : {
		background : { type : "outer_panel", pos: [0, 0], size: [29, 19] },
		title 		 : { type : "text", pos: [0, 12], size: [px(27), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"},

		storing    : { type : "text", pos: [34, 40], font : FONT_NORMAL_BLACK_ON_LIGHT },
		free_space : { type : "text", pos: [220, 40], font : FONT_NORMAL_BLACK_ON_LIGHT },

		good0_icon : { type : "resource_icon", pos: [32, 60] },
		good0_text : { type : "text", pos: [54, 64], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good1_icon : { type : "resource_icon", pos: [172, 60] },
		good1_text : { type : "text", pos: [194, 64], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good2_icon : { type : "resource_icon", pos: [292, 60] },
		good2_text : { type : "text", pos: [314, 64], font: FONT_NORMAL_BLACK_ON_LIGHT },

		good3_icon : { type : "resource_icon", pos: [32, 90] },
		good3_text : { type : "text", pos: [54, 94], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good4_icon : { type : "resource_icon", pos: [172, 60] },
		good4_text : { type : "text", pos: [194, 94], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good5_icon : { type : "resource_icon", pos: [292, 90] },
		good5_text : { type : "text", pos: [314, 94], font: FONT_NORMAL_BLACK_ON_LIGHT },

		good6_icon : { type : "resource_icon", pos: [32, 120] },
		good6_text : { type : "text", pos: [54, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good7_icon : { type : "resource_icon", pos: [172, 120] },
		good7_text : { type : "text", pos: [194, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },
		good8_icon : { type : "resource_icon", pos: [292, 120] },
		good8_text : { type : "text", pos: [314, 124], font: FONT_NORMAL_BLACK_ON_LIGHT },

		warning_text : { type : "text", pos: [32, 56], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		workers_panel : { type : "inner_panel", pos : [16, 168], size: [27, 5] },
		workers_img : { type : "image", pack:PACK_GENERAL, id:134, offset:14, pos:[40, 173] },
		workers_text : { type : "text", pos: [70, 178], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) },
		workers_desc : { type : "text", pos: [70, 178 + 16], font: FONT_NORMAL_BLACK_ON_DARK },
		cartstate_img : { type : "resource_icon", pos:[40, 220] },
		cartstate_desc : { type : "text", pos: [32, 223], wrap:px(27), font : FONT_NORMAL_BLACK_ON_DARK, multiline:true },

		orders : { type:"generic_button", pos:[100, -1], size:[270, 24], text:{group: 99, id: 2}},
		button_help  : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
		button_close  : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
		mothball : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
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
	terrain_water : {pack:PACK_GENERAL, id:142},
	terrain_shrub : {pack:PACK_GENERAL, id:143},
	terrain_tree  : {pack:PACK_GENERAL, id:143},
	terrain_marshland : {pack:PACK_GENERAL, id:144},
	terrain_rock  : {pack:PACK_GENERAL, id:145},
	terrain_elevation : {pack:PACK_GENERAL, id:145},
	terrain_meadow : {pack:PACK_GENERAL, id:146},
	terrain_flooplain : {pack:PACK_GENERAL, id:146},
	terrain_road : {pack:PACK_GENERAL, id:147},
	terrain_wall : {pack:PACK_GENERAL, id:150},
	terrain_canal : {pack:PACK_GENERAL, id:151},
	terrain_dune : {pack:PACK_GENERAL, id:211},
	terrain_teal : {pack:PACK_GENERAL, id:149, offset:200},
}
