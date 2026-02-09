#pragma once

#include "graphics/elements/lang_text.h"
#include "window/autoconfig_window.h"

enum e_popup_dialog_opt {
    e_popup_dialog_none = -1,
    e_popup_dialog_dispatch_goods = 6,
    e_popup_dialog_missing_cd = 18,
    e_popup_dialog_old_version = 24,
    //
    e_popup_dialog_editor_burial_provisions_too_many = 26,
    e_popup_dialog_editor_burial_provisions_not_available = 28,
    e_popup_dialog_burial_provisions_not_enough_goods = 30,
    e_popup_dialog_burial_provisions_all_done = 32,
    //
    e_popup_dialog_editor_cities_too_many = 34,
    e_popup_dialog_transport_ship_needed = 36,
    e_popup_dialog_land_troops_needed = 38,
    e_popup_dialog_no_troops_needed = 40,
    e_popup_dialog_troops_away = 42,
    e_popup_dialog_warship_away = 44,
    //
    e_popup_dialog_good_price_cannot_change = 46,
    e_popup_dialog_error_needs_linen = 48,
    e_popup_dialog_error_needs_beer = 50,
    e_popup_dialog_error_needs_papyrus = 52,
    e_popup_dialog_mortuaries_needs_linen = 54,
    e_popup_dialog_senets_needs_beer = 56,
    e_popup_dialog_schools_needs_papyrus = 58,
    e_popup_dialog_libraries_needs_papyrus = 60,
    e_popup_dialog_error_needs_copper = 62,
    e_popup_dialog_weaponsmiths_needs_copper = 64,
    e_popup_dialog_error_needs_wood = 66,
    e_popup_dialog_chariotmakers_needs_wood = 68,
    e_popup_dialog_error_needs_recruiter = 70,
    e_popup_dialog_infantry_needs_recruiter = 72,
    e_popup_dialog_archers_needs_recruiter = 74,
    e_popup_dialog_charioteers_needs_recruiter = 76,
    e_popup_dialog_academies_needs_recruiter = 78,
    e_popup_dialog_error_needs_weapons = 80,
    e_popup_dialog_error_needs_chariots = 82,
    e_popup_dialog_infantry_needs_weapons = 84,
    e_popup_dialog_charioteers_needs_chariots = 86,
    //
    e_popup_dialog_dynasty_name_exists = 92,
    //
    e_popup_dialog_festival_not_enough_money = 96,
    e_popup_dialog_no_warships_available = 98,
    e_popup_dialog_no_warships_selected = 100,
    e_popup_dialog_multiple_troop_destinations = 102,
    //
    e_popup_dialog_delete_monument = 104,
    e_popup_dialog_delete_temple_complex = 106,
    //
    e_popup_dialog_editor_cant_save_prey_points_invalid = 108,
    e_popup_dialog_overwrite_file = 110,
    //
    e_popup_dialog_no_sellers = 112,
    e_popup_dialog_no_buyers = 114,
    e_popup_dialog_no_open_trade_routes = 116,
    e_popup_dialog_cant_open_trade_route_not_enough_money = 119,
    //
    e_popup_dialog_editor_cant_save_too_many_food_types = 121,
    e_popup_dialog_editor_cant_edit_map_low_resolution = 123,
    e_popup_dialog_editor_cant_close_map_too_many_food_types = 125,
    e_popup_dialog_editor_cant_save_fish_points_invalid = 127,
    e_popup_dialog_editor_cant_save_land_entry_points_invalid = 129,
    e_popup_dialog_editor_cant_save_river_entry_points_invalid = 131,
    e_popup_dialog_editor_cant_save_land_invasion_points_invalid = 133,
    e_popup_dialog_editor_cant_save_river_invasion_points_invalid = 135,
    //
    e_popup_dialog_please_insert_cd = 137,
    e_popup_dialog_zoo_needs_straw = 139,
    e_popup_dialog_no_missions_won_by_family = 141,
};

enum e_popup_dialog_btns { e_popup_btns_ok = 0, e_popup_btns_yes = 1, e_popup_btns_yesno = 2 };

using window_popup_dialog_callback = std::function<void(bool)>;
using window_yes_dialog_callback = std::function<void()>;

struct popup_dialog : public ui::widget {
    xstring text;
    xstring body;
    int ok_clicked;
    window_popup_dialog_callback close_func;
    e_popup_dialog_btns num_buttons;

    void draw_background(int flags);
    void draw_foreground(int flags);
    void handle_input(const mouse *m, const hotkeys *h);
    bool init(const xstring scheme, xstring loc, xstring custom_text, window_popup_dialog_callback close_func, e_popup_dialog_btns buttons);

    static void show(pcstr loc_id, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func);
    static void show(textid text, textid custom, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func);
    static void show(textid text, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func);
    static void show(xstring text, xstring custom, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func);

    template<typename Text>
    static void show_yesno(Text text, window_popup_dialog_callback close_func) {
        show(text, e_popup_btns_yesno, close_func);
    }
    
    template<typename Text>
    static void show_yesno(Text loc_id, window_yes_dialog_callback close_func) {
        show(loc_id, e_popup_btns_yesno, [=] (bool accepted) {
            if (accepted) { close_func(); }
        });
    }

    template<typename Text>
    static void show_ok(Text loc_id, window_yes_dialog_callback close_func = [] {}) {
        show(loc_id, e_popup_btns_ok, [=] (bool accepted) {
            if (accepted) { close_func(); }
        });
    }

    static void show_ok(xstring title, xstring custom, window_yes_dialog_callback close_func = [] {}) {
        show(title, custom, e_popup_btns_ok, [=] (bool accepted) {
            if (accepted) { close_func(); }
        });
    }

    // Adjust popup position when the screen resolution/size changes.
    static void on_resolution_changed();
};
