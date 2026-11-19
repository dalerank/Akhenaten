#include "file_schemas.h"

#include "io/chunk_serializer.h"
#include "building/building_chunks.h"
#include "building/building_burning_ruin_chunks.h"
#include "building/building_storage_chunks.h"
#include "city/buildings_chunks.h"
#include "city/city_chunks.h"
#include "city/city_buildings_chunks.h"
#include "city/city_figures_chunks.h"
#include "city/city_floods_chunks.h"
#include "city/city_message_chunks.h"
#include "core/random_chunks.h"
#include "empire/empire_chunks.h"
#include "empire/empire_map_chunks.h"
#include "empire/empire_object_chunks.h"
#include "empire/trade_prices_chunks.h"
#include "empire/trade_route_chunks.h"
#include "empire/trader_handler_chunks.h"
#include "figure/figure_names_chunks.h"
#include "figure/formation_chunks.h"
#include "figure/route_chunks.h"
#include "game/simulation_time_chunks.h"
#include "game/tutorial_chunks.h"
#include "io/gamestate/presentation_chunks.h"
#include "grid/building_chunks.h"
#include "grid/canals_chunks.h"
#include "grid/desirability_chunks.h"
#include "grid/elevation_chunks.h"
#include "grid/figure_chunks.h"
#include "grid/floodplain_chunks.h"
#include "grid/image_chunks.h"
#include "grid/moisture_chunks.h"
#include "grid/property_chunks.h"
#include "grid/random_chunks.h"
#include "grid/routing/routing_chunks.h"
#include "grid/sprite_chunks.h"
#include "grid/terrain_chunks.h"
#include "grid/vegetation_chunks.h"
#include "io/gamestate/chunks.h"
#include "scenario/criteria_chunks.h"
#include "scenario/scenario_chunks.h"
#include "scenario/scenario_event_manager_chunks.h"
#include "scenario/scenario_invasion_chunks.h"

