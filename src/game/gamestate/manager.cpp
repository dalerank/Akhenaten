#include "manager.h"
#include "io_chunks.h"
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
#include <map/image.h>

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

static char compress_buffer[COMPRESS_BUFFER_SIZE];

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
            push_chunk(4, false, "scenario_mission_index", iob_scenario_mission_id);
            push_chunk(8, false, "file_version", nullptr);

            push_chunk(6000, false, "junk1", iob_junk1); // ?????

            push_chunk(207936, true, "image_grid", iob_image_grid);                         // (228²) * 4 <<
            push_chunk(51984, true, "edge_grid", iob_edge_grid);                            // (228²) * 1
            push_chunk(103968, true, "building_grid", iob_building_grid);                   // (228²) * 2
            push_chunk(207936, true, "terrain_grid", iob_terrain_grid);                     // (228²) * 4 <<
            push_chunk(51984, true, "aqueduct_grid", iob_aqueduct_grid);                    // (228²) * 1
            push_chunk(103968, true, "figure_grid", iob_figure_grid);                       // (228²) * 2
            push_chunk(51984, true, "bitfields_grid", iob_bitfields_grid);                  // (228²) * 1
            push_chunk(51984, true, "sprite_grid", iob_sprite_grid);                        // (228²) * 1
            push_chunk(51984, false, "random_grid", iob_random_grid);                            // (228²) * 1
            push_chunk(51984, true, "desirability_grid", iob_desirability_grid);            // (228²) * 1
            push_chunk(51984, true, "elevation_grid", iob_elevation_grid);                  // (228²) * 1
            push_chunk(103968, true, "building_damage_grid", iob_damage_grid);     // (228²) * 2 <<
            push_chunk(51984, true, "aqueduct_backup_grid", iob_aqueduct_backup_grid);      // (228²) * 1
            push_chunk(51984, true, "sprite_backup_grid", iob_sprite_backup_grid);          // (228²) * 1
            push_chunk(776000, true, "figures", iob_figures);
            push_chunk(2000, true, "route_figures", iob_route_figures);
            push_chunk(500000, true, "route_paths", iob_route_paths);
            push_chunk(7200, true, "formations", iob_formations);
            push_chunk(12, false, "formation_totals", iob_formation_totals);
            push_chunk(37808, true, "city_data", iob_city_data);
            push_chunk(72, false, "city_data_extra", iob_city_data_extra);
            push_chunk(1056000, true, "buildings", iob_buildings);
            push_chunk(4, false, "city_view_orientation", iob_city_view_orientation); // ok
            push_chunk(20, false, "game_time", iob_game_time); // ok
            push_chunk(8, false, "building_extra_highest_id_ever", iob_building_highest_id_ever); // ok
            push_chunk(8, false, "random_iv", iob_random_iv); // ok
            push_chunk(8, false, "city_view_camera", iob_city_view_camera); // ok
//                state->building_count_culture1 = create_savegame_piece(132, false, ""); // MISSING
            push_chunk(8, false, "city_graph_order", iob_city_graph_order); // I guess ????
//                state->emperor_change_time = create_savegame_piece(8, false, ""); // MISSING
            push_chunk(12, false, "empire", iob_empire_map_params); // ok ???
            push_chunk(6466, true, "empire_cities", iob_empire_cities); // 83920 + 7681 --> 91601
            push_chunk(288, false, "building_count_industry", iob_building_count_industry); // 288 bytes ??????
            push_chunk(288, false, "trade_prices", iob_trade_prices);
            push_chunk(84, false, "figure_names", iob_figure_names);

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

            push_chunk(1596, false, "scenario_info", iob_scenario_info);

            /////////////////////

//                state->max_game_year = create_savegame_piece(4, false, ""); // MISSING
//                state->earthquake = create_savegame_piece(60, false, ""); // MISSING
//                state->emperor_change_state = create_savegame_piece(4, false, ""); // MISSING

            push_chunk(48000, true, "messages", iob_messages); // 94000 + 533 --> 94532 + 4 = 94536
            push_chunk(182, false, "message_extra", iob_message_extra); // ok
