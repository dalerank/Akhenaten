#include "io/og_save/og_save.h"

#include "content/vfs.h"
#include "core/zip.h"

#include <cstdio>

namespace og {

    static const chunk_spec k_chunks[CHUNK_COUNT] = {
      {"mission_id", 1, 1, false},
      {"campaign", 1, 1, false},
      {"previous_campaign_link", 1, 1, false},
      {"campaign_link", 1, 1, false},
      {"file_version", 4, 1, false},
      {"schema_count", 4, 1, false},
      {"schema", 20, 300, false},
      {"grid_images", 4, 51984, true},
      {"grid_edge", 1, 51984, true},
      {"grid_building_ids", 2, 51984, true},
      {"grid_terrain", 4, 51984, true},
      {"grid_canals", 1, 51984, true},
      {"grid_figure_ids", 2, 51984, true},
      {"grid_bitfields", 1, 51984, true},
      {"grid_sprite", 1, 51984, true},
      {"grid_random", 1, 51984, false},
      {"grid_desirability", 1, 51984, true},
      {"grid_elevation", 1, 51984, true},
      {"grid_building_damage", 2, 51984, true},
      {"grid_canals_backup", 1, 51984, true},
      {"grid_sprite_backup", 1, 51984, true},
      {"figures", 388, 2000, true},
      {"route_figure_ids", 2, 1000, true},
      {"route_paths", 1, 500000, true},
      {"formations", 144, 50, true},
      {"formation_id_last_in_use", 4, 1, false},
      {"formation_id_last_legion", 4, 1, false},
      {"formation_num_legions", 4, 1, false},
      {"city_players", 18904, 2, true},
      {"city_player_faction", 2, 2, false},
      {"city_player_names", 32, 2, false},
      {"city_current_player", 4, 1, false},
      {"buildings", 264, 4000, true},
      {"city_view_orientation", 4, 1, false},
      {"game_time_tick", 4, 1, false},
      {"game_time_day", 4, 1, false},
      {"game_time_month", 4, 1, false},
      {"game_time_year", 4, 1, false},
      {"game_time_total_days", 4, 1, false},
      {"building_highest_id_ever", 4, 1, false},
      {"city_locusts_countdown", 4, 1, false},
      {"random_iv1", 4, 1, false},
      {"random_iv2", 4, 1, false},
      {"camera_x", 4, 1, false},
      {"camera_y", 4, 1, false},
      {"city_population_graph_order", 4, 1, false},
      {"city_hailstorm_countdown", 4, 1, false},
      {"empire_scroll_x", 4, 1, false},
      {"empire_scroll_y", 4, 1, false},
      {"empire_selected_object", 4, 1, false},
      {"empire_cities", 106, 61, true},
      {"building_count_industry_total", 4, 36, false},
      {"building_count_industry_active", 4, 36, false},
      {"trade_prices", 8, 36, false},
      {"name_counter_slot_40", 4, 1, false},
      {"name_counter_slot_39", 4, 1, false},
      {"name_counter_slot_38", 4, 1, false},
      {"name_counter_slot_37", 4, 1, false},
      {"name_counter_slot_36", 4, 1, false},
      {"name_counter_slot_35", 4, 1, false},
      {"name_counter_slot_34", 4, 1, false},
      {"name_counter_slot_33", 4, 1, false},
      {"name_counter_slot_32", 4, 1, false},
      {"name_counter_slot_31", 4, 1, false},
      {"name_counter_slot_30", 4, 1, false},
      {"name_counter_slot_29", 4, 1, false},
      {"name_counter_slot_28", 4, 1, false},
      {"name_counter_slot_27", 4, 1, false},
      {"name_counter_slot_26", 4, 1, false},
      {"name_counter_slot_25", 4, 1, false},
      {"name_counter_slot_24", 4, 1, false},
      {"name_counter_slot_23", 4, 1, false},
      {"name_counter_slot_22", 4, 1, false},
      {"name_counter_slot_21", 4, 1, false},
      {"name_counter_slot_20", 4, 1, false},
      {"scenario", 1592, 1, false},
      {"scenario_max_year", 4, 1, false},
      {"messages", 48, 1000, true},
      {"city_message_next_sequence", 4, 1, false},
      {"city_message_total", 4, 1, false},
      {"city_message_current_id", 4, 1, false},
      {"city_message_population_shown", 1, 10, false},
      {"city_message_count", 4, 20, false},
      {"city_message_delay", 4, 20, false},
      {"building_burning_total", 4, 1, false},
      {"building_burning_size", 4, 1, false},
      {"figure_created_sequence", 4, 1, false},
      {"starting_favor", 4, 1, false},
      {"personal_savings_last_mission", 4, 1, false},
      {"current_mission_id", 4, 1, false},
      {"invasion_warnings", 32, 101, true},
      {"is_custom_scenario", 4, 1, false},
      {"city_sounds", 128, 70, false},
      {"building_highest_id", 4, 1, false},
      {"empire_traders", 88, 100, false},
      {"trader_next_index", 4, 1, false},
      {"building_list_burning", 2, 500, true},
      {"building_list_small", 2, 500, true},
      {"building_list_large", 2, 4000, true},
      {"saved_reserved_1", 4, 1, false},
      {"scenario_start_flags_empire_locked", 4, 1, false},
      {"name_counter_slot_3", 4, 1, false},
      {"name_counter_slot_2", 4, 1, false},
      {"name_counter_slot_1", 4, 1, false},
      {"name_counter_slot_0", 4, 1, false},
      {"city_frogs_countdown", 4, 1, false},
      {"pyramid_speedup_countdown", 4, 1, false},
      {"map_sweep_total", 4, 1, false},
      {"enemy_army_enemy_formations", 4, 1, false},
      {"enemy_army_enemy_strength", 4, 1, false},
      {"enemy_army_legion_formations", 4, 1, false},
      {"enemy_army_legion_strength", 4, 1, false},
      {"enemy_army_update_counter", 4, 1, false},
      {"building_storages", 196, 200, false},
      {"trade_route_limits", 144, 20, true},
      {"trade_route_traded", 144, 20, true},
      {"building_barracks_tower_sentry_request", 4, 1, false},
      {"building_extra_sequence", 4, 1, false},
      {"routing_stats_unused_b", 4, 1, false},
      {"routing_stats_enemy_routes_calculated", 4, 1, false},
      {"routing_stats_total_routes_calculated", 4, 1, false},
      {"routing_stats_unused_a", 4, 1, false},
      {"city_entry_flag_x", 4, 1, false},
      {"city_entry_flag_y", 4, 1, false},
      {"city_exit_flag_x", 4, 1, false},
      {"city_exit_flag_y", 4, 1, false},
      {"invasion_last_id", 2, 1, false},
      {"building_corrupt_houses_a", 4, 1, false},
      {"building_corrupt_houses_b", 4, 1, false},
      {"scenario_map_name", 65, 1, false},
      {"map_bookmarks", 8, 4, false},
      {"map_sweep_countdown", 4, 1, false},
      {"city_entry_flag_offset", 4, 1, false},
      {"city_exit_flag_offset", 4, 1, false},
      {"saved_with_game", 4, 99, false},
      {"grid_soil_fertility", 1, 51984, false},
      {"scenario_events", 18628, 1, false},
      {"ferry_queues", 224, 50, false},
      {"ferry_paths", 44, 50, false},
      {"figure_name_counters_unused", 4, 4, false},
      {"dock_queues", 820, 10, false},
      {"empire_map_headers", 32, 40, true},
      {"empire_objects", 98, 200, true},
      {"empire_routes", 324, 50, true},
      {"grid_vegetation_growth", 1, 51984, false},
      {"vegetation_growth_state", 20, 1, false},
      {"sphinx_spots", 24, 22, false},
      {"floodplain_settings", 36, 1, true},
      {"grid_service_visit", 4, 51984, true},
      {"sun_temple_spots", 24, 13, false},
      {"name_counter_ext_0", 4, 1, false},
      {"name_counter_ext_1", 4, 1, false},
      {"name_counter_ext_2", 4, 1, false},
      {"name_counter_ext_3", 4, 1, false},
      {"name_counter_ext_4", 4, 1, false},
      {"name_counter_ext_5", 4, 1, false},
      {"name_counter_ext_6", 4, 1, false},
      {"name_counter_ext_7", 4, 1, false},
      {"name_counter_ext_8", 4, 1, false},
      {"name_counter_ext_9", 4, 1, false},
      {"name_counter_ext_10", 4, 1, false},
      {"name_counter_ext_11", 4, 1, false},
      {"name_counter_ext_12", 4, 1, false},
      {"name_counter_ext_13", 4, 1, false},
      {"name_counter_ext_14", 4, 1, false},
      {"name_counter_ext_15", 4, 1, false},
      {"tutorial_flags_a", 1, 26, false},
      {"tutorial_flags_b", 1, 15, false},
      {"grid_rubble_building_type", 1, 51984, true},
      {"game_is_replay", 1, 1, false},
      {"grid_moisture", 1, 51984, true},
      {"obelisk_small_spots", 24, 10, false},
      {"obelisk_large_spots", 24, 18, false},
      {"mummies_max", 4, 1, false},
      {"difficulty", 4, 1, false},
      {"record_savings", 12, 1, false},
      {"library_spots", 24, 27, false},
      {"caesareum_spots", 24, 27, false},
      {"lighthouse_spots", 24, 15, false},
      {"abu_simbel_spots", 24, 56, false},
      {"royal_tomb_chamber_spots", 24, 75, false},
    };

