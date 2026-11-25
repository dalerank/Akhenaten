#include "mods.h"

#include "content/content.h"
#include "content/reader.h"
#include "content/zipreader.hpp"
#include "graphics/image.h"
#include "graphics/imagepak_holder.h"
#include "core/log.h"
#include "core/string.h"
#include "js/js.h"
#include "game/game_config.h"
#include "core/settings_vars.h"
#include "content/vfs.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "io/gamestate/boilerplate.h"
#include "window/popup_dialog.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <filesystem>

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#endif

mods_mananger g_mods;
mods_config ANK_VARIABLE_N(g_mods_config, "mods_config");

namespace {
    vfs::path g_mods_directory_override;
    bool g_mods_isolated = false;

    struct mod_dir_entry {
        std::string name;
        bool folder;
    };

    void sort_entries(std::vector<mod_dir_entry>& entries) {
        std::sort(entries.begin(), entries.end(), [](const mod_dir_entry& a, const mod_dir_entry& b) {
            return string_compare_case_insensitive(a.name.c_str(), b.name.c_str()) < 0;
        });
    }

    // Relative --mods paths are taken from the working directory, not from the data directory.
    std::vector<mod_dir_entry> mods_list_override_dir(const vfs::path& dir) {
        std::vector<mod_dir_entry> entries;
        std::error_code ec;
        for (const auto& e : std::filesystem::directory_iterator(dir.c_str(), ec)) {
            const std::string name = e.path().filename().string();
            if (e.is_directory(ec)) {
                entries.push_back({name, true});
            } else if (e.is_regular_file(ec) && vfs::file_has_extension(name.c_str(), "sgx")) {
                entries.push_back({name, false});
            }
        }
        sort_entries(entries);
        return entries;
    }

    std::vector<mod_dir_entry> mods_list_data_dir() {
        std::vector<mod_dir_entry> entries;
        const dir_listing* sgx_files = vfs::dir_find_files_with_extension("mods", "sgx");
        for (int i = 0; i < sgx_files->num_files; ++i) {
            entries.push_back({sgx_files->files[i], false});
        }
        const dir_listing* folders = vfs::dir_find_all_subdirectories("mods");
        for (int i = 0; i < folders->num_files; ++i) {
            entries.push_back({folders->files[i], true});
        }
        sort_entries(entries);
        return entries;
    }

    struct mod_pack_slot {
        int useridx = 0;
        int start_index = 0;
        int entries_num = 0;
    };

    bool mods_reserve_pack(pcstr name, int entries_num, mod_pack_slot& slot) {
        const int useridx = imagepak::get_max_useridx() + 1;
        const int start_index = imagepak::get_maxseen_imgid() + 1;
        if (useridx >= IMAGE_PAK_SLOTS || start_index + entries_num > IMAGE_CACHE_SIZE) {
            logs::error("[mods] %s does not fit: pak slot %d of %d, image ids %d..%d of %d", name, useridx,
              IMAGE_PAK_SLOTS, start_index, start_index + entries_num, IMAGE_CACHE_SIZE);
            return false;
        }
        slot = {useridx, start_index, entries_num};
        imagepak::useridx_update(useridx);
        imagepak::update_max_imgid(start_index + entries_num);
        return true;
    }

    int mods_count_images(const vfs::ZipArchive& archive) {
        return (int)std::count_if(archive.entries().begin(), archive.entries().end(),
          [](const xstring& e) { return vfs::file_has_extension(e.c_str(), "png"); });
    }

    const xstring* find_entry_nocase(const hvector<xstring, 32>& entries, pcstr name) {
        for (const auto& e : entries) {
            if (string_compare_case_insensitive(e.c_str(), name) == 0) {
                return &e;
            }
        }
        return nullptr;
    }

    // A mod file that shares its path with a built-in script is queued under the built-in's key,
    // so a later `import` of that path does not run it a second time.
    void mods_queue_scripts(const mod_info& mod) {
        for (const auto& s : mod.scripts) {
            bstring256 builtin(":", s.c_str());
            if (vfs::internal_file_open(builtin.c_str()).first) {
                js_vm_reload_file(builtin.c_str());
            } else {
                js_vm_reload_file(s.c_str());
            }
        }
    }
} // namespace

static bool mods_id_less(const xstring& a, const xstring& b) {
    const int c = string_compare_case_insensitive(a.c_str(), b.c_str());
    return c != 0 ? c < 0 : strcmp(a.c_str(), b.c_str()) < 0;
}

