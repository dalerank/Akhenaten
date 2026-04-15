log_info("akhenaten: ui advisor population started")

var GRAPH_HISTORY = 0
var GRAPH_CENSUS = 1
var GRAPH_SOCIETY = 2

// For graph_order k: [big, top, bot, info_panel] graph kinds
var advisor_population_graph_layout = [
	[GRAPH_HISTORY, GRAPH_CENSUS, GRAPH_SOCIETY, GRAPH_HISTORY],
	[GRAPH_CENSUS, GRAPH_SOCIETY, GRAPH_HISTORY, GRAPH_CENSUS],
	[GRAPH_SOCIETY, GRAPH_HISTORY, GRAPH_CENSUS, GRAPH_SOCIETY],
]

function advisor_population_elem_xy(el) {
	var p = el.pos
	if (p[0] !== undefined) {
		return [p[0], p[1]]
	}
	return [p.x, p.y]
}

function advisor_population_v2_add(p, dx, dy) {
	return [p[0] + dx, p[1] + dy]
}

function advisor_population_clamp(v, lo, hi) {
	return Math.max(lo, Math.min(hi, v))
}

function advisor_population_history_y_axis(max_value) {
	if (max_value <= 100) { return [100, -1] }
	if (max_value <= 200) { return [200, 0] }
	if (max_value <= 400) { return [400, 1] }
	if (max_value <= 800) { return [800, 2] }
	if (max_value <= 1600) { return [1600, 3] }
	if (max_value <= 3200) { return [3200, 4] }
	if (max_value <= 6400) { return [6400, 5] }
	if (max_value <= 12800) { return [12800, 6] }
	if (max_value <= 25600) { return [25600, 7] }
	return [51200, 8]
}

function advisor_population_min_max_month_year(max_months) {
	var month_count = city.population_stats.monthly_count()
	if (month_count > max_months) {
		var end_month = __game_simtime_month() - 1
		var end_year = game.simtime_year
		if (end_month < 0) {
			end_year -= 1
		}
		var start_month = 11 - (max_months % 12)
		var start_year = end_year - ((max_months / 12) | 0)
		return { start: { month: start_month, year: start_year }, end: { month: end_month, year: end_year } }
	}
	var start_year = scenario.start_year
	var start_month = 0
	var end_month = (max_months + start_month) % 12
	var end_year = (((max_months + start_month) / 12) | 0) + start_year
	return { start: { month: start_month, year: start_year }, end: { month: end_month, year: end_year } }
}

