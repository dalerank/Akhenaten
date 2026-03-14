log_info("akhenaten: records window started")

[es=window]
records_window {
    pos [(sw(0) - px(40))/2, (sh(0) - px(30))/2]
    ui {
        background_image : background({pack:PACK_UNLOADED, id:9})
        background       : outer_panel({size[40, 30]})
        title            : header({text[296, 0]
                                   font:FONT_LARGE_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                                   margin{top:20}})

        record_0  : text({pos[16, 70],  size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_1  : text({pos[16, 86],  size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_2  : text({pos[16, 102], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_3  : text({pos[16, 118], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_4  : text({pos[16, 134], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_5  : text({pos[16, 150], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_6  : text({pos[16, 166], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_7  : text({pos[16, 182], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_8  : text({pos[16, 198], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})
        record_9  : text({pos[16, 214], size[px(33), 16], font:FONT_NORMAL_BLACK_ON_LIGHT})

        bottom_text : text({text[31, 1]
                            font:FONT_NORMAL_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                            margin{bottom:-35}})
    }
}

[es=(records_window, init)]
function records_window_on_init(window) {
    __highscores_load()
    var count = __highscores_count()
    for (var i = 0; i < 10; i++) {
        if (i < count && __highscore_nonempty(i)) {
            var score     = __highscore_score(i)
            var mission   = __highscore_mission(i)
            var culture   = __highscore_culture(i)
            var prosper   = __highscore_prosperity(i)
            var kingdom   = __highscore_kingdom(i)
            var months    = __highscore_months(i)
            var funds     = __highscore_funds(i)
            var pop       = __highscore_population(i)
            window["record_" + i].text = (i + 1) + ". M:" + mission +
                "  S:" + score +
                "  C:" + culture + " P:" + prosper + " K:" + kingdom +
                "  m:" + months + " F:" + funds + " Pop:" + pop
        } else {
            window["record_" + i].text = "haven't played yet"
        }
    }
}