mod_info* mods_mananger::find(xstring id) const {
    for (const auto& m : list) {
        if (m->name == id) {
            return m.get();
        }
    }
    return nullptr;
}

mod_info& mods_mananger::add(xstring id) {
    if (mod_info* existing = find(id)) {
        return *existing;
    }
    auto pos = std::upper_bound(list.begin(), list.end(), id,
      [](const xstring& v, const std::unique_ptr<mod_info>& m) { return mods_id_less(v, m->name); });
    auto it = list.insert(pos, std::make_unique<mod_info>());
    (*it)->name = id;
    return **it;
}

static void mods_log_conflicts() {
    auto report = [](const mod_info& winner, const hvector<xstring, 32>& entries, auto find) {
        for (const auto& e : entries) {
            for (const auto& other : g_mods.list) {
                if (other.get() == &winner) {
                    break;
                }
                if (other->enabled && other->mounted && (other.get()->*find)(e.c_str())) {
                    logs::warn("[mods] conflict %s: %s overrides %s", e.c_str(), winner.name.c_str(),
                      other->name.c_str());
                }
            }
        }
    };

    for (const auto& m : g_mods.list) {
        if (m->enabled && m->mounted) {
            report(*m, m->scripts, &mod_info::find_script);
            report(*m, m->sounds, &mod_info::find_sound);
        }
    }
}

const xstring* mod_info::find_script(pcstr name) const {
    return find_entry_nocase(scripts, name);
}

const xstring* mod_info::find_sound(pcstr name) const {
    return find_entry_nocase(sounds, name);
}

namespace {

    std::string mods_describe(const std::vector<saved_mod>& list) {
        if (list.empty()) {
            return "none";
        }
        std::string text;
        for (const auto& m : list) {
            if (!text.empty()) {
                text += ", ";
            }
            text += m.id.c_str();
            if (!m.version.empty()) {
                text += " ";
                text += m.version.c_str();
            }
        }
        return text;
    }

    // The load does not switch mods on or off: which set is right is the player's call.
    // Mods of the last loaded save when they differ from the enabled ones; consumed by
    // mods_apply_saved_mods.
    std::vector<saved_mod> g_save_mods_pending;
    bool g_save_mods_differ = false;

    bool mods_saved_contains(const std::vector<saved_mod>& saved, xstring id) {
        return std::any_of(saved.begin(), saved.end(), [id](const saved_mod& m) { return m.id == id; });
    }

    std::vector<saved_mod> mods_missing(const std::vector<saved_mod>& saved) {
        std::vector<saved_mod> missing;
        for (const auto& m : saved) {
            const mod_info* mod = g_mods.find(m.id);
            if (!mod || !mod->downloaded) {
                missing.push_back(m);
            }
        }
        return missing;
    }
} // namespace

std::vector<saved_mod> mods_active_list() {
    std::vector<saved_mod> active;
    for (const auto& m : g_mods.list) {
        if (m->enabled && m->mounted && !m->broken) {
            active.push_back({m->name, m->version});
        }
    }
    return active;
}

void mods_check_save(const std::vector<saved_mod>& saved) {
    const std::vector<saved_mod> active = mods_active_list();
    g_save_mods_differ = !(saved == active);
    g_save_mods_pending = g_save_mods_differ ? saved : std::vector<saved_mod>{};
    if (!g_save_mods_differ) {
        if (!saved.empty()) {
            logs::info("[mods] the save's mods match the enabled ones: %s", mods_describe(saved).c_str());
        }
        return;
    }

    const std::vector<saved_mod> missing = mods_missing(saved);
    std::string text
      = "the save was made with mods: " + mods_describe(saved) + "; enabled now: " + mods_describe(active);
    if (!missing.empty()) {
        text += "; not installed: " + mods_describe(missing);
    }
    logs::warn("[mods] %s", text.c_str());
    if (g_mods_isolated) {
        return;
    }

    const xstring body = (text
                          + ".\nThe game may play differently than when it was saved."
                            "\nSwitch to the save's mods and load it again? (No keeps the current mods.)")
                           .c_str();
    game.add_frame_end_event([body] {
        popup_dialog::show(xstring(localization().text_from_key("#popup_dialog_save_mods_differ")), body,
          e_popup_btns_yesno, [](bool accepted) {
              if (accepted) {
                  mods_apply_saved_mods();
              }
          });
    });
}

void mods_forget_saved() {
    g_save_mods_differ = false;
    g_save_mods_pending.clear();
}

