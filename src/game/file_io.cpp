#include "file_io.h"

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <city/floods.h>
#include <cinttypes>
#include <core/io.h>

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

//static const int SAVE_GAME_VERSION = 0x76;

static char compress_buffer[COMPRESS_BUFFER_SIZE];

static int savegame_version[2];

typedef struct {
    buffer *buf;
    int compressed;
    char name[100];
} file_piece;

typedef struct {
    buffer *graphic_ids = new buffer;
    buffer *edge = new buffer;
    buffer *terrain = new buffer;
    buffer *bitfields = new buffer;
    buffer *random = new buffer;
    buffer *elevation = new buffer;
    buffer *random_iv = new buffer;
    buffer *camera = new buffer;
//    buffer *scenario = new buffer;
    scenario_data_buffers SCENARIO;
    buffer *end_marker = new buffer;
} scenario_state;

static struct {
    int num_pieces;
    file_piece pieces[10];
    scenario_state state;
} scenario_data = {0};

typedef struct {
//    buffer *scenario_campaign_mission = new buffer;
    buffer *file_version = new buffer;
    buffer *image_grid = new buffer;
    buffer *edge_grid = new buffer;
    buffer *building_grid = new buffer;
    buffer *terrain_grid = new buffer;
    buffer *aqueduct_grid = new buffer;
    buffer *figure_grid = new buffer;
    buffer *bitfields_grid = new buffer;
    buffer *sprite_grid = new buffer;
    buffer *random_grid = new buffer;
    buffer *desirability_grid = new buffer;
    buffer *elevation_grid = new buffer;
    buffer *building_damage_grid = new buffer;
    buffer *aqueduct_backup_grid = new buffer;
    buffer *sprite_backup_grid = new buffer;
    buffer *figures = new buffer;
    buffer *route_figures = new buffer;
    buffer *route_paths = new buffer;
    buffer *formations = new buffer;
    buffer *formation_totals = new buffer;
    buffer *city_data = new buffer;
    buffer *city_faction_unknown = new buffer;
//    buffer *player_name = new buffer;
    buffer *city_faction = new buffer;
    buffer *buildings = new buffer;
    buffer *city_view_orientation = new buffer;
    buffer *game_time = new buffer;
    buffer *building_highest_id_ever = new buffer;
    buffer *random_iv = new buffer;
    buffer *city_view_camera = new buffer;
    buffer *building_count_culture1 = new buffer;
    buffer *city_graph_order = new buffer;
    buffer *emperor_change_time = new buffer;
    buffer *empire = new buffer;
    buffer *empire_cities = new buffer;
    buffer *building_count_industry = new buffer;
    buffer *trade_prices = new buffer;
    buffer *figure_names = new buffer;
    buffer *culture_coverage = new buffer;
//    buffer *scenario = new buffer;

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

    scenario_data_buffers SCENARIO;

//    buffer *scenario_header = new buffer;
//        buffer *scenario_request_events = new buffer;
//        buffer *scenario_invasion_events = new buffer;
//    buffer *scenario_map_info1 = new buffer;
//        buffer *scenario_request_can_comply_dialogs = new buffer;
//    buffer *scenario_map_info2 = new buffer;
//        buffer *scenario_animal_herds = new buffer;
//        buffer *scenario_demands = new buffer;
//    buffer *scenario_random_events = new buffer;
//        buffer *scenario_fishing_spots = new buffer;
//        buffer *scenario_requests_extra = new buffer;
//    buffer *scenario_wheat_rome = new buffer;
//        buffer *scenario_allowed_buildings = new buffer;
//    buffer *scenario_win_criteria = new buffer;
//    buffer *scenario_map_points = new buffer;
//        buffer *scenario_invasion_points = new buffer;
//    buffer *scenario_river_entry = new buffer;
//    buffer *scenario_map_info3 = new buffer;
//    buffer *scenario_empire_info = new buffer;

    buffer *max_game_year = new buffer;
    buffer *earthquake = new buffer;
    buffer *emperor_change_state = new buffer;
    buffer *messages = new buffer;
    buffer *message_extra = new buffer;
    buffer *population_messages = new buffer;
    buffer *message_counts = new buffer;
    buffer *message_delays = new buffer;
    buffer *building_list_burning_totals = new buffer;
    buffer *figure_sequence = new buffer;
//    buffer *scenario_settings = new buffer;
    buffer *invasion_warnings = new buffer;
//    buffer *scenario_is_custom = new buffer;
    buffer *city_sounds = new buffer;
    buffer *building_highest_id = new buffer;
    buffer *figure_traders = new buffer;
    buffer *building_list_burning = new buffer;
    buffer *building_list_small = new buffer;
    buffer *building_list_large = new buffer;
    buffer *tutorial_part1 = new buffer;
    buffer *building_count_military = new buffer;
    buffer *enemy_army_totals = new buffer;
    buffer *building_storages = new buffer;
    buffer *building_count_culture2 = new buffer;
    buffer *building_count_support = new buffer;
    buffer *tutorial_part2 = new buffer;
    buffer *gladiator_revolt = new buffer;
    buffer *trade_route_limit = new buffer;
    buffer *trade_route_traded = new buffer;
    buffer *building_barracks_tower_sentry = new buffer;
    buffer *building_extra_sequence = new buffer;
    buffer *routing_counters = new buffer;
    buffer *building_count_culture3 = new buffer;
    buffer *enemy_armies = new buffer;
    buffer *city_entry_exit_xy = new buffer;
    buffer *last_invasion_id = new buffer;
    buffer *building_extra_corrupt_houses = new buffer;
//    buffer *scenario_name = new buffer;
    buffer *bookmarks = new buffer;
    buffer *tutorial_part3 = new buffer;
    buffer *empire_map_objects = new buffer;
    buffer *city_entry_exit_grid_offset = new buffer;
    buffer *floodplain_settings = new buffer;
    buffer *moisture_grid = new buffer;
    buffer *bizarre_ordered_fields_4 = new buffer;

    buffer *junk1 = new buffer;
    buffer *junk2a = new buffer;
    buffer *junk2b = new buffer;
    buffer *junk2c = new buffer;
    buffer *junk2d = new buffer;
    buffer *junk3 = new buffer;
    buffer *junk4a = new buffer;
    buffer *junk4b = new buffer;
    buffer *junk4c = new buffer;
    buffer *junk4d = new buffer;
    buffer *junk4e = new buffer;
    buffer *junk4f = new buffer;
    buffer *junk5 = new buffer;
    buffer *junk6a = new buffer;
    buffer *junk6b = new buffer;
    buffer *junk7a = new buffer;
    buffer *junk7b = new buffer;
//    buffer *junk7c = new buffer;
    buffer *junk8a = new buffer;
    buffer *junk8b = new buffer;
    buffer *junk8c = new buffer;
    buffer *junk9a = new buffer;
    buffer *junk9b = new buffer;
//    buffer *scenario_events = new buffer;
    buffer *junk10a = new buffer;
    buffer *junk10b = new buffer;
    buffer *junk10c = new buffer;
    buffer *junk10d = new buffer;
    buffer *junk10f = new buffer;
    buffer *junk11 = new buffer;
//    buffer *junk12 = new buffer;
    buffer *empire_map_routes = new buffer;
    buffer *junk14 = new buffer;
    buffer *bizarre_ordered_fields_1 = new buffer;
//    buffer *junk15 = new buffer;
    buffer *bizarre_ordered_fields_3 = new buffer;
    buffer *junk16 = new buffer;
    buffer *junk17 = new buffer;
    buffer *bizarre_ordered_fields_2 = new buffer;
    buffer *junk18 = new buffer;
    buffer *junk19 = new buffer;
    buffer *junk20 = new buffer;

    buffer *soil_fertility_grid = new buffer;
    buffer *GRID02_8BIT = new buffer;
    buffer *GRID03_32BIT = new buffer;
    buffer *soil_unk_grid = new buffer;
} savegame_state;

