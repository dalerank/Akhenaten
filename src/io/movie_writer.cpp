#include "movie_writer.h"

#include "core/log.h"

#ifdef GAME_PLATFORM_WIN

extern "C" {
	//#include <x264.h>
	#include <libswscale/swscale.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/mathematics.h>
	#include <libavformat/avformat.h>
	#include <libavformat/avio_internal.h>
	#include <libavformat/url.h>
	#include <libavutil/opt.h>
}

MovieWriter::MovieWriter(const std::string& filename, const unsigned int width_, const unsigned int height_, const int frameRate_) :
	width(width_), height(height_), iframe(0), frameRate(frameRate_), pixels(4 * width * height) 
{
	// Preparing to convert my generated RGB images to YUV frames.
	swsCtx = sws_getContext(width, height, AV_PIX_FMT_RGB24, width, height, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	pkt = new AVPacket();

	// Preparing the data concerning the format and codec,
	// in order to write properly the header, frame data and end of file.
	const std::string::size_type p(filename.find_last_of('.'));
	std::string ext = "";
	if (p != -1) {
		ext = filename.substr(p + 1);
	}

	fmt = av_guess_format(ext.c_str(), NULL, NULL);
	avformat_alloc_output_context2(&fc, NULL, NULL, filename.c_str());

	// Setting up the codec.
	const AVCodec* codec = avcodec_find_encoder_by_name("libvpx-vp9");
	AVDictionary* codec_options = NULL;
	av_dict_set(&codec_options, "crf", "0.5", 0);

	stream = avformat_new_stream(fc, codec);
	stream->time_base = AVRational{ 1, frameRate };

	ctx = avcodec_alloc_context3(codec);
	if (!ctx) {
		logs::info("Could not allocate video codec context\n");
	}

	ctx->width = width;
	ctx->height = height;
	ctx->pix_fmt = AV_PIX_FMT_YUV420P;
	ctx->time_base = AVRational{ 1, frameRate };

	if (avcodec_open2(ctx, codec, &codec_options) < 0) {
		logs::info("Could not open codec\n");
	}

	if (avcodec_parameters_from_context(stream->codecpar, ctx) < 0) {
		logs::info("Could not initialize stream parameters\n");
	}

	avcodec_open2(ctx, codec, &codec_options);
	av_dict_free(&codec_options);

	// Once the codec is set up, we need to let the container know
	// which codec are the streams using, in this case the only (video) stream.
	av_dump_format(fc, 0, filename.c_str(), 1);
	avio_open(&fc->pb, filename.c_str(), AVIO_FLAG_WRITE);

	// TODO Get a dict containing options that were not found.
	int ret = avformat_write_header(fc, &codec_options);
	av_dict_free(&codec_options);

	// Preparing the containers of the frame data:
	// Allocating memory for each RGB frame, which will be lately converted to YUV.
	rgbpic = av_frame_alloc();
	rgbpic->format = AV_PIX_FMT_RGB24;
	rgbpic->width = width;
	rgbpic->height = height;
	ret = av_frame_get_buffer(rgbpic, 1);

	// Allocating memory for each conversion output YUV frame.
	yuvpic = av_frame_alloc();
	yuvpic->format = AV_PIX_FMT_YUV420P;
	yuvpic->width = width;
	yuvpic->height = height;
	ret = av_frame_get_buffer(yuvpic, 1);

	// After the format, code and general frame data is set,
	// we can write the video in the frame generation loop:
	// std::vector<uint8_t> B(width*height*3);
}

void MovieWriter::addFrame(const uint8_t* pixels, AVFrame** yuvout) {
	// The AVFrame data will be stored as RGBRGBRGB... row-wise,
	// from left to right and from top to bottom.
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			// rgbpic->linesize[0] is equal to width.
			rgbpic->data[0][y * rgbpic->linesize[0] + 3 * x + 0] = pixels[y * 4 * width + 4 * x + 2];
			rgbpic->data[0][y * rgbpic->linesize[0] + 3 * x + 1] = pixels[y * 4 * width + 4 * x + 1];
			rgbpic->data[0][y * rgbpic->linesize[0] + 3 * x + 2] = pixels[y * 4 * width + 4 * x + 0];
		}
	}

	// Not actually scaling anything, but just converting
	// the RGB data to YUV and store it in yuvpic.
	sws_scale(swsCtx, rgbpic->data, rgbpic->linesize, 0, height, yuvpic->data, yuvpic->linesize);
	
	if (yuvout) {
		// The user may be willing to keep the YUV frame
		// to use it again.
		*yuvout = yuvpic;
	}
	
	addFrame(yuvpic);
}

