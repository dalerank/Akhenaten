#include "file_io.h"

#include "building/barracks.h"
#include "building/count.h"
#include "building/list.h"
#include "building/storage.h"
#include "city/culture.h"
#include "city/data.h"
#include "core/file.h"
#include "core/log.h"
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
    buffer buf;
    int compressed;
    char name[100];
} file_piece;

typedef struct {
    buffer *graphic_ids;
    buffer *edge;
    buffer *terrain;
    buffer *bitfields;
    buffer *random;
    buffer *elevation;
    buffer *random_iv;
    buffer *camera;
//    buffer *scenario;
    scenario_data_buffers scenario_data;
    buffer *end_marker;
} scenario_state;

static struct {
    int num_pieces;
    file_piece pieces[10];
    scenario_state state;
} scenario_data = {0};

typedef struct {
    buffer *scenario_campaign_mission;
    buffer *file_version;
    buffer *image_grid;
    buffer *edge_grid;
    buffer *building_grid;
    buffer *terrain_grid;
    buffer *aqueduct_grid;
    buffer *figure_grid;
    buffer *bitfields_grid;
    buffer *sprite_grid;
    buffer *random_grid;
    buffer *desirability_grid;
    buffer *elevation_grid;
    buffer *building_damage_grid;
    buffer *aqueduct_backup_grid;
    buffer *sprite_backup_grid;
    buffer *figures;
    buffer *route_figures;
    buffer *route_paths;
    buffer *formations;
    buffer *formation_totals;
    buffer *city_data;
    buffer *city_faction_unknown;
    buffer *player_name;
    buffer *city_faction;
    buffer *buildings;
    buffer *city_view_orientation;
    buffer *game_time;
    buffer *building_extra_highest_id_ever;
    buffer *random_iv;
    buffer *city_view_camera;
    buffer *building_count_culture1;
    buffer *city_graph_order;
    buffer *emperor_change_time;
    buffer *empire;
    buffer *empire_cities;
    buffer *building_count_industry;
    buffer *trade_prices;
    buffer *figure_names;
    buffer *culture_coverage;
//    buffer *scenario;

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

//    buffer *scenario_header;
//        buffer *scenario_request_events;
//        buffer *scenario_invasion_events;
//    buffer *scenario_map_info1;
//        buffer *scenario_request_can_comply_dialogs;
//    buffer *scenario_map_info2;
//        buffer *scenario_animal_herds;
//        buffer *scenario_demands;
//    buffer *scenario_random_events;
//        buffer *scenario_fishing_spots;
//        buffer *scenario_requests_extra;
//    buffer *scenario_wheat_rome;
//        buffer *scenario_allowed_buildings;
//    buffer *scenario_win_criteria;
//    buffer *scenario_map_points;
//        buffer *scenario_invasion_points;
//    buffer *scenario_river_entry;
//    buffer *scenario_map_info3;
//    buffer *scenario_empire_info;

    buffer *max_game_year;
    buffer *earthquake;
    buffer *emperor_change_state;
    buffer *messages;
    buffer *message_extra;
    buffer *population_messages;
    buffer *message_counts;
    buffer *message_delays;
    buffer *building_list_burning_totals;
    buffer *figure_sequence;
    buffer *scenario_settings;
    buffer *invasion_warnings;
    buffer *scenario_is_custom;
    buffer *city_sounds;
    buffer *building_extra_highest_id;
    buffer *figure_traders;
    buffer *building_list_burning;
    buffer *building_list_small;
    buffer *building_list_large;
    buffer *tutorial_part1;
    buffer *building_count_military;
    buffer *enemy_army_totals;
    buffer *building_storages;
    buffer *building_count_culture2;
    buffer *building_count_support;
    buffer *tutorial_part2;
    buffer *gladiator_revolt;
    buffer *trade_route_limit;
    buffer *trade_route_traded;
    buffer *building_barracks_tower_sentry;
    buffer *building_extra_sequence;
    buffer *routing_counters;
    buffer *building_count_culture3;
    buffer *enemy_armies;
    buffer *city_entry_exit_xy;
    buffer *last_invasion_id;
    buffer *building_extra_corrupt_houses;
    buffer *scenario_name;
    buffer *bookmarks;
    buffer *tutorial_part3;
    buffer *city_entry_exit_grid_offset;
    buffer *end_marker;

    buffer *ph_unk01;
    buffer *ph_unk02;
    buffer *ph_unk03;
    buffer *ph_unk04;
    buffer *ph_unk05;
    buffer *ph_unk06;
    buffer *ph_unk07;
    buffer *ph_unk08;
    buffer *ph_unk09;
    buffer *ph_unk10;

    buffer *junk1;
    buffer *junk2;
    buffer *junk3;
    buffer *junk4;
    buffer *junk5;
    buffer *junk6;
    buffer *junk7;
    buffer *junk8;
    buffer *junk9;
    buffer *junk10;
    buffer *junk11;
    buffer *junk12;
    buffer *junk13;
    buffer *junk14;
    buffer *junk15;
    buffer *junk16;
    buffer *junk17;
    buffer *junk18;
    buffer *junk19;
    buffer *junk20;
} savegame_state;

