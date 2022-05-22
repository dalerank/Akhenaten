#include "manager.h"
#include "io/gamestate/chunks.h"
#include <string.h>
#include <cinttypes>
#include "io/io.h"
#include "core/string.h"
#include "core/zip.h"
#include "io/log.h"
#include "grid/image.h"
#include "core/stopwatch.h"

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

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

FileIOManager FILEIO;

///

void FileIOManager::clear() {
    loaded = false;
    strncpy_safe(file_path, "", MAX_FILE_NAME);
    file_size = 0;
    file_offset = 0;
    file_format = FILE_FORMAT_NULL;
    file_version = -1;
    for (int i = 0; i < num_chunks(); ++i)
        file_chunks.at(i).VALID = false;
    alloc_index = 0;
}
void FileIOManager::init_chunk_schema() {
    switch (file_format) {
        case FILE_FORMAT_MAP:
            push_chunk(4, false, "scenario_mission_index", iob_scenario_mission_id);
            push_chunk(4, false, "file_version", iob_file_version);
            push_chunk(6004, false, "chunks_schema", iob_chunks_schema);

            push_chunk(207936, false, "image_grid", iob_image_grid);
            push_chunk(51984, false, "edge_grid", iob_edge_grid);
            push_chunk(207936, false, "terrain_grid", iob_terrain_grid);
            push_chunk(51984, false, "bitfields_grid", iob_bitfields_grid);
            push_chunk(51984, false, "random_grid", iob_random_grid);
            push_chunk(51984, false, "elevation_grid", iob_elevation_grid);

            push_chunk(8, false, "random_iv", iob_random_iv);
            push_chunk(8, false, "city_view_camera", iob_city_view_camera);
            push_chunk(1592, false, "scenario_info", iob_scenario_info);

            push_chunk(51984, false, "soil_fertility_grid", iob_soil_fertility_grid);
            push_chunk(18600, false, "scenario_events", iob_scenario_events);
            push_chunk(28, false, "scenario_events_extra", iob_scenario_events_extra);
            push_chunk(1280, true, "junk11", iob_junk11);
            push_chunk(file_version < 160 ? 15200 : 19600, true, "empire_map_objects", iob_empire_map_objects);
            push_chunk(16200, true, "empire_map_routes", iob_empire_map_routes);
            push_chunk(51984, false, "vegetation_growth", iob_vegetation_growth); // not sure what's the point of this in MAP...

            push_chunk(file_version < 147 ? 32 : 36, true, "floodplain_settings", iob_floodplain_settings);
            push_chunk(288, false, "trade_prices", iob_trade_prices);
            push_chunk(51984, true, "moisture_grid", iob_moisture_grid);

            break;
        case FILE_FORMAT_PAK:
        case FILE_FORMAT_SAV:
            push_chunk(4, false, "scenario_mission_index", iob_scenario_mission_id);
            push_chunk(4, false, "file_version", iob_file_version);
            push_chunk(6004, false, "chunks_schema", iob_chunks_schema);

            push_chunk(207936, true, "image_grid", iob_image_grid);                         // (228²) * 4 <<
            push_chunk(51984, true, "edge_grid", iob_edge_grid);                            // (228²) * 1
            push_chunk(103968, true, "building_grid", iob_building_grid);                   // (228²) * 2
            push_chunk(207936, true, "terrain_grid", iob_terrain_grid);                     // (228²) * 4 <<
            push_chunk(51984, true, "aqueduct_grid", iob_aqueduct_grid);                    // (228²) * 1
            push_chunk(103968, true, "figure_grid", iob_figure_grid);                       // (228²) * 2
            push_chunk(51984, true, "bitfields_grid", iob_bitfields_grid);                  // (228²) * 1
            push_chunk(51984, true, "sprite_grid", iob_sprite_grid);                        // (228²) * 1
            push_chunk(51984, false, "random_grid", iob_random_grid);                       // (228²) * 1
            push_chunk(51984, true, "desirability_grid", iob_desirability_grid);            // (228²) * 1
            push_chunk(51984, true, "elevation_grid", iob_elevation_grid);                  // (228²) * 1
            push_chunk(103968, true, "building_damage_grid", iob_damage_grid);              // (228²) * 2 <<
            push_chunk(51984, true, "aqueduct_backup_grid", iob_aqueduct_backup_grid);      // (228²) * 1
            push_chunk(51984, true, "sprite_backup_grid", iob_sprite_backup_grid);          // (228²) * 1
            push_chunk(776000, true, "figures", iob_figures);
            push_chunk(2000, true, "route_figures", iob_route_figures);
            push_chunk(500000, true, "route_paths", iob_route_paths);
            push_chunk(7200, true, "formations", iob_formations);
            push_chunk(12, false, "formations_info", iob_formations_info);
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
            push_chunk(12, false, "empire_map_params", iob_empire_map_params); // ok ???
            push_chunk(6466, true, "empire_cities", iob_empire_cities); // 83920 + 7681 --> 91601
            push_chunk(288, false, "building_count_industry", iob_building_count_industry); // 288 bytes ??????
            push_chunk(288, false, "trade_prices", iob_trade_prices);
            push_chunk(84, false, "figure_names", iob_figure_names);

//                state->culture_coverage = create_savegame_piece(60, false, ""); // MISSING
            push_chunk(1592, false, "scenario_info", iob_scenario_info);

            /////////////////////

            push_chunk(4, false, "max_year", iob_max_year);
            push_chunk(48000, true, "messages", iob_messages); // 94000 + 533 --> 94532 + 4 = 94536
            push_chunk(182, false, "message_extra", iob_message_extra); // ok

            push_chunk(8, false, "building_burning_list_info", iob_building_burning_list_info); // ok
            push_chunk(4, false, "figure_sequence", iob_figure_sequence); // ok
            push_chunk(12, false, "scenario_carry_settings", iob_scenario_carry_settings); // ok
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

            // 32 bytes     00 00 00 00 ??? 8 x int
            // 24 bytes     00 00 00 00 ??? 6 x int
            push_chunk(32, false, "junk7a", iob_junk7a); // unknown bytes
            push_chunk(24, false, "junk7b", iob_junk7b); // unknown bytes
            push_chunk(39200, false, "building_storages", iob_building_storages); // storage instructions

            push_chunk(2880, true, "trade_routes_limits", iob_trade_routes_limits); // ok
            push_chunk(2880, true, "trade_routes_traded", iob_trade_routes_traded); // ok

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
            push_chunk(50, false, "junk8", iob_routing_stats); // unknown bytes

//                state->last_invasion_id = create_savegame_piece(2, false, "");
//                state->building_extra_corrupt_houses = create_savegame_piece(8, false, "");

            push_chunk(65, false, "scenario_map_name", iob_scenario_map_name); // ok
            push_chunk(32, false, "bookmarks", iob_bookmarks); // ok


            // 12 bytes     00 00 00 00 ??? 3 x int
            // 396 bytes    00 00 00 00 ??? 99 x int
            push_chunk(12, false, "junk9a", iob_junk9a); // ok ????
            push_chunk(396, false, "junk9b", iob_junk9b);

            // 51984 bytes  00 00 00 00 ???
            push_chunk(51984, false, "soil_fertility_grid", iob_soil_fertility_grid);

            // 18600 bytes  00 00 00 00 ??? 150 x 124-byte chunk
            // 28 bytes     2F 01 00 00 ???
            push_chunk(18600, false, "scenario_events", iob_scenario_events);
            push_chunk(28, false, "scenario_events_extra", iob_scenario_events_extra);

            // 11000 bytes  00 00 00 00 ??? 50 x 224-byte chunk (50 x 220 for old version)
            // 2200 bytes   00 00 00 00 ??? 50 x 44-byte chunk
            // 16 bytes     00 00 00 00 ??? 4 x int
            // 8200 bytes   00 00 00 00 ??? 10 x 820-byte chunk
            push_chunk(file_version < 149 ? 11000 : 11200, false, "junk10a", iob_junk10a);
            push_chunk(2200, false, "junk10b", iob_junk10b);
            push_chunk(16, false, "junk10c", iob_junk10c);
            push_chunk(8200, false, "junk10d", iob_junk10d);

            // 1280 bytes   00 00 00 00 ??? 40 x 32-byte chunk
            push_chunk(1280, true, "junk11", iob_junk11); // unknown compressed data

            push_chunk(file_version < 160 ? 15200 : 19600, true, "empire_map_objects", iob_empire_map_objects);
            push_chunk(16200, true, "empire_map_routes", iob_empire_map_routes);

            // 51984 bytes  FF FF FF FF ???          // (228²) * 1 ?????????????????
            push_chunk(51984, false, "vegetation_growth", iob_vegetation_growth); // todo: 1-byte grid

            // 20 bytes     19 00 00 00 ???
            push_chunk(20, false, "junk14", iob_junk14);

            // 528 bytes    00 00 00 00 ??? 22 x 24-byte chunk
            push_chunk(528, false, "bizarre_ordered_fields_1", iob_bizarre_ordered_fields_1);

            push_chunk(file_version < 147 ? 32 : 36, true, "floodplain_settings", iob_floodplain_settings); // floodplain_settings
            push_chunk(207936, true, "GRID03_32BIT", iob_GRID03_32BIT); // todo: 4-byte grid

            // 312 bytes    2B 00 00 00 ??? 13 x 24-byte chunk
            push_chunk(312, false, "bizarre_ordered_fields_4", iob_bizarre_ordered_fields_4); // 71x 4-bytes emptiness

            // 64 bytes     00 00 00 00 ???
            push_chunk(64, false, "junk16", iob_junk16); // 71x 4-bytes emptiness
            push_chunk(41, false, "tutorial_flags_struct", iob_tutorial_flags); // 41 x 1-byte flag fields
            push_chunk(51984, true, "GRID04_8BIT", iob_GRID04_8BIT);

            // lone byte ???
            push_chunk(1, false, "junk17", iob_junk17);
            push_chunk(51984, true, "moisture_grid", iob_moisture_grid);

            // 240 bytes    0F 00 00 00 ??? 10 x 24-byte chunk
            // 432 bytes    0F 00 00 00 ??? 18 x 24-byte chunk
            push_chunk(240, false, "bizarre_ordered_fields_2", iob_bizarre_ordered_fields_2);
            push_chunk(432, false, "bizarre_ordered_fields_3", iob_bizarre_ordered_fields_3);

            // 8 bytes      00 00 00 00 ??? 2 x int
            push_chunk(8, false, "junk18", iob_junk18);

            if (file_version >= 160) {

                // 12 bytes     00 00 00 00 ??? 3 x int
                push_chunk(20, false, "junk19", iob_junk19);

                // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
                // 648 bytes   00 00 00 00 ??? 27 x 24-byte chunk
                // 360 bytes   00 00 00 00 ??? 15 x 24-byte chunk
                // 1344 bytes  00 00 00 00 ??? 56 x 24-byte chunk
                // 1800 bytes  00 00 00 00 ??? 75 x 24-byte chunk <--- I can't even... their own schema is wrong. it's >> 74! <<
                push_chunk(648, false, "bizarre_ordered_fields_5", iob_bizarre_ordered_fields_5);
                push_chunk(648, false, "bizarre_ordered_fields_6", iob_bizarre_ordered_fields_6);
                push_chunk(360, false, "bizarre_ordered_fields_7", iob_bizarre_ordered_fields_7);
                push_chunk(1344, false, "bizarre_ordered_fields_8", iob_bizarre_ordered_fields_8);
                push_chunk(1776, false, "bizarre_ordered_fields_9", iob_bizarre_ordered_fields_9);

            }
            break;
    }
}
//bool FileIOManager::determine_version_from_file(const char *filename, const int offset) {
//
//
//
//    // read file header data (required for schema...)
//    GamestateIO::read_file_version
//    file_version = read_file_version(file_path, file_offset);
//
//    // determine appropriate schema and related data
//    if (file_has_extension(filename, "pak") || file_has_extension(filename, "sav"))
//        file_format = FILE_FORMAT_SAV;
//    else if (file_has_extension(filename, "map"))
//        file_format = FILE_FORMAT_MAP;
//    if (file_has_extension(filename, "pak") && file_version < 149)
//        set_image_grid_correction_shift(539); //14791
//    else
//        set_image_grid_correction_shift(0); //14252
//
//    return true;
//}

