log_info("akhenaten: hotkey_actions started")

function hotkey_map_from_pairs(pairs) {
    var m = {}
    for (var i = 0; i < pairs.length; i++) {
        m[pairs[i][0]] = pairs[i][1]
    }
    return m
}

function hotkey_action_is_arrow(action) {
    return action === HOTKEY_ARROW_UP
        || action === HOTKEY_ARROW_DOWN
        || action === HOTKEY_ARROW_LEFT
        || action === HOTKEY_ARROW_RIGHT
}

function hotkey_scroll_arrow(action, is_down) {
    switch (action) {
    case HOTKEY_ARROW_UP: __scroll_arrow(0, is_down); break
    case HOTKEY_ARROW_DOWN: __scroll_arrow(1, is_down); break
    case HOTKEY_ARROW_LEFT: __scroll_arrow(2, is_down); break
    case HOTKEY_ARROW_RIGHT: __scroll_arrow(3, is_down); break
    }
}

function hotkey_action_is_repeatable(action) {
    return action === HOTKEY_INCREASE_GAME_SPEED
        || action === HOTKEY_DECREASE_GAME_SPEED
        || action === HOTKEY_DEBUG_1_UP
        || action === HOTKEY_DEBUG_1_DOWN
        || action === HOTKEY_DEBUG_RENDER_UP
        || action === HOTKEY_DEBUG_RENDER_DOWN
}

var hotkey_bindings = {
    defs: [],
    arrows: []
}

function hotkey_bindings_add_def(defs, key, modifiers, action, repeatable) {
    if (!key) {
        return
    }
    defs.push({
        key: key,
        modifiers: modifiers | 0,
        action: action,
        repeatable: repeatable ? 1 : 0
    })
}

function hotkey_bindings_rebuild() {
    var defs = []
    var arrows = []
    for (var action = HOTKEY_NONE + 1; action < HOTKEY_MAX_ITEMS; action++) {
        var m = __hotkey_read_mapping(action, 0)
        if (!m) {
            continue
        }
        if (hotkey_action_is_arrow(action)) {
            if (m.key) {
                arrows.push({ key: m.key, action: action })
            }
            if (m.alt_key) {
                arrows.push({ key: m.alt_key, action: action })
            }
        } else {
            var repeatable = hotkey_action_is_repeatable(action)
            hotkey_bindings_add_def(defs, m.key, m.modifiers, action, repeatable)
            hotkey_bindings_add_def(defs, m.alt_key, m.alt_modifiers, action, repeatable)
        }
    }
    hotkey_bindings.defs = defs
    hotkey_bindings.arrows = arrows
}

[es=event_hotkey_bindings_changed]
function hotkey_on_bindings_changed(ev) {
    hotkey_bindings_rebuild()
}

[es=event_level_post_load]
function hotkey_on_level_post_load(ev) {
    hotkey_bindings_rebuild()
}

[es=event_hotkey_key]
function hotkey_on_key(ev) {
    if (ui.window_is("window_hotkey_editor")) {
        emit event_hotkey_editor_key{ key: ev.key, modifiers: ev.modifiers, pressed: ev.pressed }
        return
    }

    if (ev.key === KEY_NONE) {
        return
    }

    var i
    if (ev.pressed) {
        for (i = 0; i < hotkey_bindings.arrows.length; i++) {
            if (hotkey_bindings.arrows[i].key === ev.key) {
                hotkey_scroll_arrow(hotkey_bindings.arrows[i].action, 1)
            }
        }
        if (ev.key === KEY_ENTER && ev.modifiers === KEY_MOD_NONE) {
            __hotkeys.enter_pressed = 1
        }
        if (ev.key === KEY_ESCAPE && ev.modifiers === KEY_MOD_NONE) {
            __hotkeys.escape_pressed = 1
        }
        for (i = 0; i < hotkey_bindings.defs.length; i++) {
            var d = hotkey_bindings.defs[i]
            if (d.key === ev.key && d.modifiers === ev.modifiers && (!ev.repeat || d.repeatable)) {
                emit event_hotkey_fired{ action: d.action }
            }
        }
        return
    }

    for (i = 0; i < hotkey_bindings.arrows.length; i++) {
        if (hotkey_bindings.arrows[i].key === ev.key) {
            hotkey_scroll_arrow(hotkey_bindings.arrows[i].action, 0)
        }
    }
}

