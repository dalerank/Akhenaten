log_info("akhenaten: ui display options window started")

display_options_window {
    pos [(sw(0) - px(24))/2, (sh(0) - px(21))/2]

    ui {
        background  : outer_panel({size[24, 21] })
        title       : header({pos[10, 10], size[px(24), 20], text:"${42.0}", align:"center"})

        btnfullscreen : button({pos[16, 46], size[224, 20] })
        videodriver : text({pos[px(24)/2 + 60, 50]})

        resolutions : scrollable_list({pos[16, 70], size[20, 14],  view_items:13, draw_scrollbar_always:true})

        save_changes: text({margin{left:px(24)/2 - 80, bottom:-35}, text[43, 5]})
        btnok       : ok_button({margin{left:px(24)/2 + 10, bottom:-40}})
        btncancel   : cancel_button({margin{left:px(24)/2 + 60, bottom:-40}})
    }
}