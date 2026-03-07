log_info("akhenaten: ui advisor labor started")

advisor_labors_window {
    ui {
        background      : outer_panel({size[40, 27]})

        title           : text({pos[60, 12], text{group:50, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT })
        advisor_icon    : image({pack:PACK_GENERAL, id:128, offset:0, pos:[10, 10] })

        // table headers
        h1              : text({pos[60, 46], text{group:50, id:21}, font : FONT_SMALL_PLAIN })
        h2              : text({pos[170, 46], text{group:50, id:22}, font : FONT_SMALL_PLAIN })
        h3              : text({pos[400, 46], text{group:50, id:23}, font : FONT_SMALL_PLAIN })
        h4              : text({pos[500, 46], text{group:50, id:24}, font : FONT_SMALL_PLAIN })

        // employed
        main_panel      : inner_panel({pos[32, 65], size[36, 16]})
        item            : dummy({pos[40, 25], size:[px(35), 22], })
        item_image      : image({pack:PACK_GENERAL, id:94, pos:[40, 4], enabled:false})
        item_priority   : dummy({pos[55, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_category   : dummy({pos[100, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_needed     : dummy({pos[370, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_allocated  : dummy({pos[470, 5], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW})
        items_area      : dummy({pos[0, 67]})

        employed        : text({pos[32, 325]
                                text:"${city.workers_employed} ${50.12} ${city.workers_unemployed} ${50.13} ${city.unemployment_percentage}"
                                font : FONT_NORMAL_BLACK_ON_LIGHT })
        // wages panel
        wages_panel     : inner_panel({pos[64, 350], size[32, 2]})
        dec_wages       : arrowdown({pos[158, 354], tiny:false, onclick: advisor_labors_window_dec_wages })
        inc_wages       : arrowup({pos[182, 354], tiny:false, onclick: advisor_labors_window_inc_wages })
        wages_title     : text({text{group:50, id:14}, pos[70, 359], font:FONT_NORMAL_WHITE_ON_DARK})
        wages_value     : text({pos[230, 359], text:"${finance.wages}  ${50.15}  ${50.18} ${finance.wages_kingdome})", font:FONT_NORMAL_WHITE_ON_DARK})
        wages_estimated : text({pos[264, 395], text:"${50.19} ${finance.estimated_wages}", font:FONT_NORMAL_BLACK_ON_LIGHT})
    }
}

function advisor_labors_window_dec_wages() {
    emit event_finance_change_wages{ value:-1 }
}

function advisor_labors_window_inc_wages() {
    emit event_finance_change_wages{ value:1 }
}

function labor_category_name(cat) {
    if (cat === LABOR_CATEGORY_CULTURE)
        return "Culture"

    return __loc(50, cat + 1)
}

[es=(advisor_labors_window, ui_draw_foreground)]
function advisor_labors_window_draw(window) {
    var item_pos = {x:40, y:25}
    var items_area = {x:0, y:67}
    var item_image = {x:40, y:4}
    var item_priority = {x:55, y:5}
    var item_category = {x:100, y:5}
    var item_needed = {x:370, y:5}
    var item_allocated = {x:470, y:5}
    var item_size = {x:px(35), y:22}

    var priority_icon = get_image({ pack: PACK_GENERAL, id: 94 })

    for (var i = 0; i < LABOR_CATEGORY_SIZE - 1; i++) {
        var pos = {x: item_pos.x + items_area.x, y: item_pos.y * i + items_area.y}

        var clicked = ui.button({ text: "", pos: pos, size: item_size, border: true, body: false })
        if (clicked) {
            __window_labor_priority_show(i)
        }

        var cat = city.labor.get_category(i)
        if (cat.priority) {
            ui.image(priority_icon, [pos.x + item_image.x, pos.y + item_image.y])
            ui.label(String(cat.priority), [pos.x + item_priority.x, pos.y + item_priority.y], FONT_NORMAL_WHITE_ON_DARK)
        }

        ui.label(labor_category_name(i), [pos.x + item_category.x, pos.y + item_category.y], FONT_NORMAL_WHITE_ON_DARK)
        ui.label(String(cat.workers_needed), [pos.x + item_needed.x, pos.y + item_needed.y], FONT_NORMAL_WHITE_ON_DARK)

        var allocated_font = (cat.workers_needed !== cat.workers_allocated) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
        ui.label(String(cat.workers_allocated), [pos.x + item_allocated.x, pos.y + item_allocated.y], allocated_font)
    }
}