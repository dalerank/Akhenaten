#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <city/floods.h>
#include <cinttypes>
#include <core/io.h>
#include <core/string.h>
#include <chrono>
#include <core/zip.h>
#include <core/log.h>
#include <core/image.h>

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

static char compress_buffer[COMPRESS_BUFFER_SIZE];

struct {
//    buffer *scenario_campaign_mission = nullptr;
    buffer *file_version = nullptr;
    buffer *image_grid = nullptr;
    buffer *edge_grid = nullptr;
    buffer *building_grid = nullptr;
    buffer *terrain_grid = nullptr;
    buffer *aqueduct_grid = nullptr;
    buffer *figure_grid = nullptr;
    buffer *bitfields_grid = nullptr;
    buffer *sprite_grid = nullptr;
    buffer *random_grid = nullptr;
    buffer *desirability_grid = nullptr;
    buffer *elevation_grid = nullptr;
    buffer *building_damage_grid = nullptr;
    buffer *aqueduct_backup_grid = nullptr;
    buffer *sprite_backup_grid = nullptr;
    buffer *figures = nullptr;
    buffer *route_figures = nullptr;
    buffer *route_paths = nullptr;
    buffer *formations = nullptr;
    buffer *formation_totals = nullptr;
    buffer *city_data = nullptr;
    buffer *city_faction_unknown = nullptr;
//    buffer *player_name = nullptr;
    buffer *city_faction = nullptr;
    buffer *buildings = nullptr;
    buffer *city_view_orientation = nullptr;
    buffer *game_time = nullptr;
    buffer *building_highest_id_ever = nullptr;
    buffer *random_iv = nullptr;
    buffer *city_view_camera = nullptr;
    buffer *building_count_culture1 = nullptr;
    buffer *city_graph_order = nullptr;
    buffer *emperor_change_time = nullptr;
    buffer *empire = nullptr;
    buffer *empire_cities = nullptr;
    buffer *building_count_industry = nullptr;
    buffer *trade_prices = nullptr;
    buffer *figure_names = nullptr;
    buffer *culture_coverage = nullptr;
//    buffer *scenario = nullptr;

    // 1. header
    // 2. requests/invasions
    // 3. map info 1
    // 4. request can-comply dialog
    // 5. map info 2
    // 6. herds
    // 7. demands
    // 8. random events
    // 9. fishing
    // 10. other request data
    // 11. wheat
    // 12. allowed buildings
    // 13. win criteria
    // 14. map points
    // 15. invasion entry points
    // 16. river entry points
    // 17. map info 3
    // 18. empire info

    struct {
        buffer *mission_index = nullptr;
        buffer *map_name = nullptr;
        buffer *map_settings = nullptr;
        buffer *is_custom = nullptr;
        buffer *player_name = nullptr;

        buffer *header = nullptr;
        buffer *info1 = nullptr;
        buffer *info2 = nullptr;
        buffer *info3 = nullptr;
        buffer *events = nullptr;
        buffer *win_criteria = nullptr;
        buffer *map_points = nullptr;
        buffer *river_points = nullptr;
        buffer *empire = nullptr;
        buffer *wheat = nullptr;
        buffer *climate_id = nullptr;

        buffer *requests = nullptr;
        buffer *invasions = nullptr;
        buffer *invasion_points = nullptr;
        buffer *request_comply_dialogs = nullptr;
        buffer *herds = nullptr;
        buffer *demands = nullptr;
        buffer *price_changes = nullptr;
        buffer *fishing_points = nullptr;
        buffer *request_extra = nullptr;
        buffer *allowed_builds = nullptr;

        buffer *events_ph = nullptr;

        buffer *monuments = nullptr;

    } SCENARIO;
//    scenario_data_buffers SCENARIO;

//    buffer *scenario_header = nullptr;
//        buffer *scenario_request_events = nullptr;
//        buffer *scenario_invasion_events = nullptr;
//    buffer *scenario_map_info1 = nullptr;
//        buffer *scenario_request_can_comply_dialogs = nullptr;
//    buffer *scenario_map_info2 = nullptr;
//        buffer *scenario_animal_herds = nullptr;
//        buffer *scenario_demands = nullptr;
//    buffer *scenario_random_events = nullptr;
//        buffer *scenario_fishing_spots = nullptr;
//        buffer *scenario_requests_extra = nullptr;
//    buffer *scenario_wheat_rome = nullptr;
//        buffer *scenario_allowed_buildings = nullptr;
//    buffer *scenario_win_criteria = nullptr;
//    buffer *scenario_map_points = nullptr;
//        buffer *scenario_invasion_points = nullptr;
//    buffer *scenario_river_entry = nullptr;
//    buffer *scenario_map_info3 = nullptr;
//    buffer *scenario_empire_info = nullptr;

