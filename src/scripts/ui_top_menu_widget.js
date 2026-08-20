log_info("akhenaten: ui top menu config started")

top_menu_state = {
	open_sub_menu: ""
	focus_menu_id: ""
	focus_sub_menu_id: ""
	date_str: ""
	population_str: ""
	item_clicked: 0
	rotate_hover: 0
	headers_right: 0
	status_shift: 0
	header_layout: {}
	menu_size: {}
	item_enabled: {}
}

function top_menu_clear_state() {
	top_menu_state.open_sub_menu = ""
	top_menu_state.focus_menu_id = ""
	top_menu_state.focus_sub_menu_id = ""
	top_menu_state.item_clicked = 0
}

function top_menu_dismiss() {
	var open = ui.window_is("top_menu_submenu")
	top_menu_clear_state()
	if (open) {
		window_go_back()
	}
}

function widget_top_menu_clear_state() {
	top_menu_clear_state()
}

function top_menu_resolve_text(text) {
	if (text === undefined || text === null) {
		return ""
	}
	if (typeof text === "string") {
		if (text.indexOf("${loc.") === 0) {
			return __loc("#" + text.substring(6, text.length - 1))
		}
		return __loc(text)
	}
	if (typeof text === "object" && text.group !== undefined) {
		return __loc(text.group, text.id)
	}
	return ""
}

function top_menu_item_text(item) {
	if (!item) {
		return ""
	}
	if (item.textfn) {
		return item.textfn(item.parameter)
	}
	return top_menu_resolve_text(item.text)
}

function top_menu_find_menu(menu_id) {
	var menus = top_menu_widget.menus
	if (!menus) {
		return null
	}
	for (var i = 0; i < menus.length; i++) {
		if (menus[i].id == menu_id) {
			return menus[i]
		}
	}
	return null
}

function top_menu_find_item(menu, item_id) {
	if (!menu || !menu.items) {
		return null
	}
	for (var i = 0; i < menu.items.length; i++) {
		if (menu.items[i].id == item_id) {
			return menu.items[i]
		}
	}
	return null
}

function top_menu_item_enabled_key(menu_id, item_id) {
	return menu_id + "/" + item_id
}

function top_menu_is_item_enabled(menu, item) {
	if (!item || item.hidden) {
		return false
	}
	var flag = top_menu_state.item_enabled[top_menu_item_enabled_key(menu.id, item.id)]
	if (flag === false) {
		return false
	}
	return true
}

function top_menu_set_item_enabled(menu_id, item_id, enabled) {
	top_menu_state.item_enabled[top_menu_item_enabled_key(menu_id, item_id)] = !!enabled
}

function top_menu_apply_item_enabled() {
	top_menu_set_item_enabled("file", "new_game", !game_features.gameui_hide_new_game_top_menu)
	top_menu_set_item_enabled("options", "display_options", !screen.is_fullscreen_only)
}

function top_menu_header_layout(menu_id) {
	return top_menu_state.header_layout[menu_id]
}

function top_menu_set_header_layout(menu_id, x_start, x_end) {
	top_menu_state.header_layout[menu_id] = { x_start: x_start, x_end: x_end }
}

function top_menu_menu_size(menu_id) {
	return top_menu_state.menu_size[menu_id]
}

function top_menu_header_at_mouse() {
	var menus = top_menu_widget.menus
	if (!menus) {
		return ""
	}
	var mx = __mouse.x
	var my = __mouse.y
	var y0 = top_menu_widget.offset.y
	var y1 = y0 + top_menu_widget.header_hit_height
	if (my < y0 || my >= y1) {
		return ""
	}
	for (var i = 0; i < menus.length; i++) {
		var layout = top_menu_header_layout(menus[i].id)
		if (layout && layout.x_start <= mx && layout.x_end > mx) {
			return menus[i].id
		}
	}
	return ""
}

function top_menu_open_submenu(menu_id) {
	top_menu_state.open_sub_menu = menu_id
	top_menu_apply_item_enabled()
	ui.set_tooltip("")
	if (!ui.window_is("top_menu_submenu")) {
		window_show_by_id("top_menu_submenu")
	}
}

function top_menu_activate_item(menu, item) {
	if (!menu || !top_menu_is_item_enabled(menu, item)) {
		return
	}
	top_menu_state.item_clicked = 1
}

