log_info("akhenaten: ui config started")

top_menu_bar = {
	x_offset : 10,
	y_offset : 6,
	item_height : 20,
	background: IMG_TOP_MENU_BACKGROUND,
	spacing : 32,
	offset_funds_basic : 540,
	offset_population_basic : 400,
	offset_date_basic : 150,
	offset_rotate_basic : 200,
}

main_menu_window = {
	ui : {
		continue_game : { type:"large_button", pos:[192, 125 + 40 * 0], size:[256, 25], text:{group: 13, id: 5}},
		select_player : { type:"large_button", pos:[192, 125 + 40 * 1], size:[256, 25], text:{group: 30, id: 0}},
		show_records  : { type:"large_button", pos:[192, 125 + 40 * 2], size:[256, 25], text:{group: 30, id: 5}},
		show_config   : { type:"large_button", pos:[192, 125 + 40 * 3], size:[256, 25], text:{group: 2, id: 0}},
		quit_game     : { type:"large_button", pos:[192, 125 + 40 * 4], size:[256, 25], text:{group: 30, id: 4}},
		version_number: { type:"text", pos:[18, game.screen.h - 30], text: game.version, font: FONT_SMALL_PLAIN, color: 0xffb3b3b3}
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
		title 		 : { type : "text", pos: [0, 12], size: [28 * 16, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
		warning_text : { type : "text", pos: [32, 40], size: [28 * 16, 0], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
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
