log_info("akhenaten: ui advisors window started")

function advisor_autoconfig_section(advisor) {
    switch (advisor) {
        case ADVISOR_LABOR: return "advisor_labors_window"
        case ADVISOR_MILITARY: return "advisor_military_window"
        case ADVISOR_IMPERIAL: return "advisor_imperial_window"
        case ADVISOR_RATINGS: return "advisor_ratings_window"
        case ADVISOR_TRADE: return "advisor_trade_window"
        case ADVISOR_POPULATION: return "advisor_population_window"
        case ADVISOR_HEALTH: return "advisor_health_window"
        case ADVISOR_EDUCATION: return "advisor_education_window"
        case ADVISOR_ENTERTAINMENT: return "advisor_entertainment_window"
        case ADVISOR_RELIGION: return "advisor_religion_window"
        case ADVISOR_FINANCIAL: return "advisor_financial_window"
        case ADVISOR_CHIEF: return "advisor_chief_window"
        case ADVISOR_MONUMENTS: return "advisor_monuments_window"
        case ADVISOR_HOUSING: return "advisor_housing_window"
        default: return null
    }
}

function advisor_window_supported_list() {
    return [
        ADVISOR_LABOR,
        ADVISOR_MILITARY,
        ADVISOR_IMPERIAL,
        ADVISOR_RATINGS,
        ADVISOR_TRADE,
        ADVISOR_POPULATION,
        ADVISOR_HEALTH,
        ADVISOR_EDUCATION,
        ADVISOR_ENTERTAINMENT,
        ADVISOR_RELIGION,
        ADVISOR_FINANCIAL,
        ADVISOR_CHIEF,
        ADVISOR_MONUMENTS,
        ADVISOR_HOUSING
    ]
}

function advisor_window_is_supported(advisor) {
    return advisor_autoconfig_section(advisor) !== null
}

function advisor_window_is_available(advisor) {
    return city.is_advisor_available(advisor) > 0
}

function window_advisors_show_advisor(advisor) {
    if (!advisor_window_is_supported(advisor)) {
        city.warnings.show("#not_available_in_this_assignment")
        return 0
    }

    var avail = city.is_advisor_available(advisor)
    if (avail === 0 || avail === -1) {
        city.warnings.show(avail === 0 ? "#not_available_in_this_assignment" : "#not_available_yet")
        return 0
    }
    window_advisors_prepare_opening()
    __game_settings.last_advisor = advisor
    window_advisors_show()
    return 1
}

var ADVISOR_BACKGROUND_MODE = "cover" // "cover", "contain", "original"
var ADVISOR_BACKGROUND_BLURRED_BACKDROP = false