var hotkey_actions = {
    advisors: hotkey_map_from_pairs([
        [HOTKEY_SHOW_ADVISOR_LABOR, ADVISOR_LABOR],
        [HOTKEY_SHOW_ADVISOR_MILITARY, ADVISOR_MILITARY],
        [HOTKEY_SHOW_ADVISOR_KINGDOME, ADVISOR_IMPERIAL],
        [HOTKEY_SHOW_ADVISOR_RATINGS, ADVISOR_RATINGS],
        [HOTKEY_SHOW_ADVISOR_TRADE, ADVISOR_TRADE],
        [HOTKEY_SHOW_ADVISOR_POPULATION, ADVISOR_POPULATION],
        [HOTKEY_SHOW_ADVISOR_HEALTH, ADVISOR_HEALTH],
        [HOTKEY_SHOW_ADVISOR_EDUCATION, ADVISOR_EDUCATION],
        [HOTKEY_SHOW_ADVISOR_ENTERTAINMENT, ADVISOR_ENTERTAINMENT],
        [HOTKEY_SHOW_ADVISOR_RELIGION, ADVISOR_RELIGION],
        [HOTKEY_SHOW_ADVISOR_FINANCIAL, ADVISOR_FINANCIAL],
        [HOTKEY_SHOW_ADVISOR_CHIEF, ADVISOR_CHIEF],
        [HOTKEY_SHOW_ADVISOR_HOUSING, ADVISOR_HOUSING]
    ]),
    buildings: hotkey_map_from_pairs([
        [HOTKEY_BUILD_VACANT_HOUSE, BUILDING_HOUSE_VACANT_LOT],
        [HOTKEY_BUILD_CLEAR_LAND, BUILDING_CLEAR_LAND],
        [HOTKEY_BUILD_ROAD, BUILDING_ROAD],
        [HOTKEY_BUILD_ARCHITECT, BUILDING_ARCHITECT_POST],
        [HOTKEY_BUILD_WALL, BUILDING_MUD_WALL],
        [HOTKEY_BUILD_GATEHOUSE, BUILDING_MUD_GATEHOUSE],
        [HOTKEY_BUILD_FIREHOUSE, BUILDING_FIREHOUSE],
        [HOTKEY_BUILD_GRANARY, BUILDING_GRANARY],
        [HOTKEY_BUILD_STORAGE_YARD, BUILDING_STORAGE_YARD],
        [HOTKEY_BUILD_BAZAAR, BUILDING_BAZAAR],
        [HOTKEY_BUILD_PLAZA, BUILDING_PLAZA],
        [HOTKEY_BUILD_GARDENS, BUILDING_GARDENS],
        [HOTKEY_BUILD_WATERLIFT, BUILDING_WATER_LIFT],
        [HOTKEY_BUILD_CANAL, BUILDING_IRRIGATION_DITCH],
        [HOTKEY_BUILD_WATER_SUPPLY, BUILDING_WATER_SUPPLY],
        [HOTKEY_BUILD_APOTHECARY, BUILDING_APOTHECARY],
        [HOTKEY_BUILD_ROADBLOCK, BUILDING_ROADBLOCK]
    ]),
    overlays: hotkey_map_from_pairs([
        [HOTKEY_SHOW_OVERLAY_WATER, 1],
        [HOTKEY_SHOW_OVERLAY_FIRE, 1],
        [HOTKEY_SHOW_OVERLAY_DAMAGE, 1],
        [HOTKEY_SHOW_OVERLAY_CRIME, 1],
        [HOTKEY_SHOW_OVERLAY_PROBLEMS, 1],
        [HOTKEY_SHOW_OVERLAY_MALARIA_RISK, 1],
        [HOTKEY_SHOW_OVERLAY_DISEASE, 1],
        [HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS, 1]
    ]),
    handlers: hotkey_map_from_pairs([
        [HOTKEY_TOGGLE_PAUSE, function(a) { emit event_toggle_pause{ value: a } }],
        [HOTKEY_TOGGLE_OVERLAY, function(a) { emit event_toggle_overlay{ value: a } }],
        [HOTKEY_TOGGLE_FLAT_BUILDINGS, function(a) { emit event_toggle_flat_buildings{ value: a } }],
        [HOTKEY_CYCLE_LEGION, function(a) { emit event_toggle_legion{ value: a } }],
        [HOTKEY_INCREASE_GAME_SPEED, function(a) { emit event_change_gamespeed{ increase: true } }],
        [HOTKEY_DECREASE_GAME_SPEED, function(a) { emit event_change_gamespeed{ increase: false } }],
        [HOTKEY_ROTATE_MAP_LEFT, function(a) { emit event_rotate_map{ value: a } }],
        [HOTKEY_ROTATE_MAP_RIGHT, function(a) { emit event_rotate_map{ value: a } }],
        [HOTKEY_EDITOR_TOGGLE_BATTLE_INFO, function(a) { emit event_editor_toggle_battle_info{ value: a } }],
        [HOTKEY_LOAD_FILE, function(a) {
            if (game.editor_is_active()) {
                emit event_load_scenario{ value: a }
            } else {
                emit event_load_city{ value: a }
            }
        }],
        [HOTKEY_SAVE_FILE, function(a) {
            if (game.editor_is_active()) {
                emit event_save_scenario{ value: a }
            } else {
                emit event_save_city{ value: a }
            }
        }],
        [HOTKEY_QUICKSAVE, function(a) { emit event_quicksave{ value: a } }],
        [HOTKEY_QUICKLOAD, function(a) { emit event_quickload{ value: a } }],
        [HOTKEY_ROTATE_BUILDING, function(a) { emit event_rotate_building{ value: a } }],
        [HOTKEY_CHANGE_BUILDING_VARIANT, function(a) { emit event_change_building_variant{ value: a } }],
        [HOTKEY_GO_TO_BOOKMARK_1, function(a) { emit event_goto_bookmark{ value: 0 } }],
        [HOTKEY_GO_TO_BOOKMARK_2, function(a) { emit event_goto_bookmark{ value: 1 } }],
        [HOTKEY_GO_TO_BOOKMARK_3, function(a) { emit event_goto_bookmark{ value: 2 } }],
        [HOTKEY_GO_TO_BOOKMARK_4, function(a) { emit event_goto_bookmark{ value: 3 } }],
        [HOTKEY_SET_BOOKMARK_1, function(a) { emit event_set_bookmark{ value: 0 } }],
        [HOTKEY_SET_BOOKMARK_2, function(a) { emit event_set_bookmark{ value: 1 } }],
        [HOTKEY_SET_BOOKMARK_3, function(a) { emit event_set_bookmark{ value: 2 } }],
        [HOTKEY_SET_BOOKMARK_4, function(a) { emit event_set_bookmark{ value: 3 } }],
        [HOTKEY_CENTER_WINDOW, function(a) { emit event_app_center_screen{ value: a } }],
        [HOTKEY_TOGGLE_FULLSCREEN, function(a) { emit event_app_toggle_fullscreen{ value: a } }],
        [HOTKEY_SAVE_SCREENSHOT, function(a) { emit event_app_screenshot{ value: a } }],
        [HOTKEY_SAVE_CITY_SCREENSHOT, function(a) { emit event_app_city_screenshot{ value: a } }],
        [HOTKEY_COPY_BUILD, function(a) { emit event_copy_build_from_cursor{ value: 1 } }],
        [HOTKEY_DEBUG_1_UP, function(a) { emit event_debug_tile_change{ value: 1 } }],
        [HOTKEY_DEBUG_1_DOWN, function(a) { emit event_debug_tile_change{ value: -1 } }],
        [HOTKEY_DEBUG_RENDER_UP, function(a) { emit event_debug_render_change{ value: 1 } }],
        [HOTKEY_DEBUG_RENDER_DOWN, function(a) { emit event_debug_render_change{ value: -1 } }]
    ])
}

[es=event_hotkey_fired]
function hotkey_on_fired(ev) {
    var action = ev.action

    var advisor = hotkey_actions.advisors[action]
    if (advisor !== undefined && advisor !== null) {
        emit event_show_advisor{ advisor: advisor }
        return
    }

    var building = hotkey_actions.buildings[action]
    if (building !== undefined && building !== null) {
        emit event_city_building_mode{ value: building }
        return
    }

    if (hotkey_actions.overlays[action]) {
        emit event_hotkey_overlay{ value: action }
        return
    }

    var handler = hotkey_actions.handlers[action]
    if (handler) {
        handler(action)
    }
}
