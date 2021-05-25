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

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

//static const int SAVE_GAME_VERSION = 0x76;

static char compress_buffer[COMPRESS_BUFFER_SIZE];

static int savegame_version;

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
    scenario_data_buffers scenario_data;
    buffer *end_marker = new buffer;
} scenario_state;

static struct {
    int num_pieces;
    file_piece pieces[10];
    scenario_state state;
} scenario_data = {0};

typedef struct {
    buffer *scenario_campaign_mission = new buffer;
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
    buffer *player_name = new buffer;
    buffer *city_faction = new buffer;
    buffer *buildings = new buffer;
    buffer *city_view_orientation = new buffer;
    buffer *game_time = new buffer;
    buffer *building_extra_highest_id_ever = new buffer;
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

    scenario_data_buffers scenario_data;

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
    buffer *scenario_settings = new buffer;
    buffer *invasion_warnings = new buffer;
    buffer *scenario_is_custom = new buffer;
    buffer *city_sounds = new buffer;
    buffer *building_extra_highest_id = new buffer;
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
    buffer *scenario_name = new buffer;
    buffer *bookmarks = new buffer;
    buffer *tutorial_part3 = new buffer;
    buffer *empire_map_objects = new buffer;
    buffer *city_entry_exit_grid_offset = new buffer;
    buffer *floodplain_settings = new buffer;
    buffer *moisture_grid = new buffer;
    buffer *end_marker = new buffer;

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
    buffer *junk7c = new buffer;
    buffer *junk8a = new buffer;
    buffer *junk8b = new buffer;
    buffer *junk8c = new buffer;
    buffer *junk9 = new buffer;
    buffer *junk10a = new buffer;
    buffer *junk10b = new buffer;
    buffer *junk10c = new buffer;
    buffer *junk10d = new buffer;
    buffer *junk10e = new buffer;
    buffer *junk11 = new buffer;
//    buffer *junk12 = new buffer;
    buffer *junk13 = new buffer;
    buffer *junk14a = new buffer;
    buffer *junk14b = new buffer;
//    buffer *junk15 = new buffer;
    buffer *junk16a = new buffer;
    buffer *junk16b = new buffer;
    buffer *junk17 = new buffer;
    buffer *junk18a = new buffer;
    buffer *junk18b = new buffer;
    buffer *junk19 = new buffer;
    buffer *junk20 = new buffer;

    buffer *GRID01_8BIT = new buffer;
    buffer *GRID02_8BIT = new buffer;
    buffer *GRID03_32BIT = new buffer;
    buffer *GRID04_8BIT = new buffer;
} savegame_state;

static struct {
    int num_pieces;
    file_piece pieces[200];
    savegame_state state;
} savegame_data = {0};

static void init_file_piece(file_piece *piece, int size, int compressed) {
    piece->compressed = compressed;
    piece->buf = new buffer(size);
}
static buffer *create_scenario_piece(int size, const char *name) {
    file_piece *piece = &scenario_data.pieces[scenario_data.num_pieces++];
    init_file_piece(piece, size, 0);
    strncpy(piece->name, name, 99);
    return piece->buf;
}
static buffer *create_savegame_piece(int size, int compressed, const char *name) {
    file_piece *piece = &savegame_data.pieces[savegame_data.num_pieces++];
    init_file_piece(piece, size, compressed);
    strncpy(piece->name, name, 99);
    return piece->buf;
}

