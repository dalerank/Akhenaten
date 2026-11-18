#include "chunk_container.h"

#include "core/log.h"
#include "core/zip.h"

#include <cstring>

namespace {

constexpr uint16_t EPILOG_MARK = 0xFFFF;
constexpr char MAGIC[8] = {'A', 'K', 'H', 'N', 'S', 'V', 'X', '\0'};
constexpr size_t MAX_SECTIONS = 256;

#pragma pack(push, 1)
struct file_header {
    char magic[8];
    uint32_t container_rev;
    uint32_t save_data_version;
    uint32_t section_count;
    uint16_t section_header_size;
    uint16_t epilog_size;
};

struct section_header {
    char name[svx::NAME_LEN];
    uint32_t payload_size;
    uint32_t raw_size;
    uint32_t crc;
};

struct section_epilog {
    uint16_t mark_begin;
    char name[svx::NAME_LEN];
    uint16_t mark_end;
};
#pragma pack(pop)

static_assert(sizeof(file_header) == 24, "svx file_header must stay 24 bytes on disk");
static_assert(sizeof(section_header) == 44, "svx section_header must stay 44 bytes on disk");
static_assert(sizeof(section_epilog) == 36, "svx section_epilog must stay 36 bytes on disk");

bool peek_file_header(vfs::reader reader, int offset, file_header &out) {
    if (!reader || offset < 0) {
        return false;
    }

    if (offset + (int)sizeof(file_header) > reader->size()) {
        return false;
    }

    reader->seek(offset);
    reader->r(&out, sizeof(out));

    return memcmp(out.magic, MAGIC, sizeof(MAGIC)) == 0;
}

} // namespace

pcstr svx::scan_result_str(e_scan_result r) {
    switch (r) {
    case SCAN_OK: return "ok";
    case SCAN_NOT_CONTAINER: return "not a container";
    case SCAN_CORRUPT: return "corrupt";
    }
    return "?";
}

bool svx::decompress_prefixed(const void *src, uint32_t compressed_size, void *dst, int expected_raw_size) {
    if (!src || !dst || expected_raw_size <= 0 || compressed_size == 0
        || compressed_size == PAYLOAD_UNCOMPRESSED
        || (int)compressed_size > CODEC_SCRATCH_SIZE) {
        return false;
    }

    const auto written = zip_decompress(xspan<const uint8_t>((const uint8_t*)src, compressed_size),
      xspan<uint8_t>((uint8_t*)dst, (size_t)expected_raw_size));
    return written && *written == (size_t)expected_raw_size;
}

bool svx::is_container(vfs::reader reader, int offset) {
    file_header hdr = {};
    return peek_file_header(reader, offset, hdr);
}

