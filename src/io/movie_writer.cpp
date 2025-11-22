#include "movie_writer.h"

#include "core/log.h"

#ifdef GAME_PLATFORM_WIN

#include <vpx/vpx_codec.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

MovieWriter::MovieWriter(const std::string& filename_, const unsigned int width_, const unsigned int height_, const int frameRate_) :
	width(width_), height(height_), iframe(0), frameRate(frameRate_), filename(filename_), initialized(false)
{
	// Allocate YUV buffer (YUV420: Y plane + U/V planes)
	yuv_buffer.resize(width * height * 3 / 2); // Y: width*height, U: width*height/4, V: width*height/4
	
	// Change extension to .webm if needed
	std::string output_filename = filename;
	if (output_filename.size() < 5 || output_filename.substr(output_filename.size() - 5) != ".webm") {
		output_filename = filename + ".webm";
	}
	
	// Open output file
	output_file.open(output_filename, std::ios::binary);
	if (!output_file.is_open()) {
		logs::info("MovieWriter: Failed to open output file: %s\n", output_filename.c_str());
		return;
	}
	filename = output_filename;
	
	// Initialize VP9 encoder
	codec = new vpx_codec_ctx_t;
	vpx_codec_enc_cfg_t cfg;
	vpx_codec_err_t res;
	
	// Get default VP9 encoder configuration
	res = vpx_codec_enc_config_default(vpx_codec_vp9_cx(), &cfg, 0);
	if (res != VPX_CODEC_OK) {
		logs::info("MovieWriter: Failed to get default VP9 config\n");
		delete codec;
		codec = nullptr;
		return;
	}
	
	// Configure encoder
	cfg.g_w = width;
	cfg.g_h = height;
	cfg.g_timebase.num = 1;
	cfg.g_timebase.den = frameRate;
	cfg.rc_target_bitrate = width * height * frameRate / 1000; // Simple bitrate calculation
	cfg.g_lag_in_frames = 0; // No lookahead for real-time encoding
	cfg.g_error_resilient = 1;
	
	// Set encoder options in config before initialization
	cfg.g_usage = 0; // Real-time encoding
	cfg.rc_end_usage = VPX_CBR; // Constant bitrate
	
	// Initialize encoder
	res = vpx_codec_enc_init_ver(codec, vpx_codec_vp9_cx(), &cfg, 0, VPX_ENCODER_ABI_VERSION);
	if (res != VPX_CODEC_OK) {
		logs::info("MovieWriter: Failed to initialize VP9 encoder: %s\n", vpx_codec_error_detail(codec));
		delete codec;
		codec = nullptr;
		return;
	}
	
	// Set encoder options after initialization using vpx_codec_control
	// Note: vpx_codec_ctl is a macro, use vpx_codec_control directly
	if (vpx_codec_control(codec, VP8E_SET_CPUUSED, 4) != VPX_CODEC_OK) {
		logs::info("MovieWriter: Warning - failed to set CPUUSED\n");
	}
	if (vpx_codec_control(codec, VP9E_SET_LOSSLESS, 0) != VPX_CODEC_OK) {
		logs::info("MovieWriter: Warning - failed to set LOSSLESS\n");
	}
	
	// Allocate YUV image
	yuv_image = vpx_img_alloc(nullptr, VPX_IMG_FMT_I420, width, height, 1);
	if (!yuv_image) {
		logs::info("MovieWriter: Failed to allocate YUV image\n");
		vpx_codec_destroy(codec);
		delete codec;
		codec = nullptr;
		return;
	}
	
	// Note: For now, we write raw VP9 frames
	// A proper WebM muxer would wrap these in EBML/Matroska container
	// The output file will be raw VP9 stream - can be converted to WebM with:
	// ffmpeg -i input.raw -c:v copy output.webm
	// Or we can add libwebm for proper WebM muxing later
	
	initialized = true;
	logs::info("MovieWriter: Initialized VP9 encoder for %dx%d @ %d fps\n", width, height, frameRate);
}

