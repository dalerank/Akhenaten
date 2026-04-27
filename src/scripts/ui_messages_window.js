log_info("akhenaten: messages window started")

function message_list_window_on_render_item(p) {
    var idx = p.user_data
    var rowX = p.x
    var rowY = p.y
    var font = p.flags ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK
    var read = __city_message_is_read(idx)
    var cat = __city_message_lang_category(idx)
    var typeOff = 0
    if (cat == 1) {
        typeOff = 2
    }
    if (cat == 4) {
        typeOff = 4
    }
    var msgIcon = get_image({ pack: PACK_GENERAL, id: 90, offset: (read ? 15 : 14) + typeOff })
    ui.image(msgIcon, [rowX, rowY])
    var month = __city_message_month(idx)
    var year = __city_message_year(idx)
    ui.label(__loc(25, month), [rowX + 42, rowY], font)
    ui.label_year(year, [rowX + 76, rowY], font)
    if (__city_message_eventmsg_body_id(idx) != -1) {
        var titleId = __city_message_eventmsg_title_id(idx)
        ui.label(__scenario_event_msg_text(titleId, 0), [rowX + 190, rowY], font)
    } else {
        ui.label(__lang_message_title_text(__city_message_mm_text_id(idx)), [rowX + 190, rowY], font)
    }
}

function message_list_window_open_entry(index) {
    __city_messages.current_message_id = index
    if (index >= __city_message_count()) {
        return
    }
    var mmTextId = __city_message_mm_text_id(index)
    var mmMsg = __lang_get_message_id(mmTextId)
    __city_message_mark_read(index)
    var year = __city_message_year(index)
    var month = __city_message_month(index)
    var param1 = __city_message_param1(index)
    var param2 = __city_message_param2(index)
    __ui_window_message_dialog_show_city_message(mmMsg, index, year, month, param1, param2, mmTextId)
}

function message_list_window_on_click_item(p) {
    if (!p) {
        return
    }
    message_list_window_open_entry(p.user_data)
}

var message_list_window_ref = null

function message_list_window_refresh_rows(window) {
    __city_message_sort_and_compact()
    var n = __city_message_count()
    window.messages_list.clear()
    for (var i = 0; i < n; i++) {
        window.messages_list.add_item("", i)
    }
}

function message_list_window_delete_at(message_index) {
    if (message_index < 0 || message_index >= __city_message_count()) {
        return
    }
    __city_messages.current_message_id = message_index
    __city_message_delete(message_index)
}

function message_list_window_on_rightclick_item(p) {
    if (!p) {
        return
    }
    message_list_window_delete_at(p.user_data)
    if (message_list_window_ref) {
        message_list_window_refresh_rows(message_list_window_ref)
    }
}

[es=(message_list_window, init)]
function message_list_window_on_init(window) {
    message_list_window_ref = window
    message_list_window_refresh_rows(window)
}

[es=modal_window]
message_list_window {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(22))/2]
    read_icon : {pack:PACK_GENERAL, id:90, offset:14}
    help_id: "message_game_control_messages"
    draw_underlying: true
    allow_rmb_goback: true

    ui {
        background    : outer_panel({size:[30, 22]})
        title         : header({pos[10, 10], size[px(30), 20], text[63, 0], align:"center"})

        messages_list : scrollable_list({pos[16, 42]
                                         size:[26, 16]
                                         view_items:15
                                         draw_scrollbar_always:true
                                         onrender_item: message_list_window_on_render_item
                                         onclick_item: message_list_window_on_click_item
                                         onrightclick_item: message_list_window_on_rightclick_item })

        message_icon  : dummy({pos[0, 0]})
        message_row   : dummy({pos[0, 0], size[px(13), 20]})
        message_read_icon : dummy({pos[0, 0]})
        message_month : text({pos[42, 0]})
        message_year  : text({pos[76, 0]})
        message_title : text({pos[190, 0], size[px(8), 20]})

        help_text     : text({margin{left:50, bottom:-45}, size[16 * 26 - 100, -1], text[63, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, multiline:true, wrap:16 * 26 - 100})
        empty_text    : text({margin{left:32, centery:-20}, size[16 * 26 - 48, -1], text[63, 1], enabled:false, font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:16 * 26 - 48})

        btnhelp       : help_button({tooltip:"#message_game_control_messages", onclick: function() { window_message_dialog_show("message_dialog_messages") } })
        btnclose      : close_button({tooltip:"#exit_this_panel", onclick: window_go_back })
    }
}