static void init_scenario_data(void) {
    return;
    if (scenario_data.num_pieces > 0) {
        for (int i = 0; i < scenario_data.num_pieces; i++)
            savegame_data.pieces[i].buf->clear();
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
    state->scenario_data.header = create_scenario_piece(14, "");
    state->scenario_data.requests = create_scenario_piece(160, "");
    state->scenario_data.invasions = create_scenario_piece(202, "");
    state->scenario_data.info1 = create_scenario_piece(614, "");
    state->scenario_data.request_comply_dialogs = create_scenario_piece(20, "");
    state->scenario_data.info2 = create_scenario_piece(6, "");
    state->scenario_data.herds = create_scenario_piece(16, "");
    state->scenario_data.demands = create_scenario_piece(120, "");
    state->scenario_data.price_changes = create_scenario_piece(120, "");
    state->scenario_data.events = create_scenario_piece(44, "");
    state->scenario_data.fishing_points = create_scenario_piece(32, "");
    state->scenario_data.request_extra = create_scenario_piece(120, "");
    state->scenario_data.wheat = create_scenario_piece(4, "");
    state->scenario_data.allowed_builds = create_scenario_piece(100, "");
    state->scenario_data.win_criteria = create_scenario_piece(52, "");
    state->scenario_data.map_points = create_scenario_piece(12, "");
    state->scenario_data.invasion_points = create_scenario_piece(32, "");
    state->scenario_data.river_points = create_scenario_piece(8, "");
    state->scenario_data.info3 = create_scenario_piece(32, "");
    state->scenario_data.empire = create_scenario_piece(12, "");

    state->end_marker = create_scenario_piece(4, "");
}
static void init_savegame_data(int expanded) {
    if (savegame_data.num_pieces > 0) {
        for (int i = 0; i < savegame_data.num_pieces; i++)
            savegame_data.pieces[i].buf->clear();
        savegame_data.num_pieces = 0;
    }
    savegame_state *state = &savegame_data.state;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3: {
            state->scenario_campaign_mission = create_savegame_piece(4, 0, "scenario_campaign_mission");
            state->file_version = create_savegame_piece(4, 0, "file_version");
            state->image_grid = create_savegame_piece(52488, 1, "image_grid");
            state->edge_grid = create_savegame_piece(26244, 1, "edge_grid");
            state->building_grid = create_savegame_piece(52488, 1, "building_grid");
            state->terrain_grid = create_savegame_piece(52488, 1, "terrain_grid");
            state->aqueduct_grid = create_savegame_piece(26244, 1, "aqueduct_grid");
            state->figure_grid = create_savegame_piece(52488, 1, "figure_grid");
            state->bitfields_grid = create_savegame_piece(26244, 1, "bitfields_grid");
            state->sprite_grid = create_savegame_piece(26244, 1, "sprite_grid");
            state->random_grid = create_savegame_piece(26244, 0, "random_grid");
            state->desirability_grid = create_savegame_piece(26244, 1, "desirability_grid");
            state->elevation_grid = create_savegame_piece(26244, 1, "elevation_grid");
            state->building_damage_grid = create_savegame_piece(26244, 1, "building_damage_grid");
            state->aqueduct_backup_grid = create_savegame_piece(26244, 1, "aqueduct_backup_grid");
            state->sprite_backup_grid = create_savegame_piece(26244, 1, "sprite_backup_grid");
            if (expanded) {
                state->figures = create_savegame_piece(640000, 1, "figures");
                state->route_figures = create_savegame_piece(6000, 1, "route_figures");
                state->route_paths = create_savegame_piece(1500000, 1, "route_paths");
                state->formations = create_savegame_piece(32000, 1, "formations");
            } else {
                state->figures = create_savegame_piece(128000, 1, "figures");
                state->route_figures = create_savegame_piece(1200, 1, "route_figures");
                state->route_paths = create_savegame_piece(300000, 1, "route_paths");
                state->formations = create_savegame_piece(6400, 1, "formations");
            }
            state->formation_totals = create_savegame_piece(12, 0, "formation_totals");
            state->city_data = create_savegame_piece(36136, 1, "city_data");
            state->city_faction_unknown = create_savegame_piece(2, 0, "city_faction_unknown");
            state->player_name = create_savegame_piece(64, 0, "player_name");
            state->city_faction = create_savegame_piece(4, 0, "city_faction");
            if (expanded)
                state->buildings = create_savegame_piece(1280000, 1, "buildings");
            else
                state->buildings = create_savegame_piece(256000, 1, "buildings");
            state->city_view_orientation = create_savegame_piece(4, 0, "city_view_orientation");
            state->game_time = create_savegame_piece(20, 0, "game_time");
            state->building_extra_highest_id_ever = create_savegame_piece(8, 0, "building_extra_highest_id_ever");
            state->random_iv = create_savegame_piece(8, 0, "random_iv");
            state->city_view_camera = create_savegame_piece(8, 0, "city_view_camera");
            state->building_count_culture1 = create_savegame_piece(132, 0, "building_count_culture1");
            state->city_graph_order = create_savegame_piece(8, 0, "city_graph_order");
            state->emperor_change_time = create_savegame_piece(8, 0, "emperor_change_time");
            state->empire = create_savegame_piece(12, 0, "empire");
            state->empire_cities = create_savegame_piece(2706, 1, "empire_cities");
            state->building_count_industry = create_savegame_piece(128, 0, "building_count_industry");
            state->trade_prices = create_savegame_piece(128, 0, "trade_prices");
            state->figure_names = create_savegame_piece(84, 0, "figure_names");
            state->culture_coverage = create_savegame_piece(60, 0, "culture_coverage");
            //    state->scenario = create_savegame_piece(1720, 0, "");
            state->scenario_data.header = create_savegame_piece(14, 0, "header");
            state->scenario_data.requests = create_savegame_piece(160, 0, "requests");
            state->scenario_data.invasions = create_savegame_piece(202, 0, "invasions");
            state->scenario_data.info1 = create_savegame_piece(614, 0, "info1");
            state->scenario_data.request_comply_dialogs = create_savegame_piece(20, 0, "request_comply_dialogs");
            state->scenario_data.info2 = create_savegame_piece(6, 0, "info2");
            state->scenario_data.herds = create_savegame_piece(16, 0, "herds");
            state->scenario_data.demands = create_savegame_piece(120, 0, "demands");
            state->scenario_data.price_changes = create_savegame_piece(120, 0, "price_changes");
            state->scenario_data.events = create_savegame_piece(44, 0, "events");
            state->scenario_data.fishing_points = create_savegame_piece(32, 0, "fishing_points");
            state->scenario_data.request_extra = create_savegame_piece(120, 0, "request_extra");
            state->scenario_data.wheat = create_savegame_piece(4, 0, "wheat");
            state->scenario_data.allowed_builds = create_savegame_piece(100, 0, "allowed_builds");
            state->scenario_data.win_criteria = create_savegame_piece(52, 0, "win_criteria");
            state->scenario_data.map_points = create_savegame_piece(12, 0, "map_points");
            state->scenario_data.invasion_points = create_savegame_piece(32, 0, "invasion_points");
            state->scenario_data.river_points = create_savegame_piece(8, 0, "river_points");
            state->scenario_data.info3 = create_savegame_piece(32, 0, "info3");
            state->scenario_data.empire = create_savegame_piece(12, 0, "empire");

            state->max_game_year = create_savegame_piece(4, 0, "max_game_year");
            state->earthquake = create_savegame_piece(60, 0, "earthquake");
            state->emperor_change_state = create_savegame_piece(4, 0, "emperor_change_state");
            state->messages = create_savegame_piece(16000, 1, "messages");
            state->message_extra = create_savegame_piece(12, 0, "message_extra");
            state->population_messages = create_savegame_piece(10, 0, "population_messages");
            state->message_counts = create_savegame_piece(80, 0, "message_counts");
            state->message_delays = create_savegame_piece(80, 0, "message_delays");
            state->building_list_burning_totals = create_savegame_piece(8, 0, "building_list_burning_totals");
            state->figure_sequence = create_savegame_piece(4, 0, "figure_sequence");
            state->scenario_settings = create_savegame_piece(12, 0, "scenario_settings");
            state->invasion_warnings = create_savegame_piece(3232, 1, "invasion_warnings");
            state->scenario_is_custom = create_savegame_piece(4, 0, "scenario_is_custom");
            state->city_sounds = create_savegame_piece(8960, 0, "city_sounds");
            state->building_extra_highest_id = create_savegame_piece(4, 0, "building_extra_highest_id");
            state->figure_traders = create_savegame_piece(4804, 0, "figure_traders");
            if (expanded) {
                state->building_list_burning = create_savegame_piece(5000, 1, "building_list_burning");
                state->building_list_small = create_savegame_piece(5000, 1, "building_list_small");
                state->building_list_large = create_savegame_piece(20000, 1, "building_list_large");
            } else {
                state->building_list_burning = create_savegame_piece(1000, 1, "building_list_burning");
                state->building_list_small = create_savegame_piece(1000, 1, "building_list_small");
                state->building_list_large = create_savegame_piece(4000, 1, "building_list_large");
            }
            state->tutorial_part1 = create_savegame_piece(32, 0, "tutorial_part1");
            state->building_count_military = create_savegame_piece(16, 0, "building_count_military");
            state->enemy_army_totals = create_savegame_piece(20, 0, "enemy_army_totals");
            if (expanded)
                state->building_storages = create_savegame_piece(32000, 0, "building_storages");
            else
                state->building_storages = create_savegame_piece(6400, 0, "building_storages");
            state->building_count_culture2 = create_savegame_piece(32, 0, "building_count_culture2");
            state->building_count_support = create_savegame_piece(24, 0, "building_count_support");
            state->tutorial_part2 = create_savegame_piece(4, 0, "tutorial_part2");
            state->gladiator_revolt = create_savegame_piece(16, 0, "gladiator_revolt");
            state->trade_route_limit = create_savegame_piece(1280, 1, "trade_route_limit");
            state->trade_route_traded = create_savegame_piece(1280, 1, "trade_route_traded");
            state->building_barracks_tower_sentry = create_savegame_piece(4, 0, "building_barracks_tower_sentry");
            state->building_extra_sequence = create_savegame_piece(4, 0, "building_extra_sequence");
            state->routing_counters = create_savegame_piece(16, 0, "routing_counters");
            state->building_count_culture3 = create_savegame_piece(40, 0, "building_count_culture3");
            state->enemy_armies = create_savegame_piece(900, 0, "enemy_armies");
            state->city_entry_exit_xy = create_savegame_piece(16, 0, "city_entry_exit_xy");
            state->last_invasion_id = create_savegame_piece(2, 0, "last_invasion_id");
            state->building_extra_corrupt_houses = create_savegame_piece(8, 0, "building_extra_corrupt_houses");
            state->scenario_name = create_savegame_piece(65, 0, "scenario_name");
            state->bookmarks = create_savegame_piece(32, 0, "bookmarks");
            state->tutorial_part3 = create_savegame_piece(4, 0, "tutorial_part3");
            state->city_entry_exit_grid_offset = create_savegame_piece(8, 0, "city_entry_exit_grid_offset");
            state->end_marker = create_savegame_piece(284, 0, "end_marker"); // 71x 4-bytes emptiness
            break;
        }
        case ENGINE_ENV_PHARAOH: {
            state->scenario_campaign_mission = create_savegame_piece(1, 0, "scenario_campaign_mission");

//                state->file_version = create_savegame_piece(4, 0, "");
//                state->unk01 = create_savegame_piece(3, 0, ""); // 3 bytes
            state->junk1 = create_savegame_piece(6011, 0, "junk1"); // ?????

            state->image_grid = create_savegame_piece(207936, 1, "image_grid");                         // (228²) * 4 <<
            state->edge_grid = create_savegame_piece(51984, 1, "edge_grid");                            // (228²) * 1
            state->building_grid = create_savegame_piece(103968, 1, "building_grid");                   // (228²) * 2
            state->terrain_grid = create_savegame_piece(207936, 1, "terrain_grid");                     // (228²) * 4 <<
            state->aqueduct_grid = create_savegame_piece(51984, 1, "aqueduct_grid");                    // (228²) * 1
            state->figure_grid = create_savegame_piece(103968, 1, "figure_grid");                       // (228²) * 2
            state->bitfields_grid = create_savegame_piece(51984, 1, "bitfields_grid");                  // (228²) * 1
            state->sprite_grid = create_savegame_piece(51984, 1, "sprite_grid");                        // (228²) * 1
            state->random_grid = create_savegame_piece(51984, 0, "random_grid");                            // (228²) * 1
            state->desirability_grid = create_savegame_piece(51984, 1, "desirability_grid");            // (228²) * 1
            state->elevation_grid = create_savegame_piece(51984, 1, "elevation_grid");                  // (228²) * 1
            state->building_damage_grid = create_savegame_piece(103968, 1, "building_damage_grid");     // (228²) * 2 <<
            state->aqueduct_backup_grid = create_savegame_piece(51984, 1, "aqueduct_backup_grid");      // (228²) * 1
            state->sprite_backup_grid = create_savegame_piece(51984, 1, "sprite_backup_grid");          // (228²) * 1
            state->figures = create_savegame_piece(776000, 1, "figures");
            state->route_figures = create_savegame_piece(2000, 1, "route_figures");
            state->route_paths = create_savegame_piece(500000, 1, "route_paths");
            state->formations = create_savegame_piece(7200, 1, "formations");
            state->formation_totals = create_savegame_piece(12, 0, "formation_totals");
            state->city_data = create_savegame_piece(37808, 1, "city_data");
            state->city_faction_unknown = create_savegame_piece(4, 0, "city_faction_unknown");
            state->player_name = create_savegame_piece(64, 0, "player_name");
            state->city_faction = create_savegame_piece(4, 0, "city_faction");
            state->buildings = create_savegame_piece(1056000, 1, "buildings");
            state->city_view_orientation = create_savegame_piece(4, 0, "city_view_orientation"); // ok
            state->game_time = create_savegame_piece(20, 0, "game_time"); // ok
            state->building_extra_highest_id_ever = create_savegame_piece(8, 0, "building_extra_highest_id_ever"); // ok
            state->random_iv = create_savegame_piece(8, 0, "random_iv"); // ok
            state->city_view_camera = create_savegame_piece(8, 0, "city_view_camera"); // ok
//                state->building_count_culture1 = create_savegame_piece(132, 0, ""); // MISSING
            state->city_graph_order = create_savegame_piece(8, 0, "city_graph_order"); // I guess ????
//                state->emperor_change_time = create_savegame_piece(8, 0, ""); // MISSING
            state->empire = create_savegame_piece(12, 0, "empire"); // ok ???
            state->empire_cities = create_savegame_piece(6466, 1, "empire_cities"); // 83920 + 7681 --> 91601
            state->building_count_industry = create_savegame_piece(288, 0, "building_count_industry"); // 288 bytes ??????
            state->trade_prices = create_savegame_piece(288, 0, "trade_prices");
            state->figure_names = create_savegame_piece(84, 0, "figure_names");

//                state->culture_coverage = create_savegame_piece(60, 0, ""); // MISSING
//                state->scenario = create_savegame_piece(1720, 0, ""); // MISSING
            state->scenario_data.header = create_savegame_piece(32, 0, "scenario_data.header");
            state->scenario_data.info1 = create_savegame_piece(614, 0, "scenario_data.info1");
//                state->scenario_request_can_comply_dialogs = create_savegame_piece(20, 0, ""); // MISSING
            state->scenario_data.info2 = create_savegame_piece(6, 0, "scenario_data.info2");

            // 48 bytes     FF FF FF FF (non cyclic) ???
            // 44 bytes     00 00 00 00 ???
            // 64 bytes     FF FF FF FF (cyclic) invasion points???
            // 36 bytes     01 00 01 00 ???
            state->junk2a = create_savegame_piece(48, 0, "junk2a"); // unknown bytes
            state->junk2b = create_savegame_piece(44, 0, "junk2b"); // unknown bytes
            state->junk2c = create_savegame_piece(64, 0, "junk2c"); // unknown bytes
            state->junk2d = create_savegame_piece(36, 0, "junk2d"); // unknown bytes

            state->scenario_data.win_criteria = create_savegame_piece(60, 0, "scenario_data.win_criteria");

            // 4 bytes     FF FF FF FF ???
            state->junk3 = create_savegame_piece(4, 0, "junk3"); // unknown bytes

            state->city_entry_exit_xy = create_savegame_piece(8, 0, "city_entry_exit_xy");

            // 40 bytes     FF FF FF FF (non cyclic?) ???
            // 4  bytes     B8 0B 00 00 ???
            // 12 bytes     0A 00 00 00 (3x4) ???
            // 12 bytes     CB 32 00 00 (3x4) ??? (n, n+2, n+1497)
            // 14 bytes     01 00 00 00 ???
            // 2  bytes     FF FF       ???
            state->junk4a = create_savegame_piece(40, 0, "junk4a"); // unknown bytes
            state->junk4b = create_savegame_piece(4, 0, "junk4b"); // unknown bytes
            state->junk4c = create_savegame_piece(12, 0, "junk4c"); // unknown bytes
            state->junk4d = create_savegame_piece(12, 0, "junk4d"); // unknown bytes
            state->junk4e = create_savegame_piece(14, 0, "junk4e"); // unknown bytes
            state->junk4f = create_savegame_piece(2, 0, "junk4f"); // unknown bytes
            state->scenario_data.herds = create_savegame_piece(32, 0, "scenario_data.herds");
            state->scenario_data.allowed_builds = create_savegame_piece(228, 0, "scenario_data.allowed_builds");

            // 24 bytes     FF FF FF FF (cyclic) ???
            state->junk5 = create_savegame_piece(24, 0, "junk5"); // unknown bytes
            state->scenario_data.monuments = create_savegame_piece(10, 0, "scenario_data.monuments"); // 4 bytes + 3 x 2-byte

            // 290 bytes    00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            // 4 bytes      00 00 00 00 ???
            state->junk6a = create_savegame_piece(290, 0, "junk6a"); // unknown bytes
            state->junk6b = create_savegame_piece(4 + 4 + 4, 0, "junk6b"); // unknown bytes

            /////////////////////

//                state->max_game_year = create_savegame_piece(4, 0, ""); // MISSING
//                state->earthquake = create_savegame_piece(60, 0, ""); // MISSING
//                state->emperor_change_state = create_savegame_piece(4, 0, ""); // MISSING

            state->messages = create_savegame_piece(48000, 1, "messages"); // 94000 + 533 --> 94532 + 4 = 94536
            state->message_extra = create_savegame_piece(12, 0, "message_extra"); // ok
            state->population_messages = create_savegame_piece(10, 0, "population_messages"); // ok
            state->message_counts = create_savegame_piece(80, 0, "message_counts"); // ok
            state->message_delays = create_savegame_piece(80, 0, "message_delays"); // ok
            state->building_list_burning_totals = create_savegame_piece(8, 0, "building_list_burning_totals"); // ok
            state->figure_sequence = create_savegame_piece(4, 0, "figure_sequence"); // ok
            state->scenario_settings = create_savegame_piece(12, 0, "scenario_settings"); // ok
            state->invasion_warnings = create_savegame_piece(3232, 1, "invasion_warnings"); // 94743 + 31 --> 94774 + 4 = 94778
            state->scenario_is_custom = create_savegame_piece(4, 0, "scenario_is_custom"); // ok
            state->city_sounds = create_savegame_piece(8960, 0, "city_sounds"); // ok
            state->building_extra_highest_id = create_savegame_piece(4, 0, "building_extra_highest_id"); // ok
            state->figure_traders = create_savegame_piece(8804, 0, "figure_traders"); // +4000 ???
            state->building_list_burning = create_savegame_piece(1000, 1, "building_list_burning"); // ok
            state->building_list_small = create_savegame_piece(1000, 1, "building_list_small"); // ok
            state->building_list_large = create_savegame_piece(8000, 1, "building_list_large"); // ok

//                state->tutorial_part1 = create_savegame_piece(32, 0, "");
//                state->building_count_military = create_savegame_piece(16, 0, "");
//                state->enemy_army_totals = create_savegame_piece(20, 0, "");
//                state->building_storages = create_savegame_piece(6400, 0, "");
//                state->building_count_culture2 = create_savegame_piece(32, 0, "");
//                state->building_count_support = create_savegame_piece(24, 0, "");
//                state->tutorial_part2 = create_savegame_piece(4, 0, "");
//                state->gladiator_revolt = create_savegame_piece(16, 0, "");

            // 32 bytes     00 00 00 00 ???
            // 24 bytes     00 00 00 00 ???
            // 39200 bytes  00 00 00 00 ??? 200 x 196-byte chunk
            state->junk7a = create_savegame_piece(32, 0, "junk7a"); // unknown bytes
            state->junk7b = create_savegame_piece(24, 0, "junk7b"); // unknown bytes
            state->junk7c = create_savegame_piece(39200, 0, "junk7c"); // unknown bytes

            state->trade_route_limit = create_savegame_piece(2880, 1, "trade_route_limit"); // ok
            state->trade_route_traded = create_savegame_piece(2880, 1, "trade_route_traded"); // ok

//                state->building_barracks_tower_sentry = create_savegame_piece(4, 0, "");
//                state->building_extra_sequence = create_savegame_piece(4, 0, "");
//                state->routing_counters = create_savegame_piece(16, 0, "");
//                state->building_count_culture3 = create_savegame_piece(40, 0, "");
//                state->enemy_armies = create_savegame_piece(900, 0, "");

            // 12 bytes     00 00 00 00 ???
            // 16 bytes     00 00 00 00 ???
            // 22 bytes     00 00 00 00 ???
            state->junk8a = create_savegame_piece(12, 0, "junk8a"); // unknown bytes
            state->junk8b = create_savegame_piece(16, 0, "junk8b"); // unknown bytes
            state->junk8c = create_savegame_piece(22, 0, "junk8c"); // unknown bytes

//                state->last_invasion_id = create_savegame_piece(2, 0, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, 0, "");

            state->scenario_name = create_savegame_piece(65, 0, "scenario_name"); // ok
            state->bookmarks = create_savegame_piece(32, 0, "bookmarks"); // ok
            state->tutorial_part3 = create_savegame_piece(4, 0, "tutorial_part3"); // ok ????

            // 8 bytes      00 00 00 00 ???
            state->junk9 = create_savegame_piece(8, 0, "junk9");

            // 52370 bytes  00 00 00 00 ???
            state->GRID01_8BIT = create_savegame_piece(52370, 0, "GRID01_8BIT"); // todo: 1-byte grid

            // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
            // 38 bytes     2F 01 00 00 ???
            // 13416 bytes  00 00 00 00 ??? (200 less for non-expanded file)
            // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
            state->junk10a = create_savegame_piece(18600, 0, "junk10a");
            state->junk10b = create_savegame_piece(38, 0, "junk10b");
            state->junk10c = create_savegame_piece(13216, 0, "junk10c");
            if (expanded)
                state->junk10d = create_savegame_piece(200, 0, "junk10d");
            state->junk10e = create_savegame_piece(8200, 0, "junk10e");

            state->junk11 = create_savegame_piece(1280, 1, "junk11"); // unknown compressed data
            if (expanded)
                state->empire_map_objects = create_savegame_piece(19600, 1, "junk12"); // unknown compressed data
            else
                state->empire_map_objects = create_savegame_piece(15200, 1, "junk12"); // unknown compressed data
            state->junk13 = create_savegame_piece(16200, 1, "junk13"); // unknown compressed data

            // 51984 bytes  FF FF FF FF ???          // (228²) * 1 ?????????????????
            state->GRID02_8BIT = create_savegame_piece(51984, 0, "GRID02_8BIT"); // todo: 1-byte grid

            // 20 bytes     19 00 00 00 ???
            // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
            state->junk14a = create_savegame_piece(20, 0, "junk14a");
            state->junk14b = create_savegame_piece(528, 0, "junk14b");

            state->floodplain_settings = create_savegame_piece(36, 1, "floodplain_settings"); // floodplain_settings
            state->GRID03_32BIT = create_savegame_piece(207936, 1, "GRID03_32BIT"); // todo: 4-byte grid

            // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
            // 64 bytes     00 00 00 00 ???
            state->junk16a = create_savegame_piece(312 , 0, "junk16a"); // 71x 4-bytes emptiness
            state->junk16b = create_savegame_piece(64, 0, "junk16b"); // 71x 4-bytes emptiness
            state->tutorial_part1 = create_savegame_piece(41, 0, "tutorial_part1"); // 41 x 1-byte flag fields
            state->GRID04_8BIT = create_savegame_piece(51984, 1, "GRID04_8BIT"); // todo: 1-byte grid

            // lone byte ???
            state->junk17 = create_savegame_piece(1, 0, "junk17");
            state->moisture_grid = create_savegame_piece(51984, 1, "moisture_grid");

            // 672 bytes    0F 00 00 00 ??? 28 x 24-byte chunk
            // 20 bytes     00 00 00 00 ???
            // 4800 bytes   00 00 00 00 ???
            state->junk18a = create_savegame_piece(672, 0, "junk18a");
            state->junk18b = create_savegame_piece(20, 0, "junk18b");
            state->end_marker = create_savegame_piece(4800, 0, "end_marker");

            break;
        }
    }
}

