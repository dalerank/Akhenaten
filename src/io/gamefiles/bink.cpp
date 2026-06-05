#include "bink.h"

#include "core/log.h"
#include "content/vfs.h"

#include <SDL.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <deque>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

constexpr uint32_t kBikTagMask = 0x00FFFFFFu;
constexpr uint32_t kBikTag = 0x004B4942u;
constexpr char kSupportedRevision = 'f';
constexpr uint16_t kAudioFlagStereo = 0x2000;
constexpr uint16_t kAudioFlagUseDct = 0x1000;
constexpr double kPi = 3.14159265358979323846;

constexpr int kParamBlockTypes = 0;
constexpr int kParamSubBlockTypes = 1;
constexpr int kParamColors = 2;
constexpr int kParamPattern = 3;
constexpr int kParamXOff = 4;
constexpr int kParamYOff = 5;
constexpr int kParamIntraDc = 6;
constexpr int kParamInterDc = 7;
constexpr int kParamRun = 8;
constexpr int kParamCount = 9;

constexpr int kSkipBlock = 0;
constexpr int kScaledBlock = 1;
constexpr int kMotionBlock = 2;
constexpr int kRunBlock = 3;
constexpr int kResidueBlock = 4;
constexpr int kIntraBlock = 5;
constexpr int kFillBlock = 6;
constexpr int kInterBlock = 7;
constexpr int kPatternBlock = 8;
constexpr int kRawBlock = 9;

constexpr int kHuffmanTreeCount = 16;
constexpr int kHuffmanSymbolCount = 16;
constexpr int kHuffmanMaxCodeLength = 7;

constexpr std::array<int, 4> kBlockTypeRleLengths = {4, 8, 12, 32};
constexpr std::array<int, 25> kCriticalFrequencies = {
    100, 200, 300, 400, 510, 630, 770, 920,
    1080, 1270, 1480, 1720, 2000, 2320, 2700, 3150,
    3700, 4400, 5300, 6400, 7700, 9500, 12000, 15500, 24500
};
constexpr std::array<int, 16> kRleLengthTable = {
    2, 3, 4, 5, 6, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 32, 64
};

constexpr uint8_t kHuffmanCodeBits[kHuffmanTreeCount][kHuffmanSymbolCount] = {
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F },
    { 0x00, 0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F },
    { 0x00, 0x02, 0x01, 0x09, 0x05, 0x15, 0x0D, 0x1D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x17, 0x0F, 0x1F },
    { 0x00, 0x02, 0x06, 0x01, 0x09, 0x05, 0x0D, 0x1D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x17, 0x0F, 0x1F },
    { 0x00, 0x04, 0x02, 0x06, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x17, 0x0F, 0x1F },
    { 0x00, 0x04, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x07, 0x17, 0x0F, 0x1F },
    { 0x00, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x1B, 0x07, 0x17, 0x0F, 0x1F },
    { 0x00, 0x01, 0x05, 0x03, 0x13, 0x0B, 0x1B, 0x3B, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x01, 0x03, 0x13, 0x0B, 0x2B, 0x1B, 0x3B, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x01, 0x05, 0x0D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x02, 0x01, 0x05, 0x0D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x13, 0x0B, 0x1B, 0x07, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x02, 0x01, 0x03, 0x13, 0x0B, 0x1B, 0x3B, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x2F, 0x1F, 0x3F },
    { 0x00, 0x01, 0x05, 0x03, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x4F, 0x2F, 0x6F, 0x1F, 0x5F, 0x3F, 0x7F },
    { 0x00, 0x01, 0x05, 0x03, 0x07, 0x17, 0x37, 0x77, 0x0F, 0x4F, 0x2F, 0x6F, 0x1F, 0x5F, 0x3F, 0x7F },
    { 0x00, 0x02, 0x01, 0x05, 0x03, 0x07, 0x27, 0x17, 0x37, 0x0F, 0x2F, 0x6F, 0x1F, 0x5F, 0x3F, 0x7F }
};

