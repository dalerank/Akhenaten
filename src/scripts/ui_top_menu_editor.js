log_info("akhenaten: ui top menu editor started")

top_menu_editor_state = {
	open_sub_menu: ""
	focus_menu_id: ""
	focus_sub_menu_id: ""
	item_clicked: 0
	header_layout: {}
	menu_size: {}
}

function top_menu_editor_clear_state() {
	top_menu_editor_state.open_sub_menu = ""
	top_menu_editor_state.focus_menu_id = ""
	top_menu_editor_state.focus_sub_menu_id = ""
	top_menu_editor_state.item_clicked = 0
}

function top_menu_editor_dismiss() {
	var open = ui.window_is("top_menu_editor_submenu")
	top_menu_editor_clear_state()
	if (open) {
		window_go_back()
	}
}

function top_menu_editor_resolve_text(text) {
	if (text === undefined || text === null) {
		return ""
	}
	if (typeof text === "string") {
		return __loc(text)
	}
	if (typeof text === "object" && text.group !== undefined) {
		return __loc(text.group, text.id)
	}
	return ""
}

function top_menu_editor_item_text(item) {
	if (!item) {
		return ""
	}
	return top_menu_editor_resolve_text(item.text)
}

function top_menu_editor_find_menu(menu_id) {
	var menus = top_menu_editor_widget.menus
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

function top_menu_editor_set_header_layout(menu_id, x_start, x_end) {
	top_menu_editor_state.header_layout[menu_id] = { x_start: x_start, x_end: x_end }
}

function top_menu_editor_header_layout(menu_id) {
	return top_menu_editor_state.header_layout[menu_id]
}

function top_menu_editor_menu_size(menu_id) {
	return top_menu_editor_state.menu_size[menu_id]
}

function top_menu_editor_header_at_mouse() {
	var menus = top_menu_editor_widget.menus
	if (!menus) {
		return ""
	}
	var mx = __mouse.x
	var my = __mouse.y
	var y0 = 0
	var y1 = top_menu_editor_widget.height
	if (my < y0 || my >= y1) {
		return ""
	}
	for (var i = 0; i < menus.length; i++) {
		var layout = top_menu_editor_header_layout(menus[i].id)
		if (layout && layout.x_start <= mx && layout.x_end > mx) {
			return menus[i].id
		}
	}
	return ""
}

function top_menu_editor_open_submenu(menu_id) {
	top_menu_editor_state.open_sub_menu = menu_id
	ui.set_tooltip("")
	if (!ui.window_is("top_menu_editor_submenu")) {
		window_show_by_id("top_menu_editor_submenu")
	}
}

function top_menu_editor_activate_item(menu, item) {
	if (!menu || !item || item.hidden) {
		return
	}
	top_menu_editor_state.item_clicked = 1
}

function top_menu_editor_calc_menu_size(menu) {
	var max_width = 0
	var height_pixels = top_menu_editor_widget.item_height
	var items = menu.items || []
	for (var i = 0; i < items.length; i++) {
		var item = items[i]
		if (item.hidden) {
			continue
		}
		var text = top_menu_editor_item_text(item)
		var width_pixels = __ui_text_width(text, FONT_NORMAL_BLACK_ON_LIGHT)
		if (width_pixels > max_width) {
			max_width = width_pixels
		}
		height_pixels += top_menu_editor_widget.item_height
	}
	var blocks = ((max_width + 8) / 16 | 0) + 1
	if (blocks < 10) {
		blocks = 10
	}
	var height_blocks = (height_pixels / 16) | 0
	if (height_blocks < 1) {
		height_blocks = 1
	}
	top_menu_editor_state.menu_size[menu.id] = {
		width_blocks: blocks,
		height_blocks: height_blocks
	}
}

[es=(top_menu_editor_submenu, new_map)]
function top_menu_editor_new_map(ev) {
	top_menu_editor_dismiss()
	__ui_window_select_list_show(50, 50, 33, 7, top_menu_editor_map_size_selected)
}

function top_menu_editor_map_size_selected(size) {
	top_menu_editor_clear_state()
	if (size >= 0 && size <= 5) {
		__game_editor_create_scenario(size)
		ui.window_editor_map_show()
	} else {
		window_go_back()
	}
}

[es=(top_menu_editor_submenu, load_map)]
function top_menu_editor_load_map(ev) {
	top_menu_editor_dismiss()
	ui.window_editor_map_show()
	window_show_by_id("file_dialog_load_scenario")
}

[es=(top_menu_editor_submenu, save_map)]
function top_menu_editor_save_map(ev) {
	top_menu_editor_dismiss()
	ui.window_editor_map_show()
	window_show_by_id("file_dialog_save_scenario")
}

[es=(top_menu_editor_submenu, exit)]
function top_menu_editor_exit(ev) {
	top_menu_editor_dismiss()
	ui.window_editor_map_show()

	if (__scenario_is_saved()) {
		game.exit_editor()
		return
	}

	ui.show_yesno("#popup_dialog_quit_without_saving",
		function() { game.exit_editor() },
		function() { ui.window_editor_map_show() }
	)
}

[es=(top_menu_editor_submenu, help)]
function top_menu_editor_show_help(ev) {
	top_menu_editor_dismiss()
	__ui_window_message_dialog_editor("message_dialog_editor_help")
}

[es=(top_menu_editor_submenu, about)]
function top_menu_editor_show_about(ev) {
	top_menu_editor_dismiss()
	__ui_window_message_dialog_editor("message_dialog_editor_about")
}

[es=(top_menu_editor_submenu, herds)]
function top_menu_editor_reset_herds(ev) {
	__scenario_editor_clear_predator_herd_points()
	top_menu_editor_dismiss()
}

[es=(top_menu_editor_submenu, fish)]
function top_menu_editor_reset_fish(ev) {
	__scenario_editor_clear_fishing_points()
	top_menu_editor_dismiss()
}

[es=(top_menu_editor_submenu, invasions)]
function top_menu_editor_reset_invasions(ev) {
	__scenario_editor_clear_invasion_points()
	top_menu_editor_dismiss()
}

[es=(top_menu_editor_submenu, choose)]
function top_menu_editor_empire_choose(ev) {
	top_menu_editor_dismiss()
	__ui_window_editor_empire_show()
}

function top_menu_editor_open_window(window_id) {
	top_menu_editor_dismiss()
	ui.window_editor_map_show()
	window_show_by_id(window_id)
}

[es=(top_menu_editor_submenu, sound)]
function top_menu_editor_sound_options(ev) { top_menu_editor_open_window("sound_options_window") }

[es=(top_menu_editor_submenu, speed)]
function top_menu_editor_speed_options(ev) { top_menu_editor_open_window("speed_options_window") }

top_menu_editor_widget {
	offset {x: 10, y: 6}
	submenu_offset {x: 8, y: 2}
	item_height : 20
	height : 30
	background { pack:PACK_GENERAL, id:11 }
	spacing : 16

	menus [
		{
			id: "file"
			text: "#top_menu_file"
			items [
				{ id: "new_map", text: "#top_menu_editor_new_map" }
				{ id: "load_map", text: "#top_menu_editor_load_map" }
				{ id: "save_map", text: "#top_menu_editor_save_map" }
				{ id: "exit", text: "#top_menu_editor_exit" }
			]
		}
		{
			id: "options"
			text: "#top_menu_options"
			items [
				{ id: "sound", text: "#top_menu_sound_settings" }
				{ id: "speed", text: "#top_menu_speed_settings" }
			]
		}
		{
			id: "help"
			text: "#top_menu_help"
			items [
				{ id: "help", text: "#top_menu_help_item" }
				{ id: "about", text: "#top_menu_about" }
			]
		}
		{
			id: "resets"
			text: "#top_menu_editor_resets"
			items [
				{ id: "herds", text: "#top_menu_editor_clear_herds" }
				{ id: "fish", text: "#top_menu_editor_clear_fish" }
				{ id: "invasions", text: "#top_menu_editor_clear_invasions" }
			]
		}
		{
			id: "empire"
			text: "#top_menu_editor_empire"
			items [
				{ id: "choose", text: "#top_menu_editor_empire_choose" }
			]
		}
	]
}

[es=modal_window]
top_menu_editor_submenu {
	allow_rmb_goback: true
	ui {
		background : dummy({size[sw(0), sh(0)]})
	}
}

[es=(top_menu_editor_submenu, init)]
function top_menu_editor_submenu_init(window) {
	top_menu_editor_state.item_clicked = 0
}

[es=(top_menu_editor_submenu, go_back)]
function top_menu_editor_submenu_go_back(window) {
	top_menu_editor_dismiss()
}

[es=(top_menu_editor_submenu, draw_background)]
function top_menu_editor_submenu_draw_background(window) {
	__ui_window_editor_map_draw_all()
}

[es=(top_menu_editor_submenu, ui_draw_foreground)]
function top_menu_editor_submenu_ui_draw_foreground(window) {
	var menu = top_menu_editor_find_menu(top_menu_editor_state.open_sub_menu)
	if (!menu) {
		return
	}

	top_menu_editor_calc_menu_size(menu)
	var layout = top_menu_editor_header_layout(menu.id)
	var size = top_menu_editor_menu_size(menu.id)
	if (!layout || !size) {
		return
	}

	__ui_unbordered_panel(layout.x_start, top_menu_editor_widget.height, size.width_blocks, size.height_blocks)

	var sub = top_menu_editor_widget.submenu_offset
	var y_offset = top_menu_editor_widget.height + sub.y
	var items = menu.items || []
	var focus_id = ""

	for (var i = 0; i < items.length; i++) {
		var item = items[i]
		if (item.hidden) {
			continue
		}

		var text = top_menu_editor_item_text(item)
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
			size: [btn_size.x - sub.x, top_menu_editor_widget.item_height],
			font: font,
			border: false,
			body: false,
			flags: UiFlags_AlignYCentered,
			onclick_event: item.onclick_event || menu.onclick_event || item.id,
			param1: item.parameter | 0
		})
		if (clicked == ui.button_clicked) {
			top_menu_editor_activate_item(menu, item)
			return
		}

		y_offset += top_menu_editor_widget.item_height
	}

	top_menu_editor_state.focus_sub_menu_id = focus_id
}

