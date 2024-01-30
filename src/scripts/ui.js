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
	}
}

advisor_rating_window = {
  ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", image : IMG_ADVISOR_RATING_ICON, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text: {group: 53, id: 0},	pos:[60, 17] },
		population_label : { type : "label", text : "",	pos  : {x: 300, y:20} },
		background_image : { type : "image", image : IMG_ADVISOR_BACKGROUND, pos : {x:60, y:38}	},
	},
	column_offset : {x: 30, y:-11}
}

mission_briefing_window = {
	ui : {
		outer_panel : { type : "outer_panel",	pos: [16, 32], size : {w:38, h:27} },
		title 		  : { type : "text", pos : {x:32, y:48}, font : FONT_LARGE_BLACK_ON_LIGHT },
		subtitle 		: { type : "text",	pos : {x: 32, y:78}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		objectives_panel : { type : "inner_panel", pos : {x:32, y:96}, size: {w:33, h:6} },
		objectives_label : { type : "label", text : {group:62, id:10}, pos : {x:48, y:104},	font : FONT_NORMAL_WHITE_ON_DARK },
		tocity_label : { type : "label", text : {group:62, id:7},	pos : {x:416, y:433}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		goal_0 : { type : "label", pos : {x:32 + 16, y:90 + 32}, body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_1 : { type : "label", pos : {x:288 + 16, y:90 + 32},	body : {w:15, h:1},	font : FONT_NORMAL_YELLOW, enabled: false },
		goal_2 : { type : "label", pos : {x:32 + 16, y:112 + 32}, body : {w:15, h:1},	font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_3 : { type : "label", pos : {x:288 + 16, y:112 + 32}, body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false },
		goal_4 : { type : "label", pos : {x:32 + 16, y:134 + 32}, body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false	},
		goal_5 : { type : "label", pos : {x:288 + 16, y:134 + 32}, body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false },
		goal_immediate : { type : "label", pos : {x:32 + 16, y:134 + 32},	body : {w:31, h:1},	font : FONT_NORMAL_YELLOW, enabled: false },
		description_panel : { type : "inner_panel", pos : {x:32, y:200}, size: {w:33, h:14} },
		difficulty_label : { type : "label", pos : {x:105, y:433}, font : FONT_NORMAL_BLACK_ON_LIGHT },
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
