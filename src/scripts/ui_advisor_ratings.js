log_info("akhenaten: ui advisor ratings started")

var SELECTED_RATING_CULTURE = 1
var SELECTED_RATING_PROSPERITY = 2
var SELECTED_RATING_MONUMENT = 3
var SELECTED_RATING_KINGDOM = 4

function advisor_ratings_draw_column(basePos, value, openPlay, goal) {
	var enabled = !openPlay && goal
	var hasReached = !enabled || value >= goal
	var valueToDraw = ((value * 0.75) | 0)
	if (game_features.gameui_complete_ratings_columns) {
		if (hasReached && value < 25) {
			valueToDraw = 25
		}
	}
	var imgBase = get_image({ pack: PACK_GENERAL, id: 189, offset: 0 })
	var imgBody = get_image({ pack: PACK_GENERAL, id: 189, offset: 1 })
	var imgTop = get_image({ pack: PACK_GENERAL, id: 189, offset: 2 })
	var px = basePos.x
	var py = basePos.y
	var y = imgBase.height
	ui.image(imgBase, [px - 4, py + y])
	var i
	for (i = 0; i < 2 * valueToDraw; i++) {
		y = y - 1
		ui.image(imgBody, [px + 11, py + y])
	}
	if (hasReached) {
		ui.image(imgTop, [px - 6, py + y - 50])
	}
}

function advisor_ratings_refresh_row(window, id, name, value, openPlay, goal) {
	var enabled = !openPlay && goal
	var btn = window["rating_" + name]
	var valueEl = window["value_" + name]
	var goalEl = window["goal_" + name]
	btn.selected = (advisor_ratings_window.selected === id + 1)
	btn.text = __loc(53, 1 + id)
	valueEl.text = String(value)
	goalEl.text = String(enabled ? goal : 0) + " " + __loc(53, 5)
}

[es=(advisor_ratings_window, select_culture)]
function advisor_ratings_select_culture(window) {
	advisor_ratings_window.selected = SELECTED_RATING_CULTURE
	var expl = city.rating.get_culture_explanation()
	window.advice_header.text = __loc(53, 1)
	window.advice_text.text = (city.rating.culture <= 90) ? __loc(53, 9 + expl) : __loc(53, 50)
}

[es=(advisor_ratings_window, select_prosperity)]
function advisor_ratings_select_prosperity(window) {
	advisor_ratings_window.selected = SELECTED_RATING_PROSPERITY
	var expl = city.rating.get_prosperity_explanation()
	window.advice_header.text = __loc(53, 2)
	window.advice_text.text = (city.rating.prosperity <= 90) ? __loc(53, 16 + expl) : __loc(53, 51)
}

[es=(advisor_ratings_window, select_monument)]
function advisor_ratings_select_monument(window) {
	advisor_ratings_window.selected = SELECTED_RATING_MONUMENT
	var expl = city.rating.get_monument_explanation()
	window.advice_header.text = __loc(53, 3)
	window.advice_text.text = (city.rating.monument <= 90) ? __loc(53, 41 + expl) : __loc(53, 52)
}

[es=(advisor_ratings_window, select_kingdom)]
function advisor_ratings_select_kingdom(window) {
	advisor_ratings_window.selected = SELECTED_RATING_KINGDOM
	var expl = city.rating.get_kingdom_explanation()
	window.advice_header.text = __loc(53, 4)
	window.advice_text.text = (city.rating.kingdom <= 90) ? __loc(53, 27 + expl) : __loc(53, 53)
}

