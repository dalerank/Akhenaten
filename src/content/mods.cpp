#include "mods.h"

#include "content/content.h"
#include "content/reader.h"
#include "content/zipreader.hpp"
#include "core/log.h"
#include "js/js.h"

flat_map<xstring, mod_info, 32> g_mods_list;

vfs::path mods_get_path(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return "";
    }
    return it->second.path.c_str();
}

bool mods_get_enabled(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return false;
    }
    return it->second.enabled;
}

void mods_set_enabled(xstring name, bool enabled) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return;
    }
    it->second.enabled = enabled;
}

void mods_toggle(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return;
    }

    it->second.enabled = !it->second.enabled;
}

void mods_remount() {
    for (const auto &it : g_mods_list) {
        if (it.second.enabled) {
            vfs::mount_pack(it.second.path.c_str());

            for (const auto &s: it.second.scripts) {
                js_vm_reload_file(s.c_str());
            }
        } else {
            vfs::umount_pack(it.second.path.c_str());

            for (const auto &s : it.second.scripts) {
                js_vm_reload_file(s.c_str());
            }
        }
    }
}

void mods_init() {
    g_mods_list.clear();

    auto append_mods = [] (pcstr dir, const dir_listing *files) {
        for (int i = 0; i < files->num_files; ++i) {
            bstring128 mod_name_short(files->files[i]);
            mod_name_short.replace_str(".sgx", "");
            mod_name_short.replace_str(dir, "");

            xstring mod_name(mod_name_short.c_str());
            auto it = g_mods_list.find(mod_name);
            if (it == g_mods_list.end()) {
                mod_info &mod = g_mods_list[mod_name];
                mod.path.printf("Mods/%s", files->files[i]);
                mod.name = mod_name;

                vfs::path full_path = vfs::path::resolve(mod.path.c_str()).resolve();
                if (full_path.empty()) {
                    continue;
                }

                vfs::ZipArchive archive(full_path);
                if (!archive.isValid()) {
                    continue;
                }

                const auto &entries = archive.entries();
                mod.scripts.clear();

                for (const auto &entry : entries) {
                    if (vfs::file_has_extension(entry.c_str(), "js")) {
                        mod.scripts.push_back(entry);
                    }
                }
            } else {
                logs::warn("WARN! Duplicate mod %s", mod_name.c_str());
            }
        }
    };

    const dir_listing *sgx_files = vfs::dir_find_files_with_extension("Mods", "sgx");
    append_mods("Mods/", sgx_files);
}

const mod_info &mods_find(xstring hash) {
    auto it = g_mods_list.find(hash);
    if (it != g_mods_list.end()) {
        return it->second;
    }

    static mod_info dummy;
    return dummy;
}

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled) {
    if (!script_path || !*script_path) {
        return {};
    }

    for (const auto &it : g_mods_list) {
        if (!it.second.enabled) {
            continue;
        }

        if (!it.second.exist(script_path)) {
            continue;
        }

        vfs::path mod_script_path(it.second.path.c_str(), "/", script_path);
        vfs::reader reader = vfs::file_open(mod_script_path, "rt");
        if (reader) {
            return { mod_script_path.c_str(), reader };
        }
    }

    return {};
}