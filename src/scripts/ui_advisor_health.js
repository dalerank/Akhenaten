log_info("akhenaten: ui advisor health started")

function advisor_health_advice_index() {
	var d = city.houses.health
	var req = city.houses.requiring
	if (d === 1) {
		return req.water_supply ? 1 : 0
	}
	if (d === 2) {
		return req.dentist ? 3 : 2
	}
	if (d === 3) {
		return req.physician ? 5 : 4
	}
	if (d === 4) {
		return 6
	}
	return 7
}

var ADVISOR_HEALTH_FACILITIES = [
	{ id: "physician", building: BUILDING_PHYSICIAN, nameLoc8: 25 },
	{ id: "dentist", building: BUILDING_DENTIST, nameLoc8: 27 },
	{ id: "apothecary", building: BUILDING_APOTHECARY, nameLoc8: 29 },
	{ id: "mortuary", building: BUILDING_MORTUARY, nameLoc8: 31 }
]

function advisor_health_facility_row(key) {
	for (var i = 0; i < ADVISOR_HEALTH_FACILITIES.length; i++) {
		if (ADVISOR_HEALTH_FACILITIES[i].id === key) {
			return ADVISOR_HEALTH_FACILITIES[i]
		}
	}
	return null
}

function advisor_health_facilities_on_render_item(p) {
	var key = p.text
	if (!key) {
		return
	}
	var row = advisor_health_facility_row(key)
	if (!row) {
		return
	}
	var font = FONT_NORMAL_BLACK_ON_DARK
	var btype = row.building
	var act = city.count_active_buildings(btype)
	var covPct10 = city.coverage[row.id]
	var totalStr = city.count_total_buildings(btype) + " " + __loc(8, row.nameLoc8)
	var careStr = (1000 * act) + " " + __loc(56, 6)
	var covgStr = __loc(57, ((covPct10 / 10) | 0) + 11)
	var py = p.y
	var flagsCell = UiFlags_AlignYCentered | UiFlags_AlignCentered
	ui.label_ex(totalStr, {x: p.x + 15, y: py}, font, UiFlags_AlignYCentered, 125)
	ui.label_ex(String(act), [p.x + 160, py], font, flagsCell, 40)
	ui.label_ex(careStr, [p.x + 290, py], font, flagsCell, 40)
	ui.label_ex(covgStr, [p.x + 440, py], font, flagsCell, 60)
	if (p.hover) {
		ui.border({ x: p.x + 4, y: p.y - 2 }, { x: p.sizex - 8, y: p.sizey + 2 }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
	}
}

[es=advisor_window]
advisor_health_window {
	advisor: ADVISOR_HEALTH
	allow_rmb_goback : true
	help_id: "message_overseer_public_health"
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
            ui : {
				background   : outer_panel({size:[40, 18]})
				advisor_icon : image({pack:PACK_GENERAL, id:128, offset:6, pos:[10, 10] })
				title        : header({pos:[60, 17], text:{group:56, id:0}})
				city_health  : multiline({pos:[60, 46], size:[520, 90], wrap:500, font: FONT_NORMAL_BLACK_ON_LIGHT})

				working      : label({text:[56, 3], pos:[180, 94], font:FONT_SMALL_PLAIN})
				care_for     : label({text:[56, 4], pos:[290, 94], font:FONT_SMALL_PLAIN})
				city_coverage: text_center({text:[56, 5], pos:[440, 94], size:[160, 20], font:FONT_SMALL_PLAIN})

				facilities_list : scrollable_list({
					pos:[32, 108]
					size:[36, 6]
					view_items:4
					buttons_size_y:20
					buttons_margin_x:0
					buttons_margin_y:10
					text_padding_x:0
					text_padding_y:0
					draw_scrollbar_always:false
					draw_paneling:true
					onrender_item: advisor_health_facilities_on_render_item
				})

				health_advice : multiline({pos:[60, 218], size:[520, 90], wrap:500, font: FONT_NORMAL_BLACK_ON_LIGHT })
			}
		})
	})
}

[es=(advisor_health_window, init)]
function advisor_health_window_init(window) {
	var pop = city.population
	var hr = city.health_rating

	window.city_health.text = (pop >= 200) ? __loc(56, ((hr / 10) | 0) + 16) : __loc(56, 15)

	var list = window.facilities_list
	list.clear()
	for (var i = 0; i < ADVISOR_HEALTH_FACILITIES.length; i++) {
		list.add_item(ADVISOR_HEALTH_FACILITIES[i].id)
	}

	window.health_advice.text = __loc(56, 6 + advisor_health_advice_index())

	advisors_toolbar_refresh(window, ADVISOR_HEALTH)
}
