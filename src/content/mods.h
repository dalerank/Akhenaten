#pragma once

#include "core/xstring.h"
#include "content/dir.h"
#include "core/flat_map.h"
#include "content/vfs.h"
#include "core/hvector.h"
#include "core/archive.h"

struct mod_entry {
    xstring name;
    xstring desc;
    xstring version;
    xstring author;
    xstring url;
    xstring email;
};
ANK_CONFIG_STRUCT(mod_entry,
    name, desc, version, author, url, email)

struct mod_url {
    xstring url;
};
ANK_CONFIG_STRUCT(mod_url, url)

struct mods_config {
    std::vector<mod_url> mods_repo;
    std::vector<mod_entry> mods_list;
};
ANK_CONFIG_STRUCT(mods_config,
    mods_repo, mods_list)

struct mod_info : public mod_entry {
    vfs::path path;
    uint16_t useridx;
    uint16_t start_index;
    uint16_t entries_num;
    hvector<xstring, 32> scripts;
    hvector<xstring, 32> sounds;
    uint8_t download_progress = 0;
    bool downloaded = false;
    bool enabled = false;

    bool script_exist(const xstring& name) const {
        auto it = std::find(scripts.begin(), scripts.end(), name);
        return (it != scripts.end());
    }

    bool audio_exist(const xstring &name) const {
        auto it = std::find(sounds.begin(), sounds.end(), name);
        return (it != sounds.end());
    }

    void fill_entries();
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
void mods_save();
void mods_load();
void mods_refresh_available_list();
void mods_download_mod_async(xstring name);

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled);
mod_reader mods_find_audio(pcstr wav_path);

vfs::path mods_exist_audio(pcstr wav_path);