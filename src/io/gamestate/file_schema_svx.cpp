#include "file_schemas.h"

#include "building/building_storage.h"
#include "chunks.h"
#include "grid/image.h"
#include "io/chunk_serializer.h"

// Akhenaten .svx - sectioned container when g_chunk_io.is_sectioned(), else legacy
// positional layout (keeps dead file_version/chunks_schema slots for old files).
void file_schema_svx(const int file_version) {
    g_chunk_io.push_chunk(4, false, "scenario_mission_index", iob_scenario_mission_id);
    if (!g_chunk_io.is_sectioned()) {
        // Two dead chunks that only the positional layout needs. file_version is
        // read into a static nobody uses, and chunks_schema writes 6004 zero bytes
        // because chunks_in_used is never set. They must keep their slots for old
        // .svx files - dropping them would shift every following chunk by 6008
        // bytes - but the container carries the version in its header instead.
        g_chunk_io.push_chunk(4, false, "file_version", iob_file_version);
        g_chunk_io.push_chunk(6004, false, "chunks_schema", iob_chunks_schema);
    }
    g_chunk_io.push_chunk(51984 * 4, false, "image_grid", &io_image_grid::instance());        // (228�) * 4 <<
    g_chunk_io.push_chunk(51984, false, "edge_grid", iob_edge_grid);                       // (228�) * 1
    g_chunk_io.push_chunk(103968, false, "building_grid", iob_building_grid);              // (228�) * 2
    g_chunk_io.push_chunk(51984 * 4, false, "terrain_grid", iob_terrain_grid);                // (228�) * 4 <<
    g_chunk_io.push_chunk(51984, false, "aqueduct_grid", iob_aqueduct_grid);               // (228�) * 1
    g_chunk_io.push_chunk(103968, false, "figure_grid", iob_figure_grid);                  // (228�) * 2
    g_chunk_io.push_chunk(51984, false, "bitfields_grid", iob_bitfields_grid);             // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "sprite_grid", iob_sprite_grid);                   // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "random_grid", iob_random_grid);                   // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "desirability_grid", iob_desirability_grid);       // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "elevation_grid", iob_elevation_grid);             // (228�) * 1
    g_chunk_io.push_chunk(103968, false, "building_damage_grid", iob_damage_grid);         // (228�) * 2 <<
    g_chunk_io.push_chunk(51984, false, "aqueduct_backup_grid", iob_aqueduct_backup_grid); // (228�) * 1
    g_chunk_io.push_chunk(51984, false, "sprite_backup_grid", iob_sprite_backup_grid);     // (228�) * 1
    g_chunk_io.push_chunk(776000, false, "figures", iob_figures);
    g_chunk_io.push_chunk(2000, false, "route_figures", iob_route_figures);
    g_chunk_io.push_chunk(500000, false, "route_paths", iob_route_paths);
    g_chunk_io.push_chunk(7200, false, "formations", iob_formations);
    g_chunk_io.push_chunk(12, false, "formations_info", iob_formations_info);
    g_chunk_io.push_chunk(37808, false, "city_data", iob_city_data);
    g_chunk_io.push_chunk(72, false, "city_data_extra", iob_city_data_extra);
    g_chunk_io.push_chunk(1056000, false, "buildings", iob_buildings);
    g_chunk_io.push_chunk(4, false, "city_view_orientation", iob_camera_view_orientation);             // ok
    g_chunk_io.push_chunk(20, false, "game_time", iob_game_time);                                    // ok
    g_chunk_io.push_chunk(8, false, "building_extra_highest_id_ever", iob_building_highest_id_ever); // ok
    g_chunk_io.push_chunk(8, false, "random_iv", iob_random_iv);                                     // ok
    g_chunk_io.push_chunk(8, false, "city_view_camera", iob_city_view_camera);                       // ok
    g_chunk_io.push_chunk(8, false, "city_graph_order", iob_city_graph_order);                       // I guess ????
    g_chunk_io.push_chunk(12, false, "empire_map_params", iob_empire_map_params);                    // ok ???
    // 106 bytes/city: classic 61�106=6466; v178+ 80�106=8480 (Cleopatra name ids 61+)
    g_chunk_io.push_chunk(file_version > 177 ? 8480 : 6466, false, "empire_cities", iob_empire_cities);
    g_chunk_io.push_chunk(288, false, "building_count_industry", iob_building_count_industry); // 288 bytes ??????
    g_chunk_io.push_chunk(288, false, "trade_prices", iob_trade_prices);
    g_chunk_io.push_chunk(84, false, "figure_names", iob_figure_names);
    g_chunk_io.push_chunk(1592, false, "scenario_info", iob_scenario_info);
    g_chunk_io.push_chunk(4, false, "max_year", iob_max_year);
    g_chunk_io.push_chunk(48000, false, "messages", iob_messages);         // 94000 + 533 --> 94532 + 4 = 94536
    g_chunk_io.push_chunk(182, false, "message_extra", iob_message_extra); // ok
    g_chunk_io.push_chunk(8, false, "building_burning_list_info", iob_building_burning_list_info); // ok
    g_chunk_io.push_chunk(4, false, "figure_sequence", iob_figure_sequence);                       // ok
    g_chunk_io.push_chunk(12, false, "scenario_carry_settings", iob_scenario_carry_settings);      // ok
    g_chunk_io.push_chunk(3232, false, "invasion_warnings", iob_invasion_warnings); // 94743 + 31 --> 94774 + 4 = 94778
    g_chunk_io.push_chunk(4, false, "scenario_is_custom", iob_scenario_is_custom);  // ok
    g_chunk_io.push_chunk(8960, false, "city_sounds", iob_city_sounds);             // ok
    g_chunk_io.push_chunk(4, false, "building_extra_highest_id", iob_building_highest_id);  // ok
    g_chunk_io.push_chunk(8804, false, "empire_traders", iob_empire_traders);               // +4000 ???
    g_chunk_io.push_chunk(1000, false, "building_list_burning", iob_building_list_burning); // ok
    g_chunk_io.push_chunk(1000, false, "building_list_small", iob_city_utilities_data);     // ok
    g_chunk_io.push_chunk(8000, false, "building_list_large", iob_building_list_large);     // ok
    g_chunk_io.push_chunk(32, false, "junk7a", iob_junk7a);                                 // unknown bytes
    g_chunk_io.push_chunk(24, false, "junk7b", iob_junk7b);                                 // unknown bytes
    g_chunk_io.push_chunk(39200, false, "building_storages", iob_building_storages);        // storage instructions
    g_chunk_io.push_chunk(2880, false, "trade_routes_limits", iob_trade_routes_limits);     // ok
    g_chunk_io.push_chunk(2880, false, "trade_routes_traded", iob_trade_routes_traded);     // ok
    g_chunk_io.push_chunk(50, false, "junk8", iob_routing_stats);                           // unknown bytes
    g_chunk_io.push_chunk(65, false, "scenario_map_name", iob_scenario_map_name);           // ok
    g_chunk_io.push_chunk(32, false, "bookmarks", iob_city_bookmarks);                           // ok
    g_chunk_io.push_chunk(12, false, "junk9a", iob_junk9a);                                 // ok ????
    g_chunk_io.push_chunk(396, false, "junk9b", iob_junk9b);
    g_chunk_io.push_chunk(51984, false, "soil_fertility_grid", iob_soil_fertility_grid);
    g_chunk_io.push_chunk(18600, false, "scenario_events", iob_scenario_events);
    g_chunk_io.push_chunk(28, false, "scenario_events_extra", iob_scenario_events_extra);
    g_chunk_io.push_chunk(11200, false, "junk10a", iob_junk10a);
    g_chunk_io.push_chunk(2200, false, "junk10b", iob_junk10b);
    g_chunk_io.push_chunk(16, false, "junk10c", iob_junk10c);
    g_chunk_io.push_chunk(8200, false, "junk10d", iob_junk10d);
    g_chunk_io.push_chunk(1280, false, "junk11", iob_junk11); // unknown compressed data
    g_chunk_io.push_chunk(19600, true, "empire_map_objects", iob_empire_map_objects);
    g_chunk_io.push_chunk(16200, false, "empire_map_routes", iob_empire_map_routes);
    g_chunk_io.push_chunk(51984, false, "vegetation_growth", iob_vegetation_growth); // todo: 1-byte grid
    g_chunk_io.push_chunk(20, false, "junk14", iob_junk14);
    g_chunk_io.push_chunk(528, false, "bizarre_ordered_fields_1", iob_bizarre_ordered_fields_1);
    g_chunk_io.push_chunk(36, false, "floodplain_settings", iob_floodplain_settings); // floodplain_settings
    g_chunk_io.push_chunk(51984 * 4, false, "GRID03_32BIT", iob_GRID03_32BIT);           // todo: 4-byte grid
    g_chunk_io.push_chunk(312, false, "bizarre_ordered_fields_4", iob_bizarre_ordered_fields_4);                           // 71x 4-bytes emptiness
    g_chunk_io.push_chunk(64, false, "junk16", iob_junk16);                        // 71x 4-bytes emptiness
    g_chunk_io.push_chunk(41, false, "tutorial_flags_struct", iob_tutorial_flags); // 41 x 1-byte flag fields
    g_chunk_io.push_chunk(51984, false, "GRID04_8BIT", iob_GRID04_8BIT);
    g_chunk_io.push_chunk(1, false, "junk17", iob_junk17);
    g_chunk_io.push_chunk(51984, false, "moisture_grid", iob_moisture_grid);
    g_chunk_io.push_chunk(240, false, "bizarre_ordered_fields_2", iob_bizarre_ordered_fields_2);
    g_chunk_io.push_chunk(432, false, "bizarre_ordered_fields_3", iob_bizarre_ordered_fields_3);
    g_chunk_io.push_chunk(8, false, "junk18", iob_junk18);
    g_chunk_io.push_chunk(20, false, "junk19", iob_junk19);
    g_chunk_io.push_chunk(648, false, "bizarre_ordered_fields_5", iob_bizarre_ordered_fields_5);
    g_chunk_io.push_chunk(648, false, "bizarre_ordered_fields_6", iob_bizarre_ordered_fields_6);
    g_chunk_io.push_chunk(360, false, "bizarre_ordered_fields_7", iob_bizarre_ordered_fields_7);
    g_chunk_io.push_chunk(1344, false, "bizarre_ordered_fields_8", iob_bizarre_ordered_fields_8);
    g_chunk_io.push_chunk(1776, false, "bizarre_ordered_fields_9", iob_bizarre_ordered_fields_9);
    g_chunk_io.push_chunk(51984, false, "terrain_floodplain_growth", iob_terrain_floodplain_growth);
    g_chunk_io.push_chunk(51984 * 4, false, "monuments_progress", iob_monuments_progress_grid); // (228�) * 4
    if (file_version > 167) {
        g_chunk_io.push_chunk(51984, false, "rubble_type_grid", iob_rubble_type_grid); //  (228�) * 1
        g_chunk_io.push_chunk(103968, false, "sandstone_grid", iob_sandstone);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "stone_grid", iob_stone);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "limestone_grid", iob_limestone);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "granite_grid", iob_granite);              // (228�) * 2
    }
    if (file_version > 168) {
        g_chunk_io.push_chunk(103968, false, "golden_grid", iob_golden);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "clay_grid", iob_clay);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "copper_grid", iob_copper);              // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "gems_grid", iob_gems);              // (228�) * 2
        g_chunk_io.push_chunk(51984, false, "irrigation_value_grid", iob_irrigation_value_grid); // (228�) * 1
    }
    if (file_version > 169) {
        g_chunk_io.push_chunk(16384, false, "iob_enemy_armies_stats", iob_enemy_armies_stats); // actual 15360 + 256 bytes
    }
    if (file_version > 170) {
        g_chunk_io.push_chunk(103968, false, "bridge_part_grid", iob_bridge_part_grid); // (228�) * 2
        g_chunk_io.push_chunk(103968, false, "bridge_type_grid", iob_bridge_type_grid); // (228�) * 2
    }
    if (file_version > 171) {
        // v172 stub � keep schema position for old saves
        g_chunk_io.push_chunk(272, false, "invasion_event_pending", iob_invasion_event_pending);
    }
    if (file_version > 172) {
        // 8 + 16*12 + 64*20 = 1480
        g_chunk_io.push_chunk(1480, false, "invasion_runtime", iob_invasion_runtime);
    }
    if (file_version > 174) {
        // 25 chars: a section name must fit svx::NAME_LEN (32)
        g_chunk_io.push_chunk(BUILDING_STORAGE_EMPTY_ALL_BACKUP_CHUNK_SIZE, false,
                          "storages_empty_all_backup",
                          iob_building_storages_empty_all_backup);
    }
    if (file_version > 175) {
        g_chunk_io.push_chunk(51984, false, "wall_material_grid", iob_wall_material_grid); // (228�) * 1
    }
    if (file_version > 176) {
        // count+head+8 order + 8*(bool+u16+u8+i16+bool+pad) + pad = 80
        g_chunk_io.push_chunk(80, false, "invasion_auto_resolve", iob_invasion_auto_resolve);
    }
    if (file_version > 182) {
        // 3 troop slots � 8 + notice + pad = 32
        g_chunk_io.push_chunk(32, false, "campaign_carry_troops", iob_campaign_carry_troops);
    }
    if (file_version > 183) {
        // 8 monument slots � 12 = 96
        g_chunk_io.push_chunk(96, false, "campaign_carry_monuments", iob_campaign_carry_monuments);
    }
    if (file_version > 185) {
        // STORAGE labor category priority (workers_* recomputed each tick)
        g_chunk_io.push_chunk(4, false, "labor_storage_priority", iob_labor_storage_priority);
    }
    if (file_version > 186) {
        // local cults + festival calendar theme state (Enhanced PC2)
        g_chunk_io.push_chunk(64, false, "enhanced_religion", iob_enhanced_religion);
    }
    if (file_version > 187) {
        // recorded trails pool + per-building last-4 rings
        // slot: used+len+tiles[254]+figure_type+reserved = 515 (same as old used+len+tiles[256])
        // 512*515 + 4000*4*2 = 263680 + 32000 = 295680
        g_chunk_io.push_chunk(295680, true, "recorded_paths", iob_recorded_paths);
    }
    if (file_version > 197) {
        // count + reserved + 32 * (id[48] + version[16]) = 2052
        g_chunk_io.push_chunk(2052, false, "mods", iob_mods);
    }
    // Sectioned saves before 200 lack it and get the defaulter; the positional layout must not grow.
    if (file_version > 199 || g_chunk_io.is_sectioned()) {
        // count + 16 x (int32 x, int32 y) = 132
        g_chunk_io.push_chunk(132, false, "clouds", iob_clouds);
    }
}
