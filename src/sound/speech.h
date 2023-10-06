#pragma once

#include "content/vfs.h"

vfs::path sound_speed_filename(const char *filename);
bool sound_speech_file_exist(const char *filename);
void sound_speech_set_volume(int percentage);
void sound_speech_play_file(const char* filename, int volume = 40);
void sound_speech_stop(void);