constexpr uint8_t kHuffmanCodeLengths[kHuffmanTreeCount][kHuffmanSymbolCount] = {
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
    { 1, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 2, 2, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5 },
    { 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5 },
    { 1, 3, 3, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 1, 2, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 1, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 2, 2, 3, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6 },
    { 1, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6 },
    { 2, 2, 2, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 1, 3, 3, 3, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7 },
    { 1, 3, 3, 3, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
    { 2, 2, 3, 3, 3, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7 }
};

struct audio_track_info {
    uint16_t sample_rate = 0;
    uint32_t max_decoded_size = 0;
    bool is_stereo = false;
};

struct frame_index_entry {
    uint32_t offset = 0;
    uint32_t size = 0;
    bool is_keyframe = false;
};

struct audio_packet {
    std::vector<uint8_t> payload;
};

struct frame_packet {
    std::vector<audio_packet> audio_packets;
    std::vector<uint8_t> video_payload;
};

static bool read_u32_le(FILE* fp, uint32_t& out) {
    uint8_t bytes[4];
    if (std::fread(bytes, 1, 4, fp) != 4) {
        logs::error("BIK: Unexpected end of file.");
        return false;
    }
    out = (uint32_t)bytes[0]
        | ((uint32_t)bytes[1] << 8)
        | ((uint32_t)bytes[2] << 16)
        | ((uint32_t)bytes[3] << 24);
    return true;
}

static bool read_u16_le(FILE* fp, uint16_t& out) {
    uint8_t bytes[2];
    if (std::fread(bytes, 1, 2, fp) != 2) {
        logs::error("BIK: Unexpected end of file.");
        return false;
    }
    out = (uint16_t)(bytes[0] | (bytes[1] << 8));
    return true;
}

static int clamp_int(int value, int min_value, int max_value) {
    return value < min_value ? min_value : (value > max_value ? max_value : value);
}

static int int_log2(int value) {
    int result = 0;
    while ((1 << (result + 1)) <= value) {
        ++result;
    }
    return result;
}

static int align8(int value) {
    return (value + 7) & ~7;
}

class bit_reader_le {
public:
    explicit bit_reader_le(const std::vector<uint8_t>& data) : data_(data) {}

    bool ok() const { return ok_; }
    int bits_remaining() const { return (int)data_.size() * 8 - bit_position_; }

    bool read_bit() { return read_bits(1) != 0; }

    uint32_t read_bits(int count) {
        if (!ok_) {
            return 0;
        }
        if (count < 0 || count > 32 || bits_remaining() < count) {
            logs::error("BIK: Invalid bit read.");
            ok_ = false;
            return 0;
        }
        uint32_t value = 0;
        for (int i = 0; i < count; ++i) {
            int absolute_bit = bit_position_ + i;
            int byte_index = absolute_bit >> 3;
            int bit_index = absolute_bit & 7;
            uint32_t bit = (data_[byte_index] >> bit_index) & 1u;
            value |= bit << i;
        }
        bit_position_ += count;
        return value;
    }

    void skip_bits(int count) {
        if (!ok_) {
            return;
        }
        if (count < 0 || bits_remaining() < count) {
            logs::error("BIK: Invalid bit skip.");
            ok_ = false;
            return;
        }
        bit_position_ += count;
    }

    void align32() {
        int padding = (-bit_position_) & 31;
        if (padding) {
            skip_bits(padding);
        }
    }

private:
    const std::vector<uint8_t>& data_;
    int bit_position_ = 0;
    bool ok_ = true;
};

class bink_file {
public:
    static bink_file load(const std::string& path) {
        bink_file result;
        FILE* fp = std::fopen(path.c_str(), "rb");
        if (!fp) {
            logs::error("BIK: Unable to open BIK file.");
            return result;
        }

        uint32_t codec_tag = 0;
        if (!read_u32_le(fp, codec_tag)) {
            std::fclose(fp);
            return result;
        }
        if ((codec_tag & kBikTagMask) != kBikTag) {
            logs::error("BIK: Unsupported BIK signature.");
            std::fclose(fp);
            return result;
        }

        char revision = (char)((codec_tag >> 24) & 0xff);
        if (revision != kSupportedRevision) {
            logs::error("BIK: Only BIKf video is supported.");
            std::fclose(fp);
            return result;
        }

        uint32_t declared_file_size = 0;
        uint32_t frame_count = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t fps_numerator = 0;
        uint32_t fps_denominator = 0;
        uint32_t video_flags_raw = 0;
        uint32_t audio_track_count = 0;
        uint32_t max_decoded_size = 0;
        uint16_t sample_rate = 0;
        uint16_t flags = 0;
        uint32_t ignored_u32 = 0;

        if (!read_u32_le(fp, declared_file_size)
            || !read_u32_le(fp, frame_count)
            || !read_u32_le(fp, ignored_u32)
            || !read_u32_le(fp, ignored_u32)
            || !read_u32_le(fp, width)
            || !read_u32_le(fp, height)
            || !read_u32_le(fp, fps_numerator)
            || !read_u32_le(fp, fps_denominator)
            || !read_u32_le(fp, video_flags_raw)
            || !read_u32_le(fp, audio_track_count)) {
            std::fclose(fp);
            return result;
        }
        declared_file_size += 8u;

        if (video_flags_raw != 0) {
            logs::error("BIK: Only plain YUV BIKf videos are supported.");
            std::fclose(fp);
            return result;
        }
        if (audio_track_count != 1) {
            logs::error("BIK: Only single-track BIKf files are supported.");
            std::fclose(fp);
            return result;
        }

        if (!read_u32_le(fp, max_decoded_size)
            || !read_u16_le(fp, sample_rate)
            || !read_u16_le(fp, flags)) {
            std::fclose(fp);
            return result;
        }
        if ((flags & kAudioFlagUseDct) != 0) {
            logs::error("BIK: Only RDFT Bink audio is supported.");
            std::fclose(fp);
            return result;
        }

        audio_track_info audio_track;
        audio_track.sample_rate = sample_rate;
        audio_track.max_decoded_size = max_decoded_size;
        audio_track.is_stereo = (flags & kAudioFlagStereo) != 0;

        uint32_t next_pos = 0;
        if (!read_u32_le(fp, ignored_u32) || !read_u32_le(fp, next_pos)) {
            std::fclose(fp);
            return result;
        }

        bool next_keyframe = true;
        std::vector<frame_index_entry> index;
        index.reserve(frame_count);

        for (uint32_t i = 0; i < frame_count; ++i) {
            bool is_keyframe = next_keyframe;
            uint32_t pos = next_pos & ~1u;
            if (i == frame_count - 1) {
                next_pos = declared_file_size;
                next_keyframe = false;
            } else {
                uint32_t raw_next_pos = 0;
                if (!read_u32_le(fp, raw_next_pos)) {
                    std::fclose(fp);
                    return result;
                }
                next_keyframe = (raw_next_pos & 1u) != 0;
                next_pos = raw_next_pos & ~1u;
            }

            if (next_pos <= pos) {
                logs::error("BIK: Invalid BIK frame index.");
                std::fclose(fp);
                return result;
            }

            index.push_back({pos, next_pos - pos, is_keyframe});
        }

        std::fclose(fp);
        result = bink_file(path, width, height, fps_numerator, fps_denominator, audio_track, std::move(index));
        result.valid_ = true;
        return result;
    }

    bink_file() = default;

    bool valid() const { return valid_; }
    const std::string& path() const { return file_path_; }
    int width() const { return (int)width_; }
    int height() const { return (int)height_; }
    int micros_per_frame() const {
        if (fps_numerator_ == 0) {
            return 0;
        }
        double fps = (double)fps_numerator_ / std::max<uint32_t>(fps_denominator_, 1u);
        return (int)std::llround(1000000.0 / std::max(fps, 1.0));
    }
    const audio_track_info& audio_track() const { return audio_track_; }
    const std::vector<frame_index_entry>& frame_index() const { return frame_index_; }

private:
    bink_file(
        std::string file_path,
        uint32_t width,
        uint32_t height,
        uint32_t fps_numerator,
        uint32_t fps_denominator,
        audio_track_info audio_track,
        std::vector<frame_index_entry> frame_index)
        : file_path_(std::move(file_path))
        , width_(width)
        , height_(height)
        , fps_numerator_(fps_numerator)
        , fps_denominator_(fps_denominator)
        , audio_track_(audio_track)
        , frame_index_(std::move(frame_index)) {}

    std::string file_path_;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    uint32_t fps_numerator_ = 0;
    uint32_t fps_denominator_ = 0;
    audio_track_info audio_track_;
    std::vector<frame_index_entry> frame_index_;
    bool valid_ = false;
};

class bink_sequential_packet_reader {
public:
    explicit bink_sequential_packet_reader(const bink_file& file) : file_(file) {
        if (!file.valid()) {
            return;
        }
        fp_ = std::fopen(file.path().c_str(), "rb");
        if (!fp_) {
            logs::error("BIK: Unable to open BIK stream.");
            return;
        }
        valid_ = true;
    }

    bool valid() const { return valid_; }

    ~bink_sequential_packet_reader() {
        if (fp_) {
            std::fclose(fp_);
        }
    }

    bool read_frame_packet(int frame_number, frame_packet& packet) {
        packet = {};
        if (!valid_) {
            return false;
        }

        const auto& index = file_.frame_index();
        if (frame_number < 0 || frame_number >= (int)index.size()) {
            logs::error("BIK: Frame index out of range.");
            valid_ = false;
            return false;
        }

        const frame_index_entry& entry = index[frame_number];
        std::fseek(fp_, (long)entry.offset, SEEK_SET);

        uint32_t audio_size = 0;
        if (!read_u32_le(fp_, audio_size)) {
            valid_ = false;
            return false;
        }
        int bytes_consumed = 4;
        if (audio_size > entry.size - (uint32_t)bytes_consumed) {
            logs::error("BIK: Invalid BIK audio packet boundary.");
            valid_ = false;
            return false;
        }

        int encoded_size = 0;
        if (audio_size > 3) {
            uint32_t ignored = 0;
            if (!read_u32_le(fp_, ignored)) {
                valid_ = false;
                return false;
            }
            bytes_consumed += 4;
            encoded_size = (int)audio_size - 4;
        }

        std::vector<uint8_t> audio_payload;
        if (!read_exact(encoded_size, audio_payload)) {
            valid_ = false;
            return false;
        }
        bytes_consumed += (int)audio_payload.size();

        int video_size = (int)entry.size - bytes_consumed;
        std::vector<uint8_t> video_payload;
        if (!read_exact(video_size, video_payload)) {
            valid_ = false;
            return false;
        }

        packet.audio_packets.push_back({std::move(audio_payload)});
        packet.video_payload = std::move(video_payload);
        return true;
    }

private:
    bool read_exact(int count, std::vector<uint8_t>& result) {
        if (count < 0) {
            logs::error("BIK: Negative packet size.");
            return false;
        }
        result.assign((size_t)count, 0);
        if (count > 0 && std::fread(result.data(), 1, (size_t)count, fp_) != (size_t)count) {
            logs::error("BIK: Unexpected end of BIK file.");
            return false;
        }
        return true;
    }

    const bink_file& file_;
    FILE* fp_ = nullptr;
    bool valid_ = false;
};

struct bink_reference_data {
    static bink_reference_data& instance() {
        static bink_reference_data data = create();
        return data;
    }

    std::array<int, 64> scan{};
    std::array<std::array<int, 64>, 17> patterns{};
    std::array<std::array<int, 64>, 16> intra_quant{};
    std::array<std::array<int, 64>, 16> inter_quant{};

private:
    static bink_reference_data create() {
        static constexpr const char* packed_base_quant =
            "11231143113210102232101034232322322312112211333332211010111110001223113211210010212110102323221222221100110032222111100011000000eyopuy4feb531jgwzmirsxwt3asvjj7r3sm2nm4jh8ulwin58cjwmrbnsfcb8mwje2b7yu6vk8fwwgbpezdvdpanec950snamd506soxoiyu5tyo3nse5lyha0qlpde7k5fr2lxpk6zrm67nd3c9t1dqhnc6n4gvhc3yvw4meg2fa83mxfva5w1az2t9fnkykiaj7wj3wpovhkgepdh5529kpareotlnzhvzr2evca6rayt5ulkq1sxt6a58x7mxg1xpjz2ogi6vom0m47tz5ftgr9aekmnura7g6c0w48u30wpasfmbljblwgxtlh8vguh077we04awyg6dtl5pzcczt3djwqhv557xe1y58ygdvvo0oh96usw9k9rl3pot";
        static constexpr int embedded_scan[64] = {
            0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15,
            20, 21, 28, 29, 22, 23, 30, 31, 16, 17, 24, 25, 32, 33, 40, 41,
            34, 35, 42, 43, 48, 49, 56, 57, 50, 51, 58, 59, 18, 19, 26, 27,
            36, 37, 44, 45, 38, 39, 46, 47, 52, 53, 60, 61, 54, 55, 62, 63
        };
        static constexpr int embedded_patterns[17][64] = {
            {0, 8, 16, 24, 32, 40, 48, 56, 57, 49, 41, 33, 25, 17, 9, 1, 2, 10, 18, 26, 34, 42, 50, 58, 59, 51, 43, 35, 27, 19, 11, 3, 4, 12, 20, 28, 36, 44, 52, 60, 61, 53, 45, 37, 29, 21, 13, 5, 6, 14, 22, 30, 38, 46, 54, 62, 63, 55, 47, 39, 31, 23, 15, 7},
            {59, 58, 57, 56, 48, 49, 50, 51, 43, 42, 41, 40, 32, 33, 34, 35, 27, 26, 25, 24, 16, 17, 18, 19, 11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 20, 21, 22, 23, 31, 30, 29, 28, 36, 37, 38, 39, 47, 46, 45, 44, 52, 53, 54, 55, 63, 62, 61, 60},
            {25, 17, 18, 26, 27, 19, 11, 3, 2, 10, 9, 1, 0, 8, 16, 24, 32, 40, 48, 56, 57, 49, 41, 42, 50, 58, 59, 51, 43, 35, 34, 33, 29, 21, 22, 30, 31, 23, 15, 7, 6, 14, 13, 5, 4, 12, 20, 28, 36, 44, 52, 60, 61, 53, 45, 46, 54, 62, 63, 55, 47, 39, 38, 37},
            {3, 11, 2, 10, 1, 9, 0, 8, 16, 24, 17, 25, 18, 26, 19, 27, 35, 43, 34, 42, 33, 41, 32, 40, 48, 56, 49, 57, 50, 58, 51, 59, 60, 52, 61, 53, 62, 54, 63, 55, 47, 39, 46, 38, 45, 37, 44, 36, 28, 20, 29, 21, 30, 22, 31, 23, 15, 7, 14, 6, 13, 5, 12, 4},
            {24, 25, 16, 17, 8, 9, 0, 1, 2, 3, 10, 11, 18, 19, 26, 27, 28, 29, 20, 21, 12, 13, 4, 5, 6, 7, 14, 15, 22, 23, 30, 31, 39, 38, 47, 46, 55, 54, 63, 62, 61, 60, 53, 52, 45, 44, 37, 36, 35, 34, 43, 42, 51, 50, 59, 58, 57, 56, 49, 48, 41, 40, 33, 32},
            {0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27, 32, 33, 34, 35, 40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59, 4, 5, 6, 7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31, 36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 60, 61, 62, 63},
            {6, 7, 15, 14, 13, 5, 12, 4, 3, 11, 2, 10, 9, 1, 0, 8, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31, 39, 47, 38, 46, 37, 45, 36, 44, 35, 43, 34, 42, 33, 41, 32, 40, 49, 48, 56, 57, 58, 50, 59, 51, 60, 52, 61, 53, 54, 55, 63, 62},
            {0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8, 16, 17, 18, 19, 20, 21, 22, 23, 31, 30, 29, 28, 27, 26, 25, 24, 32, 33, 34, 35, 36, 37, 38, 39, 47, 46, 45, 44, 43, 42, 41, 40, 48, 49, 50, 51, 52, 53, 54, 55, 63, 62, 61, 60, 59, 58, 57, 56},
            {0, 8, 9, 1, 2, 3, 11, 10, 18, 19, 27, 26, 25, 17, 16, 24, 32, 40, 41, 33, 34, 35, 43, 42, 50, 49, 48, 56, 57, 58, 59, 51, 52, 60, 61, 62, 63, 55, 54, 53, 45, 44, 36, 37, 38, 46, 47, 39, 31, 23, 22, 30, 29, 28, 20, 21, 13, 12, 4, 5, 6, 14, 15, 7},
            {24, 25, 16, 17, 8, 9, 0, 1, 2, 3, 10, 11, 18, 19, 26, 27, 28, 29, 20, 21, 12, 13, 4, 5, 6, 7, 14, 15, 22, 23, 30, 31, 38, 39, 46, 47, 54, 55, 62, 63, 60, 61, 52, 53, 44, 45, 36, 37, 34, 35, 42, 43, 50, 51, 58, 59, 56, 57, 48, 49, 40, 41, 32, 33},
            {0, 8, 1, 9, 2, 10, 3, 11, 19, 27, 18, 26, 17, 25, 16, 24, 32, 40, 33, 41, 34, 42, 35, 43, 51, 59, 50, 58, 49, 57, 48, 56, 60, 52, 61, 53, 62, 54, 63, 55, 47, 39, 46, 38, 45, 37, 44, 36, 31, 23, 30, 22, 29, 21, 28, 20, 12, 4, 13, 5, 14, 6, 15, 7},
            {0, 8, 16, 24, 25, 26, 27, 19, 11, 3, 2, 1, 9, 17, 18, 10, 4, 12, 20, 28, 29, 30, 31, 23, 15, 7, 6, 5, 13, 21, 22, 14, 36, 44, 52, 60, 61, 62, 63, 55, 47, 39, 38, 37, 45, 53, 54, 46, 32, 40, 48, 56, 57, 58, 59, 51, 43, 35, 34, 33, 41, 49, 50, 42},
            {0, 8, 9, 1, 2, 3, 11, 10, 19, 27, 26, 18, 17, 16, 24, 25, 33, 32, 40, 41, 42, 34, 35, 43, 51, 59, 58, 50, 49, 57, 56, 48, 52, 60, 61, 53, 54, 62, 63, 55, 47, 39, 38, 46, 45, 44, 36, 37, 29, 28, 20, 21, 22, 30, 31, 23, 14, 15, 7, 6, 5, 13, 12, 4},
            {24, 16, 8, 0, 1, 2, 3, 11, 19, 27, 26, 25, 17, 10, 9, 18, 28, 20, 12, 4, 5, 6, 7, 15, 23, 31, 30, 29, 21, 14, 13, 22, 60, 52, 44, 36, 37, 38, 39, 47, 55, 63, 62, 61, 53, 46, 45, 54, 56, 48, 40, 32, 33, 34, 35, 43, 51, 59, 58, 57, 49, 42, 41, 50},
            {0, 8, 9, 1, 2, 10, 18, 17, 16, 24, 25, 26, 27, 19, 11, 3, 7, 6, 14, 15, 23, 22, 21, 13, 5, 4, 12, 20, 28, 29, 30, 31, 63, 62, 54, 55, 47, 46, 45, 53, 61, 60, 52, 44, 36, 37, 38, 39, 56, 48, 49, 57, 58, 50, 42, 41, 40, 32, 33, 34, 35, 43, 51, 59},
            {0, 1, 8, 9, 16, 17, 24, 25, 32, 33, 40, 41, 48, 49, 56, 57, 58, 59, 50, 51, 42, 43, 34, 35, 26, 27, 18, 19, 10, 11, 2, 3, 4, 5, 12, 13, 20, 21, 28, 29, 36, 37, 44, 45, 52, 53, 60, 61, 62, 63, 54, 55, 46, 47, 38, 39, 30, 31, 22, 23, 14, 15, 6, 7}
        };

        bink_reference_data data;
        for (int i = 0; i < 64; ++i) {
            data.scan[i] = embedded_scan[i];
        }
        for (int p = 0; p < 17; ++p) {
            for (int i = 0; i < 64; ++i) {
                data.patterns[p][i] = embedded_patterns[p][i];
            }
        }

        std::vector<int> base_quant = unpack_values(4, packed_base_quant);
        constexpr double factors[16] = {
            1.0, 4.0 / 3.0, 5.0 / 3.0, 2.0,
            8.0 / 3.0, 7.0 / 2.0, 4.0, 5.0,
            6.0, 8.0, 12.0, 17.0,
            22.0, 28.0, 34.0, 44.0
        };

        for (int level = 0; level < 32; ++level) {
            auto& target = level < 16 ? data.intra_quant[level & 15] : data.inter_quant[level & 15];
            int source_offset = level < 16 ? 0 : 64;
            double factor = factors[level & 15];
            for (int i = 0; i < 64; ++i) {
                target[i] = (int)std::llround(base_quant[source_offset + i] * factor);
            }
        }
        return data;
    }

    static std::vector<int> unpack_values(int width, const char* packed) {
        int packed_len = (int)std::strlen(packed);
        int len = packed_len / width;
        std::vector<int> values((size_t)len);
        std::vector<char> token((size_t)width);
        for (int index = 0; index < len; ++index) {
            for (int i = 0; i < width; ++i) {
                token[(size_t)i] = packed[(i * len) + index];
            }
            values[(size_t)index] = parse_base36(token);
        }
        return values;
    }

    static int parse_base36(const std::vector<char>& token) {
        int value = 0;
        for (char c0 : token) {
            char c = (char)std::tolower((unsigned char)c0);
            int digit = 0;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'a' && c <= 'z') {
                digit = 10 + (c - 'a');
            } else {
                logs::error("BIK: Invalid base36 character.");
                return 0;
            }
            value = value * 36 + digit;
        }
        return value;
    }
};