    buffer *max_game_year = nullptr;
    buffer *earthquake = nullptr;
    buffer *emperor_change_state = nullptr;
    buffer *messages = nullptr;
    buffer *message_extra = nullptr;
    buffer *population_messages = nullptr;
    buffer *message_counts = nullptr;
    buffer *message_delays = nullptr;
    buffer *building_list_burning_totals = nullptr;
    buffer *figure_sequence = nullptr;
//    buffer *scenario_settings = nullptr;
    buffer *invasion_warnings = nullptr;
//    buffer *scenario_is_custom = nullptr;
    buffer *city_sounds = nullptr;
    buffer *building_highest_id = nullptr;
    buffer *figure_traders = nullptr;
    buffer *building_list_burning = nullptr;
    buffer *building_list_small = nullptr;
    buffer *building_list_large = nullptr;
    buffer *tutorial_part1 = nullptr;
    buffer *building_count_military = nullptr;
    buffer *enemy_army_totals = nullptr;
    buffer *building_storages = nullptr;
    buffer *building_count_culture2 = nullptr;
    buffer *building_count_support = nullptr;
    buffer *tutorial_part2 = nullptr;
    buffer *gladiator_revolt = nullptr;
    buffer *trade_route_limit = nullptr;
    buffer *trade_route_traded = nullptr;
    buffer *building_barracks_tower_sentry = nullptr;
    buffer *building_extra_sequence = nullptr;
    buffer *routing_counters = nullptr;
    buffer *building_count_culture3 = nullptr;
    buffer *enemy_armies = nullptr;
    buffer *city_entry_exit_xy = nullptr;
    buffer *last_invasion_id = nullptr;
    buffer *building_extra_corrupt_houses = nullptr;
//    buffer *scenario_name = nullptr;
    buffer *bookmarks = nullptr;
    buffer *tutorial_part3 = nullptr;
    buffer *empire_map_objects = nullptr;
    buffer *city_entry_exit_grid_offset = nullptr;
    buffer *floodplain_settings = nullptr;
    buffer *moisture_grid = nullptr;
    buffer *bizarre_ordered_fields_4 = nullptr;

    buffer *junk1 = nullptr;
    buffer *junk2a = nullptr;
    buffer *junk2b = nullptr;
    buffer *junk2c = nullptr;
    buffer *junk2d = nullptr;
    buffer *junk3 = nullptr;
    buffer *junk4a = nullptr;
    buffer *junk4b = nullptr;
    buffer *junk4c = nullptr;
    buffer *junk4d = nullptr;
    buffer *junk4e = nullptr;
    buffer *junk4f = nullptr;
    buffer *junk5 = nullptr;
    buffer *junk6a = nullptr;
    buffer *junk6b = nullptr;
    buffer *junk7a = nullptr;
    buffer *junk7b = nullptr;
//    buffer *junk7c = nullptr;
    buffer *junk8a = nullptr;
    buffer *junk8b = nullptr;
    buffer *junk8c = nullptr;
    buffer *junk9a = nullptr;
    buffer *junk9b = nullptr;
//    buffer *scenario_events = nullptr;
    buffer *junk10a = nullptr;
    buffer *junk10b = nullptr;
    buffer *junk10c = nullptr;
    buffer *junk10d = nullptr;
    buffer *junk10f = nullptr;
    buffer *junk11 = nullptr;
//    buffer *junk12 = nullptr;
    buffer *empire_map_routes = nullptr;
    buffer *junk14 = nullptr;
    buffer *bizarre_ordered_fields_1 = nullptr;
//    buffer *junk15 = nullptr;
    buffer *bizarre_ordered_fields_3 = nullptr;
    buffer *junk16 = nullptr;
    buffer *junk17 = nullptr;
    buffer *bizarre_ordered_fields_2 = nullptr;
    buffer *junk18 = nullptr;
    buffer *junk19 = nullptr;
    buffer *junk20 = nullptr;

    buffer *soil_fertility_grid = nullptr;
    buffer *GRID02_8BIT = nullptr;
    buffer *GRID03_32BIT = nullptr;
    buffer *soil_unk_grid = nullptr;
} buffers;
FileManager FileIO;

void FileManager::clear() {
    loaded = false;
    safe_strncpy(file_path, "", MAX_FILE_NAME);
    file_size = 0;
    file_offset = 0;
    file_version = {-1, -1};
    for (int i = 0; i < num_chunks(); ++i) {
        delete file_chunks.at(i).buf;
    }
    file_chunks.clear();
}

