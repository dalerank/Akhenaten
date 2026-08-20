#include "file_schemas.h"

#include "chunks.h"
#include "grid/image.h"
#include "io/chunk_serializer.h"

// Classic Pharaoh .sav — positional, compressed chunks.
void file_schema_sav(const int file_version) {
    g_chunk_io.push_chunk(4, false, "scenario_mission_index", iob_scenario_mission_id);
    g_chunk_io.push_chunk(4, false, "file_version", iob_file_version);
    g_chunk_io.push_chunk(6004, false, "chunks_schema", iob_chunks_schema);

    g_chunk_io.push_chunk(207936, true, "image_grid", &io_image_grid::instance());        // (228�) * 4 <<
    g_chunk_io.push_chunk(51984, true, "edge_grid", iob_edge_grid);                       // (228�) * 1
    g_chunk_io.push_chunk(103968, true, "building_grid", iob_building_grid);              // (228�) * 2
    g_chunk_io.push_chunk(207936, true, "terrain_grid", iob_terrain_grid);                // (228�) * 4 <<
    g_chunk_io.push_chunk(51984, true, "aqueduct_grid", iob_aqueduct_grid);               // (228�) * 1
    g_chunk_io.push_chunk(103968, true, "figure_grid", iob_figure_grid);                  // (228�) * 2
    g_chunk_io.push_chunk(51984, true, "bitfields_grid", iob_bitfields_grid);             // (228�) * 1
    g_chunk_io.push_chunk(51984, true, "sprite_grid", iob_sprite_grid);                   // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "random_grid", iob_random_grid);                  // (228�) * 1
    g_chunk_io.push_chunk(51984, true, "desirability_grid", iob_desirability_grid);       // (228�) * 1
    g_chunk_io.push_chunk(51984, true, "elevation_grid", iob_elevation_grid);             // (228�) * 1
    g_chunk_io.push_chunk(103968, true, "building_damage_grid", iob_damage_grid);         // (228�) * 2 <<
    g_chunk_io.push_chunk(51984, true, "aqueduct_backup_grid", iob_aqueduct_backup_grid); // (228�) * 1
    g_chunk_io.push_chunk(51984, true, "sprite_backup_grid", iob_sprite_backup_grid);     // (228�) * 1
    g_chunk_io.push_chunk(776000, true, "figures", iob_figures);
    g_chunk_io.push_chunk(2000, true, "route_figures", iob_route_figures);
    g_chunk_io.push_chunk(500000, true, "route_paths", iob_route_paths);
    g_chunk_io.push_chunk(7200, true, "formations", iob_formations);
    g_chunk_io.push_chunk(12, false, "formations_info", iob_formations_info);
    g_chunk_io.push_chunk(37808, true, "city_data", iob_city_data);
    g_chunk_io.push_chunk(72, false, "city_data_extra", iob_city_data_extra);
    g_chunk_io.push_chunk(1056000, true, "buildings", iob_buildings);
    g_chunk_io.push_chunk(4, false, "city_view_orientation", iob_camera_view_orientation);             // ok
    g_chunk_io.push_chunk(20, false, "game_time", iob_game_time);                                    // ok
    g_chunk_io.push_chunk(8, false, "building_extra_highest_id_ever", iob_building_highest_id_ever); // ok
    g_chunk_io.push_chunk(8, false, "random_iv", iob_random_iv);                                     // ok
    g_chunk_io.push_chunk(8, false, "city_view_camera", iob_city_view_camera);                       // ok
    //                state->building_count_culture1 = create_savegame_piece(132, false, ""); // MISSING
    g_chunk_io.push_chunk(8, false, "city_graph_order", iob_city_graph_order); // I guess ????
    //                state->emperor_change_time = create_savegame_piece(8, false, ""); // MISSING
    g_chunk_io.push_chunk(12, false, "empire_map_params", iob_empire_map_params);              // ok ???
    // 106 bytes/city: classic 61�106=6466; v178+ 80�106=8480 (Cleopatra name ids 61+)
    g_chunk_io.push_chunk(file_version > 177 ? 8480 : 6466, true, "empire_cities", iob_empire_cities);
    g_chunk_io.push_chunk(288, false, "building_count_industry", iob_building_count_industry); // 288 bytes ??????
    g_chunk_io.push_chunk(288, false, "trade_prices", iob_trade_prices);
    g_chunk_io.push_chunk(84, false, "figure_names", iob_figure_names);

    //                state->culture_coverage = create_savegame_piece(60, false, ""); // MISSING
    g_chunk_io.push_chunk(1592, false, "scenario_info", iob_scenario_info);

    /////////////////////

    g_chunk_io.push_chunk(4, false, "max_year", iob_max_year);
    g_chunk_io.push_chunk(48000, true, "messages", iob_messages);          // 94000 + 533 --> 94532 + 4 = 94536
    g_chunk_io.push_chunk(182, false, "message_extra", iob_message_extra); // ok

    g_chunk_io.push_chunk(8, false, "building_burning_list_info", iob_building_burning_list_info); // ok
    g_chunk_io.push_chunk(4, false, "figure_sequence", iob_figure_sequence);                       // ok
    g_chunk_io.push_chunk(12, false, "scenario_carry_settings", iob_scenario_carry_settings);      // ok
    g_chunk_io.push_chunk(3232, true, "invasion_warnings", iob_invasion_warnings); // 94743 + 31 --> 94774 + 4 = 94778
    g_chunk_io.push_chunk(4, false, "scenario_is_custom", iob_scenario_is_custom); // ok
    g_chunk_io.push_chunk(8960, false, "city_sounds", iob_city_sounds);            // ok
    g_chunk_io.push_chunk(4, false, "building_extra_highest_id", iob_building_highest_id); // ok
    g_chunk_io.push_chunk(8804, false, "empire_traders", iob_empire_traders);              // +4000 ???

    g_chunk_io.push_chunk(1000, true, "building_list_burning", iob_building_list_burning); // ok
    g_chunk_io.push_chunk(1000, true, "building_list_small", iob_city_utilities_data);     // ok
    g_chunk_io.push_chunk(8000, true, "building_list_large", iob_building_list_large);     // ok

    //                state->tutorial_part1 = create_savegame_piece(32, false, "");
    //                state->building_count_military = create_savegame_piece(16, false, "");
    //                state->enemy_army_totals = create_savegame_piece(20, false, "");
    //                state->building_storages = create_savegame_piece(6400, false, "");
    //                state->building_count_culture2 = create_savegame_piece(32, false, "");
    //                state->building_count_support = create_savegame_piece(24, false, "");
    //                state->tutorial_part2 = create_savegame_piece(4, false, "");
    //                state->gladiator_revolt = create_savegame_piece(16, false, "");

    // 32 bytes     00 00 00 00 ??? 8 x int
    // 24 bytes     00 00 00 00 ??? 6 x int
    g_chunk_io.push_chunk(32, false, "junk7a", iob_junk7a);                          // unknown bytes
    g_chunk_io.push_chunk(24, false, "junk7b", iob_junk7b);                          // unknown bytes
    g_chunk_io.push_chunk(39200, false, "building_storages", iob_building_storages); // storage instructions

    g_chunk_io.push_chunk(2880, true, "trade_routes_limits", iob_trade_routes_limits); // ok
    g_chunk_io.push_chunk(2880, true, "trade_routes_traded", iob_trade_routes_traded); // ok

    //                state->building_barracks_tower_sentry = create_savegame_piece(4, false, "");
    //                state->building_extra_sequence = create_savegame_piece(4, false, "");
    //                state->routing_counters = create_savegame_piece(16, false, "");
    //                state->building_count_culture3 = create_savegame_piece(40, false, "");
    //                state->enemy_armies = create_savegame_piece(900, false, "");

    // 12 bytes     00 00 00 00 ??? 3 x int
    // 16 bytes     00 00 00 00 ??? 4 x int
    // 12 bytes     00 00 00 00 ??? 3 x int
    //  2 bytes     00 00       ??? 1 x short
    //  8 bytes     00 00 00 00 ??? 2 x int
    g_chunk_io.push_chunk(50, false, "junk8", iob_routing_stats); // unknown bytes

    //                state->last_invasion_id = create_savegame_piece(2, false, "");
    //                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

    g_chunk_io.push_chunk(65, false, "scenario_map_name", iob_scenario_map_name); // ok
    g_chunk_io.push_chunk(32, false, "bookmarks", iob_city_bookmarks);                 // ok

    // 12 bytes     00 00 00 00 ??? 3 x int
    // 396 bytes    00 00 00 00 ??? 99 x int
    g_chunk_io.push_chunk(12, false, "junk9a", iob_junk9a); // ok ????
    g_chunk_io.push_chunk(396, false, "junk9b", iob_junk9b);

    // 51984 bytes  00 00 00 00 ???
    g_chunk_io.push_chunk(51984, false, "soil_fertility_grid", iob_soil_fertility_grid);

    // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
    // 28 bytes     2F 01 00 00 ???
    g_chunk_io.push_chunk(18600, false, "scenario_events", iob_scenario_events);
    g_chunk_io.push_chunk(28, false, "scenario_events_extra", iob_scenario_events_extra);

    // 11000 bytes  00 00 00 00 ??? 50 x 224-byte chunk (50 x 220 for old version)
    // 2200 bytes   00 00 00 00 ??? 50 x 44-byte chunk
    // 16 bytes     00 00 00 00 ??? 4 x int
    // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
    g_chunk_io.push_chunk(file_version < 149 ? 11000 : 11200, false, "junk10a", iob_junk10a);
    g_chunk_io.push_chunk(2200, false, "junk10b", iob_junk10b);
    g_chunk_io.push_chunk(16, false, "junk10c", iob_junk10c);
    g_chunk_io.push_chunk(8200, false, "junk10d", iob_junk10d);

    // 1280 bytes   00 00 00 00 ??? 40 x 32-byte chunk
    g_chunk_io.push_chunk(1280, true, "junk11", iob_junk11); // unknown compressed data

    g_chunk_io.push_chunk(file_version < 160 ? 15200 : 19600, true, "empire_map_objects", iob_empire_map_objects);
    g_chunk_io.push_chunk(16200, true, "empire_map_routes", iob_empire_map_routes);

    // 51984 bytes  FF FF FF FF ???          // (228�) * 1 ?????????????????
    g_chunk_io.push_chunk(51984, false, "vegetation_growth", iob_vegetation_growth); // todo: 1-byte grid

    // 20 bytes     19 00 00 00 ???
    g_chunk_io.push_chunk(20, false, "junk14", iob_junk14);

    // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
    g_chunk_io.push_chunk(528, false, "bizarre_ordered_fields_1", iob_bizarre_ordered_fields_1);

    g_chunk_io.push_chunk(file_version < 147 ? 32 : 36,
                      true,
                      "floodplain_settings",
                      iob_floodplain_settings);                        // floodplain_settings
    g_chunk_io.push_chunk(207936, true, "GRID03_32BIT", iob_GRID03_32BIT); // todo: 4-byte grid

    // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
    g_chunk_io.push_chunk(312,
                      false,
                      "bizarre_ordered_fields_4",
                      iob_bizarre_ordered_fields_4); // 71x 4-bytes emptiness

    // 64 bytes     00 00 00 00 ???
    g_chunk_io.push_chunk(64, false, "junk16", iob_junk16);                        // 71x 4-bytes emptiness
    g_chunk_io.push_chunk(41, false, "tutorial_flags_struct", iob_tutorial_flags); // 41 x 1-byte flag fields
    g_chunk_io.push_chunk(51984, true, "GRID04_8BIT", iob_GRID04_8BIT);

    // lone byte ???
    g_chunk_io.push_chunk(1, false, "junk17", iob_junk17);
    g_chunk_io.push_chunk(51984, true, "moisture_grid", iob_moisture_grid);

    // 240 bytes    0F 00 00 00 ??? 10 x 24-byte chunk
    // 432 bytes    0F 00 00 00 ??? 18 x 24-byte chunk
    g_chunk_io.push_chunk(240, false, "bizarre_ordered_fields_2", iob_bizarre_ordered_fields_2);
    g_chunk_io.push_chunk(432, false, "bizarre_ordered_fields_3", iob_bizarre_ordered_fields_3);

    // 8 bytes      00 00 00 00 ??? 2 x int
    g_chunk_io.push_chunk(8, false, "junk18", iob_junk18);

    if (file_version >= 160) {
        // 12 bytes     00 00 00 00 ??? 3 x int
        g_chunk_io.push_chunk(20, false, "junk19", iob_junk19);

        // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
        // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
        // 360 bytes   00 00 00 00 ??? 15 x 24-byte chunk
        // 1344 bytes  00 00 00 00 ??? 56 x 24-byte chunk
        // 1800 bytes  00 00 00 00 ??? 75 x 24-byte chunk <--- I can't even... their own schema is wrong. it's >>
        // 74! <<
        g_chunk_io.push_chunk(648, false, "bizarre_ordered_fields_5", iob_bizarre_ordered_fields_5);
        g_chunk_io.push_chunk(648, false, "bizarre_ordered_fields_6", iob_bizarre_ordered_fields_6);
        g_chunk_io.push_chunk(360, false, "bizarre_ordered_fields_7", iob_bizarre_ordered_fields_7);
        g_chunk_io.push_chunk(1344, false, "bizarre_ordered_fields_8", iob_bizarre_ordered_fields_8);
        g_chunk_io.push_chunk(1776, false, "bizarre_ordered_fields_9", iob_bizarre_ordered_fields_9);
    }
}

// Tiny positional .sav stub used only to create Save/<player>/ when starting a dynasty.
// The chunk has no io_buffer — serialize writes a zeroed 4-byte piece.
void file_schema_family_marker(e_file_format, const int) {
    g_chunk_io.push_chunk(4, false, "family_index", nullptr);
}
