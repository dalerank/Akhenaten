#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "core/vec2i.h"
#include "platform/platform.h"

struct AVFrame;

#ifdef GAME_PLATFORM_WIN

struct SwsContext;
struct AVOutputFormat;
struct AVStream;
struct AVFormatContext;
struct AVCodecContext;
struct AVPacket;

class MovieWriter {
	const uint16_t width, height;
	uint16_t iframe;
	uint16_t frameRate;

	SwsContext* swsCtx = nullptr;
	const AVOutputFormat* fmt = nullptr;
	AVStream* stream = nullptr;
	AVFormatContext* fc = nullptr;
	AVCodecContext* ctx = nullptr;
	AVPacket *pkt = nullptr;

	AVFrame *rgbpic = nullptr;
	AVFrame *yuvpic = nullptr;

	std::vector<uint8_t> pixels;

public:
	MovieWriter(const std::string& filename, const unsigned int width, const unsigned int height, const int frameRate = 25);

	void addFrame(const uint8_t* pixels, AVFrame** yuvout = nullptr);
	void addFrame(AVFrame* yuvframe);
	vec2i frameSize() const { return {width, height}; }
	
	~MovieWriter();
};
#else

class MovieWriter {
public:
	MovieWriter(const std::string &, const unsigned int, const unsigned int, const int) {}

	void addFrame(const uint8_t *pixels, AVFrame **yuvout = nullptr) {}
	void addFrame(AVFrame *yuvframe) {}
	vec2i frameSize() const { return {0, 0}; }

	~MovieWriter() {};
};

#endif // GAME_PLATFORM_WIN