struct tree_t {
    int tree_index = 0;
    std::array<uint8_t, 16> symbols{};
};

struct bundle_t {
    int length_bits = 0;
    tree_t tree;
    std::vector<int> data;
    int read_index = 0;
    bool active = false;

    void reset() {
        data.clear();
        read_index = 0;
        active = true;
    }
};

struct bink_video_transforms {
    static constexpr int kDctC0 = 2896;
    static constexpr int kDctC1 = 2217;
    static constexpr int kDctC2 = 3784;
    static constexpr int kDctC3 = -5352;

    static void idct_put(int* block, uint8_t* destination, size_t destination_len, int destination_offset, int stride) {
        for (int i = 0; i < 8; ++i) {
            idct(block, i, nullptr, 0, i, true);
        }
        for (int i = 0; i < 64; i += 8) {
            if (destination_offset >= (int)destination_len) {
                break;
            }
            idct(block, i, destination, destination_len, destination_offset, false);
            destination_offset += stride;
        }
    }

    static void idct_add(int* block, uint8_t* destination, size_t destination_len, int destination_offset, int stride) {
        for (int i = 0; i < 8; ++i) {
            idct(block, i, nullptr, 0, i, true);
        }
        for (int i = 0; i < 64; i += 8) {
            idct(block, i, nullptr, 0, i, false);
        }
        add_block_8x8(block, destination, destination_len, destination_offset, stride);
    }

    static void add_block_8x8(int* block, uint8_t* destination, size_t destination_len, int destination_offset, int stride) {
        for (int y = 0; y < 8; ++y) {
            int row_offset = destination_offset + y * stride;
            for (int x = 0; x < 8; ++x) {
                int destination_index = row_offset + x;
                if (destination_index < 0 || destination_index >= (int)destination_len) {
                    continue;
                }
                destination[(size_t)destination_index] = (uint8_t)(destination[(size_t)destination_index] + block[y * 8 + x]);
            }
        }
    }

private:
    static void idct(int* source, int source_offset, uint8_t* destination, size_t destination_len, int destination_offset, bool column) {
        int index_shift = column ? 3 : 0;
        int constant_to_add = column ? 0 : 0x7f;
        int destination_shift = column ? 0 : 8;

        int a0 = source[source_offset] + constant_to_add;
        int b0 = source[source_offset + (1 << index_shift)];
        int a2 = source[source_offset + (2 << index_shift)];
        int x3 = source[source_offset + (3 << index_shift)];
        int x4 = source[source_offset + (4 << index_shift)];
        int a4 = source[source_offset + (5 << index_shift)];
        int x6 = source[source_offset + (6 << index_shift)];
        int x7 = source[source_offset + (7 << index_shift)];

        int a1 = a0 - x4;
        int a3 = (kDctC0 * (a2 - x6)) >> 11;
        int a5 = a4 - x3;
        int a7 = b0 - x7;
        a0 += x4;
        a2 += x6;
        a4 += x3;
        b0 += x7;

        int a0_plus_a2 = a0 + a2;
        int a0_minus_a2 = a0 - a2;
        int a1_plus_a3_minus_a2 = a1 + a3 - a2;
        int a1_minus_a3_plus_a2 = a1 - a3 + a2;

        int b1 = (kDctC2 * (a5 + a7)) >> 11;
        int b3 = (kDctC0 * (b0 - a4)) >> 11;
        b0 += a4;
        int b2 = ((kDctC3 * a5) >> 11) - b0 + b1;
        b3 -= b2;
        int b4 = ((kDctC1 * a7) >> 11) + b3 - b1;

        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 0, a0_plus_a2 + b0);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 1, a1_plus_a3_minus_a2 + b2);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 2, a1_minus_a3_plus_a2 + b3);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 3, a0_minus_a2 - b4);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 4, a0_minus_a2 + b4);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 5, a1_minus_a3_plus_a2 - b3);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 6, a1_plus_a3_minus_a2 - b2);
        write(destination, destination_len, source, destination_offset, source_offset, index_shift, destination_shift, 7, a0_plus_a2 - b0);
    }

    static void write(uint8_t* destination, size_t destination_len, int* source, int destination_offset, int source_offset, int index_shift, int destination_shift, int element, int value) {
        int shifted = value >> destination_shift;
        int index = destination_offset + (element << index_shift);
        if (!destination) {
            source[index] = shifted;
            return;
        }
        if (index < 0 || index >= (int)destination_len) {
            return;
        }
        destination[(size_t)index] = (uint8_t)shifted;
    }
};

