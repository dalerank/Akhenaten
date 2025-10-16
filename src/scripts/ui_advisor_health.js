log_info("akhenaten: ui advisor health started")

advisor_health_window {
    ui {
        background   : outer_panel({size[40, 18]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:6, pos:[10, 10] })
        title        : header({pos[60, 17], text:{group:56, id:0}})
        city_health  : multiline({pos[60, 46], wrap:512, font: FONT_NORMAL_BLACK_ON_LIGHT})

        working      : label({text[56, 3], pos[180, 94], font:FONT_SMALL_PLAIN})
        care_for     : label({text[56, 4], pos[290, 94], font:FONT_SMALL_PLAIN})
        city_coverage: text_center({text[56, 5], pos[440, 94], size[160, 20], font:FONT_SMALL_PLAIN})

        inner_panel  : inner_panel({pos[32, 108], size[36, 5]
            ui : {
                physicians_total : label({pos[15, 6], font:FONT_NORMAL_BLACK_ON_DARK})
                physicians_active: text_center({pos[160, 6], size[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
                physicians_care  : text_center({pos[290, 6], size[40, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
                physicians_covg  : text_center({pos[440, 6], size[60, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

                dentist_total    : label({pos[15, 24], font:FONT_NORMAL_BLACK_ON_DARK})
                dentist_active   : text_center({pos[160, 24], size[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
                dentist_care     : text_center({pos[290, 24], size[40, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
                dentist_covg     : text_center({pos[440, 24], size[60, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

                apothecary_total : label({pos[15, 42], font:FONT_NORMAL_BLACK_ON_DARK})
                apothecary_active: text_center({pos[160, 42], size[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
                apothecary_care  : text_center({pos[290, 42], size[40, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
                apothecary_covg  : text_center({pos[440, 42], size[60, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})

                mortuary_total   : label({pos:[15, 60], font:FONT_NORMAL_BLACK_ON_DARK})
                mortuary_active  : text_center({pos[160, 60], size[40, 20], font:FONT_NORMAL_BLACK_ON_DARK})
                mortuary_care    : text_center({pos[290, 60], size[40, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
                mortuary_covg    : text_center({pos[440, 60], size[60, 20], text[56, 2], font:FONT_NORMAL_BLACK_ON_DARK})
            }
        })

        health_advice : multiline({pos[60, 198], wrap:px(32), font: FONT_NORMAL_BLACK_ON_LIGHT })
    }
}