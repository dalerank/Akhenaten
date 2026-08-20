log_info("akhenaten: ui empire map started")

function empire_window_set_xy(dst, x, y) {
    dst.x = x
    dst.y = y
}

function empire_window_refresh_screen_bounds() {
    var sb = empire_window.screen_bounds
    empire_window_set_xy(sb.min_pos, 0, 0)
    empire_window_set_xy(sb.max_pos, screen.width, screen.height)
    sb.ready = true
}

function empire_window_rebuild_camera() {
    var sb = empire_window.screen_bounds
    var map = empire_window.map_size
    var cam = empire_window.camera
    if (!sb.ready || !map) {
        cam.valid = false
        return null
    }

    var clip_x = sb.min_pos.x + empire_window.start_pos.x
    var clip_y = sb.min_pos.y + empire_window.start_pos.y
    var area_x = Math.max(1, (sb.max_pos.x - sb.min_pos.x) - empire_window.finish_pos.x)
    var area_y = Math.max(1, (sb.max_pos.y - sb.min_pos.y) - empire_window.finish_pos.y)
    var scale = Math.max(area_x / map.x, area_y / map.y)
    var scale_safe = Math.max(0.001, scale)
    var scaled_x = Math.max(1, Math.round(map.x * scale))
    var scaled_y = Math.max(1, Math.round(map.y * scale))
    var base_x = clip_x + Math.max(0, ((area_x - scaled_x) / 2) | 0)
    var base_y = clip_y + Math.max(0, ((area_y - scaled_y) / 2) | 0)
    var scroll = __empire_map_get_scroll()
    var origin_x = base_x - Math.round(scroll.x * scale)
    var origin_y = base_y - Math.round(scroll.y * scale)
    var vp_x = Math.min(map.x, Math.max(1, Math.round(area_x / scale_safe)))
    var vp_y = Math.min(map.y, Math.max(1, Math.round(area_y / scale_safe)))

    cam.scale = scale
    cam.scale_safe = scale_safe
    empire_window_set_xy(cam.clip, clip_x, clip_y)
    empire_window_set_xy(cam.area, area_x, area_y)
    empire_window_set_xy(cam.base, base_x, base_y)
    empire_window_set_xy(cam.draw_origin, origin_x, origin_y)
    empire_window_set_xy(cam.viewport, vp_x, vp_y)
    empire_window_set_xy(cam.map, map.x, map.y)
    empire_window_set_xy(empire_window.draw_offset, origin_x, origin_y)
    cam.valid = true
    return cam
}

function empire_window_camera() {
    var cam = empire_window.camera
    if (cam.valid) {
        return cam
    }
    return empire_window_rebuild_camera()
}

function empire_window_map_scale() {
    var cam = empire_window_camera()
    return cam ? cam.scale : 1
}

function empire_window_is_outside_map(x, y) {
    var cam = empire_window_camera()
    if (!cam) {
        return true
    }
    var o = cam.clip
    var size = cam.area
    return x < o.x || x >= o.x + size.x || y < o.y || y >= o.y + size.y
}

function empire_window_map_point(draw_offset, pos) {
    var s = empire_window_map_scale()
    return {
        x: draw_offset.x + Math.round(pos.x * s),
        y: draw_offset.y + Math.round(pos.y * s)
    }
}

function empire_window_city_is_trading_type(type) {
    return type == EMPIRE_CITY_PHARAOH_TRADING
        || type == EMPIRE_CITY_EGYPTIAN_TRADING
        || type == EMPIRE_CITY_FOREIGN_TRADING
}

function empire_window_city_image(type) {
    var tid = __empire_city_image_id(type)
    if (tid <= 0) {
        return null
    }
    return get_image({ tid: tid })
}

function empire_window_draw_map_animation(object_index, img, draw_pos, scale) {
    if (!img || !img.animation_speed_id) {
        return
    }
    var frame = __empire_update_map_animation(object_index, img.tid)
    var anim = get_image({ tid: img.tid + frame })
    if (!anim) {
        return
    }
    ui.image_scaled(anim, {
        x: draw_pos.x + Math.round((img.animation_offset_x || 0) * scale),
        y: draw_pos.y + Math.round((img.animation_offset_y || 0) * scale)
    }, scale)
}

