#pragma once

struct ozymandias_args {
    char data_directory[256] = {0};
    char version_str[32] = {0};
    int display_scale_percentage;
    int cursor_scale_percentage;
    int game_engine_env;
    int game_engine_debug_mode;
    bool window_mode;
    char driver[64] = {0};
    int window_width = 0, window_height = 0;
    int tutorial_skip = 0;
};

extern ozymandias_args ozymandias_core;
int platform_parse_arguments(int argc, char **argv, ozymandias_args &output_args);