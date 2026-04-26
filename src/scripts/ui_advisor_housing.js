log_info("akhenaten: ui advisor housing started")

function advisor_housing_on_graphs_button() {
	window_advisors_show_advisor(ADVISOR_POPULATION)
}

[es=(advisor_housing_window, ondraw_housing_chart)]
function advisor_housing_es_ondraw_chart(window) {
	var elm = window.housing_graph
	var max_value = 0
	var i
	for (i = 0; i < 20; i++) {
		var c = city.housing_type_count_at(i)
		if (c > max_value) {
			max_value = c
		}
	}
	if (max_value < 1) {
		max_value = 1
	}
	var ypx = advisor_population_history_y_axis(max_value)
	var y_max = ypx[0]
	var y_shift = ypx[1]

	var gh = {
		y_axis_offset  : { x: -66, y: 0 }
		y_axis_label_w : 60
		y_axis_height  : 200
		x_axis_offset  : { x: -40, y: 240 }
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

	ui.label_ex(String(y_max), y_axis_base, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex(String((y_max / 2) | 0), { x: y_axis_base.x, y: y_axis_base.y + (axisH / 2 | 0) }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	ui.label_ex("0", { x: y_axis_base.x, y: y_axis_base.y + axisH }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)

	var xAxisDy = ((gh.x_axis_offset.y * lh) / HISTORY_REF_H) | 0
	var plotPad = 8
	var gw = Math.max(1, lw - plotPad * 2)
	var n = 20
	for (i = 0; i <= 4; i++) {
		var dx = plotPad + (((i * gw) / 4) | 0)
		ui.label_ex(String(i * 5), advisor_population_v2_add({ x: elm.pos.x - 30, y: elm.pos.y }, dx, xAxisDy), FONT_SMALL_PLAIN, UiFlags_AlignCentered, gh.y_axis_label_w)
	}

	ui.set_clip_rectangle([bx, by], [lw, lh])
	for (i = 0; i < n; i++) {
		var cnt = city.housing_type_count_at(i)
		var val = (y_shift === -1) ? (2 * cnt) : (cnt >> y_shift)
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

[es=(advisor_housing_window, init)]
function advisor_housing_window_show_total(window) {
	window.total_population.text = __loc("#TR_ADVISOR_TOTAL_POPULATION") + " " + String(city.population)
	window.stat_total_value.text = String(city.total_housing_buildings())
	window.stat_avail_value.text = String(city.open_housing_capacity())
	window.stat_cap_value.text = String(city.total_housing_capacity())
	window.goods_demanding_0_value.text = String(city.houses_demanding_goods_at(0))
	window.goods_demanding_1_value.text = String(city.houses_demanding_goods_at(1))
	window.goods_demanding_2_value.text = String(city.houses_demanding_goods_at(2))
	window.goods_demanding_3_value.text = String(city.houses_demanding_goods_at(3))

	advisors_toolbar_refresh(window, ADVISOR_HOUSING)
}

[es=advisor_window]
advisor_housing_window {
	advisor: ADVISOR_HOUSING
	allow_rmb_goback : true
	help_id: "message_housing_and_desirability"
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2], size:[px(40), px(27)]
            ui : {
				background       : outer_panel({size:[40, 27]})
				advisor_icon     : image({pack:PACK_GENERAL, id:128, offset:5, pos:[10, 10]})
				title            : label({font: FONT_LARGE_BLACK_ON_LIGHT, text:"#TR_ADVISOR_ADVISOR_HEADER_HOUSING", pos:[60, 12]})
				total_population : label({font: FONT_NORMAL_BLACK_ON_LIGHT, pos:[450, 25]})
				inner_panel      : inner_panel({pos:[65, 70], size:[28, 13]})
				housing_graph    : label({pos:[75, 75], size:[395, 195], ondraw_event: "ondraw_housing_chart"})

				graphs_caption   : text_center({font: FONT_NORMAL_BLACK_ON_LIGHT, text:"#TR_ADVISOR_BUTTON_GRAPHS", pos:[545, 315]})
				graphs_btn       : image_button({
										pos: [545, 260]
										pack: PACK_GENERAL, id: 29
										composite: true
										border: 3
										tooltip: [68, 106]
										onclick: advisor_housing_on_graphs_button,
									}),

				stat_total_label : label({ font: FONT_NORMAL_BLACK_ON_DARK, text: "#TR_ADVISOR_TOTAL_NUM_HOUSES", pos: [370, 354] })
				stat_total_value : label({ font: FONT_NORMAL_WHITE_ON_DARK, pos: [550, 354] })
				stat_avail_label : label({ font: FONT_NORMAL_BLACK_ON_DARK, text: "#TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY", pos: [370, 377] })
				stat_avail_value : label({ font: FONT_NORMAL_WHITE_ON_DARK, pos: [550, 377] })
				stat_cap_label   : label({ font: FONT_NORMAL_BLACK_ON_DARK, text: "#TR_ADVISOR_TOTAL_HOUSING_CAPACITY", pos: [370, 400] })
				stat_cap_value   : label({ font: FONT_NORMAL_WHITE_ON_DARK, pos: [550, 400] })

				goods_demanding_0_icon : resource_icon({ pos: [34, 328], resource: RESOURCE_POTTERY })
				goods_demanding_0_text : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY", pos: [60, 331] })
				goods_demanding_0_value : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, pos: [320, 331] })
				goods_demanding_1_icon : resource_icon({ pos: [34, 351], resource: RESOURCE_LUXURY_GOODS })
				goods_demanding_1_text : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE", pos: [60, 354] })
				goods_demanding_1_value : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, pos: [320, 354] })
				goods_demanding_2_icon : resource_icon({ pos: [34, 374], resource: RESOURCE_MEAT })
				goods_demanding_2_text : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_ADVISOR_RESIDENCES_DEMANDING_LINEN", pos: [60, 377] })
				goods_demanding_2_value : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, pos: [320, 377] })
				goods_demanding_3_icon : resource_icon({ pos: [34, 397], resource: RESOURCE_BEER })
				goods_demanding_3_text : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_ADVISOR_RESIDENCES_DEMANDING_BEER", pos: [60, 400] })
				goods_demanding_3_value : label({ font: FONT_NORMAL_BLACK_ON_LIGHT, pos: [320, 400] })

				button_help   : help_button({})
			}
		})
	})
}
