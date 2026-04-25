log_info("akhenaten: ui sound options window started")

var SOUND_CHANNEL_EFFECTS_MIN = 2
var SOUND_CHANNEL_EFFECTS_MAX = 44
var SOUND_CHANNEL_CITY_MIN = 45
var SOUND_CHANNEL_CITY_MAX = 148

function sound_options_on_cancel() {
    var w = sound_options_window

    game_features.gameopt_sound_effects_enabled = !!w.orig_effects_en
    game_features.gameopt_sound_effects_volume = w.orig_effects_vol;
    game_features.gameopt_sound_music_enabled = !!w.orig_music_en
    game_features.gameopt_sound_music_volume = w.orig_music_vol
    game_features.gameopt_sound_speech_enabled = !!w.orig_speech_en
    game_features.gameopt_sound_speech_volume = w.orig_speech_vol
    game_features.gameopt_sound_city_enabled = !!w.orig_city_en
    game_features.gameopt_sound_city_volume = w.orig_city_vol
    if (w.orig_music_en) {
        if ((game_features.gameopt_sound_music_enabled ? 1 : 0) != w.orig_music_en) {
            __game_sound.music_update(1)
        }
    } else {
        __game_sound.music_stop()
    }

    window_go_back()
}

function sound_options_toggle_music() {
    game_features.gameopt_sound_music_enabled = !game_features.gameopt_sound_music_enabled
    if (game_features.gameopt_sound_music_enabled) {
        __game_sound.music_update(1)
    } else {
        __game_sound.music_stop()
    }
}

function sound_options_toggle_speech() {
    game_features.gameopt_sound_speech_enabled = !game_features.gameopt_sound_speech_enabled
    if (!game_features.gameopt_sound_speech_enabled) {
        __game_sound.speech_stop()
    }
}

function sound_options_toggle_effects() {
    game_features.gameopt_sound_effects_enabled = !game_features.gameopt_sound_effects_enabled
}

function sound_options_toggle_city() {
    game_features.gameopt_sound_city_enabled = !game_features.gameopt_sound_city_enabled
}

function sound_options_effects_step(delta) {
    var v = game_features.gameopt_sound_effects_volume + delta
    game_features.gameopt_sound_effects_volume = v
}

function sound_options_music_step(delta) {
    var v = game_features.gameopt_sound_music_volume + delta
    game_features.gameopt_sound_music_volume = v
}

function sound_options_speech_step(delta) {
    var v = game_features.gameopt_sound_speech_volume + delta
    game_features.gameopt_sound_speech_volume = v
}

function sound_options_city_step(delta) {
    var v = game_features.gameopt_sound_city_volume + delta
    game_features.gameopt_sound_city_volume = v
}

[es=(sound_options_window, init)]
function sound_options_window_es_init(window) {
    var w = sound_options_window
    w.orig_effects_en = game_features.gameopt_sound_effects_enabled ? 1 : 0
    w.orig_effects_vol = game_features.gameopt_sound_effects_volume
    w.orig_music_en = game_features.gameopt_sound_music_enabled ? 1 : 0
    w.orig_music_vol = game_features.gameopt_sound_music_volume
    w.orig_speech_en = game_features.gameopt_sound_speech_enabled ? 1 : 0
    w.orig_speech_vol = game_features.gameopt_sound_speech_volume
    w.orig_city_en = game_features.gameopt_sound_city_enabled ? 1 : 0
    w.orig_city_vol = game_features.gameopt_sound_city_volume
}

