log_info("akhenaten: ui advisor labor started")

advisor_labors_window = {
    ui : {
        background      : outer_panel({size:[40, 27]})

        title           : text({pos:[60, 12], text:{group:50, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT })
        advisor_icon    : image({pack:PACK_GENERAL, id:128, offset:0, pos:[10, 10] })

        // table headers
        h1              : text({pos:[60, 46], text:{group:50, id:21}, font : FONT_SMALL_PLAIN })
        h2              : text({pos:[170, 46], text:{group:50, id:22}, font : FONT_SMALL_PLAIN })
        h3              : text({pos:[400, 46], text:{group:50, id:23}, font : FONT_SMALL_PLAIN })
        h4              : text({pos:[500, 46], text:{group:50, id:24}, font : FONT_SMALL_PLAIN })

        // employed
        main_panel      : inner_panel({pos:[32, 60], size:[36, 16]})
        item            : dummy({pos:[40, 25], size:[px(35), 22], })
        item_image      : image({pack:PACK_GENERAL, id:94, pos:[40, 4], enabled:false})
        item_priority   : dummy({pos:[55, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_category   : dummy({pos:[100, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_needed     : dummy({pos:[370, 5], font: FONT_NORMAL_WHITE_ON_DARK})
        item_allocated  : dummy({pos:[470, 5], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW})
        items_area      : dummy({pos:[0, 67]})

        employed        : text({pos:[32, 325], font : FONT_NORMAL_BLACK_ON_LIGHT })
        // wages panel
        wages_panel     : inner_panel({pos:[64, 350], size:[32, 2]})
        dec_wages       : arrowdown({pos:[158, 354], tiny:false})
        inc_wages       : arrowup({pos:[182, 354], tiny:false})
        wages_title     : text({text:{group:50, id:14}, pos:[70, 359], font:FONT_NORMAL_WHITE_ON_DARK})
        wages_value     : text({pos:[230, 359], text: "${finance.wages}  ${50.15}  ${50.18} ${finance.wages_kingdome})", font:FONT_NORMAL_WHITE_ON_DARK})
        wages_estimated : text({pos:[264, 395], text:"${50.19} ${finance.estimated_wages}", font:FONT_NORMAL_BLACK_ON_LIGHT})
    }
}