class bink_rdft_audio_decoder {
public:
    explicit bink_rdft_audio_decoder(const audio_track_info& track) {
        original_channels_ = track.is_stereo ? 2 : 1;

        int frame_length_bits = 0;
        if (track.sample_rate < 22050) {
            frame_length_bits = 9;
        } else if (track.sample_rate < 44100) {
            frame_length_bits = 10;
        } else {
            frame_length_bits = 11;
        }
        frame_length_bits += int_log2(original_channels_);

        frame_length_ = 1 << frame_length_bits;
        overlap_length_ = frame_length_ / 16;
        root_ = (float)(2.0 / (std::sqrt((double)frame_length_) * 32768.0));

        quant_table_.resize(96);
        for (int i = 0; i < 96; ++i) {
            quant_table_[(size_t)i] = (float)(std::exp(i * 0.15289164787221954) * root_);
        }

        int sample_rate_for_bands = track.sample_rate * original_channels_;
        int sample_rate_half = (sample_rate_for_bands + 1) / 2;
        int num_bands = 1;
        while (num_bands < 25 && sample_rate_half > kCriticalFrequencies[(size_t)(num_bands - 1)]) {
            ++num_bands;
        }

        bands_.resize((size_t)num_bands + 1);
        bands_[0] = 2;
        for (int i = 1; i < num_bands; ++i) {
            bands_[(size_t)i] = (uint32_t)((kCriticalFrequencies[(size_t)(i - 1)] * frame_length_ / sample_rate_half) & ~1);
        }
        bands_[(size_t)num_bands] = (uint32_t)frame_length_;

        previous_overlap_.assign((size_t)overlap_length_, 0.0f);

        int quarter_length = frame_length_ >> 2;
        rdft_cos_table_.resize((size_t)quarter_length);
        rdft_sin_table_.resize((size_t)quarter_length);
        double theta = (2.0 * kPi) / frame_length_;
        for (int i = 0; i < quarter_length; ++i) {
            rdft_cos_table_[(size_t)i] = (float)std::cos(i * theta);
            rdft_sin_table_[(size_t)i] = (float)std::sin(i * theta);
        }

        int fft_size = frame_length_ >> 1;
        int fft_bits = int_log2(fft_size);
        fft_bit_reverse_.resize((size_t)fft_size);
        for (int i = 0; i < fft_size; ++i) {
            fft_bit_reverse_[(size_t)i] = reverse_bits(i, fft_bits);
        }

        fft_twiddles_.resize((size_t)fft_size);
        for (int i = 0; i < (fft_size >> 1); ++i) {
            int twiddle_index = i << 1;
            double angle = (-2.0 * kPi * i) / fft_size;
            fft_twiddles_[(size_t)twiddle_index] = (float)std::cos(angle);
            fft_twiddles_[(size_t)(twiddle_index + 1)] = (float)std::sin(angle);
        }
    }

    bool decode_packet(const std::vector<uint8_t>& audio_payload, std::vector<float>& output) {
        output.clear();
        bit_reader_le reader(audio_payload);
        output.reserve((size_t)frame_length_);

        while (reader.bits_remaining() > 0) {
            std::vector<float> coeffs = decode_coefficients(reader);
            if (!reader.ok()) {
                output.clear();
                return false;
            }
            std::vector<float> transformed = inverse_packed_rdft(coeffs);
            apply_overlap(transformed);
            std::vector<float> block = slice_playable_samples(transformed);
            output.insert(output.end(), block.begin(), block.end());
            reader.align32();
            if (!reader.ok()) {
                output.clear();
                return false;
            }
        }
        return true;
    }

private:
    std::vector<float> decode_coefficients(bit_reader_le& reader) {
        std::vector<float> coeffs((size_t)frame_length_, 0.0f);
        coeffs[0] = read_packed_float(reader) * root_;
        coeffs[1] = read_packed_float(reader) * root_;

        std::vector<float> quantizers(bands_.size() - 1);
        for (size_t i = 0; i < quantizers.size(); ++i) {
            int index = (int)reader.read_bits(8);
            quantizers[i] = quant_table_[(size_t)std::min(index, 95)];
        }

        size_t band_index = 0;
        float current_quantizer = quantizers[0];
        int coefficient_index = 2;
        while (coefficient_index < frame_length_) {
            bool has_run = reader.read_bit();
            int group_end = 0;
            if (has_run) {
                int run_length = kRleLengthTable[(size_t)reader.read_bits(4)];
                group_end = coefficient_index + run_length * 8;
            } else {
                group_end = coefficient_index + 8;
            }
            group_end = std::min(group_end, frame_length_);

            int width = (int)reader.read_bits(4);
            if (width == 0) {
                while (coefficient_index < group_end) {
                    coeffs[(size_t)coefficient_index++] = 0.0f;
                    while (band_index + 1 < bands_.size() && bands_[band_index] < (uint32_t)coefficient_index) {
                        current_quantizer = quantizers[std::min(band_index, quantizers.size() - 1)];
                        ++band_index;
                    }
                }
                continue;
            }

            while (coefficient_index < group_end) {
                if (band_index < bands_.size() - 1 && bands_[band_index] == (uint32_t)coefficient_index) {
                    current_quantizer = quantizers[band_index];
                    ++band_index;
                }
                uint32_t coefficient = reader.read_bits(width);
                if (coefficient == 0) {
                    coeffs[(size_t)coefficient_index] = 0.0f;
                } else {
                    bool negative = reader.read_bit();
                    float value = current_quantizer * (float)coefficient;
                    coeffs[(size_t)coefficient_index] = negative ? -value : value;
                }
                ++coefficient_index;
            }
        }

        return coeffs;
    }

    std::vector<float> inverse_packed_rdft(const std::vector<float>& packed_coefficients) {
        int n = frame_length_;
        std::vector<float> data = packed_coefficients;
        float dc = data[0];
        float nyquist = data[1];
        data[0] = 0.5f * (dc + nyquist);
        data[1] = 0.5f * (dc - nyquist);

        int quarter_length = n >> 2;
        for (int i = 1; i < quarter_length; ++i) {
            int i1 = 2 * i;
            int i2 = n - i1;

            float d01 = data[(size_t)i1];
            float d02 = data[(size_t)i2];
            float d11 = data[(size_t)(i1 + 1)];
            float d12 = data[(size_t)(i2 + 1)];

            float even_re = 0.5f * (d01 + d02);
            float odd_im = 0.5f * (d01 - d02);
            float even_im = 0.5f * (d11 - d12);
            float odd_re = -0.5f * (d11 + d12);

            float cos_value = rdft_cos_table_[(size_t)i];
            float sin_value = rdft_sin_table_[(size_t)i];

            data[(size_t)i1] = even_re + odd_re * cos_value - odd_im * sin_value;
            data[(size_t)(i1 + 1)] = even_im + odd_im * cos_value + odd_re * sin_value;
            data[(size_t)i2] = even_re - odd_re * cos_value + odd_im * sin_value;
            data[(size_t)(i2 + 1)] = -even_im + odd_im * cos_value + odd_re * sin_value;
        }

        forward_fft_in_place(data);
        return data;
    }

    void apply_overlap(std::vector<float>& samples) {
        if (!first_frame_) {
            for (int i = 0; i < overlap_length_; ++i) {
                samples[(size_t)i] = ((previous_overlap_[(size_t)i] * (overlap_length_ - i)) + (samples[(size_t)i] * i)) / overlap_length_;
            }
        }
        std::copy(samples.end() - overlap_length_, samples.end(), previous_overlap_.begin());
        first_frame_ = false;
    }

    std::vector<float> slice_playable_samples(const std::vector<float>& samples) const {
        int count = frame_length_ - overlap_length_;
        return std::vector<float>(samples.begin(), samples.begin() + count);
    }

    static float read_packed_float(bit_reader_le& reader) {
        int exponent = (int)reader.read_bits(5);
        uint32_t mantissa = reader.read_bits(23);
        bool negative = reader.read_bit();
        double value = mantissa * std::pow(2.0, exponent - 23);
        return negative ? (float)-value : (float)value;
    }

