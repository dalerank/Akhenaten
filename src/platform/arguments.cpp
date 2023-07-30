#include "arguments.h"

#include "io/log.h"
#include "core/version.h"
#include "platform/platform.h"

#include <SDL.h>

#define CURSOR_SCALE_ERROR_MESSAGE "Option --cursor-scale must be followed by a scale value of 1, 1.5 or 2"
#define DISPLAY_SCALE_ERROR_MESSAGE "Option --display-scale must be followed by a scale value between 0.5 and 5"
#define UNKNOWN_OPTION_ERROR_MESSAGE "Option %s not recognized"

ozymandias_args ozymandias_core;

static int parse_decimal_as_percentage(const char *str) {
    const char *start = str;
    char *end;
    long whole = SDL_strtol(start, &end, 10);
    int percentage = 100 * (int) whole;
    if (*end == ',' || *end == '.') {
        end++;
        start = end;
        long fraction = SDL_strtol(start, &end, 10);
        switch (end - start) {
            case 0:
                break;
            case 1:
                percentage += fraction * 10;
                break;
            case 2:
                percentage += fraction;
                break;
            default: {
                int fraction_digits = (int) (end - start);
                while (fraction_digits > 2) {
                    fraction = fraction / 10;
                    fraction_digits--;
                }
                percentage += fraction;
                break;
            }
        }
    }
    if (*end) {
        // still some characters left, print out warning
        SDL_Log("Invalid decimal: %s", str);
        return -1;
    }
    return percentage;
}

int platform_parse_arguments(int argc, char **argv, ozymandias_args &output_args) {
    int ok = 1;

    // Set sensible defaults
    memset(output_args.data_directory, 256, 0);
    output_args.display_scale_percentage = 100;
    output_args.cursor_scale_percentage = 100;
    output_args.game_engine_env = 1; // run pharaoh by default
    output_args.game_engine_debug_mode = 0;
    output_args.window_mode = false;

    snprintf(output_args.version_str, 31, "%u.%u.%u b%u %s", GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVSN, GAME_BUILD_NUMBER, GAME_PLATFORM_NAME);

    for (int i = 1; i < argc; i++) {
        // we ignore "-psn" arguments, this is needed to launch the app
        // from the Finder on macOS.
        // https://hg.libsdl.org/SDL/file/c005c49beaa9/test/testdropfile.c#l47
        if (SDL_strncmp(argv[i], "-psn", 4) == 0)
            continue;

        if (SDL_strcmp(argv[i], "--caesar3") == 0)
            output_args.game_engine_env = 0;
        else if (SDL_strcmp(argv[i], "--debug") == 0)
            output_args.game_engine_debug_mode = 1;
        else if (SDL_strcmp(argv[i], "--window") == 0)
            output_args.window_mode = true;
        else if (SDL_strcmp(argv[i], "--tutorial_skip") == 0) {
            sscanf("%d", argv[i + 1], &output_args.tutorial_skip);
            ++i;
        }  else if (SDL_strcmp(argv[i], "--render") == 0) {
            strcpy(output_args.driver, argv[i + 1]);
            i++;
        } else if (SDL_strcmp(argv[i], "--display-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                i++;
                if (percentage < 50 || percentage > 500) {
                    log_info(DISPLAY_SCALE_ERROR_MESSAGE);
                    ok = 0;
                } else {
                    output_args.display_scale_percentage = percentage;
                }
            } else {
                log_info(DISPLAY_SCALE_ERROR_MESSAGE);
                ok = 0;
            }
        } else if (SDL_strcmp(argv[i], "--size") == 0) {
            if (i + 1 < argc) {
                SDL_sscanf(argv[i + 1], "%dx%d", &output_args.window_width, &output_args.window_height);
                i++;
            } else {
                log_info(DISPLAY_SCALE_ERROR_MESSAGE);
                ok = 0;
            }
        } else if (SDL_strcmp(argv[i], "--cursor-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                i++;
                if (percentage == 100 || percentage == 150 || percentage == 200)
                    output_args.cursor_scale_percentage = percentage;
                else {
                    log_info(CURSOR_SCALE_ERROR_MESSAGE);
                    ok = 0;
                }
            } else {
                log_info(CURSOR_SCALE_ERROR_MESSAGE);
                ok = 0;
            }
        } else if (SDL_strcmp(argv[i], "--help") == 0)
            ok = 0;
        else if (SDL_strncmp(argv[i], "--", 2) == 0) {
            log_info(UNKNOWN_OPTION_ERROR_MESSAGE, argv[i]);
            ok = 0;
        } else {
            strcpy(output_args.data_directory, argv[i]);
        }
    }

    if (!ok) {
        log_info("Usage: ozymandias [ARGS] [DATA_DIR]");
        log_info("ARGS may be:");
        log_info("--display-scale NUMBER");
        log_info("          Scales the display by a factor of NUMBER. Number can be between 0.5 and 5");
        log_info("--cursor-scale NUMBER");
        log_info("          Scales the mouse cursor by a factor of NUMBER. Number can be 1, 1.5 or 2");
        log_info("--window");
        log_info("          setup window mode on");
        log_info("--debug");
        log_info("          Prints additional debug information on the screen");
        log_info("The last argument, if present, is interpreted as data directory of the Pharaoh installation");
    }

    return ok;
}
