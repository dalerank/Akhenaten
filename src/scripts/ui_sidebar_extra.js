log_info("akhenaten: sidebar extra started")

var SIDEBAR_EXTRA_DISPLAY_NONE = 0
var SIDEBAR_EXTRA_DISPLAY_GAME_SPEED = 1
var SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT = 2
var SIDEBAR_EXTRA_DISPLAY_RATINGS = 4
var SIDEBAR_EXTRA_DISPLAY_ALL = 7

var EXTRA_INFO_HEIGHT_GAME_SPEED = 64
var EXTRA_INFO_HEIGHT_UNEMPLOYMENT = 48
var EXTRA_INFO_HEIGHT_RATINGS = 176
var EXTRA_INFO_HEIGHT_NILOMETER = 36
// Must match extra_background / first extra widget Y in ui_sidebar_window.js.
var SIDEBAR_EXTRA_START_Y = 480

var sidebar_extra_nilometer_cache = { state: -1, quality: -1, progress: -1 }

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

    // Always keep game speed (minimal strip) even when the logical viewport is
    // shorter than EXTRA_INFO_HEIGHT_GAME_SPEED — common with high Android UI scale.
    if (infoRequested & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
        result |= SIDEBAR_EXTRA_DISPLAY_GAME_SPEED
        ah -= EXTRA_INFO_HEIGHT_GAME_SPEED
    }

    if (ah >= EXTRA_INFO_HEIGHT_UNEMPLOYMENT && (infoRequested & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT)) {
        ah -= EXTRA_INFO_HEIGHT_UNEMPLOYMENT
        result |= SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT
    }

    if (ah >= EXTRA_INFO_HEIGHT_RATINGS && (infoRequested & SIDEBAR_EXTRA_DISPLAY_RATINGS)) {
        result |= SIDEBAR_EXTRA_DISPLAY_RATINGS
    }
    return result
}

function sidebar_extra_set_pos(el, x, y) {
    if (!el) {
        return
    }
    el.pos = { x: x, y: y }
}

function sidebar_extra_apply_nilometer_offsets(window, niloOn) {
    var dy = niloOn ? EXTRA_INFO_HEIGHT_NILOMETER : 0
    var base = SIDEBAR_EXTRA_START_Y

    sidebar_extra_set_pos(window.nilometer_quality, 11, base + 5)
    sidebar_extra_set_pos(window.nilometer_phase, 11, base + 21)

    sidebar_extra_set_pos(window.speed_header, 11, base + 5 + dy)
    sidebar_extra_set_pos(window.speed_current, 65, base + 28 + dy)
    sidebar_extra_set_pos(window.dec_speed, 11, base - 10 + 30 + dy)
    sidebar_extra_set_pos(window.inc_speed, 35, base - 10 + 30 + dy)

    sidebar_extra_set_pos(window.unemp_header, 11, base + 50 + dy)
    sidebar_extra_set_pos(window.unemp_current, 11, base + 70 + dy)

    sidebar_extra_set_pos(window.population_header, 11, base + 90 + dy)
    sidebar_extra_set_pos(window.population_current, 11, base + 110 + dy)

    sidebar_extra_set_pos(window.culture_header, 11, base + 130 + dy)
    sidebar_extra_set_pos(window.culture_current, 11, base + 150 + dy)

    sidebar_extra_set_pos(window.prosperity_header, 11, base + 170 + dy)
    sidebar_extra_set_pos(window.prosperity_current, 11, base + 190 + dy)

    sidebar_extra_set_pos(window.monument_header, 11, base + 210 + dy)
    sidebar_extra_set_pos(window.monument_current, 11, base + 230 + dy)

    sidebar_extra_set_pos(window.kingdom_header, 11, base + 250 + dy)
    sidebar_extra_set_pos(window.kingdom_current, 11, base + 270 + dy)

    sidebar_extra_set_pos(window.report_bug, 114, base + 258 + dy)
}