bool mods_apply_saved_mods() {
    if (!g_save_mods_differ) {
        return false;
    }
    g_save_mods_differ = false;

    const std::vector<saved_mod> saved = std::move(g_save_mods_pending);
    g_save_mods_pending.clear();
    for (auto& m : g_mods.list) {
        if (m->downloaded) {
            m->enabled = mods_saved_contains(saved, m->name);
        }
    }
    mods_remount();

    const xstring save = game.session.last_loaded_mission;
    logs::info("[mods] switched to the save's mods (%s), reloading %s", mods_describe(saved).c_str(), save.c_str());
    // Frame end events run before js_vm_frame_end, and one queued from a callback runs a frame
    // later: the double hop loads the save after the scripts of the new mod set are in.
    game.add_frame_end_event(
      [save] { game.add_frame_end_event([save] { GamestateIO::load_savegame(save.c_str()); }); });
    return true;
}

void mods_queue_enabled_scripts() {
    for (const auto& it : g_mods.list) {
        if (it->enabled && it->mounted && !it->broken) {
            mods_queue_scripts(*it);
        }
    }
}

xstring mods_owner_of_script(pcstr text) {
    if (!text || !*text) {
        return {};
    }
    for (const auto& m : g_mods.list) {
        if (!m->mounted || m->path.empty()) {
            continue;
        }
        const size_t len = strlen(m->path.c_str());
        // "<mod path>/" so that mods/a is not taken for mods/a_b.
        for (pcstr p = strstr(text, m->path.c_str()); p; p = strstr(p + 1, m->path.c_str())) {
            if (p[len] == '/') {
                return m->name;
            }
        }
    }
    return {};
}

bool mods_mark_broken(xstring id, pcstr reason) {
    mod_info* mod = g_mods.find(id);
    if (!mod || mod->broken) {
        return false;
    }
    mod->broken = true;
    logs::error("[mods] %s is broken (%s); its scripts stay unloaded until it is switched off and on", id.c_str(),
      reason ? reason : "script error");
    js_vm_request_reset();
    return true;
}

vfs::path mods_directory() {
    return g_mods_directory_override.empty() ? vfs::path("mods") : g_mods_directory_override;
}

static bool mods_valid_name(const xstring& name) {
    if (name.empty()) {
        return false;
    }
    for (pcstr c = name.c_str(); *c; ++c) {
        if (!((*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || *c == '_')) {
            return false;
        }
    }
    return true;
}

mod_info* mods_add_remote_file(xstring name, xstring uri) {
    if (!mods_valid_name(name)) {
        logs::error("[mods] bad mod name \"%s\" in the catalog, ignored", name.empty() ? "" : name.c_str());
        return nullptr;
    }

    mod_info* it = g_mods.find(name);

    if (it) {
        return it;
    }

    auto& new_mod = g_mods.add(name);
    new_mod.path = "";
    new_mod.downloaded = false;
    new_mod.url = uri;
    new_mod.name = name;

    return &new_mod;
}

vfs::path mods_get_path(xstring name) {
    mod_info* it = g_mods.find(name);
    if (!it) {
        return "";
    }
    return it->path.c_str();
}

bool mods_get_enabled(xstring name) {
    mod_info* it = g_mods.find(name);
    if (!it) {
        return false;
    }
    return it->enabled;
}

void mods_set_enabled(xstring name, bool enabled) {
    mod_info* it = g_mods.find(name);
    if (!it) {
        return;
    }
    it->enabled = enabled;
    mods_save();
}

#ifdef GAME_HAVE_CURL
struct mod_download_progress_data {
    std::string id;
    std::ofstream* file = nullptr;
    int last_progress = 0;
};

static size_t mods_download_write_callback(void* contents, size_t size, size_t nmemb,
  mod_download_progress_data* data) {
    const size_t total = size * nmemb;
    if (!data || !data->file || !data->file->write((const char*)contents, (std::streamsize)total)) {
        return 0;
    }
    return total;
}

static int mods_download_progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t,
  curl_off_t) {
    auto data = (mod_download_progress_data*)clientp;
    if (!data || dltotal <= 0) {
        return 0;
    }

    const int progress = std::clamp((int)((dlnow * 100) / dltotal), 1, 99);
    if (progress != data->last_progress) {
        data->last_progress = progress;
        game.add_frame_end_event([id = data->id, progress] {
            if (mod_info* mod = g_mods.find(xstring(id.c_str()))) {
                mod->download_progress = (uint8_t)progress;
            }
        });
    }
    return 0;
}

