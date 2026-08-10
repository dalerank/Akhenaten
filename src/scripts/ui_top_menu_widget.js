log_info("akhenaten: ui top menu config started")

function top_menu_autosave_options_text(p1, p2) { return __loc(19, game_features.gameopt_monthly_autosave ? 51 : 52) }
function top_menu_autosave_options_toggle(p1, p2) { game_features.gameopt_monthly_autosave = !game_features.gameopt_monthly_autosave }

function top_menu_autosave_slots_clamp(n) {
	n = Math.round(n)
	if (n < 1) return 1
	if (n > 10) return 10
	return n
}

function top_menu_autosave_slots_text(p1, p2) {
	var n = top_menu_autosave_slots_clamp(game_features.gameopt_autosave_slots)
	return __loc("#autosave_slots") + ": " + n
}

function top_menu_autosave_slots_cycle(p1, p2) {
	var cur = top_menu_autosave_slots_clamp(game_features.gameopt_autosave_slots)
	var opts = [1, 3, 5, 10]
	var next = opts[0]
	for (var i = 0; i < opts.length; i++) {
		if (cur === opts[i]) {
			next = opts[(i + 1) % opts.length]
			break
		}
		if (cur < opts[i]) {
			next = opts[i]
			break
		}
	}
	game_features.gameopt_autosave_slots = next
}

function top_menu_tooltip_text(p1, p2) { return __loc(3, game_features.gameopt_tooltips_mode + 2) }
function top_menu_tooltip_toggle(p1, p2) { game_features.gameopt_tooltips_mode = (game_features.gameopt_tooltips_mode + 1) % 3 }

function top_menu_warnings_text(p1, p2) { return __loc(3, game_features.gameopt_warnings ? 6 : 5) }
function top_menu_warnings_toggle(p1, p2) { game_features.gameopt_warnings = !game_features.gameopt_warnings }

function top_menu_cities_old_text(p1, p2) { return __loc(2, game_features.gameui_empire_city_old_names ? 7 : 8) }
function top_menu_cities_old_toggle(p1, p2) { game_features.gameui_empire_city_old_names = !game_features.gameui_empire_city_old_names }

function top_menu_pyramid_speedup_text(p1, p2) { return __loc(2, game_features.gameopt_pyramid_speedup ? 5 : 4) }
function top_menu_pyramid_speedup_toggle(p1, p2) { game_features.gameopt_pyramid_speedup = !game_features.gameopt_pyramid_speedup }

function top_menu_open_advisor(advisor, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	emit event_show_window{ id:advisor }
}

function top_menu_show_console(p1, p2) { window_show_cheat_console(true) }

function top_menu_js_debugger_text(p1, p2) {
	return __js_debugger_is_running()
		? "JS debugger ON"
		: "JS debugger OFF"
}

function top_menu_js_debugger_toggle(p1, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	if (__js_debugger_is_running())
		__js_debugger_stop()
	else
		__js_debugger_start(4711)
}
function top_menu_make_fullscreenshot(p1, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	__game_save_screenshot(SCREENSHOT_FULL_CITY)
}

function top_menu_make_screenshot(p1, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	__game_save_screenshot(SCREENSHOT_DISPLAY)
}
function top_menu_debug_properties_text(p1, p2) { return game.debug_properties ? "Properties ON" : "Properties OFF" }
function top_menu_debug_properties_toggle(p1, p2) {
	game.debug_properties = !game.debug_properties
	widget_top_menu_clear_state()
	window_go_back()
}
function top_menu_debug_terrain_paint_text(p1, p2) { return game.debug_terrain_paint ? "Terrain paint ON" : "Terrain paint OFF" }
function top_menu_debug_terrain_paint_toggle(p1, p2) {
	game.debug_terrain_paint = !game.debug_terrain_paint
	if (!game.debug_terrain_paint) {
		__editor_tool_deactivate()
	}
	widget_top_menu_clear_state()
	window_go_back()
}
function top_menu_debug_write_video_text(p1, p2) { return video_capture.active ? "Write Video ON" : "Write Video OFF" }

function top_menu_debug_buildings_text(p1, p2) { return game.debug_render_mode_name == "building" ? "Buildings ON" : "Buildings OFF" }
function top_menu_debug_buildings_toggle(p1, p2) {
	game.debug_render_mode_name = (game.debug_render_mode_name == "building") ? "" : "building"
}

function top_menu_date_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_date_display", -1) }
function top_menu_population_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_population_display", -1) }
function top_menu_funds_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_money_display_window", -1) }

