#ifndef GAME_FILE_H
#define GAME_FILE_H

#include <stdint.h>

bool game_start_loaded_scenario();

bool game_load_scenario(const char *filename, bool start_immediately = true);
bool game_load_scenario(const uint8_t *scenario_name, bool start_immediately = true);
bool game_load_scenario(int scenario_id, bool start_immediately = true);

/**
 * Load saved game
 * @param filename File to load
 * @return Boolean true on success, false on failure
 */
bool game_file_load_saved_game(const char *filename);

/**
 * Write saved game to disk
 * @param filename File to save to
 * @return Boolean true on success, false on failure
 */
bool game_file_write_saved_game(const char *filename);

/**
 * Delete saved game
 * @param filename File to delete
 * @return Boolean true on success, false on failure
 */
bool game_file_delete_saved_game(const char *filename);

/**
 * Write starting save for the current campaign mission
 */
void game_file_write_mission_saved_game(void);

#endif // GAME_FILE_H
