#include <core/log.h>
#include "file_io.h"

#include "manager.h"

//bool game_file_io_read_scenario(const char *filename) {
//    // TODO
//    return false;
//
////    init_scenario_data();
////    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
////    if (!fp) {
////        log_error("Unable to access file", filename, 0);
////        return false;
////    }
////    log_info("Loading scenario", filename, 0);
////    for (int i = 0; i < scenario_data.num_pieces; i++) {
////        int bytes_read = scenario_data.file_chunks[i].buf->from_file((size_t) scenario_data.file_chunks[i].buf->size(), fp);
////        if (bytes_read != scenario_data.file_chunks[i].buf->size()) {
////            log_error("Unable to load scenario", filename, 0);
////            file_close(fp);
////            return false;
////        }
////
//////        if (fread(scenario_data.pieces[i].buf->data, 1, scenario_data.pieces[i].buf->size, fp) != scenario_data.pieces[i].buf->size) {
//////            log_error("Unable to load scenario", filename, 0);
//////            file_close(fp);
//////            return 0;
//////        }
////    }
////    file_close(fp);
////
////    scenario_load_from_state(&scenario_data.state);
//    return true;
//}
//bool game_file_io_write_scenario(const char *filename) {
//    // TODO
//    return false;
////    log_info("Saving scenario", filename, 0);
////    init_scenario_data();
////    scenario_save_to_state(&scenario_data.state);
////
////    FILE *fp = file_open(filename, "wb");
////    if (!fp) {
////        log_error("Unable to save scenario", 0, 0);
////        return 0;
////    }
////    for (int i = 0; i < scenario_data.num_pieces; i++) {
////        fwrite(scenario_data.pieces[i].buf->data, 1, scenario_data.pieces[i].buf->size, fp);
////    }
////    file_close(fp);
////    return 1;
//}
bool game_file_io_read_saved_game(const char *filename, int offset) {
    if (!FileIO.read_from_file(filename, offset))
        return false;
    FileIO.load_state();
    return true;
}
bool game_file_io_write_saved_game(const char *filename) {
//    init_file_data();
//
//    log_info("Saving game", filename, 0);
////    savegame_version = SAVE_GAME_VERSION;
//    savegame_save_to_state(&file_data.state);
//
//    FILE *fp = file_open(filename, "wb");
//    if (!fp) {
//        log_error("Unable to save game", 0, 0);
//        return false;
//    }
//    write_file_pieces(fp);
//    file_close(fp);
    return true;
}
bool game_file_io_delete_saved_game(const char *filename) {
    log_info("Deleting game", filename, 0);
    int result = file_remove(filename);
    if (!result)
        log_error("Unable to delete game", 0, 0);

    return result;
}
