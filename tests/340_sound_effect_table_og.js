// play_effect maps the Caesar III effect ids the call sites use onto OG's effect and figure sound tables
// (effect.c) and plays them on an effects channel (2..44), never on the effect number as a channel: effect
// 45/46 used to land on the house city channels. Checked through the "[sound] effect" log lines, which are
// written under --integraltests with or without audio hardware or Pharaoh data.

var __t340_ok = false

var T340_EFFECTS = [
    // [effect, expected log tail]
    [5, 'og effect 17 Wavs/crash.wav'],          // SOUND_EFFECT_EXPLOSION -> BUILDING_DESTROYED
    [6, 'og effect 9 Wavs/fanfare1.wav'],        // SOUND_EFFECT_FANFARE -> MESSAGE
    [7, 'og effect 9 Wavs/fanfare1.wav'],        // SOUND_EFFECT_FANFARE_URGENT -> MESSAGE, as OG message.c
    [3, 'og effect 0 Wavs/button.wav'],          // SOUND_EFFECT_ICON
    [2, 'og effect 6 Wavs/menu.wav'],            // SOUND_EFFECT_SIDEBAR
    [43, 'og effect 18 Wavs/fire.wav'],          // SOUND_EFFECT_FIRE_SPLASH
    [8, 'og figure 11.2 Wavs/arch_atk.wav'],     // SOUND_EFFECT_ARROW -> archer hit
    [32, 'og figure 21.3 Wavs/die1.wav'],        // SOUND_EFFECT_SOLDIER_DIE
    [39, 'og figure 28.3 Wavs/die8.wav'],        // SOUND_EFFECT_CITIZEN_DIE + 3
]

var T340_SILENT = [45, 46, 25] // DANCER_DIE, FLOODED, MARCHING: no OG sound

function t340_fail(msg) {
    __log_info_native('[test:340] FAIL: ' + msg)
    return false
}

function t340_check() {
    for (var i = 0; i < T340_EFFECTS.length; i++) {
        var effect = T340_EFFECTS[i][0]
        var channel = __test_sound_play_effect(effect)
        if (channel < 2 || channel > 44) {
            return t340_fail('effect ' + effect + ' picked channel ' + channel + ', not an effects channel')
        }
        var line = '[sound] effect ' + effect + ' -> ' + T340_EFFECTS[i][1] + ' channel ' + channel
        if (!__test_find_inlog(line)) {
            return t340_fail('missing log line: ' + line)
        }
    }

    for (var j = 0; j < T340_SILENT.length; j++) {
        var silent = T340_SILENT[j]
        if (__test_sound_play_effect(silent) != -1) {
            return t340_fail('effect ' + silent + ' should be silent')
        }
        if (!__test_find_inlog('[sound] effect ' + silent + ' -> silent')) {
            return t340_fail('missing silent log line for effect ' + silent)
        }
    }

    game_features.set('gameopt_sound_effects_enabled', false)
    var off = __test_sound_play_effect(5)
    game_features.set('gameopt_sound_effects_enabled', true)
    if (off != -1) {
        return t340_fail('effects disabled still picked channel ' + off)
    }
    return true
}

function run_test() {
    __log_info_native('[test:340] OG sound effect table')
    test_reload_city_session('data/default.map')

    var effects_prev = game_features.get('gameopt_sound_effects_enabled') === true
    game_features.set('gameopt_sound_effects_enabled', true)
    var ok = t340_check()
    game_features.set('gameopt_sound_effects_enabled', effects_prev)

    if (ok) {
        __log_marker('sound_effect_table_ok')
    }
    __t340_ok = ok
    __test_signal_ready()
}

function check_valid() {
    return __t340_ok && __test_find_inlog('sound_effect_table_ok')
}