buffer *FileIOManager::push_chunk(int size, bool compressed, const char *name, io_buffer *iob) {
    // add empty piece onto the stack if we're beyond the current capacity
    if (alloc_index >= file_chunks.size())
        file_chunks.push_back(file_chunk_t());

    // fill info
    auto chunk = &file_chunks.at(alloc_index);
    chunk->compressed = compressed;
    safe_realloc_for_size(&chunk->buf, size);
    strncpy(chunk->name, name, 99);

    // fill io_buffer content
    if (iob != nullptr) {
        iob->hook(chunk->buf, size, compressed, name);
        chunk->iob = iob;
        chunk->VALID = true;
    }

    // advance allocator index
    alloc_index++;

    // return linked buffer pointer so that it can be assigned for read/write access later
    return chunk->buf;
}
const int FileIOManager::num_chunks() {
    return alloc_index;
}

int findex;
char *fname;
static void export_unzipped(file_chunk_t *chunk) {
    char *lfile = (char *) malloc(200);
//    sprintf(lfile, "DEV_TESTING/zip/%03i_%i_%s", findex + 1, chunk->buf->size(), fname);
    sprintf(lfile, "DEV_TESTING/zip/%03i_%s", findex + 1, fname);
    FILE *log = fopen(lfile, "wb+");
    if (log)
        fwrite(chunk->buf->get_data(), chunk->buf->size(), 1, log);
    fclose(log);
    free(lfile);
}
static void log_hex(file_chunk_t *chunk, int i, int offs, int num_chunks) {
    // log first few bytes of the filepiece
    size_t s = chunk->buf->size() < 16 ? chunk->buf->size() : 16;
    char hexstr[40] = {0};
    for (int b = 0; b < s; b++) {
        char hexcode[3] = {0};
        uint8_t inbyte = chunk->buf->get_value(b);
        snprintf(hexcode, sizeof(hexcode)/sizeof(hexcode[0]), "%02X", inbyte);
        strncat(hexstr, hexcode, sizeof(hexcode)/sizeof(hexcode[0]) - 1);
        if ((b + 1) % 4 == 0 || (b + 1) == s)
            strncat(hexstr, " ", 2);
    }

    // Unfortunately, MSVCRT only supports C89 and thus, "zu" leads to segfault
    SDL_Log("Piece %s %03i/%i : %8i@ %-36s(%" PRI_SIZET ") %s", chunk->compressed ? "(C)" : "---", i + 1, num_chunks,
            offs, hexstr, chunk->buf->size(), fname);
}

