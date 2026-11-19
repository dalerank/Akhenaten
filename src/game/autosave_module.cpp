#include "game/autosave_module.h"

#include "content/vfs.h"
#include "core/app_module.h"
#include "core/log.h"
#include "core/xvalue.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "io/gamestate/boilerplate.h"
#include "window/file_dialog_common.h"

#include <filesystem>

pcstr autosave_module_t::basename_of(pcstr path) {
    if (!path || !*path) {
        return "";
    }
    pcstr slash = path;
    for (pcstr p = path; *p; ++p) {
        if (*p == '/' || *p == '\\') {
            slash = p + 1;
        }
    }
    return slash;
}

bool autosave_module_t::starts_with_ci(pcstr s, pcstr prefix) {
    if (!s || !prefix) {
        return false;
    }
    while (*prefix) {
        const char a = (*s >= 'A' && *s <= 'Z') ? (char)(*s - 'A' + 'a') : *s;
        const char b = (*prefix >= 'A' && *prefix <= 'Z') ? (char)(*prefix - 'A' + 'a') : *prefix;
        if (!*s || a != b) {
            return false;
        }
        ++s;
        ++prefix;
    }
    return true;
}

uint64_t autosave_module_t::file_mtime_or_max(pcstr full_path) {
    namespace fs = std::filesystem;
    std::error_code ec;
    const auto ft = fs::last_write_time(full_path, ec);
    if (ec) {
        return UINT64_MAX;
    }
    return (uint64_t)ft.time_since_epoch().count();
}

int autosave_module_t::clamp_slots(int slots) {
    if (slots < 1) {
        return 1;
    }
    if (slots > k_max_slots) {
        return k_max_slots;
    }
    return slots;
}

bool autosave_module_t::is_monthly_filename(pcstr filename_short) {
    return starts_with_ci(basename_of(filename_short), "autosave_month");
}

bool autosave_module_t::is_ironwill_exempt_save(pcstr filename_short) {
    pcstr base = basename_of(filename_short);
    return starts_with_ci(base, "ironwill.") || starts_with_ci(base, "autosave_replay.");
}

bstring256 autosave_module_t::format_monthly_filename(int slots, int slot_1based, pcstr extension) {
    bstring256 name;
    const char *ext = (extension && *extension) ? extension : "svx";
    if (slots <= 1) {
        name.printf("autosave_month.%s", ext);
        return name;
    }
    int slot = slot_1based;
    if (slot < 1) {
        slot = 1;
    }
    if (slot > slots) {
        slot = slots;
    }
    name.printf("autosave_month_%d.%s", slot, ext);
    return name;
}

int autosave_module_t::pick_slot(int slots, const bool *exists, const uint64_t *mtime) {
    slots = clamp_slots(slots);
    if (!exists) {
        return 1;
    }
    for (int i = 0; i < slots; ++i) {
        if (!exists[i]) {
            return i + 1;
        }
    }
    int best = 1;
    uint64_t best_m = mtime ? mtime[0] : 0;
    for (int i = 1; i < slots; ++i) {
        const uint64_t m = mtime ? mtime[i] : 0;
        if (m < best_m) {
            best_m = m;
            best = i + 1;
        }
    }
    return best;
}

bstring256 autosave_module_t::next_monthly_filename(pcstr extension) {
    const int slots = clamp_slots(game_features::gameopt_autosave_slots.to_int());
    if (slots <= 1) {
        bstring256 name = format_monthly_filename(1, 1, extension);
        logs::info("Autosave: slots=%d (legacy) → %s", slots, name.c_str());
        return name;
    }

    bool exists[k_max_slots] = {};
    uint64_t mtime[k_max_slots] = {};
    int existing = 0;
    for (int i = 0; i < slots; ++i) {
        bstring256 short_name = format_monthly_filename(slots, i + 1, extension);
        vfs::path full = fullpath_saves(short_name.c_str()).resolve();
        exists[i] = vfs::file_exists(full);
        mtime[i] = exists[i] ? file_mtime_or_max(full.c_str()) : UINT64_MAX;
        if (exists[i]) {
            ++existing;
        }
    }
    const int slot = pick_slot(slots, exists, mtime);
    bstring256 name = format_monthly_filename(slots, slot, extension);
    const bool was_missing = !exists[slot - 1];
    logs::info("Autosave: slots=%d existing=%d → %s (%s)",
               slots,
               existing,
               name.c_str(),
               was_missing ? "empty slot" : "oldest overwrite");
    return name;
}

void autosave_module_t::on_advance_month() {
    if (!game_features::gameopt_monthly_autosave.to_bool()) {
        return;
    }
    if (game_features::gameopt_ironwill.to_bool()) {
        logs::info("Autosave: skipped (Ironwill mode)");
        return;
    }
    bstring256 autosave_file = next_monthly_filename(saved_game_data_expanded.extension);
    logs::info("Autosave: writing monthly save %s", autosave_file.c_str());
    if (!GamestateIO::write_savegame(autosave_file)) {
        logs::error("Autosave: write failed for %s", autosave_file.c_str());
    }
}

void autosave_module_t::register_callbacks() {
    events::subscribe_permanent([this](event_advance_month) {
        on_advance_month();
    });
    logs::info("Autosave: module registered (monthly event)");
}

void ANK_REGISTER_APPLICATION_MODULE(register_autosave_module) {
    auto &module = xvalue<autosave_module_t>::ref();
    module.register_callbacks();
}
