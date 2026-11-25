log_info("akhenaten: window features started")

var FEATURES_PER_PAGE = 14
var FEATURES_TAB_SLOTS = 18

function wposbtn(i) { return { x: 208, y: 72 + i * 25} }
function wpostxt(i) { return { x: 240, y: 78 + i * 25} }
function wpostab(i) { return { x: 16, y: 48 + i * 22} }

// ---- Feature descriptors by type ----

function window_features_make_game_feature(fname, fval, ftext) {
    return {
        text: ftext
        original: fval
        type: "game_feature"
        key: fname
        checkedfn: function () { return game_features.get(fname) === true }
        toggle: function (p1, p2) {
            game_features.set(fname, !game_features.get(fname))
            window_features.needs_rebuild = true
        }
        reset: function () { game_features.set(fname, fval) }
    }
}

function window_features_add_tab(pages, title, features) {
    var first = pages.length
    for (var i = 0; i < features.length; i += FEATURES_PER_PAGE) {
        pages.push({title: title, first: first, features: features.slice(i, i + FEATURES_PER_PAGE)})
    }
}

function window_features_append_gameplay_pages(pages) {
    var ng = game_features.group_count()
    for (var g = 0; g < ng; g++) {
        var pf = []
        var n = game_features.group_size(g)
        for (var i = 0; i < n; i++) {
            var name = game_features.group_feature(g, i)

            // Ironwill: chosen at mission briefing; locked for the playthrough (IW5).
            if (name === "gameopt_ironwill" && game_mission_options_locked)
                continue

            if (name === "gameopt_auto_update" && !__updater_available())
                continue

            pf.push(window_features_make_game_feature(name, game_features.get(name), game_features.text(name)))
        }
        window_features_add_tab(pages, game_features.group_title(g), pf)
    }
}

function window_features_make_scenario_animals(orig) {
    return {
        text: "#TR_CONFIG_ANIMALS"
        original: orig
        type: "scenario_animals"
        checkedfn: function () { return scenario.has_animals }
        toggle: function (p1, p2) {
            scenario.has_animals = !scenario.has_animals;
            window_features.needs_rebuild = true
        }
        reset: function () { scenario.has_animals = orig }
    }
}

function window_features_make_scenario_flotsam(orig) {
    return {
        text: "#TR_CONFIG_FLOTSAM"
        original: orig
        type: "scenario_flotsam"
        checkedfn: function () { return scenario.flotsam_enabled }
        toggle: function (p1, p2) {
            scenario.flotsam_enabled = !scenario.flotsam_enabled;
            window_features.needs_rebuild = true
        }
        reset: function () { scenario.flotsam_enabled = orig }
    }
}

function window_features_append_scenario_pages(pages) {
    if (!game.session_active)
        return
    var sc_orig_animals = scenario.has_animals
    var sc_orig_flotsam = scenario.flotsam_enabled
    window_features_add_tab(pages, "#TR_CONFIG_HEADER_SCENARIO_CHANGES", [
        window_features_make_scenario_animals(sc_orig_animals),
        window_features_make_scenario_flotsam(sc_orig_flotsam)
    ])
}

function window_features_make_god(godIdx) {
    var godOrig = city.gods.is_known(godIdx)
    return {
        text: __loc("#features_god_enabled") + " " + city.gods.get_name(godIdx)
        key: godIdx
        original: godOrig
        type: "god"
        checkedfn: function () { return city.gods.is_known(godIdx) }
        toggle: function (p1, p2) {
            city.gods.set_known(godIdx, !city.gods.is_known(godIdx));
            window_features.needs_rebuild = true
        }
        reset: function () { city.gods.set_known(godIdx, godOrig) }
    }
}

function window_features_append_gods_pages(pages) {
    if (!game.session_active)
        return
    var gf = []
    for (var i = 0; i < 5; i++) {
        gf.push(window_features_make_god(i))
    }
    window_features_add_tab(pages, "#TR_CONFIG_HEADER_GODS_CHANGES", gf)
}

