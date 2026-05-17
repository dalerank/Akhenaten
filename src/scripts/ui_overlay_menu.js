log_info("akhenaten: ui overlay menu started")

overlay_menu {
	menus [
		{
			title: "#overlay_menu_normal"
			ids[OVERLAY_NONE]		
		}

		{
			title: "#overlay_menu_water"
			ids[OVERLAY_WATER]
		}

		{
			title: "#overlay_menu_risks"
			ids[ 
			    OVERLAY_FIRE,
				OVERLAY_DAMAGE,
				OVERLAY_MALARIA_RISK,
				OVERLAY_CRIME,
				OVERLAY_CRIMINAL,
				OVERLAY_NATIVE,
				OVERLAY_PROBLEMS,
				OVERLAY_LABOR,
				OVERLAY_ROUTING
	        ]
	    }

	    {
	    	title: "#overlay_menu_entertainment"
	    	ids[
	    		OVERLAY_ENTERTAINMENT,
				OVERLAY_BOOTH,
				OVERLAY_BANDSTAND,
				OVERLAY_PAVILION,
				OVERLAY_SENET_HOUSE,
	    	]
	    }

	    {
	    	title: "#overlay_menu_education"
	    	ids[
	    		OVERLAY_EDUCATION,
			    OVERLAY_SCRIBAL_SCHOOL,
			    OVERLAY_LIBRARY,
			    OVERLAY_ACADEMY,
	    	]
	    }

	    {
	    	title: "#overlay_menu_health"
	    	ids[
	    	    OVERLAY_HEALTH,
				OVERLAY_APOTHECARY,
				OVERLAY_PHYSICIAN,
				OVERLAY_DENTIST,
				OVERLAY_MORTUARY,
				// OVERLAY_DISEASE
				// OVERLAY_INFECTED_HOUSING
				// OVERLAY_MALARIA
	    	]
	    }

	    {
	    	title: "#overlay_menu_administration"
	    	ids[
	    		OVERLAY_TAX_INCOME,
			    OVERLAY_BAZAAR_ACCESS,
			    OVERLAY_DESIRABILITY,
			    OVERLAY_FERTILITY,
			    OVERLAY_COUTHOUSE,
			    OVERLAY_FOOD_STOCKS,
			    OVERLAY_LABOR_ACCESS,
			    // OVERLAY_LABOR
			    // OVERLAY_ADMINISTRATION_PROBLEMS
			    // OVERLAY_WATER_CROSSINGS
			    // OVERLAY_EMPTY_HOUSING
			    // OVERLAY_MAGISTRATE
	    	]
	    }

	    {
	    	title: "#overlay_menu_religion"
	    	ids[
	    		OVERLAY_RELIGION,
			    OVERLAY_RELIGION_OSIRIS,
			    OVERLAY_RELIGION_RA,
			    OVERLAY_RELIGION_PTAH,
			    OVERLAY_RELIGION_SETH,
			    OVERLAY_RELIGION_BAST,
	    	]
	    }

	    {
	    	title: "#overlay_menu_food"
	    	ids[
	    		// OVERLAY_GRAIN
	    		// OVERLAY_CHICKPEAS
				// OVERLAY_POMEGRANATES
				// OVERLAY_FIGS
				// OVERLAY_MEAT
				// OVERLAY_GAME
				// OVERLAY_POTTERY
				// OVERLAY_JEWELRY
				// OVERLAY_LINEN
				// OVERLAY_BEER
	    	]
	    }

	    {
	    	title: "#overlay_menu_other"
	    	ids[
				// OVERLAY_IRRIGATION
				// OVERLAY_CITY_DEFENSES
				// OVERLAY_HIDE_CLIFFS
	    	]
	    }
	]
}

overlay_menu_widget {
	pos [-85, 20]
	selected_menu: 0
	selected_submenu: 0
	keep_submenu_open: 0
	ui {
		background : dummy({})
		category_item : dummy({pos[0, 24], size[160, 20]})
		submenu_image : image({pos[-17, 6], pack:PACK_GENERAL, id:158, enabled:false})
		submenu_item  : dummy({pos[-185, 24], size[160, 20]}) 
	}
}

function overlay_menu_ids_count(menu) {
	if (!menu || menu.ids === undefined) {
		return 0
	}
	if (menu.ids.length !== undefined) {
		return menu.ids.length
	}
	return 1
}

