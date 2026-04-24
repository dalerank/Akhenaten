log_info("akhenaten: ui advisor education started")

function education_advice_index() {
	var demandsEdu = city.houses.education
	var reqSchool = city.houses.requiring.school
	var reqLib = city.houses.requiring.library
	if (demandsEdu === 1) {
		return reqSchool ? 1 : 0
	}
	if (demandsEdu === 2) {
		return reqLib ? 3 : 2
	}
	if (demandsEdu === 3) {
		return 4
	}
	var coverage_school = city.coverage.school
	var coverage_academy = city.coverage.academy
	var coverage_library = city.coverage.library
	var advice_id
	if (!reqSchool) {
		advice_id = 5
	} else if (!reqLib) {
		if (coverage_school >= 100 && coverage_academy >= 100) {
			advice_id = 6
		} else if (coverage_school <= coverage_academy) {
			advice_id = 7
		} else {
			advice_id = 8
		}
	} else {
		if (coverage_school >= 100 && coverage_academy >= 100 && coverage_library >= 100) {
			advice_id = 6
		} else if (coverage_school <= coverage_academy && coverage_school <= coverage_library) {
			advice_id = 7
		} else if (coverage_academy <= coverage_school && coverage_academy <= coverage_library) {
			advice_id = 8
		} else if (coverage_library <= coverage_school && coverage_library <= coverage_academy) {
			advice_id = 9
		} else {
			advice_id = 6
		}
	}
	return advice_id
}

// id = list entry and key on city.coverage; nameLoc8 = group 8 building name suffix; careLoc57 = group 57 care caption
var ADVISOR_EDUCATION_FACILITIES = [
	{ id: "school", building: BUILDING_SCRIBAL_SCHOOL, nameLoc8: 18, careLoc57: 7 },
	{ id: "academy", building: BUILDING_ACADEMY, nameLoc8: 20, careLoc57: 8 },
    { id: "library", building: BUILDING_LIBRARY, nameLoc8: 22, careLoc57: 9 }
]

function advisor_education_facility_row(key) {
	for (var i = 0; i < ADVISOR_EDUCATION_FACILITIES.length; i++) {
		if (ADVISOR_EDUCATION_FACILITIES[i].id === key) {
			return ADVISOR_EDUCATION_FACILITIES[i]
		}
	}
	return null
}

function advisor_education_facilities_on_render_item(p) {
	var key = p.text
	if (!key) {
		return
	}
	var row = advisor_education_facility_row(key)
	if (!row) {
		return
	}
	var font = FONT_NORMAL_WHITE_ON_DARK
	var btype = row.building
	var act = city.count_active_buildings(btype)
	var covPct10 = city.coverage[row.id]
	var totalStr = city.count_total_buildings(btype) + " " + __loc(8, row.nameLoc8)
	var careStr = (75 * act) + " " + __loc(57, row.careLoc57)
	var covgStr = __loc(57, ((covPct10 / 10) | 0) + 11)
	var py = p.y
	var flagsCell = UiFlags_AlignYCentered | UiFlags_AlignCentered
	ui.label_ex(totalStr, [p.x + 5, py], font, UiFlags_AlignYCentered, 95)
	ui.label_ex(String(act), [p.x + 100, py], font, flagsCell, 150)
	ui.label_ex(careStr, [p.x + 280, py], font, flagsCell, 40)
	ui.label_ex(covgStr, [p.x + 440, py], font, flagsCell, 60)
	if (p.hover) {
		ui.border({ x: p.x + 4, y: p.y - 2 }, { x: p.sizex - 8, y: p.sizey + 2 }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
	}
}

[es=advisor_window]
advisor_education_window {
	advisor: ADVISOR_EDUCATION
	allow_rmb_goback : true
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
			ui : {
				background   : outer_panel({size:[40, 19]})
				advisor_icon : image({pack:PACK_GENERAL, id:128, offset:7, pos:[10, 10] })
				title        : header({pos:[60, 17], text:[57, 0]})

				population   : text_center({pos:[20, 50], size:[200, 20], text:"${city.population} ${57.6}", font: FONT_NORMAL_BLACK_ON_LIGHT})
				school_age   : text_center({pos:[220, 50], size:[200, 20], text: "${city.population_kids} ${57.4}", font: FONT_NORMAL_BLACK_ON_LIGHT})
				academy_age  : text_center({pos:[420, 50], size:[200, 20], text: "${city.population_youngs} ${57.6}", font: FONT_NORMAL_BLACK_ON_LIGHT})

				header1      : text({text:[57, 4], pos:[180, 86], font:FONT_SMALL_PLAIN})
				header2      : text({text:[57, 5], pos:[290, 86], font:FONT_SMALL_PLAIN})
				header3      : text({text:[57, 6], pos:[478, 86], font:FONT_SMALL_PLAIN})

				facilities_list : scrollable_list({
					pos:[32, 108]
    				size:[36, 8]
					view_items:3
					buttons_size_y:25
					buttons_margin_x:0
					buttons_margin_y:10
					text_padding_x:0
					text_padding_y:0
					draw_scrollbar_always:false
					draw_paneling:true
					onrender_item: advisor_education_facilities_on_render_item
				})

				education_advice : multiline({pos:[30, 250], size:[px(37), 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
			}
		})
	})
}

[es=(advisor_education_window, init)]
function advisor_education_window_init(window) {
	window.education_advice.text = __loc(57, 22 + education_advice_index())
	var list = window.facilities_list
	list.clear()
	for (var i = 0; i < ADVISOR_EDUCATION_FACILITIES.length; i++) {
		list.add_item(ADVISOR_EDUCATION_FACILITIES[i].id)
	}

	advisors_toolbar_refresh(window)
}