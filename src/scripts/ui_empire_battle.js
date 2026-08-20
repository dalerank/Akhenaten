log_info("akhenaten: ui empire battle started")

function empire_window_draw_object_info_kingdome_army(ev, obj) {
    var battle = empire.active_battle
    if (battle.egyptian_months_to_travel_back > 0) {
        if (battle.egyptian_months_traveled === obj.distant_battle_travel_months) {
            var sb = empire_window.screen_bounds
            if (!sb.ready) {
                return
            }
            var ox = ((sb.min_pos.x + sb.max_pos.x - 240) / 2) | 0
            var oy = sb.max_pos.y - 68
            var text_id = battle.egyptian_months_to_travel_forth ? 15 : 16
            __lang_text_draw_multiline(47, text_id, ox, oy, 240, FONT_NORMAL_BLACK_ON_LIGHT)
        }
    }
}

function empire_window_draw_object_info_enemy_army(ev, obj) {
    var battle = empire.active_battle
    if (battle.months_until_battle > 0) {
        // enemy_months_traveled() historically returned egyptian_months_traveled.
        if (battle.egyptian_months_traveled === obj.distant_battle_travel_months) {
            var sb = empire_window.screen_bounds
            if (!sb.ready) {
                return
            }
            var ox = ((sb.min_pos.x + sb.max_pos.x - 240) / 2) | 0
            var oy = sb.max_pos.y - 68
            __lang_text_draw_multiline(47, 14, ox, oy, 240, FONT_NORMAL_BLACK_ON_LIGHT)
        }
    }
}

[es=(empire_window, draw_object_info), memory=frame]
function empire_window_draw_object_info(ev) {
    var obj = empire_window.selected_object
    if (!obj) {
        return
    }
    switch (obj.type) {
    case EMPIRE_OBJECT_KINGDOME_ARMY:
        empire_window_draw_object_info_kingdome_army(ev, obj)
        break
    case EMPIRE_OBJECT_ENEMY_ARMY:
        empire_window_draw_object_info_enemy_army(ev, obj)
        break
    }
}

function empire_window_draw_kingdome_army(ev) {
    var obj = empire.get_object(ev.object_index)
    var battle = empire.active_battle
    if (!(battle.egyptian_months_to_travel_forth > 0 || battle.egyptian_months_to_travel_back > 0)) {
        return
    }
    if (battle.egyptian_months_traveled !== obj.distant_battle_travel_months) {
        return
    }
    empire_window_draw_sprite_object(ev, obj)
}

function empire_window_draw_enemy_army(ev) {
    var obj = empire.get_object(ev.object_index)
    var battle = empire.active_battle
    if (battle.months_until_battle <= 0) {
        return
    }
    // Matches distant_battles_t::enemy_months_traveled() (returns egyptian_months_traveled).
    if (battle.egyptian_months_traveled !== obj.distant_battle_travel_months) {
        return
    }
    empire_window_draw_sprite_object(ev, obj)
}

function empire_window_draw_battle_icon(ev) {
    var obj = empire.get_object(ev.object_index)
    var img = get_image("pharaoh_general/empire_bits_00001")
    if (!img) {
        return
    }

    ui.image(img, empire_window_map_point(ev.draw_offset, obj.map_pos))
}

function empire_window_draw_distant_battle_path(ev) {
    if (!empire.has_distant_battle) {
        return
    }

    var n = empire.active_battle.path_length
    if (n <= 0) {
        return
    }

    var img = get_image(empire_window.open_trade_route)
    if (!img) {
        return
    }

    for (var i = 0; i < n; i++) {
        var p = empire.active_battle.path_point(i)
        var sp = empire_window_map_point(ev.draw_offset, p)
        ui.image(img, sp)
        if (i < n - 1) {
            var p2 = empire.active_battle.path_point(i + 1)
            var sp2 = empire_window_map_point(ev.draw_offset, p2)
            empire_window_route_segment_sprites(img, sp, sp2)
            if (empire.route_debug_points) {
                ui.fill_rect({ x: sp.x - 4, y: sp.y - 4 }, { x: 8, y: 8 }, COLOR_BLACK)
            }
        }
    }
}

function empire_window_draw_distant_battle_icon(ev) {
    if (!empire.has_distant_battle) {
        return
    }

    var ecity = empire.get_city(empire.active_battle.city)
    if (!ecity) {
        return
    }

    var battle_icon = get_image("pharaoh_general/empire_bits_00001")
    if (!battle_icon) {
        return
    }

    var battle_icon_pos = vec2i(empire_window_map_point(ev.draw_offset, ecity.empire_object.pos))
                            .add({x: -battle_icon.width / 2, y: -battle_icon.height / 2})

    ui.image(battle_icon, battle_icon_pos)
}

function empire_window_draw_dispatched_army_icon(ev) {
    if (empire.dispatched_army.state <= 0) {
        return
    }

    var army_icon = get_image("pharaoh_general/empire_bits_00009")
    if (!army_icon) {
        return
    }

    var army_icon_pos = vec2i(empire_window_map_point(ev.draw_offset, empire.dispatched_army.pos))
                            .add({x: -army_icon.width / 2, y: -army_icon.height / 2})

    ui.image(army_icon, army_icon_pos)
}