function top_menu_calc_menu_size(menu) {
	var max_width = 0
	var height_pixels = top_menu_widget.item_height
	var items = menu.items || []
	for (var i = 0; i < items.length; i++) {
		var item = items[i]
		if (!top_menu_is_item_enabled(menu, item)) {
			continue
		}
		var text = top_menu_item_text(item)
		var width_pixels = __ui_text_width(text, FONT_NORMAL_BLACK_ON_LIGHT)
		if (width_pixels > max_width) {
			max_width = width_pixels
		}
		height_pixels += top_menu_widget.item_height
	}
	var blocks = ((max_width + 8) / 16 | 0) + 1
	if (blocks < 10) {
		blocks = 10
	}
	var height_blocks = (height_pixels / 16) | 0
	if (height_blocks < 1) {
		height_blocks = 1
	}
	top_menu_state.menu_size[menu.id] = {
		width_blocks: blocks,
		height_blocks: height_blocks
	}
}

top_menu_widget {
	offset {x: 10, y: 6}
	submenu_offset {x: 8, y: -8}
	item_height : 20
	height : 30
	header_hit_height : 12
	background { pack:PACK_GENERAL, id:121, offset:8 }
	sidebar_offset : 158
	spacing : 16
	rotate_x : -170
	rotate_img { pack:PACK_GENERAL, id:136, offset:72 }
	status_header_gap : 16
	status_date { right: -110, w: 117, h: 20 }
	status_pop { right: -310, w: 117, h: 20 }
	status_funds { right: -440, w: 117, h: 20 }
	status_rot_l { right: -174, w: 14, h: 24 }
	status_rot_m { right: -160, w: 14, h: 24 }
	status_rot_r { right: -144, w: 14, h: 24 }

	menus [
		{
			id: "file"
			text: "#top_menu_file"
			tooltip: "#top_menu_file_tooltip"
			items [
				{ id: "new_game", text: "#top_menu_new_game" }
				{ id: "replay_map", text: "#replay_mission" }
				{ id: "load_game", text: "#top_menu_load_game" }
				{ id: "save_game", text: "#top_menu_save_game" }
				{ id: "delete_game", text: "#top_menu_delete_game" }
				{ id: "exit_game", text: "#top_menu_exit_game" }
			]
		}
		{
			id: "options"
			text: "#top_menu_options"
			tooltip: "#top_menu_options_tooltip"
			items [
				{ id: "display_options", text: "#top_menu_display_settings" }
				{ id: "sound_options", text: "#top_menu_sound_settings" }
				{ id: "speed_options", text: "#top_menu_speed_settings" }
				{ id: "pyramid_speedup", textfn: top_menu_pyramid_speedup_text }
				{ id: "difficulty_options", text: "#top_menu_difficulty" }
				{ id: "popup_messages", text: "#top_menu_popup_messages" }
				{ id: "cities_options", textfn: top_menu_cities_old_text }
				{ id: "autosave_options", textfn: top_menu_autosave_options_text }
				{ id: "autosave_slots", textfn: top_menu_autosave_slots_text }
				{ id: "hotkeys_options", text: "#TR_BUTTON_CONFIGURE_HOTKEYS" }
				{ id: "enhanced_options", text: "#TR_CONFIG_TITLE" }
			]
		}
		{
			id: "help"
			text: "#top_menu_help"
			tooltip: "#top_menu_help_tooltip"
			items [
				{ id: "help", text: "#top_menu_help_item" }
				{ id: "mouse", textfn: top_menu_tooltip_text }
				{ id: "warnings", textfn: top_menu_warnings_text }
				{ id: "about", text: "#top_menu_about" }
			]
		}
		{
			id: "advisors"
			text: "#top_menu_overseers"
			tooltip: "#top_menu_overseers_tooltip"
			onclick_event: "open_advisor"
			items [
				{ id: "advisor_labor", text: "#top_menu_advisor_labor", parameter: ADVISOR_LABOR }
				{ id: "advisor_military", text: "#top_menu_advisor_military", parameter: ADVISOR_MILITARY }
				{ id: "advisor_imperial", text: "#top_menu_advisor_imperial", parameter: ADVISOR_IMPERIAL }
				{ id: "advisor_ratings", text: "#top_menu_advisor_ratings", parameter: ADVISOR_RATINGS }
				{ id: "advisor_trade", text: "#top_menu_advisor_trade", parameter: ADVISOR_TRADE }
				{ id: "advisor_population", text: "#top_menu_advisor_population", parameter: ADVISOR_POPULATION }
				{ id: "advisor_health", text: "#top_menu_advisor_health", parameter: ADVISOR_HEALTH }
				{ id: "advisor_education", text: "#top_menu_advisor_education", parameter: ADVISOR_EDUCATION }
				{ id: "advisor_entertainment", text: "#top_menu_advisor_entertainment", parameter: ADVISOR_ENTERTAINMENT }
				{ id: "advisor_religion", text: "#top_menu_advisor_religion", parameter: ADVISOR_RELIGION }
				{ id: "advisor_financial", text: "#top_menu_advisor_financial", parameter: ADVISOR_FINANCIAL }
				{ id: "advisor_chief", text: "#top_menu_advisor_chief", parameter: ADVISOR_CHIEF }
			]
		}
		{
			id: "debug"
			text: "#top_menu_debug"
			items [
				{ id: "properties", textfn: top_menu_debug_properties_text }
				{ id: "terrain_paint", textfn: top_menu_debug_terrain_paint_text }
				{ id: "make_screenshot", text: "#TR_HOTKEY_SAVE_SCREENSHOT" }
				{ id: "make_full_screenshot", text: "#TR_HOTKEY_SAVE_CITY_SCREENSHOT" }
				{ id: "write_video", textfn: top_menu_debug_write_video_text }
				{ id: "show_console", text: "#top_menu_cheat_console" }
				{ id: "js_debugger", textfn: top_menu_js_debugger_text }
			]
		}
		{
			id: "debug_render"
			text: "#top_menu_debug_render"
			items [
				{ id: "buildings", textfn: top_menu_debug_buildings_text }
			]
		}
	]
}

