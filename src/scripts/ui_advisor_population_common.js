log_info("akhenaten: ui advisor population common started")

var GRAPH_HISTORY = 0
var GRAPH_CENSUS = 1
var GRAPH_SOCIETY = 2
var HOUSE_LEVEL_MAX = 20

// graph_order matches GRAPH_* (0..2): main graph + info strip. Top/bot preview = (go+1)%3, (go+2)%3.
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
	if (max_value <= 1500) { return [1500, 3] }
	if (max_value <= 3000) { return [3000, 4] }
	if (max_value <= 6000) { return [6000, 5] }
	if (max_value <= 12000) { return [12000, 6] }
	if (max_value <= 25000) { return [25000, 7] }
	return [50000, 8]
}

// Layout baseline (pixels) matching advisor_population_graph_history offsets.
var HISTORY_REF_W = 456
var HISTORY_REF_H = 220

var advisor_population_info_icon_img = null
function advisor_population_get_info_icon_img() {
	if (!advisor_population_info_icon_img) {
		advisor_population_info_icon_img = get_image({ pack: PACK_GENERAL, id: 158 })
	}
	return advisor_population_info_icon_img
}

function advisor_population_info_lines_on_render_item(p) {
	var ix = p.user_data
	var lines = advisor_population_window._info_panel_lines
	if (lines === undefined || ix === undefined || lines[ix] === undefined) {
		return
	}
	var img = advisor_population_get_info_icon_img()
	ui.image(img, { x: p.x + 8, y: p.y + 2 })
	ui.label_ex(lines[ix], [p.x + 35, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, px(32))
	if (p.hover) {
		ui.border({ x: p.x + 4, y: p.y - 2 }, { x: p.sizex - 8, y: p.sizey + 2 }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
	}
}

function advisor_population_info_panel_fill_list(window, lines) {
	advisor_population_window._info_panel_lines = lines
	var list = window.info_lines_list
	list.clear()
	for (var i = 0; i < lines.length; i++) {
		list.add_item("", i)
	}
}

function advisor_population_print_census_info(window) {
	var ps = city.population_stats
	advisor_population_info_panel_fill_list(window, [
		__loc("#TR_ADVISOR_AVERAGE_AGE") + " " + String(ps.average_age()),
		__loc("#TR_ADVISOR_PERCENT_IN_WORKFORCE") + " " + String(advisor_population_percent_in_workforce_value()),
		__loc("#TR_ADVISOR_BIRTHS_LAST_YEAR") + " " + String(ps.yearly_births()),
		__loc("#TR_ADVISOR_DEATHS_LAST_YEAR") + " " + String(ps.yearly_deaths()),
	])
}

function advisor_population_print_society_info(window) {
	var houses = city.total_housing_buildings()
	advisor_population_info_panel_fill_list(window, [
		__loc("#TR_ADVISOR_HOUSING_PROSPERITY_RATING") + " " + String(city.rating.prosperity_max),
		__loc("#TR_ADVISOR_PERCENTAGE_IN_MANORS") + " " + String(Math.calc_percentage(city.population_stats.people_in_manors, city.population_stats.current)),
		__loc("#TR_ADVISOR_PERCENTAGE_IN_SHANTIES") + " " + String(Math.calc_percentage(city.population_stats.people_in_shanties, city.population_stats.current)),
		__loc("#TR_ADVISOR_AVERAGE_TAX") + " " + String(Math.floor(city.taxes.estimated_income / houses)),
	])
}

function advisor_population_print_history_info(window) {
	var line1
	if (scenario.kingdom_supplies_grain()) {
		line1 = __loc(55, 11)
	} else {
		var text = __loc(8, 6) + " " + String(__city_resource_operating_granaries())
		var months = __city_resource_food_supply_months()
		if (months > 0) {
			text += __loc(55, 12) + " " + __loc(8, 4) + " " + String(months)
		} else {
			var gst = __city_resource_granary_total_stored()
			var need = __city_resource_food_needed_per_month()
			if (gst > (need >> 1)) {
				text += __loc(55, 13)
			} else if (gst > 0) {
				text += __loc(55, 15)
			} else {
				text += __loc(55, 14)
			}
		}
		line1 = text
	}

	var line2 = __loc(55, 16) + " " + String(__city_resource_food_types_available_num())

	var line3
	var newcomers = __city_migration_newcomers()
	if (newcomers >= 5) {
		line3 = __loc(55, 24) + " " + String(newcomers) + " " + __loc(55, 17)
	} else if (__city_migration_no_room_for_immigrants()) {
		line3 = __loc(55, 24) + " " + __loc(55, 19)
	} else if (__city_migration_percentage() < 80) {
		var t = __loc(55, 25)
		var cause = __city_migration_problems_cause()
		var tid = 0
		if (cause === 0) {
			tid = 20
		} else if (cause === 1) {
			tid = 21
		} else if (cause === 2) {
			tid = 22
		} else if (cause === 3) {
			tid = 23
		} else if (cause === 4) {
			tid = 31
		} else if (cause === 5) {
			tid = 32
		}
		if (tid) {
			t += __loc(55, tid)
		}
		line3 = t
	} else {
		var tail = __loc(55, newcomers === 1 ? 18 : 17)
		line3 = __loc(55, 24) + ", " + String(newcomers) + tail
	}

	advisor_population_info_panel_fill_list(window, [line1, line2, line3])
}