advisor_window_base {
    ui {
        advisors_backdrop : background({
            pack:PACK_UNLOADED,
            id:11,
            mode:ADVISOR_BACKGROUND_MODE,
            backdrop_cover_blur:ADVISOR_BACKGROUND_BLURRED_BACKDROP,
            backdrop_blur_radius:12,
            backdrop_blur_alpha:255,
            backdrop_shade_alpha:112,
            fill_width:true,
            fill_height:true
        })
        advisors_strip    : image({ pack:PACK_GENERAL, id:160, pos:[sw(-640)/2, sh(400)/2] })
        labor_btn         : image_button({ pos:[sw(-640)/2 + 12, sh(418)/2], size:[33, 32], pack:PACK_GENERAL, id:159, offset:0, tooltip:[68, 71], onclick: show_advisor_window(ADVISOR_LABOR) })
        military_btn      : image_button({ pos:[sw(-640)/2 + 52, sh(418)/2], size:[39, 32], pack:PACK_GENERAL, id:159, offset:4, tooltip:[68, 72], onclick: show_advisor_window(ADVISOR_MILITARY) })
        imperial_btn      : image_button({ pos:[sw(-640)/2 + 96, sh(418)/2], size:[34, 32], pack:PACK_GENERAL, id:159, offset:8, tooltip:[68, 73], onclick: show_advisor_window(ADVISOR_IMPERIAL) })
        ratings_btn       : image_button({ pos:[sw(-640)/2 + 135, sh(418)/2], size:[38, 32], pack:PACK_GENERAL, id:159, offset:12, tooltip:[68, 74], onclick: show_advisor_window(ADVISOR_RATINGS) })
        trade_btn         : image_button({ pos:[sw(-640)/2 + 178, sh(418)/2], size:[46, 32], pack:PACK_GENERAL, id:159, offset:16, tooltip:[68, 75], onclick: show_advisor_window(ADVISOR_TRADE) })
        population_btn    : image_button({ pos:[sw(-640)/2 + 229, sh(418)/2], size:[48, 32], pack:PACK_GENERAL, id:159, offset:20, tooltip:[68, 76], onclick: show_advisor_window(ADVISOR_POPULATION) })
        health_btn        : image_button({ pos:[sw(-640)/2 + 282, sh(418)/2], size:[35, 32], pack:PACK_GENERAL, id:159, offset:24, tooltip:[68, 77], onclick: show_advisor_window(ADVISOR_HEALTH) })
        education_btn     : image_button({ pos:[sw(-640)/2 + 322, sh(418)/2], size:[38, 32], pack:PACK_GENERAL, id:159, offset:28, tooltip:[68, 78], onclick: show_advisor_window(ADVISOR_EDUCATION) })
        entertainment_btn : image_button({ pos:[sw(-640)/2 + 363, sh(418)/2], size:[39, 32], pack:PACK_GENERAL, id:159, offset:32, tooltip:[68, 79], onclick: show_advisor_window(ADVISOR_ENTERTAINMENT) })
        religion_btn      : image_button({ pos:[sw(-640)/2 + 406, sh(418)/2], size:[35, 32], pack:PACK_GENERAL, id:159, offset:36, tooltip:[68, 80], onclick: show_advisor_window(ADVISOR_RELIGION) })
        financial_btn     : image_button({ pos:[sw(-640)/2 + 445, sh(418)/2], size:[40, 32], pack:PACK_GENERAL, id:159, offset:40, tooltip:[68, 81], onclick: show_advisor_window(ADVISOR_FINANCIAL) })
        chief_btn         : image_button({ pos:[sw(-640)/2 + 490, sh(418)/2], size:[46, 32], pack:PACK_GENERAL, id:159, offset:44, tooltip:[68, 82], onclick: show_advisor_window(ADVISOR_CHIEF) })
        monuments_btn     : image_button({ pos:[sw(-640)/2 + 542, sh(418)/2], size:[40, 32], pack:PACK_GENERAL, id:159, offset:48, tooltip:[68, 83], onclick: show_advisor_window(ADVISOR_MONUMENTS) })
        back_btn          : image_button({ pos:[sw(-640)/2 + 588, sh(418)/2], size:[40, 32], pack:PACK_GENERAL, id:159, offset:52, tooltip:[68, 84], onclick: ui.window_city_show })
    }
}

function show_advisor_window(advisor) {
    return function() {
        if (!advisor_window_is_supported(advisor)) {
            city.warnings.show("#not_available_in_this_assignment")
            return 0
        }

        window_advisors_show_advisor(advisor)
    }
}

function window_advisors_show_checked() {
    var last = __game_settings.last_advisor
    if (advisor_window_is_supported(last) && advisor_window_is_available(last)) {
        return window_advisors_show_advisor(last)
    }

    var advisors = advisor_window_supported_list()
    for (var i = 0; i < advisors.length; i++) {
        var adv = advisors[i]
        if (advisor_window_is_available(adv)) {
            return window_advisors_show_advisor(adv)
        }
    }

    city.warnings.show("#not_available_in_this_assignment")
}