[es=modal_window]
top_menu_submenu {
	allow_rmb_goback: true
	ui {
		background : dummy({size[sw(0), sh(0)]})
	}
}

[es=(top_menu_submenu, init)]
function top_menu_submenu_init(window) {
	top_menu_apply_item_enabled()
	top_menu_state.item_clicked = 0
}

[es=(top_menu_submenu, go_back)]
function top_menu_submenu_go_back(window) {
	top_menu_dismiss()
}

[es=(top_menu_submenu, draw_background)]
function top_menu_submenu_draw_background(window) {
	__ui_window_city_draw_panels()
	top_menu_draw()
	__ui_window_city_draw()
	__ui_widget_sidebar_city_draw_foreground()
}

[es=(top_menu_submenu, ui_draw_foreground)]
function top_menu_submenu_ui_draw_foreground(window) {
	var menu = top_menu_find_menu(top_menu_state.open_sub_menu)
	if (!menu) {
		return
	}

	top_menu_calc_menu_size(menu)
	var layout = top_menu_header_layout(menu.id)
	var size = top_menu_menu_size(menu.id)
	if (!layout || !size) {
		return
	}

	__ui_unbordered_panel(layout.x_start, top_menu_widget.height, size.width_blocks, size.height_blocks)

	var sub = top_menu_widget.submenu_offset
	var y_offset = top_menu_widget.height + top_menu_widget.offset.y * 2 + sub.y
	var items = menu.items || []
	var focus_id = ""

	for (var i = 0; i < items.length; i++) {
		var item = items[i]
		if (!top_menu_is_item_enabled(menu, item)) {
			continue
		}

		var text = top_menu_item_text(item)
		var item_x = layout.x_start + sub.x
		var btn_pos = { x: layout.x_start, y: y_offset - 2 }
		var btn_size = { x: 16 * size.width_blocks, y: 19 }
		var hovered = (__mouse.x >= btn_pos.x && __mouse.x < btn_pos.x + btn_size.x
			&& __mouse.y >= btn_pos.y && __mouse.y < btn_pos.y + btn_size.y)
		if (hovered) {
			focus_id = item.id
		}

		var font = (item.id == focus_id) ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT
		var clicked = ui.button({
			text: text,
			pos: [item_x, y_offset],
			size: [btn_size.x - sub.x, top_menu_widget.item_height],
			font: font,
			border: false,
			body: false,
			flags: UiFlags_AlignYCentered,
			onclick_event: item.onclick_event || menu.onclick_event || item.id,
			param1: item.parameter | 0
		})
		if (clicked == ui.button_clicked) {
			top_menu_activate_item(menu, item)
			return
		}

		y_offset += top_menu_widget.item_height
	}

	top_menu_state.focus_sub_menu_id = focus_id
}

[es=(top_menu_submenu, ui_handle_mouse)]
function top_menu_submenu_ui_handle_mouse(window) {
	if (__input_go_back_requested()) {
		top_menu_dismiss()
		return
	}

	var menu_id = top_menu_header_at_mouse()
	if (menu_id) {
		top_menu_state.focus_menu_id = menu_id
		if (menu_id != top_menu_state.open_sub_menu) {
			top_menu_state.open_sub_menu = menu_id
			top_menu_apply_item_enabled()
		}
	}

	if (!__mouse.left.went_up) {
		return
	}

	if (top_menu_state.item_clicked) {
		top_menu_state.item_clicked = 0
		return
	}

	top_menu_dismiss()
}