function window_features_make_resource(res) {
    var resOrig = city.resources.can_produce(res)
    return {
        text: __loc("#features_city_allow") + " " + city.resources.get_name(res)
        original: resOrig
        type: "resource"
        key: res
        checkedfn: function () { return city.resources.can_produce(res) }
        toggle: function (p1, p2) {
            city.resources.set_produce(res, !city.resources.can_produce(res));
            window_features.needs_rebuild = true
        }
        reset: function () { city.resources.set_produce(res, resOrig) }
    }
}

function window_features_append_resource_pages(pages) {
    if (!game.session_active)
        return
    var rf = []
    var n_res = city.resources.count
    for (var i = 0; i < n_res; i++) {
        rf.push(window_features_make_resource(city.resources.get_id(i)))
    }
    window_features_add_tab(pages, "#TR_CONFIG_HEADER_RESOURCES", rf)
}

function window_features_make_language(langId, caption) {
    return {
        text: caption
        original: langId
        type: "language"
        key: langId
        checkedfn: function () { return game.languages.current == langId }
        toggle: function (p1, p2) {
            game.languages.current = langId;
            window_features.needs_rebuild = true
        }
        reset: function () { game.languages.current = langId }
    }
}

function window_features_append_language_pages(pages) {
    var lf = []
    var n_langs = game.languages.count
    for (var i = 0; i < n_langs; i++) {
        lf.push(window_features_make_language(game.languages.get_id(i), game.languages.get_caption(i)))
    }
    window_features_add_tab(pages, "#TR_CONFIG_HEADER_LANGUAGES", lf)
}

// ---- State management ----

function window_features_build_pages() {
    var pages = []

    window_features_append_gameplay_pages(pages)
    window_features_append_scenario_pages(pages)
    window_features_append_gods_pages(pages)
    window_features_append_resource_pages(pages)
    window_features_append_language_pages(pages)

    window_features.pages = pages
}

function window_features_tabs() {
    var tabs = []
    for (var p = 0; p < window_features.pages.length; p++) {
        if (window_features.pages[p].first == p)
            tabs.push(p)
    }
    return tabs
}

function window_features_rebuild_tabs(window) {
    var tabs = window_features_tabs()
    var current = window_features.pages[window_features.page].first
    for (var i = 0; i < FEATURES_TAB_SLOTS; i++) {
        var tab = window["btab" + i]
        tab.enabled = i < tabs.length
        tab.text = (i < tabs.length) ? window_features.pages[tabs[i]].title : ""
        tab.selected = (i < tabs.length) && tabs[i] == current
    }
}

function window_features_select_tab(index) {
    var tabs = window_features_tabs()
    if (index < 0 || index >= tabs.length)
        return
    window_features.page = tabs[index]
    window_features.needs_rebuild = true
}

function window_features_rebuild_button_features(window) {
    window_features_rebuild_tabs(window)
    window_features.button_features = []
    var page = window_features.pages[window_features.page]
    for (var i = 0; i < FEATURES_PER_PAGE; i++) {
        window_features.button_features[i] = (i < page.features.length) ? page.features[i] : null
        var option = window["bfeature" + i]
        var label = window["tfeature" + i]
        var f = window_features.button_features[i]
        option.enabled = f ? true : false
        option.checkedfn = f ? f.checkedfn : undefined
        label.text = f ? f.text : ""
    }
}