static bool mods_download_file(const std::string& id, const std::string& url, const std::filesystem::path& part_path) {
    std::ofstream out_file(part_path, std::ios::binary | std::ios::trunc);
    if (!out_file.is_open()) {
        logs::error("[mods] cannot write %s", part_path.string().c_str());
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        logs::error("curl_easy_init failed");
        return false;
    }

    mod_download_progress_data progress;
    progress.id = id;
    progress.file = &out_file;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mods_download_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &progress);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, mods_download_progress_callback);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progress);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);

    const CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);
    out_file.close();

    if (res != CURLE_OK || http_code != 200 || !out_file) {
        logs::error("[mods] download of %s failed: %s (HTTP %ld)", id.c_str(), curl_easy_strerror(res), http_code);
        return false;
    }
    return true;
}

struct mod_download_job {
    std::string id;
    std::string url;
    std::filesystem::path part_path;
    std::filesystem::path final_path;
    bool ok = false;
};

static void mods_finish_download(const mod_download_job& job) {
    const std::string& id = job.id;
    const std::filesystem::path& part_path = job.part_path;
    const std::filesystem::path& final_path = job.final_path;
    bool ok = job.ok;
    std::error_code ec;
    mod_info* mod = g_mods.find(xstring(id.c_str()));
    if (ok && mod) {
        std::filesystem::rename(part_path, final_path, ec);
        if (ec) {
            logs::error("[mods] cannot move %s to %s: %s", part_path.string().c_str(), final_path.string().c_str(),
              ec.message().c_str());
            ok = false;
        }
    }
    if (!ok || !mod) {
        std::filesystem::remove(part_path, ec);
        if (mod) {
            mod->download_progress = 0;
        }
        return;
    }

    const vfs::path mod_path(mods_directory(), "/", final_path.filename().string().c_str());
    const vfs::ZipArchive archive(mod_path);
    mod_pack_slot slot;
    if (!archive.isValid() || !mods_reserve_pack(id.c_str(), mods_count_images(archive), slot)) {
        logs::error("[mods] downloaded %s is not a usable mod archive, removed", id.c_str());
        std::filesystem::remove(final_path, ec);
        mod->download_progress = 0;
        return;
    }

    mod->downloaded = true;
    mod->download_progress = 100;
    mod->path = mod_path;
    mod->useridx = slot.useridx;
    mod->start_index = slot.start_index;
    mod->entries_num = slot.entries_num;
    logs::info("Successfully downloaded mod: %s", id.c_str());
}
#endif

void mods_download_info_async() {
    g_mods.inupdate = true;
    game.add_frame_end_event([]() {
        mods_refresh_available_list();
        g_mods.inupdate = false;
        events::emit(event_mods_info_updated{static_cast<uint64_t>(g_mods.list.size())});
    });
}

void mods_download_mod_async(xstring name) {
    mod_info* it = g_mods.find(name);
    if (!it) {
        logs::error("Mod not found: %s", name.c_str());
        return;
    }

    mod_info& mod = *it;

    if (mod.downloaded) {
        logs::warn("Mod already downloaded: %s", name.c_str());
        return;
    }

    if (mod.url.empty()) {
        logs::error("No download URL for mod: %s", name.c_str());
        return;
    }

    if (mod.download_progress > 0 && mod.download_progress < 100) {
        logs::warn("Mod download already in progress: %s", name.c_str());
        return;
    }
    if (!mods_valid_name(name)) {
        logs::error("[mods] bad mod name \"%s\", not downloaded", name.c_str());
        return;
    }

#ifdef GAME_HAVE_CURL
    const std::filesystem::path mods_dir = mods_directory().resolve().c_str();
    std::error_code ec;
    std::filesystem::create_directories(mods_dir, ec);
    auto job = std::make_shared<mod_download_job>();
    job->id = name.c_str();
    job->url = mod.url.c_str();
    job->final_path = mods_dir / (job->id + ".sgx");
    job->part_path = mods_dir / (job->id + ".sgx.part");

    mod.download_progress = 1;
    game.mtrpc.detach_task([job]() {
        job->ok = mods_download_file(job->id, job->url, job->part_path);
        game.add_frame_end_event([job]() { mods_finish_download(*job); });
    });
#else
    logs::error("Mod download not supported on this platform (libcurl is not available).");
    mod.download_progress = 0;
#endif
}

void mods_toggle(xstring name) {
    mod_info* it = g_mods.find(name);
    if (!it) {
        return;
    }

    it->enabled = !it->enabled;
    mods_save();
}