static buffer *version_buffer = new buffer(8);
file_version_t read_file_version(const char *filename, int offset) {
    file_version_t version = {-1, -1};
    version_buffer->clear();
    if (io_read_file_part_into_buffer(filename, NOT_LOCALIZED, version_buffer, 8, offset + 4)) {
        version.minor = version_buffer->read_i32();
        version.major = version_buffer->read_i32();
    }
    return version;
}
void FileManager::init_with_schema(file_schema_enum_t mapping_schema, file_version_t version) {
    if (loaded)
        clear(); // make sure the pieces
    file_version = version;
    auto state = &buffers;
    switch (mapping_schema) {
        case FILE_SCHEMA_MAP: // TODO!!!!
//            scenario_state *state = &scenario_data.state;
//            state->graphic_ids = create_scenario_piece(52488, "");
//            state->edge = create_scenario_piece(26244, "");
//            state->terrain = create_scenario_piece(52488, "");
//            state->bitfields = create_scenario_piece(26244, "");
//            state->random = create_scenario_piece(26244, "");
//            state->elevation = create_scenario_piece(26244, "");
//            state->random_iv = create_scenario_piece(8, "");
//            state->camera = create_scenario_piece(8, "");
//        //    state->scenario = create_scenario_piece(1720, "");
//            state->SCENARIO.header = create_scenario_piece(14, "");
//            state->SCENARIO.requests = create_scenario_piece(160, "");
//            state->SCENARIO.invasions = create_scenario_piece(202, "");
//            state->SCENARIO.info1 = create_scenario_piece(614, "");
//            state->SCENARIO.request_comply_dialogs = create_scenario_piece(20, "");
//            state->SCENARIO.info2 = create_scenario_piece(6, "");
//            state->SCENARIO.herds = create_scenario_piece(16, "");
//            state->SCENARIO.demands = create_scenario_piece(120, "");
//            state->SCENARIO.price_changes = create_scenario_piece(120, "");
//            state->SCENARIO.events = create_scenario_piece(44, "");
//            state->SCENARIO.fishing_points = create_scenario_piece(32, "");
//            state->SCENARIO.request_extra = create_scenario_piece(120, "");
//            state->SCENARIO.wheat = create_scenario_piece(4, "");
//            state->SCENARIO.allowed_builds = create_scenario_piece(100, "");
//            state->SCENARIO.win_criteria = create_scenario_piece(52, "");
//            state->SCENARIO.map_points = create_scenario_piece(12, "");
//            state->SCENARIO.invasion_points = create_scenario_piece(32, "");
//            state->SCENARIO.river_points = create_scenario_piece(8, "");
//            state->SCENARIO.info3 = create_scenario_piece(32, "");
//            state->SCENARIO.empire = create_scenario_piece(12, "");
//
//            state->end_marker = create_scenario_piece(4, "");
            break;
        case FILE_SCHEMA_SAV: {
            state->SCENARIO.mission_index = push_chunk(4, false, "SCENARIO.mission_index");
            state->file_version = push_chunk(8, false, "file_version");

            state->junk1 = push_chunk(6000, false, "junk1"); // ?????

            state->image_grid = push_chunk(207936, true, "image_grid");                         // (228²) * 4 <<
            state->edge_grid = push_chunk(51984, true, "edge_grid");                            // (228²) * 1
            state->building_grid = push_chunk(103968, true, "building_grid");                   // (228²) * 2
            state->terrain_grid = push_chunk(207936, true, "terrain_grid");                     // (228²) * 4 <<
            state->aqueduct_grid = push_chunk(51984, true, "aqueduct_grid");                    // (228²) * 1
            state->figure_grid = push_chunk(103968, true, "figure_grid");                       // (228²) * 2
            state->bitfields_grid = push_chunk(51984, true, "bitfields_grid");                  // (228²) * 1
            state->sprite_grid = push_chunk(51984, true, "sprite_grid");                        // (228²) * 1
            state->random_grid = push_chunk(51984, false, "random_grid");                            // (228²) * 1
            state->desirability_grid = push_chunk(51984, true, "desirability_grid");            // (228²) * 1
            state->elevation_grid = push_chunk(51984, true, "elevation_grid");                  // (228²) * 1
            state->building_damage_grid = push_chunk(103968, true, "building_damage_grid");     // (228²) * 2 <<
            state->aqueduct_backup_grid = push_chunk(51984, true, "aqueduct_backup_grid");      // (228²) * 1
            state->sprite_backup_grid = push_chunk(51984, true, "sprite_backup_grid");          // (228²) * 1
            state->figures = push_chunk(776000, true, "figures");
            state->route_figures = push_chunk(2000, true, "route_figures");
            state->route_paths = push_chunk(500000, true, "route_paths");
            state->formations = push_chunk(7200, true, "formations");
            state->formation_totals = push_chunk(12, false, "formation_totals");
            state->city_data = push_chunk(37808, true, "city_data");
            state->city_faction_unknown = push_chunk(4, false, "city_faction_unknown");
            state->SCENARIO.player_name = push_chunk(64, false, "SCENARIO.player_name");
            state->city_faction = push_chunk(4, false, "city_faction");
            state->buildings = push_chunk(1056000, true, "buildings");
            state->city_view_orientation = push_chunk(4, false, "city_view_orientation"); // ok
            state->game_time = push_chunk(20, false, "game_time"); // ok
            state->building_highest_id_ever = push_chunk(8, false, "building_extra_highest_id_ever"); // ok
            state->random_iv = push_chunk(8, false, "random_iv"); // ok
            state->city_view_camera = push_chunk(8, false, "city_view_camera"); // ok
//                state->building_count_culture1 = create_savegame_piece(132, false, ""); // MISSING
            state->city_graph_order = push_chunk(8, false, "city_graph_order"); // I guess ????
//                state->emperor_change_time = create_savegame_piece(8, false, ""); // MISSING
            state->empire = push_chunk(12, false, "empire"); // ok ???
            state->empire_cities = push_chunk(6466, true, "empire_cities"); // 83920 + 7681 --> 91601
            state->building_count_industry = push_chunk(288, false, "building_count_industry"); // 288 bytes ??????
            state->trade_prices = push_chunk(288, false, "trade_prices");
            state->figure_names = push_chunk(84, false, "figure_names");

//                state->culture_coverage = create_savegame_piece(60, false, ""); // MISSING
//                state->scenario = create_savegame_piece(1720, false, ""); // MISSING



//            state->scenario_data.requests = create_savegame_piece(160, false, "requests");
//            state->scenario_data.invasions = create_savegame_piece(202, false, "invasions");

//            state->scenario_data.request_comply_dialogs = create_savegame_piece(20, false, "request_comply_dialogs");

//            state->scenario_data.demands = create_savegame_piece(120, false, "demands");
//            state->scenario_data.price_changes = create_savegame_piece(120, false, "price_changes");
//            state->scenario_data.events = create_savegame_piece(44, false, "events");
//            state->scenario_data.fishing_points = create_savegame_piece(32, false, "fishing_points");
//            state->scenario_data.request_extra = create_savegame_piece(120, false, "request_extra");
//            state->scenario_data.wheat = create_savegame_piece(4, false, "wheat");

//            state->scenario_data.map_points = create_savegame_piece(12, false, "map_points");
//            state->scenario_data.invasion_points = create_savegame_piece(32, false, "invasion_points");
//            state->scenario_data.river_points = create_savegame_piece(8, false, "river_points");
//            state->scenario_data.info3 = create_savegame_piece(32, false, "info3");
//            state->scenario_data.empire = create_savegame_piece(12, false, "empire");


            state->SCENARIO.header = push_chunk(32, false, "SCENARIO.header");
            state->SCENARIO.info1 = push_chunk(614, false, "SCENARIO.info1");
//                state->scenario_request_can_comply_dialogs = create_savegame_piece(20, false, ""); // MISSING
            state->SCENARIO.info2 = push_chunk(6, false, "SCENARIO.info2");

            // 48 bytes     FF FF FF FF (non cyclic) ???
            // 44 bytes     00 00 00 00 ???
            // 64 bytes     FF FF FF FF (cyclic) invasion points???
            // 36 bytes     01 00 01 00 ???
            state->junk2a = push_chunk(48, false, "junk2a"); // unknown bytes
            state->junk2b = push_chunk(44, false, "junk2b"); // unknown bytes
            state->junk2c = push_chunk(64, false, "junk2c"); // unknown bytes
            state->junk2d = push_chunk(36, false, "junk2d"); // unknown bytes

            state->SCENARIO.win_criteria = push_chunk(60, false, "SCENARIO.win_criteria");

            // 4 bytes     FF FF FF FF ???
            state->junk3 = push_chunk(4, false, "junk3"); // unknown bytes

            state->city_entry_exit_xy = push_chunk(8, false, "city_entry_exit_xy");

            // 40 bytes     FF FF FF FF (non cyclic?) ???
            // 4  bytes     B8 0B 00 00 ???
            // 12 bytes     0A 00 00 00 (3x4) ???
            // 12 bytes     CB 32 00 00 (3x4) ??? (n, n+2, n+1497)
            // 14 bytes     01 00 00 00 ???
            // 2  bytes     FF FF       ???
            state->junk4a = push_chunk(40, false, "junk4a"); // unknown bytes
            state->junk4b = push_chunk(4, false, "junk4b"); // unknown bytes
            state->junk4c = push_chunk(12, false, "junk4c"); // unknown bytes
            state->junk4d = push_chunk(12, false, "junk4d"); // unknown bytes
            state->SCENARIO.climate_id = push_chunk(2, false, "SCENARIO.climate_id");
            state->junk4e = push_chunk(10, false, "junk4e"); // unknown bytes
            state->junk4f = push_chunk(2, false, "junk4f"); // unknown bytes
            state->junk4f = push_chunk(2, false, "junk4g"); // unknown bytes
            state->SCENARIO.herds = push_chunk(32, false, "SCENARIO.herds");
            state->SCENARIO.allowed_builds = push_chunk(228, false, "SCENARIO.allowed_builds");

            // 24 bytes     FF FF FF FF (cyclic) ???
            state->junk5 = push_chunk(28, false, "junk5"); // unknown bytes
            state->SCENARIO.monuments = push_chunk(6, false, "SCENARIO.monuments"); // 3 x 2-byte

            // 290 bytes    00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            state->junk6a = push_chunk(290, false, "junk6a"); // unknown bytes
            state->junk6b = push_chunk(4 + 4 + 4, false, "junk6b"); // unknown bytes

            /////////////////////

//                state->max_game_year = create_savegame_piece(4, false, ""); // MISSING
//                state->earthquake = create_savegame_piece(60, false, ""); // MISSING
//                state->emperor_change_state = create_savegame_piece(4, false, ""); // MISSING

            state->messages = push_chunk(48000, true, "messages"); // 94000 + 533 --> 94532 + 4 = 94536
            state->message_extra = push_chunk(12, false, "message_extra"); // ok
            state->population_messages = push_chunk(10, false, "population_messages"); // ok
            state->message_counts = push_chunk(80, false, "message_counts"); // ok
            state->message_delays = push_chunk(80, false, "message_delays"); // ok
            state->building_list_burning_totals = push_chunk(8, false, "building_list_burning_totals"); // ok
            state->figure_sequence = push_chunk(4, false, "figure_sequence"); // ok
            state->SCENARIO.map_settings = push_chunk(12, false, "SCENARIO.map_settings"); // ok
            state->invasion_warnings = push_chunk(3232, true, "invasion_warnings"); // 94743 + 31 --> 94774 + 4 = 94778
            state->SCENARIO.is_custom = push_chunk(4, false, "SCENARIO.is_custom"); // ok
            state->city_sounds = push_chunk(8960, false, "city_sounds"); // ok
            state->building_highest_id = push_chunk(4, false, "building_extra_highest_id"); // ok
            state->figure_traders = push_chunk(8804, false, "figure_traders"); // +4000 ???
            state->building_list_burning = push_chunk(1000, true, "building_list_burning"); // ok
            state->building_list_small = push_chunk(1000, true, "building_list_small"); // ok
            state->building_list_large = push_chunk(8000, true, "building_list_large"); // ok

//                state->tutorial_part1 = create_savegame_piece(32, false, "");
//                state->building_count_military = create_savegame_piece(16, false, "");
//                state->enemy_army_totals = create_savegame_piece(20, false, "");
//                state->building_storages = create_savegame_piece(6400, false, "");
//                state->building_count_culture2 = create_savegame_piece(32, false, "");
//                state->building_count_support = create_savegame_piece(24, false, "");
//                state->tutorial_part2 = create_savegame_piece(4, false, "");
//                state->gladiator_revolt = create_savegame_piece(16, false, "");

            // 32 bytes     00 00 00 00 ???
            // 24 bytes     00 00 00 00 ???
            state->junk7a = push_chunk(32, false, "junk7a"); // unknown bytes
            state->junk7b = push_chunk(24, false, "junk7b"); // unknown bytes
            state->building_storages = push_chunk(39200, false, "building_storages"); // storage instructions

            state->trade_route_limit = push_chunk(2880, true, "trade_route_limit"); // ok
            state->trade_route_traded = push_chunk(2880, true, "trade_route_traded"); // ok

//                state->building_barracks_tower_sentry = create_savegame_piece(4, false, "");
//                state->building_extra_sequence = create_savegame_piece(4, false, "");
//                state->routing_counters = create_savegame_piece(16, false, "");
//                state->building_count_culture3 = create_savegame_piece(40, false, "");
//                state->enemy_armies = create_savegame_piece(900, false, "");

            // 12 bytes     00 00 00 00 ???
            // 16 bytes     00 00 00 00 ???
            // 22 bytes     00 00 00 00 ???
            state->junk8a = push_chunk(12, false, "junk8a"); // unknown bytes
            state->junk8b = push_chunk(16, false, "junk8b"); // unknown bytes
            state->junk8c = push_chunk(22, false, "junk8c"); // unknown bytes

//                state->last_invasion_id = create_savegame_piece(2, false, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

            state->SCENARIO.map_name = push_chunk(65, false, "SCENARIO.map_name"); // ok
            state->bookmarks = push_chunk(32, false, "bookmarks"); // ok
            state->tutorial_part3 = push_chunk(4, false, "tutorial_part3"); // ok ????

//            int t_sub = 228;

            // 8 bytes      00 00 00 00 ???
            state->junk9a = push_chunk(8, false, "junk9a");
            state->junk9b = push_chunk(396, false, "junk9b");

            // 51984 bytes  00 00 00 00 ???
            state->soil_fertility_grid = push_chunk(51984, false, "soil_fertility_grid");


            // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
            state->SCENARIO.events_ph = push_chunk(18600, false, "SCENARIO.events_ph");

            // 28 bytes     2F 01 00 00 ???
            // 13416 bytes  00 00 00 00 ??? (200 less for non-expanded file)
            // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
            state->junk10a = push_chunk(28, false, "junk10a");
            state->junk10b = push_chunk(version.minor < 149 ? 13216 : 13416, false, "junk10b");
            state->junk10c = push_chunk(8200, false, "junk10c");

            state->junk11 = push_chunk(1280, true, "junk11"); // unknown compressed data

            state->empire_map_objects = push_chunk(version.minor < 160 ? 15200 : 19600, true, "empire_objects");
            state->empire_map_routes = push_chunk(16200, true, "empire_routes");

            // 51984 bytes  FF FF FF FF ???          // (228²) * 1 ?????????????????
            state->GRID02_8BIT = push_chunk(51984, false, "GRID02_8BIT"); // todo: 1-byte grid

            // 20 bytes     19 00 00 00 ???
            state->junk14 = push_chunk(20, false, "junk14");

            // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
            state->bizarre_ordered_fields_1 = push_chunk(528, false, "bizarre_ordered_fields_1");

            state->floodplain_settings = push_chunk(36, true, "floodplain_settings"); // floodplain_settings
            state->GRID03_32BIT = push_chunk(207936, true, "GRID03_32BIT"); // todo: 4-byte grid

            // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
            state->bizarre_ordered_fields_3 = push_chunk(312, false, "bizarre_ordered_fields_3"); // 71x 4-bytes emptiness

            // 64 bytes     00 00 00 00 ???
            state->junk16 = push_chunk(64, false, "junk16"); // 71x 4-bytes emptiness
            state->tutorial_part1 = push_chunk(41, false, "tutorial_part1"); // 41 x 1-byte flag fields
            state->soil_unk_grid = push_chunk(51984, true, "floodplain_soil_depletion");

            // lone byte ???
            state->junk17 = push_chunk(1, false, "junk17");
            state->moisture_grid = push_chunk(51984, true, "moisture_grid");

            // 672 bytes    0F 00 00 00 ??? 28 x 24-byte chunk
            state->bizarre_ordered_fields_2 = push_chunk(672, false, "bizarre_ordered_fields_2");

            // 20 bytes     00 00 00 00 ???
            // 4800 bytes   00 00 00 00 ???
            state->junk18 = push_chunk(20, false, "junk18");
            state->bizarre_ordered_fields_4 = push_chunk(4800, false, "bizarre_ordered_fields_4");

            break;
        }
    }
}
const file_version_t *FileManager::get_file_version() {
    return &file_version;
}