static char compress_buffer[COMPRESS_BUFFER_SIZE];
static bool read_compressed_chunk(FILE *fp, buffer *buf, int filepiece_size) {
    // check that the stream size isn't above maximum temp buffer
    if (filepiece_size > COMPRESS_BUFFER_SIZE)
        return false;

    // read 32-bit int header denoting size of compressed chunk
    uint32_t chunk_size = 0;
    fread(&chunk_size, 4, 1, fp);

    // if file signature says "uncompressed" well man, it's uncompressed. read as normal ignoring the directive
    if ((unsigned int) chunk_size == UNCOMPRESSED) {
        if (buf->from_file(filepiece_size, fp) != filepiece_size)
            return false;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        int csize = fread(compress_buffer, 1, chunk_size, fp);
        if (csize != chunk_size) {
            SDL_Log("Incorrect chunk size, expected %i, found %i", chunk_size, csize);
            return false;
        }
        int bsize = zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size);
        if (bsize != buf->size()) {
            SDL_Log("Incorrect buffer size, expected %i, found %i", buf->size(), bsize);
            return false;
        }
//        if (fread(compress_buffer, 1, chunk_size, fp) != chunk_size
//            || zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size) !=
//               buf->size())
//            return 0;
    }
//    buf->force_validate_unsafe_pls_use_carefully();

    return true;
}
static bool write_compressed_chunk(FILE *fp, buffer *buf, int bytes_to_write) {
    if (bytes_to_write > COMPRESS_BUFFER_SIZE)
        return false;

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
    return true;
}

