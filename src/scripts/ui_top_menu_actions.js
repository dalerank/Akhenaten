log_info("akhenaten: ui top menu actions started")

function top_menu_autosave_options_text(p1, p2) {
	return __loc(game_features.gameopt_monthly_autosave ? "#monthly_autosave_on" : "#monthly_autosave_off")
}

[es=(top_menu_submenu, autosave_options)]
function top_menu_autosave_options_toggle(ev) { game_features.gameopt_monthly_autosave = !game_features.gameopt_monthly_autosave }

function top_menu_autosave_slots_clamp(n) {
	n = Math.round(n)
	if (n < 1) return 1
	if (n > 10) return 10
	return n
}

function top_menu_autosave_slots_text(p1, p2) {
	var n = top_menu_autosave_slots_clamp(game_features.gameopt_autosave_slots)
	return fmt("#autosave_slots: ${n}", { n: n })
}

[es=(top_menu_submenu, autosave_slots)]
function top_menu_autosave_slots_cycle(ev) {
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

function top_menu_tooltip_text(p1, p2) {
	var keys = ["#top_menu_mouse_help_off", "#top_menu_mouse_help_some", "#top_menu_mouse_help_full"]
	return __loc(keys[game_features.gameopt_tooltips_mode] || keys[0])
}

[es=(top_menu_submenu, mouse)]
function top_menu_tooltip_toggle(ev) { game_features.gameopt_tooltips_mode = (game_features.gameopt_tooltips_mode + 1) % 3 }

function top_menu_warnings_text(p1, p2) {
	return __loc(game_features.gameopt_warnings ? "#top_menu_warnings_on" : "#top_menu_warnings_off")
}

[es=(top_menu_submenu, warnings)]
function top_menu_warnings_toggle(ev) { game_features.gameopt_warnings = !game_features.gameopt_warnings }

function top_menu_cities_old_text(p1, p2) {
	return __loc(game_features.gameui_empire_city_old_names ? "#top_menu_cities_egyptian" : "#top_menu_cities_classical")
}

[es=(top_menu_submenu, cities_options)]
function top_menu_cities_old_toggle(ev) { game_features.gameui_empire_city_old_names = !game_features.gameui_empire_city_old_names }

function top_menu_pyramid_speedup_text(p1, p2) {
	return __loc(game_features.gameopt_pyramid_speedup ? "#top_menu_pyramid_speedup_on" : "#top_menu_pyramid_speedup_off")
}

[es=(top_menu_submenu, pyramid_speedup)]
function top_menu_pyramid_speedup_toggle(ev) { game_features.gameopt_pyramid_speedup = !game_features.gameopt_pyramid_speedup }

[es=(top_menu_submenu, open_advisor)]
function top_menu_open_advisor(ev) {
	top_menu_dismiss()
	window_advisors_show_advisor(ev.param1)
}

[es=(top_menu_submenu, show_console)]
function top_menu_show_console(ev) {
	top_menu_dismiss()
	window_show_cheat_console(true)
}

function top_menu_js_debugger_text(p1, p2) {
	return __loc(__js_debugger_is_running()
		? "#top_menu_js_debugger_on"
		: "#top_menu_js_debugger_off")
}

[es=(top_menu_submenu, js_debugger)]
function top_menu_js_debugger_toggle(ev) {
	top_menu_dismiss()
	if (__js_debugger_is_running())
		__js_debugger_stop()
	else
		__js_debugger_start(4711)
}

[es=(top_menu_submenu, make_full_screenshot)]
function top_menu_make_fullscreenshot(ev) {
	top_menu_dismiss()
	__game_save_screenshot(SCREENSHOT_FULL_CITY)
}

[es=(top_menu_submenu, make_screenshot)]
function top_menu_make_screenshot(ev) {
	top_menu_dismiss()
	__game_save_screenshot(SCREENSHOT_DISPLAY)
}

function top_menu_debug_properties_text(p1, p2) {
	return __loc(game.debug_properties ? "#top_menu_properties_on" : "#top_menu_properties_off")
}

[es=(top_menu_submenu, properties)]
function top_menu_debug_properties_toggle(ev) {
	game.debug_properties = !game.debug_properties
	top_menu_dismiss()
}

function top_menu_debug_terrain_paint_text(p1, p2) {
	return __loc(game.debug_terrain_paint ? "#top_menu_terrain_paint_on" : "#top_menu_terrain_paint_off")
}

[es=(top_menu_submenu, terrain_paint)]
function top_menu_debug_terrain_paint_toggle(ev) {
	game.debug_terrain_paint = !game.debug_terrain_paint
	if (!game.debug_terrain_paint) {
		__editor_tool_deactivate()
	}
	top_menu_dismiss()
}

function top_menu_debug_write_video_text(p1, p2) {
	return __loc(video_capture.active ? "#top_menu_write_video_on" : "#top_menu_write_video_off")
}

[es=(top_menu_submenu, write_video)]
function top_menu_write_video(ev) {
	video_capture.toggle()
}

function top_menu_debug_buildings_text(p1, p2) {
	return __loc(game.debug_render_mode_name == "building" ? "#top_menu_buildings_on" : "#top_menu_buildings_off")
}

[es=(top_menu_submenu, buildings)]
function top_menu_debug_buildings_toggle(ev) {
	game.debug_render_mode_name = (game.debug_render_mode_name == "building") ? "" : "building"
}

function top_menu_date_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_date_display", -1) }
function top_menu_population_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_population_display", -1) }
function top_menu_funds_explanation(p1, p2) { ui.window_message_dialog_show("message_game_control_money_display_window", -1) }

[es=(top_menu_submenu, new_game)]
function top_menu_new_game(ev) {
	top_menu_dismiss()
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

[es=(top_menu_submenu, replay_map)]
function top_menu_replay_map(ev) {
	top_menu_dismiss()
	ui.show_yesno("#replay_mission",
		function() {
			__ui_city_planner_reset()
			var is_custom = scenario.scmode != e_scenario_normal
			if (is_custom) {
				__game_load_savegame("autosave_replay.svx")
				ui.window_city_show()
			} else {
				top_menu_clear_state()
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

[es=(top_menu_submenu, load_game)]
function top_menu_load_map(ev) {
	if (!game_allows_midgame_load()) {
		top_menu_dismiss()
		game_toast_ironwill_load_blocked()
		return
	}
	top_menu_dismiss()
	__ui_city_planner_reset()
	ui.window_city_show()
	window_show_by_id("file_dialog_load")
}

[es=(top_menu_submenu, save_game)]
function top_menu_save_map(ev) {
	if (!game_allows_player_save()) {
		top_menu_dismiss()
		game_toast_ironwill_save_blocked()
		return
	}
	top_menu_dismiss()
	ui.window_city_show()
	window_show_by_id("file_dialog_save")
}

[es=(top_menu_submenu, delete_game)]
function top_menu_delete_map(ev) {
	top_menu_dismiss()
	ui.window_city_show()
	window_show_by_id("file_dialog_delete")
}

[es=(top_menu_submenu, exit_game)]
function top_menu_exit_game(ev) {
	top_menu_dismiss()
	game_confirm_exit_to_main_menu()
}

function top_menu_open_window(window_id) {
	top_menu_dismiss()
	emit event_show_window{ id: window_id }
}

[es=(top_menu_submenu, display_options)]
function top_menu_display_options(ev) { top_menu_open_window("display_options_window") }

[es=(top_menu_submenu, sound_options)]
function top_menu_sound_options(ev) { top_menu_open_window("sound_options_window") }

[es=(top_menu_submenu, speed_options)]
function top_menu_speed_options(ev) { top_menu_open_window("speed_options_window") }

[es=(top_menu_submenu, difficulty_options)]
function top_menu_difficulty_options(ev) { top_menu_open_window("difficulty_options_window") }

[es=(top_menu_submenu, popup_messages)]
function top_menu_popup_messages(ev) { top_menu_open_window("popup_messages_window") }

[es=(top_menu_submenu, hotkeys_options)]
function top_menu_hotkeys_options(ev) { top_menu_open_window("window_hotkey_config") }

[es=(top_menu_submenu, enhanced_options)]
function top_menu_enhanced_options(ev) { top_menu_open_window("window_features") }

[es=(top_menu_submenu, help)]
function top_menu_show_help(ev) {
	top_menu_dismiss()
	ui.window_message_dialog("message_dialog_help")
}

[es=(top_menu_submenu, about)]
function top_menu_show_about(ev) {
	top_menu_dismiss()
	ui.window_message_dialog("message_dialog_about")
}
