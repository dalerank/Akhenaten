#pragma once

#include "lame.h"
#include "core/vfs/vfs.h"

struct lame_helper {
	static const int PCM_SIZE = 4096;
	static const int MP3_SIZE = 4096;

    static void init_decoder_tables();

    lame_helper();
	~lame_helper();

	//Decode a mp3 to pcm
	vfs::reader decode(const char* mp3_in);	
};