buffer *FileManager::push_chunk(int size, bool compressed, const char *name) {
    // add empty piece onto the stack
    file_chunks.push_back(file_chunk_t());
    auto piece = &file_chunks.at(file_chunks.size() - 1);

    // fill info
    piece->compressed = compressed;
    safe_realloc_for_size(&piece->buf, size);
    strncpy(piece->name, name, 99);

    // return linked buffer pointer so that it can be assigned for read/write access later
    return piece->buf;
}
const int FileManager::num_chunks() {
    return file_chunks.size();
}

#include "SDL.h"

#ifdef _WIN32
#  ifdef _WIN64
#    define PRI_SIZET PRIu64
#  else
#    define PRI_SIZET PRIu32
#  endif
#else
#  define PRI_SIZET "zu"
#endif

int findex;
char *fname;

void log_hex(file_chunk_t *piece, int i, int offs) {
    // log first few bytes of the filepiece
    size_t s = piece->buf->size() < 16 ? piece->buf->size() : 16;
    char hexstr[40] = {0};
    for (int b = 0; b < s; b++) {
        char hexcode[3] = {0};
        uint8_t inbyte = piece->buf->get_value(b);
        snprintf(hexcode, sizeof(hexcode)/sizeof(hexcode[0]), "%02X", inbyte);
        strncat(hexstr, hexcode, sizeof(hexcode)/sizeof(hexcode[0]) - 1);
        if ((b + 1) % 4 == 0 || (b + 1) == s)
            strncat(hexstr, " ", 2);
    }

    // Unfortunately, MSVCRT only supports C89 and thus, "zu" leads to segfault
    SDL_Log("Piece %s %03i/%i : %8i@ %-36s(%" PRI_SIZET ") %s", piece->compressed ? "(C)" : "---", i + 1, FileIO.num_chunks(),
            offs, hexstr, piece->buf->size(), fname);
}
static int read_compressed_chunk(FILE *fp, buffer *buf, int filepiece_size) {
    // check that the stream size isn't above maximum temp buffer
    if (filepiece_size > COMPRESS_BUFFER_SIZE)
        return 0;

    // read 32-bit int header denoting size of compressed chunk
    uint32_t chunk_size = 0;
    fread(&chunk_size, 4, 1, fp);

    // if file signature says "uncompressed" well man, it's uncompressed. read as normal ignoring the directive
    if ((unsigned int) chunk_size == UNCOMPRESSED) {
        if (buf->from_file(filepiece_size, fp) != filepiece_size)
            return 0;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        int csize = fread(compress_buffer, 1, chunk_size, fp);
        if (csize != chunk_size) {
            SDL_Log("Incorrect chunk size, expected %i, found %i", chunk_size, csize);
            return 0;
        }
        int bsize = zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size);
        if (bsize != buf->size()) {
            SDL_Log("Incorrect buffer size, expected %i, found %i", buf->size(), bsize);
            return 0;
        }
//        if (fread(compress_buffer, 1, chunk_size, fp) != chunk_size
//            || zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size) !=
//               buf->size())
//            return 0;
    }
