#pragma once

// Internal load machinery used by GamestateIO and dump tests — not the game-facing facade.

class GamestateLoadDetail {
public:
    // Matches ChunkSerializer::unserialize version callback.
    static const int read_file_version(const char *filename, int offset);

    static void pre_load();
    static void post_load();

    /** Load a .map as a campaign mission without post_load / start. */
    static bool load_mission_map_raw(int scenario_id, const char *map_path);
};
