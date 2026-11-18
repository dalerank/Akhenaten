#include "core/zip.h"

#include "core/log.h"

#include <algorithm>
#include <array>
#include <memory>

namespace {

    enum class explode_status {
        success,
        invalid_window_size,
        literal_encoding_unsupported,
        too_few_input_bytes,
        error_decoding,
    };

    constexpr int TOKEN_EOF = 773;
    constexpr int TOKEN_ERROR = 774;
    constexpr int INPUT_BLOCK_SIZE = 2048;
    constexpr int WINDOW_SIZE_BYTES = 4096;
    constexpr int MAX_COPY_LENGTH = 518;

    constexpr std::array<uint8_t, 64> copy_offset_bits
      = {2, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    constexpr std::array<uint8_t, 64> copy_offset_code = {0x03, 0x0D, 0x05, 0x19, 0x09, 0x11, 0x01, 0x3E, 0x1E, 0x2E,
      0x0E, 0x36, 0x16, 0x26, 0x06, 0x3A, 0x1A, 0x2A, 0x0A, 0x32, 0x12, 0x22, 0x42, 0x02, 0x7C, 0x3C, 0x5C, 0x1C, 0x6C,
      0x2C, 0x4C, 0x0C, 0x74, 0x34, 0x54, 0x14, 0x64, 0x24, 0x44, 0x04, 0x78, 0x38, 0x58, 0x18, 0x68, 0x28, 0x48, 0x08,
      0xF0, 0x70, 0xB0, 0x30, 0xD0, 0x50, 0x90, 0x10, 0xE0, 0x60, 0xA0, 0x20, 0xC0, 0x40, 0x80, 0x00};

    constexpr std::array<uint8_t, 16> copy_length_base_bits = {3, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7};

    constexpr std::array<uint16_t, 16> copy_length_base_value
      = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0A, 0x0E, 0x16, 0x26, 0x46, 0x86, 0x106};

    constexpr std::array<uint8_t, 16> copy_length_base_code
      = {0x05, 0x03, 0x01, 0x06, 0x0A, 0x02, 0x0C, 0x14, 0x04, 0x18, 0x08, 0x30, 0x10, 0x20, 0x40, 0x00};