function window_features_toggle_slot(index) {
    var f = window_features.button_features[index]
    if (f && f.toggle) {
        f.toggle(0, 0)
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
    window_show_by_id("window_hotkey_config")
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
    pos: window_features_centered_pos()
    defer_relayout : true
    default_font : FONT_NORMAL_BLACK_ON_LIGHT
    pages : []
    page : 0
    button_features : []
    needs_rebuild : true

    ui : {
        background_image: background({pack:PACK_UNLOADED, id:8})
        background    : outer_panel({size: [48, 35] })

        title         : text({pos:[0, 16], size:[px(48), 20], align:"center", font:FONT_LARGE_BLACK_ON_LIGHT})

        btn_prev      : button({margin:{left:20, top:16}, size:[50, 25], text:"#features_prev_page"})
        btn_next      : button({margin:{right:-70, top:16}, size:[50, 25], text:"#features_next_page"})

        btab0         : button({pos:wpostab(0), size:[176, 20], param1:0, onclick_event:"select_tab"})
        btab1         : button({pos:wpostab(1), size:[176, 20], param1:1, onclick_event:"select_tab"})
        btab2         : button({pos:wpostab(2), size:[176, 20], param1:2, onclick_event:"select_tab"})
        btab3         : button({pos:wpostab(3), size:[176, 20], param1:3, onclick_event:"select_tab"})
        btab4         : button({pos:wpostab(4), size:[176, 20], param1:4, onclick_event:"select_tab"})
        btab5         : button({pos:wpostab(5), size:[176, 20], param1:5, onclick_event:"select_tab"})
        btab6         : button({pos:wpostab(6), size:[176, 20], param1:6, onclick_event:"select_tab"})
        btab7         : button({pos:wpostab(7), size:[176, 20], param1:7, onclick_event:"select_tab"})
        btab8         : button({pos:wpostab(8), size:[176, 20], param1:8, onclick_event:"select_tab"})
        btab9         : button({pos:wpostab(9), size:[176, 20], param1:9, onclick_event:"select_tab"})
        btab10        : button({pos:wpostab(10), size:[176, 20], param1:10, onclick_event:"select_tab"})
        btab11        : button({pos:wpostab(11), size:[176, 20], param1:11, onclick_event:"select_tab"})
        btab12        : button({pos:wpostab(12), size:[176, 20], param1:12, onclick_event:"select_tab"})
        btab13        : button({pos:wpostab(13), size:[176, 20], param1:13, onclick_event:"select_tab"})
        btab14        : button({pos:wpostab(14), size:[176, 20], param1:14, onclick_event:"select_tab"})
        btab15        : button({pos:wpostab(15), size:[176, 20], param1:15, onclick_event:"select_tab"})
        btab16        : button({pos:wpostab(16), size:[176, 20], param1:16, onclick_event:"select_tab"})
        btab17        : button({pos:wpostab(17), size:[176, 20], param1:17, onclick_event:"select_tab"})

        bfeature0     : checkbox({pos:wposbtn(0)})
        tfeature0     : text({pos:wpostxt(0)  })
        bfeature1     : checkbox({pos:wposbtn(1)})
        tfeature1     : text({pos:wpostxt(1)  })
        bfeature2     : checkbox({pos:wposbtn(2)})
        tfeature2     : text({pos:wpostxt(2)  })
        bfeature3     : checkbox({pos:wposbtn(3)})
        tfeature3     : text({pos:wpostxt(3)  })
        bfeature4     : checkbox({pos:wposbtn(4)})
        tfeature4     : text({pos:wpostxt(4)  })
        bfeature5     : checkbox({pos:wposbtn(5)})
        tfeature5     : text({pos:wpostxt(5)  })
        bfeature6     : checkbox({pos:wposbtn(6)})
        tfeature6     : text({pos:wpostxt(6)  })
        bfeature7     : checkbox({pos:wposbtn(7)})
        tfeature7     : text({pos:wpostxt(7)  })
        bfeature8     : checkbox({pos:wposbtn(8)})
        tfeature8     : text({pos:wpostxt(8)  })
        bfeature9     : checkbox({pos:wposbtn(9)})
        tfeature9     : text({pos:wpostxt(9)  })
        bfeature10    : checkbox({pos:wposbtn(10)})
        tfeature10    : text({pos:wpostxt(10) })
        bfeature11    : checkbox({pos:wposbtn(11)})
        tfeature11    : text({pos:wpostxt(11) })
        bfeature12    : checkbox({pos:wposbtn(12)})
        tfeature12    : text({pos:wpostxt(12) })
        bfeature13    : checkbox({pos:wposbtn(13)})
        tfeature13    : text({pos:wpostxt(13) })

        btn_defaults  : button({pos:[314, 468], size:[150, 30], text:"#TR_BUTTON_RESET_DEFAULTS"})
        btn_hotkeys   : button({pos:[154, 468], size:[150, 30], text:"#TR_BUTTON_CONFIGURE_HOTKEYS"})
        btn_close     : button({pos:[474, 468], size:[100, 30], text:"#TR_BUTTON_CANCEL"})
        btn_save      : button({pos:[584, 468], size:[100, 30], text:"#TR_BUTTON_OK"})

        // Own row below the page buttons, so they show on every features page.
        btn_display   : button({pos:[179, 506], size:[200, 30], text:"#display_options_title"})
        btn_sound     : button({pos:[389, 506], size:[200, 30], text:[46, 0]})
    }
}

[es=(window_features, bfeature0)]
function window_features_on_bfeature0(window) { window_features_toggle_slot(0) }
[es=(window_features, bfeature1)]
function window_features_on_bfeature1(window) { window_features_toggle_slot(1) }
[es=(window_features, bfeature2)]
function window_features_on_bfeature2(window) { window_features_toggle_slot(2) }
[es=(window_features, bfeature3)]
function window_features_on_bfeature3(window) { window_features_toggle_slot(3) }
[es=(window_features, bfeature4)]
function window_features_on_bfeature4(window) { window_features_toggle_slot(4) }
[es=(window_features, bfeature5)]
function window_features_on_bfeature5(window) { window_features_toggle_slot(5) }
[es=(window_features, bfeature6)]
function window_features_on_bfeature6(window) { window_features_toggle_slot(6) }
[es=(window_features, bfeature7)]
function window_features_on_bfeature7(window) { window_features_toggle_slot(7) }
[es=(window_features, bfeature8)]
function window_features_on_bfeature8(window) { window_features_toggle_slot(8) }
[es=(window_features, bfeature9)]
function window_features_on_bfeature9(window) { window_features_toggle_slot(9) }
[es=(window_features, bfeature10)]
function window_features_on_bfeature10(window) { window_features_toggle_slot(10) }
[es=(window_features, bfeature11)]
function window_features_on_bfeature11(window) { window_features_toggle_slot(11) }
[es=(window_features, bfeature12)]
function window_features_on_bfeature12(window) { window_features_toggle_slot(12) }
[es=(window_features, bfeature13)]
function window_features_on_bfeature13(window) { window_features_toggle_slot(13) }

[es=(window_features, select_tab)]
function window_features_on_select_tab(ev) {
    window_features_select_tab(Math.round(ev.param1))
}

[es=(window_features, btn_defaults)]
function window_features_on_btn_defaults(window) {
    window_features_btn_defaults()
}

[es=(window_features, btn_display)]
function window_features_on_btn_display(window) {
    window_show_by_id("display_options_window")
}

[es=(window_features, btn_sound)]
function window_features_on_btn_sound(window) {
    emit event_show_window{ id: "sound_options_window" }
}

[es=(window_features, btn_hotkeys)]
function window_features_on_btn_hotkeys(window) {
    window_features_btn_hotkeys()
}

[es=(window_features, btn_close)]
function window_features_on_btn_close(window) {
    window_features_btn_close()
}

[es=(window_features, btn_save)]
function window_features_on_btn_save(window) {
    window_features_btn_save()
}

[es=(window_features, btn_prev)]
function window_features_on_btn_prev(window) {
    window_features_btn_prev()
}

[es=(window_features, btn_next)]
function window_features_on_btn_next(window) {
    window_features_btn_next()
}

// ---- Init ----

[es=(window_features, init)]
function window_features_on_init(window) {
    window_features_build_pages()
    if (window_features.page >= window_features.pages.length)
        window_features.page = 0
    window_features.needs_rebuild = true
}

// ---- Draw ----

function window_features_centered_pos() {
    return [(sw(0) - px(48)) / 2, (sh(0) - px(35)) / 2]
}

[es=(window_features, ui_draw_foreground)]
function window_features_draw(window) {
    // defer_relayout: follow screen-size changes (e.g. from display options) without a reload.
    var p = window_features_centered_pos()
    __window_set_pos("window_features", p[0], p[1])
    var cur = window_features.pages[window_features.page]
    window.title.text = cur.title
    if (window_features.needs_rebuild) {
        window_features_rebuild_button_features(window)
        window_features.needs_rebuild = false
    }
}