//    buf->force_validate_unsafe_pls_use_carefully();

    return 1;
}
static int write_compressed_chunk(FILE *fp, buffer *buf, int bytes_to_write) {
    if (bytes_to_write > COMPRESS_BUFFER_SIZE)
        return 0;

    int output_size = COMPRESS_BUFFER_SIZE;
    if (zip_compress(buf->get_data(), bytes_to_write, compress_buffer, &output_size)) {
//        write_int32(fp, output_size);
        fwrite(&output_size, 4, 1, fp);
        fwrite(compress_buffer, 1, output_size, fp);
    } else {
        // unable to compress: write uncompressed
//        write_int32(fp, UNCOMPRESSED);
        output_size = UNCOMPRESSED;
        fwrite(&output_size, 4, 1, fp);
        fwrite(buf->get_data(), 1, bytes_to_write, fp);
    }
    return 1;
}

//static void write_file_pieces(FILE *fp) {
//    for (int i = 0; i < file_data.num_pieces; i++) {
//        file_chunk_t *piece = &file_data.file_chunks[i];
//        if (piece->compressed)
//            write_compressed_chunk(fp, piece->buf, piece->buf->size());
//        else
//            piece->buf->to_file(piece->buf->size(), fp);
//    }
//}
bool FileManager::load_file_headers() {
    file_version = read_file_version(file_path, file_offset);
    if (file_version.major == -1 || file_version.minor == -1)
        return false;
    return true;
    // TODO: file size?
}
bool FileManager::load_file_body() {
    FILE *fp = file_open(dir_get_file(file_path, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        return false;
    }
    if (file_offset)
        fseek(fp, file_offset, SEEK_SET);

    // read contents
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t *chunk = &file_chunks.at(i);
        findex = i;
        fname = chunk->name;
        int result = 0;

        auto offs = ftell(fp);

        if (chunk->compressed)
            result = read_compressed_chunk(fp, chunk->buf, chunk->buf->size());
        else
            result = chunk->buf->from_file(chunk->buf->size(), fp) == chunk->buf->size();

        // export uncompressed buffer data to zip folder for debugging
        char *lfile = (char *) malloc(200);
        sprintf(lfile, "DEV_TESTING/zip/%03i_%i_%s", findex + 1, chunk->buf->size(), fname);
        FILE *log = fopen(lfile, "wb+");
        if (log)
            fwrite(chunk->buf->get_data(), chunk->buf->size(), 1, log);
        fclose(log);
        free(lfile);

        ///

//        log_hex(chunk, i, offs);

        // The last piece may be smaller than buf->size
        if (!result && i != (num_chunks() - 1)) {
            log_error("Unable to load game, unable to read savefile.", 0, 0);
            return false;
        }
    }
    file_close(fp);
    return true;
}