    void forward_fft_in_place(std::vector<float>& data) {
        int n = (int)data.size() >> 1;
        for (int i = 0; i < n; ++i) {
            int j = fft_bit_reverse_[(size_t)i];
            if (j > i) {
                int i2 = i << 1;
                int j2 = j << 1;
                std::swap(data[(size_t)i2], data[(size_t)j2]);
                std::swap(data[(size_t)(i2 + 1)], data[(size_t)(j2 + 1)]);
            }
        }

        for (int length = 2; length <= n; length <<= 1) {
            int half_size = length >> 1;
            int step = n / length;
            for (int i = 0; i < n; i += length) {
                int twiddle_index = 0;
                for (int j = 0; j < half_size; ++j) {
                    float wr = fft_twiddles_[(size_t)(twiddle_index << 1)];
                    float wi = fft_twiddles_[(size_t)((twiddle_index << 1) + 1)];
                    int even_index = (i + j) << 1;
                    int odd_index = (i + j + half_size) << 1;
                    float er = data[(size_t)even_index];
                    float ei = data[(size_t)(even_index + 1)];
                    float orr = data[(size_t)odd_index];
                    float oi = data[(size_t)(odd_index + 1)];

                    float tr = wr * orr - wi * oi;
                    float ti = wr * oi + wi * orr;

                    data[(size_t)odd_index] = er - tr;
                    data[(size_t)(odd_index + 1)] = ei - ti;
                    data[(size_t)even_index] = er + tr;
                    data[(size_t)(even_index + 1)] = ei + ti;
                    twiddle_index += step;
                }
            }
        }
    }

    static int reverse_bits(int value, int bit_count) {
        int result = 0;
        for (int i = 0; i < bit_count; ++i) {
            result = (result << 1) | ((value >> i) & 1);
        }
        return result;
    }

    int original_channels_ = 0;
    int frame_length_ = 0;
    int overlap_length_ = 0;
    float root_ = 0.0f;
    std::vector<float> quant_table_;
    std::vector<uint32_t> bands_;
    std::vector<float> previous_overlap_;
    std::vector<float> rdft_cos_table_;
    std::vector<float> rdft_sin_table_;
    std::vector<int> fft_bit_reverse_;
    std::vector<float> fft_twiddles_;
    bool first_frame_ = true;
};

class bink_video_decoder {
public:
    explicit bink_video_decoder(const bink_file& file)
        : width_(file.width())
        , height_(file.height())
        , num_pixels_(width_ * height_)
        , uv_size_(((width_ + 1) >> 1) * ((height_ + 1) >> 1))
        , previous_frame_data_((size_t)(num_pixels_ + uv_size_ * 2), 0)
        , reference_data_(bink_reference_data::instance()) {
        for (auto& tree : color_high_trees_) {
            tree.tree_index = 0;
            for (int i = 0; i < 16; ++i) {
                tree.symbols[(size_t)i] = (uint8_t)i;
            }
        }
    }

    bool decode(const frame_packet& packet, std::vector<uint8_t>& yuv) {
        if (!ok_) {
            return false;
        }

        int chroma_width = (width_ + 1) >> 1;
        int chroma_height = (height_ + 1) >> 1;
        yuv = previous_frame_data_;
        bit_reader_le reader(packet.video_payload);

        decode_plane(reader, yuv, width_, height_, 0);
        if (!ok_ || !reader.ok()) {
            ok_ = false;
            return false;
        }
        if (reader.bits_remaining() >= 1) {
            decode_plane(reader, yuv, chroma_width, chroma_height, num_pixels_);
            if (!ok_ || !reader.ok()) {
                ok_ = false;
                return false;
            }
        }
        if (reader.bits_remaining() >= 1) {
            decode_plane(reader, yuv, chroma_width, chroma_height, num_pixels_ + uv_size_);
            if (!ok_ || !reader.ok()) {
                ok_ = false;
                return false;
            }
        }

        previous_frame_data_ = yuv;
        return true;
    }

    bool ok() const { return ok_; }

private:
    void decode_plane(bit_reader_le& reader, std::vector<uint8_t>& frame_data, int current_width, int current_height, int plane_offset) {
        int block_width = (current_width + 7) >> 3;
        int block_height = (current_height + 7) >> 3;
        int plane_size = current_width * current_height;

        plane_data_.assign(frame_data.begin() + plane_offset, frame_data.begin() + plane_offset + plane_size);
        previous_plane_data_.assign(previous_frame_data_.begin() + plane_offset, previous_frame_data_.begin() + plane_offset + plane_size);
        plane_data_offset_ = 0;
        plane_end_offset_ = plane_size;
        stride_ = current_width;
        current_plane_width_ = current_width;
        current_plane_height_ = current_height;

        init_lengths(std::max(current_width, 8), block_width);
        read_plane_trees(reader);
        if (!ok_ || !reader.ok()) {
            ok_ = false;
            return;
        }

        int block_line_increment = stride_ * 7;
        int current_block_y = 0;
        int current_plane_ptr = 0;

        while (current_block_y++ < block_height) {
            read_block_types(reader, bundles_[kParamBlockTypes]);
            read_block_types(reader, bundles_[kParamSubBlockTypes]);
            read_colors(reader, bundles_[kParamColors]);
            read_patterns(reader, bundles_[kParamPattern]);
            read_motion_values(reader, bundles_[kParamXOff]);
            read_motion_values(reader, bundles_[kParamYOff]);
            read_dcs(reader, bundles_[kParamIntraDc], false);
            read_dcs(reader, bundles_[kParamInterDc], true);
            read_runs(reader, bundles_[kParamRun]);
            if (!ok_ || !reader.ok()) {
                ok_ = false;
                return;
            }

            int current_block_x = 0;
            while (current_block_x++ < block_width) {
                int block_type = get_value(kParamBlockTypes);
                if (!ok_) {
                    return;
                }
                switch (block_type) {
                case kSkipBlock:
                    break;
                case kScaledBlock:
                    if ((current_block_y & 1) != 0) {
                        decode_scaled_block(reader, current_plane_ptr);
                        if (!ok_ || !reader.ok()) {
                            return;
                        }
                    }
                    ++current_block_x;
                    current_plane_ptr += 16;
                    continue;
                case kMotionBlock:
                    decode_motion_block(current_plane_ptr);
                    break;
                case kRunBlock:
                    decode_run_block(reader, plane_data_.data(), plane_data_.size(), current_plane_ptr, stride_, true);
                    break;
                case kResidueBlock:
                    decode_residue_block(reader, current_plane_ptr);
                    break;
                case kIntraBlock:
                    decode_intra_block(reader, plane_data_.data(), plane_data_.size(), current_plane_ptr, stride_, true);
                    break;
                case kFillBlock:
                    decode_fill_block(current_plane_ptr, 8);
                    break;
                case kInterBlock:
                    decode_inter_block(reader, current_plane_ptr);
                    break;
                case kPatternBlock:
                    decode_pattern_block(plane_data_.data(), plane_data_.size(), current_plane_ptr, stride_, true);
                    break;
                case kRawBlock:
                    decode_raw_block(current_plane_ptr);
                    break;
                default:
                    logs::error("BIK: Invalid BIK block type.");
                    ok_ = false;
                    return;
                }
                if (!ok_ || !reader.ok()) {
                    ok_ = false;
                    return;
                }
                current_plane_ptr += 8;
            }
            current_plane_ptr += block_line_increment;
        }

        reader.align32();
        if (!reader.ok()) {
            ok_ = false;
        }
        std::copy(plane_data_.begin(), plane_data_.end(), frame_data.begin() + plane_offset);
    }

    void decode_motion_block(int destination_offset) {
        int x_off = get_value(kParamXOff);
        int y_off = get_value(kParamYOff);
        int source_offset = destination_offset + x_off + y_off * stride_;
        copy_block(source_offset, destination_offset);
    }

    void decode_run_block(bit_reader_le& reader, uint8_t* block, size_t block_len, int offset, int block_stride, bool plane_target) {
        int i = 0;
        int scan_index = (int)reader.read_bits(4) << 6;
        do {
            int run = get_value(kParamRun) + 1;
            i += run;

            if (reader.read_bit()) {
                int value = get_value(kParamColors);
                for (int j = 0; j < run; ++j) {
                    int pos = scan_index < 1024 ? reference_data_.patterns[(size_t)(scan_index >> 6)][(size_t)(scan_index & 63)] : 0;
                    ++scan_index;
                    write_block_byte(block, block_len, offset + ((pos >> 3) * block_stride) + (pos & 7), (uint8_t)value, plane_target);
                }
            } else {
                for (int j = 0; j < run; ++j) {
                    int pos = scan_index < 1024 ? reference_data_.patterns[(size_t)(scan_index >> 6)][(size_t)(scan_index & 63)] : 0;
                    ++scan_index;
                    write_block_byte(block, block_len, offset + ((pos >> 3) * block_stride) + (pos & 7), (uint8_t)get_value(kParamColors), plane_target);
                }
            }
        } while (i < 63);

        if (i == 63) {
            int pos = scan_index < 1024 ? reference_data_.patterns[(size_t)(scan_index >> 6)][(size_t)(scan_index & 63)] : 0;
            write_block_byte(block, block_len, offset + ((pos >> 3) * block_stride) + (pos & 7), (uint8_t)get_value(kParamColors), plane_target);
        }
    }

    void decode_residue_block(bit_reader_le& reader, int destination_offset) {
        int x_off = get_value(kParamXOff);
        int y_off = get_value(kParamYOff);
        int source_offset = destination_offset + x_off + y_off * stride_;
        std::fill(temp_dct_buffer_.begin(), temp_dct_buffer_.end(), 0);
        read_coefficients_or_residue(reader, temp_dct_buffer_.data(), -1, false);
        copy_block(source_offset, destination_offset);
        bink_video_transforms::add_block_8x8(temp_dct_buffer_.data(), plane_data_.data(), plane_data_.size(), destination_offset, stride_);
    }

    void decode_intra_block(bit_reader_le& reader, uint8_t* block, size_t block_len, int offset, int block_stride, bool) {
        temp_dct_buffer_[0] = get_value(kParamIntraDc);
        std::fill(temp_dct_buffer_.begin() + 1, temp_dct_buffer_.end(), 0);
        read_coefficients_or_residue(reader, temp_dct_buffer_.data(), 0, false);
        bink_video_transforms::idct_put(temp_dct_buffer_.data(), block, block_len, offset, block_stride);
    }