function top_menu_show_window_by_id(window_id) {
	return function() {
		widget_top_menu_clear_state()
		window_go_back()
		emit event_show_window{ id:window_id }
	}
}

function top_menu_new_game() {
	widget_top_menu_clear_state()
	ui.show_yesno("#popup_dialog_quit",
		function() {
			__ui_city_planner_reset()
			__game_undo_disable()

			game_mission_options_locked = false
			window_show_by_id("window_dinasty_menu")
		},
		function() {
			ui.window_city_show()
		}
	)
}

function top_menu_replay_map() {
	widget_top_menu_clear_state()
	ui.show_yesno("#replay_mission",
		function() {
			__ui_city_planner_reset()
			var is_custom = scenario.scmode != e_scenario_normal
			if (is_custom) {
				__game_load_savegame("autosave_replay.svx")
				ui.window_city_show()
			} else {
				widget_top_menu_clear_state()
				// Replay is not a victory advance — drop dynasty / troop / monument carry.
				city.kingdome.campaign_carry_personal_savings = 0
				city.kingdome.personal_savings = 0
				__campaign_carry_clear()
				__game_load_mission(scenario.campaign_scenario_id, 1)
			}
		},
		function() {
			ui.window_city_show()
		}
	)
}

function top_menu_load_map() {
	if (!game_allows_midgame_load()) {
		widget_top_menu_clear_state()
		game_toast_ironwill_load_blocked()
		return
	}
	widget_top_menu_clear_state()
	__ui_city_planner_reset()
	ui.window_city_show()
	window_show_by_id("file_dialog_load")
}

function top_menu_save_map() {
	if (!game_allows_player_save()) {
		widget_top_menu_clear_state()
		game_toast_ironwill_save_blocked()
		return
	}
	widget_top_menu_clear_state()
	ui.window_city_show()
	window_show_by_id("file_dialog_save")
}

function top_menu_delete_map() {
	widget_top_menu_clear_state()
	ui.window_city_show()
	window_show_by_id("file_dialog_delete")
}

function top_menu_exit_game() {
	widget_top_menu_clear_state()
	game_confirm_exit_to_main_menu()
}

function top_menu_features(p1, p2) {
	window_show_by_id("window_features")
}

function top_menu_show_help(p1, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	ui.window_message_dialog("message_dialog_help")
}

function top_menu_show_about(p1, p2) {
	widget_top_menu_clear_state()
	window_go_back()
	ui.window_message_dialog("message_dialog_about")
}

