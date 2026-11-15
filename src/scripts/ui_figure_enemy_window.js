log_info("akhenaten: ui figure enemy window started")

function figure_enemy_info_window_setup(window, fid) {
    figure_info_window_setup_tabs(window)

    var f = city.get_figure(fid)
    if (!f.valid) {
        return
    }

    window.bigimage.image = f.params.first_img("big_image")
    window.phrase.text = ""
    f.setup_phrase()

    __figure_info_set_help(fid)
}

function figure_enemy_info_window_background(window) {
    var f = city.get_figure(__object_info_figure_id())

    window.name.text = f.name
    window.typename.text = f.class_name

    figure_info_window_update_toolbar(window, f)
    figure_info_window_sync_tab_selection(window)
    figure_info_check_phrase(window)
}

[es=figure_enemy_info_window]
figure_enemy_barbarian_info_window {
    related_figures [
        FIGURE_ENEMY_BARBARIAN_ARCHER, FIGURE_ENEMY_BARBARIAN_SWORD, FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_assyrian_info_window {
    related_figures [
        FIGURE_ENEMY_ASSYRIAN_ARCHER, FIGURE_ENEMY_ASSYRIAN_SWORD, FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_ASSYRIAN_WAR_SHIP, FIGURE_ENEMY_ASSYRIAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_canaanite_info_window {
    related_figures [
        FIGURE_ENEMY_CANAANITE_ARCHER, FIGURE_ENEMY_CANAANITE_SWORD, FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_CANAANITE_WAR_SHIP, FIGURE_ENEMY_CANAANITE_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_egyptian_info_window {
    related_figures [
        FIGURE_ENEMY_EGYPTIAN_SPEAR, FIGURE_ENEMY_EGYPTIAN_ARCHER, FIGURE_ENEMY_EGYPTIAN_FAST_SWORD,
        FIGURE_ENEMY_EGYPTIAN_CAMEL, FIGURE_ENEMY_EGYPTIAN_ELEPHANT, FIGURE_ENEMY_EGYPTIAN_CHARIOT,
        FIGURE_ENEMY_EGYPTIAN_SWORD, FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD, FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER, FIGURE_ENEMY_EGYPTIAN_AXE, FIGURE_ENEMY_EGYPTIAN_WARSHIP,
        FIGURE_ENEMY_EGYPTIAN_GALERA
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_kingdome_info_window {
    related_figures [
        FIGURE_ENEMY_KINGDOME_JAVELIN, FIGURE_ENEMY_KINGDOME_MOUNTED, FIGURE_ENEMY_KINGDOME_INFANTRY
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_hittite_info_window {
    related_figures [
        FIGURE_ENEMY_HITTITE_ARCHER, FIGURE_ENEMY_HITTITE_SPEARMAN, FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_HITTITE_WAR_SHIP, FIGURE_ENEMY_HITTITE_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_hyksos_info_window {
    related_figures [
        FIGURE_ENEMY_HYKSOS_ARCHER, FIGURE_ENEMY_HYKSOS_SWORDMAN, FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP,
        FIGURE_ENEMY_HYKSOS_WAR_SHIP, FIGURE_ENEMY_HYKSOS_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_kushite_info_window {
    related_figures [
        FIGURE_ENEMY_KUSHITE_SPEARMAN, FIGURE_ENEMY_KUSHITE_AXEMAN, FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_KUSHITE_WAR_SHIP, FIGURE_ENEMY_KUSHITE_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_libian_info_window {
    related_figures [
        FIGURE_ENEMY_LIBIAN_ARCHER, FIGURE_ENEMY_LIBIAN_SWORDMAN, FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_LIBIAN_WAR_SHIP, FIGURE_ENEMY_LIBIAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_nubian_info_window {
    related_figures [
        FIGURE_ENEMY_NUBIAN_ARCHER, FIGURE_ENEMY_NUBIAN_AXEMAN, FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_NUBIAN_WAR_SHIP, FIGURE_ENEMY_NUBIAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_persian_info_window {
    related_figures [
        FIGURE_ENEMY_PERSIAN_ARCHER, FIGURE_ENEMY_PERSIAN_SPEARMAN, FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_PERSIAN_WAR_SHIP, FIGURE_ENEMY_PERSIAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_phoenician_info_window {
    related_figures [
        FIGURE_ENEMY_PHOENICIAN_SPEARMAN, FIGURE_ENEMY_PHOENICIAN_SWORDMAN, FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_PHOENICIAN_WAR_SHIP, FIGURE_ENEMY_PHOENICIAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_roman_info_window {
    related_figures [
        FIGURE_ENEMY_ROMAN_ARCHER, FIGURE_ENEMY_ROMAN_LEGIONER, FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_ROMAN_WAR_SHIP, FIGURE_ENEMY_ROMAN_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_seapeople_info_window {
    related_figures [
        FIGURE_ENEMY_SEAPEOPLE_ARCHER, FIGURE_ENEMY_SEAPEOPLE_SWORDMAN, FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP,
        FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP, FIGURE_ENEMY_SEAPEOPLE_CHARIOT
    ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_bedouin_info_window {
    related_figures [ FIGURE_BEDOUIN ]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_naval_info_window {
    related_figures [FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP]
    ui : baseui(figure_info_window, {})
}

[es=figure_enemy_info_window]
figure_enemy_mummy_info_window {
    related_figures [FIGURE_MUMMY]
    ui : baseui(figure_info_window, {})
}

// Windows tagged [es=figure_enemy_info_window] fall back here when they have no exact handler.
[es=(figure_enemy_info_window, init)]
function figure_enemy_info_window_on_init(window) {
    figure_enemy_info_window_setup(window, __object_info_figure_id())
}

[es=(figure_enemy_info_window, window_info_background)]
function figure_enemy_info_window_on_window_info_background(window) {
    figure_enemy_info_window_background(window)
}

[es=(figure_enemy_info_window, select_figure)]
function figure_enemy_info_window_on_select_figure(ev) {
    figure_info_window_on_select_figure(ev)
}

[es=(figure_enemy_info_window, show_path)]
function figure_enemy_info_window_on_show_path(window) {
    figure_info_window_on_show_path(window)
}

[es=(figure_enemy_info_window, show_overlay)]
function figure_enemy_info_window_on_show_overlay(window) {
    figure_info_window_on_show_overlay(window)
}

[es=(figure_enemy_info_window, show_follow)]
function figure_enemy_info_window_on_show_follow(window) {
    figure_info_window_on_show_follow(window)
}
