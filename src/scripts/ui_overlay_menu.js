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
				OVERLAY_ARCHITECT_REACH,
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
				OVERLAY_BREWERY,
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

function overlay_menu_overlay_title(overlay_id) {
	return __city_get_overlay_title(overlay_id)
}

function overlay_menu_point_in_rect(mx, my, x, y, w, h) {
	return mx >= x && mx < x + w && my >= y && my < y + h
}

[es=modal_window]
overlay_menu_widget {
	pos [sw(0)-355, 40]
	allow_rmb_goback: true
	selected_menu: 0
	selected_submenu: 0
	keep_submenu_open: 0
	submenu_focus_time: 0
	submenu_close_ms: 500
	ui {
		background    : dummy({pos[0, 0], size[155, 200]})
		submenu_image : image({pos[-17, 6], pack:PACK_GENERAL, id:158, enabled:false})
		submenu_item  : dummy({pos[-185, 24], size[160, 20]}) 
	}
}

overlay_menu_widget.button_menu_item = function(index) {
	var menu = overlay_menu.menus[index]
	if (!menu) {
		return
	}

	if (this.keep_submenu_open && this.selected_submenu == index) {
		this.close_submenu()
		return
	}

	this.open_submenu(index, 1)
}

overlay_menu_widget.close_submenu = function() {
	this.keep_submenu_open = 0
	this.selected_menu = 0
	this.selected_submenu = 0
}

overlay_menu_widget.open_submenu = function(index, keep_open) {
	this.keep_submenu_open = keep_open
	this.selected_menu = index
	this.selected_submenu = index
	this.submenu_focus_time = __game_time_millis()
}

[es=(overlay_menu_widget, init)]
function overlay_menu_widget_init(window) {
	overlay_menu_widget.close_submenu()
	overlay_menu_widget.submenu_focus_time = __game_time_millis()
}

[es=(overlay_menu_widget, go_back)]
function overlay_menu_widget_go_back(window) {
	overlay_menu_widget.close_submenu()
	window_go_back()
}

[es=(overlay_menu_widget, ui_draw_foreground)]
function overlay_menu_widget_ui_draw_foreground(window) {
	__ui_window_city_draw_panels()
	__ui_widget_sidebar_city_draw_foreground()
	__ui_window_city_draw()

	var cat_size = {x:160, y:20}
	var sub_item = window.submenu_item
	var base_x = 0
	var base_y = 0
	var menus = overlay_menu.menus
	var mx = __mouse.x - window.pos.x
	var my = __mouse.y - window.pos.y
	var menu_focus = false
	var submenu_focus = false

	for (var i = 0; i < menus.length; i++) {
		var btn_pos = {x:base_x, y:base_y + i * (cat_size.y + 4)}

		var clicked = ui.button({ text: __loc(menus[i].title), pos: btn_pos, size: cat_size, font: FONT_NORMAL_BLACK_ON_DARK, flags: UiFlags_PanelSmall })
		if (clicked == ui.button_clicked) {
			city.current_overlay = menus[i].ids[0]
			overlay_menu_widget.close_submenu()
			window_go_back()
		}

		if (overlay_menu_point_in_rect(mx, my, btn_pos.x, btn_pos.y, cat_size.x, cat_size.y)) {
			menu_focus = true
			if (menus[i].ids != undefined && menus[i].ids.length > 1) {
				overlay_menu_widget.open_submenu(i, 0)
			} else {
				overlay_menu_widget.close_submenu()
			}
		}
	}

	if (overlay_menu_widget.selected_submenu > 0) {
		var menu = overlay_menu.menus[overlay_menu_widget.selected_menu]
		if (menu != undefined && menu.ids != undefined && menu.ids.length > 1) {
			for (var j = 0; j < menu.ids.length; j++) {
				var sub_x = base_x + sub_item.pos.x
				var sub_y = base_y + sub_item.pos.y * (j + overlay_menu_widget.selected_menu)

				if (overlay_menu_point_in_rect(mx, my, sub_x, sub_y, sub_item.size.x, sub_item.size.y)) {
					submenu_focus = true
				}

				var sub_text = overlay_menu_overlay_title(menu.ids[j])
				var clicked = ui.button({ text: sub_text, pos: [sub_x, sub_y], size: sub_item.size, font: FONT_NORMAL_BLACK_ON_DARK, flags: UiFlags_PanelSmall })
				if (clicked == ui.button_clicked) {
					city.current_overlay = menu.ids[j]
					overlay_menu_widget.close_submenu()
					window_go_back()
					return
				}
			}
		}
	}

	if (!overlay_menu_widget.keep_submenu_open) {
		if (menu_focus || submenu_focus) {
			overlay_menu_widget.submenu_focus_time = __game_time_millis()
		} else if (overlay_menu_widget.selected_submenu > 0
			&& __game_time_millis() - overlay_menu_widget.submenu_focus_time > overlay_menu_widget.submenu_close_ms) {
			overlay_menu_widget.close_submenu()
		}
	}
}