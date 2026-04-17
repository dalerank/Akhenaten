log_info("akhenaten: ui advisor population started")

function advisor_population_draw_graph_button(elm, kind, title_elm) {
	if (kind === GRAPH_HISTORY) {
		advisor_population_draw_history_graph_button(elm, title_elm)
	} else if (kind === GRAPH_CENSUS) {
		advisor_population_draw_census_graph_button(elm, title_elm)
	} else {
		advisor_population_draw_society_graph_button(elm, title_elm)
	}
}

[es=(advisor_population_window, ondraw_big)]
function advisor_population_es_ondraw_big(window) {
	var go = advisor_population_window.graph_order
    var elm = window[window.active_id]

    if (go === GRAPH_HISTORY) {
		advisor_population_draw_history_graph(elm, window.big_text)
	} else if (go === GRAPH_CENSUS) {
		advisor_population_draw_census_graph(elm, window.big_text)
	} else {
		advisor_population_draw_society_graph(elm, window.big_text)
	}
}

[es=(advisor_population_window, ondraw_top)]
function advisor_population_es_ondraw_top(window) {
	var go = advisor_population_window.graph_order
    var elm = window[window.active_id]
	advisor_population_draw_graph_button(elm, (go + 1) % 3, window.top_text)
}

[es=(advisor_population_window, ondraw_bottom)]
function advisor_population_es_ondraw_bot(window) {
	var go = advisor_population_window.graph_order
    var elm = window[window.active_id]
	advisor_population_draw_graph_button(elm, (go + 2) % 3, window.bot_text)
}

[es=(advisor_population_window, init)]
function advisor_population_on_init(window) {
	window.population.text = __loc("#TR_ADVISOR_TOTAL_POPULATION") + " "+ String(city.population)
	advisor_population_window._info_text_graph_order = -1
    window.title.text = __loc(55, advisor_population_window.graph_order)
	window.housing.text = "#TR_HEADER_HOUSING"
}

function advisor_population_on_housing_button() {
	ui.show_advisor(ADVISOR_HOUSING)
}

function advisor_population_on_next_graph() {
	advisor_population_window.graph_order++
	advisor_population_window.graph_order %= 3
}

function advisor_population_on_prev_graph() {
	advisor_population_window.graph_order--
	if (advisor_population_window.graph_order < 0) {
		advisor_population_window.graph_order = 2
	}
}

function advisor_population_percent_in_workforce_value() {
	var cur = city.population_stats.current
	if (!cur) {
		return 0
	}
	if (game_features.get("gameplay_change_fixed_workers")) {
		return 38
	}
	var wa = city.labor.workers_available
	return (100 * wa / cur) | 0
}

[es=(advisor_population_window, ui_draw_foreground)]
function advisor_population_window_ui_draw_foreground(window) {
	var go = advisor_population_window.graph_order
	if (advisor_population_window._info_text_graph_order === go) {
		return
	}
	advisor_population_window._info_text_graph_order = go
	if (go === GRAPH_CENSUS) {
		advisor_population_print_census_info(window)
	} else if (go === GRAPH_SOCIETY) {
		advisor_population_print_society_info(window)
	} else {
		advisor_population_print_history_info(window)
	}
}

[es=advisor_window]
advisor_population_window = {
	advisor: ADVISOR_POPULATION
	graph_order: 0

	ui: {
		background   : outer_panel({size:[40, 27] })
		advisor_icon : image({pack:PACK_GENERAL, id:128, offset:5, pos:[10, 10] })
		title        : label({font : FONT_LARGE_BLACK_ON_LIGHT, pos:[60, 17]})
		bgimage      : image({pack : PACK_UNLOADED, id:21, offset:14, pos:[56, 60]})
		population   : label({font : FONT_NORMAL_BLACK_ON_DARK, pos:[450, 25]})
		housing      : text_center({font : FONT_NORMAL_BLACK_ON_DARK, pos:[545, 315]})

		housing_button : image_button({
			pos: [545, 260]
			pack: PACK_GENERAL, id: 29
			composite: true
			border: 3
			tooltip: [68, 106]
			onclick: advisor_population_on_housing_button,
		}),

		top_text     : text({pos:[503, 44], font:FONT_NORMAL_BLACK_ON_DARK})
		next_graph   : button({pos:[503, 61], size:[104, 55], tooltip:[68, 106], ondraw_event: "ondraw_top", onclick: advisor_population_on_next_graph }),

		bot_text     : text({pos:[503, 144], font:FONT_NORMAL_BLACK_ON_DARK}),
		prev_graph   : button({pos:[503, 161], size:[104, 55], tooltip:[68, 106], ondraw_event: "ondraw_bottom", onclick: advisor_population_on_prev_graph }),

		big_text     : label({font : FONT_NORMAL_BLACK_ON_DARK, pos:[60, 44]}),
		big_graph_tx : label({pos:[65, 65], size:[395, 195], ondraw_event: "ondraw_big"}),

        info_lines_list : scrollable_list({
                        pos: [48, 336]
                        size: [34, 5]
                        view_items: 4
                        buttons_size_y: 18
                        buttons_margin_x: 0
                        buttons_margin_y: 4
                        text_padding_x: 0
                        text_padding_y: 0
                        draw_scrollbar_always: false
                        draw_paneling: true
                        onrender_item: advisor_population_info_lines_on_render_item
                    })
	}
}