[es=(sound_options_window, ui_draw_foreground)]
function sound_options_window_es_draw(window) {
    window.btn_music.text = __loc(46, game_features.gameopt_sound_music_enabled ? 2 : 1)
    window.music_pct.text = String(Math.round(game_features.gameopt_sound_music_volume)) + "%"
    window.btn_speech.text = __loc(46, game_features.gameopt_sound_speech_enabled ? 4 : 3)
    window.speech_pct.text = String(Math.round(game_features.gameopt_sound_speech_volume)) + "%"
    window.btn_effects.text = __loc(46, game_features.gameopt_sound_effects_enabled ? 6 : 5)
    window.effects_pct.text = String(Math.round(game_features.gameopt_sound_effects_volume)) + "%"
    window.btn_city.text = __loc(46, game_features.gameopt_sound_city_enabled ? 8 : 7)
    window.city_pct.text = String(Math.round(game_features.gameopt_sound_city_volume)) + "%"
}

[es=modal_window]
sound_options_window {
    allow_rmb_goback : true
    draw_underlying : true
    pos [(sw(0) - px(24))/2, (sh(0) - px(18))/2]

    orig_effects_en : 0
    orig_effects_vol : 0
    orig_music_en : 0
    orig_music_vol : 0
    orig_speech_en : 0
    orig_speech_vol : 0
    orig_city_en : 0
    orig_city_vol : 0

    ui {
        background         : outer_panel({size[24, 18]})
        title              : header({pos[10, 10], size[px(24), 20], text[46, 0], align:"center"})

        arrow_music_down   : arrowdown({pos[264, 68], tiny:false, allow_repeat: true
                                        onclick: function() { sound_options_music_step(-1) } })
        arrow_music_up     : arrowup({pos[288, 68], tiny:false, allow_repeat: true
                                        onclick: function() { sound_options_music_step(1) } })

        arrow_speech_down  : arrowdown({pos[264, 98], tiny:false
                                        onclick: function() { sound_options_speech_step(-1) } })
        arrow_speech_up    : arrowup({pos[288, 98], tiny:false
                                         onclick: function() { sound_options_speech_step(1) } })

        arrow_effects_down : arrowdown({pos[264, 128], tiny:false
                                         onclick: function() { sound_options_effects_step(-1) } })
        arrow_effects_up   : arrowup({pos[288, 128], tiny:false
                                        onclick: function() { sound_options_effects_step(1) } })

        arrow_city_down    : arrowdown({pos[264, 158], tiny:false
                                        onclick: function() { sound_options_city_step(-1) } })
        arrow_city_up      : arrowup({pos[288, 158], tiny:false
                                        onclick: function() { sound_options_city_step(1) } })

        lbl_quiet          : text({pos[16, 48], text[46, 10], font: FONT_SMALL_PLAIN})
        lbl_loud           : text({pos[280, 48], text[46, 11], font: FONT_SMALL_PLAIN})

        btn_music          : button({pos[16,68], size[224, 20], font: FONT_NORMAL_BLACK_ON_DARK
                                     onclick: function() { sound_options_toggle_music() } })
        music_pct          : text({pos[326, 72], font: FONT_SMALL_PLAIN})
        btn_speech         : button({pos[16, 98], size[224, 20], font: FONT_NORMAL_BLACK_ON_DARK
                                     onclick: function() { sound_options_toggle_speech() } })
        speech_pct         : text({pos[326, 102], font: FONT_SMALL_PLAIN})
        btn_effects        : button({pos[16, 128], size[224, 20], font: FONT_NORMAL_BLACK_ON_DARK
                                     onclick: function() { sound_options_toggle_effects() } })
        effects_pct        : text({pos[326, 132], font: FONT_SMALL_PLAIN})
        btn_city           : button({pos[16, 158], size[224, 20], font: FONT_NORMAL_BLACK_ON_DARK
                                     onclick: function() { sound_options_toggle_city() } })
        city_pct           : text({pos[326, 162], font: FONT_SMALL_PLAIN})

        btnok              : ok_button({margin{left:px(24)/2 - 40, bottom:-40}, onclick: window_go_back })
        btncancel          : cancel_button({margin{left:px(24)/2 + 20, bottom:-40}, onclick: sound_options_on_cancel })
    }
}
