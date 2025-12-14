#include "window_mods.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player_data.h"
#include "game/game.h"
#include "content/content.h"
#include "window/popup_dialog.h"
#include "js/js_game.h"
#include "content/dir.h"
#include "core/xstring.h"

#include <vector>
#include <map>

struct mod_info {
    xstring path;
    bool enabled;
};

static std::vector<mod_info> g_mods_list;
static std::map<xstring, bool> g_mods_status;

ui::mods_window g_mods_window;

void ui::mods_window::init() {
    autoconfig_window::init();

    g_mods_list.clear();
    const dir_listing *sgx_files = vfs::dir_find_files_with_extension("Mods", "sgx");

    for (int i = 0; i < sgx_files->num_files; ++i) {
        mod_info mod;
        mod.path.printf("Mods/%s", sgx_files->files[i]);

        auto it = g_mods_status.find(mod.path);
        mod.enabled = (it != g_mods_status.end()) ? it->second : true;

        g_mods_list.push_back(mod);
    }

    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->clear();
        mods->onrefill([] (std::vector<xstring> &r) {
            for (size_t i = 0; i < g_mods_list.size(); i++) {
                for (const auto &mod : g_mods_list) {
                    bstring128 entry;
                    entry.printf("[%s] %s", mod.enabled ? "ON" : "OFF", mod.path.c_str());
                    r.push_back(entry.c_str());
                }
            }
        });

        mods->onclick_item([] (int selected_idx, int) {
            if (selected_idx >= 0 && selected_idx < (int)g_mods_list.size()) {
                mods_toggle(selected_idx);
            }
        });
    }
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));

    return 0;
}

int ui::mods_window::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_go_back();
        return 0;
    }

    return 0;
}

void ui::mods_window::show() {
    static window_type instance = {
        WINDOW_PLAYER_SELECTION,
        [] (int flags) { g_mods_window.draw_background(flags); },
        [] (int flags) { g_mods_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_mods_window.ui_handle_mouse(m); }
    };

    g_mods_window.init();
    window_show(&instance);
}

void window_mods_show(void) {
    ui::mods_window::show();
}

void platform_unpack_scripts() {
    xstring vpath = vfs::platform_unpack_scripts();
    popup_dialog::show_ok("#scripts_unpacked_to", vpath);
}

vfs::path mods_get_path(int index) {
    if (index < 0 || index >= (int)g_mods_list.size()) {
        return "";
    }
    return g_mods_list[index].path.c_str();
}

bool mods_get_enabled(int index) {
    if (index < 0 || index >= (int)g_mods_list.size()) {
        return false;
    }
    return g_mods_list[index].enabled;
}

void mods_set_enabled(int index, bool enabled) {
    if (index < 0 || index >= (int)g_mods_list.size()) {
        return;
    }
    g_mods_list[index].enabled = enabled;
    g_mods_status[g_mods_list[index].path] = enabled;
    
    // Refresh the window if it's open
    if (g_mods_window._is_inited) {
        g_mods_window.init();
    }
}

void mods_toggle(int index) {
    if (index < 0 || index >= (int)g_mods_list.size()) {
        return;
    }
    mods_set_enabled(index, !g_mods_list[index].enabled);
}

ANK_FUNCTION(window_mods_show)
ANK_FUNCTION(platform_unpack_scripts)