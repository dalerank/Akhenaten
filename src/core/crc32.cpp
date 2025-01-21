#include "crc32.h"

static crc32_tabel_t crc32_table = generate_crc32_lookup_table();

uint32_t crc32(const void *P, uint32_t len) {
    uint32_t ulCRC = 0xffffffff;
    uint8_t *buffer = (uint8_t *)P;

    while (len--)
        ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];

    return ulCRC ^ 0xffffffff;
}
