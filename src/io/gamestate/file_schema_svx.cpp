#include "file_schemas.h"

#include "building/building_storage.h"
#include "io/chunk_serializer.h"
#include "building/building_chunks.h"
#include "building/building_burning_ruin_chunks.h"
#include "building/building_storage_chunks.h"
#include "building/monuments_chunks.h"
#include "city/buildings_chunks.h"
#include "city/campaign_carry_chunks.h"
#include "city/city_chunks.h"
#include "city/city_buildings_chunks.h"
#include "city/city_figures_chunks.h"
#include "city/city_floods_chunks.h"
#include "city/city_message_chunks.h"
#include "city/city_recorded_paths_chunks.h"
#include "io/gamestate/presentation_chunks.h"
#include "core/random_chunks.h"
#include "empire/empire_chunks.h"
#include "empire/empire_map_chunks.h"
#include "empire/empire_object_chunks.h"
#include "empire/trade_prices_chunks.h"
#include "empire/trade_route_chunks.h"
#include "empire/trader_handler_chunks.h"
#include "figure/enemy_army_chunks.h"
#include "figure/figure_names_chunks.h"
#include "figure/formation_chunks.h"
#include "figure/route_chunks.h"
#include "game/simulation_time_chunks.h"
#include "game/tutorial_chunks.h"
#include "grid/bridge_grid_chunks.h"
#include "grid/building_chunks.h"
#include "grid/canals_chunks.h"
#include "grid/clay_chunks.h"
#include "grid/copper_chunks.h"
#include "grid/desirability_chunks.h"
#include "grid/elevation_chunks.h"
#include "grid/figure_chunks.h"
#include "grid/floodplain_chunks.h"
#include "grid/gems_chunks.h"
#include "grid/golden_chunks.h"
#include "grid/granite_chunks.h"
#include "grid/image_chunks.h"
#include "grid/irrigation_value_chunks.h"
#include "grid/limestone_chunks.h"
#include "grid/moisture_chunks.h"
#include "grid/property_chunks.h"
#include "grid/random_chunks.h"
#include "grid/routing/routing_chunks.h"
#include "grid/sandstone_chunks.h"
#include "grid/sprite_chunks.h"
#include "grid/stone_chunks.h"
#include "grid/terrain_chunks.h"
#include "grid/vegetation_chunks.h"
#include "grid/wall_material_chunks.h"
#include "io/gamestate/chunks.h"
#include "scenario/criteria_chunks.h"
#include "scenario/invasion_auto_resolve_chunks.h"
#include "scenario/scenario_chunks.h"
#include "scenario/scenario_event_manager_chunks.h"
#include "scenario/scenario_invasion_chunks.h"

