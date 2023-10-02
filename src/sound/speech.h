#pragma once

void sound_speech_set_volume(int percentage);
void sound_speech_play_file(const char* filename, int volume = 40);
void sound_speech_stop(void);