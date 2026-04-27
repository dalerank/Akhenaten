log_info("akhenaten: sidebar extra started")

var SIDEBAR_EXTRA_DISPLAY_NONE = 0
var SIDEBAR_EXTRA_DISPLAY_GAME_SPEED = 1
var SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT = 2
var SIDEBAR_EXTRA_DISPLAY_RATINGS = 4
var SIDEBAR_EXTRA_DISPLAY_ALL = 7

var EXTRA_INFO_HEIGHT_GAME_SPEED = 64
var EXTRA_INFO_HEIGHT_UNEMPLOYMENT = 48
var EXTRA_INFO_HEIGHT_RATINGS = 176

function sidebar_extra_objective_row(headerEl, currentEl, headerGroup, headerId, current, targetRaw) {
    var t = targetRaw
    if (scenario.is_open_play) {
        t = 0
    }
    headerEl.text = __loc(headerGroup, headerId)
    var met = (t <= 0) || (current >= t)
    currentEl.font = met ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW
    currentEl.text = current + " (" + t + ")"
}

function sidebar_extra_calculate_displayable_info(isCollapsed, sidebarInfoOn, infoRequested, availableHeight) {
    if (isCollapsed || !sidebarInfoOn || infoRequested === SIDEBAR_EXTRA_DISPLAY_NONE) {
        return SIDEBAR_EXTRA_DISPLAY_NONE
    }

    var result = SIDEBAR_EXTRA_DISPLAY_NONE
    var ah = availableHeight

    if (ah >= EXTRA_INFO_HEIGHT_GAME_SPEED) {
        if (infoRequested & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
            ah -= EXTRA_INFO_HEIGHT_GAME_SPEED
            result |= SIDEBAR_EXTRA_DISPLAY_GAME_SPEED
        }
    } else {
        return result
    }

    if (ah >= EXTRA_INFO_HEIGHT_UNEMPLOYMENT) {
        if (infoRequested & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
            ah -= EXTRA_INFO_HEIGHT_UNEMPLOYMENT
            result |= SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT
        }
    } else {
        return result
    }

    if (ah >= EXTRA_INFO_HEIGHT_RATINGS) {
        if (infoRequested & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
            result |= SIDEBAR_EXTRA_DISPLAY_RATINGS
        }
    }
    return result
}

function sidebar_extra_apply_visibility(window, mask) {
    var showSpeed = (mask & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) !== 0
    var showUnemp = (mask & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) !== 0
    var showRatings = (mask & SIDEBAR_EXTRA_DISPLAY_RATINGS) !== 0

    window.dec_speed.enabled = showSpeed
    window.inc_speed.enabled = showSpeed
    window.speed_header.enabled = showSpeed
    window.speed_current.enabled = showSpeed

    window.unemp_header.enabled = showUnemp
    window.unemp_current.enabled = showUnemp

    window.population_header.enabled = showRatings
    window.population_current.enabled = showRatings
    window.culture_header.enabled = showRatings
    window.culture_current.enabled = showRatings
    window.prosperity_header.enabled = showRatings
    window.prosperity_current.enabled = showRatings
    window.monument_header.enabled = showRatings
    window.monument_current.enabled = showRatings
    window.kingdom_header.enabled = showRatings
    window.kingdom_current.enabled = showRatings

    window.extra_background.enabled = mask !== SIDEBAR_EXTRA_DISPLAY_NONE
}

function sidebar_extra_embed_height_px(collapsed, mask) {
    if (collapsed) {
        return 0
    }
    if (mask === SIDEBAR_EXTRA_DISPLAY_NONE) {
        return 0
    }
    var h = 0
    if (mask & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
        h += EXTRA_INFO_HEIGHT_GAME_SPEED
    }
    if (mask & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
        h += EXTRA_INFO_HEIGHT_UNEMPLOYMENT
    }
    if (mask & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
        h += EXTRA_INFO_HEIGHT_RATINGS
    }
    return h
}

[es=(sidebar_window_expanded, ui_draw_extra)]
function sidebar_window_extra_ui_draw_foreground(window) {
    var sidebarOn = !!game_features.gameui_sidebar_info
    var collapsed = window.opened_menu !== 0

    var fullHeight = 0
    if (!collapsed && sidebarOn) {
        fullHeight = EXTRA_INFO_HEIGHT_GAME_SPEED + EXTRA_INFO_HEIGHT_UNEMPLOYMENT + EXTRA_INFO_HEIGHT_RATINGS
    }

    var availableBelow = game.screen.h - window.pos.y - fullHeight
    var mask = sidebar_extra_calculate_displayable_info(collapsed, sidebarOn, SIDEBAR_EXTRA_DISPLAY_ALL, availableBelow)

    sidebar_extra_apply_visibility(window, mask)
    window.extra_background.size.y = sidebar_extra_embed_height_px(collapsed, mask)

    window.speed_current.text = Math.round(game_features.gameopt_game_speed) + "%"
    window.unemp_current.text = city.labor.unemployment_percentage + "% (" + city.workers_diff + ")"

    sidebar_extra_objective_row(window.population_header, window.population_current, 53, 6, city.population, city.winning.population)
    sidebar_extra_objective_row(window.culture_header, window.culture_current, 53, 1, city.rating.culture, city.winning.culture)
    sidebar_extra_objective_row(window.prosperity_header, window.prosperity_current, 53, 2, city.rating.prosperity, city.winning.prosperity)
    sidebar_extra_objective_row(window.monument_header, window.monument_current, 53, 3, city.rating.monument, city.winning.monument)
    sidebar_extra_objective_row(window.kingdom_header, window.kingdom_current, 53, 4, city.rating.kingdom, city.winning.kingdom)
}