static stopwatch WATCH;

bool FileIOManager::serialize(const char *filename, int offset, file_format_t format, const int version) {

    WATCH.START();

    // first, clear up the manager data and set the new file info
    clear();
    strncpy_safe(file_path, filename, MAX_FILE_NAME);
    file_offset = offset;
    file_format = format;
    file_version = version;

    // open file handle
    FILE *fp = file_open(dir_get_file(file_path, NOT_LOCALIZED), "wb");
    if (!fp) {
        log_error("Unable to save game, access denied.", 0, 0);
        goto failure;
    } else if (file_offset)
        fseek(fp, file_offset, SEEK_SET);

    // dump GAME STATE into buffers
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->write();
    }

    // init file chunks and buffer collection
    init_chunk_schema();

    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t *chunk = &file_chunks.at(i);

        int result = 0;
        if (chunk->compressed)
            result = write_compressed_chunk(fp, chunk->buf, chunk->buf->size());
        else
            result = chunk->buf->to_file(chunk->buf->size(), fp);

        // The last piece may be smaller than buf->size
        if (!result) {
            log_error("Unable to save game, write failure.", 0, 0);
            goto failure;
        }
    }

    // close file handle
    file_close(fp);

    SDL_Log("Saving game state to file %s %i@ --- VERSION: %i --- %" PRIu64 " milliseconds", file_path, file_offset, file_version,
            WATCH.STOP());

    return true;