    constexpr std::array<uint8_t, 16> copy_length_extra_bits = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};

    template <size_t N>
    std::array<uint8_t, 256> make_jump_table(const std::array<uint8_t, N>& bits, const std::array<uint8_t, N>& codes) {
        std::array<uint8_t, 256> jump{};
        for (int i = (int)N - 1; i >= 0; i--) {
            int code = codes[i];
            do {
                jump[code] = (uint8_t)i;
                code += 1 << bits[i];
            } while (code < 0x100);
        }
        return jump;
    }

    class exploder {
    public:
        exploder(xspan<const uint8_t> input, xspan<uint8_t> output) : input(input), output(output) {}

        std::optional<size_t> run() {
            const explode_status status = explode();
            if (status != explode_status::success || stopped) {
                logs::error("COMP Error uncompressing.");
                return std::nullopt;
            }
            return output_pos;
        }

    private:
        size_t read_input(uint8_t* dst, size_t length) {
            if (stopped || input_pos >= input.size()) {
                return 0;
            }
            length = std::min(length, input.size() - input_pos);
            std::copy_n(input.data() + input_pos, length, dst);
            input_pos += length;
            return length;
        }

        void write_output(const uint8_t* src, size_t length) {
            if (stopped) {
                return;
            }
            if (output_pos >= output.size()) {
                logs::error("COMP2 Out of buffer space.");
                stopped = true;
                return;
            }
            if (output.size() - output_pos < length) {
                logs::error("COMP1 Corrupt.");
                stopped = true;
                return;
            }
            std::copy_n(src, length, output.data() + output_pos);
            output_pos += length;
        }

        bool skip_bits(int num_bits) {
            if (bits_available >= num_bits) {
                bits_available -= num_bits;
                bit_buffer = (uint16_t)(bit_buffer >> num_bits);
                return true;
            }
            bit_buffer = (uint16_t)(bit_buffer >> bits_available);
            if (input_block_pos == input_block_end) {
                input_block_pos = INPUT_BLOCK_SIZE;
                input_block_end = read_input(input_block.data(), INPUT_BLOCK_SIZE);
                if (!input_block_end) {
                    return false;
                }
                input_block_pos = 0;
            }
            bit_buffer |= (uint16_t)(input_block[input_block_pos++] << 8);
            bit_buffer = (uint16_t)(bit_buffer >> (num_bits - bits_available));
            bits_available += 8 - num_bits;
            return true;
        }

        int decode_next_token() {
            if (!(bit_buffer & 1)) {
                if (!skip_bits(1)) {
                    return TOKEN_ERROR;
                }
                const int literal = bit_buffer & 0xff;
                if (!skip_bits(8)) {
                    return TOKEN_ERROR;
                }
                return literal;
            }

            if (!skip_bits(1)) {
                return TOKEN_ERROR;
            }
            int index = copy_length_jump_table[bit_buffer & 0xff];
            if (!skip_bits(copy_length_base_bits[index])) {
                return TOKEN_ERROR;
            }
            const int extra_bits = copy_length_extra_bits[index];
            if (extra_bits) {
                const int extra_value = bit_buffer & ((1 << extra_bits) - 1);
                if (!skip_bits(extra_bits) && index + extra_value != 270) {
                    return TOKEN_ERROR;
                }
                index = copy_length_base_value[index] + extra_value;
            }
            return index + 256;
        }

        int decode_copy_offset(int copy_length) {
            const int index = copy_offset_jump_table[bit_buffer & 0xff];
            if (!skip_bits(copy_offset_bits[index])) {
                return 0;
            }
            int offset;
            if (copy_length == 2) {
                offset = (bit_buffer & 3) | (index << 2);
                if (!skip_bits(2)) {
                    return 0;
                }
            } else {
                offset = (bit_buffer & dictionary_mask) | (index << window_size);
                if (!skip_bits(window_size)) {
                    return 0;
                }
            }
            return offset + 1;
        }

        int explode_tokens() {
            int window_pos = WINDOW_SIZE_BYTES;
            int token;
            while (true) {
                token = decode_next_token();
                if (token >= TOKEN_EOF) {
                    break;
                }
                if (token >= 256) {
                    const int length = token - 254;
                    const int offset = decode_copy_offset(length);
                    if (!offset) {
                        token = TOKEN_ERROR;
                        break;
                    }
                    for (int i = 0; i < length; i++) {
                        window[window_pos + i] = window[window_pos - offset + i];
                    }
                    window_pos += length;
                } else {
                    window[window_pos++] = (uint8_t)token;
                }
                if (window_pos >= 2 * WINDOW_SIZE_BYTES) {
                    write_output(&window[WINDOW_SIZE_BYTES], WINDOW_SIZE_BYTES);
                    std::copy(window.begin() + WINDOW_SIZE_BYTES, window.begin() + window_pos, window.begin());
                    window_pos -= WINDOW_SIZE_BYTES;
                }
            }
            write_output(&window[WINDOW_SIZE_BYTES], window_pos - WINDOW_SIZE_BYTES);
            return token;
        }

        explode_status explode() {
            input_block_pos = INPUT_BLOCK_SIZE;
            input_block_end = read_input(input_block.data(), INPUT_BLOCK_SIZE);
            if (input_block_end <= 4) {
                return explode_status::too_few_input_bytes;
            }
            const bool has_literal_encoding = input_block[0] != 0;
            window_size = input_block[1];
            bit_buffer = input_block[2];
            bits_available = 0;
            input_block_pos = 3;

            if (window_size < 4 || window_size > 6) {
                return explode_status::invalid_window_size;
            }
            dictionary_mask = 0xFFFF >> (16 - window_size);
            if (has_literal_encoding) {
                return explode_status::literal_encoding_unsupported;
            }

            copy_length_jump_table = make_jump_table(copy_length_base_bits, copy_length_base_code);
            copy_offset_jump_table = make_jump_table(copy_offset_bits, copy_offset_code);

            return explode_tokens() == TOKEN_EOF ? explode_status::success : explode_status::error_decoding;
        }

        xspan<const uint8_t> input;
        size_t input_pos = 0;
        xspan<uint8_t> output;
        size_t output_pos = 0;
        bool stopped = false;

        int window_size = 0;
        int dictionary_mask = 0;
        uint16_t bit_buffer = 0;
        int bits_available = 0;

        size_t input_block_pos = 0;
        size_t input_block_end = 0;
        std::array<uint8_t, INPUT_BLOCK_SIZE> input_block{};
        std::array<uint8_t, 2 * WINDOW_SIZE_BYTES + MAX_COPY_LENGTH> window{};

        std::array<uint8_t, 256> copy_offset_jump_table{};
        std::array<uint8_t, 256> copy_length_jump_table{};
    };

} // namespace

std::optional<size_t> zip_decompress(xspan<const uint8_t> input, xspan<uint8_t> output) {
    return std::make_unique<exploder>(input, output)->run();
}
