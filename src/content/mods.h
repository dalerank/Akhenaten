#pragma once

#include <cstdint>

#include "core/xstring.h"
#include "content/dir.h"
#include <memory>
#include <vector>
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
    // A script of this mod threw or failed to parse; it stays out of the VM until switched off and on.
    bool broken = false;

    const xstring* find_script(pcstr name) const;
    const xstring* find_sound(pcstr name) const;

    void fill_entries();
};

struct mod_reader {
    xstring path;
    vfs::reader reader;
    xstring mod;
};

// Mod order and conflicts
// -----------------------
// Mods are kept sorted by id (file or folder name, case-insensitive). That is the order in which
// they are mounted, get image pack slots and run their scripts, and it is the only conflict rule:
// when two enabled mods provide the same file (script or sound), the one later in id order wins
// (e.g. `b_mod/speech.js` over `a_mod/speech.js`); a mod file always wins over the built-in one.
// mods_remount logs every such clash as "[mods] conflict <path>: <winner> overrides <loser>".
// Image packs never clash: each mod's pack is named after its id.
struct mods_mananger {
    // unique_ptr keeps mod_info addresses stable while the list grows.
    std::vector<std::unique_ptr<mod_info>> list;
    bool inupdate = false;

    mod_info* find(xstring id) const;
    mod_info& add(xstring id);
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
// Queues the scripts of every mounted, working mod; js_vm_sync calls it after a VM reset.
void mods_queue_enabled_scripts();
// Id of the mounted mod whose file path appears in `text` (a script name, error or stack trace).
xstring mods_owner_of_script(pcstr text);
// Marks the mod broken and asks for a VM rebuild without it. False if it was already broken.
bool mods_mark_broken(xstring id, pcstr reason);
// After loading a save made with other mods: enable exactly the save's installed mods and load the
// save again. False when the last load had no mismatch.
bool mods_apply_saved_mods();
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