bool FileManager::read_from_file(const char *filename, int offset) {

    //////////////////////////////////////////////////////////////////
    auto TIME_START = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    // first, clear up the manager data and set the new file info
    clear();
    safe_strncpy(file_path, filename, MAX_FILE_NAME);
    file_offset = offset;

    // read file header data
    if (!load_file_headers()) {
        log_info("Invalid file and/or version header!", filename, 0);
        return false;
    }

    // determine appropriate schema and related data
    if (file_has_extension(filename, "pak") || file_has_extension(filename, "sav"))
        file_schema = FILE_SCHEMA_SAV;
    else if (file_has_extension(filename, "map"))
        file_schema = FILE_SCHEMA_MAP;
    if (file_has_extension(filename, "pak") && file_version.minor < 149)
        terrain_ph_offset = 539; //14791
    else
        terrain_ph_offset = 0; //14252

    // init file chunks and buffer collection
    init_with_schema(file_schema, file_version);

    // fill buffers with file contents
    if (!load_file_body()) {
        return false;
    }

    //////////////////////////////////////////////////////////////////
    auto TIME_FINISH = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    SDL_Log("Loading savestate from file %s %i@ --- VERSION HEADER: %i %i --- %" PRIu64 " milliseconds", file_path, file_offset, file_version.minor, file_version.major,
            std::chrono::duration_cast<std::chrono::milliseconds>(TIME_FINISH - TIME_START));

    return true;
}
bool FileManager::write_to_file(const char *filename, int offset) {

}

