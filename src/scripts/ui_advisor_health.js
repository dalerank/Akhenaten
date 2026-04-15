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

[es=advisor_window]
advisor_health_window {
	advisor: ADVISOR_HEALTH
	ui {
		background   : outer_panel({size:[40, 18]})
		advisor_icon : image({pack:PACK_GENERAL, id:128, offset:6, pos:[10, 10] })
		title        : header({pos:[60, 17], text:{group:56, id:0}})
		city_health  : multiline({pos:[60, 46], size:[520, 90], wrap:500, font: FONT_NORMAL_BLACK_ON_LIGHT})

		working      : label({text:[56, 3], pos:[180, 94], font:FONT_SMALL_PLAIN})
		care_for     : label({text:[56, 4], pos:[290, 94], font:FONT_SMALL_PLAIN})
		city_coverage: text_center({text:[56, 5], pos:[440, 94], size:[160, 20], font:FONT_SMALL_PLAIN})

		inner_panel  : inner_panel({
			pos:[32, 108]
			size:[36, 6]
			ui : {
				physicians_total : label({pos:[15, 8], font:FONT_NORMAL_BLACK_ON_DARK})
				physicians_active: text_center({pos:[160, 8], size:[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
				physicians_care  : text_center({pos:[290, 8], size:[40, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
				physicians_covg  : text_center({pos:[440, 8], size:[60, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

				dentist_total    : label({pos:[15, 28], font:FONT_NORMAL_BLACK_ON_DARK})
				dentist_active   : text_center({pos:[160, 28], size:[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
				dentist_care     : text_center({pos:[290, 28], size:[40, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
				dentist_covg     : text_center({pos:[440, 28], size:[60, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

				apothecary_total : label({pos:[15, 46], font:FONT_NORMAL_BLACK_ON_DARK})
				apothecary_active: text_center({pos:[160, 46], size:[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
				apothecary_care  : text_center({pos:[290, 46], size:[40, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
				apothecary_covg  : text_center({pos:[440, 46], size:[60, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

				mortuary_total   : label({pos:[15, 66], font:FONT_NORMAL_BLACK_ON_DARK})
				mortuary_active  : text_center({pos:[160, 66], size:[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
				mortuary_care    : text_center({pos:[290, 66], size:[40, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
				mortuary_covg    : text_center({pos:[440, 66], size:[60, 20], text:[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
			}
		})

		health_advice : multiline({pos:[60, 218], size:[520, 90], wrap:500, font: FONT_NORMAL_BLACK_ON_LIGHT })
	}
}

[es=(advisor_health_window, init)]
function advisor_health_window_init(window) {
	var cov = city.coverage
	var pop = city.population
	var hr = city.health_rating

	window.city_health.text = (pop >= 200) ? __loc(56, ((hr / 10) | 0) + 16) : __loc(56, 15)

	var apoAct = city.count_active_buildings(BUILDING_APOTHECARY)
	window.apothecary_total.text = city.count_total_buildings(BUILDING_APOTHECARY) + " " + __loc(8, 29)
	window.apothecary_active.text = String(apoAct)
	window.apothecary_care.text = (1000 * apoAct) + " " + __loc(56, 6)
	window.apothecary_covg.text = __loc(57, ((cov.apothecary / 10) | 0) + 11)

	var denAct = city.count_active_buildings(BUILDING_DENTIST)
	window.dentist_total.text = city.count_total_buildings(BUILDING_DENTIST) + " " + __loc(8, 27)
	window.dentist_active.text = String(denAct)
	window.dentist_care.text = (1000 * denAct) + " " + __loc(56, 6)
	window.dentist_covg.text = __loc(57, ((cov.dentist / 10) | 0) + 11)

	var phyAct = city.count_active_buildings(BUILDING_PHYSICIAN)
	window.physicians_total.text = city.count_total_buildings(BUILDING_PHYSICIAN) + " " + __loc(8, 25)
	window.physicians_active.text = String(phyAct)
	window.physicians_care.text = (1000 * phyAct) + " " + __loc(56, 6)
	window.physicians_covg.text = __loc(57, ((cov.physician / 10) | 0) + 11)

	var morAct = city.count_active_buildings(BUILDING_MORTUARY)
	window.mortuary_total.text = city.count_total_buildings(BUILDING_MORTUARY) + " " + __loc(8, 31)
	window.mortuary_active.text = String(morAct)
	window.mortuary_care.text = (1000 * morAct) + " " + __loc(56, 6)
	window.mortuary_covg.text = __loc(57, ((cov.mortuary / 10) | 0) + 11)

	window.health_advice.text = __loc(56, 6 + advisor_health_advice_index())
}