function sidebar_extra_apply_visibility(window, mask, niloOn) {
    var showSpeed = (mask & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) !== 0
    var showUnemp = (mask & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) !== 0
    var showRatings = (mask & SIDEBAR_EXTRA_DISPLAY_RATINGS) !== 0

    if (window.nilometer_quality) {
        window.nilometer_quality.enabled = niloOn
    }
    if (window.nilometer_phase) {
        window.nilometer_phase.enabled = niloOn
    }

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

    window.extra_background.enabled = niloOn || mask !== SIDEBAR_EXTRA_DISPLAY_NONE
}

function sidebar_extra_embed_height_px(collapsed, mask, niloOn) {
    if (collapsed) {
        return 0
    }
    var h = 0
    if (niloOn) {
        h += EXTRA_INFO_HEIGHT_NILOMETER
    }
    if (mask === SIDEBAR_EXTRA_DISPLAY_NONE && !niloOn) {
        return 0
    }
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

function sidebar_extra_update_nilometer(window, niloOn) {
    if (!niloOn || !window.nilometer_quality || !window.nilometer_phase) {
        sidebar_extra_nilometer_cache.state = -1
        sidebar_extra_nilometer_cache.quality = -1
        sidebar_extra_nilometer_cache.progress = -1
        return
    }

    var state = city.floods.state
    var quality = city.floods.expected_quality()
    var progress = city.floods.flood_progress
    var cache = sidebar_extra_nilometer_cache
    if (cache.state === state && cache.quality === quality && cache.progress === progress) {
        return
    }
    cache.state = state
    cache.quality = quality
    cache.progress = progress

    window.nilometer_quality.text = floods_ui_format_next_line(quality)
    window.nilometer_phase.text = floods_ui_format_phase(state)
    if (floods_ui_show_water_bar(state)) {
        window.nilometer_phase.text += " (" + floods_ui_water_level(progress) + "/30)"
    }
}

[es=(sidebar_window_expanded, ui_draw_extra)]
function sidebar_window_extra_ui_draw_foreground(window) {
    var sidebarOn = !!game_features.gameui_sidebar_info
    var collapsed = false
    var niloOn = floods_ui_enhanced_active()

    // Space from the extra strip start to the bottom of the screen. Nilometer
    // takes its own slice first; the rest is the speed/unemp/ratings ladder.
    var ladderBudget = screen.height - window.pos.y - SIDEBAR_EXTRA_START_Y
    if (ladderBudget < 0) {
        ladderBudget = 0
    }
    if (niloOn) {
        ladderBudget -= EXTRA_INFO_HEIGHT_NILOMETER
        if (ladderBudget < 0) {
            ladderBudget = 0
        }
    }
    var mask = sidebar_extra_calculate_displayable_info(collapsed, sidebarOn, SIDEBAR_EXTRA_DISPLAY_ALL, ladderBudget)

    sidebar_extra_apply_nilometer_offsets(window, niloOn)
    sidebar_extra_apply_visibility(window, mask, niloOn)
    // einner_panel size is in 16px blocks. Assign whole vec2i — `size.y = n` only
    // mutates the temporary from proxy_get_size and never calls proxy_set_size.
    var embedPx = sidebar_extra_embed_height_px(collapsed, mask, niloOn)
    var blocksY = embedPx > 0 ? ((embedPx + 15) >> 4) : 0
    window.extra_background.size = { x: 10, y: blocksY }

    sidebar_extra_update_nilometer(window, niloOn)

    window.speed_current.text = Math.round(game_features.gameopt_game_speed) + "%"
    window.unemp_current.text = city.labor.unemployment_percentage + "% (" + city.workers_diff + ")"

    sidebar_extra_objective_row(window.population_header, window.population_current, 53, 6, city.population, city.winning.population.goal)
    sidebar_extra_objective_row(window.culture_header, window.culture_current, 53, 1, city.rating.culture, city.winning.culture.goal)
    sidebar_extra_objective_row(window.prosperity_header, window.prosperity_current, 53, 2, city.rating.prosperity, city.winning.prosperity.goal)
    sidebar_extra_objective_row(window.monument_header, window.monument_current, 53, 3, city.rating.monument, city.winning.monuments.goal)
    sidebar_extra_objective_row(window.kingdom_header, window.kingdom_current, 53, 4, city.rating.kingdom, city.winning.kingdom.goal)
}
