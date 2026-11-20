// NU0–NU2: enhanced nilometer helpers (floods_ui_*).
// Markers:
//   [test-marker] nilometer_flag_default_off_ok
//   [test-marker] nilometer_hide_gate_ok
//   [test-marker] nilometer_enhanced_gate_ok
//   [test-marker] nilometer_quality_tiers_ok
//   [test-marker] nilometer_phase_keys_ok
//   [test-marker] nilometer_water_bar_ok

function run_test() {
    __log_info_native('[test:045] nilometer UI helpers')
    test_ensure_city_session('data/default.map')

    var prev_flag = game_features.get('gameui_enhanced_nilometer')
    var prev_hide = scenario.hide_nilometer
    var prev_has_fp = city.floods.has_floodplains
    var prev_state = city.floods.state
    var prev_progress = city.floods.flood_progress
    var prev_q_last = city.floods.quality_last

    function finish() {
        game_features.set('gameui_enhanced_nilometer', prev_flag)
        scenario.hide_nilometer = prev_hide
        city.floods.has_floodplains = prev_has_fp
        city.floods.state = prev_state
        city.floods.flood_progress = prev_progress
        city.floods.quality_last = prev_q_last
        __test_signal_ready()
    }

    function fail(reason) {
        __log_info_native('[test:045] FAIL: ' + reason)
        finish()
    }

    if (game_features.default('gameui_enhanced_nilometer')) {
        fail('flag_default_should_be_off')
        return
    }
    __log_marker('nilometer_flag_default_off_ok')

    city.floods.has_floodplains = true
    scenario.hide_nilometer = true
    if (floods_ui_should_show()) {
        fail('hide_nilometer_should_block_show')
        return
    }
    scenario.hide_nilometer = false
    if (!floods_ui_should_show()) {
        fail('should_show_with_floodplains')
        return
    }
    city.floods.has_floodplains = false
    if (floods_ui_should_show()) {
        fail('no_floodplains_should_hide')
        return
    }
    __log_marker('nilometer_hide_gate_ok')

    city.floods.has_floodplains = true
    game_features.set('gameui_enhanced_nilometer', false)
    if (floods_ui_enhanced_active()) {
        fail('enhanced_off_should_be_inactive')
        return
    }
    game_features.set('gameui_enhanced_nilometer', true)
    if (!floods_ui_enhanced_active()) {
        fail('enhanced_on_should_be_active')
        return
    }
    scenario.hide_nilometer = true
    if (floods_ui_enhanced_active()) {
        fail('enhanced_should_respect_hide')
        return
    }
    scenario.hide_nilometer = false
    __log_marker('nilometer_enhanced_gate_ok')

    if (floods_ui_quality_text_id(100) !== 197
        || floods_ui_quality_text_id(76) !== 196
        || floods_ui_quality_text_id(51) !== 195
        || floods_ui_quality_text_id(26) !== 194
        || floods_ui_quality_text_id(1) !== 193
        || floods_ui_quality_text_id(0) !== 192) {
        fail('quality_text_id_tiers')
        return
    }
    if (floods_ui_quality_font(1) !== FONT_NORMAL_BLACK_ON_DARK
        || floods_ui_quality_font(0) !== FONT_NORMAL_YELLOW) {
        fail('quality_font')
        return
    }
    city.floods.quality_last = 80
    var last = floods_ui_format_last_line()
    if (!last || last.indexOf(__loc('#nilometer_last_prefix')) !== 0) {
        fail('last_line_prefix')
        return
    }
    __log_marker('nilometer_quality_tiers_ok')

    if (floods_ui_phase_key(FLOOD_STATE_IMMINENT) !== '#flood_phase_imminent'
        || floods_ui_phase_key(FLOOD_STATE_FLOODING) !== '#flood_phase_flooding'
        || floods_ui_phase_key(FLOOD_STATE_INUNDATED) !== '#flood_phase_inundated'
        || floods_ui_phase_key(FLOOD_STATE_CONTRACTING) !== '#flood_phase_contracting'
        || floods_ui_phase_key(FLOOD_STATE_RESTING) !== '#flood_phase_resting'
        || floods_ui_phase_key(FLOOD_STATE_FARMABLE) !== '#flood_phase_farmable') {
        fail('phase_keys')
        return
    }
    if (!floods_ui_format_phase(FLOOD_STATE_FARMABLE)) {
        fail('phase_format_empty')
        return
    }
    __log_marker('nilometer_phase_keys_ok')

    city.floods.state = FLOOD_STATE_FARMABLE
    if (floods_ui_show_water_bar()) {
        fail('water_bar_hidden_when_farmable')
        return
    }
    city.floods.state = FLOOD_STATE_FLOODING
    if (!floods_ui_show_water_bar()) {
        fail('water_bar_shown_when_flooding')
        return
    }
    city.floods.flood_progress = 5
    if (floods_ui_water_level() !== 25) {
        fail('water_level_progress_5')
        return
    }
    city.floods.flood_progress = 40
    if (floods_ui_water_level() !== 0) {
        fail('water_level_clamp_high')
        return
    }
    city.floods.flood_progress = -3
    if (floods_ui_water_level() !== 30) {
        fail('water_level_clamp_low')
        return
    }
    __log_marker('nilometer_water_bar_ok')

    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] nilometer_flag_default_off_ok')
        && __test_find_inlog('[test-marker] nilometer_hide_gate_ok')
        && __test_find_inlog('[test-marker] nilometer_enhanced_gate_ok')
        && __test_find_inlog('[test-marker] nilometer_quality_tiers_ok')
        && __test_find_inlog('[test-marker] nilometer_phase_keys_ok')
        && __test_find_inlog('[test-marker] nilometer_water_bar_ok')
}