static struct {
    int num_pieces;
    file_piece pieces[200];
    savegame_state state;
} file_data = {0};

static void init_file_piece(file_piece *piece, int size, bool compressed) {
    piece->compressed = compressed;
    piece->buf = new buffer(size);
}
static buffer *create_scenario_piece(int size, const char *name) {
    file_piece *piece = &scenario_data.pieces[scenario_data.num_pieces++];
    init_file_piece(piece, size, 0);
    strncpy(piece->name, name, 99);
    return piece->buf;
}
static buffer *push_io_piece(int size, bool compressed, const char *name) {
    file_piece *piece = &file_data.pieces[file_data.num_pieces++];
    init_file_piece(piece, size, compressed);
    strncpy(piece->name, name, 99);
    return piece->buf;
}

static void init_scenario_data(void) {
    return;
    if (scenario_data.num_pieces > 0) {
        for (int i = 0; i < scenario_data.num_pieces; i++)
            file_data.pieces[i].buf->clear();
        return;
    }
    scenario_state *state = &scenario_data.state;
    state->graphic_ids = create_scenario_piece(52488, "");
    state->edge = create_scenario_piece(26244, "");
    state->terrain = create_scenario_piece(52488, "");
    state->bitfields = create_scenario_piece(26244, "");
    state->random = create_scenario_piece(26244, "");
    state->elevation = create_scenario_piece(26244, "");
    state->random_iv = create_scenario_piece(8, "");
    state->camera = create_scenario_piece(8, "");
//    state->scenario = create_scenario_piece(1720, "");
    state->SCENARIO.header = create_scenario_piece(14, "");
    state->SCENARIO.requests = create_scenario_piece(160, "");
    state->SCENARIO.invasions = create_scenario_piece(202, "");
    state->SCENARIO.info1 = create_scenario_piece(614, "");
    state->SCENARIO.request_comply_dialogs = create_scenario_piece(20, "");
    state->SCENARIO.info2 = create_scenario_piece(6, "");
    state->SCENARIO.herds = create_scenario_piece(16, "");
    state->SCENARIO.demands = create_scenario_piece(120, "");
    state->SCENARIO.price_changes = create_scenario_piece(120, "");
    state->SCENARIO.events = create_scenario_piece(44, "");
    state->SCENARIO.fishing_points = create_scenario_piece(32, "");
    state->SCENARIO.request_extra = create_scenario_piece(120, "");
    state->SCENARIO.wheat = create_scenario_piece(4, "");
    state->SCENARIO.allowed_builds = create_scenario_piece(100, "");
    state->SCENARIO.win_criteria = create_scenario_piece(52, "");
    state->SCENARIO.map_points = create_scenario_piece(12, "");
    state->SCENARIO.invasion_points = create_scenario_piece(32, "");
    state->SCENARIO.river_points = create_scenario_piece(8, "");
    state->SCENARIO.info3 = create_scenario_piece(32, "");
    state->SCENARIO.empire = create_scenario_piece(12, "");

    state->end_marker = create_scenario_piece(4, "");
}
static void init_file_data(int version1, int version2) {
    if (file_data.num_pieces > 0) {
        for (int i = 0; i < file_data.num_pieces; i++)
            file_data.pieces[i].buf->clear();
        file_data.num_pieces = 0;
    }
    savegame_state *state = &file_data.state;
    switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH: {
            state->SCENARIO.mission_index = push_io_piece(4, false, "SCENARIO.mission_index");
            state->file_version = push_io_piece(8, false, "file_version");
//                state->unk01 = create_savegame_piece(3, false, ""); // 3 bytes
            state->junk1 = push_io_piece(6000, false, "junk1"); // ?????

            state->image_grid = push_io_piece(207936, true, "image_grid");                         // (228²) * 4 <<
            state->edge_grid = push_io_piece(51984, true, "edge_grid");                            // (228²) * 1
            state->building_grid = push_io_piece(103968, true, "building_grid");                   // (228²) * 2
            state->terrain_grid = push_io_piece(207936, true, "terrain_grid");                     // (228²) * 4 <<
            state->aqueduct_grid = push_io_piece(51984, true, "aqueduct_grid");                    // (228²) * 1
            state->figure_grid = push_io_piece(103968, true, "figure_grid");                       // (228²) * 2
            state->bitfields_grid = push_io_piece(51984, true, "bitfields_grid");                  // (228²) * 1
            state->sprite_grid = push_io_piece(51984, true, "sprite_grid");                        // (228²) * 1
            state->random_grid = push_io_piece(51984, false, "random_grid");                            // (228²) * 1
            state->desirability_grid = push_io_piece(51984, true, "desirability_grid");            // (228²) * 1
            state->elevation_grid = push_io_piece(51984, true, "elevation_grid");                  // (228²) * 1
            state->building_damage_grid = push_io_piece(103968, true, "building_damage_grid");     // (228²) * 2 <<
            state->aqueduct_backup_grid = push_io_piece(51984, true, "aqueduct_backup_grid");      // (228²) * 1
            state->sprite_backup_grid = push_io_piece(51984, true, "sprite_backup_grid");          // (228²) * 1
            state->figures = push_io_piece(776000, true, "figures");
            state->route_figures = push_io_piece(2000, true, "route_figures");
            state->route_paths = push_io_piece(500000, true, "route_paths");
            state->formations = push_io_piece(7200, true, "formations");
            state->formation_totals = push_io_piece(12, false, "formation_totals");
            state->city_data = push_io_piece(37808, true, "city_data");
            state->city_faction_unknown = push_io_piece(4, false, "city_faction_unknown");
            state->SCENARIO.player_name = push_io_piece(64, false, "SCENARIO.player_name");
            state->city_faction = push_io_piece(4, false, "city_faction");
            state->buildings = push_io_piece(1056000, true, "buildings");
            state->city_view_orientation = push_io_piece(4, false, "city_view_orientation"); // ok
            state->game_time = push_io_piece(20, false, "game_time"); // ok
            state->building_highest_id_ever = push_io_piece(8, false, "building_extra_highest_id_ever"); // ok
            state->random_iv = push_io_piece(8, false, "random_iv"); // ok
            state->city_view_camera = push_io_piece(8, false, "city_view_camera"); // ok
//                state->building_count_culture1 = create_savegame_piece(132, false, ""); // MISSING
            state->city_graph_order = push_io_piece(8, false, "city_graph_order"); // I guess ????
//                state->emperor_change_time = create_savegame_piece(8, false, ""); // MISSING
            state->empire = push_io_piece(12, false, "empire"); // ok ???
            state->empire_cities = push_io_piece(6466, true, "empire_cities"); // 83920 + 7681 --> 91601
            state->building_count_industry = push_io_piece(288, false, "building_count_industry"); // 288 bytes ??????
            state->trade_prices = push_io_piece(288, false, "trade_prices");
            state->figure_names = push_io_piece(84, false, "figure_names");

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


            state->SCENARIO.header = push_io_piece(32, false, "SCENARIO.header");
            state->SCENARIO.info1 = push_io_piece(614, false, "SCENARIO.info1");
//                state->scenario_request_can_comply_dialogs = create_savegame_piece(20, false, ""); // MISSING
            state->SCENARIO.info2 = push_io_piece(6, false, "SCENARIO.info2");

            // 48 bytes     FF FF FF FF (non cyclic) ???
            // 44 bytes     00 00 00 00 ???
            // 64 bytes     FF FF FF FF (cyclic) invasion points???
            // 36 bytes     01 00 01 00 ???
            state->junk2a = push_io_piece(48, false, "junk2a"); // unknown bytes
            state->junk2b = push_io_piece(44, false, "junk2b"); // unknown bytes
            state->junk2c = push_io_piece(64, false, "junk2c"); // unknown bytes
            state->junk2d = push_io_piece(36, false, "junk2d"); // unknown bytes

            state->SCENARIO.win_criteria = push_io_piece(60, false, "SCENARIO.win_criteria");

            // 4 bytes     FF FF FF FF ???
            state->junk3 = push_io_piece(4, false, "junk3"); // unknown bytes

            state->city_entry_exit_xy = push_io_piece(8, false, "city_entry_exit_xy");

            // 40 bytes     FF FF FF FF (non cyclic?) ???
            // 4  bytes     B8 0B 00 00 ???
            // 12 bytes     0A 00 00 00 (3x4) ???
            // 12 bytes     CB 32 00 00 (3x4) ??? (n, n+2, n+1497)
            // 14 bytes     01 00 00 00 ???
            // 2  bytes     FF FF       ???
            state->junk4a = push_io_piece(40, false, "junk4a"); // unknown bytes
            state->junk4b = push_io_piece(4, false, "junk4b"); // unknown bytes
            state->junk4c = push_io_piece(12, false, "junk4c"); // unknown bytes
            state->junk4d = push_io_piece(12, false, "junk4d"); // unknown bytes
            state->SCENARIO.climate_id = push_io_piece(2, false, "SCENARIO.climate_id");
            state->junk4e = push_io_piece(10, false, "junk4e"); // unknown bytes
            state->junk4f = push_io_piece(2, false, "junk4f"); // unknown bytes
            state->junk4f = push_io_piece(2, false, "junk4g"); // unknown bytes
            state->SCENARIO.herds = push_io_piece(32, false, "SCENARIO.herds");
            state->SCENARIO.allowed_builds = push_io_piece(228, false, "SCENARIO.allowed_builds");

            // 24 bytes     FF FF FF FF (cyclic) ???
            state->junk5 = push_io_piece(28, false, "junk5"); // unknown bytes
            state->SCENARIO.monuments = push_io_piece(6, false, "SCENARIO.monuments"); // 3 x 2-byte

            // 290 bytes    00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            state->junk6a = push_io_piece(290, false, "junk6a"); // unknown bytes
            state->junk6b = push_io_piece(4 + 4 + 4, false, "junk6b"); // unknown bytes

            /////////////////////

//                state->max_game_year = create_savegame_piece(4, false, ""); // MISSING
//                state->earthquake = create_savegame_piece(60, false, ""); // MISSING
//                state->emperor_change_state = create_savegame_piece(4, false, ""); // MISSING

            state->messages = push_io_piece(48000, true, "messages"); // 94000 + 533 --> 94532 + 4 = 94536
            state->message_extra = push_io_piece(12, false, "message_extra"); // ok
            state->population_messages = push_io_piece(10, false, "population_messages"); // ok
            state->message_counts = push_io_piece(80, false, "message_counts"); // ok
            state->message_delays = push_io_piece(80, false, "message_delays"); // ok
            state->building_list_burning_totals = push_io_piece(8, false, "building_list_burning_totals"); // ok
            state->figure_sequence = push_io_piece(4, false, "figure_sequence"); // ok
            state->SCENARIO.map_settings = push_io_piece(12, false, "SCENARIO.map_settings"); // ok
            state->invasion_warnings = push_io_piece(3232, true, "invasion_warnings"); // 94743 + 31 --> 94774 + 4 = 94778
            state->SCENARIO.is_custom = push_io_piece(4, false, "SCENARIO.is_custom"); // ok
            state->city_sounds = push_io_piece(8960, false, "city_sounds"); // ok
            state->building_highest_id = push_io_piece(4, false, "building_extra_highest_id"); // ok
            state->figure_traders = push_io_piece(8804, false, "figure_traders"); // +4000 ???
            state->building_list_burning = push_io_piece(1000, true, "building_list_burning"); // ok
            state->building_list_small = push_io_piece(1000, true, "building_list_small"); // ok
            state->building_list_large = push_io_piece(8000, true, "building_list_large"); // ok

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
            state->junk7a = push_io_piece(32, false, "junk7a"); // unknown bytes
            state->junk7b = push_io_piece(24, false, "junk7b"); // unknown bytes
            state->building_storages = push_io_piece(39200, false, "building_storages"); // storage instructions

            state->trade_route_limit = push_io_piece(2880, true, "trade_route_limit"); // ok
            state->trade_route_traded = push_io_piece(2880, true, "trade_route_traded"); // ok

//                state->building_barracks_tower_sentry = create_savegame_piece(4, false, "");
//                state->building_extra_sequence = create_savegame_piece(4, false, "");
//                state->routing_counters = create_savegame_piece(16, false, "");
//                state->building_count_culture3 = create_savegame_piece(40, false, "");
//                state->enemy_armies = create_savegame_piece(900, false, "");

            // 12 bytes     00 00 00 00 ???
            // 16 bytes     00 00 00 00 ???
            // 22 bytes     00 00 00 00 ???
            state->junk8a = push_io_piece(12, false, "junk8a"); // unknown bytes
            state->junk8b = push_io_piece(16, false, "junk8b"); // unknown bytes
            state->junk8c = push_io_piece(22, false, "junk8c"); // unknown bytes

//                state->last_invasion_id = create_savegame_piece(2, false, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

            state->SCENARIO.map_name = push_io_piece(65, false, "SCENARIO.map_name"); // ok
            state->bookmarks = push_io_piece(32, false, "bookmarks"); // ok
            state->tutorial_part3 = push_io_piece(4, false, "tutorial_part3"); // ok ????

            int t_sub = 228;

            // 8 bytes      00 00 00 00 ???
            state->junk9a = push_io_piece(8, false, "junk9a");
            state->junk9b = push_io_piece(396, false, "junk9b");

            // 51984 bytes  00 00 00 00 ???
            state->soil_fertility_grid = push_io_piece(51984, false, "soil_fertility_grid");


            // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
            state->SCENARIO.events_ph = push_io_piece(18600, false, "SCENARIO.events_ph");

            // 28 bytes     2F 01 00 00 ???
            // 13416 bytes  00 00 00 00 ??? (200 less for non-expanded file)
            // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
            state->junk10a = push_io_piece(28, false, "junk10a");
            state->junk10b = push_io_piece(13216, false, "junk10b");
            if (version1 >= 149)
                state->junk10c = push_io_piece(200, false, "junk10c");
            state->junk10d = push_io_piece(8200, false, "junk10d");

//            if (version1 < 160)
            state->junk11 = push_io_piece(1280, true, "junk11"); // unknown compressed data
            if (version1 >= 160)
//                if (version2 == FILE_SAVEGAME)
                    state->empire_map_objects = push_io_piece(19600, true, "empire_state_objects"); // unknown compressed data
//                else
//                    state->junk11 = push_io_piece(1280, true, "junk11"); // unknown compressed data
            else
                state->empire_map_objects = push_io_piece(15200, true, "empire_state_objects"); // unknown compressed data
            state->empire_map_routes = push_io_piece(16200, true, "junk13"); // unknown compressed data

            // 51984 bytes  FF FF FF FF ???          // (228²) * 1 ?????????????????
            state->GRID02_8BIT = push_io_piece(51984, false, "GRID02_8BIT"); // todo: 1-byte grid

            // 20 bytes     19 00 00 00 ???
            state->junk14 = push_io_piece(20, false, "junk14");

            // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
            state->bizarre_ordered_fields_1 = push_io_piece(528, false, "bizarre_ordered_fields_1");

            state->floodplain_settings = push_io_piece(36, true, "floodplain_settings"); // floodplain_settings
            state->GRID03_32BIT = push_io_piece(207936, true, "GRID03_32BIT"); // todo: 4-byte grid

            // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
            state->bizarre_ordered_fields_3 = push_io_piece(312 , false, "bizarre_ordered_fields_3"); // 71x 4-bytes emptiness

            // 64 bytes     00 00 00 00 ???
            state->junk16 = push_io_piece(64, false, "junk16"); // 71x 4-bytes emptiness
            state->tutorial_part1 = push_io_piece(41, false, "tutorial_part1"); // 41 x 1-byte flag fields
            state->soil_unk_grid = push_io_piece(51984, true, "floodplain_soil_depletion");

            // lone byte ???
            state->junk17 = push_io_piece(1, false, "junk17");
            state->moisture_grid = push_io_piece(51984, true, "moisture_grid");

            // 672 bytes    0F 00 00 00 ??? 28 x 24-byte chunk
            state->bizarre_ordered_fields_2 = push_io_piece(672, false, "bizarre_ordered_fields_2");

            // 20 bytes     00 00 00 00 ???
            // 4800 bytes   00 00 00 00 ???
            state->junk18 = push_io_piece(20, false, "junk18");
            state->bizarre_ordered_fields_4 = push_io_piece(4800, false, "bizarre_ordered_fields_4");

            break;
        }
    }
}

