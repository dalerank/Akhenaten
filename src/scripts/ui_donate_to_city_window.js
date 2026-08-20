log_info("akhenaten: ui donate to city window started")

[es=(donate_to_city_window, init)]
function donate_to_city_window_init(window) {
    city.kingdome.set_donation_amount(city.kingdome.donate_amount)
}

[es=modal_window]
donate_to_city_window {
    pos [(sw(0) - px(32)) / 2, (sh(0) - px(10)) / 2]
    allow_rmb_goback : true
    draw_underlying : true

    ui {
        background_image : background({pack:PACK_UNLOADED, id:11})
        background       : outer_panel({size[32, 10]})
        resource_icon    : resource_icon({pos[16, 16], resource:RESOURCE_DEBEN})
        title            : text_center({pos[48, 16], size[px(32) - 64, 20], text[52, 16], font: FONT_LARGE_BLACK_ON_LIGHT})

        amounts_panel    : inner_panel({pos[48, 48], size[26, 4]
            ui {
                btn_0     : button({pos[16, 8], size[64, 20], text:"0", font: FONT_NORMAL_WHITE_ON_DARK })
                btn_500   : button({pos[96, 8], size[64, 20], text:"500", font: FONT_NORMAL_WHITE_ON_DARK })
                btn_2000  : button({pos[176, 8], size[64, 20], text:"2000", font: FONT_NORMAL_WHITE_ON_DARK })
                btn_5000  : button({pos[256, 8], size[64, 20], text:"5000", font: FONT_NORMAL_WHITE_ON_DARK })
                btn_all   : button({pos[336, 8], size[64, 20], text[52, 19], font: FONT_NORMAL_WHITE_ON_DARK })
            }
        })

        hint_label       : text({pos[64, 88], text[52, 17], font: FONT_NORMAL_WHITE_ON_DARK})
        arrow_down       : arrowdown({pos[176, 82], tiny: false, allow_repeat: true })
        arrow_up         : arrowup({pos[200, 82], tiny: false, allow_repeat: true })
        amount_value     : label({pos[256, 88], font: FONT_NORMAL_WHITE_ON_DARK
                                  textfn: function() { return String(city.kingdome.donate_amount) }})

        btn_donate       : button({pos[80, 123], size[160, 20], text[52, 18], font: FONT_NORMAL_BLACK_ON_LIGHT })
        btn_cancel       : button({pos[272, 123], size[160, 20], text[13, 4], font: FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

[es=(donate_to_city_window, btn_donate)]
function donate_to_city_btn_donate(window) {
    city.kingdome.donate_savings_to_city()
    window_advisors_show()
}

[es=(donate_to_city_window, btn_cancel)]
function donate_to_city_btn_cancel(window) {
    window_advisors_show()
}

[es=(donate_to_city_window, btn_0)]
function donate_to_city_btn_0(window) {
    city.kingdome.set_donation_amount(0)
}

[es=(donate_to_city_window, btn_500)]
function donate_to_city_btn_500(window) {
    city.kingdome.set_donation_amount(500)
}

[es=(donate_to_city_window, btn_2000)]
function donate_to_city_btn_2000(window) {
    city.kingdome.set_donation_amount(2000)
}

[es=(donate_to_city_window, btn_5000)]
function donate_to_city_btn_5000(window) {
    city.kingdome.set_donation_amount(5000)
}

[es=(donate_to_city_window, btn_all)]
function donate_to_city_btn_all(window) {
    city.kingdome.set_donation_amount(1000000)
}

[es=(donate_to_city_window, arrow_down)]
function donate_to_city_arrow_down(window) {
    city.kingdome.change_donation_amount(-10)
}

[es=(donate_to_city_window, arrow_up)]
function donate_to_city_arrow_up(window) {
    city.kingdome.change_donation_amount(10)
}
