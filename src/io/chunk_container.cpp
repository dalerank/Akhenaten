#include "chunk_container.h"

#include "core/log.h"

#include <cstring>

namespace svx {

pcstr scan_result_str(e_scan_result r) {
    switch (r) {
    case SCAN_OK: return "ok";
    case SCAN_NOT_CONTAINER: return "not a container";
    case SCAN_CORRUPT: return "corrupt";
    }
    return "?";
}

bool peek_header(vfs::reader reader, int offset, file_header &out) {
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

e_scan_result scan(vfs::reader reader, int offset, file_header &hdr, section_list &out) {
    out.clear();

    if (!peek_header(reader, offset, hdr)) {
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

} // namespace svx