void mods_remount() {
    bool reset_vm = false;
    for (auto& it : g_mods.list) {
        if (!it->downloaded) {
            continue;
        }

        mod_info& mod = *it;
        if (mod.enabled) {
            if (!mod.folder) {
                vfs::mount_pack(mod.path);

                auto& modpack = g_image_data->pak_list[mod.useridx];
                if (!modpack.handle) {
                    modpack.entries_num = mod.entries_num;
                    modpack.index = mod.start_index;
                    modpack.id = mod.useridx;
                    modpack.name = mod.name;
                    modpack.delayed = true;
                    modpack.custom = true;
                }
            }

            if (!mod.mounted) {
                mod.mounted = true;
                mod.broken = false;
                mod.fill_entries();
                mods_queue_scripts(mod);
            }
        } else {
            if (!mod.folder) {
                vfs::umount_pack(mod.path);

                auto& modpack = g_image_data->pak_list[mod.useridx];
                if (modpack.handle) {
                    image_unload_pak(mod.useridx);

                    modpack.entries_num = 0;
                    modpack.index = 0;
                    modpack.id = 0;
                    modpack.delayed = true;
                    modpack.name = xstring();
                }
            }

            if (mod.mounted) {
                mod.mounted = false;
                // Scripts cannot be unloaded one by one: rebuild the VM without this mod.
                reset_vm |= !mod.scripts.empty();
            }
        }
    }

    if (reset_vm) {
        js_vm_request_reset();
    }

    mods_log_conflicts();
    mods_save();
}

void mods_init(const mods_options& opts) {
    g_mods.list.clear();

    g_mods_isolated = opts.isolated;
    g_mods_directory_override.clear();
    vfs::path requested = opts.directory;
    if (requested.empty() && opts.isolated) {
        for (pcstr fixture : {"tests/fixtures/mods", "../tests/fixtures/mods"}) {
            if (vfs::is_directory(fixture)) {
                requested = fixture;
                break;
            }
        }
    }
    if (!requested.empty()) {
        std::error_code ec;
        g_mods_directory_override = std::filesystem::absolute(requested.c_str(), ec).generic_string();
        logs::info("[mods] directory %s", g_mods_directory_override.c_str());
    }
    const vfs::path dir = mods_directory();

    auto append_mod = [&dir](const mod_dir_entry& entry) {
        pcstr file = entry.name.c_str();
        bstring128 mod_name_short(file);
        if (!entry.folder) {
            mod_name_short.replace_str(".sgx", "");
        }

        xstring mod_name(mod_name_short.c_str());
        if (g_mods.find(mod_name)) {
            logs::warn("[mods] duplicate id %s: %s ignored", mod_name.c_str(), file);
            return;
        }

        const vfs::path mod_path(dir, "/", file);
        mod_pack_slot slot;
        if (!entry.folder) {
            const vfs::ZipArchive archive(mod_path);
            if (!archive.isValid()) {
                logs::warn("[mods] %s is not a valid archive, skipped", file);
                return;
            }
            if (!mods_reserve_pack(file, mods_count_images(archive), slot)) {
                return;
            }
        }

        mod_info& mod = g_mods.add(mod_name);
        mod.path = mod_path;
        mod.name = mod_name;
        mod.downloaded = true;
        mod.folder = entry.folder;
        if (mod.folder) {
            // Plain files are opened through the OS, so the path must not stay relative to the data dir.
            mod.path = mod.path.resolve();
            mod.fill_entries();
            return;
        }

        mod.useridx = slot.useridx;
        mod.start_index = slot.start_index;
        mod.entries_num = slot.entries_num;

        mod.fill_entries();
    };

    std::vector<mod_dir_entry> entries;
    if (!g_mods_directory_override.empty()) {
        entries = mods_list_override_dir(dir);
    } else if (!opts.isolated) {
        entries = mods_list_data_dir();
    }
    for (const auto& entry : entries) {
        append_mod(entry);
    }
    mods_refresh_from_config();
}

const mod_info& mods_find(xstring hash) {
    mod_info* it = g_mods.find(hash);
    if (it) {
        return *it;
    }

    static mod_info dummy;
    return dummy;
}

