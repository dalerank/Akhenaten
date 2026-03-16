#include "window_mods.h"

#include "content/mods.h"
#include "content/vfs.h"
#include "core/log.h"
#include "core/xstring.h"
#include "game/game.h"
#include "js/js_game.h"
#include "window/autoconfig_window.h"
#include "window/popup_dialog.h"

#include <vector>
#include <map>
#include <algorithm>

ui::mods_window g_mods_window;

void ui::mods_window::init() {
    autoconfig_window::init();

    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->refill();
    }
}

void ui::mods_window::update_mods() {
    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->clear();
        mods->refill();
    }
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    if (update_info) {
        if (time_last_update_check + 30 < game.frame) {
            bstring32 text = ui["refresh_mods"].text().c_str();
            int num_points = std::count(text.data(), text.data() + text.len(), '.');
            num_points = (num_points + 1) % 4;
            text.replace('.', '\0');
            for (int i = 0; i < num_points; ++i) {
                text.append('.');
            }
            ui["refresh_mods"] = text;
            time_last_update_check = game.frame;
        }
    }

    return 0;
}

void window_mods_show(void) {
    autoconfig_window::show_by_section("mods_window");
}

void __window_mods_unpack_scripts() {
    xstring vpath = vfs::platform_unpack_scripts();
    popup_dialog::show_ok("#scripts_unpacked_to", vpath);
}

void __window_mods_refresh_available_list() {
    game.mt.detach_task([] () {
        g_mods_window.update_info = true;
        mods_refresh_available_list();
        g_mods_window.update_mods();
        g_mods_window.update_info = false;
    });
}

ANK_FUNCTION(window_mods_show)
ANK_FUNCTION(__window_mods_unpack_scripts)
ANK_FUNCTION(__window_mods_refresh_available_list)