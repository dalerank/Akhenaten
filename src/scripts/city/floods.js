log_info("akhenaten: city floods started")

city.floods = extend(__city_floods, {
    state_is: function(state) {
        return this.state == state
    },

    expected_quality: __city_floods_expected_quality,
    expected_month: __city_floods_expected_month,
})

// Shared nilometer / flood UI formatters (NU0). Quality tiers match Chief Advisor
// (`>` thresholds), not the yearly popup (`>=`).

function floods_ui_should_show() {
    if (scenario.hide_nilometer) {
        return false
    }
    return !!city.floods.has_floodplains
}

function floods_ui_enhanced_active() {
    return !!game_features.gameui_enhanced_nilometer && floods_ui_should_show()
}

function floods_ui_quality_text_id(q) {
    if (q === 100) {
        return 197
    }
    if (q > 75) {
        return 196
    }
    if (q > 50) {
        return 195
    }
    if (q > 25) {
        return 194
    }
    if (q > 0) {
        return 193
    }
    return 192
}

function floods_ui_quality_font(q) {
    return (q > 0) ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW
}

function floods_ui_format_next_line(quality, month) {
    var q = (quality !== undefined && quality !== null) ? quality : city.floods.expected_quality()
    var text = __loc(61, floods_ui_quality_text_id(q))
    if (q > 0) {
        var m = (month !== undefined && month !== null) ? month : city.floods.expected_month()
        text += " " + __loc(61, 204 + m)
    }
    return text
}

// Nilometer expected_month is early/late Jun–Sep half-index (0–7).
function floods_expected_half_month(month_half) {
    var m = (month_half !== undefined && month_half !== null) ? month_half : city.floods.expected_month()
    if (m < 0) {
        return 0
    }
    if (m > 7) {
        return 7
    }
    return m | 0
}

// Farm flood_info uses plain calendar months (group 160), same as OG / #572.
// Half 0–1→June … 6–7→September.
function floods_ui_format_farm_flood_month(month_half) {
    var half = floods_expected_half_month(month_half)
    var month = 5 + Math.floor(half / 2)
    return __loc(160, month)
}

function floods_ui_phase_key(state) {
    var s = (state !== undefined && state !== null) ? state : city.floods.state
    if (s == FLOOD_STATE_IMMINENT) {
        return "#flood_phase_imminent"
    }
    if (s == FLOOD_STATE_FLOODING) {
        return "#flood_phase_flooding"
    }
    if (s == FLOOD_STATE_INUNDATED) {
        return "#flood_phase_inundated"
    }
    if (s == FLOOD_STATE_CONTRACTING) {
        return "#flood_phase_contracting"
    }
    if (s == FLOOD_STATE_RESTING) {
        return "#flood_phase_resting"
    }
    return "#flood_phase_farmable"
}

function floods_ui_format_phase(state) {
    return __loc(floods_ui_phase_key(state))
}

function floods_ui_format_last_line(quality) {
    var q = (quality !== undefined && quality !== null) ? quality : city.floods.quality_last
    return __loc("#nilometer_last_prefix") + " " + __loc(61, floods_ui_quality_text_id(q))
}

function floods_ui_water_level(progress) {
    var p = (progress !== undefined && progress !== null) ? progress : city.floods.flood_progress
    if (p < 0) {
        p = 0
    }
    if (p > 30) {
        p = 30
    }
    return 30 - p
}

function floods_ui_show_water_bar(state) {
    var s = (state !== undefined && state !== null) ? state : city.floods.state
    return s == FLOOD_STATE_FLOODING || s == FLOOD_STATE_INUNDATED || s == FLOOD_STATE_CONTRACTING
}
