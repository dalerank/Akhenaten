#pragma once

#include "content/path.h"
#include "core/xstring.h"
#include "game/player_record.h"

struct player_profile_t {
    xstring name;

    bool valid() const { return !name.empty(); }
    vfs::path folder() const;

    static bool create(pcstr player_name);
    static bool remove(pcstr player_name);

    bool select(pcstr player_name);
    bool save() const;

    const player_record& record(int scenario_id) const;
    bool beaten(int scenario_id) const;
    void record_win(const mission_result_t& result);

    pcstr last_autosave() const { return last_autosave_path.c_str(); }

    player_record records[MAX_PLAYER_SCENARIOS];
    vfs::path last_autosave_path;

private:
    bool load_progress();
    bool import_legacy_dat();
    void find_last_autosave();
};

extern player_profile_t g_player;