static void scenario_load_from_state(scenario_state *file) {
    map_image_load_state(file->graphic_ids);
    map_terrain_load_state(file->terrain);
    map_property_load_state(file->bitfields, file->edge);
    map_random_load_state(file->random);
    map_elevation_load_state(file->elevation);
    city_view_load_scenario_state(file->camera);

    random_load_state(file->random_iv);

    scenario_load_state(&file->scenario_data);

//    file->end_marker->skip(4);
}
static void scenario_save_to_state(scenario_state *file) {
    map_image_save_state(file->graphic_ids);
    map_terrain_save_state(file->terrain);
    map_property_save_state(file->bitfields, file->edge);
    map_random_save_state(file->random);
    map_elevation_save_state(file->elevation);
    city_view_save_scenario_state(file->camera);

    random_save_state(file->random_iv);

    scenario_save_state(&file->scenario_data);

//    file->end_marker->skip(4);
}
static void savegame_load_from_state(savegame_state *state) {
//    savegame_version = state->file_version->read_i32();

    scenario_settings_load_state(state->scenario_campaign_mission,
                                 state->scenario_settings,
                                 state->scenario_is_custom,
                                 state->player_name,
                                 state->scenario_name);

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
                         state->city_entry_exit_grid_offset,
                         state->floodplain_settings);

    building_load_state(state->buildings,
                        state->building_extra_highest_id,
                        state->building_extra_highest_id_ever);
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

    scenario_load_state(&state->scenario_data);
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

