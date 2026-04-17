log_info("akhenaten: ui advisor population graph society started")

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
	var pad = 4
	var gw = advisor_population_clamp(elm.size.x - pad * 2, 1, 10000)
	var graphH = advisor_population_clamp(elm.size.y - 10, 8, 512)
	y_shift += 2
	var max_bar = 0
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var t = city.population_stats.at_level(i) >> y_shift
		if (t > max_bar) {
			max_bar = t
		}
	}
	for (i = 0; i < HOUSE_LEVEL_MAX; i++) {
		var val2 = city.population_stats.at_level(i) >> y_shift
		if (val2 <= 0) {
			continue
		}
		var h = max_bar > 0 ? Math.max(1, ((val2 * graphH) / max_bar) | 0) : 1
		var x0 = bx + pad + (((i * gw) / HOUSE_LEVEL_MAX) | 0)
		var x1 = bx + pad + ((((i + 1) * gw) / HOUSE_LEVEL_MAX) | 0)
		var bw = Math.max(1, x1 - x0)
		ui.fill_rect([x0, by + graphH - h + 4], [bw, h], COLOR_RED)
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

	var gh = {
		y_axis_offset  : { x: -66, y: 0 }
		y_axis_label_w : 60
		y_axis_height  : 200
		x_axis_offset  : { x: -20, y: 245 }
		x_axis_width   : 400
		plot_offset    : { x: -5, y: 20 }
	}
	var bx = elm.pos.x
	var by = elm.pos.y
	var lw = elm.size.x > 8 ? elm.size.x : HISTORY_REF_W
	var lh = elm.size.y > 8 ? elm.size.y : HISTORY_REF_H
	var yo = gh.y_axis_offset
	var axisH = Math.max(32, ((gh.y_axis_height * lh) / HISTORY_REF_H) | 0)
	if (axisH > lh - 4) {
		axisH = lh - 4
	}
	var yo0s = ((yo.x * lw) / HISTORY_REF_W) | 0
	var y_axis_base = { x: bx + yo0s, y: by + yo.y }

	title_elm.text = __loc(55, 8)
	ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex(String((y_max / 2) | 0), { x: y_axis_base.x, y: y_axis_base.y + (axisH / 2 | 0) }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex("0", { x: y_axis_base.x, y: y_axis_base.y + axisH }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)

	var xAxisDy = ((gh.x_axis_offset.y * lh) / HISTORY_REF_H) | 0
	var xAxisDxL = ((gh.x_axis_offset.x * lw) / HISTORY_REF_W) | 0
	var xAxisDxR = (((gh.x_axis_offset.x + gh.x_axis_width) * lw) / HISTORY_REF_W) | 0
	ui.label_ex(__loc(55, 9), advisor_population_v2_add(elm.pos, xAxisDxL, xAxisDy), FONT_SMALL_PLAIN, 0, 0)
	ui.label_ex(__loc(55, 10), advisor_population_v2_add(elm.pos, xAxisDxR, xAxisDy), FONT_SMALL_PLAIN, 0, 0)

	ui.set_clip_rectangle([bx, by], [lw, lh])
	var plotPad = 8
	var gw = Math.max(1, lw - plotPad * 2)
	var n = HOUSE_LEVEL_MAX
	for (i = 0; i < n; i++) {
		var pop = city.population_stats.at_level(i)
		var val = (y_shift === -1) ? (2 * pop) : (pop >> y_shift)
		if (val <= 0) {
			continue
		}
		var barH = Math.min(axisH, val | 0)
		if (barH <= 0) {
			continue
		}
		var x0 = bx + plotPad + (((i * gw) / n) | 0)
		var x1 = bx + plotPad + ((((i + 1) * gw) / n) | 0)
		var bw = Math.max(1, x1 - x0)
		ui.fill_rect([x0 + gh.plot_offset.x, by + axisH - barH + gh.plot_offset.y], [bw, barH], COLOR_RED)
	}
	ui.reset_clip_rectangle()
}