function empire_window_draw_city(ev) {
    var obj = empire.get_object(ev.object_index)
    var city = empire.get_city(obj.city_id)
    if (!city || !city.in_use) {
        return
    }

    var img = empire_window_city_image(city.type)
    if (!img) {
        return
    }

    var scale = empire_window_map_scale()
    var draw_pos = empire_window_map_point(ev.draw_offset, obj.map_pos)
    ui.image_scaled(img, draw_pos, scale)

    var scaled_w = Math.max(1, Math.round(img.width * scale))
    var scaled_h = Math.max(1, Math.round(img.height * scale))
    var name = city.name

    if (city.is_sieged) {
        var siege = get_image("pharaoh_general/empire_bits_00001")
        if (siege) {
            ui.image(siege, {
                x: draw_pos.x + ((scaled_w / 2 - siege.width / 2) | 0),
                y: draw_pos.y - siege.height - 5
            })
        }
    }

    empire_window_request_city_trade_route(city, ev.draw_offset, false)

    var letter_h = 11
    var text_pos = {
        x: draw_pos.x + scaled_w,
        y: draw_pos.y + (((scaled_h - letter_h) / 2) | 0)
    }
    ui.label_colored(name, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED)

    if (city.is_sieged) {
        ui.label_colored("under siege", { x: text_pos.x, y: text_pos.y + letter_h + 2 }, FONT_SMALL_PLAIN, COLOR_FONT_RED)
    }

    empire_window_draw_map_animation(ev.object_index, img, draw_pos, scale)
}

function empire_window_draw_text(ev) {
    var obj = empire.get_object(ev.object_index)
    var sp = empire_window_map_point(ev.draw_offset, obj.map_pos)
    ui.label_colored(obj.label, { x: sp.x - 5, y: sp.y }, FONT_SMALL_PLAIN, COLOR_FONT_SHITTY_BROWN)
}

function empire_window_draw_sprite_object(ev, obj) {
    var image_id = obj.map_image_id
    if (!image_id) {
        return
    }
    var img = get_image({ tid: image_id })
    if (!img) {
        return
    }
    var scale = empire_window_map_scale()
    var draw_pos = empire_window_map_point(ev.draw_offset, obj.map_pos)
    ui.image_scaled(img, draw_pos, scale)
    empire_window_draw_map_animation(ev.object_index, img, draw_pos, scale)
}

function empire_window_draw_ornament(ev) {
    empire_window_draw_sprite_object(ev, empire.get_object(ev.object_index))
}

function empire_window_route_segment_sprites(img, p1, p2) {
    var dx = p2.x - p1.x
    var dy = p2.y - p1.y
    var len = 0.2 * Math.sqrt(dx * dx + dy * dy)
    if (len <= 0) {
        return
    }
    var scaled_x = dx / len
    var scaled_y = dy / len
    var progress = 1.0
    while (progress < len) {
        ui.image(img, {
            x: p1.x + ((scaled_x * progress) | 0),
            y: p1.y + ((scaled_y * progress) | 0)
        })
        progress += 1.0
    }
}

function empire_window_trade_route_state(city) {
    var rs = empire_window.route_state
    var is_selected = empire_window.selected_city == city.id
    if (city.is_open) {
        return is_selected ? rs.open_selected : rs.open
    }
    return is_selected ? rs.closed_selected : rs.closed
}

function empire_window_prepare_deferred_trade_route() {
    empire_window.deferred_route_city_id = -1
    var cid = empire_window.selected_city
    if (!cid) {
        return
    }
    var city = empire.get_city(cid)
    if (!city || !city.in_use || !empire_window_city_is_trading_type(city.type)) {
        return
    }
    var rs = empire_window.route_state
    var state = empire_window_trade_route_state(city)
    if (state == rs.open_selected || state == rs.closed_selected) {
        empire_window.deferred_route_city_id = cid
    }
}