#include "building/barracks.h"
#include "building/count.h"
#include "building/list.h"
#include "building/storage.h"
#include "city/culture.h"
#include "city/data.h"
#include "core/file.h"
#include "core/log.h"
#include "core/image.h"
#include "core/game_environment.h"
#include "city/message.h"
#include "city/view.h"
#include "core/dir.h"
#include "core/random.h"
#include "core/zip.h"
#include "empire/city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/enemy_army.h"
#include "figure/formation.h"
#include "figure/name.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "map/aqueduct.h"
#include "map/bookmark.h"
#include "map/building.h"
#include "map/desirability.h"
#include "map/elevation.h"
#include "map/figure.h"
#include "map/image.h"
#include "map/property.h"
#include "map/random.h"
#include "map/routing.h"
#include "map/sprite.h"
#include "map/terrain.h"
#include "scenario/criteria.h"
#include "scenario/earthquake.h"
#include "scenario/emperor_change.h"
#include "scenario/gladiator_revolt.h"
#include "scenario/invasion.h"
#include "scenario/scenario.h"
#include "sound/city.h"

static void scenario_load_from_state() {
    auto state = &buffers;
//    map_image_load_state(state->graphic_ids);
//    map_terrain_load_state(state->terrain);
//    map_property_load_state(state->bitfields, state->edge);
//    map_random_load_state(state->random);
//    map_elevation_load_state(state->elevation);
//    city_view_load_scenario_state(state->camera);
//
//    random_load_state(state->random_iv);
//
//    scenario_load_state(&state->SCENARIO);

//    file->end_marker->skip(4);
}
static void scenario_save_to_state() {
    auto state = &buffers;
//    map_image_save_state(state->graphic_ids);
//    map_terrain_save_state(state->terrain);
//    map_property_save_state(state->bitfields, state->edge);
//    map_random_save_state(state->random);
//    map_elevation_save_state(state->elevation);
//    city_view_save_scenario_state(state->camera);
//
//    random_save_state(state->random_iv);
//
//    scenario_save_state(&state->SCENARIO);

//    file->end_marker->skip(4);
}
void FileManager::load_state() {
//    file_data.version.minor = state->file_version->read_i32();
//    file_data.version.major = state->file_version->read_i32();

    auto state = &buffers;
//    scenario_load_state(&state->SCENARIO);

    map_image_load_state(state->image_grid, terrain_ph_offset);
    map_building_load_state(state->building_grid, state->building_damage_grid);
    map_terrain_load_state(state->terrain_grid);
    map_aqueduct_load_state(state->aqueduct_grid, state->aqueduct_backup_grid);
    map_figure_load_state(state->figure_grid);
    map_sprite_load_state(state->sprite_grid, state->sprite_backup_grid);
    map_property_load_state(state->bitfields_grid, state->edge_grid);
    map_random_load_state(state->random_grid);
    map_desirability_load_state(state->desirability_grid);
    map_elevation_load_state(state->elevation_grid);

    figure_load_state(state->figures, state->figure_sequence);
    figure_route_load_state(state->route_figures, state->route_paths);
    formations_load_state(state->formations, state->formation_totals);

    city_data_load_state(state->city_data,
                         state->city_faction,
                         state->city_faction_unknown,
                         state->city_graph_order,
                         state->city_entry_exit_xy,
                         state->city_entry_exit_grid_offset);
    floodplains_load_state(state->floodplain_settings);

    building_load_state(state->buildings,
                        state->building_highest_id,
                        state->building_highest_id_ever);
//    building_barracks_load_state(state->building_barracks_tower_sentry);
    city_view_load_state(state->city_view_orientation, state->city_view_camera);
    game_time_load_state(state->game_time);
    random_load_state(state->random_iv);
//    building_count_load_state(state->building_count_industry,
//                              state->building_count_culture1,
//                              state->building_count_culture2,
//                              state->building_count_culture3,
//                              state->building_count_military,
//                              state->building_count_support);

//    scenario_emperor_change_load_state(state->emperor_change_time, state->emperor_change_state);

    empire_load_state(state->empire);
    empire_city_load_state(state->empire_cities);
    trade_prices_load_state(state->trade_prices);
    figure_name_load_state(state->figure_names);
//    city_culture_load_state(state->culture_coverage);

//    scenario_max_year_load_state(state->max_game_year);
//    scenario_earthquake_load_state(state->earthquake);
    city_message_load_state(state->messages, state->message_extra,
                            state->message_counts, state->message_delays,
                            state->population_messages);
    sound_city_load_state(state->city_sounds);
    traders_load_state(state->figure_traders);

    building_list_load_state(state->building_list_small, state->building_list_large,
                             state->building_list_burning, state->building_list_burning_totals);

    tutorial_load_state(state->tutorial_part1, state->tutorial_part2, state->tutorial_part3);

    building_storage_load_state(state->building_storages);
//    scenario_gladiator_revolt_load_state(state->gladiator_revolt);
    trade_routes_load_state(state->trade_route_limit, state->trade_route_traded);
//    map_routing_load_state(state->routing_counters);
//    enemy_armies_load_state(state->enemy_armies, state->enemy_army_totals);
//    scenario_invasion_load_state(state->last_invasion_id, state->invasion_warnings);
    map_bookmark_load_state(state->bookmarks);

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        map_soil_fertility_load_state(state->soil_fertility_grid);
        map_soil_unk_grid_load_state(state->soil_unk_grid);
        map_moisture_load_state(state->moisture_grid);
        empire_load_internal_ph(state->empire_map_objects, state->empire_map_routes);

        map_temp_grid_load(state->GRID02_8BIT, 1);
        map_temp_grid_load(state->GRID03_32BIT, 2);
//        map_GRID03_32BIT_load_split_state(state->GRID03_32BIT);

    }
