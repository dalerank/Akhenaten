#pragma once

#include "core/core.h"
#include "core/hvector.h"
#include "content/reader.h"

#include <cstdint>

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

namespace svx {

constexpr int NAME_LEN = 32;
constexpr uint16_t EPILOG_MARK = 0xFFFF;
constexpr uint32_t CONTAINER_REV = 1;
constexpr char MAGIC[8] = {'A', 'K', 'H', 'N', 'S', 'V', 'X', '\0'};

// Every payload starts with this u32: either the size of the zip stream that
// follows, or this marker meaning "the rest is raw". Uncompressed chunks carry the
// marker too, so a payload can be read back without knowing the schema's
// compression flag - that flag only decides how we write.
constexpr uint32_t PAYLOAD_UNCOMPRESSED = 0x80000000u;

// max sections we are willing to index from one file; the schema has ~116
constexpr size_t MAX_SECTIONS = 256;

#pragma pack(push, 1)
struct file_header {
    char magic[8];
    uint32_t container_rev;
    uint32_t save_data_version;
    uint32_t section_count;       // diagnostic only - the scan is the source of truth
    uint16_t section_header_size; // lets a future header grow without breaking old builds
    uint16_t epilog_size;
};

struct section_header {
    char name[NAME_LEN]; // NUL-padded, the lookup key
    uint32_t payload_size; // bytes on disk between this header and the epilog
    uint32_t raw_size;     // size of the data after decompression
    uint32_t crc;          // crc32 over the DECOMPRESSED data, not over the payload
};

struct section_epilog {
    uint16_t mark_begin;
    char name[NAME_LEN];
    uint16_t mark_end;
};
#pragma pack(pop)

static_assert(sizeof(file_header) == 24, "svx::file_header must stay 24 bytes on disk");
static_assert(sizeof(section_header) == 44, "svx::section_header must stay 44 bytes on disk");
static_assert(sizeof(section_epilog) == 36, "svx::section_epilog must stay 36 bytes on disk");

struct section_info {
    char name[NAME_LEN + 1] = ""; // NUL-terminated copy of the on-disk name
    uint32_t payload_offset = 0;  // absolute file offset of the payload
    uint32_t payload_size = 0;
    uint32_t raw_size = 0;
    uint32_t crc = 0;
    bool compressed = false; // read from the payload prefix, for tooling only
};

using section_list = hvector<section_info, 128>;

enum e_scan_result {
    SCAN_OK,
    SCAN_NOT_CONTAINER, // no magic - caller should fall back to the legacy reader
    SCAN_CORRUPT,       // magic present but the section chain does not hold up
};

// Reads the file header if the magic is there. Cheap - does not walk the sections.
bool peek_header(vfs::reader reader, int offset, file_header &out);

// Walks the section chain and builds the index. Touches no io_buffer and no game
// state, so the console tools and the loader can share it: svx_dump must never be
// able to overwrite the running city just by looking at a file.
e_scan_result scan(vfs::reader reader, int offset, file_header &hdr, section_list &out);

pcstr scan_result_str(e_scan_result r);

} // namespace svx
