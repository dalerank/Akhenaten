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
		outer_panel_pos : {x:0, y:0},
		outer_panel_size : {w:40, h:27},
		advisor_icon_image : IMG_ADVISOR_RATING_ICON,
		advisor_icon_pos : {x: 10, y: 10},
		header_pos : {x:60, y:17},
		header_population_pos : {x: 160, y:20},
		background_img : IMG_ADVISOR_BACKGROUND,
		background_img_pos: {x:60, y:38},
		column_offset : {x: 30, y:-11}
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