function advisor_window_reflow(window) {
    if (!window) {
        return
    }

    var frameX = ((screen.width - px(40)) / 2) | 0
    var frameY = ((screen.height - px(30)) / 2) | 0

    if (window.advisor_area) {
        window.advisor_area.pos = { x: frameX, y: frameY }
    }

    if (window.advisors_strip) {
        window.advisors_strip.pos = { x: frameX, y: frameY + 440 }
    }

    function set_toolbar_pos(id, dx) {
        if (window[id]) {
            window[id].pos = { x: frameX + dx, y: frameY + 449 }
        }
    }

    set_toolbar_pos("labor_btn", 12)
    set_toolbar_pos("military_btn", 52)
    set_toolbar_pos("imperial_btn", 96)
    set_toolbar_pos("ratings_btn", 135)
    set_toolbar_pos("trade_btn", 178)
    set_toolbar_pos("population_btn", 229)
    set_toolbar_pos("health_btn", 282)
    set_toolbar_pos("education_btn", 322)
    set_toolbar_pos("entertainment_btn", 363)
    set_toolbar_pos("religion_btn", 406)
    set_toolbar_pos("financial_btn", 445)
    set_toolbar_pos("chief_btn", 490)
    set_toolbar_pos("monuments_btn", 542)
    set_toolbar_pos("back_btn", 588)
}

function advisors_toolbar_refresh(window, advisor) {
    advisor_window_reflow(window)
    __game_settings.last_advisor = advisor

    window.labor_btn.selected = (ADVISOR_LABOR == advisor)
    window.military_btn.selected = (ADVISOR_MILITARY == advisor)
    window.imperial_btn.selected = (ADVISOR_IMPERIAL == advisor)
    window.ratings_btn.selected = (ADVISOR_RATINGS == advisor)
    window.trade_btn.selected = (ADVISOR_TRADE == advisor)
    window.population_btn.selected = (ADVISOR_POPULATION == advisor)
    window.health_btn.selected = (ADVISOR_HEALTH == advisor)
    window.education_btn.selected = (ADVISOR_EDUCATION == advisor)
    window.entertainment_btn.selected = (ADVISOR_ENTERTAINMENT == advisor)
    window.religion_btn.selected = (ADVISOR_RELIGION == advisor)
    window.financial_btn.selected = (ADVISOR_FINANCIAL == advisor)
    window.chief_btn.selected = (ADVISOR_CHIEF == advisor)
    window.monuments_btn.selected = (ADVISOR_MONUMENTS == advisor)

    window.labor_btn.readonly = !advisor_window_is_available(ADVISOR_LABOR)
    window.military_btn.readonly = !advisor_window_is_available(ADVISOR_MILITARY)
    window.imperial_btn.readonly = !advisor_window_is_available(ADVISOR_IMPERIAL)
    window.ratings_btn.readonly = !advisor_window_is_available(ADVISOR_RATINGS)
    window.trade_btn.readonly = !advisor_window_is_available(ADVISOR_TRADE)
    window.population_btn.readonly = !advisor_window_is_available(ADVISOR_POPULATION)
    window.health_btn.readonly = !advisor_window_is_available(ADVISOR_HEALTH)
    window.education_btn.readonly = !advisor_window_is_available(ADVISOR_EDUCATION)
    window.entertainment_btn.readonly = !advisor_window_is_available(ADVISOR_ENTERTAINMENT)
    window.religion_btn.readonly = !advisor_window_is_available(ADVISOR_RELIGION)
    window.financial_btn.readonly = !advisor_window_is_available(ADVISOR_FINANCIAL)
    window.chief_btn.readonly = !advisor_window_is_available(ADVISOR_CHIEF)
    window.monuments_btn.readonly = !advisor_window_is_available(ADVISOR_MONUMENTS)

    window.back_btn.enabled = true
}

[es=event_show_advisor]
function on_event_show_advisor_hotkey(ev) {
    if (ui.window_is("window_city")) {
        window_advisors_show_advisor(ev.advisor)
        return
    }

    if (__game_settings.last_advisor === ev.advisor) {
        ui.window_city_show()
    } else {
        window_advisors_show_advisor(ev.advisor)
    }
}