top_menu_widget {
	offset [10, 6]
	item_height : 20
	background { pack:PACK_GENERAL, id:121, offset:8 }
	sidebar_offset : 158
	spacing : 16

	headers {
		file 			: menu_header({text: "${loc.top_menu_file}", tooltip: "${loc.top_menu_file_tooltip}" })
		options			: menu_header({text: "${loc.top_menu_options}", tooltip: "${loc.top_menu_options_tooltip}" })
		help		   	: menu_header({text: "${loc.top_menu_help}", tooltip: "${loc.top_menu_help_tooltip}" })
		advisors  		: menu_header({text: "${loc.top_menu_overseers}", tooltip: "${loc.top_menu_overseers_tooltip}", onclick: top_menu_open_advisor })
		debug		   	: menu_header({text: "Debug" })
		debug_render  	: menu_header({text: "Render" })
	}

	file {
		new_game     	: menu_item({text {group:1, id:1}, onclick: top_menu_new_game })
		replay_map   	: menu_item({text:"#replay_mission", onclick: top_menu_replay_map })
		load_game	    : menu_item({text {group:1, id:3}, onclick: top_menu_load_map })
		save_game	    : menu_item({text {group:1, id:4}, onclick: top_menu_save_map })
		delete_game	  	: menu_item({text {group:1, id:6}, onclick: top_menu_delete_map })
		exit_game	    : menu_item({text {group:1, id:5}, onclick: top_menu_exit_game })
	}

	options {
		display_options	: menu_item({text {group:2, id:1}, onclick: top_menu_show_window_by_id("display_options_window") })
		sound_options  	: menu_item({text {group:2, id:2}, onclick: top_menu_show_window_by_id("sound_options_window") })
		speed_options  	: menu_item({text {group:2, id:3}, onclick: top_menu_show_window_by_id("speed_options_window") })
		pyramid_speedup : menu_item({textfn: top_menu_pyramid_speedup_text
									 onclick: top_menu_pyramid_speedup_toggle })
		difficulty_options: menu_item({ text {group:2, id:6}, onclick: top_menu_show_window_by_id("difficulty_options_window") })
		popup_messages  : menu_item({text {group:2, id:11}, onclick: top_menu_show_window_by_id("popup_messages_window") })

		cities_options  : menu_item({textfn: top_menu_cities_old_text
									 onclick: top_menu_cities_old_toggle })

		autosave_options: menu_item({textfn: top_menu_autosave_options_text
									 onclick: top_menu_autosave_options_toggle })
		autosave_slots: menu_item({textfn: top_menu_autosave_slots_text
								   onclick: top_menu_autosave_slots_cycle })

		hotkeys_options : menu_item({text: "Hotkeys options", onclick: top_menu_show_window_by_id("window_hotkey_config") })
		enhanced_options: menu_item({text: "Enhanced options", onclick: top_menu_features })
	}

	help {
		help 			: menu_item({text {group:3, id:1}, onclick: top_menu_show_help })

		mouse 			: menu_item({textfn: top_menu_tooltip_text
									 onclick: top_menu_tooltip_toggle })

		warnings 		: menu_item({textfn: top_menu_warnings_text
									 onclick: top_menu_warnings_toggle })

		about 			: menu_item({text: {group:3, id:7}, onclick: top_menu_show_about })
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
									 onclick: top_menu_debug_properties_toggle })

 		terrain_paint	: menu_item({textfn: top_menu_debug_terrain_paint_text
									 onclick: top_menu_debug_terrain_paint_toggle })

 		make_screenshot : menu_item({text: "Make full screenshot", onclick: top_menu_make_fullscreenshot })
 		make_full_screenshot : menu_item({text: "Make screenshot", onclick: top_menu_make_screenshot })

 		write_video     : menu_item({textfn: top_menu_debug_write_video_text
			                         onclick: video_capture.toggle })

		show_console    : menu_item({text: "Cheat console", onclick: top_menu_show_console })

		js_debugger     : menu_item({textfn: top_menu_js_debugger_text
									 onclick: top_menu_js_debugger_toggle })
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

		rotate_left		: link({ margin{right: -174}, size[14, 24]
								 onclick:   function() { emit event_rotate_map{ value: HOTKEY_ROTATE_MAP_LEFT } } })

		rotate_reset	: link({ margin{right: -160}, size[14, 24]
								 onclick:   function() { emit event_rotate_map_reset{ value: 0 } } })

		rotate_right	: link({ margin{right: -144}, size[14, 24],
								 onclick:   function() { emit event_rotate_map{ value: HOTKEY_ROTATE_MAP_RIGHT } } })
	}
}

[es=top_menu_widget_init]
function top_menu_widget_open_submenu(window) {
	window.new_game.enabled = !game_features.gameui_hide_new_game_top_menu
	window.display_options.enabled = !screen.is_fullscreen_only
}

[es=top_menu_widget_background_draw]
function top_menu_widget_background_draw(window) {
	var block_img = get_image(top_menu_widget.background)
    if (!block_img) {
		return
    }

	var want_sidebar_offset = top_menu_widget.sidebar_offset
	var block_width = block_img.width
	var screen_width = screen.width
	var current_sidebar_offset = ui.sidebar.offset_x

	var step = block_width - want_sidebar_offset
	if (step <= 0) {
		return
	}

    for (var x = -(screen_width - current_sidebar_offset); x < screen_width; x += step) {
        ui.draw_texture({ x: x, y: 0 }, block_img.tid)
    }

    ui.draw_texture({ x: current_sidebar_offset - block_width + want_sidebar_offset, y: 0 }, block_img.tid)

	var rotate_hover_state = 0
    if (window.rotate_left.hovered){
		rotate_hover_state = 2
	} else if (window.rotate_reset.hovered){
		rotate_hover_state = 1
	} else if (window.rotate_right.hovered){
		rotate_hover_state = 3
	}
	var rotate_img = get_image({pack:PACK_GENERAL, id:136, offset:72 + rotate_hover_state })
	ui.draw_texture({ x: screen.width - 170, y: 0 }, rotate_img.tid)
}

[es=top_menu_widget_draw]
function top_menu_widget_draw(window) {
	var treasury = city.finance.treasury

    window.funds.font = treasury >= 0 ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_BLUE
    window.funds.text_color = treasury < 0 ? COLOR_FONT_RED : COLOR_WHITE
    window.funds.text = __loc(6, 0) + " " + treasury

	window.date.text = top_menu_widget.date_str
	window.population.text = top_menu_widget.population_str
}

[es=event_population_changed]
function top_menu_update_population_text(ev) {
	top_menu_widget.population_str = __loc(6, 1) + " " + ev.value;
}

[es=event_advance_day]
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