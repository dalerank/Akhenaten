#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>
#include "core/vec2i.h"
#include "platform/platform.h"

#ifdef GAME_PLATFORM_WIN

struct vpx_codec_ctx;
struct vpx_image;

class MovieWriter {
	const uint16_t width, height;
	uint32_t iframe;
	uint16_t frameRate;

	vpx_codec_ctx* codec = nullptr;
	vpx_image* yuv_image = nullptr;
	
	std::ofstream output_file;
	std::string filename;
	std::vector<uint8_t> encoded_frames; // Store encoded frames before writing WebM header
	
	// RGB to YUV conversion buffer
	std::vector<uint8_t> yuv_buffer;

	bool initialized = false;

	// Simple RGB to YUV420 conversion
	void convertRGBtoYUV420(const uint8_t* rgb, uint8_t* yuv);

public:
	MovieWriter(const std::string& filename, const unsigned int width, const unsigned int height, const int frameRate = 25);

	void addFrame(const uint8_t* pixels);
	vec2i frameSize() const { return {width, height}; }
	
	~MovieWriter();
};
#else

class MovieWriter {
public:
	MovieWriter(const std::string &, const unsigned int, const unsigned int, const int) {}

	void addFrame(const uint8_t *pixels) {}
	vec2i frameSize() const { return {0, 0}; }

	~MovieWriter() {};
};

#endif // GAME_PLATFORM_WIN
