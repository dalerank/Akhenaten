#include "js/test/js_test_common.h"

#include "content/vfs.h"
#include "core/crc32.h"
#include "figure/figure_type.h"

#include <cstdio>
#include <cstring>
#include <vector>

// Rewrites a saved .svx so it looks like a pre-linearisation save: the container
// header drops to an old data version and entertainer/fireman/boat/soldier figure
// action states are bumped back to their legacy numbering. Returns the number of
// patched figure records, or a negative value on failure (-1 read, -2 layout).
static int __test_legacyify_save(pcstr path) {
    vfs::path full = vfs::path(path).resolve();
    FILE *fp = vfs::file_open_os(full, "rb");
    if (!fp) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    const long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::vector<uint8_t> data((size_t)file_size);
    if (fread(data.data(), 1, (size_t)file_size, fp) != (size_t)file_size) {
        fclose(fp);
        return -1;
    }
    fclose(fp);

    constexpr uint32_t PAYLOAD_UNCOMPRESSED = 0x80000000u;
    constexpr int FIGURE_RECORD_SIZE = 388;
    constexpr uint32_t HEADER_VERSION_OFFSET = 12;
    constexpr uint32_t LEGACY_VERSION = 189;

    int patched = 0;
    bool found_figures = false;

    size_t pos = 24; // sizeof(file_header)
    while (pos + 44 <= data.size()) {
        char name[33] = {};
        memcpy(name, data.data() + pos, 32);
        const uint32_t payload_size = *reinterpret_cast<const uint32_t *>(data.data() + pos + 32);
        const uint32_t raw_size = *reinterpret_cast<const uint32_t *>(data.data() + pos + 36);
        const uint32_t crc_offset = pos + 40;
        const size_t payload_at = pos + 44;
        const size_t epilog_at = payload_at + payload_size;

        if (strcmp(name, "figures") == 0) {
            found_figures = true;
            if (raw_size == 0 || raw_size % FIGURE_RECORD_SIZE != 0) {
                return -2;
            }
            const uint32_t prefix = *reinterpret_cast<const uint32_t *>(data.data() + payload_at);
            if (prefix != PAYLOAD_UNCOMPRESSED) {
                return -2;
            }

            uint8_t *body = data.data() + payload_at + 4;
            for (uint32_t i = 0; i < raw_size / FIGURE_RECORD_SIZE; ++i) {
                uint8_t *rec = body + i * FIGURE_RECORD_SIZE;
                const uint8_t ftype = rec[10];
                int16_t action = *reinterpret_cast<int16_t *>(rec + 56);
                int16_t legacy = action;
                switch (ftype) {
                case FIGURE_JUGGLER:
                case FIGURE_MUSICIAN:
                case FIGURE_DANCER:
                case FIGURE_SENET_PLAYER:
                    if (action >= 0 && action <= 6) {
                        legacy = action + 90;
                    } else if (action == 7) {
                        legacy = 13;
                    }
                    break;
                case FIGURE_FIREMAN:
                    if (action >= 0 && action <= 7) {
                        legacy = action + 70;
                    }
                    break;
                case FIGURE_FISHING_BOAT:
                    if (action >= 0 && action <= 8) {
                        legacy = action + 190;
                    }
                    break;
                case FIGURE_FERRY_BOAT:
                    if (action >= 0 && action <= 4) {
                        legacy = action + 200;
                    }
                    break;
                case FIGURE_ARCHER:
                case FIGURE_INFANTRY:
                case FIGURE_FCHARIOTEER:
                    if (action >= 0 && action <= 11) {
                        legacy = action + 80;
                    }
                    break;
                default:
                    break;
                }
                if (legacy != action) {
                    *reinterpret_cast<int16_t *>(rec + 56) = legacy;
                    patched++;
                }
            }

            const uint32_t new_crc = crc32(body, raw_size);
            *reinterpret_cast<uint32_t *>(data.data() + crc_offset) = new_crc;
        }

        if (epilog_at + 36 > data.size()) {
            break;
        }
        pos = epilog_at + 36;
    }

    if (!found_figures) {
        return -2;
    }

    *reinterpret_cast<uint32_t *>(data.data() + HEADER_VERSION_OFFSET) = LEGACY_VERSION;

    fp = vfs::file_open_os(full, "wb");
    if (!fp) {
        return -1;
    }
    const size_t written = fwrite(data.data(), 1, data.size(), fp);
    fclose(fp);
    return (written == data.size()) ? patched : -1;
}
ANK_FUNCTION_1(__test_legacyify_save);