// Akhenaten .svx - sectioned container when g_chunk_io.is_sectioned(), else legacy
// positional layout (keeps dead file_version/chunks_schema slots for old files).
void file_schema_svx(const int file_version) {
    g_chunk_io.push_chunk<scenario_mission_index_chunk>(4, false);
    if (!g_chunk_io.is_sectioned()) {
        // Two dead chunks that only the positional layout needs. file_version is
        // read into a static nobody uses, and chunks_schema writes 6004 zero bytes
        // because chunks_in_used is never set. They must keep their slots for old
        // .svx files - dropping them would shift every following chunk by 6008
        // bytes - but the container carries the version in its header instead.
        g_chunk_io.push_chunk<file_version_chunk>(4, false);
        g_chunk_io.push_chunk<chunks_schema_chunk>(6004, false);
    }
    g_chunk_io.push_chunk<image_grid_chunk>(51984 * 4, false);        // (228�) * 4 <<
    g_chunk_io.push_chunk<edge_grid_chunk>(51984, false);             // (228�) * 1
    g_chunk_io.push_chunk<building_grid_chunk>(103968, false);        // (228�) * 2
    g_chunk_io.push_chunk<terrain_grid_chunk>(51984 * 4, false);      // (228�) * 4 <<
    g_chunk_io.push_chunk<aqueduct_grid_chunk>(51984, false);         // (228�) * 1
    g_chunk_io.push_chunk<figure_grid_chunk>(103968, false);          // (228�) * 2
    g_chunk_io.push_chunk<bitfields_grid_chunk>(51984, false);        // (228�) * 1
    g_chunk_io.push_chunk<sprite_grid_chunk>(51984, false);           // (228�) * 1
    g_chunk_io.push_chunk<random_grid_chunk>(51984, false);           // (228�) * 1
    g_chunk_io.push_chunk<desirability_grid_chunk>(51984, false);     // (228�) * 1
    g_chunk_io.push_chunk<elevation_grid_chunk>(51984, false);        // (228�) * 1
    g_chunk_io.push_chunk<building_damage_grid_chunk>(103968, false); // (228�) * 2 <<
    g_chunk_io.push_chunk<aqueduct_backup_grid_chunk>(51984, false);  // (228�) * 1
    g_chunk_io.push_chunk<sprite_backup_grid_chunk>(51984, false);    // (228�) * 1
    g_chunk_io.push_chunk<figures_chunk>(776000, false);
    g_chunk_io.push_chunk<route_figures_chunk>(2000, false);
    g_chunk_io.push_chunk<route_paths_chunk>(500000, false);
    g_chunk_io.push_chunk<formations_chunk>(7200, false);
    g_chunk_io.push_chunk<formations_info_chunk>(12, false);
    g_chunk_io.push_chunk<city_data_chunk>(37808, false);
    g_chunk_io.push_chunk<city_data_extra_chunk>(72, false);
    g_chunk_io.push_chunk<buildings_chunk>(1056000, false);
    g_chunk_io.push_chunk<city_view_orientation_chunk>(4, false);          // ok
    g_chunk_io.push_chunk<game_time_chunk>(20, false);                     // ok
    g_chunk_io.push_chunk<building_extra_highest_id_ever_chunk>(8, false); // ok
    g_chunk_io.push_chunk<random_iv_chunk>(8, false);                      // ok
    g_chunk_io.push_chunk<city_view_camera_chunk>(8, false);               // ok
    g_chunk_io.push_chunk<city_graph_order_chunk>(8, false);               // I guess ????
    g_chunk_io.push_chunk<empire_map_params_chunk>(12, false);             // ok ???
    // 106 bytes/city: classic 61�106=6466; v178+ 80�106=8480 (Cleopatra name ids 61+)
    g_chunk_io.push_chunk<empire_cities_chunk>(file_version > 177 ? 8480 : 6466, false);
    g_chunk_io.push_chunk<building_count_industry_chunk>(288, false); // 288 bytes ??????
    g_chunk_io.push_chunk<trade_prices_chunk>(288, false);
    g_chunk_io.push_chunk<figure_names_chunk>(84, false);
    g_chunk_io.push_chunk<scenario_info_chunk>(1592, false);
    g_chunk_io.push_chunk<max_year_chunk>(4, false);
    g_chunk_io.push_chunk<messages_chunk>(48000, false);               // 94000 + 533 --> 94532 + 4 = 94536
    g_chunk_io.push_chunk<message_extra_chunk>(182, false);            // ok
    g_chunk_io.push_chunk<building_burning_list_info_chunk>(8, false); // ok
    g_chunk_io.push_chunk<figure_sequence_chunk>(4, false);            // ok
    g_chunk_io.push_chunk<scenario_carry_settings_chunk>(12, false);   // ok
    g_chunk_io.push_chunk<invasion_warnings_chunk>(3232, false);       // 94743 + 31 --> 94774 + 4 = 94778
    g_chunk_io.push_chunk<scenario_is_custom_chunk>(4, false);         // ok
    g_chunk_io.push_chunk<city_sounds_chunk>(8960, false);             // ok
    g_chunk_io.push_chunk<building_extra_highest_id_chunk>(4, false);  // ok
    g_chunk_io.push_chunk<empire_traders_chunk>(8804, false);          // +4000 ???
    g_chunk_io.push_chunk<building_list_burning_chunk>(1000, false);   // ok
    g_chunk_io.push_chunk<building_list_small_chunk>(1000, false);     // ok
    g_chunk_io.push_chunk<building_list_large_chunk>(8000, false);     // ok
    g_chunk_io.push_chunk<junk7a_chunk>(32, false);                    // unknown bytes
    g_chunk_io.push_chunk<junk7b_chunk>(24, false);                    // unknown bytes
    g_chunk_io.push_chunk<building_storages_chunk>(39200, false);      // storage instructions
    g_chunk_io.push_chunk<trade_routes_limits_chunk>(2880, false);     // ok
    g_chunk_io.push_chunk<trade_routes_traded_chunk>(2880, false);     // ok
    g_chunk_io.push_chunk<junk8_chunk>(50, false);                     // unknown bytes
    g_chunk_io.push_chunk<scenario_map_name_chunk>(65, false);         // ok
    g_chunk_io.push_chunk<bookmarks_chunk>(32, false);                 // ok
    g_chunk_io.push_chunk<junk9a_chunk>(12, false);                    // ok ????
    g_chunk_io.push_chunk<junk9b_chunk>(396, false);
    g_chunk_io.push_chunk<soil_fertility_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<scenario_events_chunk>(18600, false);
    g_chunk_io.push_chunk<scenario_events_extra_chunk>(28, false);
    g_chunk_io.push_chunk<junk10a_chunk>(11200, false);
    g_chunk_io.push_chunk<junk10b_chunk>(2200, false);
    g_chunk_io.push_chunk<junk10c_chunk>(16, false);
    g_chunk_io.push_chunk<junk10d_chunk>(8200, false);
    g_chunk_io.push_chunk<junk11_chunk>(1280, false); // unknown compressed data
    g_chunk_io.push_chunk<empire_map_objects_chunk>(19600, true);
    g_chunk_io.push_chunk<empire_map_routes_chunk>(16200, false);
    g_chunk_io.push_chunk<vegetation_growth_chunk>(51984, false); // todo: 1-byte grid
    g_chunk_io.push_chunk<junk14_chunk>(20, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_1_chunk>(528, false);
    g_chunk_io.push_chunk<floodplain_settings_chunk>(36, false);       // floodplain_settings
    g_chunk_io.push_chunk<GRID03_32BIT_chunk>(51984 * 4, false);       // todo: 4-byte grid
    g_chunk_io.push_chunk<bizarre_ordered_fields_4_chunk>(312, false); // 71x 4-bytes emptiness
    g_chunk_io.push_chunk<junk16_chunk>(64, false);                    // 71x 4-bytes emptiness
    g_chunk_io.push_chunk<tutorial_flags_struct_chunk>(41, false);     // 41 x 1-byte flag fields
    g_chunk_io.push_chunk<GRID04_8BIT_chunk>(51984, false);
    g_chunk_io.push_chunk<junk17_chunk>(1, false);
    g_chunk_io.push_chunk<moisture_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_2_chunk>(240, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_3_chunk>(432, false);
    g_chunk_io.push_chunk<junk18_chunk>(8, false);
    g_chunk_io.push_chunk<junk19_chunk>(20, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_5_chunk>(648, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_6_chunk>(648, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_7_chunk>(360, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_8_chunk>(1344, false);
    g_chunk_io.push_chunk<bizarre_ordered_fields_9_chunk>(1776, false);
    g_chunk_io.push_chunk<terrain_floodplain_growth_chunk>(51984, false);
    g_chunk_io.push_chunk<monuments_progress_chunk>(51984 * 4, false); // (228�) * 4
    if (file_version > 167) {
        g_chunk_io.push_chunk<rubble_type_grid_chunk>(51984, false); //  (228�) * 1
        g_chunk_io.push_chunk<sandstone_grid_chunk>(103968, false);  // (228�) * 2
        g_chunk_io.push_chunk<stone_grid_chunk>(103968, false);      // (228�) * 2
        g_chunk_io.push_chunk<limestone_grid_chunk>(103968, false);  // (228�) * 2
        g_chunk_io.push_chunk<granite_grid_chunk>(103968, false);    // (228�) * 2
    }
    if (file_version > 168) {
        g_chunk_io.push_chunk<golden_grid_chunk>(103968, false);          // (228�) * 2
        g_chunk_io.push_chunk<clay_grid_chunk>(103968, false);            // (228�) * 2
        g_chunk_io.push_chunk<copper_grid_chunk>(103968, false);          // (228�) * 2
        g_chunk_io.push_chunk<gems_grid_chunk>(103968, false);            // (228�) * 2
        g_chunk_io.push_chunk<irrigation_value_grid_chunk>(51984, false); // (228�) * 1
    }
    if (file_version > 169) {
        g_chunk_io.push_chunk<iob_enemy_armies_stats_chunk>(16384, false); // actual 15360 + 256 bytes
    }
    if (file_version > 170) {
        g_chunk_io.push_chunk<bridge_part_grid_chunk>(103968, false); // (228�) * 2
        g_chunk_io.push_chunk<bridge_type_grid_chunk>(103968, false); // (228�) * 2
    }
    if (file_version > 171) {
        // v172 stub � keep schema position for old saves
        g_chunk_io.push_chunk<invasion_event_pending_chunk>(272, false);
    }
    if (file_version > 172) {
        // 8 + 16*12 + 64*20 = 1480
        g_chunk_io.push_chunk<invasion_runtime_chunk>(1480, false);
    }
    if (file_version > 174) {
        // 25 chars: a section name must fit svx::NAME_LEN (32)
        g_chunk_io.push_chunk<storages_empty_all_backup_chunk>(BUILDING_STORAGE_EMPTY_ALL_BACKUP_CHUNK_SIZE, false);
    }
    if (file_version > 175) {
        g_chunk_io.push_chunk<wall_material_grid_chunk>(51984, false); // (228�) * 1
    }
    if (file_version > 176) {
        // count+head+8 order + 8*(bool+u16+u8+i16+bool+pad) + pad = 80
        g_chunk_io.push_chunk<invasion_auto_resolve_chunk>(80, false);
    }
    if (file_version > 182) {
        // 3 troop slots � 8 + notice + pad = 32
        g_chunk_io.push_chunk<campaign_carry_troops_chunk>(32, false);
    }
    if (file_version > 183) {
        // 8 monument slots � 12 = 96
        g_chunk_io.push_chunk<campaign_carry_monuments_chunk>(96, false);
    }
    if (file_version > 185) {
        // STORAGE labor category priority (workers_* recomputed each tick)
        g_chunk_io.push_chunk<labor_storage_priority_chunk>(4, false);
    }
    if (file_version > 186) {
        // local cults + festival calendar theme state (Enhanced PC2)
        g_chunk_io.push_chunk<enhanced_religion_chunk>(64, false);
    }
    if (file_version > 187) {
        // recorded trails pool + per-building last-4 rings
        // slot: used+len+tiles[254]+figure_type+reserved = 515 (same as old used+len+tiles[256])
        // 512*515 + 4000*4*2 = 263680 + 32000 = 295680
        g_chunk_io.push_chunk<recorded_paths_chunk>(295680, true);
    }
    if (file_version > 197) {
        // count + reserved + 32 * (id[48] + version[16]) = 2052
        g_chunk_io.push_chunk<mods_chunk>(2052, false);
    }
    // Sectioned saves before 200 lack it and get the defaulter; the positional layout must not grow.
    if (file_version > 199 || g_chunk_io.is_sectioned()) {
        // count + 16 x (int32 x, int32 y) = 132
        g_chunk_io.push_chunk<clouds_chunk>(132, false);
    }
}
