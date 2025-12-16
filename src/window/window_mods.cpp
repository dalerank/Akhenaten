#include "window_mods.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player_data.h"
#include "game/game.h"
#include "content/content.h"
#include "content/reader.h"
#include "core/log.h"
#include "window/popup_dialog.h"
#include "js/js_game.h"
#include "content/dir.h"
#include "core/xstring.h"
#include "core/flat_map.h"
#include "content/mods.h"
#include "graphics/text.h"

#include <vector>
#include <map>

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
            text.printf("[%s] %s", mod.enabled ? "ON" : "OFF", mod.name.c_str());
            
            text_draw(text.c_str(), pos.x, pos.y, font, 0);
        });

        mods->onclick_double_ex_item([] (scrollable_list::entry_data* item) {
            if (!item) {
                return;
            }

            mods_toggle(item->text);
            mods_remount();
        });
    }
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));

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

ANK_FUNCTION(window_mods_show)
ANK_FUNCTION(platform_unpack_scripts)