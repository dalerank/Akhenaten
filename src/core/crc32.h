#pragma once

#include <cstdint>
#include <array>
#include <string>

using crc32_tabel_t = std::array<uint32_t, 256>;

// Reflects CRC bits in the lookup table
constexpr inline uint32_t reflect(uint32_t ref, char ch) {
    uint32_t value(0);

    // Swap bit 0 for bit 7
    // bit 1 for bit 6, etc.
    for (int i = 1; i < (ch + 1); i++) {
        if (ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}

constexpr inline crc32_tabel_t generate_crc32_lookup_table() {
    crc32_tabel_t crc32_table{};

    // This is the official polynomial used by CRC-32
    // in PKZip, WinZip and Ethernet.
    uint32_t ulPolynomial = 0x04c11db7;

    // 256 values representing ASCII character codes.
    for (int i = 0; i <= 0xFF; i++) {
        crc32_table[i] = reflect(i, 8) << 24;
        for (int j = 0; j < 8; j++) {
            crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
        }
        crc32_table[i] = reflect(crc32_table[i], 32);
    }

    return crc32_table;
}

constexpr inline uint32_t crc32_str(const char* P) {
    size_t len = std::char_traits<char>::length(P);
    constexpr crc32_tabel_t crc32_table_c = generate_crc32_lookup_table();
    // Pass a text string to this function and it will return the CRC.

    // Once the lookup table has been filled in by the two functions above,
    // this function creates all CRCs using only the lookup table.

    // Be sure to use unsigned variables,
    // because negative values introduce high bits
    // where zero bits are required.

    // Start out with all bits set high.
    uint32_t ulCRC = 0xffffffff;

    // Perform the algorithm on each character
    // in the string, using the lookup table values.
    while (len--) {
        ulCRC = (ulCRC >> 8) ^ crc32_table_c[(ulCRC & 0xFF) ^ (*P)];
        P++;
    }

    // Exclusive OR the result with the beginning value.
    return ulCRC ^ 0xffffffff;
}

uint32_t crc32(const void *P, uint32_t len);