log_info("akhenaten: ui donate to city window started")

function donate_to_city_do_donate() {
    city.kingdome.donate_savings_to_city()
    window_advisors_show()
}

function donate_to_city_cancel() {
    window_advisors_show()
}

[es=(donate_to_city_window, init)]
function donate_to_city_window_init(window) {
    city.kingdome.set_donation_amount(city.kingdome.donate_amount)
}

[es=modal_window]
donate_to_city_window {
    allow_rmb_goback : true
    draw_underlying : true
    pos [(sw(0) - px(32)) / 2, (sh(0) - px(10)) / 2]

    ui {
        background_image : background({pack:PACK_UNLOADED, id:11})
        background       : outer_panel({size[32, 10]})
        resource_icon    : resource_icon({pos[16, 16], resource:RESOURCE_DEBEN})
        title            : text_center({pos[48, 16], size[px(32) - 64, 20], text[52, 16], font: FONT_LARGE_BLACK_ON_LIGHT})

        amounts_panel    : inner_panel({pos[48, 48], size[26, 4]
            ui {
                btn_0     : button({pos[16, 8], size[64, 20], text:"0", font: FONT_NORMAL_WHITE_ON_DARK
                                    onclick: function() { city.kingdome.set_donation_amount(0) }})
                btn_500   : button({pos[96, 8], size[64, 20], text:"500", font: FONT_NORMAL_WHITE_ON_DARK
                                    onclick: function() { city.kingdome.set_donation_amount(500) }})
                btn_2000  : button({pos[176, 8], size[64, 20], text:"2000", font: FONT_NORMAL_WHITE_ON_DARK
                                    onclick: function() { city.kingdome.set_donation_amount(2000) }})
                btn_5000  : button({pos[256, 8], size[64, 20], text:"5000", font: FONT_NORMAL_WHITE_ON_DARK
                                    onclick: function() { city.kingdome.set_donation_amount(5000) }})
                btn_all   : button({pos[336, 8], size[64, 20], text[52, 19], font: FONT_NORMAL_WHITE_ON_DARK
                                    onclick: function() { city.kingdome.set_donation_amount(1000000) }})
            }
        })

        hint_label       : text({pos[64, 88], text[52, 17], font: FONT_NORMAL_WHITE_ON_DARK})
        arrow_down       : arrowdown({pos[176, 82], tiny: false, allow_repeat: true
                                      onclick: function() { city.kingdome.change_donation_amount(-10) }})
        arrow_up         : arrowup({pos[200, 82], tiny: false, allow_repeat: true
                                    onclick: function() { city.kingdome.change_donation_amount(10) }})
        amount_value     : label({pos[256, 88], font: FONT_NORMAL_WHITE_ON_DARK
                                  textfn: function() { return String(city.kingdome.donate_amount) }})

        btn_donate       : button({pos[80, 123], size[160, 20], text[52, 18], font: FONT_NORMAL_BLACK_ON_LIGHT
                                    onclick: donate_to_city_do_donate})
        btn_cancel       : button({pos[272, 123], size[160, 20], text[13, 4], font: FONT_NORMAL_BLACK_ON_LIGHT
                                    onclick: donate_to_city_cancel})
    }
}
