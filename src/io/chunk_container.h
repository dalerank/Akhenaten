#pragma once

#include "core/core.h"
#include "core/hvector.h"
#include "content/reader.h"

#include <cstdint>
#include <cstdio>
#include <vector>

// Sectioned container for .svx savegames.
//
//     [file header][section][section] ... [section]
//
// Every section is self-describing: a header with the chunk name and sizes, the
// payload, then an epilog repeating the name between 0xFFFF markers. Section order
// in the file carries no meaning - chunks are located by name.
//
// A chunk missing from the file is NOT an error: the save simply predates that
// chunk, and the loader falls back to its defaults. A corrupt or truncated file IS
// an error and the whole load is refused - there is no partial load.
//
// Legacy .svx files (written before this container existed) have no magic and are
// read by the old positional path instead.
//
// On-disk layout (packed headers, magic, epilog marks) stays in the .cpp.

class svx {
public:
    static constexpr int NAME_LEN = 32;
    static constexpr uint32_t CONTAINER_REV = 1;

    // Scratch for one chunk/section compress or decompress. Shared by the legacy
    // positional path and the sectioned container - both use the same prefixed layout.
    static constexpr int CODEC_SCRATCH_SIZE = 3000000;

    // Payload u32 prefix: zip byte count, or this marker meaning "the rest is raw".
    static constexpr uint32_t PAYLOAD_UNCOMPRESSED = 0x80000000u;

    struct section_info {
        char name[NAME_LEN + 1] = "";
        uint32_t payload_offset = 0;
        uint32_t payload_size = 0;
        uint32_t raw_size = 0;
        uint32_t crc = 0;
        bool compressed = false;
    };

    using section_list = hvector<section_info, 128>;

    enum e_scan_result {
        SCAN_OK,
        SCAN_NOT_CONTAINER,
        SCAN_CORRUPT,
    };

    // Public fields from the file header that callers actually need after a scan.
    struct scan_header {
        uint32_t container_rev = 0;
        uint32_t save_data_version = 0;
    };

    struct prefixed_payload {
        uint32_t prefix = PAYLOAD_UNCOMPRESSED;
        const void *body = nullptr;
        uint32_t body_size = 0;
    };

    static bool is_container(vfs::reader reader, int offset);

    // Walks the section chain and builds the index. Touches no io_buffer and no game
    // state, so the console tools and the loader can share it: svx_dump must never be
    // able to overwrite the running city just by looking at a file.
    static e_scan_result scan(vfs::reader reader, int offset, scan_header &hdr, section_list &out);

    static pcstr scan_result_str(e_scan_result r);

    static bool decompress_prefixed(const void *src, uint32_t compressed_size, void *dst, int expected_raw_size);

    struct byte_sink {
        FILE* fp = nullptr;
        std::vector<uint8_t>* bytes = nullptr;

        bool write(const void* data, size_t size);
    };

    static bool write_file_header(byte_sink& out, uint32_t save_data_version, uint32_t section_count, pcstr debug_path);

    static bool write_section(byte_sink& out, pcstr name, const prefixed_payload& payload, uint32_t raw_size,
      uint32_t crc, int index, pcstr debug_path);
};
