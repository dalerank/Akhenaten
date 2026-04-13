log_info("akhenaten: ui advisor religion started")

function advisor_religion_advice_index() {
	var leastHappy = city.gods.least_happy()
	var demands = city.houses
	var reqRel = city.houses.requiring.religion
	if (leastHappy >= 0 && leastHappy < gods.length && city.gods.at(leastHappy).wrath_bolts > 4) {
		return 6 + leastHappy
	}
	if (demands.religion === 1) {
		return reqRel ? 1 : 0
	}
	if (demands.religion === 2) {
		return 2
	}
	if (demands.religion === 3) {
		return 3
	}
	if (!reqRel) {
		return 4
	}
	if (leastHappy >= 0 && leastHappy < gods.length) {
		return 6 + leastHappy
	}
	return 5
}

[es=advisor_window]
advisor_religion_window = {
	advisor: ADVISOR_RELIGION
	ui : {
		background : outer_panel({size:[40, 27] }),
		title : text({pos: [60, 12], text: {group:59, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT }),
		advisor_icon : image({pack:PACK_GENERAL, id:128, offset:9, pos:[10, 10] }),
		nogods_text : text({pos: [60, 256], text: {group:59, id:43}, wrap:520, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

		temple_header: { type : "text", pos: [180, 32], text: {group:59, id:5}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		complex_header: { type : "text", pos: [170, 46], text: {group:59, id:2}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		tempe_header: { type : "text", pos: [250, 46], text: {group:59, id:1}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		shrine_header: { type : "text", pos: [320, 46], text: {group:28, id:150}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		months_header: { type : "text", pos: [390, 18], text: {group:59, id:6}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		since_header: { type : "text", pos: [400, 32], text: {group:59, id:8}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		fest_header: { type : "text", pos: [390, 46], text: {group:59, id:7}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		mood_header: { type : "text", pos: [460, 46], text: {group:59, id:3}, font : FONT_NORMAL_BLACK_ON_LIGHT },

		inner_panel : { type : "inner_panel", pos:[32, 60], size:[36, 13] },

		god_0_name: { type : "text", pos: [40, 66]},
		god_0_known: { type : "text", pos: [100, 66]},
		god_0_complex: { type : "text", pos: [200, 66]},
		god_0_temple: { type : "text", pos: [265, 66]},
		god_0_shrine: { type : "text", pos: [330, 66]},
		god_0_fest: { type : "text", pos: [390, 66]},
		god_0_mood: { type : "text", pos: [460, 66]},
		god_0_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 63], enabled:false },
		god_0_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 63], enabled:false },
		god_0_desc: { type : "text", pos: [40, 86], font : FONT_NORMAL_BLACK_ON_DARK },

		god_1_name: { type : "text", pos: [40, 106]},
		god_1_known: { type : "text", pos: [100, 106]},
		god_1_complex: { type : "text", pos: [200, 106]},
		god_1_temple: { type : "text", pos: [265, 106]},
		god_1_shrine: { type : "text", pos: [330, 106]},
		god_1_fest: { type : "text", pos: [390, 106]},
		god_1_mood: { type : "text", pos: [460, 106]},
		god_1_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 103], enabled:false },
		god_1_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 103], enabled:false },
		god_1_desc: { type : "text", pos: [100, 126], font : FONT_NORMAL_BLACK_ON_DARK },

		god_2_name: { type : "text", pos: [40, 146]},
		god_2_known: { type : "text", pos: [100, 146]},
		god_2_complex: { type : "text", pos: [200, 146]},
		god_2_temple: { type : "text", pos: [265, 146]},
		god_2_shrine: { type : "text", pos: [330, 146]},
		god_2_fest: { type : "text", pos: [390, 146]},
		god_2_mood: { type : "text", pos: [460, 146]},
		god_2_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 143], enabled:false },
		god_2_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 143], enabled:false },
		god_2_desc: { type : "text", pos: [100, 166], font : FONT_NORMAL_BLACK_ON_DARK },

		god_3_name: { type : "text", pos: [40, 186]},
		god_3_known: { type : "text", pos: [100, 186]},
		god_3_complex: { type : "text", pos: [200, 186]},
		god_3_temple: { type : "text", pos: [265, 186]},
		god_3_shrine: { type : "text", pos: [330, 186]},
		god_3_fest: { type : "text", pos: [390, 186]},
		god_3_mood: { type : "text", pos: [460, 186]},
		god_3_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 183], enabled:false },
		god_3_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 183], enabled:false },
		god_3_desc: { type : "text", pos: [100, 206], font : FONT_NORMAL_BLACK_ON_DARK },

		god_4_name: { type : "text", pos: [40, 226]},
		god_4_known: { type : "text", pos: [100, 226]},
		god_4_complex: { type : "text", pos: [200, 226]},
		god_4_temple: { type : "text", pos: [265, 226]},
		god_4_shrine: { type : "text", pos: [330, 226]},
		god_4_fest: { type : "text", pos: [390, 226]},
		god_4_mood: { type : "text", pos: [460, 226]},
		god_4_bolt: { type : "image", pack:PACK_GENERAL, id:129, offset:34, pos:[540, 223], enabled:false },
		god_4_angel: { type : "image", pack:PACK_GENERAL, id:129, offset:33, pos:[540, 223], enabled:false },
		god_4_desc: { type : "text", pos: [100, 246], font : FONT_NORMAL_BLACK_ON_DARK },

		advice_text : { type : "text", pos: [60, 273], wrap:512, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		fest_inner_panel : { type : "inner_panel", pos:[48, 252 + 68], size:[34, 6] },
		fest_icon : { type : "image", pack:PACK_UNLOADED, id:21, offset:15, pos:[460, 255 + 68] },
		fest_months_last : { type : "label", pos:[112, 328], font:FONT_NORMAL_WHITE_ON_DARK},
		planed_festival : { type : "text", pos: [102, 284 + 68], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" },
		hold_festival_btn : { type:"generic_button", pos:[102, 278 + 68], size:[300, 24] },
		festival_advice : { type : "text", pos: [56, 305 + 68], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true },
	}
}

