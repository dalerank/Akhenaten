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
	x_pos : 192,
	y_pos : 125,
	btn_width : 256,
	btn_height : 25,
	button_offset : 40,

	buttons : [
		{group: 13, id: 5, },
	  {group: 30, id: 0, },
	  {group: 30, id: 5, },
	  {group: 2, id: 0, },
	  {group: 30, id: 4, }
	]
}