//    state->end_marker->skip(284);
}
static void savegame_save_to_state() {
    auto state = &buffers;
//    state->file_version->write_i32(file_data.version.minor);
//    state->file_version->write_i32(file_data.version.major);

//    scenario_save_state(&state->SCENARIO);

//    scenario_settings_save_state(state->scenario_campaign_mission,
//                                 state->scenario_settings,
//                                 state->scenario_is_custom,
//                                 state->player_name,
//                                 state->scenario_name);

    map_image_save_state(state->image_grid);
    map_building_save_state(state->building_grid, state->building_damage_grid);
    map_terrain_save_state(state->terrain_grid);
    map_aqueduct_save_state(state->aqueduct_grid, state->aqueduct_backup_grid);
    map_figure_save_state(state->figure_grid);
    map_sprite_save_state(state->sprite_grid, state->sprite_backup_grid);
    map_property_save_state(state->bitfields_grid, state->edge_grid);
    map_random_save_state(state->random_grid);
    map_desirability_save_state(state->desirability_grid);
    map_elevation_save_state(state->elevation_grid);

    figure_save_state(state->figures, state->figure_sequence);
    figure_route_save_state(state->route_figures, state->route_paths);
    formations_save_state(state->formations, state->formation_totals);

    city_data_save_state(state->city_data,
                         state->city_faction,
                         state->city_faction_unknown,
                         state->city_graph_order,
                         state->city_entry_exit_xy,
                         state->city_entry_exit_grid_offset, nullptr);

    building_save_state(state->buildings,
                        state->building_highest_id,
                        state->building_highest_id_ever);
    building_barracks_save_state(state->building_barracks_tower_sentry);
    city_view_save_state(state->city_view_orientation, state->city_view_camera);
    game_time_save_state(state->game_time);
    random_save_state(state->random_iv);
    building_count_save_state(state->building_count_industry,
                              state->building_count_culture1,
                              state->building_count_culture2,
                              state->building_count_culture3,
                              state->building_count_military,
                              state->building_count_support);

    scenario_emperor_change_save_state(state->emperor_change_time, state->emperor_change_state);

    empire_save_state(state->empire);
    empire_city_save_state(state->empire_cities);
    trade_prices_save_state(state->trade_prices);
    figure_name_save_state(state->figure_names);
    city_culture_save_state(state->culture_coverage);

//    scenario_save_state(&state->SCENARIO);
    scenario_max_year_save_state(state->max_game_year);
    scenario_earthquake_save_state(state->earthquake);
    city_message_save_state(state->messages, state->message_extra,
                            state->message_counts, state->message_delays,
                            state->population_messages);
    sound_city_save_state(state->city_sounds);
    traders_save_state(state->figure_traders);

    building_list_save_state(state->building_list_small, state->building_list_large,
                             state->building_list_burning, state->building_list_burning_totals);

    tutorial_save_state(state->tutorial_part1, state->tutorial_part2, state->tutorial_part3);

    building_storage_save_state(state->building_storages);
    scenario_gladiator_revolt_save_state(state->gladiator_revolt);
    trade_routes_save_state(state->trade_route_limit, state->trade_route_traded);
    map_routing_save_state(state->routing_counters);
    enemy_armies_save_state(state->enemy_armies, state->enemy_army_totals);
    scenario_invasion_save_state(state->last_invasion_id, state->invasion_warnings);
    map_bookmark_save_state(state->bookmarks);

//    state->end_marker->skip(284);
}