[es=(advisor_religion_window, draw_background)]
function advisor_religion_window_draw_background(window) {
	__city_religion_calculate_least_happy_god()
	var root = window.ui !== undefined ? window.ui : window
	if (!game.gods_enabled) {
		root.nogods_text.enabled = true
		return
	}
	root.nogods_text.enabled = false

	var fest = city.festival
	var m = fest.months_since_festival
	root.fest_months_last.text = String(m) + " " + __loc(8, 5) + " " + __loc(58, 15)

	var festivalTextIffs = [0, 10, 20, 31]
	if (city.festival.is_planned) {
		var size = __city_festival_selected_size()
		var monthsLeft = __city_festival_months_till_next()
		var plannedMonth = (__game_simtime_month() + monthsLeft) % 12
		var baseIdx = (size >= 0 && size < festivalTextIffs.length) ? festivalTextIffs[size] : festivalTextIffs[festivalTextIffs.length - 1]

		root.hold_festival_btn.enabled = false
		root.planed_festival.text = __loc(58, 34) + " " + __loc(160, plannedMonth)
		root.festival_advice.text = __loc(295, baseIdx + monthsLeft - 1)
	} else {
		root.hold_festival_btn.enabled = true
		root.hold_festival_btn.text = __loc(58, 16)
		root.hold_festival_btn.onclick = function() {
			if (city.count_total_buildings(BUILDING_FESTIVAL_SQUARE) === 0) {
				ui.show_ok("#popup_dialog_no_festival_square")
				return
			}
			if (!city.festival.is_planned) {
				show_window_by_id("hold_festival_window")
			}
		}
		root.festival_advice.text = __loc(58, 18 + city.festival.get_advice())
	}

	root.advice_text.text = __loc(59, 9 + advisor_religion_advice_index())
}

// Bolt/angel icon Y per row (matches god_N_bolt pos in ui above)
advisor_religion_bolt_base_y = [63, 103, 143, 183, 223]

[es=(advisor_religion_window, ui_draw_foreground)]
function advisor_religion_window_ui_draw_foreground(window) {
	if (!game.gods_enabled) {
		return
	}
	var root = window.ui !== undefined ? window.ui : window
	var boltImg = get_image({ pack: PACK_GENERAL, id: 129, offset: 34 })
	var angelImg = get_image({ pack: PACK_GENERAL, id: 129, offset: 33 })
	var boltX = 540
	var rows = advisor_religion_bolt_base_y

	for (var row = 0; row < gods.length; row++) {
		var g = gods[row]
		var p = "god_" + row + "_"
		var gs = city.gods.at(g.type)
		var st = gs.status
		var font = (st === 0) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW

		root[p + "name"].text = __loc(157, g.type)
		root[p + "name"].font = font
		root[p + "known"].text = __loc(187, st)
		root[p + "known"].font = font
		root[p + "desc"].text = __loc(158, g.type)

		root[p + "complex"].text = "-"
		root[p + "temple"].text = "-"
		root[p + "shrine"].text = "-"
		root[p + "fest"].text = "-"
		root[p + "mood"].text = "-"

		if (st === 0) {
			continue
		}

		var bcount = "-"
		if (scenario.building_allowed(g.complex_type)) {
			bcount = String(city.count_active_buildings(g.complex_type))
		}
		var activeTemples = city.count_active_buildings(g.temple_type)
		var totalTemples = city.count_total_buildings(g.temple_type)
		root[p + "complex"].text = bcount
		root[p + "temple"].text = activeTemples + " (" + totalTemples + ")"
		root[p + "shrine"].text = String(city.count_active_buildings(g.shrine_type))
		root[p + "fest"].text = String(gs.months_since_festival)
		root[p + "mood"].text = __loc(59, 20 + ((gs.happiness / 10) | 0))

		var by = rows[row]
		var wrath = gs.wrath_bolts
		var i = 0
		for (i = 0; i < ((wrath / 20) | 0); i++) {
			ui.image(boltImg, { x: boltX + i * 10, y: by })
		}
		var happy = gs.happy_angels
		var j = 0
		for (j = 0; j < ((happy / 20) | 0); j++) {
			ui.image(angelImg, { x: boltX + j * 10, y: by })
		}
	}
}
