log_info("akhenaten: ui advisor imperial started")

function rating_advice_text() {
    return __loc(52, (city.rating_kingdom / 5) + 22)
}

function player_rank_text() {
    return __loc(32, player.rank);
}

function salary_rank_text() {
    return __loc(52, player.salary_rank + 4) + " " + player.salary_amount + " " + __loc(52, 3);
}

advisor_imperial_window {
    ui {
        background   : outer_panel({size[40, 27]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:2, pos[10, 10] })
        header_label : header({pos[60, 17], text:"Political overseer for ${player.name}"})
        rating_label : label({pos[60, 42], text:"${52.0} ${rating.kingdom}", font:FONT_NORMAL_BLACK_ON_LIGHT})
        rating_advice : multiline({pos[60, 64], size[px(36), 20], wrap:px(35), font:FONT_NORMAL_BLACK_ON_LIGHT, textfn:rating_advice_text})
        inner_panel  : inner_panel({pos[32, 110], size[36, 13] })
        
        button_request : dummy({pos[38, 116], size[562, 45],
            ui {
                button_request_icon   : dummy({pos[7, 7]})
                button_request_amount : dummy({pos[30, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_months : dummy({pos[310, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_saved  : dummy({pos[30, 25], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_allow  : dummy({pos[310, 25], font: FONT_NORMAL_WHITE_ON_DARK})
            }
        })

        bottom_panel : inner_panel({pos[64, 324], size[32, 6] })
        player_rank  : header({pos[72, 332], textfn:player_rank_text})            

        donate_to_city : button({pos[320, 330], size[250, 20]
                                 text{group:52, id:2}, tooltip:"${68.96}", font:FONT_NORMAL_WHITE_ON_DARK 
                                 onclick: window_donate_to_city_show
                                })
                                
        send_gift    : button({pos[320, 352], size[250, 20]
                               text{group:52, id:49}, tooltip:"${68.133}", font:FONT_NORMAL_WHITE_ON_DARK, 
                               onclick: window_gift_to_kingdome_show })

        personal_savings : label({pos[72, 374], text:"${52.1} ${city.personal_savings} ${6.0}" })
        money_lost   : label({pos[272, 374], text:"0 debens lost this year throught theft" })
        no_requests  : label({margin{ centerx:-100, centery:-10}, text:"${52.21}", font:FONT_NORMAL_WHITE_ON_DARK })
        
        salary_rank  : button({pos[70, 392], size[500, 24], tooltip[68, 97], textfn:salary_rank_text, font:FONT_NORMAL_WHITE_ON_DARK })

        big_text     : text_center({pos[60, 295], size[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        top_text     : text_center({pos[504, 130], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        bot_text     : text_center({pos[504, 230], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
    }
}