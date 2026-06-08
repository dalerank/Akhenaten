log_info("akhenaten: hotkey config window started")

function hotkey_config_row_y(i) { return 80 + 24 * i }
function hotkey_config_label_pos(i) { return { x: 32, y: hotkey_config_row_y(i) + 6 } }
function hotkey_config_btn_pos(i) { return { x: 290, y: hotkey_config_row_y(i) } }
function hotkey_config_btn_alt_pos(i) { return { x: 430, y: hotkey_config_row_y(i) } }

function hotkey_config_btn_key(row, is_alt) {
    var scroll = window_hotkey_config.scroll_position
    var widgets = window_hotkey_config.widgets
    var widget = widgets[row + scroll]
    if (!widget || widget.action === window_hotkey_config.header_action)
        return
    __hotkey_editor_show(widget.action, is_alt)
}

function hotkey_config_btn_defaults(p1, p2) {
    window_hotkey_config.load_default_mappings()
    window_hotkey_config.needs_rebuild = true
}

function hotkey_config_btn_cancel(p1, p2) {
    window_go_back()
}

function hotkey_config_btn_save(p1, p2) {
    var mappings = window_hotkey_config.mappings
    for (var action in mappings) {
        var m = mappings[action]
        __hotkey_set_mapping(+action, m.key, m.modifiers, m.alt_key, m.alt_modifiers)
    }
    __hotkey_save_and_install()
    window_go_back()
}

function hotkey_config_update_rows(window) {
    var scroll = window.list_scroll.value
    window_hotkey_config.scroll_position = scroll
    var widgets = window_hotkey_config.widgets
    var header = window_hotkey_config.header_action
    for (var i = 0; i < window_hotkey_config.visible_rows; i++) {
        var widget = widgets[i + scroll]
        var label = window["trow" + i]
        var btn1 = window["kbtn" + i]
        var btn2 = window["kbtn" + i + "alt"]

        if (!widget) {
            label.text = ""
            btn1.enabled = false
            btn2.enabled = false
            btn1.text = ""
            btn2.text = ""
            continue
        }

        if (widget.action === header) {
            label.text = widget.text ? widget.text : ""
            label.font = FONT_NORMAL_WHITE_ON_DARK
            btn1.enabled = false
            btn2.enabled = false
            btn1.text = ""
            btn2.text = ""
        } else {
            label.text = widget.text ? widget.text : ""
            label.font = FONT_NORMAL_BLACK_ON_DARK
            btn1.enabled = true
            btn2.enabled = true
            var m = window_hotkey_config.mappings[widget.action]
            btn1.text = (m && m.key) ? __hotkey_key_display_name(m.key, m.modifiers) : ""
            btn2.text = (m && m.alt_key) ? __hotkey_key_display_name(m.alt_key, m.alt_modifiers) : ""
        }
    }
}

[es=event_hotkey_editor_result]
function hotkey_config_on_editor_result(ev) {
    var mappings = window_hotkey_config.mappings
    if (!mappings[ev.action])
        mappings[ev.action] = {}
    if (ev.is_alt) {
        mappings[ev.action].alt_key = ev.key
        mappings[ev.action].alt_modifiers = ev.modifiers
    } else {
        mappings[ev.action].key = ev.key
        mappings[ev.action].modifiers = ev.modifiers
    }
    window_hotkey_config.needs_rebuild = true
}

