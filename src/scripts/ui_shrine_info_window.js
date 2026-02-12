log_info("akhenaten: shrine info window started")

shrine_info_window {
    ui {
        background   : outer_panel({ size: [29, 14] })
        title        : text({ pos[0, 16], size[px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        warning_text : text({ pos[20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        god_image    : image({ pos[190, 94] })
        show_overlay : button({ margin:{right:-64, bottom:-40}, size:[23, 23] })

        button_help  : help_button({})
        button_close : close_button({})
    }
}

[es=building_info_window]
info_window_shrine {
    related_buildings [BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST]
    ui : baseui(shrine_info_window, {
    })
}

function info_window_shrine_common_init(window) {
    var b = city.get_building(window.bid)
    var image_offset = 0
    var title_id = 0, text_id = 1

    switch (b.type) {
    case BUILDING_SHRINE_OSIRIS: image_offset = 21; title_id = 0; text_id = 1; break
    case BUILDING_SHRINE_RA:     image_offset = 22; title_id = 2; text_id = 3; break
    case BUILDING_SHRINE_PTAH:   image_offset = 23; title_id = 4; text_id = 5; break
    case BUILDING_SHRINE_SETH:   image_offset = 24; title_id = 6; text_id = 7; break
    case BUILDING_SHRINE_BAST:   image_offset = 25; title_id = 8; text_id = 9; break
    default:
        return
    }

    var img_id = get_image({ pack: PACK_UNLOADED, id: 21, offset: image_offset })
    if (img_id) {
        window.god_image.image = img_id.tid
    }

    window.title.text = __loc(161, title_id)
    window.warning_text.text = __loc(161, text_id)
}

[es=info_window_shrine_init]
function info_window_shrine_on_init(window) {
    info_window_shrine_common_init(window)
}
