#include "content/mods.h"

#include "core/profiler.h"
#include "js/js_game.h"

int __mods_count() { return (int)g_mods_list.size(); } ANK_FUNCTION(__mods_count)

pcstr __mods_name(int index) {
    int i = 0;
    for (auto& p : g_mods_list) {
        if (i == index) return p.second.name.c_str();
        ++i;
    }
    return "";
}
ANK_FUNCTION_1(__mods_name)

pcstr __mods_display_name(pcstr mod_id) { return mods_find(mod_id).name.c_str(); } ANK_FUNCTION_1(__mods_display_name)
bool __mods_downloaded(pcstr mod_id) { return mods_find(mod_id).downloaded; } ANK_FUNCTION_1(__mods_downloaded)
int __mods_download_progress(pcstr mod_id) { return mods_find(mod_id).download_progress; } ANK_FUNCTION_1(__mods_download_progress)
bool __mods_enabled(pcstr mod_id) { return mods_find(mod_id).enabled; } ANK_FUNCTION_1(__mods_enabled)

void __mods_download_mod_async(pcstr mod_id) { mods_download_mod_async(mod_id); } ANK_FUNCTION_1(__mods_download_mod_async)
void __mods_toggle(pcstr mod_id) { mods_toggle(mod_id); } ANK_FUNCTION_1(__mods_toggle)
void __mods_remount() { mods_remount(); } ANK_FUNCTION(__mods_remount)