    void decode_fill_block(int destination_offset, int size) {
        int value = get_value(kParamColors);
        for (int y = 0; y < size; ++y) {
            int row_offset = destination_offset + y * stride_;
            for (int x = 0; x < size; ++x) {
                write_plane_byte(row_offset + x, (uint8_t)value);
            }
        }
    }

    void decode_inter_block(bit_reader_le& reader, int destination_offset) {
        int x_off = get_value(kParamXOff);
        int y_off = get_value(kParamYOff);
        int source_offset = destination_offset + x_off + y_off * stride_;
        copy_block(source_offset, destination_offset);
        temp_dct_buffer_[0] = get_value(kParamInterDc);
        std::fill(temp_dct_buffer_.begin() + 1, temp_dct_buffer_.end(), 0);
        read_coefficients_or_residue(reader, temp_dct_buffer_.data(), 0, true);
        bink_video_transforms::idct_add(temp_dct_buffer_.data(), plane_data_.data(), plane_data_.size(), destination_offset, stride_);
    }

    void decode_pattern_block(uint8_t* block, size_t block_len, int offset, int block_stride, bool plane_target) {
        int color0 = get_value(kParamColors);
        int color1 = get_value(kParamColors);
        for (int i = 0; i < 8; ++i) {
            int value = get_value(kParamPattern);
            for (int j = 0; j < 8; ++j) {
                write_block_byte(block, block_len, offset + i * block_stride + j, (uint8_t)(((value & 1) == 0) ? color0 : color1), plane_target);
                value >>= 1;
            }
        }
    }

    void decode_raw_block(int destination_offset) {
        for (int y = 0; y < 8; ++y) {
            int row_offset = destination_offset + y * stride_;
            for (int x = 0; x < 8; ++x) {
                write_plane_byte(row_offset + x, (uint8_t)get_value(kParamColors));
            }
        }
    }

    void decode_scaled_block(bit_reader_le& reader, int destination_offset) {
        int sub_block = get_value(kParamSubBlockTypes);
        switch (sub_block) {
        case kRawBlock:
            for (int i = 0; i < 64; ++i) {
                temp_scaling_buffer_[(size_t)i] = (uint8_t)get_value(kParamColors);
            }
            break;
        case kIntraBlock:
            decode_intra_block(reader, temp_scaling_buffer_.data(), temp_scaling_buffer_.size(), 0, 8, false);
            break;
        case kFillBlock:
            decode_fill_block(destination_offset, 16);
            return;
        case kRunBlock:
            decode_run_block(reader, temp_scaling_buffer_.data(), temp_scaling_buffer_.size(), 0, 8, false);
            break;
        case kPatternBlock:
            decode_pattern_block(temp_scaling_buffer_.data(), temp_scaling_buffer_.size(), 0, 8, false);
            break;
        default:
            logs::error("BIK: Invalid BIK scaled block type.");
            ok_ = false;
            return;
        }

        int source_index = 0;
        int destination_line = destination_offset;
        int max_destination_line = destination_line + (stride_ << 4);
        int line_increment = (stride_ << 1) - 15;
        while (destination_line < max_destination_line) {
            uint8_t value = temp_scaling_buffer_[(size_t)source_index++];
            write_plane_byte(destination_line, value);
            write_plane_byte(destination_line + stride_, value);
            ++destination_line;
            write_plane_byte(destination_line, value);
            write_plane_byte(destination_line + stride_, value);
            destination_line += (source_index & 0x7) != 0 ? 1 : line_increment;
        }
    }