function empire_window_request_city_trade_route(city, draw_offset, force) {
    if (!city || !empire_window_city_is_trading_type(city.type)) {
        return
    }

    if (!force && city.id == empire_window.deferred_route_city_id) {
        return
    }

    var rs = empire_window.route_state
    var state = empire_window_trade_route_state(city)
    if (state == rs.closed || empire.trade_route_num_points(city.route_id) <= 0) {
        return
    }

    empire_window_draw_trade_route({
        draw_offset: draw_offset,
        route_id: city.route_id,
        effect: state
    })
}

function empire_window_map_background_image() {
    var cfg = get_mission_config(scenario.campaign_scenario_id)
    if (cfg && cfg.map_background) {
        return get_image(cfg.map_background)
    }
    return get_image(empire_window.image)
}

function empire_window_draw_map_begin(ev) {
    var img = empire_window_map_background_image()
    if (img) {
        ui.image_scaled(img, ev.draw_offset, empire_window_map_scale())
    }
}

function empire_window_draw_map_objects(ev) {
    var payload = { draw_offset: ev.draw_offset, object_index: 0 }
    for (var i = 0; i < empire.object_slots; i++) {
        var obj = empire.get_object(i)
        if (!obj.in_use) {
            continue
        }
        // LAND/SEA pak route markers skipped: city routes drawn via request_city_trade_route.
        // TRADER slots skipped: live traders drawn from g_empire_traders.
        // DISTANT_BATTLE_ROUTE skipped: full path drawn once from active_battle in draw_map.
        switch (obj.type) {
        case EMPIRE_OBJECT_LAND_TRADE_ROUTE:
        case EMPIRE_OBJECT_SEA_TRADE_ROUTE:
        case EMPIRE_OBJECT_TRADER:
        case EMPIRE_OBJECT_DISTANT_BATTLE_ROUTE:
            break
        case EMPIRE_OBJECT_CITY:
            payload.object_index = i
            empire_window_draw_city(payload)
            break
        case EMPIRE_OBJECT_TEXT:
            payload.object_index = i
            empire_window_draw_text(payload)
            break
        case EMPIRE_OBJECT_ORNAMENT:
            payload.object_index = i
            empire_window_draw_ornament(payload)
            break
        case EMPIRE_OBJECT_KINGDOME_ARMY:
            payload.object_index = i
            empire_window_draw_kingdome_army(payload)
            break
        case EMPIRE_OBJECT_ENEMY_ARMY:
            payload.object_index = i
            empire_window_draw_enemy_army(payload)
            break
        case EMPIRE_OBJECT_BATTLE_ICON:
            payload.object_index = i
            empire_window_draw_battle_icon(payload)
            break
        }
    }
}

function empire_window_draw_invasion_warnings(ev) {
    var scale = empire_window_map_scale()
    for (var i = 0; i < invasions.warning_slots; i++) {
        var w = invasions.get_warning(i)
        if (!w.in_use || !w.handled) {
            continue
        }
        var img = get_image({ tid: w.image_id })
        if (!img) {
            continue
        }
        ui.image_scaled(img, empire_window_map_point(ev.draw_offset, w.pos), scale)
    }
}

function empire_window_draw_deferred_trade_route(ev) {
    var cid = empire_window.deferred_route_city_id
    empire_window.deferred_route_city_id = -1
    if (cid < 0) {
        return
    }
    var city = empire.get_city(cid)
    if (!city || !city.in_use) {
        return
    }
    empire_window_request_city_trade_route(city, ev.draw_offset, true)
}