failure:
    clear();
    return false;
}
bool FileIOManager::unserialize(const char *filename, int offset, file_format_t format, const int(*determine_file_version)(const char *fnm, int ofst)) {

    WATCH.START();

    // first, clear up the manager data and set the new file info
    clear();
    strncpy_safe(file_path, filename, MAX_FILE_NAME);
    file_offset = offset;
    file_format = format;

    // open file handle
    FILE *fp = file_open(dir_get_file(file_path, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        goto failure;
    } else if (file_offset)
        fseek(fp, file_offset, SEEK_SET);

    // determine file version based on provided format
    file_version = determine_file_version(file_path, offset);
    if (file_version == -1) {
        log_info("Invalid file and/or version header!", filename, 0);
        goto failure;
    }

    // init file chunks and buffer collection
    init_chunk_schema();

    // read file contents into buffers
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t *chunk = &file_chunks.at(i);
        findex = i;
        fname = chunk->name;

        auto offs = ftell(fp);

        bool result = false;
        if (chunk->compressed) {
            result = read_compressed_chunk(fp, chunk->buf, chunk->buf->size());
            if (!result) {
                log_error("Unable to read file, decompression failed.", 0, 0);
                goto failure;
            }
        } else {
            int got = chunk->buf->from_file(chunk->buf->size(), fp);
            int exp = chunk->buf->size();
            result = got == exp;
            if (!result) {
                SDL_Log("Incorrect buffer size, expected %i, found %i", exp, got);
                log_error("Unable to read file, chunk size incorrect.", 0, 0);
                goto failure;
            }
        }

        // ******** DEBUGGING ********
        export_unzipped(chunk); // export uncompressed buffer data to zip folder
        if (true) log_hex(chunk, i, offs, num_chunks()); // print full chunk read log info
        // ***************************
    }

    // close file handle
    file_close(fp);

    // load GAME STATE from buffers
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->read();
    }

    SDL_Log("Reading from file %s %i@ --- VERSION HEADER: %i --- %" PRIu64 " milliseconds", file_path, file_offset, file_version,
            WATCH.STOP());

    return true;

failure:
    clear();
    return false;
}