//            push_chunk(10, false, "population_messages", iob_population_messages); // ok
//            push_chunk(80, false, "message_counts", iob_message_counts); // ok
//            push_chunk(80, false, "message_delays", iob_message_delays); // ok

            push_chunk(8, false, "building_list_burning_totals", iob_building_list_burning_totals); // ok
            push_chunk(4, false, "figure_sequence", iob_figure_sequence); // ok
            push_chunk(12, false, "scenario_starting_rank", iob_scenario_starting_rank); // ok
            push_chunk(3232, true, "invasion_warnings", iob_invasion_warnings); // 94743 + 31 --> 94774 + 4 = 94778
            push_chunk(4, false, "scenario_is_custom", iob_scenario_is_custom); // ok
            push_chunk(8960, false, "city_sounds", iob_city_sounds); // ok
            push_chunk(4, false, "building_extra_highest_id", iob_building_highest_id); // ok
            push_chunk(8804, false, "figure_traders", iob_figure_traders); // +4000 ???

            push_chunk(1000, true, "building_list_burning", iob_building_list_burning); // ok
            push_chunk(1000, true, "building_list_small", iob_building_list_small); // ok
            push_chunk(8000, true, "building_list_large", iob_building_list_large); // ok

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
            push_chunk(32, false, "junk7a", iob_junk7a); // unknown bytes
            push_chunk(24, false, "junk7b", iob_junk7b); // unknown bytes
            push_chunk(39200, false, "building_storages", iob_building_storages); // storage instructions

            push_chunk(2880, true, "trade_route_limit", iob_trade_route_limit); // ok
            push_chunk(2880, true, "trade_route_traded", iob_trade_route_traded); // ok

//                state->building_barracks_tower_sentry = create_savegame_piece(4, false, "");
//                state->building_extra_sequence = create_savegame_piece(4, false, "");
//                state->routing_counters = create_savegame_piece(16, false, "");
//                state->building_count_culture3 = create_savegame_piece(40, false, "");
//                state->enemy_armies = create_savegame_piece(900, false, "");

            // 12 bytes     00 00 00 00 ???
            // 16 bytes     00 00 00 00 ???
            // 22 bytes     00 00 00 00 ???
            push_chunk(12, false, "junk8a", iob_junk8a); // unknown bytes
            push_chunk(16, false, "junk8b", iob_junk8b); // unknown bytes
            push_chunk(22, false, "junk8c", iob_junk8c); // unknown bytes

//                state->last_invasion_id = create_savegame_piece(2, false, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

            push_chunk(65, false, "scenario_map_name", iob_scenario_map_name); // ok
            push_chunk(32, false, "bookmarks", iob_bookmarks); // ok
            push_chunk(4, false, "tutorial_part3", iob_junk9a); // ok ????

