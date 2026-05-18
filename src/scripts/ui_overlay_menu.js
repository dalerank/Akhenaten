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
	ui {
		background    : dummy({pos[0, 0], size[155, 200]})
		submenu_image : image({pos[-17, 6], pack:PACK_GENERAL, id:158, enabled:false})
		submenu_item  : dummy({pos[-185, 24], size[160, 20]}) 
	}
}

overlay_menu_widget.show = function() {
	emit event_show_window{ id:"overlay_menu_widget" }
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
}

[es=(overlay_menu_widget, init)]
function overlay_menu_widget_init(window) {
	overlay_menu_widget.close_submenu()
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
	var sub_img = window.submenu_image
	var sub_item = window.submenu_item
	var base_x = 0
	var base_y = 0
	var menus = overlay_menu.menus

	for (var i = 0; i < menus.length; i++) {
		var btn_pos = {x:base_x, y:base_y + i * (cat_size.y + 4)}

		var clicked = __ui_draw_button(__loc(menus[i].title), btn_pos, cat_size, FONT_NORMAL_BLACK_ON_DARK, UiFlags_PanelSmall, "")
		if (clicked) {
			city.current_overlay = menus[i].ids[0]
			overlay_menu_widget.close_submenu()
			window_go_back()
		}

		if (overlay_menu_point_in_rect(__mouse.x - window.pos.x, __mouse.y - window.pos.y, btn_pos.x, btn_pos.y, cat_size.x, cat_size.y)) {
			overlay_menu_widget.open_submenu(i, 1)
		}
	}

	if (overlay_menu_widget.selected_submenu > 0) {
		var menu = overlay_menu.menus[overlay_menu_widget.selected_menu]
		if (menu == undefined || menu.ids == undefined || menu.ids.length <= 1) {
			return
		}

		for (var j = 0; j < menu.ids.length; j++) {
			var sub_x = base_x + sub_item.pos.x
			var sub_y = base_y + sub_item.pos.y * (j + overlay_menu_widget.selected_menu)
			
			var sub_text = overlay_menu_overlay_title(menu.ids[j])
			var clicked = __ui_draw_button(sub_text, [sub_x, sub_y], [sub_item.size.x, sub_item.size.y], FONT_NORMAL_BLACK_ON_DARK, UiFlags_PanelSmall, "")
			if (clicked) {			
				city.current_overlay = menu.ids[j]		
				overlay_menu_widget.close_submenu()
				window_go_back()
				return
			}
		}
	}
}