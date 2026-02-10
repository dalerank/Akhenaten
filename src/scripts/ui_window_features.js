log_info("akhenaten: window features started")

function wposbtn(i) { return { x: 32, y: 72 + i * 25} }
function wpostxt(i) { return { x: 64, y: 78 + i * 25} }

window_features = {
    pos: [(sw(0) - px(40))/2, (sh(0) - px(30))/2]
    default_font : FONT_NORMAL_BLACK_ON_LIGHT

    ui : {
        background_image: background({pack:PACK_UNLOADED, id:8})
        background    : outer_panel({size: [40, 30] })

        title         : text({pos:[0, 16], size:[px(40), 20], align:"center", font:FONT_LARGE_BLACK_ON_LIGHT})

        btn_prev      : button({margin:{left:20, top:16}, size:[50, 25], text:"Prev"})
        btn_next      : button({margin:{right:-70, top:16}, size:[50, 25], text:"Next"})

        bfeature0     : button({pos:wposbtn(0), size:[23, 23]})
        tfeature0     : text({pos:wpostxt(0) })

        bfeature1     : button({pos:wposbtn(1), size:[23, 23]})
        tfeature1     : text({pos:wpostxt(1) })

        bfeature2     : button({pos:wposbtn(2), size:[23, 23]})
        tfeature2     : text({pos:wpostxt(2) })

        bfeature3     : button({pos:wposbtn(3), size:[23, 23]})
        tfeature3     : text({pos:wpostxt(3) })

        bfeature4     : button({pos:wposbtn(4), size:[23, 23]})
        tfeature4     : text({pos:wpostxt(4) })

        bfeature5     : button({pos:wposbtn(5), size:[23, 23]})
        tfeature5     : text({pos:wpostxt(5) })

        bfeature6     : button({pos:wposbtn(6), size:[23, 23]})
        tfeature6     : text({pos:wpostxt(6) })

        bfeature7     : button({pos:wposbtn(7), size:[23, 23]})
        tfeature7     : text({pos:wpostxt(7) })

        bfeature8     : button({pos:wposbtn(8), size:[23, 23]})
        tfeature8     : text({pos:wpostxt(8) })

        bfeature9     : button({pos:wposbtn(9), size:[23, 23]})
        tfeature9     : text({pos:wpostxt(9) })

        bfeature10     : button({pos:wposbtn(10), size:[23, 23]})
        tfeature10     : text({pos:wpostxt(10) })

        bfeature11     : button({pos:wposbtn(11), size:[23, 23]})
        tfeature11     : text({pos:wpostxt(11) })

        bfeature12     : button({pos:wposbtn(12), size:[23, 23]})
        tfeature12     : text({pos:wpostxt(12) })

        bfeature13     : button({pos:wposbtn(13), size:[23, 23]})
        tfeature13     : text({pos:wpostxt(13) })

        btn_defaults   : button({pos:[250, 436], size:[150, 30], text:"#TR_BUTTON_RESET_DEFAULTS"}),
        btn_hotkeys    : button({pos:[90, 436], size:[150, 30], text:"#TR_BUTTON_CONFIGURE_HOTKEYS"}),

        btn_close      : button({pos:[410, 436], size:[100, 30], text:"#TR_BUTTON_CANCEL"}),
        btn_save       : button({pos:[520, 436], size:[100, 30], text:"#TR_BUTTON_OK"})
    }
}