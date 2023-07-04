#ifndef PLATFORM_ARGUMENTS_H
#define PLATFORM_ARGUMENTS_H

struct ozymandias_args {
    const char *data_directory;
    int display_scale_percentage;
    int cursor_scale_percentage;
    int game_engine_env;
    int game_engine_debug_mode;
    bool window_mode;
    int window_width = 0, window_height = 0;
};

extern ozymandias_args ozymandias_core;
int platform_parse_arguments(int argc, char **argv, ozymandias_args &output_args);

#endif // PLATFORM_ARGUMENTS_H