[es=advisor_window]
advisor_ratings_window {
	advisor: ADVISOR_RATINGS
	selected: SELECTED_RATING_CULTURE
	ui {
		background       : outer_panel({size:[40, 27]})
		background_image : image({pack:PACK_UNLOADED, id:2, pos:[60, 38]})
		rating_culture: button({pos:[80, 276], align:"xcenter", size:[120, 60], tooltip:[68, 104], onclick_event: "select_culture",
			ui: {
				value_culture : text({pos:[0, 22], size:[120, 20], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),
				goal_culture  : text({pos:[0, 42], size:[120, 20], align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT}),
			}
		}),
		base_culture  : text({pos:[110, 213], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),

		rating_prosperity: button({pos:[200, 276], align:"xcenter", size:[120, 60], tooltip:[68, 105], onclick_event: "select_prosperity",
			ui: {
				value_prosperity: text({pos:[0, 22], size:[120, 20], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),
				goal_prosperity : text({pos:[0, 42], size:[120, 20], align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT}),
			}
		}),
		base_prosperity : text({pos:[230, 213], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),

		rating_monument: button({pos:[320, 276], align:"xcenter", size:[120, 60], tooltip:[68, 106], onclick_event: "select_monument",
			ui: {
				value_monument: text({pos:[0, 22], size:[120, 20], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),
				goal_monument : text({pos:[0, 42], size:[120, 20], align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT}),
			}
		}),
		base_monument : text({pos:[350, 213], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),

		rating_kingdom: button({pos:[440, 276], align:"xcenter", size:[120, 60], tooltip:[68, 107], onclick_event: "select_kingdom",
			ui: {
				value_kingdom : text({pos:[0, 22], size:[120, 20], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),
				goal_kingdom  : text({pos:[0, 42], size:[120, 20], align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT}),
			}
		}),
		base_kingdom  : text({pos:[470, 213], align:"center", font: FONT_LARGE_BLACK_ON_LIGHT}),

		inner_panel   : inner_panel({pos:[40, 340], size:[35, 5]}),
		advice_header : text({pos:[68, 344], font: FONT_NORMAL_WHITE_ON_DARK}),
		advice_text   : text({pos:[68, 368], wrap:520, font: FONT_NORMAL_WHITE_ON_DARK, multiline:true}),
		advisor_icon  : image({pack:PACK_GENERAL, id:128, offset:3, pos:[10, 10]}),
		header_label  : label({font: FONT_LARGE_BLACK_ON_LIGHT, text:{group:53, id:0}, pos:[60, 17]}),
		population_label : label({pos:[300, 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),
	}
}

[es=(advisor_ratings_window, init)]
function advisor_ratings_window_init(window) {
    advisor_ratings_select_culture(window)

	var winPop = city.winning.population
	var openPlay = scenario.is_open_play
	var caption = __loc(53, 7)
	if (winPop && !openPlay) {
		caption = __loc(53, 6) + String(winPop)
	}
	window.population_label.text = caption

	advisor_ratings_refresh_row(window, 0, "culture", city.rating.culture, openPlay, city.winning.culture)
	advisor_ratings_refresh_row(window, 1, "prosperity", city.rating.prosperity, openPlay, city.winning.prosperity)
	advisor_ratings_refresh_row(window, 2, "monument", city.rating.monument, openPlay, city.winning.monument)
	advisor_ratings_refresh_row(window, 3, "kingdom", city.rating.kingdom, openPlay, city.winning.kingdom)
}

[es=(advisor_ratings_window, draw_background)]
function advisor_ratings_window_draw_background(window) {

}

[es=(advisor_ratings_window, ui_draw_foreground)]
function advisor_ratings_window_ui_draw_foreground(window) {
	var openPlay = scenario.is_open_play
	advisor_ratings_draw_column(window.base_culture.pos, city.rating.culture, openPlay, city.winning.culture)
	advisor_ratings_draw_column(window.base_prosperity.pos, city.rating.prosperity, openPlay, city.winning.prosperity)
	advisor_ratings_draw_column(window.base_monument.pos, city.rating.monument, openPlay, city.winning.monument)
	advisor_ratings_draw_column(window.base_kingdom.pos, city.rating.kingdom, openPlay, city.winning.kingdom)
}