// Classic Pharaoh .sav — positional, compressed chunks.
void file_schema_sav(const int file_version) {
    g_chunk_io.push_chunk<scenario_mission_index_chunk>(4, false);
    g_chunk_io.push_chunk<file_version_chunk>(4, false);
    g_chunk_io.push_chunk<chunks_schema_chunk>(6004, false);

    g_chunk_io.push_chunk<image_grid_chunk>(207936, true);           // (228�) * 4 <<
    g_chunk_io.push_chunk<edge_grid_chunk>(51984, true);             // (228�) * 1
    g_chunk_io.push_chunk<building_grid_chunk>(103968, true);        // (228�) * 2
    g_chunk_io.push_chunk<terrain_grid_chunk>(207936, true);         // (228�) * 4 <<
    g_chunk_io.push_chunk<aqueduct_grid_chunk>(51984, true);         // (228�) * 1
    g_chunk_io.push_chunk<figure_grid_chunk>(103968, true);          // (228�) * 2
    g_chunk_io.push_chunk<bitfields_grid_chunk>(51984, true);        // (228�) * 1
    g_chunk_io.push_chunk<sprite_grid_chunk>(51984, true);           // (228�) * 1
    g_chunk_io.push_chunk<random_grid_chunk>(51984, false);          // (228�) * 1
    g_chunk_io.push_chunk<desirability_grid_chunk>(51984, true);     // (228�) * 1
    g_chunk_io.push_chunk<elevation_grid_chunk>(51984, true);        // (228�) * 1
    g_chunk_io.push_chunk<building_damage_grid_chunk>(103968, true); // (228�) * 2 <<
    g_chunk_io.push_chunk<aqueduct_backup_grid_chunk>(51984, true);  // (228�) * 1
    g_chunk_io.push_chunk<sprite_backup_grid_chunk>(51984, true);    // (228�) * 1
    g_chunk_io.push_chunk<figures_chunk>(776000, true);
    g_chunk_io.push_chunk<route_figures_chunk>(2000, true);
    g_chunk_io.push_chunk<route_paths_chunk>(500000, true);
    g_chunk_io.push_chunk<formations_chunk>(7200, true);
    g_chunk_io.push_chunk<formations_info_chunk>(12, false);
    g_chunk_io.push_chunk<city_data_chunk>(37808, true);
    g_chunk_io.push_chunk<city_data_extra_chunk>(72, false);
    g_chunk_io.push_chunk<buildings_chunk>(1056000, true);
    g_chunk_io.push_chunk<city_view_orientation_chunk>(4, false);          // ok
    g_chunk_io.push_chunk<game_time_chunk>(20, false);                     // ok
    g_chunk_io.push_chunk<building_extra_highest_id_ever_chunk>(8, false); // ok
    g_chunk_io.push_chunk<random_iv_chunk>(8, false);                      // ok
    g_chunk_io.push_chunk<city_view_camera_chunk>(8, false);               // ok
    //                state->building_count_culture1 = create_savegame_piece(132, false, ""); // MISSING
    g_chunk_io.push_chunk<city_graph_order_chunk>(8, false); // I guess ????
    //                state->emperor_change_time = create_savegame_piece(8, false, ""); // MISSING
    g_chunk_io.push_chunk<empire_map_params_chunk>(12, false); // ok ???
    // 106 bytes/city: classic 61�106=6466; v178+ 80�106=8480 (Cleopatra name ids 61+)
    g_chunk_io.push_chunk<empire_cities_chunk>(file_version > 177 ? 8480 : 6466, true);
    g_chunk_io.push_chunk<building_count_industry_chunk>(288, false); // 288 bytes ??????
    g_chunk_io.push_chunk<trade_prices_chunk>(288, false);
    g_chunk_io.push_chunk<figure_names_chunk>(84, false);

    //                state->culture_coverage = create_savegame_piece(60, false, ""); // MISSING
    g_chunk_io.push_chunk<scenario_info_chunk>(1592, false);

    /////////////////////

    g_chunk_io.push_chunk<max_year_chunk>(4, false);
    g_chunk_io.push_chunk<messages_chunk>(48000, true);     // 94000 + 533 --> 94532 + 4 = 94536
    g_chunk_io.push_chunk<message_extra_chunk>(182, false); // ok

    g_chunk_io.push_chunk<building_burning_list_info_chunk>(8, false); // ok
    g_chunk_io.push_chunk<figure_sequence_chunk>(4, false);            // ok
    g_chunk_io.push_chunk<scenario_carry_settings_chunk>(12, false);   // ok
    g_chunk_io.push_chunk<invasion_warnings_chunk>(3232, true);        // 94743 + 31 --> 94774 + 4 = 94778
    g_chunk_io.push_chunk<scenario_is_custom_chunk>(4, false);         // ok
    g_chunk_io.push_chunk<city_sounds_chunk>(8960, false);             // ok
    g_chunk_io.push_chunk<building_extra_highest_id_chunk>(4, false);  // ok
    g_chunk_io.push_chunk<empire_traders_chunk>(8804, false);          // +4000 ???

    g_chunk_io.push_chunk<building_list_burning_chunk>(1000, true); // ok
    g_chunk_io.push_chunk<building_list_small_chunk>(1000, true);   // ok
    g_chunk_io.push_chunk<building_list_large_chunk>(8000, true);   // ok

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
    g_chunk_io.push_chunk<junk7a_chunk>(32, false);               // unknown bytes
    g_chunk_io.push_chunk<junk7b_chunk>(24, false);               // unknown bytes
    g_chunk_io.push_chunk<building_storages_chunk>(39200, false); // storage instructions

    g_chunk_io.push_chunk<trade_routes_limits_chunk>(2880, true); // ok
    g_chunk_io.push_chunk<trade_routes_traded_chunk>(2880, true); // ok

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
    g_chunk_io.push_chunk<junk8_chunk>(50, false); // unknown bytes

    //                state->last_invasion_id = create_savegame_piece(2, false, "");
    //                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

    g_chunk_io.push_chunk<scenario_map_name_chunk>(65, false); // ok
    g_chunk_io.push_chunk<bookmarks_chunk>(32, false);         // ok

    // 12 bytes     00 00 00 00 ??? 3 x int
    // 396 bytes    00 00 00 00 ??? 99 x int
    g_chunk_io.push_chunk<junk9a_chunk>(12, false); // ok ????
    g_chunk_io.push_chunk<junk9b_chunk>(396, false);

    // 51984 bytes  00 00 00 00 ???
    g_chunk_io.push_chunk<soil_fertility_grid_chunk>(51984, false);

    // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
    // 28 bytes     2F 01 00 00 ???
    g_chunk_io.push_chunk<scenario_events_chunk>(18600, false);
    g_chunk_io.push_chunk<scenario_events_extra_chunk>(28, false);

    // 11000 bytes  00 00 00 00 ??? 50 x 224-byte chunk (50 x 220 for old version)
    // 2200 bytes   00 00 00 00 ??? 50 x 44-byte chunk
    // 16 bytes     00 00 00 00 ??? 4 x int
    // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
    g_chunk_io.push_chunk<junk10a_chunk>(file_version < 149 ? 11000 : 11200, false);
    g_chunk_io.push_chunk<junk10b_chunk>(2200, false);
    g_chunk_io.push_chunk<junk10c_chunk>(16, false);
    g_chunk_io.push_chunk<junk10d_chunk>(8200, false);

    // 1280 bytes   00 00 00 00 ??? 40 x 32-byte chunk
    g_chunk_io.push_chunk<junk11_chunk>(1280, true); // unknown compressed data

    g_chunk_io.push_chunk<empire_map_objects_chunk>(file_version < 160 ? 15200 : 19600, true);
    g_chunk_io.push_chunk<empire_map_routes_chunk>(16200, true);

    // 51984 bytes  FF FF FF FF ???          // (228�) * 1 ?????????????????
    g_chunk_io.push_chunk<vegetation_growth_chunk>(51984, false); // todo: 1-byte grid

    // 20 bytes     19 00 00 00 ???
    g_chunk_io.push_chunk<junk14_chunk>(20, false);

    // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
    g_chunk_io.push_chunk<bizarre_ordered_fields_1_chunk>(528, false);

    g_chunk_io.push_chunk<floodplain_settings_chunk>(file_version < 147 ? 32 : 36, true); // floodplain_settings
    g_chunk_io.push_chunk<GRID03_32BIT_chunk>(207936, true);                              // todo: 4-byte grid

    // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
    g_chunk_io.push_chunk<bizarre_ordered_fields_4_chunk>(312, false); // 71x 4-bytes emptiness

    // 64 bytes     00 00 00 00 ???
    g_chunk_io.push_chunk<junk16_chunk>(64, false);                // 71x 4-bytes emptiness
    g_chunk_io.push_chunk<tutorial_flags_struct_chunk>(41, false); // 41 x 1-byte flag fields
    g_chunk_io.push_chunk<GRID04_8BIT_chunk>(51984, true);

    // lone byte ???
    g_chunk_io.push_chunk<junk17_chunk>(1, false);
    g_chunk_io.push_chunk<moisture_grid_chunk>(51984, true);

    // 240 bytes    0F 00 00 00 ??? 10 x 24-byte chunk
    // 432 bytes    0F 00 00 00 ??? 18 x 24-byte chunk
    g_chunk_io.push_chunk<bizarre_ordered_fields_2_chunk>(240, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_3_chunk>(432, false);

    // 8 bytes      00 00 00 00 ??? 2 x int
    g_chunk_io.push_chunk<junk18_chunk>(8, false);

    if (file_version >= 160) {
        // 12 bytes     00 00 00 00 ??? 3 x int
        g_chunk_io.push_chunk<junk19_chunk>(20, false);

        // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
        // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
        // 360 bytes   00 00 00 00 ??? 15 x 24-byte chunk
        // 1344 bytes  00 00 00 00 ??? 56 x 24-byte chunk
        // 1800 bytes  00 00 00 00 ??? 75 x 24-byte chunk <--- I can't even... their own schema is wrong. it's >>
        // 74! <<
        g_chunk_io.push_chunk<bizarre_ordered_fields_5_chunk>(648, false);
        g_chunk_io.push_chunk<bizarre_ordered_fields_6_chunk>(648, false);
        g_chunk_io.push_chunk<bizarre_ordered_fields_7_chunk>(360, false);
        g_chunk_io.push_chunk<bizarre_ordered_fields_8_chunk>(1344, false);
        g_chunk_io.push_chunk<bizarre_ordered_fields_9_chunk>(1776, false);
    }
}

// Tiny positional .sav stub used only to create Save/<player>/ when starting a dynasty.
// The chunk has no io_buffer — serialize writes a zeroed 4-byte piece.
void file_schema_family_marker(e_file_format, const int) {
    g_chunk_io.push_chunk(4, false, "family_index", nullptr);
}