function overlay_menu_id_at(menu, index) {
	if (menu.ids.length !== undefined) {
		return menu.ids[index]
	}
	return menu.ids
}

function overlay_menu_overlay_config(overlay_id) {
	for (var i = 0; i < overlays.length; i++) {
		if (overlays[i].id === overlay_id) {
			return overlays[i]
		}
	}
	return null
}

function overlay_menu_overlay_title(overlay_id) {
	var cfg = overlay_menu_overlay_config(overlay_id)
	if (!cfg || !cfg.title) {
		return "unknown"
	}
	return __loc(cfg.title)
}

function overlay_menu_open_submenu(window, index, keep_open) {
	window.keep_submenu_open = keep_open
	window.selected_menu = index
	window.selected_submenu = index
}

function overlay_menu_close_submenu(window) {
	window.keep_submenu_open = 0
	window.selected_menu = 0
	window.selected_submenu = 0
}

function overlay_menu_button_menu_item(window, index) {
	var menu = overlay_menu.menus[index]
	if (!menu) {
		return
	}

	if (window.selected_submenu === 0 || overlay_menu_ids_count(menu) <= 1) {
		city.current_overlay = overlay_menu_id_at(menu, 0)
		overlay_menu_close_submenu(window)
		ui.window_city_show()
		return
	}

	if (window.keep_submenu_open && window.selected_submenu === index) {
		overlay_menu_close_submenu(window)
		return
	}

	overlay_menu_open_submenu(window, index, 1)
}

function overlay_menu_button_submenu_item(window, index) {
	var menu = overlay_menu.menus[window.selected_submenu]
	if (!menu) {
		return
	}

	var overlay = overlay_menu_id_at(menu, index)
	if (overlay) {
		city.current_overlay = overlay
	}

	overlay_menu_close_submenu(window)
	ui.window_city_show()
}

function overlay_menu_point_in_rect(mx, my, x, y, w, h) {
	return mx >= x && mx < x + w && my >= y && my < y + h
}

function overlay_menu_draw_button(text, pos, size) {
	return __ui_draw_button(text, pos, size, FONT_NORMAL_BLACK_ON_DARK, UiFlags_PanelSmall, "")
}

[es=(overlay_menu_widget, init)]
function overlay_menu_widget_init(window) {
	window.selected_menu = 0
	window.selected_submenu = 0
	window.keep_submenu_open = 0
}

[es=(overlay_menu_widget, ui_draw_foreground)]
function overlay_menu_widget_ui_draw_foreground(window) {
	__ui_window_city_draw_panels()
	__ui_widget_sidebar_city_draw_foreground()
	__ui_window_city_draw()

	var x_offset = __ui_overlay_menu_viewport_offset_x()
	var cat = window.category_item
	var sub_img = window.submenu_image
	var sub_item = window.submenu_item
	var base_x = window.pos.x + x_offset
	var base_y = window.pos.y
	var menus = overlay_menu.menus

	for (var i = 0; i < menus.length; i++) {
		var btn_x = base_x
		var btn_y = base_y + cat.pos.y * i
		var btn_pos = [btn_x, btn_y]
		var btn_size = [cat.size.x, cat.size.y]

		if (overlay_menu_draw_button(__loc(menus[i].title), btn_pos, btn_size)) {
			overlay_menu_button_menu_item(window, i)
		}

		if (overlay_menu_point_in_rect(__mouse.x, __mouse.y, btn_x, btn_y, btn_size[0], btn_size[1])) {
			overlay_menu_open_submenu(window, i, 1)
		}
	}

	if (window.selected_submenu > 0) {
		var sel_menu = overlay_menu.menus[window.selected_menu]
		if (sel_menu && overlay_menu_ids_count(sel_menu) > 1) {
			var img = get_image(sub_img)
			if (img) {
				ui.image(img, [base_x + sub_img.pos.x, base_y + sub_img.pos.y + sub_item.pos.y * window.selected_menu])
			}

			for (var j = 0; j < overlay_menu_ids_count(sel_menu); j++) {
				var sub_x = base_x + sub_item.pos.x
				var sub_y = base_y + sub_item.pos.y * (j + window.selected_menu)
				var sub_text = overlay_menu_overlay_title(overlay_menu_id_at(sel_menu, j))
				if (overlay_menu_draw_button(sub_text, [sub_x, sub_y], [sub_item.size.x, sub_item.size.y])) {
					overlay_menu_button_submenu_item(window, j)
				}
			}
		}
	}
}