void MovieWriter::convertRGBtoYUV420(const uint8_t* rgb, uint8_t* yuv) {
	// Convert ARGB8888 to YUV420
	// Input: RGB in ARGB format (4 bytes per pixel: A, R, G, B)
	// Output: YUV420 (Y plane, then U plane, then V plane)
	
	uint8_t* y_plane = yuv;
	uint8_t* u_plane = yuv + width * height;
	uint8_t* v_plane = yuv + width * height * 5 / 4;
	
	// Convert each pixel
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			// Get RGB values (skip alpha channel)
			int r = rgb[(y * width + x) * 4 + 2];
			int g = rgb[(y * width + x) * 4 + 1];
			int b = rgb[(y * width + x) * 4 + 0];
			
			// Convert to YUV (ITU-R BT.601)
			int y_val = (int)(0.299 * r + 0.587 * g + 0.114 * b);
			int u_val = (int)(-0.169 * r - 0.331 * g + 0.5 * b + 128);
			int v_val = (int)(0.5 * r - 0.419 * g - 0.081 * b + 128);
			
			// Clamp values
			y_plane[y * width + x] = (uint8_t)(y_val < 0 ? 0 : (y_val > 255 ? 255 : y_val));
			
			// For U and V, we need to downsample (420 format)
			if (x % 2 == 0 && y % 2 == 0) {
				u_plane[(y / 2) * (width / 2) + (x / 2)] = (uint8_t)(u_val < 0 ? 0 : (u_val > 255 ? 255 : u_val));
				v_plane[(y / 2) * (width / 2) + (x / 2)] = (uint8_t)(v_val < 0 ? 0 : (v_val > 255 ? 255 : v_val));
			}
		}
	}
}

void MovieWriter::addFrame(const uint8_t* pixels) {
	if (!initialized || !codec || !output_file.is_open()) {
		return;
	}
	
	// Convert RGB to YUV420
	convertRGBtoYUV420(pixels, yuv_buffer.data());
	
	// Copy to vpx_image structure
	// Y plane
	for (unsigned int y = 0; y < height; y++) {
		memcpy(yuv_image->planes[VPX_PLANE_Y] + y * yuv_image->stride[VPX_PLANE_Y],
		       yuv_buffer.data() + y * width,
		       width);
	}
	// U plane
	for (unsigned int y = 0; y < height / 2; y++) {
		memcpy(yuv_image->planes[VPX_PLANE_U] + y * yuv_image->stride[VPX_PLANE_U],
		       yuv_buffer.data() + width * height + y * (width / 2),
		       width / 2);
	}
	// V plane
	for (unsigned int y = 0; y < height / 2; y++) {
		memcpy(yuv_image->planes[VPX_PLANE_V] + y * yuv_image->stride[VPX_PLANE_V],
		       yuv_buffer.data() + width * height * 5 / 4 + y * (width / 2),
		       width / 2);
	}
	
	// Encode frame
	vpx_codec_iter_t iter = nullptr;
	const vpx_codec_cx_pkt_t* pkt;
	
	vpx_codec_err_t res = vpx_codec_encode(codec, yuv_image, iframe, 1, 0, VPX_DL_GOOD_QUALITY);
	if (res != VPX_CODEC_OK) {
		logs::info("MovieWriter: Encoding error: %s\n", vpx_codec_error_detail(codec));
		return;
	}
	
	// Get encoded packets
	while ((pkt = vpx_codec_get_cx_data(codec, &iter)) != nullptr) {
		if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
			// Write frame data (for now, just write raw VP9 data)
			// In a full implementation, we'd mux this into WebM format
			output_file.write((const char*)pkt->data.frame.buf, pkt->data.frame.sz);
			encoded_frames.push_back(iframe);
			
			logs::info("MovieWriter: Encoded frame %d (size = %zu)\n", iframe, pkt->data.frame.sz);
		}
	}
	
	iframe++;
}

MovieWriter::~MovieWriter() {
	if (!initialized) {
		return;
	}
	
	// Flush encoder
	if (codec) {
		vpx_codec_iter_t iter = nullptr;
		const vpx_codec_cx_pkt_t* pkt;
		
		// Encode NULL frame to flush
		vpx_codec_err_t res = vpx_codec_encode(codec, nullptr, iframe, 1, 0, VPX_DL_GOOD_QUALITY);
		if (res == VPX_CODEC_OK) {
			while ((pkt = vpx_codec_get_cx_data(codec, &iter)) != nullptr) {
				if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
					output_file.write((const char*)pkt->data.frame.buf, pkt->data.frame.sz);
					logs::info("MovieWriter: Flushed frame (size = %zu)\n", pkt->data.frame.sz);
				}
			}
		}
		
		vpx_codec_destroy(codec);
		delete codec;
	}
	
	// Cleanup
	if (yuv_image) {
		vpx_img_free(yuv_image);
	}
	
	if (output_file.is_open()) {
		output_file.close();
	}
	
	logs::info("MovieWriter: Finished writing %d frames to %s\n", iframe, filename.c_str());
}

#endif // GAME_PLATFORM_WIN
