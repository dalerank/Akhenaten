#pragma once

#include <cstdint>

#include "core/xstring.h"
#include "content/dir.h"
#include "core/flat_map.h"
#include "content/vfs.h"
#include "core/hvector.h"
#include "core/archive.h"

struct event_mods_info_updated { uint64_t count; };

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

struct mods_config {
    std::vector<mod_entry> mods_list;
};
ANK_CONFIG_STRUCT(mods_config, mods_list)

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
    bool folder = false; // a plain directory instead of an .sgx archive
    bool mounted = false;

    const xstring* find_script(pcstr name) const;
    const xstring* find_sound(pcstr name) const;

    void fill_entries();
};

struct mod_reader {
    xstring path;
    vfs::reader reader;
    xstring mod;
};

struct mods_mananger {
    flat_map<xstring, mod_info, 32> list;
    bool inupdate = false;
};

extern mods_mananger g_mods;

struct mods_options {
    vfs::path directory; // empty: "mods" under the Pharaoh data directory
    // --integraltests: mods only from `directory` (default tests/fixtures/mods), none enabled
    // from the user's config, and the enabled list is never written back.
    bool isolated = false;
};

vfs::path mods_get_path(xstring hash);
bool mods_get_enabled(xstring hash);
void mods_set_enabled(xstring hash, bool enabled);
void mods_toggle(xstring hash);
void mods_init(const mods_options& opts);
vfs::path mods_directory();
// Queues the scripts of every mounted mod; js_vm_sync calls it after a VM reset.
void mods_queue_enabled_scripts();
const mod_info& mods_find(xstring hash);
void mods_remount();
void mods_save();
void mods_load();
void mods_refresh_from_config();
void mods_refresh_available_list();
void mods_download_mod_async(xstring name);
void mods_download_info_async();

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled);
mod_reader mods_find_audio(pcstr wav_path);

vfs::path mods_exist_audio(pcstr wav_path);