svx::e_scan_result svx::scan(vfs::reader reader, int offset, scan_header &hdr_out, section_list &out) {
    out.clear();
    hdr_out = {};

    file_header hdr = {};
    if (!peek_file_header(reader, offset, hdr)) {
        return SCAN_NOT_CONTAINER;
    }

    // A future revision may grow the section header or the epilog; we read the part
    // we know and step over the rest. Smaller than what we know means the file was
    // written by something that is not us.
    if (hdr.section_header_size < sizeof(section_header) || hdr.epilog_size < sizeof(section_epilog)) {
        logs::error("svx: bad section layout in header (hdr=%u epilog=%u)",
                    hdr.section_header_size, hdr.epilog_size);
        return SCAN_CORRUPT;
    }

    hdr_out.container_rev = hdr.container_rev;
    hdr_out.save_data_version = hdr.save_data_version;

    const int64_t file_size = reader->size();
    const int64_t shdr_size = hdr.section_header_size;
    const int64_t epilog_size = hdr.epilog_size;

    int64_t pos = (int64_t)offset + (int64_t)sizeof(file_header);

    while (pos < file_size) {
        // every bound is checked before the seek: reader_base::seek() treats an
        // out-of-range position as a fatal verify_no_crash, not as an error return
        if (pos + shdr_size > file_size) {
            logs::error("svx: truncated section header at offset %d", (int)pos);
            return SCAN_CORRUPT;
        }

        reader->seek((int)pos);
        section_header sh;
        reader->r(&sh, sizeof(sh));

        const int64_t payload_at = pos + shdr_size;
        const int64_t epilog_at = payload_at + (int64_t)sh.payload_size;
        if (epilog_at + epilog_size > file_size) {
            logs::error("svx: section [%.*s] at %d claims %u payload bytes, past end of file (%d)",
                        NAME_LEN, sh.name, (int)pos, sh.payload_size, (int)file_size);
            return SCAN_CORRUPT;
        }

        reader->seek((int)epilog_at);
        section_epilog ep;
        reader->r(&ep, sizeof(ep));

        if (ep.mark_begin != EPILOG_MARK || ep.mark_end != EPILOG_MARK
            || memcmp(ep.name, sh.name, NAME_LEN) != 0) {
            logs::error("svx: section [%.*s] at %d has a broken epilog", NAME_LEN, sh.name, (int)pos);
            return SCAN_CORRUPT;
        }

        if (out.size() >= MAX_SECTIONS) {
            logs::error("svx: more than %u sections, refusing to index further", (uint32_t)MAX_SECTIONS);
            return SCAN_CORRUPT;
        }

        section_info info;
        memcpy(info.name, sh.name, NAME_LEN);
        info.name[NAME_LEN] = '\0';
        info.payload_offset = (uint32_t)payload_at;
        info.payload_size = sh.payload_size;
        info.raw_size = sh.raw_size;
        info.crc = sh.crc;

        // peek the compression prefix so tooling can show it without decompressing
        if (sh.payload_size >= sizeof(uint32_t)) {
            reader->seek((int)payload_at);
            uint32_t prefix = 0;
            reader->r(&prefix, sizeof(prefix));
            info.compressed = (prefix != PAYLOAD_UNCOMPRESSED);
        }

        out.push_back(info);

        pos = epilog_at + epilog_size;
    }

    if (hdr.section_count != out.size()) {
        // the scan wins - the count is only a hint, and a file appended to by an
        // external tool is still perfectly readable
        logs::warn("svx: header says %u sections, found %u", hdr.section_count, (uint32_t)out.size());
    }

    return SCAN_OK;
}

bool svx::byte_sink::write(const void* data, size_t size) {
    if (size == 0) {
        return true;
    }
    if (bytes) {
        const uint8_t* p = (const uint8_t*)data;
        bytes->insert(bytes->end(), p, p + size);
        return true;
    }
    return fp && fwrite(data, 1, size, fp) == size;
}

bool svx::write_file_header(byte_sink& out, uint32_t save_data_version, uint32_t section_count, pcstr debug_path) {
    file_header hdr = {};
    memcpy(hdr.magic, MAGIC, sizeof(hdr.magic));
    hdr.container_rev = CONTAINER_REV;
    hdr.save_data_version = save_data_version;
    hdr.section_count = section_count;
    hdr.section_header_size = (uint16_t)sizeof(section_header);
    hdr.epilog_size = (uint16_t)sizeof(section_epilog);

    if (!out.write(&hdr, sizeof(hdr))) {
        logs::error("Unable to write file [%s], container header write failed.", debug_path);
        return false;
    }
    return true;
}

bool svx::write_section(byte_sink& out, pcstr name, const prefixed_payload& payload, uint32_t raw_size, uint32_t crc,
  int index, pcstr debug_path) {
    section_header sh = {};
    const size_t name_len = name ? ::strlen(name) : 0;
    if (name_len > 0) {
        memcpy(sh.name, name, (name_len < NAME_LEN) ? name_len : NAME_LEN);
    }
    sh.payload_size = (uint32_t)sizeof(payload.prefix) + payload.body_size;
    sh.raw_size = raw_size;
    sh.crc = crc;

    section_epilog ep = {};
    ep.mark_begin = EPILOG_MARK;
    ep.mark_end = EPILOG_MARK;
    memcpy(ep.name, sh.name, NAME_LEN);

    const bool ok = out.write(&sh, sizeof(sh)) && out.write(&payload.prefix, sizeof(payload.prefix))
                    && out.write(payload.body, payload.body_size) && out.write(&ep, sizeof(ep));

    if (!ok) {
        logs::error("Unable to write file [%s], write failure at section %d (%s).",
                    debug_path, index, name ? name : "");
        return false;
    }
    return true;
}
