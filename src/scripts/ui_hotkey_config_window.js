log_info("akhenaten: hotkey config window started")

var HOTKEY_CONFIG_VISIBLE_ROWS = 14

function hotkey_config_row_y(i) { return 80 + 24 * i }
function hotkey_config_label_pos(i) { return { x: 32, y: hotkey_config_row_y(i) + 6 } }
function hotkey_config_key_pos(row, is_alt) { return { x: is_alt ? 430 : 290, y: hotkey_config_row_y(row) } }

function hotkey_config_key_button(row, is_alt) {
    return {
        pos: hotkey_config_key_pos(row, is_alt),
        size: [140, 22],
        param1: row,
        param2: is_alt ? 1 : 0,
        onclick_event: "edit_key"
    }
}

function hotkey_config_rows_ui(count) {
    var rows = {}
    for (var i = 0; i < count; i++) {
        rows["trow" + i] = text({ pos: hotkey_config_label_pos(i) })
        rows["kbtn" + i] = button(hotkey_config_key_button(i, false))
        rows["kbtn" + i + "alt"] = button(hotkey_config_key_button(i, true))
    }
    return rows
}

function hotkey_config_keys_match(key1, mod1, key2, mod2) {
    return !!key1 && key1 === key2 && (mod1 | 0) === (mod2 | 0)
}

function hotkey_config_action_label(action) {
    var widgets = window_hotkey_config.widgets
    for (var i = 0; i < widgets.length; i++) {
        if (widgets[i].action === +action)
            return __loc(widgets[i].text)
    }
    return ""
}

function hotkey_config_find_conflict(action, is_alt, key, modifiers) {
    if (!key)
        return null

    var mappings = window_hotkey_config.mappings
    for (var other_action in mappings) {
        var m = mappings[other_action]
        var same_action = (+other_action === +action)

        if (hotkey_config_keys_match(key, modifiers, m.key, m.modifiers)) {
            if (!(same_action && !is_alt))
                return +other_action
        }
        if (hotkey_config_keys_match(key, modifiers, m.alt_key, m.alt_modifiers)) {
            if (!(same_action && is_alt))
                return +other_action
        }
    }
    return null
}

[es=event_hotkey_editor_result]
function hotkey_config_on_editor_result(ev) {
    var conflict_action = hotkey_config_find_conflict(ev.action, ev.is_alt, ev.key, ev.modifiers)
    if (conflict_action !== null) {
        var name = hotkey_config_action_label(conflict_action)
        ui.show_ok(_format(__loc("#TR_HOTKEY_DUPLICATE_MESSAGE"), name), __loc("#TR_HOTKEY_DUPLICATE_TITLE"))
        return
    }

    var m = window_hotkey_config.mappings[ev.action]
    if (!m)
        m = window_hotkey_config.mappings[ev.action] = {}
    if (ev.is_alt) {
        m.alt_key = ev.key
        m.alt_modifiers = ev.modifiers
    } else {
        m.key = ev.key
        m.modifiers = ev.modifiers
    }
    window_hotkey_config.needs_rebuild = true
}

[es=(window_hotkey_config, edit_key)]
function hotkey_config_on_edit_key(ev) {
    var cfg = window_hotkey_config
    var widget = cfg.widgets[ev.param1 + cfg.scroll_position]
    if (!widget || widget.action === cfg.header_action)
        return
    __hotkey_editor_show(widget.action, ev.param2)
}

[es=(window_hotkey_config, reset_defaults)]
function hotkey_config_on_reset_defaults() {
    window_hotkey_config.load_default_mappings()
}

[es=(window_hotkey_config, save)]
function hotkey_config_on_save() {
    var mappings = window_hotkey_config.mappings
    for (var action in mappings) {
        var m = mappings[action]
        __hotkey_set_mapping(+action, m.key, m.modifiers, m.alt_key, m.alt_modifiers)
    }
    __hotkey_save_and_install()
    window_go_back()
}

[es=window]
window_hotkey_config {
    pos: [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
    allow_rmb_goback: true
    default_font: FONT_NORMAL_BLACK_ON_DARK
    visible_rows: HOTKEY_CONFIG_VISIBLE_ROWS
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

    load_mappings: function (use_defaults) {
        var result = {}
        var header = this.header_action
        for (var i = 0; i < this.widgets.length; i++) {
            var widget = this.widgets[i]
            if (widget.action === header)
                continue
            result[widget.action] = __hotkey_read_mapping(widget.action, !!use_defaults)
        }
        this.mappings = result
    }

    load_default_mappings: function () {
        this.load_mappings(true)
        this.needs_rebuild = true
    }

    update_rows: function (window) {
        var scroll = window.list_scroll.value
        this.scroll_position = scroll
        var header = this.header_action
        for (var i = 0; i < this.visible_rows; i++) {
            var widget = this.widgets[i + scroll]
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

            label.text = widget.text ? widget.text : ""
            if (widget.action === header) {
                label.font = FONT_NORMAL_WHITE_ON_DARK
                btn1.enabled = false
                btn2.enabled = false
                btn1.text = ""
                btn2.text = ""
            } else {
                label.font = FONT_NORMAL_BLACK_ON_DARK
                btn1.enabled = true
                btn2.enabled = true
                var m = this.mappings[widget.action]
                btn1.text = (m && m.key) ? __hotkey_key_display_name(m.key, m.modifiers) : ""
                btn2.text = (m && m.alt_key) ? __hotkey_key_display_name(m.alt_key, m.alt_modifiers) : ""
            }
        }
    }

    ui: ui_extend({
        background_image: background({ pack: PACK_UNLOADED, id: 8 })
        background: outer_panel({ size: [40, 30] })

        title: text({ pos: [0, 16], size: [px(40), 20], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, text: "#TR_HOTKEY_TITLE" })
        label_primary: text({ pos: [290, 55], size: [140, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_HOTKEY_LABEL" })
        label_alt: text({ pos: [430, 55], size: [140, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#TR_HOTKEY_ALTERNATIVE_LABEL" })

        content_panel: inner_panel({ pos: [20, 72], size: [35, 22] })
        list_scroll: scrollbar({ pos: [580, 72], size: [0, 352] })

        btn_defaults: button({ pos: [240, 430], size: [160, 30], text: "#TR_BUTTON_RESET_DEFAULTS", onclick_event: "reset_defaults" })
        btn_cancel: button({ pos: [410, 430], size: [100, 30], text: "#TR_BUTTON_CANCEL", onclick: window_go_back })
        btn_save: button({ pos: [520, 430], size: [100, 30], text: "#TR_BUTTON_OK", onclick_event: "save" })
    }, hotkey_config_rows_ui(HOTKEY_CONFIG_VISIBLE_ROWS))
}

[es=(window_hotkey_config, init)]
function hotkey_config_on_init(window) {
    __log_marker("window_show:window_hotkey_config")
    window_hotkey_config.load_mappings(false)
    window_hotkey_config.needs_rebuild = true
    window.list_scroll.max_value = window_hotkey_config.widgets.length - window_hotkey_config.visible_rows
}

[es=(window_hotkey_config, ui_draw_foreground)]
function hotkey_config_draw(window) {
    window_hotkey_config.update_rows(window)
    window_hotkey_config.needs_rebuild = false
}