static struct {
    int num_pieces;
    file_piece pieces[200];
    savegame_state state;
} savegame_data = {0};

static void init_file_piece(file_piece *piece, int size, int compressed)
{
    piece->compressed = compressed;
    void *data = malloc(size);
    memset(data, 0, size);
    buffer_init(&piece->buf, data, size);
}
static buffer *create_scenario_piece(int size, char *name)
{
    file_piece *piece = &scenario_data.pieces[scenario_data.num_pieces++];
    init_file_piece(piece, size, 0);
    strncpy(piece->name, name, 99);
    return &piece->buf;
}
static buffer *create_savegame_piece(int size, int compressed, char *name)
{
//    if (compressed)
//        switch (GAME_ENV) {
//            case ENGINE_ENV_PHARAOH:
//                size *= 10;
//        }

    file_piece *piece = &savegame_data.pieces[savegame_data.num_pieces++];
    init_file_piece(piece, size, compressed);
    strncpy(piece->name, name, 99);
    return &piece->buf;
}

static void init_savegame_buffers(savegame_state* state)
{
    state->scenario_campaign_mission = 0;
    state->file_version = 0;
    state->image_grid = 0;
    state->edge_grid = 0;
    state->building_grid = 0;
    state->terrain_grid = 0;
    state->aqueduct_grid = 0;
    state->figure_grid = 0;
    state->bitfields_grid = 0;
    state->sprite_grid = 0;
    state->random_grid = 0;
    state->desirability_grid = 0;
    state->elevation_grid = 0;
    state->building_damage_grid = 0;
    state->aqueduct_backup_grid = 0;
    state->sprite_backup_grid = 0;
    state->figures = 0;
    state->route_figures = 0;
    state->route_paths = 0;
    state->formations = 0;
    state->formation_totals = 0;
    state->city_data = 0;
    state->city_faction_unknown = 0;
    state->player_name = 0;
    state->city_faction = 0;
    state->buildings = 0;
    state->city_view_orientation = 0;
    state->game_time = 0;
    state->building_extra_highest_id_ever = 0;
    state->random_iv = 0;
    state->city_view_camera = 0;
    state->building_count_culture1 = 0;
    state->city_graph_order = 0;
    state->emperor_change_time = 0;
    state->empire = 0;
    state->empire_cities = 0;
    state->building_count_industry = 0;
    state->trade_prices = 0;
    state->figure_names = 0;
    state->culture_coverage = 0;
//    state->scenario = 0;

//    state->scenario_data = {0};
    state->scenario_data.header = 0;
    state->scenario_data.info1 = 0;
    state->scenario_data.info2 = 0;
    state->scenario_data.info3 = 0;
    state->scenario_data.events = 0;
    state->scenario_data.win_criteria = 0;
    state->scenario_data.map_points = 0;
    state->scenario_data.river_points = 0;
    state->scenario_data.empire = 0;
    state->scenario_data.wheat = 0;
    state->scenario_data.requests = 0;
    state->scenario_data.invasions = 0;
    state->scenario_data.invasion_points = 0;
    state->scenario_data.request_comply_dialogs = 0;
    state->scenario_data.herds = 0;
    state->scenario_data.demands = 0;
    state->scenario_data.price_changes = 0;
    state->scenario_data.fishing_points = 0;
    state->scenario_data.request_extra = 0;
    state->scenario_data.allowed_builds = 0;
    // pharaoh only
    state->scenario_data.monuments = 0;

    state->max_game_year = 0;
    state->earthquake = 0;
    state->emperor_change_state = 0;
    state->messages = 0;
    state->message_extra = 0;
    state->population_messages = 0;
    state->message_counts = 0;
    state->message_delays = 0;
    state->building_list_burning_totals = 0;
    state->figure_sequence = 0;
    state->scenario_settings = 0;
    state->invasion_warnings = 0;
    state->scenario_is_custom = 0;
    state->city_sounds = 0;
    state->building_extra_highest_id = 0;
    state->figure_traders = 0;
    state->building_list_burning = 0;
    state->building_list_small = 0;
    state->building_list_large = 0;
    state->tutorial_part1 = 0;
    state->building_count_military = 0;
    state->enemy_army_totals = 0;
    state->building_storages = 0;
    state->building_count_culture2 = 0;
    state->building_count_support = 0;
    state->tutorial_part2 = 0;
    state->gladiator_revolt = 0;
    state->trade_route_limit = 0;
    state->trade_route_traded = 0;
    state->building_barracks_tower_sentry = 0;
    state->building_extra_sequence = 0;
    state->routing_counters = 0;
    state->building_count_culture3 = 0;
    state->enemy_armies = 0;
    state->city_entry_exit_xy = 0;
    state->last_invasion_id = 0;
    state->building_extra_corrupt_houses = 0;
    state->scenario_name = 0;
    state->bookmarks = 0;
    state->tutorial_part3 = 0;
    state->city_entry_exit_grid_offset = 0;
    state->end_marker = 0;

    state->ph_unk01 = 0;
    state->ph_unk02 = 0;
    state->ph_unk03 = 0;
    state->ph_unk04 = 0;
    state->ph_unk05 = 0;
    state->ph_unk06 = 0;
    state->ph_unk07 = 0;
    state->ph_unk08 = 0;
    state->ph_unk09 = 0;
    state->ph_unk10 = 0;

    state->junk1 = 0;
    state->junk2 = 0;
    state->junk3 = 0;
    state->junk4 = 0;
    state->junk5 = 0;
    state->junk6 = 0;
}
static void init_scenario_data(void)
{
    return;
    if (scenario_data.num_pieces > 0) {
        for (int i = 0; i < scenario_data.num_pieces; i++) {
            buffer_reset(&scenario_data.pieces[i].buf);
        }
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
static void init_savegame_data(void)
{
    if (savegame_data.num_pieces > 0) {
        for (int i = 0; i < savegame_data.num_pieces; i++) {
            buffer_reset(&savegame_data.pieces[i].buf);
            free(savegame_data.pieces[i].buf.data);
        }
        //return;
        savegame_data.num_pieces = 0;
    }
    savegame_state *state = &savegame_data.state;
    init_savegame_buffers(state);

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
            state->figures = create_savegame_piece(640000, 1, "figures");
            state->route_figures = create_savegame_piece(6000, 1, "route_figures");
            state->route_paths = create_savegame_piece(1500000, 1, "route_paths");
            state->formations = create_savegame_piece(32000, 1, "formations");
            state->formation_totals = create_savegame_piece(12, 0, "formation_totals");
            state->city_data = create_savegame_piece(36136, 1, "city_data");
            state->city_faction_unknown = create_savegame_piece(2, 0, "city_faction_unknown");
            state->player_name = create_savegame_piece(64, 0, "player_name");
            state->city_faction = create_savegame_piece(4, 0, "city_faction");
            state->buildings = create_savegame_piece(1280000, 1, "buildings");
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
            state->building_list_burning = create_savegame_piece(5000, 1, "building_list_burning");
            state->building_list_small = create_savegame_piece(5000, 1, "building_list_small");
            state->building_list_large = create_savegame_piece(20000, 1, "building_list_large");
            state->tutorial_part1 = create_savegame_piece(32, 0, "tutorial_part1");
            state->building_count_military = create_savegame_piece(16, 0, "building_count_military");
            state->enemy_army_totals = create_savegame_piece(20, 0, "enemy_army_totals");
            state->building_storages = create_savegame_piece(32000, 0, "building_storages");
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
//                state->ph_unk01 = create_savegame_piece(3, 0, ""); // 3 bytes
        state->junk1 = create_savegame_piece(6011, 0, "junk1"); // ?????

                    state->image_grid = create_savegame_piece(207936, 1, "image_grid");
                    state->edge_grid = create_savegame_piece(51984, 1, "edge_grid");
                    state->building_grid = create_savegame_piece(103968, 1, "building_grid");
                    state->terrain_grid = create_savegame_piece(207936, 1, "terrain_grid");
                    state->aqueduct_grid = create_savegame_piece(51984, 1, "aqueduct_grid");
                    state->figure_grid = create_savegame_piece(103968, 1, "figure_grid");
                    state->bitfields_grid = create_savegame_piece(51984, 1, "bitfields_grid");
                    state->sprite_grid = create_savegame_piece(51984, 1, "sprite_grid");
                state->random_grid = create_savegame_piece(51984, 0, "random_grid"); // 26244
                    state->desirability_grid = create_savegame_piece(51984, 1, "desirability_grid");
                    state->elevation_grid = create_savegame_piece(51984, 1, "elevation_grid");
                    state->building_damage_grid = create_savegame_piece(103968, 1, "building_damage_grid");
                    state->aqueduct_backup_grid = create_savegame_piece(51984, 1, "aqueduct_backup_grid");
                    state->sprite_backup_grid = create_savegame_piece(51984, 1, "sprite_backup_grid");
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


                /////////////////////


//                state->scenario = create_savegame_piece(1720, 0, ""); // MISSING
                state->scenario_data.header = create_savegame_piece(32, 0, "scenario_data.header");
                state->scenario_data.info1 = create_savegame_piece(614, 0, "scenario_data.info1");
//                state->scenario_request_can_comply_dialogs = create_savegame_piece(20, 0, ""); // MISSING
                state->scenario_data.info2 = create_savegame_piece(6, 0, "scenario_data.info2");

        // 48 bytes     FF FF FF FF (non cyclic) ???
        // 44 bytes     00 00 00 00 ???
        // 64 bytes     FF FF FF FF (cyclic) invasion points???
        // 36 bytes     01 00 01 00 ???
        state->junk2 = create_savegame_piece(48+44+64+36, 0, "junk2"); // unknown bytes

                state->scenario_data.win_criteria = create_savegame_piece(60, 0, "scenario_data.win_criteria");

        // 52 bytes     FF FF FF FF (non cyclic) ???
        // 4  bytes     B8 0B 00 00 ???
        // 12 bytes     0A 00 00 00 (3x4) ???
        // 12 bytes     CB 32 00 00 (3x4) ??? (n, n+2, n+1497)
        // 14 bytes     01 00 00 00 ???
        // 34 bytes     FF FF 2C 00 (....non cyclic?) ???
        state->junk3 = create_savegame_piece(52+4+12+12+14+34, 0, "junk3"); // unknown bytes

                state->scenario_data.allowed_builds = create_savegame_piece(228, 0, "scenario_data.allowed_builds");

        // 24 bytes     FF FF FF FF (cyclic) ???
        state->junk4 = create_savegame_piece(24, 0, "junk4"); // unknown bytes

                state->scenario_data.monuments = create_savegame_piece(10, 0, "scenario_data.monuments"); // 4 bytes + 3 x 2-byte


        // 290 bytes    00 00 00 00 ???
        // 4 bytes      00 00 00 00 ???
        // 4 bytes      00 00 00 00 ???
        // 4 bytes      00 00 00 00 ???
        state->junk5 = create_savegame_piece(290+4+4+4, 0, "junk5"); // unknown bytes

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
//                state->figure_traders = create_savegame_piece(4804, 0, "");
                state->figure_traders = create_savegame_piece(8804, 0, "figure_traders"); // +4000 ???
                    state->building_list_burning = create_savegame_piece(1000, 1, "building_list_burning"); // ok
                    state->building_list_small = create_savegame_piece(1000, 1, "building_list_small"); // ok
                    state->building_list_large = create_savegame_piece(8000, 1, "building_list_large"); // ok
                state->tutorial_part1 = create_savegame_piece(32, 0, "tutorial_part1"); // ok ????

//                state->building_count_military = create_savegame_piece(16, 0, "");
//                state->enemy_army_totals = create_savegame_piece(20, 0, "");
//                state->building_storages = create_savegame_piece(6400, 0, "");
//                state->building_count_culture2 = create_savegame_piece(32, 0, "");
//                state->building_count_support = create_savegame_piece(24, 0, "");
//                state->tutorial_part2 = create_savegame_piece(4, 0, "");
//                state->gladiator_revolt = create_savegame_piece(16, 0, "");


        // 24 bytes     00 00 00 00 ???
        // 39200 bytes  00 00 00 00 ??? 200 x 196-byte chunk
        state->junk6 = create_savegame_piece(39224, 0, "junk6"); // 39224 bytes

                    state->trade_route_limit = create_savegame_piece(2880, 1, "trade_route_limit"); // ok
                    state->trade_route_traded = create_savegame_piece(2880, 1, "trade_route_traded"); // ok

//                state->building_barracks_tower_sentry = create_savegame_piece(4, 0, "");
//                state->building_extra_sequence = create_savegame_piece(4, 0, "");
//                state->routing_counters = create_savegame_piece(16, 0, "");
//                state->building_count_culture3 = create_savegame_piece(40, 0, "");
//                state->enemy_armies = create_savegame_piece(900, 0, "");

        // 12 bytes     00 00 00 00 ???
        state->junk7 = create_savegame_piece(12, 0, "junk7"); // 12 bytes

                state->city_entry_exit_xy = create_savegame_piece(16, 0, "city_entry_exit_xy"); // ok ?????

//                state->last_invasion_id = create_savegame_piece(2, 0, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, 0, "");

        // 22 bytes     00 00 00 00 ???
        state->junk8 = create_savegame_piece(22, 0, "junk8"); // 22 bytes

                state->scenario_name = create_savegame_piece(65, 0, "scenario_name"); // ok
                state->bookmarks = create_savegame_piece(32, 0, "bookmarks"); // ok
                state->tutorial_part3 = create_savegame_piece(4, 0, "tutorial_part3"); // ok ????
                state->city_entry_exit_grid_offset = create_savegame_piece(8, 0, "city_entry_exit_grid_offset"); // ok ????

//                state->end_marker = create_savegame_piece(284, 0, ""); // 71x 4-bytes emptiness 150684

        // 52370 bytes  00 00 00 00 ???
        // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
        // 38 bytes     2F 01 00 00 ???
        // 13416 bytes  00 00 00 00 ???
        // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
        state->junk9 = create_savegame_piece(52370+18600+38+13416+8200, 0, "junk9"); // 71x 4-bytes emptiness

        state->junk10 = create_savegame_piece(1280, 1, "junk10"); // unknown compressed data
        state->junk11 = create_savegame_piece(19600, 1, "junk11"); // unknown compressed data
        state->junk12 = create_savegame_piece(16200, 1, "junk12"); // unknown compressed data

        // 51984 bytes  FF FF FF FF ???
        // 20 bytes     19 00 00 00 ???
        // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
        state->junk13 = create_savegame_piece(51984+20+528, 0, "junk13"); // 71x 4-bytes emptiness

        state->junk14 = create_savegame_piece(36, 1, "junk14"); // unknown compressed data
        state->junk15 = create_savegame_piece(207936, 1, "junk15"); // unknown compressed data

        // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
        // 64 bytes     00 00 00 00 ???
        // 41 bytes     00 00 00 00 ??? 41 x 1-byte flag fields
        state->junk16 = create_savegame_piece(312+64+41, 0, "junk16"); // 71x 4-bytes emptiness

        state->junk17 = create_savegame_piece(51984, 1, "junk17"); // unknown compressed data

        // lone byte ???
        state->junk18 = create_savegame_piece(1, 0, "junk18");

        state->junk19 = create_savegame_piece(51984, 1, "junk19"); // unknown compressed data

        // 672 bytes    0F 00 00 00 ??? 28 x 24-byte chunk
        // 20 bytes     00 00 00 00 ???
        // 4800 bytes   00 00 00 00 ???
        state->junk20 = create_savegame_piece(672+20, 0, "junk20");
                state->end_marker = create_savegame_piece(4800, 0, "end_marker");

                break;
            }
    }
}
static void init_savegame_data_expanded(void)
{ // this SHOULD only happen in C3....
    if (savegame_data.num_pieces > 0) {
        for (int i = 0; i < savegame_data.num_pieces; i++) {
            buffer_reset(&savegame_data.pieces[i].buf);
            free(savegame_data.pieces[i].buf.data);
        }
        //return;
        savegame_data.num_pieces = 0;
    }

    savegame_state *state = &savegame_data.state;
    init_savegame_buffers(state);

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
    state->figures = create_savegame_piece(640000, 1, "figures");
    state->route_figures = create_savegame_piece(6000, 1, "route_figures");
    state->route_paths = create_savegame_piece(1500000, 1, "route_paths");
    state->formations = create_savegame_piece(32000, 1, "formations");
    state->formation_totals = create_savegame_piece(12, 0, "formation_totals");
    state->city_data = create_savegame_piece(36136, 1, "city_data");
    state->city_faction_unknown = create_savegame_piece(2, 0, "city_faction_unknown");
    state->player_name = create_savegame_piece(64, 0, "player_name");
    state->city_faction = create_savegame_piece(4, 0, "city_faction");
    state->buildings = create_savegame_piece(1280000, 1, "buildings");
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
    state->building_list_burning = create_savegame_piece(5000, 1, "building_list_burning");
    state->building_list_small = create_savegame_piece(5000, 1, "building_list_small");
    state->building_list_large = create_savegame_piece(20000, 1, "building_list_large");
    state->tutorial_part1 = create_savegame_piece(32, 0, "tutorial_part1");
    state->building_count_military = create_savegame_piece(16, 0, "building_count_military");
    state->enemy_army_totals = create_savegame_piece(20, 0, "enemy_army_totals");
    state->building_storages = create_savegame_piece(32000, 0, "building_storages");
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
}