//    building_storage_load_state(state->building_storages);
//    scenario_gladiator_revolt_load_state(state->gladiator_revolt);
    trade_routes_load_state(state->trade_route_limit, state->trade_route_traded);
//    map_routing_load_state(state->routing_counters);
//    enemy_armies_load_state(state->enemy_armies, state->enemy_army_totals);
//    scenario_invasion_load_state(state->last_invasion_id, state->invasion_warnings);
    map_bookmark_load_state(state->bookmarks);

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        map_temp_grid_load(state->GRID01_8BIT, 0);
        map_temp_grid_load(state->GRID02_8BIT, 1);
//        map_temp_grid_load(state->GRID03_32BIT, 2);
        map_temp_grid_load(state->GRID04_8BIT, 2);
        map_moisture_load_state(state->moisture_grid);
        map_unk32_load_state(state->GRID03_32BIT);

        empire_load_internal_ph(state->empire_map_objects);
    }
//    state->end_marker->skip(284);
}
static void savegame_save_to_state(savegame_state *state) {
    state->file_version->write_i32(savegame_version);

    scenario_settings_save_state(state->scenario_campaign_mission,
                                 state->scenario_settings,
                                 state->scenario_is_custom,
                                 state->player_name,
                                 state->scenario_name);

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
                        state->building_extra_highest_id,
                        state->building_extra_highest_id_ever);
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

    scenario_save_state(&state->scenario_data);
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

