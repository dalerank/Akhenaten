#include "lame_helper.h"

#include <memory>

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
	int read, i, samples;
	long wavsize = 0; // use to count the number of mp3 byte read, this is used to write the length of the wave file
	long cumulative_read = 0;

	short int pcm_l[PCM_SIZE], pcm_r[PCM_SIZE];
	unsigned char mp3_buffer[MP3_SIZE];

	FILE* mp3 = fopen(mp3_in, "rb");
	if(mp3 == NULL) {
		logs::info("FATAL ERROR: file '%s' can't be open for read. Aborting!\n", mp3_in);
		return vfs::reader();
	}

	fseek(mp3, 0, SEEK_END);
    long MP3_total_size = ftell(mp3);
    fseek(mp3, 0, SEEK_SET);

	vfs::path pcm_out = mp3_in;
	vfs::file_change_extension(pcm_out.data(), "wav");

	FILE* pcm = fopen(pcm_out, "wb");
	if(pcm == NULL)	{
		logs::info("FATAL ERROR: file '%s' can't be open for write. Aborting!\n", pcm_out.c_str());
		return vfs::reader();
	}

	
	lame_t lame = lame_init();
	lame_set_decode_only(lame, 1);
	if(lame_init_params(lame) == -1) {
		logs::info("FATAL ERROR: parameters failed to initialize properly in lame. Aborting!\n", pcm_out.c_str());
		return vfs::reader();
	}

	hip_t hip = hip_decode_init();
	
	mp3data_struct mp3data;
	memset(&mp3data, 0, sizeof(mp3data));
	
	int nChannels = -1;
	int nSampleRate = -1;
	int mp3_len;

	while((read = fread(mp3_buffer, sizeof(char), MP3_SIZE, mp3)) > 0) {
		mp3_len = read;
		cumulative_read += read * sizeof(char);
		do {
			samples = hip_decode1_headers(hip, mp3_buffer, mp3_len, pcm_l, pcm_r, &mp3data);
			wavsize += samples;

			if(mp3data.header_parsed == 1) { 
				if(nChannels < 0) {//reading for the first time
					//Write the header
					write_wave_header(pcm, 0x7FFFFFFF, mp3data.samplerate, mp3data.stereo, 16); //unknown size, so write maximum 32 bit signed value
				}
				nChannels = mp3data.stereo;
				nSampleRate = mp3data.samplerate;
			}

			if(samples > 0 && mp3data.header_parsed != 1) {
				logs::info("WARNING: lame decode error occured!");
				break;
			}

			if(samples > 0) {
				for(i = 0 ; i < samples; i++) {
					fwrite((char*)&pcm_l[i], sizeof(char), sizeof(pcm_l[i]), pcm);
					if(nChannels == 2) {
						fwrite((char*)&pcm_r[i], sizeof(char), sizeof(pcm_r[i]), pcm);
					}
				}
			}
			mp3_len = 0;

		} while(samples>0);
	}

	i = (16 / 8) * mp3data.stereo;
    if (wavsize <= 0) {
       wavsize = 0;
    } else if (wavsize > 0xFFFFFFD0 / i)  {
        wavsize = 0xFFFFFFD0;
    } else {
        wavsize *= i;
    }
	
	if (!fseek(pcm, 0l, SEEK_SET)) { //seek back and adjust length
		write_wave_header(pcm, (int)wavsize, mp3data.samplerate, mp3data.stereo, 16);
	} else {
		logs::info("WARNING: can't seek back to adjust length in wave header!");
	}

	hip_decode_exit(hip);
	lame_close(lame);
	fclose(mp3);
	fclose(pcm);

	return vfs::file_open(pcm_out);
}