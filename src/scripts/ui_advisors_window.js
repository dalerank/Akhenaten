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

function window_advisors_show() {
    window_advisors_prepare_opening()

    var advisor = game.last_advisor
    if (!advisor_window_is_supported(advisor) || !advisor_window_is_available(advisor)) {
        var advisors = advisor_window_supported_list()
        advisor = ADVISOR_NONE
        for (var i = 0; i < advisors.length; i++) {
            var candidate = advisors[i]
            if (advisor_window_is_available(candidate)) {
                advisor = candidate
                break
            }
        }

        if (advisor === ADVISOR_NONE) {
            city.warnings.show("#not_available_in_this_assignment")
            return 0
        }

        game.last_advisor = advisor
    }

    var section = advisor_autoconfig_section(advisor)
    if (!section) {
        city.warnings.show("#not_available_in_this_assignment")
        return 0
    }

    window_show_by_id(section)
    return 1
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

    game.last_advisor = advisor
    return window_advisors_show()
}

advisor_window_base {
    ui {
        advisors_backdrop : image({ pack:PACK_UNLOADED, id:11, pos:[sw(-1024)/2, sh(-768)/2] })
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
    return window_advisors_show()
}

function advisors_toolbar_refresh(window, advisor) {
    game.last_advisor = advisor

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

    if (game.last_advisor === ev.advisor) {
        ui.window_city_show()
    } else {
        window_advisors_show_advisor(ev.advisor)
    }
}
