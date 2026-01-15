log_info("akhenaten: ui top menu config started")

function top_menu_autosave_options_text(p1, p2) { return __loc(19, game.monthly_autosave ? 51 : 52) }
function top_menu_autosave_options_toggle(p1, p2) { game.monthly_autosave = !game.monthly_autosave }

function top_menu_tooltip_text(p1, p2) { return __loc(3, game.tooltips_mode + 2) }
function top_menu_tooltip_toggle(p1, p2) { game.tooltips_mode = (game.tooltips_mode + 1) % 3 }

function top_menu_warnings_text(p1, p2) { return __loc(3, game.warnings ? 6 : 5) }
function top_menu_warnings_toggle(p1, p2) { game.warnings = !game.warnings }

function top_menu_cities_old_text(p1, p2) { return __loc(2, game_features.gameui_empire_city_old_names ? 7 : 8) }
function top_menu_cities_old_toggle(p1, p2) { game_features.gameui_empire_city_old_names = !game_features.gameui_empire_city_old_names }

function top_menu_open_advisor(advisor, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	window_advisors_show_advisor(advisor)
}

function top_menu_show_console(p1, p2) { window_show_cheat_console(true) }
function top_menu_make_fullscreenshot(p1, p2) { game.make_screenshot(1) }
function top_menu_make_screenshot(p1, p2) { game.make_screenshot(0) }
function top_menu_debug_properties_text(p1, p2) { return game.debug_properties ? "Properties ON" : "Properties OFF" }
function top_menu_debug_write_video_text(p1, p2) { return game.debug_write_video ? "Write Video ON" : "Write Video OFF" }

function top_menu_debug_buildings_text(p1, p2) { return game.debug_render_mode == e_debug_render_building ? "Buildings ON" : "Buildings OFF" }
function top_menu_debug_buildings_toggle(p1, p2) { 
	var mode = game.debug_render_mode;
	mode = (mode == e_debug_render_building) ? e_debug_render_none : e_debug_render_building;
	game.debug_render_mode = mode;
}

function top_menu_date_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_date_display", -1) }
function top_menu_population_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_population_display", -1) }
function top_menu_funds_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_money_display_window", -1) }
function widget_top_menu_show_speed_options(p1, p2) { 
	widget_top_menu_clear_state()
	window_speed_options_show()
}

