log_info("akhenaten: window features started")

var FEATURES_PER_PAGE = 14

function wposbtn(i) { return { x: 32, y: 72 + i * 25} }
function wpostxt(i) { return { x: 64, y: 78 + i * 25} }

// ---- State management ----

function window_features_build_pages() {
    var pages = []

    // Gameplay/UI features (bool type only), FEATURES_PER_PAGE per page
    var pf = []
    var n = game_features.count
    for (var i = 0; i < n; i++) {
        var name = game_features.name(i)
        var val = game_features.get(name)

        if (typeof val !== "boolean")
            continue

        var text = game_features.text(name)
        if (!text)
            continue

        ;(function (fname, fidx, fval, ftext) {
            pf.push({
                text: ftext
                original: fval
                type: "game_feature"
                key: fname
                is_enabled : function () { return game_features.get(fname) === true }
                toggle: function (p1, p2) {
                    game_features.set(fname, !game_features.get(fname))
                    window_features.needs_rebuild = true
                }
                reset: function () { game_features.set(fname, fval) }
            })
        })(name, i, val, text)

        if (pf.length >= FEATURES_PER_PAGE) {
            pages.push({title: "#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", features: pf})
            pf = []
        }
    }

    if (pf.length > 0) {
        pages.push({title: "#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", features: pf})
    }

    // Scenario env
    if (game.session_active) {
        var sc_orig_animals = scenario.has_animals
        var sc_orig_flotsam = scenario.flotsam_enabled
        pages.push({
            title: "#TR_CONFIG_HEADER_SCENARIO_CHANGES",
            features: [
                {
                    text: "#TR_CONFIG_ANIMALS"
                    original: sc_orig_animals
                    type: "scenario_animals"
                    is_enabled : function () { return scenario.has_animals }
                    toggle: function (p1, p2) {
                        scenario.has_animals = !scenario.has_animals;
                        window_features.needs_rebuild = true
                    }
                    reset: function () { scenario.has_animals = sc_orig_animals }
                },
                {
                    text: "#TR_CONFIG_FLOTSAM"
                    original: sc_orig_flotsam

                    type: "scenario_flotsam"
                    is_enabled : function () { return scenario.flotsam_enabled }
                    toggle: function (p1, p2) {
                        scenario.flotsam_enabled = !scenario.flotsam_enabled;
                        window_features.needs_rebuild = true
                    }
                    reset: function () { scenario.flotsam_enabled = sc_orig_flotsam }
                }
            ]
        })
    }

    // Gods
    if (game.session_active) {
        var gf = []
        for (var i = 0; i < 5; i++) {
            ;(function (godIdx) {
                var godOrig = city.gods.is_known(godIdx)
                gf.push({
                    text: "God Enabled " + city.gods.get_name(godIdx)
                    key: godIdx
                    original: godOrig
                    type: "god"
                    is_enabled : function () { return city.gods.is_known(godIdx) }
                    toggle: function (p1, p2) {
                        city.gods.set_known(godIdx, !city.gods.is_known(godIdx));
                        window_features.needs_rebuild = true
                    }
                    reset: function () { city.gods.set_known(godIdx, godOrig) }
                })
            })(i)
        }
        pages.push({title: "#TR_CONFIG_HEADER_GODS_CHANGES", features: gf})
    }

    // Resources (city session only — no loaded city from main menu)
    if (game.session_active) {
        var rf = []
        var n_res = city.resources.count
        for (var i = 0; i < n_res; i++) {
            ;(function (res) {
                var resOrig = city.resources.can_produce(res)
                rf.push({
                    text: "City allow " + city.resources.get_name(res)
                    original: resOrig
                    type: "resource"
                    key: res
                    is_enabled : function () { return city.resources.can_produce(res) }
                    toggle: function (p1, p2) {
                        city.resources.set_produce(res, !city.resources.can_produce(res));
                        window_features.needs_rebuild = true
                    }
                    reset: function () { city.resources.set_produce(res, resOrig) }
                })
                if (rf.length >= FEATURES_PER_PAGE) {
                    pages.push({title: "#TR_CONFIG_HEADER_RESOURCES", features: rf})
                    rf = []
                }
            })(city.resources.get_id(i))
        }
        pages.push({title: "#TR_CONFIG_HEADER_RESOURCES", features: rf})
    }

    // Languages (volatile — apply immediately on toggle)
    var lf = []
    var n_langs = game.languages.count
    for (var i = 0; i < n_langs; i++) {
        ;(function (langId, caption) {
            lf.push({
                text: caption
                original: langId
                type: "language"
                key: langId
                is_enabled : function () { return game.languages.current == langId }
                toggle: function (p1, p2) { game.languages.current = langId; window_features.needs_rebuild = true }
                reset: function () { game.languages.current = langId }
            })
            if (lf.length >= FEATURES_PER_PAGE) {
                pages.push({title: "#TR_CONFIG_HEADER_LANGUAGES", features: lf})
                lf = []
            }
        })(game.languages.get_id(i), game.languages.get_caption(i))
    }
    pages.push({title: "#TR_CONFIG_HEADER_LANGUAGES", features: lf})

    window_features.pages = pages
}

