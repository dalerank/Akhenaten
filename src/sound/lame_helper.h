#pragma once

#include "lame.h"
#include "content/vfs.h"

struct lame_helper {
	static const int PCM_SIZE = 4096;
	static const int MP3_SIZE = 4096;

	void write_wave_header(FILE * const, int, int, int, int);
	void write_32_bits_low_high(FILE*, int);
	void write_16_bits_low_high(FILE*, int);

	lame_helper();
	~lame_helper();

	//Decode a mp3 to pcm
	vfs::reader decode(const char* mp3_in);	
};
