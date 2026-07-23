log_info("akhenaten: ui_mansion_window.js loaded")

[es=building_info_window]
info_window_mansion {
    first_advisor : ADVISOR_IMPERIAL,
    related_buildings [BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_DYNASTY_MANSION]
    ui {
        background    : outer_panel({size[29, 20]}),

        title       : text({pos[0, 16], text:"${building.name}", size[px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        change_salary : button({textfn:change_salary_button_text, onclick:show_window_by_id("set_salary_window_mansion"), margin{centerx:-200, top:70}, size[400, 30], font: FONT_NORMAL_BLACK_ON_DARK }),

        resource_img  : resource_icon({pos[16, 44], resource:RESOURCE_GOLD}),
        savings_hold  : text({pos[44, 44], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos[32, 106], text:"${text.1}", wrap:px(27), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        salary_info   : text({pos[32, 150], text:"${text.5}", font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(25), multiline:true }),

        first_advisor : image_button({pos[40, -1], size[28, 28], pack:PACK_GENERAL, id:106 }),

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

function change_salary_button_text() {
    return __loc(52, player.salary_rank + 4) + " " + player.salary_amount + " " + __loc(52, 3)
}

[es=(info_window_mansion, init)]
function info_window_mansion_on_init(window) {
    var b = city.get_building(window.bid)
    if (b.has_road_access == false) {
        window.warning_text.text = __loc("#building_no_road_access")
    } else {
        window.warning_text.text = ""
    }
    //write window.protection_info.text = b.is_protected_by_police ? __loc("#mansion_protected_by_police") : __loc("#mansion_not_protected_theft")
    window.change_salary.readonly = scenario.has_won
    window.savings_hold.text = __loc(b.meta_text_id, 2) + " " + b.tax_income_or_storage + " Db"
}
