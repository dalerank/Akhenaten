log_info("akhenaten: temple info window started")

temple_info_window {
    ui {
        background   : outer_panel({  size [29, 18]})
        title        : text({ pos[0, 16], size[px(29), 13], text:"${building.name}", font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})

        inner_panel  : inner_panel({ pos[16, 56], size[27, 4] })
        workers_img  : image({ pack:PACK_GENERAL, id:134, offset:14, pos[40, 70] })
        workers_text : text({ text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers} ${loc.building_employee_needed} )", pos[70, 74], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) })
        workers_desc : text({ pos[70, 74 + 16], font: FONT_NORMAL_BLACK_ON_DARK })
        button_help  : image_button({ margin:{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134 })
        button_close : image_button({ margin:{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4 })
        show_overlay : button({ margin:{right:-64, bottom:-40}, size[23, 23]})
        god_image    : image({ pos[190, 134] })
        mothball     : button({ margin:{right:-90, bottom:-40}, size[23, 23]})
    }
}

[es=building_info_window]
info_window_temple_complex {
    related_buildings [BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST]
    ui {
        background   : outer_panel({ size: [29, 18]})
        title        : text({ pos[0, 16], size[px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})

        inner_panel  : inner_panel({ pos[16, 56], size[27, 4] })
        workers_img  : image({ pack:PACK_GENERAL, id:134, offset:14, pos[40, 70] })
        workers_text : text({ text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", pos[70, 74], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) })
        workers_desc : text({ pos[70, 74 + 16], font: FONT_NORMAL_BLACK_ON_DARK })
        button_help  : image_button({ margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134 })
        button_close : image_button({ margin{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4 })
        show_overlay : button({ margin{right:-64, bottom:-40}, size[23, 23]})
        god_image    : image({ pos[190, 134] })

        mothball     : button({ margin{right:-90, bottom:-40}, size[23, 23]})
    }
}

[es=building_info_window]
info_window_temple {
    related_buildings [BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST]
    ui : baseui(temple_info_window, {
    })
}

function info_window_temple_common_init(window) {
    var b = city.get_building(window.bid)
    var image_offset = 0

    switch (b.type) {
    case BUILDING_TEMPLE_OSIRIS: image_offset = 21; break
    case BUILDING_TEMPLE_RA: image_offset = 22; break
    case BUILDING_TEMPLE_PTAH: image_offset = 23; break
    case BUILDING_TEMPLE_SETH: image_offset = 24; break
    case BUILDING_TEMPLE_BAST: image_offset = 25; break
    default:
        return
    }

    var img_id = get_image({ pack: PACK_UNLOADED, id: 21, offset: image_offset })
    if (!img_id) {
        return
    }

    window.god_image.image = img_id.tid
}

[es=info_window_temple_init]
function info_window_temple_on_init(window) {
    info_window_temple_common_init(window)
}

[es=info_window_temple_complex_init]
function info_window_temple_complex_on_init(window) {
    info_window_temple_common_init(window)
}