    // The original writer stores a compressed chunk as [u32 header][payload]: the header is the packed size,
    // CHUNK_STORED for a raw copy, or 0 when every byte is zero.
    static constexpr uint32_t CHUNK_STORED = 0x80000000u;

    const chunk_spec& chunk_info(int index) {
        return k_chunks[index];
    }

    int savegame::city_player_index() const {
        const int32_t current = value<int32_t>(CHUNK_CITY_CURRENT_PLAYER);
        return (current >= 0 && current < (int)players.size()) ? current : 1;
    }

    const city_player& savegame::player() const {
        return players[city_player_index()];
    }

    namespace {

        struct cursor {
            const uint8_t* data;
            size_t size;
            size_t pos = 0;

            bool take(void* dst, size_t n) {
                if (n > size - pos) {
                    return false;
                }
                std::memcpy(dst, data + pos, n);
                pos += n;
                return true;
            }
        };

        bool fail(std::string& error, const char* fmt, int a = 0, int b = 0, int c = 0) {
            char buf[256];
            std::snprintf(buf, sizeof(buf), fmt, a, b, c);
            error = buf;
            return false;
        }

        bool read_chunk(cursor& in, int index, bool compressed, std::vector<uint8_t>& out, std::string& error) {
            const chunk_spec& spec = k_chunks[index];
            const size_t raw_size = (size_t)spec.element_size * spec.count;
            out.assign(raw_size, 0);
            if (!compressed) {
                return in.take(out.data(), raw_size)
                       || fail(error, "chunk %d (%d bytes) runs past the end of the file", index, (int)raw_size);
            }

            uint32_t header = 0;
            if (!in.take(&header, sizeof(header))) {
                return fail(error, "chunk %d: compressed header runs past the end of the file", index);
            }
            if (header == 0) {
                return true;
            }
            if (header == CHUNK_STORED) {
                return in.take(out.data(), raw_size)
                       || fail(error, "chunk %d: stored payload runs past the end of the file", index);
            }
            if (header > in.size - in.pos) {
                return fail(error, "chunk %d: compressed payload of %d bytes runs past the end of the file", index,
                  (int)header);
            }
            int written = (int)raw_size;
            const int ok = zip_decompress(in.data + in.pos, (int)header, out.data(), &written);
            in.pos += header;
            if (!ok || written != (int)raw_size) {
                return fail(error, "chunk %d: decompressed %d bytes, expected %d", index, written, (int)raw_size);
            }
            return true;
        }