#include "assert.h"

static buffer *safebuf(buffer *buf)
{
    if (buf == 0) {
        int a = 325;
    }
    assert(buf != 0);
    return buf;
}
static scenario_data_buffers *safebuf_struct(scenario_data_buffers *data)
{
    return data;
    safebuf(data->header);
    safebuf(data->info1);
    safebuf(data->info2);
    safebuf(data->info3);
    safebuf(data->events);
    safebuf(data->win_criteria);
    safebuf(data->map_points);
    safebuf(data->river_points);
    safebuf(data->empire);
    safebuf(data->wheat);

    safebuf(data->requests);
    safebuf(data->invasions);
    safebuf(data->invasion_points);
    safebuf(data->request_comply_dialogs);
    safebuf(data->herds);
    safebuf(data->demands);
    safebuf(data->price_changes);
    safebuf(data->fishing_points);
    safebuf(data->request_extra);
    safebuf(data->allowed_builds);
    return data;
}

static void scenario_load_from_state(scenario_state *file)
{
    map_image_load_state(file->graphic_ids);
    map_terrain_load_state(file->terrain);
    map_property_load_state(file->bitfields, file->edge);
    map_random_load_state(file->random);
    map_elevation_load_state(file->elevation);
    city_view_load_scenario_state(file->camera);

    random_load_state(file->random_iv);

    scenario_load_state(&file->scenario_data);

    buffer_skip(file->end_marker, 4);
}
static void scenario_save_to_state(scenario_state *file)
{
    map_image_save_state(file->graphic_ids);
    map_terrain_save_state(file->terrain);
    map_property_save_state(file->bitfields, file->edge);
    map_random_save_state(file->random);
    map_elevation_save_state(file->elevation);
    city_view_save_scenario_state(file->camera);

    random_save_state(file->random_iv);

    scenario_save_state(&file->scenario_data);

    buffer_skip(file->end_marker, 4);
}
static void savegame_load_from_state(savegame_state *state)
{
//    savegame_version = buffer_read_i32(state->file_version);

    scenario_settings_load_state(safebuf(state->scenario_campaign_mission),
                                 safebuf(state->scenario_settings),
                                 safebuf(state->scenario_is_custom),
                                 safebuf(state->player_name),
                                 safebuf(state->scenario_name));

    map_image_load_state(safebuf(state->image_grid));
    map_building_load_state(safebuf(state->building_grid), safebuf(state->building_damage_grid));
    map_terrain_load_state(safebuf(state->terrain_grid));
    map_aqueduct_load_state(safebuf(state->aqueduct_grid), safebuf(state->aqueduct_backup_grid));
    map_figure_load_state(safebuf(state->figure_grid));
    map_sprite_load_state(safebuf(state->sprite_grid), safebuf(state->sprite_backup_grid));
    map_property_load_state(safebuf(state->bitfields_grid), safebuf(state->edge_grid));
    map_random_load_state(safebuf(state->random_grid));
    map_desirability_load_state(safebuf(state->desirability_grid));
    map_elevation_load_state(safebuf(state->elevation_grid));

    figure_load_state(safebuf(state->figures), safebuf(state->figure_sequence));
    figure_route_load_state(safebuf(state->route_figures), safebuf(state->route_paths));
    formations_load_state(safebuf(state->formations), safebuf(state->formation_totals));

    city_data_load_state(safebuf(state->city_data),
                         safebuf(state->city_faction),
                         safebuf(state->city_faction_unknown),
                         safebuf(state->city_graph_order),
                         safebuf(state->city_entry_exit_xy),
                         safebuf(state->city_entry_exit_grid_offset));

    building_load_state(safebuf(state->buildings),
                        safebuf(state->building_extra_highest_id),
                        safebuf(state->building_extra_highest_id_ever));
//    building_barracks_load_state(safebuf(state->building_barracks_tower_sentry));
    city_view_load_state(safebuf(state->city_view_orientation), safebuf(state->city_view_camera));
    game_time_load_state(safebuf(state->game_time));
    random_load_state(safebuf(state->random_iv));
//    building_count_load_state(safebuf(state->building_count_industry),
//                              safebuf(state->building_count_culture1),
//                              safebuf(state->building_count_culture2),
//                              safebuf(state->building_count_culture3),
//                              safebuf(state->building_count_military),
//                              safebuf(state->building_count_support));

//    scenario_emperor_change_load_state(safebuf(state->emperor_change_time), safebuf(state->emperor_change_state));

    empire_load_state(safebuf(state->empire));
    empire_city_load_state(safebuf(state->empire_cities));
    trade_prices_load_state(safebuf(state->trade_prices));
    figure_name_load_state(safebuf(state->figure_names));
//    city_culture_load_state(safebuf(state->culture_coverage));

    scenario_load_state(safebuf_struct(&state->scenario_data));
//    scenario_criteria_load_state(safebuf(state->max_game_year));
//    scenario_earthquake_load_state(safebuf(state->earthquake));
    city_message_load_state(safebuf(state->messages), safebuf(state->message_extra),
                            safebuf(state->message_counts), safebuf(state->message_delays),
                            safebuf(state->population_messages));
    sound_city_load_state(safebuf(state->city_sounds));
    traders_load_state(safebuf(state->figure_traders));

    building_list_load_state(safebuf(state->building_list_small), safebuf(state->building_list_large),
                             safebuf(state->building_list_burning), safebuf(state->building_list_burning_totals));

//    tutorial_load_state(safebuf(state->tutorial_part1), safebuf(state->tutorial_part2), safebuf(state->tutorial_part3));

//    building_storage_load_state(safebuf(state->building_storages));
//    scenario_gladiator_revolt_load_state(safebuf(state->gladiator_revolt));
    trade_routes_load_state(safebuf(state->trade_route_limit), safebuf(state->trade_route_traded));
//    map_routing_load_state(safebuf(state->routing_counters));
//    enemy_armies_load_state(safebuf(state->enemy_armies), safebuf(state->enemy_army_totals));
//    scenario_invasion_load_state(safebuf(state->last_invasion_id), safebuf(state->invasion_warnings));
    map_bookmark_load_state(safebuf(state->bookmarks));

    buffer_skip(state->end_marker, 284);
}
static void savegame_save_to_state(savegame_state *state)
{
//    buffer_write_i32(state->file_version, savegame_version);

    scenario_settings_save_state(safebuf(state->scenario_campaign_mission),
                                 safebuf(state->scenario_settings),
                                 safebuf(state->scenario_is_custom),
                                 safebuf(state->player_name),
                                 safebuf(state->scenario_name));

    map_image_save_state(safebuf(state->image_grid));
    map_building_save_state(safebuf(state->building_grid), safebuf(state->building_damage_grid));
    map_terrain_save_state(safebuf(state->terrain_grid));
    map_aqueduct_save_state(safebuf(state->aqueduct_grid), safebuf(state->aqueduct_backup_grid));
    map_figure_save_state(safebuf(state->figure_grid));
    map_sprite_save_state(safebuf(state->sprite_grid), safebuf(state->sprite_backup_grid));
    map_property_save_state(safebuf(state->bitfields_grid), safebuf(state->edge_grid));
    map_random_save_state(safebuf(state->random_grid));
    map_desirability_save_state(safebuf(state->desirability_grid));
    map_elevation_save_state(safebuf(state->elevation_grid));

    figure_save_state(safebuf(state->figures), safebuf(state->figure_sequence));
    figure_route_save_state(safebuf(state->route_figures), safebuf(state->route_paths));
    formations_save_state(safebuf(state->formations), safebuf(state->formation_totals));

    city_data_save_state(safebuf(state->city_data),
                         safebuf(state->city_faction),
                         safebuf(state->city_faction_unknown),
                         safebuf(state->city_graph_order),
                         safebuf(state->city_entry_exit_xy),
                         safebuf(state->city_entry_exit_grid_offset));

    building_save_state(safebuf(state->buildings),
                        safebuf(state->building_extra_highest_id),
                        safebuf(state->building_extra_highest_id_ever));
    building_barracks_save_state(safebuf(state->building_barracks_tower_sentry));
    city_view_save_state(safebuf(state->city_view_orientation), safebuf(state->city_view_camera));
    game_time_save_state(safebuf(state->game_time));
    random_save_state(safebuf(state->random_iv));
    building_count_save_state(safebuf(state->building_count_industry),
                              safebuf(state->building_count_culture1),
                              safebuf(state->building_count_culture2),
                              safebuf(state->building_count_culture3),
                              safebuf(state->building_count_military),
                              safebuf(state->building_count_support));

    scenario_emperor_change_save_state(safebuf(state->emperor_change_time), safebuf(state->emperor_change_state));

    empire_save_state(safebuf(state->empire));
    empire_city_save_state(safebuf(state->empire_cities));
    trade_prices_save_state(safebuf(state->trade_prices));
    figure_name_save_state(safebuf(state->figure_names));
    city_culture_save_state(safebuf(state->culture_coverage));

    scenario_save_state(safebuf_struct(&state->scenario_data));
    scenario_criteria_save_state(safebuf(state->max_game_year));
    scenario_earthquake_save_state(safebuf(state->earthquake));
    city_message_save_state(safebuf(state->messages), safebuf(state->message_extra),
                            safebuf(state->message_counts), safebuf(state->message_delays),
                            safebuf(state->population_messages));
    sound_city_save_state(safebuf(state->city_sounds));
    traders_save_state(safebuf(state->figure_traders));

    building_list_save_state(safebuf(state->building_list_small), safebuf(state->building_list_large),
                             safebuf(state->building_list_burning), safebuf(state->building_list_burning_totals));

    tutorial_save_state(safebuf(state->tutorial_part1), safebuf(state->tutorial_part2), safebuf(state->tutorial_part3));

    building_storage_save_state(safebuf(state->building_storages));
    scenario_gladiator_revolt_save_state(safebuf(state->gladiator_revolt));
    trade_routes_save_state(safebuf(state->trade_route_limit), safebuf(state->trade_route_traded));
    map_routing_save_state(safebuf(state->routing_counters));
    enemy_armies_save_state(safebuf(state->enemy_armies), safebuf(state->enemy_army_totals));
    scenario_invasion_save_state(safebuf(state->last_invasion_id), safebuf(state->invasion_warnings));
    map_bookmark_save_state(safebuf(state->bookmarks));

    buffer_skip(state->end_marker, 284);
}

