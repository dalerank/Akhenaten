#include "content/mods.h"

#include "core/profiler.h"
#include "js/js_game.h"

int __mods_count() {
    return (int)g_mods_list.size();
}

pcstr __mods_name(int index) {
    int i = 0;
    for (auto& p : g_mods_list) {
        if (i == index) return p.second.name.c_str();
        ++i;
    }
    return "";
}

ANK_FUNCTION(__mods_count)
ANK_FUNCTION_1(__mods_name)
