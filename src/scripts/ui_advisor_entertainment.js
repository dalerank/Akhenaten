log_info("akhenaten: ui advisor entertainment started")

advisor_entertainment_window = {
    ui : {
        background    : outer_panel({size:[40, 20] }),
        title         : text({pos: [60, 12], text:[58, 0], font : FONT_LARGE_BLACK_ON_LIGHT }),
        advisor_icon  : image({pack:PACK_GENERAL, id:128, offset:8, pos:[10, 10] }),

        // headers
        working       : text({text:[58, 1], pos:[180, 42], font:FONT_NORMAL_BLACK_ON_LIGHT}),
        stages        : text({text:[58, 55], pos:[180, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
        shows         : text({text:[58, 2], pos:[280, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
        can_entertain : text({text:[58, 3], pos:[340, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
        city_coverage : text({text:[58, 4], pos:[470, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),

        advice        : multiline({ margin:{left:30, bottom:-110}, size:[px(38), 208], wrap:512, font:FONT_NORMAL_BLACK_ON_LIGHT }),

        inner_panel   : inner_panel({pos:[32, 70], size:[36, 8],
            ui : {
                booth_total      : text({pos:[10,  5]}),
                booth_active     : text_center({pos:[150, 5], size:[50, 20]}),
                booth_shows      : text_center({pos:[250, 5], size:[50, 20]}),
                booth_care       : text_center({pos:[310, 5], size:[50, 20]}),
                booth_cvg        : text_center({pos:[440, 5], size:[100, 20]}),

                bandstand_total  : text({pos:[10,  30]}),
                bandstand_active : text_center({pos:[150, 30], size:[50, 20]}),
                bandstand_shows  : text_center({pos:[250, 30], size:[50, 20]}),
                bandstand_care   : text_center({pos:[310, 30], size:[50, 20]}),
                bandstand_cvg    : text_center({pos:[440, 30], size:[100, 20]}),

                pavilion_total   : text({pos:[10,  55]}),
                pavilion_active  : text_center({pos:[150, 55], size:[50, 20]}),
                pavilion_shows   : text_center({pos:[250, 55], size:[50, 20]}),
                pavilion_care    : text_center({pos:[310, 55], size:[50, 20]}),
                pavilion_cvg     : text_center({pos:[440, 55], size:[100, 20]}),

                senet_house_total: text({pos:[10,  80]}),
                senet_house_active:text_center({pos:[150, 80], size:[50, 20]}),
                senet_house_shows: text_center({pos:[250, 80], size:[50, 20]}),
                senet_house_care : text_center({pos:[310, 80], size:[50, 20]}),
                senet_house_cvg  : text_center({pos:[440, 80], size:[100, 20]}),

                zoo_total        : text({pos:[10,  105]}),
                zoo_active       : text_center({pos:[150, 105], size:[50, 20]}),
                zoo_shows        : text_center({pos:[250, 105], size:[50, 20]}),
                zoo_care         : text_center({pos:[310, 105], size:[50, 20]}),
                zoo_cvg          : text_center({pos:[440, 105], size:[100, 20]}),
            }
        }),
    }
}