int findex;
char *fname;

void log_hex(file_piece *piece, int i, int offs) {
    // log first few bytes of the filepiece
    size_t s = piece->buf->size() < 16 ? piece->buf->size() : 16;
    char hexstr[40] = {0};
    for (int b = 0; b < s; b++) {
        char hexcode[3] = {0};
        uint8_t inbyte = ((uint8_t *) piece->buf->data_const())[b];
        snprintf(hexcode, 4, "%02X", inbyte);
        strncat(hexstr, hexcode, 4);
        if ((b + 1) % 4 == 0 || (b + 1) == s)
            strncat(hexstr, " ", 2);
    }
    SDL_Log("Piece %s %03i/%i : %8i@ %-36s(%i) %s", piece->compressed ? "(C)" : "---", i + 1, savegame_data.num_pieces,
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
        if (buf->from_file(1, filepiece_size, fp) != filepiece_size)
            return 0;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        if (fread(compress_buffer, 1, chunk_size, fp) != chunk_size
            || zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size) !=
               buf->size())
            return 0;
    }
    buf->force_validate_unsafe_pls_use_carefully();
    char *lfile = (char *) malloc(200);
    sprintf(lfile, "DEV_TESTING/zip/%i_%i_%s", findex, filepiece_size, fname);
    FILE *log = fopen(lfile, "wb+");
    fwrite(buf->data_const(), filepiece_size, 1, log);
    fclose(log);
    free(lfile);
    return 1;
}
static int write_compressed_chunk(FILE *fp, buffer *buf, int bytes_to_write) {
    if (bytes_to_write > COMPRESS_BUFFER_SIZE)
        return 0;

    int output_size = COMPRESS_BUFFER_SIZE;
    if (zip_compress(buf->data_const(), bytes_to_write, compress_buffer, &output_size)) {
//        write_int32(fp, output_size);
        fwrite(&output_size, 4, 1, fp);
        fwrite(compress_buffer, 1, output_size, fp);
    } else {
        // unable to compress: write uncompressed
//        write_int32(fp, UNCOMPRESSED);
        output_size = UNCOMPRESSED;
        fwrite(&output_size, 4, 1, fp);
        fwrite(buf->data_const(), 1, bytes_to_write, fp);
    }
    return 1;
}
static int savegame_read_from_file(FILE *fp) {
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        findex = i;
        fname = piece->name;
        int result = 0;

        auto offs = ftell(fp);

        if (i == 49)
            int a = 24;

        if (piece->compressed)
            result = read_compressed_chunk(fp, piece->buf, piece->buf->size());
        else
            result = piece->buf->from_file(1, piece->buf->size(), fp) == piece->buf->size();

        log_hex(piece, i, offs);

        // The last piece may be smaller than buf->size
        if (!result && i != (savegame_data.num_pieces - 1)) {
            log_info("Incorrect buffer size, expected.", 0, piece->buf->size());
            return 0;
        }
    }
    return 1;
}
static void savegame_write_to_file(FILE *fp) {
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        if (piece->compressed)
            write_compressed_chunk(fp, piece->buf, piece->buf->size());
        else
            piece->buf->to_file(1, piece->buf->size(), fp);
    }
}

