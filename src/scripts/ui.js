log_info("akhenaten: top_menu_bar started")

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
	button_pos : {x: 192, y: 125},
	button_size : {w: 256, h: 25},
	button_offset : 40,

	buttons : [
		{group: 13, id: 5, },
	  {group: 30, id: 0, },
	  {group: 30, id: 5, },
	  {group: 2, id: 0, },
	  {group: 30, id: 4, }
	]
}

advisor_rating_window = {
  ui : {
		outer_panel : {
			type : "outer_panel",
			pos  : {x:0, y:0},
		  size : {w:40, h:27},
		},
		advisor_icon : {
			type : "image",
			image : IMG_ADVISOR_RATING_ICON,
		  pos  : {x: 10, y: 10},
		},
		header_label : {
			type : "label",
			font : FONT_LARGE_BLACK_ON_LIGHT,
			text : {group: 53, id: 0},
			pos  : {x: 60, y:17}
		},
		population_label : {
			type : "label",
			text : "",
			pos  : {x: 300, y:20}
		},
		background_image : {
			type : "image",
			image : IMG_ADVISOR_BACKGROUND,
		  pos  : {x:60, y:38},
		},
	},
	column_offset : {x: 30, y:-11}
}

mission_briefing_window = {
	ui : {
		outer_panel : {
			type : "outer_panel",
			pos  : {x:16, y:32},
		  size : {w:38, h:27},
		},
		title : {
			type : "text",
			pos : {x:32, y:48},
			font : FONT_LARGE_BLACK_ON_LIGHT,
		},
		subtitle : {
			type : "text",
			pos : {x: 32, y:78},
			font : FONT_NORMAL_BLACK_ON_LIGHT
		},
		objectives : {
			type : "label", 
			text : {group:62, id:7},
			pos : {x:376, y:433},
			font : FONT_NORMAL_BLACK_ON_LIGHT
		}
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
