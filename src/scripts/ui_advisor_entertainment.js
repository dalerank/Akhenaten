log_info("akhenaten: ui advisor entertainment started")

function advisor_entertainment_advice_index() {
	var miss = city.houses.missing
	if (miss.entertainment > miss.more_entertainment) {
		return 3
	}
	if (!miss.more_entertainment) {
		return city.avg_coverage.average_entertainment ? 1 : 0
	}
	var vns = city.entertainment.venue_needing_shows
	if (vns) {
		return 3 + vns
	}
	return 2
}

function advisor_entertainment_coverage_text(coverage) {
	if (coverage === 0) {
		return __loc(57, 7)
	}
	if (coverage >= 100) {
		return __loc(57, 18)
	}
	return __loc(57, 8 + ((coverage / 10) | 0))
}

function advisor_entertainment_fill_row(window, rowType, prefix, venueType, shows, coverage, entertainCoeff) {
	var enabled = scenario.building_allowed(venueType)
	var font = enabled ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
	var base = prefix + "_"
	var total = window[base + "total"]
	var active = window[base + "active"]
	var showsW = window[base + "shows"]
	var care = window[base + "care"]
	var cvg = window[base + "cvg"]

	total.font = font
	active.font = font
	showsW.font = font
	care.font = font
	cvg.font = font

	if (!enabled) {
		total.text = __loc(58, 47 + rowType)
		active.text = __loc(58, 51)
		showsW.text = __loc(58, 51)
		care.text = __loc(58, 51)
		cvg.text = __loc(57, 7)
		return
	}

	var actCount = city.count_active_buildings(venueType)
	total.text = __loc(58, 47 + rowType)
	active.text = String(actCount)
	showsW.text = String(shows)
	care.text = (entertainCoeff * actCount) + " " + __loc(58, 5)
	cvg.text = advisor_entertainment_coverage_text(coverage)
}

[es=advisor_window]
advisor_entertainment_window {
	advisor: ADVISOR_ENTERTAINMENT
	ui {
		background    : outer_panel({size:[40, 20] })
		title         : text({pos: [60, 12], text:[58, 0], font : FONT_LARGE_BLACK_ON_LIGHT })
		advisor_icon  : image({pack:PACK_GENERAL, id:128, offset:8, pos:[10, 10] }),

		working       : text({text:[58, 1], pos:[180, 42], font:FONT_NORMAL_BLACK_ON_LIGHT}),
		stages        : text({text:[58, 55], pos:[180, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
		shows         : text({text:[58, 2], pos:[280, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
		can_entertain : text({text:[58, 3], pos:[340, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
		city_coverage : text({text:[58, 4], pos:[470, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),

		advice        : multiline({ margin:{left:30, bottom:-110}, size:[px(38), 208], wrap:512, font:FONT_NORMAL_BLACK_ON_LIGHT }),

		inner_panel   : inner_panel({pos:[32, 70], size:[36, 8],
			ui : {
				booth_total       : text({pos:[10,  5]}),
				booth_active      : text_center({pos:[150, 5], size:[50, 20]}),
				booth_shows       : text_center({pos:[250, 5], size:[50, 20]}),
				booth_care        : text_center({pos:[310, 5], size:[50, 20]}),
				booth_cvg         : text_center({pos:[440, 5], size:[100, 20]}),

				bandstand_total   : text({pos:[10,  30]}),
				bandstand_active  : text_center({pos:[150, 30], size:[50, 20]}),
				bandstand_shows   : text_center({pos:[250, 30], size:[50, 20]}),
				bandstand_care    : text_center({pos:[310, 30], size:[50, 20]}),
				bandstand_cvg     : text_center({pos:[440, 30], size:[100, 20]}),

				pavilion_total    : text({pos:[10,  55]}),
				pavilion_active   : text_center({pos:[150, 55], size:[50, 20]}),
				pavilion_shows    : text_center({pos:[250, 55], size:[50, 20]}),
				pavilion_care     : text_center({pos:[310, 55], size:[50, 20]}),
				pavilion_cvg      : text_center({pos:[440, 55], size:[100, 20]}),

				senet_house_total : text({pos:[10,  80]}),
				senet_house_active: text_center({pos:[150, 80], size:[50, 20]}),
				senet_house_shows : text_center({pos:[250, 80], size:[50, 20]}),
				senet_house_care  : text_center({pos:[310, 80], size:[50, 20]}),
				senet_house_cvg   : text_center({pos:[440, 80], size:[100, 20]}),

				zoo_total         : text({pos:[10,  105]}),
				zoo_active        : text_center({pos:[150, 105], size:[50, 20]}),
				zoo_shows         : text_center({pos:[250, 105], size:[50, 20]}),
				zoo_care          : text_center({pos:[310, 105], size:[50, 20]}),
				zoo_cvg           : text_center({pos:[440, 105], size:[100, 20]}),
			}
		}),
	}
}

[es=(advisor_entertainment_window, ui_draw_foreground)]
function advisor_entertainment_window_ui_draw_foreground(window) {
	var ent = city.entertainment
	advisor_entertainment_fill_row(window, 0, "booth", BUILDING_BOOTH, ent.booth_shows, city.coverage.booth, 400)
	advisor_entertainment_fill_row(window, 1, "bandstand", BUILDING_BANDSTAND, ent.bandstand_shows, city.coverage.bandstand, 700)
	advisor_entertainment_fill_row(window, 2, "pavilion", BUILDING_PAVILLION, ent.pavilion_shows, city.coverage.pavilion, 1200)
	advisor_entertainment_fill_row(window, 3, "senet_house", BUILDING_SENET_HOUSE, ent.senet_house_plays, city.coverage.senet_house, 0)
	advisor_entertainment_fill_row(window, 9, "zoo", BUILDING_ZOO, 0, 0, 0)

	window.advice.text = __loc(58, 7 + advisor_entertainment_advice_index())
}
