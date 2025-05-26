log_info("akhenaten: ui advisor trade started")

advisor_trade_window = {
    ui : {
        background   : outer_panel({size:[40, 27] }),
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:4, pos:[10, 10] }),
        header_label : label({font : FONT_LARGE_BLACK_ON_LIGHT, text:"#trade_overseer", pos:[60, 17]}),
        hint_label   : label({font : FONT_NORMAL_BLACK_ON_DARK, text:"#trade_overseer_hint", pos:[60, 40]}),

        inner_panel  : inner_panel({pos:[17, 60], size:[36, 21] }),
        items            : dummy({pos:[17, 30], 
            ui : {
                item_button : dummy({pos:[20, 0], size:[550, 22], tooltip:[68, 109]}),
                item_icon : dummy({pos:[24, 3]}),
                item_name : dummy({pos:[46, 5]}),
                item_quality : dummy({pos:[152, 5]}),
                item_state : dummy({pos:[230, 3]}),
                item_status : dummy({pos:[300, 3]}),
            }
        }),

        scrollbar    : { type: "scrollbar", pos:[594, 60], size:[-1, 336] },
        goto_empire  : button({pos:[48, 396], size:[200, 24], text:"#trade_overseer_prices", tooltip:"#trade_overseer_prices_hint" }),
        show_prices  : button({pos:[368, 396], size:[200, 24], text:"#trade_overseer_goto_empire", tooltip:"#trade_overseer_goto_empire_hint" }),
    }
}