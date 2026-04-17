log_info("akhenaten: ui advisor population graph history started")

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
	var span = month_count > 0 ? month_count : 1
	var end_month = (span + start_month) % 12
	var end_year = (((span + start_month) / 12) | 0) + start_year
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
	var plot_months = Math.max(1, Math.min(month_count, max_months))

	var max_value = 0
	var m
	for (m = 0; m < plot_months; m++) {
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
	for (m = 0; m < plot_months; m++) {
		var t = city.population_stats.at_month(max_months, m) >> y_shift
		if (t > max_bar) {
			max_bar = t
		}
	}
	for (m = 0; m < plot_months; m++) {
		var val2 = city.population_stats.at_month(max_months, m) >> y_shift
		if (val2 <= 0) {
			continue
		}
		var h = max_bar > 0 ? Math.max(1, ((val2 * graphH) / max_bar) | 0) : 1
		var x0 = bx + pad + (((m * gw) / plot_months) | 0)
		var x1 = bx + pad + ((((m + 1) * gw) / plot_months) | 0)
		var bw = Math.max(1, x1 - x0)
		ui.fill_rect([x0, by + graphH - h + 4], [bw, h], COLOR_RED)
	}
}

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
	var plot_months = Math.max(1, Math.min(month_count, max_months))

	var max_value = 0
	var m
	for (m = 0; m < plot_months; m++) {
		var value = city.population_stats.at_month(max_months, m)
		if (value > max_value) {
			max_value = value
		}
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_max = ypx[0]
	var y_shift = ypx[1]

	var gh = {
        y_axis_offset  : {x: -66, y: 0}
        y_axis_label_w : 60
        y_axis_height  : 200
        x_axis_offset  : {x: -10, y: 240}
        x_axis_width   : 400
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

	ui.set_clip_rectangle([bx, by], [lw, lh])
	var pad = 2
	var gw = Math.max(1, lw - pad * 2)
	for (m = 0; m < plot_months; m++) {
		var pop = city.population_stats.at_month(max_months, m)
		var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
		if (val <= 0) {
			continue
		}
		var barH = Math.min(axisH, val | 0)
		if (barH <= 0) {
			continue
		}
		var x0 = bx + pad + (((m * gw) / plot_months) | 0)
		var x1 = bx + pad + ((((m + 1) * gw) / plot_months) | 0)
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