#include "SDL.h"

int findex;
char *fname;

static int read_int32(FILE *fp)
{
    uint8_t data[4];
    if (fread(&data, 1, 4, fp) != 4) {
        return 0;
    }
    buffer buf;
    buffer_init(&buf, data, 4);
    return buffer_read_i32(&buf);
}
static void write_int32(FILE *fp, int value)
{
    uint8_t data[4];
    buffer buf;
    buffer_init(&buf, data, 4);
    buffer_write_i32(&buf, value);
    fwrite(&data, 1, 4, fp);
}
static int read_compressed_chunk(FILE *fp, void *buffer, int filepiece_size)
{
    // check that the stream size isn't above maximum temp buffer
    if (filepiece_size > COMPRESS_BUFFER_SIZE)
        return 0;

    // read 32-bit int header denoting size of compressed chunk
    int input_size = read_int32(fp);

    // if file signature says "uncompressed" well man, it's uncompressed. read as normal ignoring the directive
    if ((unsigned int) input_size == UNCOMPRESSED) {
        if (fread(buffer, 1, filepiece_size, fp) != filepiece_size)
            return 0;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        if (fread(compress_buffer, 1, input_size, fp) != input_size
        || !zip_decompress(compress_buffer, input_size, buffer, &filepiece_size))
            return 0;
    }
    char *lfile = malloc(200);
//    char nfile = malloc(20);
    sprintf(lfile,"DEV_TESTING/zip/%i_%i_%s", findex, filepiece_size, fname);
//    strcat(lfile, nfile);
    FILE *log = fopen(lfile, "wb+");
    fwrite(buffer, filepiece_size, 1, log);
    fclose(log);
    free(lfile);
//    free(nfile);
    return 1;
}
static int write_compressed_chunk(FILE *fp, const void *buffer, int bytes_to_write)
{
    if (bytes_to_write > COMPRESS_BUFFER_SIZE) {
        return 0;
    }
    int output_size = COMPRESS_BUFFER_SIZE;
    if (zip_compress(buffer, bytes_to_write, compress_buffer, &output_size)) {
        write_int32(fp, output_size);
        fwrite(compress_buffer, 1, output_size, fp);
    } else {
        // unable to compress: write uncompressed
        write_int32(fp, UNCOMPRESSED);
        fwrite(buffer, 1, bytes_to_write, fp);
    }
    return 1;
}
static int savegame_read_from_file(FILE *fp)
{
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        findex = i;
        fname = piece->name;
        int result = 0;
        int offs = ftell(fp);
        if (piece->compressed)
            result = read_compressed_chunk(fp, piece->buf.data, piece->buf.size);
        else
            result = fread(piece->buf.data, 1, piece->buf.size, fp) == piece->buf.size;

        // log first few bytes of the filepiece
        int s = piece->buf.size < 16 ? piece->buf.size : 16;
        char hexstr[40] = {0};
        for (int b = 0; b < s; b++)
        {
            char hexcode[3] = {0};
            snprintf(hexcode, 4, "%02X", piece->buf.data[b]);
            strncat(hexstr, hexcode, 4);
            if ((b + 1) % 4 == 0 || (b + 1) == s)
                strncat(hexstr, " ", 2);
        }
        SDL_Log("Filepiece %s %02i/%i : %8i@ %-36s(%i) %s", piece->compressed ? "(C)" : "---", i+1, savegame_data.num_pieces, offs, hexstr, piece->buf.size, fname);

        // The last piece may be smaller than buf.size
        if (!result && i != (savegame_data.num_pieces - 1)) {
            log_info("Incorrect buffer size, got.", 0, result);
            log_info("Incorrect buffer size, expected.", 0, piece->buf.size);
            return 0;
        }
    }
    return 1;
}
static void savegame_write_to_file(FILE *fp)
{
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        if (piece->compressed) {
            write_compressed_chunk(fp, piece->buf.data, piece->buf.size);
        } else {
            fwrite(piece->buf.data, 1, piece->buf.size, fp);
        }
    }
}

