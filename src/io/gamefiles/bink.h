#pragma once

#include <stdint.h>

struct bink_movie;
using bink = bink_movie*;
using bink_audio_sink = void (*)(void* userdata, const void* data, int len);

bink bink_open(const char* filename);
void bink_close(bink movie);

int bink_get_width(bink movie);
int bink_get_height(bink movie);
int bink_get_micros_per_frame(bink movie);

int bink_has_audio(bink movie);
int bink_get_audio_channels(bink movie);
int bink_get_audio_sample_rate(bink movie);
int bink_get_audio_bitdepth(bink movie);

int bink_first_frame(bink movie);
int bink_next_frame(bink movie);
int bink_prebuffer_frames(bink movie, int frame_count, bink_audio_sink sink, void* userdata);
int bink_current_audio_is_prebuffered(bink movie);

const uint32_t* bink_get_frame_rgba(bink movie);
const void* bink_get_frame_audio(bink movie);
int bink_get_frame_audio_size(bink movie);
