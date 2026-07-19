log_info("akhenaten: ui fort info window started")

[es=building_info_window]
info_window_fort {
    related_buildings [BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_GROUND]
    ui {
        background     : outer_panel({size [34, 18]})
        title          : text({pos[0, 16], size [px(31), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align:"center"})

        // Standard: animal sign + flag + morale pole (same stack as original fort info).
        batalion_icon  : image({ pack:PACK_GENERAL, id:127, pos[30, 30] })
        flag_img       : image({ pack:PACK_GENERAL, id:126, pos[30, 50] })
        morale_img     : image({ pack:PACK_GENERAL, id:54, pos[30, 70] })

        soldiers_lb    : text({ pos[100, 60], text:"${138.23}", font: FONT_NORMAL_BLACK_ON_LIGHT })
        soldiers_num   : text({ pos[290, 60], font: FONT_NORMAL_BLACK_ON_LIGHT })

        health_lb      : text({ pos[100, 80], text:"${138.24}", font: FONT_NORMAL_BLACK_ON_LIGHT })
        health_num     : text({ pos[290, 80], font: FONT_NORMAL_BLACK_ON_LIGHT })

        training_lb    : text({ pos[100, 100], text:"${138.25}", font: FONT_NORMAL_BLACK_ON_LIGHT })
        experience_img : image({ path:"pharaoh_general/paneling_00537", pos[265, 96] })
        training_num   : text({ pos[300, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })

        morale_lb      : text({ pos[100, 120], text:"${138.36}", font: FONT_NORMAL_BLACK_ON_LIGHT })
        morale_num     : text({ pos[290, 120], font: FONT_NORMAL_BLACK_ON_LIGHT })

        describe       : text({pos[32, 160], font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true, wrap:px(28) })

        button_help    : help_button({})
        button_close   : close_button({})
    }
}

function fort_info_window_company_type_text(figure_type) {
    if (figure_type == FIGURE_INFANTRY) { return 74 }
    if (figure_type == FIGURE_ARCHER) { return 75 }
    if (figure_type == FIGURE_FCHARIOTEER) { return 76 }
    return 73
}

function fort_info_window_flag_offset(figure_type) {
    if (figure_type == FIGURE_ARCHER) { return 10 }
    if (figure_type == FIGURE_FCHARIOTEER) { return 20 }
    return 0
}

function fort_info_window_health_text_id(form) {
    var health = Math.calc_percentage(form.total_damage, form.max_total_damage)
    if (health <= 0) { return 26 }
    if (health <= 20) { return 27 }
    if (health <= 40) { return 28 }
    if (health <= 55) { return 29 }
    if (health <= 70) { return 30 }
    if (health <= 90) { return 31 }
    return 32
}

// UIImage.image expects a full texture id (tid), not a pack offset.
function fort_info_window_set_image(elem, pack, id, offset) {
    var img = get_image({ pack: pack, id: id, offset: offset })
    if (!img) {
        elem.enabled = false
        return null
    }
    elem.enabled = true
    elem.image = img.tid
    return img
}

function fort_info_window_layout_standard(window, form) {
    var base_x = 16
    var y = 16
    var column_w = 40

    var icon = fort_info_window_set_image(window.batalion_icon, PACK_GENERAL, 127, form.batalion_id - 1)
    if (icon) {
        window.batalion_icon.pos = { x: base_x + ((column_w - icon.width) / 2) | 0, y: y }
        y += icon.height
    }

    var flag = fort_info_window_set_image(window.flag_img, PACK_GENERAL, 126, fort_info_window_flag_offset(form.figure_type))
    if (flag) {
        window.flag_img.pos = { x: base_x + ((column_w - flag.width) / 2) | 0, y: y }
        y += flag.height
    }

    var pole = fort_info_window_set_image(window.morale_img, PACK_GENERAL, 54, 20 - ((form.morale / 5) | 0))
    if (pole) {
        window.morale_img.pos = { x: base_x + ((column_w - pole.width) / 2) | 0, y: y }
    }
}

[es=(info_window_fort, init)]
function info_window_fort_on_init(window) {
    var b = city.get_building(window.bid)
    // fort_ground keeps the same formation_id as the main fort building
    var form = city.get_formation(b.formation_id)
    if (!form || !form.in_use) {
        window.title.text = __loc(89, 0)
        window.describe.text = __loc(89, 2)
        window.soldiers_num.text = ""
        window.health_num.text = ""
        window.training_num.text = ""
        window.morale_num.text = ""
        window.batalion_icon.enabled = false
        window.flag_img.enabled = false
        window.morale_img.enabled = false
        window.experience_img.enabled = false
        return
    }

    var company_type = fort_info_window_company_type_text(form.figure_type)
    window.title.text = __loc(138, form.batalion_id - 1) + " " + __loc(138, company_type)

    fort_info_window_layout_standard(window, form)

    window.soldiers_num.text = "" + form.num_figures
    window.health_num.text = __loc(138, fort_info_window_health_text_id(form))

    var exp_level = form.experience / 100
    if (exp_level < 0) { exp_level = 0 }
    if (exp_level > 5) { exp_level = 5 }
    exp_level = exp_level | 0
    var exp_image = get_image("pharaoh_general/paneling_00537")
    if (exp_image) {
        window.experience_img.enabled = true
        window.experience_img.image = exp_image.tid + exp_level
    } else {
        window.experience_img.enabled = false
    }
    window.training_num.text = __loc(138, 60 + exp_level)

    if (form.cursed_by_seth) {
        window.morale_lb.text = __loc(138, 59)
        window.morale_num.text = ""
    } else {
        window.morale_lb.text = __loc(138, 36)
        window.morale_num.text = __loc(138, 37 + ((form.morale / 5) | 0))
    }

    var group_id = 138
    var text_id = 11
    if (form.cursed_by_seth) {
        group_id = 89
        text_id = 1
    } else if (form.num_figures > 0) {
        group_id = 89
        text_id = 2
    } else if (city.count_active_buildings(BUILDING_RECRUITER) > 0) {
        text_id = 10
    }
    window.describe.text = __loc(group_id, text_id)
}