int game_file_io_read_scenario(const char *filename)
{
    log_info("Loading scenario", filename, 0);
    init_scenario_data();
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        return 0;
    }
    for (int i = 0; i < scenario_data.num_pieces; i++) {
        if (fread(scenario_data.pieces[i].buf.data, 1, scenario_data.pieces[i].buf.size, fp) != scenario_data.pieces[i].buf.size) {
            log_error("Unable to load scenario", filename, 0);
            file_close(fp);
            return 0;
        }
    }
    file_close(fp);

    scenario_load_from_state(&scenario_data.state);
    return 1;
}
int game_file_io_write_scenario(const char *filename)
{
    log_info("Saving scenario", filename, 0);
    init_scenario_data();
    scenario_save_to_state(&scenario_data.state);

    FILE *fp = file_open(filename, "wb");
    if (!fp) {
        log_error("Unable to save scenario", 0, 0);
        return 0;
    }
    for (int i = 0; i < scenario_data.num_pieces; i++) {
        fwrite(scenario_data.pieces[i].buf.data, 1, scenario_data.pieces[i].buf.size, fp);
    }
    file_close(fp);
    return 1;
}
int game_file_io_read_saved_game(const char *filename, int offset)
{
    if (file_has_extension(filename,"svx")) {
        init_savegame_data_expanded();
        log_info("Loading saved game new format.", filename, 0);

    } else {
        log_info("Loading saved game old format.", filename, 0);
        init_savegame_data();
    }

    log_info("Loading saved game", filename, 0);
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        return 0;
    }
    if (offset) {
        fseek(fp, offset, SEEK_SET);
    }
    int result = savegame_read_from_file(fp);
    file_close(fp);
    if (!result) {
        log_error("Unable to load game, unable to read savefile.", 0, 0);
        return 0;
    }
    savegame_load_from_state(&savegame_data.state);
    return 1;
}
int game_file_io_write_saved_game(const char *filename)
{
    init_savegame_data_expanded();

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
int game_file_io_delete_saved_game(const char *filename)
{
    log_info("Deleting game", filename, 0);
    int result = file_remove(filename);
    if (!result) {
        log_error("Unable to delete game", 0, 0);
    }
    return result;
}