vfs::path mods_exist_audio(pcstr wav_path) {
    if (!wav_path || !*wav_path) {
        return {};
    }

    if (strstr(wav_path, ".sgx/") || strstr(wav_path, ".zip/")) {
        vfs::path resolved;
        if (vfs::mounted_entry_resolve(wav_path, resolved)) {
            return resolved;
        }
        return {};
    }

    vfs::path found;
    for (const auto &it : g_mods.list) {
        if (!it->enabled || !it->downloaded || it->broken) {
            continue;
        }

        if (it->folder) {
            if (const xstring* entry = it->find_sound(wav_path)) {
                found = vfs::path(it->path.c_str(), "/", entry->c_str());
            }
            continue;
        }

        vfs::path exact(it->path.c_str(), "/", wav_path);
        vfs::path resolved;
        if (vfs::mounted_entry_resolve(exact, resolved)) {
            found = resolved;
        }
    }

    return found;
}

mod_reader mods_find_audio(pcstr wav_path) {
    vfs::path path = mods_exist_audio(wav_path);
    if (path.empty()) {
        return {};
    }

    vfs::reader reader = vfs::file_open(path, "r");
    if (reader) {
        return { path.c_str(), reader };
    }

    return {};
}

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled) {
    if (!script_path || !*script_path) {
        return {};
    }

    for (auto rit = g_mods.list.rbegin(); rit != g_mods.list.rend(); ++rit) {
        const auto& it = *rit;
        if (!it->enabled || it->broken) {
            continue;
        }

        const xstring* entry = it->find_script(script_path);
        if (!entry) {
            continue;
        }

        vfs::path mod_script_path(it->path.c_str(), "/", entry->c_str());
        vfs::reader reader = vfs::file_open(mod_script_path, "rt");
        if (reader) {
            return {mod_script_path.c_str(), reader, it->name};
        }
    }

    return {};
}

void mods_save() {
    if (g_mods_isolated) {
        return;
    }

    std::string enabled_mods;
    for (const auto& it : g_mods.list) {
        if (it->enabled) {
            enabled_mods.append(it->name.c_str());
            enabled_mods.append(",");
        }
    }
    game_features::gameopt_enabled_mods = enabled_mods.c_str();
    game_features::save();
}

void mods_load() {
    if (g_mods_isolated) {
        return;
    }

    xstring enabled_mods = game_features::gameopt_enabled_mods.to_string();

    svector<bstring64, 128> mod_names;
    string_to_array_t(mod_names, enabled_mods.c_str(), ',');

    for (const auto& name : mod_names) {
        mod_info* it = g_mods.find(xstring(name.c_str()));
        if (it) {
            it->enabled = true;
        }
    }
}

void mods_refresh_from_config() {
    for (const auto& cmod : g_mods_config.mods_list) {
        mod_info* mod = mods_add_remote_file(cmod.name, cmod.url);
        if (!mod) {
            continue;
        }
        mod->desc = cmod.desc;
        mod->version = cmod.version;
        mod->author = cmod.author;
        mod->email = cmod.email;
    }
}

void mods_refresh_available_list() {
    mods_refresh_from_config();
    mods_remount();
}

static bool is_sound_file(pcstr name) {
    return vfs::file_has_extension(name, "wav") || vfs::file_has_extension(name, "mp3")
           || vfs::file_has_extension(name, "ogg");
}

void mod_info::fill_entries() {
    if (folder) {
        scripts.clear();
        sounds.clear();
        std::error_code ec;
        const std::filesystem::path root(path.c_str());
        for (auto it = std::filesystem::recursive_directory_iterator(root, ec);
          !ec && it != std::filesystem::recursive_directory_iterator(); it.increment(ec)) {
            if (!it->is_regular_file(ec)) {
                continue;
            }
            const std::string rel = std::filesystem::relative(it->path(), root, ec).generic_string();
            if (vfs::file_has_extension(rel.c_str(), "js")) {
                scripts.push_back(xstring(rel.c_str()));
            } else if (is_sound_file(rel.c_str())) {
                sounds.push_back(xstring(rel.c_str()));
            }
        }
        return;
    }

    vfs::ZipArchive archive(path.c_str());
    if (archive.isValid()) {
        const auto& entries = archive.entries();
        scripts.clear();
        sounds.clear();
        for (const auto& entry : entries) {
            if (vfs::file_has_extension(entry.c_str(), "js")) {
                scripts.push_back(entry.tolower());
            }

            if (vfs::file_has_extension(entry.c_str(), "wav")
                || vfs::file_has_extension(entry.c_str(), "mp3")
                || vfs::file_has_extension(entry.c_str(), "ogg")) {
                sounds.push_back(entry.tolower());
            }
        }
    }
}