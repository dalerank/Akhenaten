log_info("akhenaten: ui send gift window started")

function gift_to_kingdome_last_gift_text() {
    return __loc("#ui_gift_time_since_last") + " " + city.kingdome.months_since_gift + " " + __loc(8, 4)
}

function gift_to_kingdome_send_button_text() {
    var dispatch_keys = ["#ui_gift_dispatch_modest", "#ui_gift_dispatch_generous", "#ui_gift_dispatch_lavish"]
    var s = city.kingdome.selected_size
    return __loc(dispatch_keys[s])
}

function gift_to_kingdome_link_caption(loc_base, size) {
    if (!city.kingdome.can_send_gift(size)) {
        return __loc("#ui_unable_to_fulfill_request")
    }
    var id = city.kingdome.gift_item_id(size)
    var cost = city.kingdome.gift_cost(size)
    return __loc(52, loc_base + id) + " (" + cost + " db)"
}

function gift_to_kingdome_apply_link_state(window) {
    window.link_modest.selected = (city.kingdome.selected_size === gift_type.MODEST)
    window.link_generous.selected = (city.kingdome.selected_size === gift_type.GENEROUS)
    window.link_lavish.selected = (city.kingdome.selected_size === gift_type.LAVISH)
}

[es=(gift_to_kingdome_window, init)]
function gift_to_kingdome_window_init(window) {
    city.kingdome.update_gifts()

    var can_send = city.kingdome.can_send_gift(gift_type.MODEST)
    var can_gen = city.kingdome.can_send_gift(gift_type.GENEROUS)
    var can_lav = city.kingdome.can_send_gift(gift_type.LAVISH)

    city.kingdome.selected_size = gift_type.MODEST
    if (can_gen) {
        city.kingdome.selected_size = gift_type.GENEROUS
    }

    if (can_lav) {
        city.kingdome.selected_size = gift_type.MODEST
    }

    window.link_modest.text = gift_to_kingdome_link_caption(51, gift_type.MODEST)
    window.link_modest.readonly = !can_send

    window.link_generous.text = gift_to_kingdome_link_caption(55, gift_type.GENEROUS)
    window.link_generous.readonly = !can_send || !can_gen

    window.link_lavish.text = gift_to_kingdome_link_caption(59, gift_type.LAVISH)
    window.link_lavish.readonly = !can_send || !can_lav

    window.cant_send_gifts.enabled = !city.kingdome.can_send_gift(0)
    log_info("akhenaten: cant_send_gifts.enabled = " + window.cant_send_gifts.enabled)
    window.send_gift.readonly = !can_send
    window.send_gift.darkened = !can_send
    window.send_gift.onclick = gift_to_kingdome_window_on_send_gift

    gift_to_kingdome_apply_link_state(window)
}

[es=(gift_to_kingdome_window, link_modest)]
function gift_to_kingdome_window_on_link_modest(ev) {
    city.kingdome.selected_size = gift_type.MODEST
    gift_to_kingdome_apply_link_state(window)
}

[es=(gift_to_kingdome_window, link_generous)]
function gift_to_kingdome_window_on_link_generous(ev) {
    city.kingdome.selected_size = gift_type.GENEROUS
    gift_to_kingdome_apply_link_state(window)
}

[es=(gift_to_kingdome_window, link_lavish)]
function gift_to_kingdome_window_on_link_lavish(ev) {
    city.kingdome.selected_size = gift_type.LAVISH
    gift_to_kingdome_apply_link_state(window)
}

function gift_to_kingdome_window_on_send_gift(ev) {
    if (!city.kingdome.can_send_gift(city.kingdome.selected_size))
        return

    emit event_send_gift_to_kingdome{ gift_size: city.kingdome.selected_size }
    window_advisors_show()
}

[es=modal_window]
gift_to_kingdome_window {
	pos [(sw(0) - px(30))/2, (sh(0) - px(15))/2]
    allow_rmb_goback : true
    draw_underlying : true
    selected_size : 0

    ui {
    	background_image: background({pack:PACK_UNLOADED, id:11}),
        background      : outer_panel({ size[30, 15] })
        title           : header({ pos[0, 15], size[px(30), 20], text:"#ui_gift_to_kingdome_window_title", align:"center" })
        deben_icon      : resource_icon({pos[15, 15], resource:RESOURCE_GOLD})

        last_gift 		: text_center({ pos[0, 45], size[px(30), 20], textfn: gift_to_kingdome_last_gift_text })
        cant_send_gifts	: text_center({ margin:{left:16, bottom: -85}, size[px(28), -1], text:"#ui_gift_cannot_afford_savings", multiline:true })

        panel           : inner_panel({pos[16, 70], size[28, 5]
        	ui {
		        lb_modest       : text({ text:"#ui_gift_label_modest", pos[16, 10], font:FONT_NORMAL_WHITE_ON_DARK })
		        link_modest 	: link({ pos[100, 5], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW, onclick_event: "link_modest"})

		    	lb_generous		: label({ text:"#ui_gift_label_generous", pos[16, 30], font: FONT_NORMAL_WHITE_ON_DARK})
		        link_generous 	: link({ pos[100, 25], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW, onclick_event: "link_generous"})

		    	lb_lavish		: label({ text:"#ui_gift_label_lavish", pos[16, 50], font: FONT_NORMAL_WHITE_ON_DARK})
		        link_lavish 	: link({ pos[100, 45], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW, onclick_event: "link_lavish"})
		    }
	    })

        send_gift 		: button({ margin{left:20, bottom:-40}, size[260, 20], textfn: gift_to_kingdome_send_button_text, onclick_event: "send_gift" })
        button_close    : button({ margin{right:-180, bottom:-40}, size[160, 20], text:"#TR_BUTTON_CANCEL", onclick: window_go_back})
    }
}