function window_features_rebuild_button_features(window) {
    window_features.button_features = []
    var page = window_features.pages[window_features.page]
    for (var i = 0; i < FEATURES_PER_PAGE; i++) {
        window_features.button_features[i] = (i < page.features.length) ? page.features[i] : null
        var option = window["bfeature" + i]
        var label = window["tfeature" + i]
        var f = window_features.button_features[i]
        option.onclick = f ? f.toggle : undefined
        option.enabled = f ? true : false
        option.text = f ? (f.is_enabled() ? "x" : "") : ""
        label.text = f ? f.text : ""
    }
}

function window_features_btn_defaults(p1, p2) {
    for (var pi = 0; pi < window_features.pages.length; pi++) {
        var page = window_features.pages[pi]
        for (var fi = 0; fi < page.features.length; fi++) {
            page.features[fi].current = page.features[fi].original
        }
    }
    window_features.needs_rebuild = true
}

function window_features_btn_hotkeys(p1, p2) {
    main_menu_show_window("window_hotkey_config")
}

function window_features_btn_close(p1, p2) {
    for (var pi = 0; pi < window_features.pages.length; pi++) {
        var page = window_features.pages[pi]
        for (var fi = 0; fi < page.features.length; fi++) {
            page.features[fi].current = page.features[fi].original
        }
    }
    window_go_back()
}

function window_features_btn_save(p1, p2) {
    window_go_back()
}

function window_features_btn_prev(p1, p2) {
    window_features.page = (window_features.page - 1 + window_features.pages.length) % window_features.pages.length
    window_features.needs_rebuild = true
}

function window_features_btn_next(p1, p2) {
    window_features.page = (window_features.page + 1) % window_features.pages.length
    window_features.needs_rebuild = true
}

// ---- UI definition ----

[es=window]
window_features {
    pos: [(sw(0) - px(40))/2, (sh(0) - px(30))/2]
    default_font : FONT_NORMAL_BLACK_ON_LIGHT
    pages : []
    page : 0
    button_features : []
    needs_rebuild : true

    ui : {
        background_image: background({pack:PACK_UNLOADED, id:8})
        background    : outer_panel({size: [40, 30] })

        title         : text({pos:[0, 16], size:[px(40), 20], align:"center", font:FONT_LARGE_BLACK_ON_LIGHT})

        btn_prev      : button({margin:{left:20, top:16}, size:[50, 25], text:"Prev",  onclick: window_features_btn_prev})
        btn_next      : button({margin:{right:-70, top:16}, size:[50, 25], text:"Next", onclick: window_features_btn_next})

        bfeature0     : button({pos:wposbtn(0),  size:[23, 23]})
        tfeature0     : text({pos:wpostxt(0)  })
        bfeature1     : button({pos:wposbtn(1),  size:[23, 23]})
        tfeature1     : text({pos:wpostxt(1)  })
        bfeature2     : button({pos:wposbtn(2),  size:[23, 23]})
        tfeature2     : text({pos:wpostxt(2)  })
        bfeature3     : button({pos:wposbtn(3),  size:[23, 23]})
        tfeature3     : text({pos:wpostxt(3)  })
        bfeature4     : button({pos:wposbtn(4),  size:[23, 23]})
        tfeature4     : text({pos:wpostxt(4)  })
        bfeature5     : button({pos:wposbtn(5),  size:[23, 23]})
        tfeature5     : text({pos:wpostxt(5)  })
        bfeature6     : button({pos:wposbtn(6),  size:[23, 23]})
        tfeature6     : text({pos:wpostxt(6)  })
        bfeature7     : button({pos:wposbtn(7),  size:[23, 23]})
        tfeature7     : text({pos:wpostxt(7)  })
        bfeature8     : button({pos:wposbtn(8),  size:[23, 23]})
        tfeature8     : text({pos:wpostxt(8)  })
        bfeature9     : button({pos:wposbtn(9),  size:[23, 23]})
        tfeature9     : text({pos:wpostxt(9)  })
        bfeature10    : button({pos:wposbtn(10), size:[23, 23]})
        tfeature10    : text({pos:wpostxt(10) })
        bfeature11    : button({pos:wposbtn(11), size:[23, 23]})
        tfeature11    : text({pos:wpostxt(11) })
        bfeature12    : button({pos:wposbtn(12), size:[23, 23]})
        tfeature12    : text({pos:wpostxt(12) })
        bfeature13    : button({pos:wposbtn(13), size:[23, 23]})
        tfeature13    : text({pos:wpostxt(13) })

        btn_defaults  : button({pos:[250, 436], size:[150, 30], text:"#TR_BUTTON_RESET_DEFAULTS",      onclick: window_features_btn_defaults}),
        btn_hotkeys   : button({pos:[90,  436], size:[150, 30], text:"#TR_BUTTON_CONFIGURE_HOTKEYS",   onclick: window_features_btn_hotkeys}),
        btn_close     : button({pos:[410, 436], size:[100, 30], text:"#TR_BUTTON_CANCEL",              onclick: window_features_btn_close}),
        btn_save      : button({pos:[520, 436], size:[100, 30], text:"#TR_BUTTON_OK",                  onclick: window_features_btn_save})
    }
}

// ---- Init ----

[es=(window_features, init)]
function window_features_on_init(window) {
    window_features_build_pages()
    window_features.page = 0
    window_features.needs_rebuild = true
}

// ---- Draw ----

[es=(window_features, ui_draw_foreground)]
function window_features_draw(window) {
    var cur = window_features.pages[window_features.page]
    window.title.text = cur.title
    if (window_features.needs_rebuild) {
        window_features_rebuild_button_features(window)
        window_features.needs_rebuild = false
    }
}