        template <typename T>
        bool take_records(const savegame& s, e_chunk c, std::vector<T>& out, std::string& error) {
            const chunk_spec& spec = k_chunks[c];
            if ((int)sizeof(T) != spec.element_size) {
                return fail(error, "chunk %d: record of %d bytes, OG struct has %d", c, spec.element_size,
                  (int)sizeof(T));
            }
            out.resize(spec.count);
            std::memcpy(out.data(), s.chunks[c].data(), s.chunks[c].size());
            return true;
        }

        template <typename T>
        bool take_record(const savegame& s, e_chunk c, T& out, std::string& error) {
            if (s.chunks[c].size() != sizeof(T)) {
                return fail(error, "chunk %d: %d bytes, OG struct has %d", c, (int)s.chunks[c].size(), (int)sizeof(T));
            }
            std::memcpy(&out, s.chunks[c].data(), sizeof(T));
            return true;
        }

    } // namespace

    bool read_savegame(const uint8_t* data, size_t size, savegame& out, std::string& error) {
        cursor in{data, size};
        out = savegame();

        for (int i = CHUNK_MISSION_ID; i <= CHUNK_SCHEMA_COUNT; ++i) {
            if (!read_chunk(in, i, false, out.chunks[i], error)) {
                return false;
            }
        }
        out.version = out.value<int32_t>(CHUNK_FILE_VERSION);
        out.schema_count = out.value<int32_t>(CHUNK_SCHEMA_COUNT);
        if (out.version != SAVE_VERSION) {
            return fail(error, "save version %d is not supported (expected %d)", out.version, SAVE_VERSION);
        }
        if (out.schema_count != CHUNK_COUNT) {
            return fail(error, "file declares %d chunks, a v%d save has %d", out.schema_count, SAVE_VERSION,
              CHUNK_COUNT);
        }

        if (!read_chunk(in, CHUNK_SCHEMA, false, out.chunks[CHUNK_SCHEMA], error)) {
            return false;
        }
        const auto* schema = out.array<chunk_schema_record>(CHUNK_SCHEMA);
        std::array<bool, CHUNK_COUNT> absent = {};
        for (int i = 0; i < CHUNK_COUNT; ++i) {
            const chunk_spec& spec = k_chunks[i];
            // Some v160 files carry only the base chunks with the Cleopatra records left empty in the schema; the
            // bytes then end after chunk 146.
            absent[i] = i >= CHUNK_FIRST_EXTENDED && schema[i].element_size == 0 && schema[i].count == 0;
            if (absent[i]) {
                continue;
            }
            if (schema[i].element_size != spec.element_size || schema[i].count != spec.count
                || (schema[i].compressed != 0) != spec.compressed) {
                char buf[256];
                std::snprintf(buf, sizeof(buf), "chunk %d (%s): file schema %dx%d%s, expected %dx%d%s", i, spec.name,
                  schema[i].element_size, schema[i].count, schema[i].compressed ? " compressed" : "", spec.element_size,
                  spec.count, spec.compressed ? " compressed" : "");
                error = buf;
                return false;
            }
        }

        for (int i = CHUNK_SCHEMA + 1; i < CHUNK_COUNT; ++i) {
            if (absent[i]) {
                // An empty compressed chunk still has its 4-byte header.
                uint32_t header = 0;
                if (schema[i].compressed && !in.take(&header, sizeof(header))) {
                    return fail(error, "chunk %d: compressed header runs past the end of the file", i);
                }
                out.chunks[i].assign((size_t)k_chunks[i].element_size * k_chunks[i].count, 0);
                out.missing_chunks++;
                continue;
            }
            if (!read_chunk(in, i, k_chunks[i].compressed, out.chunks[i], error)) {
                return false;
            }
        }
        if (in.pos != in.size) {
            return fail(error, "%d bytes left after the last chunk", (int)(in.size - in.pos));
        }

        return take_records(out, CHUNK_BUILDINGS, out.buildings, error)
               && take_records(out, CHUNK_FIGURES, out.figures, error)
               && take_records(out, CHUNK_FORMATIONS, out.formations, error)
               && take_records(out, CHUNK_CITY_PLAYERS, out.players, error)
               && take_records(out, CHUNK_CITY_PLAYER_NAMES, out.player_names, error)
               && take_record(out, CHUNK_SCENARIO, out.scenario, error)
               && take_records(out, CHUNK_EMPIRE_CITIES, out.empire_cities, error)
               && take_records(out, CHUNK_EMPIRE_OBJECTS, out.empire_objects, error)
               && take_records(out, CHUNK_EMPIRE_ROUTES, out.empire_routes, error)
               && take_records(out, CHUNK_EMPIRE_TRADERS, out.empire_traders, error)
               && take_records(out, CHUNK_EMPIRE_MAP_HEADERS, out.empire_map_headers, error)
               && take_records(out, CHUNK_MESSAGES, out.messages, error)
               && take_records(out, CHUNK_CITY_SOUNDS, out.city_sounds, error)
               && take_records(out, CHUNK_BUILDING_STORAGES, out.storages, error)
               && take_records(out, CHUNK_FERRY_QUEUES, out.ferry_queues, error)
               && take_records(out, CHUNK_FERRY_PATHS, out.ferry_paths, error)
               && take_records(out, CHUNK_DOCK_QUEUES, out.dock_queues, error)
               && take_record(out, CHUNK_FLOODPLAIN_SETTINGS, out.floodplain, error)
               && take_record(out, CHUNK_VEGETATION_GROWTH_STATE, out.vegetation_growth, error);
    }

    bool read_savegame_file(const char* path, savegame& out, std::string& error) {
        vfs::reader file = vfs::file_open(vfs::path(path));
        if (!file) {
            error = "cannot open file";
            return false;
        }
        return read_savegame((const uint8_t*)file->data(), (size_t)file->size(), out, error);
    }

} // namespace og
