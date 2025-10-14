log_info("akhenaten: ui advisor imperial started")

advisor_imperial_window {
    ui {
        background   : outer_panel({size[40, 27]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:2, pos[10, 10] })
        header_label : header({pos[60, 17]})
        rating_label : label({pos[460, 24]})
        rating_advice : multiline({pos[60, 46], wrap: 500})
        inner_panel  : inner_panel({pos[32, 90], size[36, 14] })
        button_request : dummy({pos[38, 96], size[562, 45],
            ui {
                button_request_icon   : dummy({pos[7, 7]})
                button_request_amount : dummy({pos[30, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_months : dummy({pos[310, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_saved  : dummy({pos[30, 25], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_allow  : dummy({pos[310, 25], font: FONT_NORMAL_WHITE_ON_DARK})
            }
        })

        bottom_panel : inner_panel({pos[64, 324], size[32, 6] })
        send_gift    : button({pos[320, 362], size[250, 24], text{group:52, id:49}, tooltip[68, 133], font:FONT_NORMAL_WHITE_ON_DARK })
        personal_savings : label({pos[72, 368], text:"${52.1} ${city.personal_savings} ${6.0}" })
        player_rank  : label({pos[72, 342]})
        donate_to_city : button({pos[320, 335], size[250, 24], text{group:52, id:2}, tooltip:[68, 96], font:FONT_NORMAL_WHITE_ON_DARK })
        salary_rank  : button({pos[70, 393], size[500, 24], tooltip[68, 97], font:FONT_NORMAL_WHITE_ON_DARK })
        big_text     : text_center({pos[60, 295], size[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        top_text     : text_center({pos[504, 130], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        bot_text     : text_center({pos[504, 230], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
    }
}