function empire_window_draw_trade_route(ev) {
    var rs = empire_window.route_state
    if (ev.effect == rs.closed) {
        return
    }
    var route_id = ev.route_id
    var n = empire.trade_route_num_points(route_id)
    if (n <= 0) {
        return
    }
    var imgDesc = null
    switch (ev.effect) {
    case rs.closed_selected:
        imgDesc = empire_window.closed_trade_route_hl
        break
    case rs.open:
        imgDesc = empire_window.open_trade_route
        break
    case rs.open_selected:
        imgDesc = empire_window.open_trade_route_hl
        break
    default:
        return
    }
    var img = get_image(imgDesc)
    if (!img) {
        return
    }
    for (var i = 0; i < n; i++) {
        var p = empire.trade_route_point(route_id, i)
        var sp = empire_window_map_point(ev.draw_offset, p)
        ui.image(img, sp)
        if (i < n - 1) {
            var p2 = empire.trade_route_point(route_id, i + 1)
            var sp2 = empire_window_map_point(ev.draw_offset, p2)
            empire_window_route_segment_sprites(img, sp, sp2)
            if (empire.route_debug_points) {
                ui.fill_rect({ x: sp.x - 4, y: sp.y - 4 }, { x: 8, y: 8 }, COLOR_BLACK)
            }
        }
    }
}

function empire_window_draw_trader(ev) {
    var t = empire.get_trader(ev.index)
    if (!t || !t.is_active) {
        return
    }

    var img = get_image({ pack: PACK_GENERAL, id: 179, offset: t.is_ship ? 0 : 1 })
    if (!img) {
        return
    }

    var flags = (!t.is_ship && t.faces_left) ? UiFlags_Mirrored : UiFlags_None
    ui.image(img, empire_window_map_point(ev.draw_offset, t.current_position), flags)
}

function empire_window_draw_traders(ev) {
    var payload = { draw_offset: ev.draw_offset, index: 0 }
    for (var i = 0; i < empire.trader_slots; i++) {
        payload.index = i
        empire_window_draw_trader(payload)
    }
}

function empire_window_city_at_screen_pos(draw_offset, mx, my) {
    var scale = empire_window_map_scale()
    for (var i = 0; i < empire.object_slots; i++) {
        var obj = empire.get_object(i)
        if (!obj.in_use || obj.type != EMPIRE_OBJECT_CITY) {
            continue
        }
        var city = empire.get_city(obj.city_id)
        if (!city || !city.in_use || city.type == EMPIRE_CITY_OURS) {
            continue
        }
        var img = empire_window_city_image(city.type)
        if (!img) {
            continue
        }
        var draw_pos = empire_window_map_point(draw_offset, obj.map_pos)
        var scaled_w = Math.max(1, Math.round(img.width * scale))
        var scaled_h = Math.max(1, Math.round(img.height * scale))
        if (mx > draw_pos.x && my > draw_pos.y
            && mx < draw_pos.x + scaled_w && my < draw_pos.y + scaled_h) {
            return city
        }
    }
    return null
}

function empire_window_update_map_hover_tooltip(draw_offset) {
    ui.set_tooltip("")
    if (!empire_window.camera.valid || empire_window_is_outside_map(__mouse.x, __mouse.y)) {
        return
    }
    var city = empire_window_city_at_screen_pos(draw_offset, __mouse.x, __mouse.y)
    if (city) {
        ui.set_tooltip(city.name)
    }
}

function empire_window_draw_map(window) {
    var cam = empire_window_camera()
    if (!cam) {
        return
    }

    ui.set_clip_rectangle(cam.clip, cam.area)
    __empire_map_set_viewport(cam.viewport)

    var draw_offset = cam.draw_origin
    var payload = { draw_offset: draw_offset }

    empire_window_prepare_deferred_trade_route()
    empire_window_update_map_hover_tooltip(draw_offset)

    empire_window_draw_map_begin(payload)
    empire_window_draw_map_objects(payload)
    empire_window_draw_invasion_warnings(payload)
    empire_window_draw_traders(payload)
    empire_window_draw_distant_battle_path(payload)
    empire_window_draw_deferred_trade_route(payload)

    var wpos = window.pos || { x: 0, y: 0 }
    ui.begin_widget(wpos)
    empire_window_draw_distant_battle_icon(payload)
    empire_window_draw_dispatched_army_icon(payload)
    ui.end_widget()

    ui.reset_clip_rectangle()
}
