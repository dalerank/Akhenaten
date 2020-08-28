#include "platform/prefs.h"

#include "platform/platform.h"
#include "core/game_environment.h"

#include "SDL.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTABLE

static FILE *open_pref_file(const char *filename, const char *mode)
{
    #if SDL_VERSION_ATLEAST(2, 0, 1)
        if (platform_sdl_version_at_least(2, 0, 1)) {
            #ifndef PORTABLE
                char *dir_path = SDL_GetPrefPath("bvschaik", "julius");
            #else
                char *dir_path = SDL_GetBasePath();
            #endif

            // because C is crap
            size_t dir_len = strlen(dir_path);
            char *file_path = malloc((strlen(filename) + dir_len + 2) * sizeof(char)); // write the full filename path into the char* buffer
            if (!file_path) {
                SDL_free(dir_path);
                return NULL;
            }
            strcpy(file_path, dir_path);
            strcpy(&file_path[dir_len], filename);
            SDL_free(dir_path);

            FILE *fp = fopen(file_path, mode);
            free(file_path);
            return fp;
        }
        #endif
    return NULL;
}
const char *pref_get_gamepath(void)
{
    static char data_dir[1000];
    FILE *fp = open_pref_file(get_engine_pref_path(), "r"); // open pref file for specific game
    if (fp) {
        size_t length = fread(data_dir, 1, 1000, fp);
        fclose(fp);
        if (length > 0) {
            data_dir[length] = 0;
            return data_dir; // return path to game data
        }
    }
    return NULL;
}
void pref_save_gamepath(const char *data_dir)
{
    FILE *fp = open_pref_file(get_engine_pref_path(), "w");
    if (fp) {
        fwrite(data_dir, 1, strlen(data_dir), fp);
        fclose(fp);
    }
}
