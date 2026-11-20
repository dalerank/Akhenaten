// Sound effects and music tracks sent from the simulation as events reach the sound manager.

var __t521_ok = false

function t521_fail(msg) {
    __log_info_native('[test:521] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:521] sound events reach the sound manager')

    __test_sound_emit_effect(SOUND_EFFECT_POLICE_ATTACK)
    var effect_line = '[sound] effect ' + SOUND_EFFECT_POLICE_ATTACK + ' -> Wavs/police_atk.wav'
    if (!__test_find_inlog(effect_line)) {
        return t521_fail('effect event not played, missing: ' + effect_line)
    }

    __test_sound_emit_track('plague_frogs')
    if (!__test_find_inlog('[sound] music plague_frogs')) {
        return t521_fail('track event not played, missing: [sound] music plague_frogs')
    }

    __log_marker('sound_events_reach_the_mixer_ok')
    __t521_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t521_ok && __test_find_inlog('[test-marker] sound_events_reach_the_mixer_ok')
}