int game_file_io_read_scenario(const char *filename) {
    return 0;
//    log_info("Loading scenario", filename, 0);
//    init_scenario_data();
//    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
//    if (!fp) {
//        return 0;
//    }
//    for (int i = 0; i < scenario_data.num_pieces; i++) {
//        if (fread(scenario_data.pieces[i].buf->data, 1, scenario_data.pieces[i].buf->size, fp) != scenario_data.pieces[i].buf->size) {
//            log_error("Unable to load scenario", filename, 0);
//            file_close(fp);
//            return 0;
//        }
//    }
//    file_close(fp);
//
//    scenario_load_from_state(&scenario_data.state);
//    return 1;
}
int game_file_io_write_scenario(const char *filename) {
    return 0;
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
int game_file_io_read_saved_game(const char *filename, int offset) {
    if (file_has_extension(filename, "pak")) {
        log_info("Loading saved game.", filename, 0);
        init_savegame_data(0);
        terrain_ph_offset = 539; //14791
    } else {
        log_info("Loading saved game (expanded).", filename, 0);
        init_savegame_data(1);
        terrain_ph_offset = 0; //14252
    }

    log_info("Loading saved game", filename, 0);
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        return 0;
    }
    if (offset)
        fseek(fp, offset, SEEK_SET);


    int result = savegame_read_from_file(fp);
    file_close(fp);
    if (!result) {
        log_error("Unable to load game, unable to read savefile.", 0, 0);
        return 0;
    }
    savegame_load_from_state(&savegame_data.state);
    return 1;
}
int game_file_io_write_saved_game(const char *filename) {
    init_savegame_data(1);

    log_info("Saving game", filename, 0);
//    savegame_version = SAVE_GAME_VERSION;
    savegame_save_to_state(&savegame_data.state);

    FILE *fp = file_open(filename, "wb");
    if (!fp) {
        log_error("Unable to save game", 0, 0);
        return 0;
    }
    savegame_write_to_file(fp);
    file_close(fp);
    return 1;
}
int game_file_io_delete_saved_game(const char *filename) {
    log_info("Deleting game", filename, 0);
    int result = file_remove(filename);
    if (!result)
        log_error("Unable to delete game", 0, 0);

    return result;
}