function advisor_population_draw_history_graph(window, fullSize, bodyId, titleId) {
	var thresholds = [
		{ count: 20, max: 20, wline: 20, graphid: 1 },
		{ count: 40, max: 40, wline: 10, graphid: 2 },
		{ count: 100, max: 100, wline: 4, graphid: 3 },
		{ count: 200, max: 200, wline: 2, graphid: 4 },
		{ count: 2147483647, max: 400, wline: 2, graphid: 4 },
	]
	var month_count = city.population_stats.monthly_count()
	var it = thresholds[0]
	var i
	for (i = 0; i < thresholds.length; i++) {
		if (month_count <= thresholds[i].count) {
			it = thresholds[i]
			break
		}
	}
	var max_months = fullSize ? it.max : advisor_population_clamp(it.max, 20, 200)
	var wline = it.wline
	var graphid = it.graphid

	var max_value = 0
	var m
	for (m = 0; m < max_months; m++) {
		var value = city.population_stats.at_month(max_months, m)
		if (value > max_value) {
			max_value = value
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_max = ypx[0]
	var y_shift = ypx[1]

	var gh = advisor_population_graph_history
	var bpos = advisor_population_elem_xy(window[bodyId])
	var bx = bpos[0]
	var by = bpos[1]
	var yo = gh.y_axis_offset
	var y_axis_base = [bx + yo[0], by + yo[1]]

	if (fullSize) {
		window[titleId].text = __loc(55, 6)
		ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
		ui.label_ex(String((y_max / 2) | 0), [y_axis_base[0], y_axis_base[1] + (gh.y_axis_height / 2 | 0)], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
		ui.label_ex("0", [y_axis_base[0], y_axis_base[1] + gh.y_axis_height], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)

		var range = advisor_population_min_max_month_year(max_months)
		var left = __loc(25, range.start.month) + " " + range.start.year
		var right = __loc(25, range.end.month) + " " + range.end.year
		ui.label_ex(left, advisor_population_v2_add(bpos, gh.x_axis_offset[0], gh.x_axis_offset[1]), FONT_SMALL_PLAIN, 0, 0)
		ui.label_ex(right, advisor_population_v2_add(bpos, gh.x_axis_offset[0] + gh.x_axis_width, gh.x_axis_offset[1]), FONT_SMALL_PLAIN, 0, 0)
	} else {
		window[titleId].text = __loc(55, 3)
	}

	if (fullSize) {
		ui.set_clip_rectangle([0, 0], [640, by + 200])
		for (m = 0; m < max_months; m++) {
			var pop = city.population_stats.at_month(max_months, m)
			var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
			if (val > 0) {
				if (max_months >= 200) {
					ui.fill_rect([bx + m, by + 200 - val], [1, val], COLOR_RED)
				} else {
					var imgBar = get_image({ pack: PACK_GENERAL, id: 157, offset: graphid - 1 })
					ui.image(imgBar, [bx + wline * m, by + 200 - val])
				}
			}
		}
		ui.reset_clip_rectangle()
	} else {
		y_shift += 2
		for (m = 0; m < max_months; m++) {
			var val2 = city.population_stats.at_month(max_months, m) >> y_shift
			if (val2 > 0) {
				if (max_months === 20) {
					ui.fill_rect([bx + m, by + 50 - val2], [4, val2 + 1], COLOR_RED)
				} else {
					ui.fill_rect([bx + m, by + 50 - val2], [1, val2], COLOR_RED)
				}
			}
		}
	}
}

function advisor_population_draw_graph_slot(window, kind, fullSize, bodyId, titleId) {
	if (kind === GRAPH_HISTORY) {
		advisor_population_draw_history_graph(window, fullSize, bodyId, titleId)
	} else {
		__advisor_population_draw_graph(kind, fullSize, bodyId, titleId)
	}
}

advisor_population_graph_census = {
	y_axis_offset  : [-56, 0]
	y_axis_label_w : 60
	y_axis_height  : 200

	x_axis_offset  : [-20, 210]
	x_axis_width   : 170
}

advisor_population_graph_history = {
	y_axis_offset  : [-56, 0]
	y_axis_label_w : 60
	y_axis_height  : 200

	x_axis_offset  : [-20, 215]
	x_axis_width   : 170
}

advisor_population_society_history = {
	y_axis_offset  : [-56, 0]
	y_axis_label_w : 60
	y_axis_height  : 200

	x_axis_offset  : [-20, 215]
	x_axis_width   : 170
}

[es=(advisor_population_window, draw_background)]
function advisor_population_window_draw_background(window) {
	window.title.text = __loc(55, advisor_population_window.graph_order)
	window.housing.text = "#TR_HEADER_HOUSING"
	window.housing_button.onclick = function () {
		ui.show_advisor(ADVISOR_HOUSING)
	}
	window.next_graph.onclick = function () {
		advisor_population_window.graph_order++
		advisor_population_window.graph_order %= 3
	}
	window.prev_graph.onclick = function () {
		advisor_population_window.graph_order--
		if (advisor_population_window.graph_order < 0) {
			advisor_population_window.graph_order = 2
		}
	}
}

[es=(advisor_population_window, ui_draw_foreground)]
function advisor_population_window_ui_draw_foreground(window) {
	var row = advisor_population_graph_layout[advisor_population_window.graph_order]
	var big = row[0]
	var top = row[1]
	var bot = row[2]
	var info = row[3]
	advisor_population_draw_graph_slot(window, big, 1, "big_graph_tx", "big_text")
	advisor_population_draw_graph_slot(window, top, 0, "next_graph_tx", "top_text")
	advisor_population_draw_graph_slot(window, bot, 0, "prev_graph_tx", "bot_text")
	__advisor_population_print_info(info)
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
		population   : label({font : FONT_NORMAL_BLACK_ON_DARK, text:"${TR_ADVISOR_TOTAL_POPULATION} ${city.population}", pos:[450, 25]})
		housing      : text_center({font : FONT_NORMAL_BLACK_ON_DARK, pos:[545, 315]})

		housing_button : button({pos:[540, 260], size:[64, 50], tooltip:[68, 106]
			ui: {
				tx   : image({pos: [3, 18], pack: PACK_GENERAL, id: 29, isometric:true })
			}
		}),

		top_text     : text({pos:[503, 44], font:FONT_NORMAL_BLACK_ON_DARK})
		next_graph   : button({pos:[503, 61], size:[104, 55]
			ui: {
				next_graph_tx : image({pos:[5, 0]}),
			}
		}),

		bot_text     : text({pos:[503, 144], font:FONT_NORMAL_BLACK_ON_DARK}),
		prev_graph   : button({pos:[503, 161], size:[104, 55],
			ui: {
				prev_graph_tx : image({pos:[5, 0]}),
			}
		}),

		big_text     : label({font : FONT_NORMAL_BLACK_ON_DARK, pos:[60, 44]}),
		big_graph_tx : label({pos:[65, 62]}),

		graph_bar_1 : image({ pack:PACK_GENERAL, id:157, pos:[-2000, 0] }),
		graph_bar_2 : image({ pack:PACK_GENERAL, id:157, offset:1, pos:[-2000, 0] }),
		graph_bar_3 : image({ pack:PACK_GENERAL, id:157, offset:2, pos:[-2000, 0] }),
		graph_bar_4 : image({ pack:PACK_GENERAL, id:157, offset:3, pos:[-2000, 0] }),

		inner_panel  : inner_panel({pos:[48, 336], size:[34, 5],
			ui: {
				img1     : image({pack: PACK_GENERAL, id: 158, pos:[8, 8]}),
				text1    : text({pos:[35, 8], font: FONT_NORMAL_WHITE_ON_DARK}),
				img2     : image({pack: PACK_GENERAL, id: 158, pos:[8, 26]}),
				text2    : text({pos:[35, 26], font: FONT_NORMAL_WHITE_ON_DARK}),
				img3     : image({pack: PACK_GENERAL, id: 158, pos:[8, 44]}),
				text3    : text({pos:[35, 44], font: FONT_NORMAL_WHITE_ON_DARK, multiline:true, wrap:px(32)}),
				img4     : image({pack: PACK_GENERAL, id: 158, pos:[8, 62]}),
				text4    : text({pos:[35, 62], font: FONT_NORMAL_WHITE_ON_DARK}),
			}
		}),
	}
}