[es=(top_menu_editor_submenu, ui_handle_mouse)]
function top_menu_editor_submenu_ui_handle_mouse(window) {
	if (__input_go_back_requested()) {
		top_menu_editor_clear_state()
		return
	}

	var menu_id = top_menu_editor_header_at_mouse()
	if (menu_id) {
		top_menu_editor_state.focus_menu_id = menu_id
		if (menu_id != top_menu_editor_state.open_sub_menu) {
			top_menu_editor_state.open_sub_menu = menu_id
		}
	}

	if (!__mouse.left.went_up) {
		return
	}

	if (top_menu_editor_state.item_clicked) {
		top_menu_editor_state.item_clicked = 0
		return
	}

	top_menu_editor_dismiss()
}

function top_menu_editor_draw_background() {
	var block_img = get_image(top_menu_editor_widget.background)
	if (!block_img) {
		return
	}

	var block_width = 24
	var screen_w = screen.width
	var base_tid = block_img.tid
	for (var i = 0; i * block_width < screen_w; i++) {
		ui.draw_texture({ x: i * block_width, y: 0 }, base_tid + (i % 8))
	}
}

function top_menu_editor_draw_headers() {
	var menus = top_menu_editor_widget.menus
	if (!menus) {
		return
	}

	var cur_x = top_menu_editor_widget.offset.x
	var cur_y = top_menu_editor_widget.offset.y
	var spacing = top_menu_editor_widget.spacing
	var mx = __mouse.x
	var my = __mouse.y
	var in_bar = (my >= 0 && my < top_menu_editor_widget.height)
	var focus_id = ""
	if (top_menu_editor_state.open_sub_menu) {
		focus_id = top_menu_editor_state.open_sub_menu
	}

	for (var i = 0; i < menus.length; i++) {
		var menu = menus[i]
		var text = top_menu_editor_resolve_text(menu.text)
		var width = __ui_text_width(text, FONT_NORMAL_BLACK_ON_LIGHT)
		var x_start = cur_x
		var x_end = cur_x + width
		top_menu_editor_set_header_layout(menu.id, x_start, x_end)

		var is_hovered
		if (focus_id) {
			is_hovered = (menu.id == focus_id)
		} else {
			is_hovered = in_bar && x_start <= mx && x_end > mx
			if (is_hovered) {
				focus_id = menu.id
			}
		}

		var font = is_hovered ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT
		ui.label(text, { x: cur_x, y: cur_y }, font)

		cur_x += width + spacing
	}

	if (!top_menu_editor_state.open_sub_menu) {
		top_menu_editor_state.focus_menu_id = focus_id
	}
}

[es=top_menu_editor_draw]
function top_menu_editor_draw(ev) {
	if (top_menu_editor_state.open_sub_menu && !ui.window_is("top_menu_editor_submenu")) {
		top_menu_editor_clear_state()
	}
	top_menu_editor_draw_background()
	top_menu_editor_draw_headers()
}

function top_menu_editor_handle_input() {
	if (top_menu_editor_state.open_sub_menu && !ui.window_is("top_menu_editor_submenu")) {
		top_menu_editor_clear_state()
	}

	var menu_id = top_menu_editor_header_at_mouse()
	top_menu_editor_state.focus_menu_id = menu_id
	if (menu_id && __mouse.left.went_up) {
		top_menu_editor_open_submenu(menu_id)
		return 1
	}
	return 0
}

[es=top_menu_editor_handle_input]
function top_menu_editor_handle_input_es(ev) {
	if (!top_menu_editor_handle_input()) {
		__ui_widget_sidebar_editor_handle_mouse()
	}
}