// Function to flush the encoder and write remaining frames to disk
void flush_encoder(AVFormatContext *fmt_ctx, AVCodecContext *codec_ctx, int stream_index) {
	int ret;
	AVPacket pkt = {0};
	av_init_packet(&pkt);

	// Send NULL packet to flush the encoder
	ret = avcodec_send_frame(codec_ctx, nullptr);

	while (ret >= 0) {
		ret = avcodec_receive_packet(codec_ctx, &pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
			break;
		}

		// Write the packet to the output file
		av_packet_rescale_ts(&pkt, codec_ctx->time_base, fmt_ctx->streams[stream_index]->time_base);
		pkt.stream_index = stream_index;
		ret = av_interleaved_write_frame(fmt_ctx, &pkt);

		av_packet_unref(&pkt);
	}
}

void MovieWriter::addFrame(AVFrame* yuvframe) {
	av_init_packet(pkt);
	pkt->data = NULL;
	pkt->size = 0;

	// The PTS of the frame are just in a reference unit,
	// unrelated to the format we are using. We set them,
	// for instance, as the corresponding frame number.
	yuvframe->pts = iframe;

	int ret = avcodec_send_frame(ctx, yuvframe);
	if (ret < 0) {
		logs::info("Error sending frame to codec, errcode = %d\n", ret);
		return;
	}
	
	ret = avcodec_receive_packet(ctx, pkt);
	if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
		logs::info("Error receiving packet from codec, errcode = %d\n", ret);
		return;

	} else if (ret >= 0) {
		// We set the packet PTS and DTS taking in the account our FPS (second argument),
		// and the time base that our selected format uses (third argument).
		av_packet_rescale_ts(pkt, AVRational{ 1, frameRate }, stream->time_base);

		pkt->stream_index = stream->index;
		logs::info("Writing frame %d (size = %d)\n", iframe++, pkt->size);

		// Write the encoded frame to the mp4 file.
		av_interleaved_write_frame(fc, pkt);
		av_packet_unref(pkt);
	}
}

MovieWriter::~MovieWriter() {
	while (1) {
		int ret = avcodec_send_frame(ctx, NULL);
		if (ret == AVERROR_EOF) {
			break;
		} else if (ret < 0) {
			logs::info("Error sending frame to codec, errcode = %d\n", ret);
			return;
		}

		ret = avcodec_receive_packet(ctx, pkt);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
			logs::info("Error receiving packet from codec, errcode = %d\n", ret);
			return;
		} else if (ret >= 0) {
			//fflush(stdout);
			av_packet_rescale_ts(pkt, AVRational{ 1, frameRate }, stream->time_base);
			pkt->stream_index = stream->index;
			logs::info("Writing frame %d (size = %d)\n", iframe++, pkt->size);
			av_interleaved_write_frame(fc, pkt);
			av_packet_unref(pkt);
		} else {
			break;
		}
	}

	// Writing the end of the file.
	av_write_trailer(fc);

	// Closing the file.
	if (!(fmt->flags & AVFMT_NOFILE)) {
		avio_closep(&fc->pb);
	}

	// Freeing all the allocated memory:
	sws_freeContext(swsCtx);
	av_frame_free(&rgbpic);
	av_frame_free(&yuvpic);
	avcodec_free_context(&ctx);
	avformat_free_context(fc);

	delete pkt;
}

#endif // GAME_PLATFORM_WIN