    void copy_block(int source_offset, int destination_offset) {
        if (source_offset == destination_offset) {
            return;
        }

        int source_base_y = floor_div(source_offset, stride_);
        int source_base_x = source_offset - source_base_y * stride_;
        int destination_row = destination_offset;
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                int dst_index = destination_row + x;
                if (dst_index < plane_data_offset_ || dst_index >= plane_end_offset_) {
                    continue;
                }

                int src_x = clamp_int(source_base_x + x, 0, current_plane_width_ - 1);
                int src_y = clamp_int(source_base_y + y, 0, current_plane_height_ - 1);
                int src_index = src_y * stride_ + src_x;
                plane_data_[(size_t)dst_index] = previous_plane_data_[(size_t)src_index];
            }
            destination_row += stride_;
        }
    }

    static int floor_div(int value, int divisor) {
        int quotient = value / divisor;
        int remainder = value % divisor;
        if (remainder != 0 && ((remainder < 0) != (divisor < 0))) {
            --quotient;
        }
        return quotient;
    }

    void write_plane_byte(int index, uint8_t value) {
        if (index >= plane_data_offset_ && index < plane_end_offset_) {
            plane_data_[(size_t)index] = value;
        }
    }

    void write_block_byte(uint8_t* block, size_t block_len, int index, uint8_t value, bool plane_target) {
        if (plane_target) {
            write_plane_byte(index, value);
        } else if (index >= 0 && index < (int)block_len) {
            block[(size_t)index] = value;
        }
    }

    void init_lengths(int current_width, int block_width) {
        int aligned_width = align8(current_width);
        bundles_[kParamBlockTypes].length_bits = int_log2((aligned_width >> 3) + 511) + 1;
        bundles_[kParamSubBlockTypes].length_bits = int_log2((aligned_width >> 4) + 511) + 1;
        bundles_[kParamColors].length_bits = int_log2(block_width * 64 + 511) + 1;
        bundles_[kParamPattern].length_bits = int_log2((block_width << 3) + 511) + 1;
        bundles_[kParamXOff].length_bits = int_log2((aligned_width >> 3) + 511) + 1;
        bundles_[kParamYOff].length_bits = int_log2((aligned_width >> 3) + 511) + 1;
        bundles_[kParamIntraDc].length_bits = int_log2((aligned_width >> 3) + 511) + 1;
        bundles_[kParamInterDc].length_bits = int_log2((aligned_width >> 3) + 511) + 1;
        bundles_[kParamRun].length_bits = int_log2(block_width * 48 + 511) + 1;
    }

    void read_plane_trees(bit_reader_le& reader) {
        for (int i = 0; i < kParamCount; ++i) {
            if (i == kParamColors) {
                for (auto& tree : color_high_trees_) {
                    read_tree(reader, tree);
                }
                color_last_value_ = 0;
            }
            if (i != kParamIntraDc && i != kParamInterDc) {
                read_tree(reader, bundles_[(size_t)i].tree);
            }
            bundles_[(size_t)i].reset();
        }
    }

    void read_tree(bit_reader_le& reader, tree_t& tree) {
        int tree_index = (int)reader.read_bits(4);
        tree.tree_index = tree_index;
        if (tree_index == 0) {
            for (int i = 0; i < 16; ++i) {
                tree.symbols[(size_t)i] = (uint8_t)i;
            }
            return;
        }

        if (reader.read_bit()) {
            int len = (int)reader.read_bits(3);
            std::array<bool, 16> used{};
            for (int i = 0; i <= len; ++i) {
                uint8_t symbol = (uint8_t)reader.read_bits(4);
                tree.symbols[(size_t)i] = symbol;
                used[(size_t)symbol] = true;
            }
            for (int i = 0; i < 16 && len < 15; ++i) {
                if (!used[(size_t)i]) {
                    tree.symbols[(size_t)++len] = (uint8_t)i;
                }
            }
        } else {
            std::array<uint8_t, 16> current{};
            std::array<uint8_t, 16> next{};
            for (int i = 0; i < 16; ++i) {
                current[(size_t)i] = (uint8_t)i;
            }
            int depth = (int)reader.read_bits(2);
            for (int i = 0; i <= depth; ++i) {
                int size = 1 << i;
                for (int t = 0; t < 16; t += size << 1) {
                    merge(reader, next, t, current, t, size);
                }
                current.swap(next);
            }
            tree.symbols = current;
        }
    }

    static void merge(bit_reader_le& reader, std::array<uint8_t, 16>& destination, int destination_offset, const std::array<uint8_t, 16>& source, int source_offset, int size) {
        int left_offset = source_offset;
        int right_offset = source_offset + size;
        int left = size;
        int right = size;
        int write_offset = destination_offset;

        while (left > 0 && right > 0) {
            if (!reader.read_bit()) {
                destination[(size_t)write_offset++] = source[(size_t)left_offset++];
                --left;
            } else {
                destination[(size_t)write_offset++] = source[(size_t)right_offset++];
                --right;
            }
        }
        while (left-- > 0) {
            destination[(size_t)write_offset++] = source[(size_t)left_offset++];
        }
        while (right-- > 0) {
            destination[(size_t)write_offset++] = source[(size_t)right_offset++];
        }
    }

    void read_block_types(bit_reader_le& reader, bundle_t& bundle) {
        int count = begin_bundle_read(reader, bundle);
        if (count <= 0) {
            return;
        }

        if (reader.read_bit()) {
            int value = (int)reader.read_bits(4);
            bundle.data.insert(bundle.data.end(), (size_t)count, value);
        } else {
            int last = 0;
            for (int i = 0; i < count;) {
                int value = decode_huff(reader, bundle.tree);
                if (value < 12) {
                    last = value;
                    bundle.data.push_back(value);
                    ++i;
                } else {
                    int run = kBlockTypeRleLengths[(size_t)(value - 12)];
                    bundle.data.insert(bundle.data.end(), (size_t)run, last);
                    i += run;
                }
            }
        }
    }

    void read_colors(bit_reader_le& reader, bundle_t& bundle) {
        int count = begin_bundle_read(reader, bundle);
        if (count <= 0) {
            return;
        }
        bool is_run = reader.read_bit();
        int iterations = is_run ? 1 : count;
        do {
            int high_value = decode_huff(reader, color_high_trees_[(size_t)color_last_value_]);
            int value = decode_huff(reader, bundle.tree) | (high_value << 4);
            color_last_value_ = high_value;
            value = value > 127 ? 256 - value : value + 128;
            if (is_run) {
                bundle.data.insert(bundle.data.end(), (size_t)count, value);
            } else {
                bundle.data.push_back(value);
            }
        } while (--iterations > 0);
    }

    void read_patterns(bit_reader_le& reader, bundle_t& bundle) {
        int count = begin_bundle_read(reader, bundle);
        for (int i = 0; i < count; ++i) {
            bundle.data.push_back(decode_huff(reader, bundle.tree) | (decode_huff(reader, bundle.tree) << 4));
        }
    }

    void read_motion_values(bit_reader_le& reader, bundle_t& bundle) {
        int count = begin_bundle_read(reader, bundle);
        if (count <= 0) {
            return;
        }
        if (reader.read_bit()) {
            int value = (int)reader.read_bits(4);
            if (value != 0) {
                int sign = reader.read_bit() ? -1 : 0;
                value = (value ^ sign) - sign;
            }
            for (int i = 0; i < count; ++i) {
                bundle.data.push_back((int8_t)value);
            }
        } else {
            for (int i = 0; i < count; ++i) {
                int value = decode_huff(reader, bundle.tree);
                if (value != 0) {
                    int sign = reader.read_bit() ? -1 : 0;
                    value = (value ^ sign) - sign;
                }
                bundle.data.push_back((int8_t)value);
            }
        }
    }

    void read_dcs(bit_reader_le& reader, bundle_t& bundle, bool has_sign) {
        int count = begin_bundle_read(reader, bundle);
        if (count <= 0) {
            return;
        }
        int value = (int)reader.read_bits(has_sign ? 10 : 11);
        if (value != 0 && has_sign) {
            int sign = reader.read_bit() ? -1 : 0;
            value = (value ^ sign) - sign;
        }
        bundle.data.push_back(value);
        int index = 1;
        while (index < count) {
            int len = std::min(count - index, 8);
            int size = (int)reader.read_bits(4);
            if (size != 0) {
                for (int j = 0; j < len; ++j) {
                    int delta = (int)reader.read_bits(size);
                    if (delta != 0) {
                        int sign = reader.read_bit() ? -1 : 0;
                        delta = (delta ^ sign) - sign;
                    }
                    value += delta;
                    bundle.data.push_back(value);
                }
            } else {
                for (int j = 0; j < len; ++j) {
                    bundle.data.push_back(value);
                }
            }
            index += len;
        }
    }

    void read_runs(bit_reader_le& reader, bundle_t& bundle) {
        int count = begin_bundle_read(reader, bundle);
        if (count <= 0) {
            return;
        }
        if (reader.read_bit()) {
            int value = (int)reader.read_bits(4);
            bundle.data.insert(bundle.data.end(), (size_t)count, value);
        } else {
            for (int i = 0; i < count; ++i) {
                bundle.data.push_back(decode_huff(reader, bundle.tree));
            }
        }
    }

    static int begin_bundle_read(bit_reader_le& reader, bundle_t& bundle) {
        if (!bundle.active || (int)bundle.data.size() > bundle.read_index) {
            return 0;
        }
        int count = (int)reader.read_bits(bundle.length_bits);
        if (count == 0) {
            bundle.active = false;
            return 0;
        }
        return count;
    }

    int get_value(int source) {
        if (!ok_) {
            return 0;
        }
        bundle_t& bundle = bundles_[(size_t)source];
        if (bundle.read_index >= (int)bundle.data.size()) {
            logs::error("BIK: BIK bundle underflow.");
            ok_ = false;
            return 0;
        }
        return bundle.data[(size_t)bundle.read_index++];
    }

    int decode_huff(bit_reader_le& reader, const tree_t& tree) {
        if (!ok_) {
            return 0;
        }
        int code = 0;
        for (int len = 1; len <= kHuffmanMaxCodeLength; ++len) {
            code |= (reader.read_bit() ? 1 : 0) << (len - 1);
            if (!reader.ok()) {
                ok_ = false;
                return 0;
            }
            for (int symbol_index = 0; symbol_index < kHuffmanSymbolCount; ++symbol_index) {
                if (kHuffmanCodeLengths[tree.tree_index][symbol_index] == len && kHuffmanCodeBits[tree.tree_index][symbol_index] == code) {
                    return tree.symbols[(size_t)symbol_index];
                }
            }
        }
        logs::error("BIK: Invalid BIK Huffman code.");
        ok_ = false;
        return 0;
    }

    void read_coefficients_or_residue(bit_reader_le& reader, int* block, int quant_start_index, bool inter) {
        bool residue = quant_start_index < 0;
        int list_start = 64;
        int list_end = residue ? 68 : 70;
        int masks_count = 0;
        int coeff_count = 0;

        coeff_list_[64] = 4;
        coeff_list_[65] = 24;
        coeff_list_[66] = 44;
        mode_list_[64] = 0;
        mode_list_[65] = 0;
        mode_list_[66] = 0;
        if (residue) {
            masks_count = (int)reader.read_bits(7);
            coeff_list_[67] = 0;
            mode_list_[67] = 2;
        } else {
            coeff_list_[67] = 1;
            coeff_list_[68] = 2;
            coeff_list_[69] = 3;
            mode_list_[67] = 3;
            mode_list_[68] = 3;
            mode_list_[69] = 3;
        }

        int bits = residue ? 1 << (int)reader.read_bits(3) : (int)reader.read_bits(4) - 1;
        while (residue ? bits != 0 : bits >= 0) {
            if (residue) {
                for (int i = 0; i < coeff_count; ++i) {
                    if (reader.read_bit()) {
                        int current_index = coeff_index_[(size_t)i];
                        int value = block[current_index];
                        block[current_index] = value < 0 ? value - bits : value + bits;
                        if (masks_count-- == 0) {
                            return;
                        }
                    }
                }
            }

            int list_pos = list_start;
            while (list_pos < list_end) {
                int coefficient = coeff_list_[(size_t)list_pos];
                int mode = mode_list_[(size_t)list_pos];
                if ((mode | coefficient) == 0 || !reader.read_bit()) {
                    ++list_pos;
                    continue;
                }

                switch (mode) {
                case 0:
                case 2:
                    if (mode == 0) {
                        coeff_list_[(size_t)list_pos] = coefficient + 4;
                        mode_list_[(size_t)list_pos] = 1;
                    } else {
                        coeff_list_[(size_t)list_pos] = 0;
                        mode_list_[(size_t)list_pos++] = 0;
                    }

                    for (int i = coefficient; i < coefficient + 4; ++i) {
                        if (reader.read_bit()) {
                            coeff_list_[(size_t)--list_start] = i;
                            mode_list_[(size_t)list_start] = 3;
                        } else if (residue) {
                            int offset = reference_data_.scan[(size_t)i];
                            coeff_index_[(size_t)coeff_count++] = offset;
                            block[offset] = reader.read_bit() ? -bits : bits;
                            if (masks_count-- == 0) {
                                return;
                            }
                        } else {
                            int value = bits != 0
                                ? apply_signed_magnitude(reader, (int)reader.read_bits(bits) | (1 << bits))
                                : 1 - ((reader.read_bit() ? 1 : 0) << 1);
                            int block_index = reference_data_.scan[(size_t)i];
                            block[block_index] = value;
                            coeff_index_[(size_t)coeff_count++] = i;
                        }
                    }
                    break;
                case 1:
                    mode_list_[(size_t)list_pos] = 2;
                    for (int i = coefficient + 4; i < coefficient + 16; i += 4) {
                        coeff_list_[(size_t)list_end] = i;
                        mode_list_[(size_t)list_end++] = 2;
                    }
                    break;
                case 3:
                    coeff_list_[(size_t)list_pos] = 0;
                    mode_list_[(size_t)list_pos++] = 0;
                    if (residue) {
                        int offset = reference_data_.scan[(size_t)coefficient];
                        coeff_index_[(size_t)coeff_count++] = offset;
                        block[offset] = reader.read_bit() ? -bits : bits;
                        if (masks_count-- == 0) {
                            return;
                        }
                    } else {
                        int value = bits != 0
                            ? apply_signed_magnitude(reader, (int)reader.read_bits(bits) | (1 << bits))
                            : 1 - ((reader.read_bit() ? 1 : 0) << 1);
                        int block_index = reference_data_.scan[(size_t)coefficient];
                        block[block_index] = value;
                        coeff_index_[(size_t)coeff_count++] = coefficient;
                    }
                    break;
                }
            }

            bits = residue ? bits >> 1 : bits - 1;
        }

        if (!residue) {
            int quant_index = (int)reader.read_bits(4);
            const auto& quant_table = inter ? reference_data_.inter_quant[(size_t)quant_index] : reference_data_.intra_quant[(size_t)quant_index];
            block[0] = (block[0] * quant_table[0]) >> 11;
            while (coeff_count-- > 0) {
                int zig_zag_index = coeff_index_[(size_t)coeff_count];
                int block_index = reference_data_.scan[(size_t)zig_zag_index];
                block[block_index] = (block[block_index] * quant_table[(size_t)zig_zag_index]) >> 11;
            }
        }
    }

    static int apply_signed_magnitude(bit_reader_le& reader, int value) {
        int sign = reader.read_bit() ? -1 : 0;
        return (value ^ sign) - sign;
    }

    int width_ = 0;
    int height_ = 0;
    int num_pixels_ = 0;
    int uv_size_ = 0;
    std::vector<uint8_t> previous_frame_data_;
    std::array<bundle_t, kParamCount> bundles_{};
    std::array<tree_t, 16> color_high_trees_{};
    std::array<int, 64> coeff_index_{};
    std::array<int, 128> coeff_list_{};
    std::array<uint8_t, 128> mode_list_{};
    std::array<uint8_t, 64> temp_scaling_buffer_{};
    std::array<int, 64> temp_dct_buffer_{};
    bink_reference_data& reference_data_;

    std::vector<uint8_t> plane_data_;
    std::vector<uint8_t> previous_plane_data_;
    int plane_data_offset_ = 0;
    int plane_end_offset_ = 0;
    int stride_ = 0;
    int color_last_value_ = 0;
    int current_plane_width_ = 0;
    int current_plane_height_ = 0;
    bool ok_ = true;
};