//            int t_sub = 228;

            // 8 bytes      00 00 00 00 ???
            push_chunk(8, false, "junk9a", iob_junk9b);
            push_chunk(396, false, "junk9b", iob_junk9c);

            // 51984 bytes  00 00 00 00 ???
            push_chunk(51984, false, "soil_fertility_grid", iob_soil_fertility_grid);


            // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
            push_chunk(18600, false, "scenario_events", iob_scenario_events);

            // 28 bytes     2F 01 00 00 ???
            // 13416 bytes  00 00 00 00 ??? (200 less for non-expanded file)
            // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
            push_chunk(28, false, "junk10a", iob_junk10a);
            push_chunk(version.minor < 149 ? 13216 : 13416, false, "junk10b", iob_junk10b);
            push_chunk(8200, false, "junk10c", iob_junk10c);

            push_chunk(1280, true, "junk11", iob_junk11); // unknown compressed data

            push_chunk(version.minor < 160 ? 15200 : 19600, true, "empire_objects", iob_empire_objects);
            push_chunk(16200, true, "empire_routes", iob_empire_map_routes);

            // 51984 bytes  FF FF FF FF ???          // (228²) * 1 ?????????????????
            push_chunk(51984, false, "GRID02_8BIT", iob_GRID02_8BIT); // todo: 1-byte grid

            // 20 bytes     19 00 00 00 ???
            push_chunk(20, false, "junk14", iob_junk14);

            // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
            push_chunk(528, false, "bizarre_ordered_fields_1", iob_bizarre_ordered_fields_1);

            push_chunk(36, true, "floodplain_settings", iob_floodplain_settings); // floodplain_settings
            push_chunk(207936, true, "GRID03_32BIT", iob_GRID03_32BIT); // todo: 4-byte grid

            // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
            push_chunk(312, false, "bizarre_ordered_fields_3", iob_bizarre_ordered_fields_3); // 71x 4-bytes emptiness

            // 64 bytes     00 00 00 00 ???
            push_chunk(64, false, "junk16", iob_junk16); // 71x 4-bytes emptiness
            push_chunk(41, false, "tutorial_part1", iob_tutorial_flags); // 41 x 1-byte flag fields
            push_chunk(51984, true, "floodplain_soil_depletion", iob_soil_unk_grid);

            // lone byte ???
            push_chunk(1, false, "junk17", iob_junk17);
            push_chunk(51984, true, "moisture_grid", iob_moisture_grid);

            // 672 bytes    0F 00 00 00 ??? 28 x 24-byte chunk
            push_chunk(672, false, "bizarre_ordered_fields_2", iob_bizarre_ordered_fields_2);

            // 20 bytes     00 00 00 00 ???
            // 4800 bytes   00 00 00 00 ???
            push_chunk(20, false, "junk18", iob_junk18);
            push_chunk(4800, false, "bizarre_ordered_fields_4", iob_bizarre_ordered_fields_4);

            break;
        }
    }
}
const file_version_t *FileManager::get_file_version() {
    return &file_version;
}

buffer *FileManager::push_chunk(int size, bool compressed, const char *name, io_buffer *iob) {
    // add empty piece onto the stack
    file_chunks.push_back(file_chunk_t());
    auto chunk = &file_chunks.at(file_chunks.size() - 1);

    // fill info
    chunk->compressed = compressed;
    safe_realloc_for_size(&chunk->buf, size);
    strncpy(chunk->name, name, 99);

    // fill io_buffer content
    if (iob != nullptr) {
        iob->hook(chunk->buf, size, compressed, name);
        chunk->iob = iob;
    }

    // return linked buffer pointer so that it can be assigned for read/write access later
    return chunk->buf;
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
        set_image_grid_correction_shift(539); //14791
    else
        set_image_grid_correction_shift(0); //14252

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
//    auto state = &buffers;
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
//    auto state = &buffers;
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
    for (int i = 0; i < num_chunks(); ++i)
        file_chunks.at(i).iob->read();

//    building_barracks_load_state(state->building_barracks_tower_sentry);
//    building_count_load_state(state->building_count_industry,
//                              state->building_count_culture1,
//                              state->building_count_culture2,
//                              state->building_count_culture3,
//                              state->building_count_military,
//                              state->building_count_support);

//    scenario_emperor_change_load_state(state->emperor_change_time, state->emperor_change_state);

//    city_culture_load_state(state->culture_coverage);

//    scenario_max_year_load_state(state->max_game_year);
//    scenario_earthquake_load_state(state->earthquake);

//    scenario_gladiator_revolt_load_state(state->gladiator_revolt);
//    map_routing_load_state(state->routing_counters);
//    enemy_armies_load_state(state->enemy_armies, state->enemy_army_totals);
//    scenario_invasion_load_state(state->last_invasion_id, state->invasion_warnings);
}
void FileManager::write_state() {
    for (int i = 0; i < num_chunks(); ++i)
        file_chunks.at(i).iob->write();
}