log_info("akhenaten: ui top menu config started")

function menu_item(config) { return __extend({ type : "menu_item"}, config) }
function menu_header(config) { return __extend({ type : "menu_header"}, config) }

top_menu_widget {
	offset [10, 6]
	item_height : 20
	background { pack:PACK_GENERAL, id:121, offset:8 }
	sidebar_offset : 158
	spacing : 16
	offset_rotate_basic : 200

	headers {
		file 			: menu_header({text: {group:7, id:0}, tooltip:[68, 51] })
		options			: menu_header({text: {group:2, id:0}, tooltip:[68, 52] })
		help		   	: menu_header({text: {group:3, id:0}, tooltip:[68, 53] })
		advisors  		: menu_header({text: {group:4, id:0} })
		debug		   	: menu_header({text: "Debug" })
		debug_render  	: menu_header({text: "Render" })
	}

	file {
		new_game     	: menu_item({text: {group:1, id:1}, onclick: __widget_top_menu_new_game })
		replay_map   	: menu_item({text: {group:1, id:2}, onclick: __widget_top_menu_replay_map })
		load_game	    : menu_item({text: {group:1, id:3}, onclick: __widget_top_menu_load_map })
		save_game	    : menu_item({text: {group:1, id:4}, onclick: __widget_top_menu_save_map })
		delete_game	  	: menu_item({text: {group:1, id:6}, onclick: __widget_top_menu_delete_map })
		exit_game	    : menu_item({text: {group:1, id:5}, onclick: __widget_top_menu_exit_game })
	}

	options {
		display_options	: menu_item({text: {group:2, id:1} })
		sound_options  	: menu_item({text: {group:2, id:2} })
		speed_options  	: menu_item({text: {group:2, id:3} })
		difficulty_options: menu_item({ text: {group:2, id:6} })
		autosave_options: menu_item({text: {group:19, id:51} })
		hotkeys_options : menu_item({text: "Hotkeys options" })
		enhanced_options: menu_item({text: "Enhanced options" })
	}

	help {
		help 			: menu_item({text: {group:3, id:1} })
		mouse 			: menu_item({text: {group:3, id:2} })
		warnings 		: menu_item({text: {group:3, id:5} })
		about 			: menu_item({text: {group:3, id:7} })
	}

	advisors {
		advisor_labor 	 :  menu_item({text:{group: 4, id: ADVISOR_LABOR}, parameter: ADVISOR_LABOR})
	    advisor_military :  menu_item({text:{group: 4, id: ADVISOR_MILITARY}, parameter: ADVISOR_MILITARY})
	    advisor_imperial :  menu_item({text:{group: 4, id: ADVISOR_IMPERIAL}, parameter: ADVISOR_IMPERIAL})
	    advisor_ratings  :  menu_item({text:{group: 4, id: ADVISOR_RATINGS}, parameter: ADVISOR_RATINGS})
	    advisor_trade    :  menu_item({text:{group: 4, id: ADVISOR_TRADE}, parameter: ADVISOR_TRADE})
	    advisor_population: menu_item({text:{group: 4, id: ADVISOR_POPULATION}, parameter: ADVISOR_POPULATION})
	    advisor_health   :  menu_item({text:{group: 4, id: ADVISOR_HEALTH}, parameter: ADVISOR_HEALTH})
	    advisor_education:  menu_item({text:{group: 4, id: ADVISOR_EDUCATION}, parameter: ADVISOR_EDUCATION})
	    advisor_entertainment: menu_item({text:{group: 4, id: ADVISOR_ENTERTAINMENT}, parameter: ADVISOR_ENTERTAINMENT})
	    advisor_religion :  menu_item({text:{group: 4, id: ADVISOR_RELIGION}, parameter: ADVISOR_RELIGION})
	    advisor_financial:  menu_item({text:{group: 4, id: ADVISOR_FINANCIAL}, parameter: ADVISOR_FINANCIAL})
	    advisor_chief    :  menu_item({text:{group: 4, id: ADVISOR_CHIEF}, parameter: ADVISOR_CHIEF})
	}

	debug {
		floods 			: menu_item({text: "", parameter: e_debug_show_floods})
 		properties		: menu_item({text: "", parameter: e_debug_show_properties})
 		show_console    : menu_item({text: "", parameter: e_debug_show_console})
 		make_screenshot : menu_item({text: "", parameter: e_debug_make_screenshot})
 		make_full_screenshot : menu_item({text: "", parameter: e_debug_make_full_screenshot})
 		write_video     : menu_item({text: "", parameter: e_debug_write_video})
	}

	debug_render {
	    buildings 		: menu_item({text:"xxx Buildings", parameter:e_debug_render_building})
	}

	ui {
		background 		: dummy({size:[sw(0), 30], fill_width: true})
		date            : link({pos:[0, 2], margin:{right: -110}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 63] })
		population   	: link({pos:[0, 2], margin:{right: -310}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 62] })
		funds        	: link({pos:[0, 2], margin:{right: -440}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 61] })
	}
}