static void scenario_load_from_state(scenario_state *state) {
    map_image_load_state(state->graphic_ids);
    map_terrain_load_state(state->terrain);
    map_property_load_state(state->bitfields, state->edge);
    map_random_load_state(state->random);
    map_elevation_load_state(state->elevation);
    city_view_load_scenario_state(state->camera);

    random_load_state(state->random_iv);

    scenario_load_state(&state->SCENARIO);

//    file->end_marker->skip(4);
}
static void scenario_save_to_state(scenario_state *state) {
    map_image_save_state(state->graphic_ids);
    map_terrain_save_state(state->terrain);
    map_property_save_state(state->bitfields, state->edge);
    map_random_save_state(state->random);
    map_elevation_save_state(state->elevation);
    city_view_save_scenario_state(state->camera);

    random_save_state(state->random_iv);

    scenario_save_state(&state->SCENARIO);

//    file->end_marker->skip(4);
}
static void savegame_load_from_state(savegame_state *state) {
    savegame_version[0] = state->file_version->read_i32();
    savegame_version[1] = state->file_version->read_i32();

    scenario_load_state(&state->SCENARIO);

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
static void savegame_save_to_state(savegame_state *state) {
    state->file_version->write_i32(savegame_version[0]);

    scenario_save_state(&state->SCENARIO);
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

void log_hex(file_piece *piece, int i, int offs) {
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
    SDL_Log("Piece %s %03i/%i : %8i@ %-36s(%" PRI_SIZET ") %s", piece->compressed ? "(C)" : "---", i + 1, file_data.num_pieces,
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
static int savegame_read_from_file(FILE *fp) {
    for (int i = 0; i < file_data.num_pieces; i++) {
        file_piece *piece = &file_data.pieces[i];
        findex = i;
        fname = piece->name;
        int result = 0;

        auto offs = ftell(fp);

        if (piece->compressed)
            result = read_compressed_chunk(fp, piece->buf, piece->buf->size());
        else
            result = piece->buf->from_file(piece->buf->size(), fp) == piece->buf->size();

        // export uncompressed buffer data to zip folder for debugging
        char *lfile = (char *) malloc(200);
        sprintf(lfile, "DEV_TESTING/zip/%03i_%i_%s", findex + 1, piece->buf->size(), fname);
        FILE *log = fopen(lfile, "wb+");
        if (log)
            fwrite(piece->buf->get_data(), piece->buf->size(), 1, log);
        fclose(log);
        free(lfile);

        ///

        log_hex(piece, i, offs);

        // The last piece may be smaller than buf->size
        if (!result && i != (file_data.num_pieces - 1)) {
//            SDL_Log("Incorrect buffer size, expected %i, found %i", piece->buf->size());
            return 0;
        }
    }
    return 1;
}
static void savegame_write_to_file(FILE *fp) {
    for (int i = 0; i < file_data.num_pieces; i++) {
        file_piece *piece = &file_data.pieces[i];
        if (piece->compressed)
            write_compressed_chunk(fp, piece->buf, piece->buf->size());
        else
            piece->buf->to_file(piece->buf->size(), fp);
    }
}

static buffer *version_buffer = new buffer(8);
static int get_file_version1(const char *filename, int offset) {
    version_buffer->clear();
    if (!io_read_file_part_into_buffer(filename, NOT_LOCALIZED, version_buffer, 8, offset))
        return 0;
    return version_buffer->read_i32();
}
static int get_file_version2(const char *filename, int offset) {
    version_buffer->clear();
    if (!io_read_file_part_into_buffer(filename, NOT_LOCALIZED, version_buffer, 8, offset))
        return 0;
    version_buffer->skip(4);
    return version_buffer->read_i32();
}
bool game_file_io_read_scenario(const char *filename) {
    // TODO
    return false;

    init_scenario_data();
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to access file", filename, 0);
        return false;
    }
    log_info("Loading scenario", filename, 0);
    for (int i = 0; i < scenario_data.num_pieces; i++) {
        int bytes_read = scenario_data.pieces[i].buf->from_file((size_t) scenario_data.pieces[i].buf->size(), fp);
        if (bytes_read != scenario_data.pieces[i].buf->size()) {
            log_error("Unable to load scenario", filename, 0);
            file_close(fp);
            return false;
        }

//        if (fread(scenario_data.pieces[i].buf->data, 1, scenario_data.pieces[i].buf->size, fp) != scenario_data.pieces[i].buf->size) {
//            log_error("Unable to load scenario", filename, 0);
//            file_close(fp);
//            return 0;
//        }
    }
    file_close(fp);

    scenario_load_from_state(&scenario_data.state);
    return true;
}
bool game_file_io_write_scenario(const char *filename) {
    // TODO
    return false;
//    log_info("Saving scenario", filename, 0);
//    init_scenario_data();
//    scenario_save_to_state(&scenario_data.state);
//
//    FILE *fp = file_open(filename, "wb");
//    if (!fp) {
//        log_error("Unable to save scenario", 0, 0);
//        return 0;
//    }
//    for (int i = 0; i < scenario_data.num_pieces; i++) {
//        fwrite(scenario_data.pieces[i].buf->data, 1, scenario_data.pieces[i].buf->size, fp);
//    }
//    file_close(fp);
//    return 1;
}
bool game_file_io_read_saved_game(const char *filename, int offset) {

    int file_version1 = get_file_version1(filename, offset + 4);
    int file_version2 = get_file_version2(filename, offset + 4);
    SDL_Log("FILE VERSION: %i TYPE: %i", file_version1, file_version2);
    init_file_data(file_version1, file_version2);

    if (file_has_extension(filename, "pak") && file_version1 == 147) {
        log_info("Loading saved game.", filename, 0);
        terrain_ph_offset = 539; //14791
    } else {
        log_info("Loading saved game (expanded).", filename, 0);
        terrain_ph_offset = 0; //14252
    }

    log_info("Loading saved game", filename, 0);
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        return false;
    }
    if (offset)
        fseek(fp, offset, SEEK_SET);

    int result = savegame_read_from_file(fp);
    file_close(fp);
    if (!result) {
        log_error("Unable to load game, unable to read savefile.", 0, 0);
        return false;
    }
    savegame_load_from_state(&file_data.state);
    return true;
}
bool game_file_io_write_saved_game(const char *filename) {
    init_file_data(0, 0);

    log_info("Saving game", filename, 0);
//    savegame_version = SAVE_GAME_VERSION;
    savegame_save_to_state(&file_data.state);

    FILE *fp = file_open(filename, "wb");
    if (!fp) {
        log_error("Unable to save game", 0, 0);
        return false;
    }
    savegame_write_to_file(fp);
    file_close(fp);
    return true;
}
bool game_file_io_delete_saved_game(const char *filename) {
    log_info("Deleting game", filename, 0);
    int result = file_remove(filename);
    if (!result)
        log_error("Unable to delete game", 0, 0);

    return result;
}
