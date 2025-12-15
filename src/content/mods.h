#pragma once

#include "core/xstring.h"
#include "content/dir.h"
#include "core/flat_map.h"
#include "content/vfs.h"

struct mod_info {
    xstring path;
    xstring name;
    xstring desc;
    uint16_t useridx;
    uint16_t start_index;
    uint16_t entries_num;
    svector<xstring, 16> scripts;
    bool enabled = false;

    bool exist(const xstring& name) const {
        auto it = std::find(scripts.begin(), scripts.end(), name);
        return (it != scripts.end());
    }
};

struct mod_reader {
    xstring path;
    vfs::reader reader;
};

extern flat_map<xstring, mod_info, 32> g_mods_list;

vfs::path mods_get_path(xstring hash);
bool mods_get_enabled(xstring hash);
void mods_set_enabled(xstring hash, bool enabled);
void mods_toggle(xstring hash);
void mods_init();
const mod_info& mods_find(xstring hash);
void mods_remount();

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled);