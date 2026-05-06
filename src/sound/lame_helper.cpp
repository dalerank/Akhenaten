#include "lame_helper.h"

#include <memory>
#include <algorithm>
#include <vector>
#include <cstring>

#include "core/log.h"

lame_helper::lame_helper() {
}

lame_helper::~lame_helper() {
}

void lame_helper::write_16_bits_low_high(FILE * fp, int val)
{
    unsigned char bytes[2];
    bytes[0] = (val & 0xff);
    bytes[1] = ((val >> 8) & 0xff);
    fwrite(bytes, 1, 2, fp);
}

void lame_helper::write_32_bits_low_high(FILE * fp, int val)
{
    unsigned char bytes[4];
    bytes[0] = (val & 0xff);
    bytes[1] = ((val >> 8) & 0xff);
    bytes[2] = ((val >> 16) & 0xff);
    bytes[3] = ((val >> 24) & 0xff);
    fwrite(bytes, 1, 4, fp);
}

void lame_helper::write_wave_header(FILE * const fp, int pcmbytes, int freq, int channels, int bits)
{
    int     bytes = (bits + 7) / 8;
    /* quick and dirty, but documented */
    fwrite("RIFF", 1, 4, fp); /* label */
    write_32_bits_low_high(fp, pcmbytes + 44 - 8); /* length in bytes without header */
    fwrite("WAVEfmt ", 2, 4, fp); /* 2 labels */
    write_32_bits_low_high(fp, 2 + 2 + 4 + 4 + 2 + 2); /* length of PCM format declaration area */
    write_16_bits_low_high(fp, 1); /* is PCM? */
    write_16_bits_low_high(fp, channels); /* number of channels */
    write_32_bits_low_high(fp, freq); /* sample frequency in [Hz] */
    write_32_bits_low_high(fp, freq * channels * bytes); /* bytes per second */
    write_16_bits_low_high(fp, channels * bytes); /* bytes per sample time */
    write_16_bits_low_high(fp, bits); /* bits per sample */
    fwrite("data", 1, 4, fp); /* label */
    write_32_bits_low_high(fp, pcmbytes); /* length in bytes of raw PCM data */
}

vfs::reader lame_helper::decode(const char* mp3_in) {
    vfs::reader mp3 = vfs::file_open(mp3_in, "rb");
    if (!mp3) {
        logs::info("FATAL ERROR: file '%s' can't be opened for read. Aborting!", mp3_in);
        return vfs::reader();
    }

    short int pcm_l[PCM_SIZE], pcm_r[PCM_SIZE];
    unsigned char mp3_buffer[MP3_SIZE];
    std::vector<uint8_t> pcm_data;

    lame_t lame = lame_init();
    lame_set_decode_only(lame, 1);
    if (lame_init_params(lame) == -1) {
        logs::info("FATAL ERROR: parameters failed to initialize properly in lame. Aborting!");
        lame_close(lame);
        return vfs::reader();
    }

    hip_t hip = hip_decode_init();
    mp3data_struct mp3data;
    memset(&mp3data, 0, sizeof(mp3data));

    int channels = 0;
    int sample_rate = 0;
    size_t offset = 0;

    while (offset < (size_t)mp3->size()) {
        const size_t chunk_size = std::min<size_t>(MP3_SIZE, (size_t)mp3->size() - offset);
        memcpy(mp3_buffer, (const uint8_t*)mp3->data() + offset, chunk_size);
        offset += chunk_size;

        int mp3_len = (int)chunk_size;
        int samples = 0;
        do {
            samples = hip_decode1_headers(hip, mp3_buffer, mp3_len, pcm_l, pcm_r, &mp3data);

            if (mp3data.header_parsed == 1) {
                channels = mp3data.stereo;
                sample_rate = mp3data.samplerate;
            }

            if (samples > 0 && mp3data.header_parsed != 1) {
                logs::info("WARNING: lame decode error occurred while decoding '%s'", mp3_in);
                break;
            }

            if (samples > 0) {
                const size_t frame_bytes = sizeof(short int) * (channels == 2 ? 2 : 1);
                const size_t old_size = pcm_data.size();
                pcm_data.resize(old_size + samples * frame_bytes);

                uint8_t* out = pcm_data.data() + old_size;
                for (int i = 0; i < samples; ++i) {
                    memcpy(out, &pcm_l[i], sizeof(short int));
                    out += sizeof(short int);
                    if (channels == 2) {
                        memcpy(out, &pcm_r[i], sizeof(short int));
                        out += sizeof(short int);
                    }
                }
            }

            mp3_len = 0;
        } while (samples > 0);
    }

    hip_decode_exit(hip);
    lame_close(lame);

    if (channels <= 0 || sample_rate <= 0) {
        logs::info("FATAL ERROR: unable to decode '%s' into PCM data", mp3_in);
        return vfs::reader();
    }

    const int pcm_bytes = (int)pcm_data.size();
    const int total_bytes = pcm_bytes + 44;
    uint8_t* wav_data = (uint8_t*)malloc(total_bytes);
    if (!wav_data) {
        return vfs::reader();
    }

    auto write_u16 = [] (uint8_t* dst, int val) {
        dst[0] = (uint8_t)(val & 0xff);
        dst[1] = (uint8_t)((val >> 8) & 0xff);
    };
    auto write_u32 = [] (uint8_t* dst, int val) {
        dst[0] = (uint8_t)(val & 0xff);
        dst[1] = (uint8_t)((val >> 8) & 0xff);
        dst[2] = (uint8_t)((val >> 16) & 0xff);
        dst[3] = (uint8_t)((val >> 24) & 0xff);
    };

    memcpy(wav_data + 0, "RIFF", 4);
    write_u32(wav_data + 4, pcm_bytes + 44 - 8);
    memcpy(wav_data + 8, "WAVEfmt ", 8);
    write_u32(wav_data + 16, 16);
    write_u16(wav_data + 20, 1);
    write_u16(wav_data + 22, channels);
    write_u32(wav_data + 24, sample_rate);
    write_u32(wav_data + 28, sample_rate * channels * 2);
    write_u16(wav_data + 32, channels * 2);
    write_u16(wav_data + 34, 16);
    memcpy(wav_data + 36, "data", 4);
    write_u32(wav_data + 40, pcm_bytes);
    if (pcm_bytes > 0) {
        memcpy(wav_data + 44, pcm_data.data(), pcm_bytes);
    }

    return std::make_shared<vfs::data_reader>(mp3_in, wav_data, total_bytes);
}
