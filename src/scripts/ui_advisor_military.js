log_info("akhenaten: ui advisor military started")

advisor_military_window {
    ui {
        background   : outer_panel({size[40, 27]})

        title        : text({pos[60, 12], text{group:51, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT })
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:1, pos[10, 10] })

        h1_1         : text({text{group:51, id:1}, pos[384, 43], font:FONT_SMALL_PLAIN})
        h1_2         : text({text{group:51, id:2}, pos[384, 58], font:FONT_SMALL_PLAIN})
        h2_1         : text({text{group:51, id:3}, pos[454, 43], font:FONT_SMALL_PLAIN})
        h2_2         : text({text{group:51, id:4}, pos[454, 58], font:FONT_SMALL_PLAIN})
        h3_1         : text({text{group:51, id:5}, pos[534, 43], font:FONT_SMALL_PLAIN})
        h3_2         : text({text{group:51, id:6}, pos[534, 58], font:FONT_SMALL_PLAIN})
        h4_morale    : text({text{group:138, id:36}, pos[234, 58], font:FONT_SMALL_PLAIN})
        h5_1         : text({text{group:51, id:17}, pos[304, 43], font:FONT_SMALL_PLAIN})
        h5_2         : text({text{group:51, id:18}, pos[304, 58], font:FONT_SMALL_PLAIN})
        
        inner_panel  : inner_panel({pos[32, 70], size[36, 17]})
        forts_area   : dummy({ margin{left:30, bottom:-90}
                               ui {
                                   imgb1       : image({path:"pharaoh_general/paneling_00047", pos[0, 10]})
                                   enemy_text  : text({pos[30, 10], font:FONT_NORMAL_BLACK_ON_LIGHT})

                                   imgb2       : image({path:"pharaoh_general/paneling_00047", pos[0, 30]})
                                   distant_text: text({pos[30, 30], font:FONT_NORMAL_BLACK_ON_LIGHT})

                                   imgb3       : image({path:"pharaoh_general/paneling_00047", pos[0, 50]})
                                   forts_text  : text({pos[30, 50], font:FONT_NORMAL_BLACK_ON_LIGHT})
                               }
                             })
    }
}

function get_figure_type_str(figure_type) {
    if (figure_type == FIGURE_INFANTRY)  return __loc(138, 34)
    if (figure_type == FIGURE_FCHARIOTEER) return __loc(138, 33)
    if (figure_type == FIGURE_ARCHER) return __loc(138, 35)
    return ""
}

[event=advisor_military_window_init]
function advisor_military_window_init(window) {    
    var enemy_text_id = 8
    if (city.figures.enemies) { enemy_text_id = 10 }
    else if (city.figures.kingdome_soldiers) { enemy_text_id = 11 }
    // else if (scenario_invasion_exists_upcoming()) { enemy_text_id = 9; }

    var distant_battle_text_id = 12
    if (empire.active_battle.egyptian_months_to_travel_back > 0) { distant_battle_text_id = 15 }
    else if (empire.active_battle.egyptian_months_to_travel_forth > 0) { distant_battle_text_id = 14 }
    else if (empire.active_battle.months_until_battle > 0) { distant_battle_text_id = 13 }

    window.enemy_text.text = __loc(51, enemy_text_id)
    window.distant_text.text = __loc(51, distant_battle_text_id)
    
    var total_soldiers_str = __loc(8, 46) + " " + city.military.total_soldiers
    var total_batalions_str = __loc(51, 8) + " " + city.military.total_batalions
    window.forts_text.text = total_soldiers_str + " " + __loc(8, 48) + " " + total_batalions_str
}

[event=advisor_military_window_draw]
function advisor_military_window_draw(window) {     
    if (city.num_forts > 0) {
        var exp_image = get_image("pharaoh_general/paneling_00537")
        var goto_legion_image = get_image("pharaoh_general/paneling_00531")
        var fort_image = get_image("pharaoh_general/paneling_00532")
        var kingdom_service = get_image("pharaoh_general/paneling_00534")
        for (var i = 0; i < city.num_forts; i++) {
            var form = city.get_battalion(i)
            
            ui.button({ text:"", pos[40, 77 + 44 * i], size[px(35), 40], font:FONT_NORMAL_BLACK_ON_DARK, border:false, body:false })

            var battalion_image = get_image(PACK_GENERAL, 127, form.batalion_id)
            ui.image(battalion_image, {x:44, y:82 + 44 * i})
            ui.label(__loc(138, form.batalion_id), vec2i(84, 83 + 44 * i), FONT_NORMAL_WHITE_ON_DARK)
 
            var num_figures_str = "" + form.num_figures + " " + get_figure_type_str(form.figure_type)
            ui.label(num_figures_str, vec2i(84, 100 + 44 * i), FONT_NORMAL_BLACK_ON_DARK);

            var morale_str = __loc(138, 37 + form.morale / 5)
            ui.label(morale_str, vec2i(224, 91 + 44 * i), FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered);
            
            var experience_level = form.experience / 100
            exp_image.tid += experience_level
            ui.button({ text:"", pos{x:314, y:83 + 44 * i}, size[30, 30], font:FONT_NORMAL_BLACK_ON_DARK})
            ui.image(exp_image, { x:317, y:86 + 44 * i})
 
            var goto_clicked = ui.button({text:"", pos{ x:394, y:83 + 44 * i }, size[ 30, 30 ] })
            if (goto_clicked) {
                city.camera_go_to(form.home)
                ui.window_city_show()
            }
            ui.image(goto_legion_image, { x:397, y:86 + 44 * i });

            fort_image.tid += (form.is_at_fort ? 1 : 0)
            var back_to_fort_clicked = ui.button({text:"", pos:{ x:464, y:83 + 44 * i }, size[ 30, 30 ], font:FONT_NORMAL_BLACK_ON_DARK});
            if (back_to_fort_clicked) {
                form.return_home()
            }
            ui.image(fort_image, { x:467, y:86 + 44 * i });

            kingdom_service.tid += (form.empire_service ? 1 : 0)
            ui.button({text:"", pos:{ x:544, y:83 + 44 * i }, size[ 30, 30 ], font:FONT_NORMAL_BLACK_ON_DARK});
            ui.image(kingdom_service, vec2i(547, 86 + 44 * i ));
        }
    } else {
        ui.label(__loc(51, 16), vec2i(64, 200), FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered)
    }
}