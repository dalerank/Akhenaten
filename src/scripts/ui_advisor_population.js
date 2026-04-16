log_info("akhenaten: ui advisor population started")

var GRAPH_HISTORY = 0
var GRAPH_CENSUS = 1
var GRAPH_SOCIETY = 2
var HOUSE_LEVEL_MAX = 20

// For graph_order k: [big, top, bot, info_panel] graph kinds
var advisor_population_graph_layout = [
	[GRAPH_HISTORY, GRAPH_CENSUS, GRAPH_SOCIETY, GRAPH_HISTORY],
	[GRAPH_CENSUS, GRAPH_SOCIETY, GRAPH_HISTORY, GRAPH_CENSUS],
	[GRAPH_SOCIETY, GRAPH_HISTORY, GRAPH_CENSUS, GRAPH_SOCIETY],
]

function advisor_population_v2_add(p, dx, dy) {
	return [p.x + dx, p.y + dy]
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

function advisor_population_draw_history_graph_button(elm, title_elm) {
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
	var max_months = advisor_population_clamp(it.max, 20, 200)

	var max_value = 0
	var m
	for (m = 0; m < max_months; m++) {
		var value = city.population_stats.at_month(max_months, m)
		if (value > max_value) {
			max_value = value
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_shift = ypx[1]

	title_elm.text = __loc(55, 3)

	var bx = elm.pos.x
	var by = elm.pos.y
	var pad = 4
	var gw = advisor_population_clamp(elm.size.x - pad * 2, 1, 10000)
	var graphH = advisor_population_clamp(elm.size.y - 10, 8, 512)

	y_shift += 2
	var max_bar = 0
	for (m = 0; m < max_months; m++) {
		var t = city.population_stats.at_month(max_months, m) >> y_shift
		if (t > max_bar) {
			max_bar = t
		}
	}
	for (m = 0; m < max_months; m++) {
		var val2 = city.population_stats.at_month(max_months, m) >> y_shift
		if (val2 <= 0) {
			continue
		}
		var h = max_bar > 0 ? Math.max(1, ((val2 * graphH) / max_bar) | 0) : 1
		var x0 = bx + pad + (((m * gw) / max_months) | 0)
		var x1 = bx + pad + ((((m + 1) * gw) / max_months) | 0)
		var bw = Math.max(1, x1 - x0)
		ui.fill_rect([x0, by + graphH - h + 4], [bw, h], COLOR_RED)
	}
}

// Layout baseline (pixels) matching advisor_population_graph_history offsets.
var HISTORY_REF_W = 456
var HISTORY_REF_H = 220

function advisor_population_draw_history_graph(elm, title_elm) {
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
	var max_months = it.max
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

	var gh = {
        y_axis_offset  : {x: -36, y: 0}
        y_axis_label_w : 60
        y_axis_height  : 200
        x_axis_offset  : {x: -10, y: 240}
        x_axis_width   : 170
        plot_offset    : {x: -5, y: 20}
    }
	var bx = elm.pos.x
	var by = elm.pos.y
	var lw = elm.size.x > 8 ? elm.size.x : HISTORY_REF_W
	var lh = elm.size.y > 8 ? elm.size.y : HISTORY_REF_H
	var yo = gh.y_axis_offset
	var axisH = Math.max(32, ((gh.y_axis_height * lh) / HISTORY_REF_H) | 0)
	var yo0s = ((yo.x * lw) / HISTORY_REF_W) | 0
	var y_axis_base = [bx + yo0s, by + yo.y]

	title_elm.text = __loc(55, 6)
	ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex(String((y_max / 2) | 0), [y_axis_base[0], y_axis_base[1] + (axisH / 2 | 0)], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex("0", [y_axis_base[0], y_axis_base[1] + axisH], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)

	var xAxisDy = ((gh.x_axis_offset.y * lh) / HISTORY_REF_H) | 0
	var xAxisDxL = ((gh.x_axis_offset.x * lw) / HISTORY_REF_W) | 0
	var xAxisDxR = (((gh.x_axis_offset.x + gh.x_axis_width) * lw) / HISTORY_REF_W) | 0

	var range = advisor_population_min_max_month_year(max_months)
	var left = __loc(25, range.start.month) + " " + range.start.year
	var right = __loc(25, range.end.month) + " " + range.end.year
	ui.label_ex(left, advisor_population_v2_add(elm.pos, xAxisDxL, xAxisDy), FONT_SMALL_PLAIN, 0, 0)
	ui.label_ex(right, advisor_population_v2_add(elm.pos, xAxisDxR, xAxisDy), FONT_SMALL_PLAIN, 0, 0)

	// Clip in the same coordinate space as fill_rect/image (parent + elm.pos), not [0,0] of the panel.
	ui.set_clip_rectangle([bx, by], [lw, lh])
	var pad = 2
	var gw = Math.max(1, lw - pad * 2)
	for (m = 0; m < max_months; m++) {
		var pop = city.population_stats.at_month(max_months, m)
		var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
		if (val <= 0) {
			continue
		}
		// val is already in "graph pixel" units from y_shift (same as original C++/JS); only cap to axis height.
		var barH = Math.min(axisH, val | 0)
		if (barH <= 0) {
			continue
		}
		var x0 = bx + pad + (((m * gw) / max_months) | 0)
		var x1 = bx + pad + ((((m + 1) * gw) / max_months) | 0)
		var bw = Math.max(1, x1 - x0)
		if (max_months >= 200) {
			ui.fill_rect([x0 + gh.plot_offset.x, by + axisH - barH + gh.plot_offset.y], [bw, barH], COLOR_RED)
		} else {
			var imgBar = get_image({ pack: PACK_GENERAL, id: 157, offset: graphid - 1 })
			var ix = x0 + ((bw - 1) >> 1)
			ui.image(imgBar, [ix, by + axisH - barH])
		}
	}

	ui.reset_clip_rectangle()
}

function advisor_population_draw_census_graph_button(elm, title_elm) {
	var max_value = 0
	var i
	for (i = 0; i < 100; i++) {
		var av = city.population_stats.at_age(i)
		if (av > max_value) {
			max_value = av
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_shift = ypx[1]

	title_elm.text = __loc(55, 4)

	var bx = elm.pos.x
	var by = elm.pos.y
	y_shift += 2
	for (i = 0; i < 100; i++) {
		var val2 = city.population_stats.at_age(i) >> y_shift
		if (val2 > 0) {
			ui.fill_rect([bx + i + 4, by + 50 - val2], [1, val2], COLOR_RED)
		}
	}
}

function advisor_population_draw_census_graph(elm, title_elm) {
	var max_value = 0
	var i
	for (i = 0; i < 100; i++) {
		var av = city.population_stats.at_age(i)
		if (av > max_value) {
			max_value = av
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_max = ypx[0]
	var y_shift = ypx[1]

	var gc = advisor_population_graph_census
	var bx = elm.pos.x
	var by = elm.pos.y
	var bpos = elm.pos
	var yo = gc.y_axis_offset
	var y_axis_base = [bx + yo[0], by + yo[1]]

	title_elm.text = __loc(55, 7)
	ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gc.y_axis_label_w)
	ui.label_ex(String((y_max / 2) | 0), [y_axis_base[0], y_axis_base[1] + (gc.y_axis_height / 2 | 0)], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gc.y_axis_label_w)
	ui.label_ex("0", [y_axis_base[0], y_axis_base[1] + gc.y_axis_height], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gc.y_axis_label_w)
	for (i = 0; i <= 10; i++) {
		ui.label_ex(String(i * 10), advisor_population_v2_add(bpos, gc.x_axis_offset[0] + 40 * i, gc.x_axis_offset[1]), FONT_SMALL_PLAIN, UiFlags_AlignCentered, gc.y_axis_label_w)
	}

	title_elm.text = __loc(55, 6)
	ui.set_clip_rectangle([0, 0], [640, by + 200])
	var imgBar = get_image({ pack: PACK_GENERAL, id: 157, offset: 1 })
	for (i = 0; i < 100; i++) {
		var pop = city.population_stats.at_age(i)
		var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
		if (val > 0) {
			ui.image(imgBar, [bx + 4 * i, by + 200 - val])
		}
	}
	ui.reset_clip_rectangle()
}

function advisor_population_draw_society_graph_button(elm, title_elm) {
	var max_value = 0
	var i
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var lv = city.population_stats.at_level(i)
		if (lv > max_value) {
			max_value = lv
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_shift = ypx[1]

	title_elm.text = __loc(55, 5)

	var bx = elm.pos.x
	var by = elm.pos.y
	y_shift += 2
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var val2 = city.population_stats.at_level(i) >> y_shift
		if (val2 > 0) {
			ui.fill_rect([bx + 5 * i + 4, by + 50 - val2], [4, val2 + 1], COLOR_RED)
		}
	}
}

function advisor_population_draw_society_graph(elm, title_elm) {
	var max_value = 0
	var i
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var lv = city.population_stats.at_level(i)
		if (lv > max_value) {
			max_value = lv
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_max = ypx[0]
	var y_shift = ypx[1]

	var gs = advisor_population_society_history
	var bx = elm.pos.x
	var by = elm.pos.y
	var bpos = elm.pos
	var yo = gs.y_axis_offset
	var y_axis_base = [bx + yo[0], by + yo[1]]

	title_elm.text = __loc(55, 8)
	ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gs.y_axis_label_w)
	ui.label_ex(String((y_max / 2) | 0), [y_axis_base[0], y_axis_base[1] + (gs.y_axis_height / 2 | 0)], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gs.y_axis_label_w)
	ui.label_ex("0", [y_axis_base[0], y_axis_base[1] + gs.y_axis_height], FONT_SMALL_PLAIN, UiFlags_AlignCentered, gs.y_axis_label_w)
	ui.label_ex(__loc(55, 9), advisor_population_v2_add(bpos, gs.x_axis_offset[0], gs.x_axis_offset[1]), FONT_SMALL_PLAIN, 0, 0)
	ui.label_ex(__loc(55, 10), advisor_population_v2_add(bpos, gs.x_axis_offset[0] + gs.x_axis_width, gs.x_axis_offset[1]), FONT_SMALL_PLAIN, 0, 0)

	ui.set_clip_rectangle([0, 0], [640, by + 200])
	var imgBar = get_image({ pack: PACK_GENERAL, id: 157, offset: 0 })
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var pop = city.population_stats.at_level(i)
		var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
		if (val > 0) {
			ui.image(imgBar, [bx + 20 * i, by + 200 - val])
		}
	}
	ui.reset_clip_rectangle()
}

function advisor_population_draw_graph_kind(elm, kind, title_elm) {
	if (kind === GRAPH_HISTORY) {
		advisor_population_draw_history_graph(elm, title_elm)
	} else if (kind === GRAPH_CENSUS) {
		advisor_population_draw_census_graph(elm, title_elm)
	} else {
		advisor_population_draw_society_graph(elm, title_elm)
	}
}

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
	var row = advisor_population_graph_layout[advisor_population_window.graph_order]
    var elm = window[window.active_id]
	advisor_population_draw_graph_kind(elm, row[0], window.big_text)
}

[es=(advisor_population_window, ondraw_top)]
function advisor_population_es_ondraw_top(window) {
	var row = advisor_population_graph_layout[advisor_population_window.graph_order]
    var elm = window[window.active_id]
	advisor_population_draw_graph_button(elm, row[1], window.top_text)
}

[es=(advisor_population_window, ondraw_bot)]
function advisor_population_es_ondraw_bot(window) {
	var row = advisor_population_graph_layout[advisor_population_window.graph_order]
    var elm = window[window.active_id]
	advisor_population_draw_graph_button(elm, row[2], window.bot_text)
}

advisor_population_graph_census = {
	y_axis_offset  : [-56, 0]
	y_axis_label_w : 60
	y_axis_height  : 200

	x_axis_offset  : [-20, 210]
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
	__advisor_population_print_info(row[3])
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
		next_graph   : button({pos:[503, 61], size:[104, 55], tooltip:[68, 106], ondraw_event: "ondraw_top" }),

		bot_text     : text({pos:[503, 144], font:FONT_NORMAL_BLACK_ON_DARK}),
		prev_graph   : button({pos:[503, 161], size:[104, 55], tooltip:[68, 106], ondraw_event: "ondraw_bot" }),

		big_text     : label({font : FONT_NORMAL_BLACK_ON_DARK, pos:[60, 44]}),
		big_graph_tx : label({pos:[65, 62], size:[800, 200], ondraw_event: "ondraw_big"}),

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