static uint8_t clamp_to_byte(int value) {
    return (uint8_t)clamp_int(value, 0, 255);
}

static void convert_bik_yuv_to_rgba(const std::vector<uint8_t>& yuv, int width, int height, std::vector<uint32_t>& pixels) {
    int chroma_width = (width + 1) >> 1;
    int y_plane_size = width * height;
    int uv_plane_size = chroma_width * ((height + 1) >> 1);
    int u_offset = y_plane_size;
    int v_offset = y_plane_size + uv_plane_size;
    pixels.resize((size_t)width * (size_t)height);

    for (int y = 0; y < height; ++y) {
        int y_row = y * width;
        int uv_row = (y >> 1) * chroma_width;
        for (int x = 0; x < width; ++x) {
            int y_sample = yuv[(size_t)(y_row + x)];
            int uv_index = uv_row + (x >> 1);
            int u_sample = yuv[(size_t)(u_offset + uv_index)];
            int v_sample = yuv[(size_t)(v_offset + uv_index)];

            int c = y_sample - 16;
            if (c < 0) {
                c = 0;
            }
            int d = u_sample - 128;
            int e = v_sample - 128;
            uint8_t red = clamp_to_byte((298 * c + 409 * e + 128) >> 8);
            uint8_t green = clamp_to_byte((298 * c - 100 * d - 208 * e + 128) >> 8);
            uint8_t blue = clamp_to_byte((298 * c + 516 * d + 128) >> 8);

            pixels[(size_t)(y * width + x)] = 0xff000000u | ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
        }
    }
}

static void floats_to_pcm_s16(const std::vector<float>& samples, std::vector<uint8_t>& pcm) {
    pcm.resize(samples.size() * sizeof(int16_t));
    auto* out = reinterpret_cast<int16_t*>(pcm.data());
    for (size_t i = 0; i < samples.size(); ++i) {
        float sample = std::max(-1.0f, std::min(1.0f, samples[i]));
        out[i] = (int16_t)std::lrint(sample * 32767.0f);
    }
}

} // namespace

struct bink_movie {
    struct decoded_frame {
        std::vector<uint32_t> rgba;
        std::vector<uint8_t> audio_pcm;
        int frame_index = -1;
        bool audio_prebuffered = false;
    };

    bink_file file;
    bink_sequential_packet_reader reader;
    bink_video_decoder video_decoder;
    bink_rdft_audio_decoder audio_decoder;
    std::vector<uint32_t> current_rgba;
    std::vector<uint8_t> current_audio_pcm;
    std::deque<decoded_frame> queued_frames;
    int current_frame = -1;
    int next_decode_frame = 0;
    int profile_logs = 0;
    bool current_audio_prebuffered = false;
    bool valid = false;

    explicit bink_movie(const std::string& path)
        : file(bink_file::load(path))
        , reader(file)
        , video_decoder(file)
        , audio_decoder(file.audio_track()) {
        if (!file.valid() || !reader.valid() || !video_decoder.ok()) {
            return;
        }
        current_rgba.reserve((size_t)file.width() * (size_t)file.height());
        current_audio_pcm.reserve(file.audio_track().max_decoded_size);
        valid = true;
    }

    bool decode_frame_data(int frame_index, decoded_frame& decoded) {
        if (!valid || !reader.valid() || !video_decoder.ok()) {
            return false;
        }

        Uint32 packet_begin = SDL_GetTicks();
        frame_packet packet;
        if (!reader.read_frame_packet(frame_index, packet)) {
            valid = false;
            return false;
        }
        Uint32 packet_end = SDL_GetTicks();
        std::vector<uint8_t> yuv;
        if (!video_decoder.decode(packet, yuv)) {
            valid = false;
            return false;
        }
        Uint32 video_end = SDL_GetTicks();
        convert_bik_yuv_to_rgba(yuv, file.width(), file.height(), decoded.rgba);
        Uint32 rgba_end = SDL_GetTicks();
        decoded.audio_pcm.clear();
        if (!packet.audio_packets.empty() && !packet.audio_packets[0].payload.empty()) {
            std::vector<float> decoded_samples;
            if (!audio_decoder.decode_packet(packet.audio_packets[0].payload, decoded_samples)) {
                valid = false;
                return false;
            }
            floats_to_pcm_s16(decoded_samples, decoded.audio_pcm);
        }
        Uint32 audio_end = SDL_GetTicks();

        if (profile_logs < 20) {
            logs::info(
                "BIK frame timings: frame=%d read_ms=%u video_ms=%u rgba_ms=%u audio_ms=%u audio_bytes=%d",
                frame_index,
                (unsigned)(packet_end - packet_begin),
                (unsigned)(video_end - packet_end),
                (unsigned)(rgba_end - video_end),
                (unsigned)(audio_end - rgba_end),
                (int)decoded.audio_pcm.size());
            ++profile_logs;
        }
        decoded.frame_index = frame_index;
        return true;
    }

    bool decode_frame(int frame_index) {
        decoded_frame decoded;
        if (!decode_frame_data(frame_index, decoded)) {
            return false;
        }

        current_rgba = std::move(decoded.rgba);
        current_audio_pcm = std::move(decoded.audio_pcm);
        current_frame = frame_index;
        current_audio_prebuffered = decoded.audio_prebuffered;
        return true;
    }

    bool prebuffer_frames(int frame_count, bink_audio_sink sink, void* userdata) {
        frame_count = std::max(frame_count, 0);
        while ((int)queued_frames.size() < frame_count && next_decode_frame < (int)file.frame_index().size()) {
            decoded_frame decoded;
            if (!decode_frame_data(next_decode_frame, decoded)) {
                return false;
            }

            if (sink && !decoded.audio_pcm.empty()) {
                sink(userdata, decoded.audio_pcm.data(), (int)decoded.audio_pcm.size());
                decoded.audio_prebuffered = true;
            }

            queued_frames.push_back(std::move(decoded));
            ++next_decode_frame;
        }

        return true;
    }

    bool advance_frame() {
        if (!queued_frames.empty()) {
            decoded_frame decoded = std::move(queued_frames.front());
            queued_frames.pop_front();
            current_rgba = std::move(decoded.rgba);
            current_audio_pcm = std::move(decoded.audio_pcm);
            current_frame = decoded.frame_index;
            current_audio_prebuffered = decoded.audio_prebuffered;
            return true;
        }

        if (next_decode_frame >= (int)file.frame_index().size()) {
            return false;
        }

        bool ok = decode_frame(next_decode_frame);
        if (ok) {
            ++next_decode_frame;
        }
        return ok;
    }
};

bink bink_open(const char* filename) {
    if (!filename || !*filename) {
        return nullptr;
    }

    vfs::path fs_file = vfs::path(filename).resolve();
    if (fs_file.empty()) {
        return nullptr;
    }

    bink_movie* movie = new bink_movie(fs_file.c_str());
    if (!movie->valid) {
        delete movie;
        return nullptr;
    }
    return movie;
}

void bink_close(bink movie) {
    delete movie;
}

int bink_get_width(bink movie) {
    return movie ? movie->file.width() : 0;
}

int bink_get_height(bink movie) {
    return movie ? movie->file.height() : 0;
}

int bink_get_micros_per_frame(bink movie) {
    return movie ? movie->file.micros_per_frame() : 0;
}

int bink_has_audio(bink movie) {
    return movie ? 1 : 0;
}

int bink_get_audio_channels(bink movie) {
    return movie ? (movie->file.audio_track().is_stereo ? 2 : 1) : 0;
}

int bink_get_audio_sample_rate(bink movie) {
    return movie ? movie->file.audio_track().sample_rate : 0;
}

int bink_get_audio_bitdepth(bink movie) {
    return movie ? 16 : 0;
}

int bink_first_frame(bink movie) {
    if (!movie || !movie->valid) {
        return 0;
    }
    movie->queued_frames.clear();
    movie->next_decode_frame = 1;
    movie->current_audio_prebuffered = false;
    return movie->decode_frame(0) ? 1 : 0;
}

int bink_next_frame(bink movie) {
    if (!movie || !movie->valid) {
        return 0;
    }
    if (movie->current_frame + 1 >= (int)movie->file.frame_index().size()) {
        return 0;
    }
    return movie->advance_frame() ? 1 : 0;
}

int bink_prebuffer_frames(bink movie, int frame_count, bink_audio_sink sink, void* userdata) {
    if (!movie || !movie->valid) {
        return 0;
    }
    return movie->prebuffer_frames(frame_count, sink, userdata) ? 1 : 0;
}

int bink_current_audio_is_prebuffered(bink movie) {
    return movie && movie->current_audio_prebuffered ? 1 : 0;
}

const uint32_t* bink_get_frame_rgba(bink movie) {
    return movie && !movie->current_rgba.empty() ? movie->current_rgba.data() : nullptr;
}

const void* bink_get_frame_audio(bink movie) {
    return movie && !movie->current_audio_pcm.empty() ? movie->current_audio_pcm.data() : nullptr;
}

int bink_get_frame_audio_size(bink movie) {
    return movie ? (int)movie->current_audio_pcm.size() : 0;
}