top_menu_widget {
	offset [10, 6]
	item_height : 20
	background { pack:PACK_GENERAL, id:121, offset:8 }
	sidebar_offset : 158
	spacing : 16
	offset_rotate_basic : 200

	headers {
		file 			: menu_header({text {group:7, id:0}, tooltip[68, 51] })
		options			: menu_header({text {group:2, id:0}, tooltip[68, 52] })
		help		   	: menu_header({text {group:3, id:0}, tooltip[68, 53] })
		advisors  		: menu_header({text {group:4, id:0}, onclick: top_menu_open_advisor })
		debug		   	: menu_header({text: "Debug" })
		debug_render  	: menu_header({text: "Render" })
	}

	file {
		new_game     	: menu_item({text {group:1, id:1}, onclick: __widget_top_menu_new_game })
		replay_map   	: menu_item({text {group:1, id:2}, onclick: __widget_top_menu_replay_map })
		load_game	    : menu_item({text {group:1, id:3}, onclick: __widget_top_menu_load_map })
		save_game	    : menu_item({text {group:1, id:4}, onclick: __widget_top_menu_save_map })
		delete_game	  	: menu_item({text {group:1, id:6}, onclick: __widget_top_menu_delete_map })
		exit_game	    : menu_item({text {group:1, id:5}, onclick: __widget_top_menu_exit_game })
	}

	options {
		display_options	: menu_item({text {group:2, id:1}, onclick: __widget_top_menu_display_options })
		sound_options  	: menu_item({text {group:2, id:2}, onclick: __widget_top_menu_sound_options })
		speed_options  	: menu_item({text {group:2, id:3}, onclick: widget_top_menu_show_speed_options })
		difficulty_options: menu_item({ text {group:2, id:6}, onclick: __widget_top_menu_difficulty_options })

		cities_options  : menu_item({text {group:2, id:7}
			                         textfn: top_menu_cities_old_text
									 onclick: top_menu_cities_old_toggle })

		autosave_options: menu_item({text {group:19, id:51}
				                     textfn: top_menu_autosave_options_text
									 onclick: top_menu_autosave_options_toggle })
									 
		hotkeys_options : menu_item({text: "Hotkeys options", onclick: __widget_top_menu_hotkeys_options })
		enhanced_options: menu_item({text: "Enhanced options", onclick: __widget_top_menu_features })
	}

	help {
		help 			: menu_item({text {group:3, id:1}, onclick: __widget_top_menu_show_help })

		mouse 			: menu_item({text {group:3, id:2}
			                         textfn: top_menu_tooltip_text
									 onclick: top_menu_tooltip_toggle })

		warnings 		: menu_item({text {group:3, id:5}
			                         textfn: top_menu_warnings_text
									 onclick: top_menu_warnings_toggle })

		about 			: menu_item({text: {group:3, id:7}, onclick: __widget_top_menu_show_about })
	}

	advisors {
		advisor_labor 	 :  menu_item({text{group: 4, id: ADVISOR_LABOR}, parameter: ADVISOR_LABOR})
	    advisor_military :  menu_item({text{group: 4, id: ADVISOR_MILITARY}, parameter: ADVISOR_MILITARY})
	    advisor_imperial :  menu_item({text{group: 4, id: ADVISOR_IMPERIAL}, parameter: ADVISOR_IMPERIAL})
	    advisor_ratings  :  menu_item({text{group: 4, id: ADVISOR_RATINGS}, parameter: ADVISOR_RATINGS})
	    advisor_trade    :  menu_item({text{group: 4, id: ADVISOR_TRADE}, parameter: ADVISOR_TRADE})
	    advisor_population: menu_item({text{group: 4, id: ADVISOR_POPULATION}, parameter: ADVISOR_POPULATION})
	    advisor_health   :  menu_item({text{group: 4, id: ADVISOR_HEALTH}, parameter: ADVISOR_HEALTH})
	    advisor_education:  menu_item({text{group: 4, id: ADVISOR_EDUCATION}, parameter: ADVISOR_EDUCATION})
	    advisor_entertainment: menu_item({text{group: 4, id: ADVISOR_ENTERTAINMENT}, parameter: ADVISOR_ENTERTAINMENT})
	    advisor_religion :  menu_item({text{group: 4, id: ADVISOR_RELIGION}, parameter: ADVISOR_RELIGION})
	    advisor_financial:  menu_item({text{group: 4, id: ADVISOR_FINANCIAL}, parameter: ADVISOR_FINANCIAL})
	    advisor_chief    :  menu_item({text{group: 4, id: ADVISOR_CHIEF}, parameter: ADVISOR_CHIEF})
	}

	debug {
 		properties		: menu_item({textfn: top_menu_debug_properties_text
									 onclick: __widget_top_menu_toggle_debug_properties })

 		make_screenshot : menu_item({text: "Make full screenshot", onclick: top_menu_make_fullscreenshot })
 		make_full_screenshot : menu_item({text: "Make screenshot", onclick: top_menu_make_screenshot })

 		write_video     : menu_item({textfn: top_menu_debug_write_video_text
			                         onclick: game.toggle_video_writing })
 		
		show_console    : menu_item({text: "Cheat console", onclick: top_menu_show_console })
	}

	debug_render {
	    buildings 		: menu_item({textfn: top_menu_debug_buildings_text
									 onclick: top_menu_debug_buildings_toggle })
	}

	ui {
		background 		: dummy({size[sw(0), 30], fill_width: true})
		date            : link({margin{right: -110}, size[117, 20]
							    onrclick: top_menu_date_explanation
								tooltip[68, 63] })

		population   	: link({margin{right: -310}, size[117, 20]
							    onrclick: top_menu_population_explanation
								tooltip[68, 62] })

		funds        	: link({margin{right: -440}, size[117, 20]
							    onrclick: top_menu_funds_explanation
			                    tooltip[68, 61] })
	}
}

[event=top_menu_widget_init]
function top_menu_widget_open_submenu(window) {
	window.new_game.enabled = !game_features.gameui_hide_new_game_top_menu
	window.display_options.enabled = !game.screen.is_fullscreen_only
}

[event=top_menu_widget_draw]
function top_menu_widget_draw(window) {
	var treasury = city.finance.treasury;
	
    window.funds.font = treasury >= 0 ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_BLUE
    window.funds.text_color = treasury < 0 ? COLOR_FONT_RED : COLOR_WHITE
    window.funds.text = __loc(6, 0) + " " + treasury
	
	window.date.text = top_menu_widget.date_str
	window.population.text = top_menu_widget.population_str
}

[event=event_population_changed]
function top_menu_update_population_text(ev) {
	top_menu_widget.population_str = __loc(6, 1) + " " + ev.value;
}

[event=event_advance_day]
function top_menu_update_date_text(ev) {
	var month_str = __loc(25, ev.month);
    if (ev.year >= 0) {
    	top_menu_widget.date_str = game.locale_year_before_ad
			 							? _format("{0} {1} AD", month_str, ev.year)
			                            : _format("{0} AD {1}", month_str, ev.year);

    }  else {	
		top_menu_widget.date_str = _format("{0} {1} BC", month_str, -ev.year);
	}
}