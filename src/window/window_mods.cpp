#include "window_mods.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player.h"
#include "game/game.h"
#include "content/content.h"
#include "content/reader.h"
#include "core/log.h"
#include "js/js_game.h"
#include "content/dir.h"
#include "core/xstring.h"
#include "core/flat_map.h"
#include "content/mods.h"
#include "window/popup_dialog.h"

#include <vector>
#include <map>
#include <algorithm>

ui::mods_window g_mods_window;

void ui::mods_window::init() {
    autoconfig_window::init();

    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->clear();
        mods->onrefill([] (escrollable_list::entry_data_vec &r) {
            for (auto &mod : g_mods_list) {
                r.push_back({ mod.second.name, 0 });
            }
        });

        mods->refill();
        mods->onrender_item([] (int index, int flags, const scrollable_list::entry_data &entry, vec2i pos, e_font font) {
            const mod_info &mod = mods_find(entry.text);

            bstring128 text;
            bstring128 mod_name;
            if (!mod.downloaded) {
                if (mod.download_progress > 0) {
                    text.printf("[%d] ", mod.download_progress);
                } else {
                    text.printf("[n/a] ");
                }

                mod_name = mod.name.c_str();
                int num_points = (game.frame % 90) / 30;
                for (int i = 0; i < num_points; ++i) {
                    mod_name.append('.');
                }
            } else {
                text.printf("[%s] ", mod.enabled ? "ON" : "OFF");
                mod_name = mod.name.c_str();
            }
            
            text.append(mod_name.c_str());
            text_draw(text.c_str(), pos.x, pos.y, font, 0);
        });

        mods->onclick_double_ex_item([] (scrollable_list::entry_data*entry) {
            if (!entry) {
                return;
            }

            const mod_info &mod = mods_find(entry->text);
            if (!mod.downloaded) {
                if (mod.download_progress == 0) {
                    mods_download_mod_async(entry->text);
                }
            } else {
                mods_toggle(entry->text);
                mods_remount();
            }
        });
    }
}

void ui::mods_window::update_mods() {
    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->refill();
    }
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));

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