[es=window]
window_hotkey_config {
    pos: [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
    allow_rmb_goback: true
    default_font: FONT_NORMAL_BLACK_ON_DARK
    visible_rows: 14
    header_action: -1
    mappings: {}
    needs_rebuild: true
    widgets: [
        { action: -1, text: "#TR_HOTKEY_HEADER_ARROWS" },
        { action: HOTKEY_ARROW_UP, text: "#TR_HOTKEY_ARROW_UP" },
        { action: HOTKEY_ARROW_DOWN, text: "#TR_HOTKEY_ARROW_DOWN" },
        { action: HOTKEY_ARROW_LEFT, text: "#TR_HOTKEY_ARROW_LEFT" },
        { action: HOTKEY_ARROW_RIGHT, text: "#TR_HOTKEY_ARROW_RIGHT" },
        { action: -1, text: "#TR_HOTKEY_HEADER_GLOBAL" },
        { action: HOTKEY_TOGGLE_FULLSCREEN, text: "#TR_HOTKEY_TOGGLE_FULLSCREEN" },
        { action: HOTKEY_CENTER_WINDOW, text: "#TR_HOTKEY_CENTER_WINDOW" },
        { action: HOTKEY_SAVE_SCREENSHOT, text: "#TR_HOTKEY_SAVE_SCREENSHOT" },
        { action: HOTKEY_SAVE_CITY_SCREENSHOT, text: "#TR_HOTKEY_SAVE_CITY_SCREENSHOT" },
        { action: HOTKEY_LOAD_FILE, text: "#TR_HOTKEY_LOAD_FILE" },
        { action: HOTKEY_SAVE_FILE, text: "#TR_HOTKEY_SAVE_FILE" },
        { action: -1, text: "#TR_HOTKEY_HEADER_CITY" },
        { action: HOTKEY_INCREASE_GAME_SPEED, text: "#TR_HOTKEY_INCREASE_GAME_SPEED" },
        { action: HOTKEY_DECREASE_GAME_SPEED, text: "#TR_HOTKEY_DECREASE_GAME_SPEED" },
        { action: HOTKEY_TOGGLE_PAUSE, text: "#TR_HOTKEY_TOGGLE_PAUSE" },
        { action: HOTKEY_CYCLE_LEGION, text: "#TR_HOTKEY_CYCLE_LEGION" },
        { action: HOTKEY_ROTATE_MAP_LEFT, text: "#TR_HOTKEY_ROTATE_MAP_LEFT" },
        { action: HOTKEY_ROTATE_MAP_RIGHT, text: "#TR_HOTKEY_ROTATE_MAP_RIGHT" },
        { action: HOTKEY_ROTATE_BUILDING, text: "#TR_HOTKEY_ROTATE_BUILDING" },
        { action: -1, text: "#TR_HOTKEY_HEADER_BUILD" },
        { action: HOTKEY_COPY_BUILD, text: "#TR_HOTKEY_COPY_BUILD" },
        { action: HOTKEY_BUILD_CLEAR_LAND, text: "#TR_HOTKEY_BUILD_CLEAR_LAND" },
        { action: HOTKEY_BUILD_VACANT_HOUSE, text: "#TR_HOTKEY_BUILD_VACANT_HOUSE" },
        { action: HOTKEY_BUILD_ROAD, text: "#TR_HOTKEY_BUILD_ROAD" },
        { action: HOTKEY_BUILD_PLAZA, text: "#TR_HOTKEY_BUILD_PLAZA" },
        { action: HOTKEY_BUILD_GARDENS, text: "#TR_HOTKEY_BUILD_GARDENS" },
        { action: HOTKEY_BUILD_FIREHOUSE, text: "#TR_HOTKEY_BUILD_FIREHOUSE" },
        { action: HOTKEY_BUILD_ARCHITECT, text: "#TR_HOTKEY_BUILD_ARCHITECT" },
        { action: HOTKEY_BUILD_APOTHECARY, text: "#TR_HOTKEY_BUILD_APOTHECARY" },
        { action: HOTKEY_BUILD_GRANARY, text: "#TR_HOTKEY_BUILD_GRANARY" },
        { action: HOTKEY_BUILD_STORAGE_YARD, text: "#TR_HOTKEY_BUILD_STORAGE_YARD" },
        { action: HOTKEY_BUILD_BAZAAR, text: "#TR_HOTKEY_BUILD_BAZAAR" },
        { action: HOTKEY_BUILD_WALL, text: "#TR_HOTKEY_BUILD_WALL" },
        { action: HOTKEY_BUILD_GATEHOUSE, text: "#TR_HOTKEY_BUILD_GATEHOUSE" },
        { action: HOTKEY_BUILD_WATERLIFT, text: "#TR_HOTKEY_BUILD_WATERLIFT" },
        { action: HOTKEY_BUILD_CANAL, text: "#TR_HOTKEY_BUILD_CANAL" },
        { action: HOTKEY_BUILD_WATER_SUPPLY, text: "#TR_HOTKEY_BUILD_WATER_SUPPLY" },
        { action: HOTKEY_BUILD_ROADBLOCK, text: "#TR_HOTKEY_BUILD_ROADBLOCK" },
        { action: -1, text: "#TR_HOTKEY_HEADER_ADVISORS" },
        { action: HOTKEY_SHOW_ADVISOR_LABOR, text: "#TR_HOTKEY_SHOW_ADVISOR_LABOR" },
        { action: HOTKEY_SHOW_ADVISOR_MILITARY, text: "#TR_HOTKEY_SHOW_ADVISOR_MILITARY" },
        { action: HOTKEY_SHOW_ADVISOR_KINGDOME, text: "#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL" },
        { action: HOTKEY_SHOW_ADVISOR_RATINGS, text: "#TR_HOTKEY_SHOW_ADVISOR_RATINGS" },
        { action: HOTKEY_SHOW_ADVISOR_TRADE, text: "#TR_HOTKEY_SHOW_ADVISOR_TRADE" },
        { action: HOTKEY_SHOW_ADVISOR_POPULATION, text: "#TR_HOTKEY_SHOW_ADVISOR_POPULATION" },
        { action: HOTKEY_SHOW_ADVISOR_HEALTH, text: "#TR_HOTKEY_SHOW_ADVISOR_HEALTH" },
        { action: HOTKEY_SHOW_ADVISOR_EDUCATION, text: "#TR_HOTKEY_SHOW_ADVISOR_EDUCATION" },
        { action: HOTKEY_SHOW_ADVISOR_ENTERTAINMENT, text: "#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT" },
        { action: HOTKEY_SHOW_ADVISOR_RELIGION, text: "#TR_HOTKEY_SHOW_ADVISOR_RELIGION" },
        { action: HOTKEY_SHOW_ADVISOR_FINANCIAL, text: "#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL" },
        { action: HOTKEY_SHOW_ADVISOR_CHIEF, text: "#TR_HOTKEY_SHOW_ADVISOR_CHIEF" },
        { action: HOTKEY_SHOW_ADVISOR_HOUSING, text: "#TR_HOTKEY_SHOW_ADVISOR_HOUSING" },
        { action: -1, text: "#TR_HOTKEY_HEADER_OVERLAYS" },
        { action: HOTKEY_TOGGLE_OVERLAY, text: "#TR_HOTKEY_TOGGLE_OVERLAY" },
        { action: HOTKEY_SHOW_OVERLAY_WATER, text: "#TR_HOTKEY_SHOW_OVERLAY_WATER" },
        { action: HOTKEY_SHOW_OVERLAY_FIRE, text: "#TR_HOTKEY_SHOW_OVERLAY_FIRE" },
        { action: HOTKEY_SHOW_OVERLAY_DAMAGE, text: "#TR_HOTKEY_SHOW_OVERLAY_DAMAGE" },
        { action: HOTKEY_SHOW_OVERLAY_CRIME, text: "#TR_HOTKEY_SHOW_OVERLAY_CRIME" },
        { action: HOTKEY_SHOW_OVERLAY_PROBLEMS, text: "#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS" },
        { action: -1, text: "#TR_HOTKEY_HEADER_BOOKMARKS" },
        { action: HOTKEY_GO_TO_BOOKMARK_1, text: "#TR_HOTKEY_GO_TO_BOOKMARK_1" },
        { action: HOTKEY_GO_TO_BOOKMARK_2, text: "#TR_HOTKEY_GO_TO_BOOKMARK_2" },
        { action: HOTKEY_GO_TO_BOOKMARK_3, text: "#TR_HOTKEY_GO_TO_BOOKMARK_3" },
        { action: HOTKEY_GO_TO_BOOKMARK_4, text: "#TR_HOTKEY_GO_TO_BOOKMARK_4" },
        { action: HOTKEY_SET_BOOKMARK_1, text: "#TR_HOTKEY_SET_BOOKMARK_1" },
        { action: HOTKEY_SET_BOOKMARK_2, text: "#TR_HOTKEY_SET_BOOKMARK_2" },
        { action: HOTKEY_SET_BOOKMARK_3, text: "#TR_HOTKEY_SET_BOOKMARK_3" },
        { action: HOTKEY_SET_BOOKMARK_4, text: "#TR_HOTKEY_SET_BOOKMARK_4" },
        { action: -1, text: "#TR_HOTKEY_HEADER_EDITOR" },
        { action: HOTKEY_EDITOR_TOGGLE_BATTLE_INFO, text: "#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO" }
    ]

    scroll_position: 0

    load_mappings: function () {
        var result = {}
        var widgets = this.widgets
        var header = this.header_action
        for (var i = 0; i < widgets.length; i++) {
            var widget = widgets[i]
            if (widget.action === header)
                continue
            result[widget.action] = __hotkey_read_mapping(widget.action, false)
        }
        this.mappings = result
    }

    load_default_mappings: function () {
        var result = {}
        var widgets = this.widgets
        var header = this.header_action
        for (var i = 0; i < widgets.length; i++) {
            var widget = widgets[i]
            if (widget.action === header)
                continue
            result[widget.action] = __hotkey_read_mapping(widget.action, true)
        }
        this.mappings = result
    }

    ui: {
        background_image: background({ pack: PACK_UNLOADED, id: 8 })
        background: outer_panel({ size: [40, 30] })

        title: text({ pos: [0, 16], size: [px(40), 20], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, text: "#TR_HOTKEY_TITLE" })
        label_primary: text({ pos: [290, 55], size: [140, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_HOTKEY_LABEL" })
        label_alt: text({ pos: [430, 55], size: [140, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_HOTKEY_ALTERNATIVE_LABEL" })

        content_panel: inner_panel({ pos: [20, 72], size: [35, 22] })
        list_scroll: scrollbar({ pos: [580, 72], size: [0, 352] })

        trow0: text({ pos: hotkey_config_label_pos(0) })
        kbtn0: button({ pos: hotkey_config_btn_pos(0), size: [140, 22], onclick: function () { hotkey_config_btn_key(0, 0) } })
        kbtn0alt: button({ pos: hotkey_config_btn_alt_pos(0), size: [140, 22], onclick: function () { hotkey_config_btn_key(0, 1) } })
        trow1: text({ pos: hotkey_config_label_pos(1) })
        kbtn1: button({ pos: hotkey_config_btn_pos(1), size: [140, 22], onclick: function () { hotkey_config_btn_key(1, 0) } })
        kbtn1alt: button({ pos: hotkey_config_btn_alt_pos(1), size: [140, 22], onclick: function () { hotkey_config_btn_key(1, 1) } })
        trow2: text({ pos: hotkey_config_label_pos(2) })
        kbtn2: button({ pos: hotkey_config_btn_pos(2), size: [140, 22], onclick: function () { hotkey_config_btn_key(2, 0) } })
        kbtn2alt: button({ pos: hotkey_config_btn_alt_pos(2), size: [140, 22], onclick: function () { hotkey_config_btn_key(2, 1) } })
        trow3: text({ pos: hotkey_config_label_pos(3) })
        kbtn3: button({ pos: hotkey_config_btn_pos(3), size: [140, 22], onclick: function () { hotkey_config_btn_key(3, 0) } })
        kbtn3alt: button({ pos: hotkey_config_btn_alt_pos(3), size: [140, 22], onclick: function () { hotkey_config_btn_key(3, 1) } })
        trow4: text({ pos: hotkey_config_label_pos(4) })
        kbtn4: button({ pos: hotkey_config_btn_pos(4), size: [140, 22], onclick: function () { hotkey_config_btn_key(4, 0) } })
        kbtn4alt: button({ pos: hotkey_config_btn_alt_pos(4), size: [140, 22], onclick: function () { hotkey_config_btn_key(4, 1) } })
        trow5: text({ pos: hotkey_config_label_pos(5) })
        kbtn5: button({ pos: hotkey_config_btn_pos(5), size: [140, 22], onclick: function () { hotkey_config_btn_key(5, 0) } })
        kbtn5alt: button({ pos: hotkey_config_btn_alt_pos(5), size: [140, 22], onclick: function () { hotkey_config_btn_key(5, 1) } })
        trow6: text({ pos: hotkey_config_label_pos(6) })
        kbtn6: button({ pos: hotkey_config_btn_pos(6), size: [140, 22], onclick: function () { hotkey_config_btn_key(6, 0) } })
        kbtn6alt: button({ pos: hotkey_config_btn_alt_pos(6), size: [140, 22], onclick: function () { hotkey_config_btn_key(6, 1) } })
        trow7: text({ pos: hotkey_config_label_pos(7) })
        kbtn7: button({ pos: hotkey_config_btn_pos(7), size: [140, 22], onclick: function () { hotkey_config_btn_key(7, 0) } })
        kbtn7alt: button({ pos: hotkey_config_btn_alt_pos(7), size: [140, 22], onclick: function () { hotkey_config_btn_key(7, 1) } })
        trow8: text({ pos: hotkey_config_label_pos(8) })
        kbtn8: button({ pos: hotkey_config_btn_pos(8), size: [140, 22], onclick: function () { hotkey_config_btn_key(8, 0) } })
        kbtn8alt: button({ pos: hotkey_config_btn_alt_pos(8), size: [140, 22], onclick: function () { hotkey_config_btn_key(8, 1) } })
        trow9: text({ pos: hotkey_config_label_pos(9) })
        kbtn9: button({ pos: hotkey_config_btn_pos(9), size: [140, 22], onclick: function () { hotkey_config_btn_key(9, 0) } })
        kbtn9alt: button({ pos: hotkey_config_btn_alt_pos(9), size: [140, 22], onclick: function () { hotkey_config_btn_key(9, 1) } })
        trow10: text({ pos: hotkey_config_label_pos(10) })
        kbtn10: button({ pos: hotkey_config_btn_pos(10), size: [140, 22], onclick: function () { hotkey_config_btn_key(10, 0) } })
        kbtn10alt: button({ pos: hotkey_config_btn_alt_pos(10), size: [140, 22], onclick: function () { hotkey_config_btn_key(10, 1) } })
        trow11: text({ pos: hotkey_config_label_pos(11) })
        kbtn11: button({ pos: hotkey_config_btn_pos(11), size: [140, 22], onclick: function () { hotkey_config_btn_key(11, 0) } })
        kbtn11alt: button({ pos: hotkey_config_btn_alt_pos(11), size: [140, 22], onclick: function () { hotkey_config_btn_key(11, 1) } })
        trow12: text({ pos: hotkey_config_label_pos(12) })
        kbtn12: button({ pos: hotkey_config_btn_pos(12), size: [140, 22], onclick: function () { hotkey_config_btn_key(12, 0) } })
        kbtn12alt: button({ pos: hotkey_config_btn_alt_pos(12), size: [140, 22], onclick: function () { hotkey_config_btn_key(12, 1) } })
        trow13: text({ pos: hotkey_config_label_pos(13) })
        kbtn13: button({ pos: hotkey_config_btn_pos(13), size: [140, 22], onclick: function () { hotkey_config_btn_key(13, 0) } })
        kbtn13alt: button({ pos: hotkey_config_btn_alt_pos(13), size: [140, 22], onclick: function () { hotkey_config_btn_key(13, 1) } })

        btn_defaults: button({ pos: [240, 430], size: [160, 30], text: "#TR_BUTTON_RESET_DEFAULTS", onclick: hotkey_config_btn_defaults })
        btn_cancel: button({ pos: [410, 430], size: [100, 30], text: "#TR_BUTTON_CANCEL", onclick: hotkey_config_btn_cancel })
        btn_save: button({ pos: [520, 430], size: [100, 30], text: "#TR_BUTTON_OK", onclick: hotkey_config_btn_save })
    }
}

[es=(window_hotkey_config, init)]
function hotkey_config_on_init(window) {
    __log_marker("window_show:window_hotkey_config")
    window_hotkey_config.load_mappings()
    window_hotkey_config.needs_rebuild = true
    window.list_scroll.max_value = window_hotkey_config.widgets.length - window_hotkey_config.visible_rows
}

[es=(window_hotkey_config, ui_draw_foreground)]
function hotkey_config_draw(window) {
    hotkey_config_update_rows(window)
    window_hotkey_config.needs_rebuild = false
}
