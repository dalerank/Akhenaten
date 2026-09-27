#include "chunk_serializer.h"
#include "core/string.h"
#include "core/log.h"
#include "core/crc32.h"
#include "core/profiler.h"
#include "io/gamestate/boilerplate.h"
#include "platform/platform.h"

#include <cassert>
#include <cinttypes>
#include <string.h>

#include "SDL.h"

#ifdef _WIN32
#ifdef _WIN64
#define PRI_SIZET PRIu64
#else
#define PRI_SIZET PRIu32
#endif
#else
#define PRI_SIZET "zu"
#endif

ChunkSerializer g_chunk_io;

void file_chunk_t::resize(int new_size) {
    safe_realloc_for_size(&buf, new_size);
    if (iob != nullptr) {
        iob->hook(buf, new_size, compressed != 0, name);
    }
}

void ChunkSerializer::clear() {
    loaded = false;
    strncpy_safe(file_path, "", MAX_FILE_NAME);
    file_size = 0;
    file_offset = 0;
    file_format = FILE_FORMAT_NULL;
    file_version = -1;
    file_sectioned = false;
    for (int i = 0; i < num_chunks(); ++i) {
        file_chunks.at(i).VALID = false;
        file_chunks.at(i).present = false;
    }
    alloc_index = 0;
}

buffer* ChunkSerializer::push_chunk(int size, bool compressed, const char* name, io_buffer* iob) {
    if (alloc_index >= file_chunks.size())
        file_chunks.push_back(file_chunk_t());

    file_chunk_t& chunk = file_chunks.at(alloc_index);
    chunk.compressed = compressed;
    chunk.present = false;
    chunk.iob = iob;
    chunk.VALID = (iob != nullptr);

    if (::strlen(name) > svx::NAME_LEN) {
        logs::error("chunk name [%s] is longer than %d chars and will not fit a section header",
                    name, svx::NAME_LEN);
        assert(false);
    }
    strncpy_safe(chunk.name, name, sizeof(chunk.name));

    chunk.resize(size);

    alloc_index++;
    return chunk.buf;
}
const int ChunkSerializer::num_chunks() {
    return alloc_index;
}

static char compress_buffer[svx::CODEC_SCRATCH_SIZE];

bool ChunkSerializer::read_compressed_chunk(vfs::reader reader, buffer* buf, int filepiece_size) {
    if (filepiece_size > svx::CODEC_SCRATCH_SIZE)
        return false;

    uint32_t prefix = 0;
    reader->r(&prefix, 4);

    if (prefix == svx::PAYLOAD_UNCOMPRESSED) {
        return buf->from_file(filepiece_size, reader) == filepiece_size;
    }

    if (prefix > svx::CODEC_SCRATCH_SIZE)
        return false;

    reader->r((void*)compress_buffer, (int)prefix);
    return svx::decompress_prefixed(compress_buffer, prefix, buf->data_unsafe_pls_use_carefully(), filepiece_size);
}

bool ChunkSerializer::write_compressed_chunk(FILE* fp, buffer* buf, int bytes_to_write) {
    if (bytes_to_write > svx::CODEC_SCRATCH_SIZE)
        return false;

    svx::prefixed_payload payload;
    svx::compress_prefixed(buf->get_data(), (uint32_t)bytes_to_write, true,
                           compress_buffer, svx::CODEC_SCRATCH_SIZE, &payload);

    fwrite(&payload.prefix, 4, 1, fp);
    fwrite(payload.body, 1, payload.body_size, fp);
    return true;
}

bool ChunkSerializer::read_section_payload(vfs::reader reader, const svx::section_info& info, buffer* buf, pcstr debug_path) {
    if (info.raw_size > (uint32_t)svx::CODEC_SCRATCH_SIZE || (int)info.raw_size > buf->size()) {
        logs::error("Unable to read file [%s], section [%s] raw size %u does not fit.",
                    debug_path, info.name, info.raw_size);
        return false;
    }

    reader->seek((int)info.payload_offset);

    uint32_t prefix = 0;
    reader->r(&prefix, sizeof(prefix));

    if (prefix == svx::PAYLOAD_UNCOMPRESSED) {
        if (buf->from_file(info.raw_size, reader) != info.raw_size) {
            logs::error("Unable to read file [%s], section [%s] short read.", debug_path, info.name);
            return false;
        }
    } else {
        if (prefix > (uint32_t)svx::CODEC_SCRATCH_SIZE || prefix > info.payload_size) {
            logs::error("Unable to read file [%s], section [%s] bad compressed size %u.",
                        debug_path, info.name, prefix);
            return false;
        }
        reader->r((void*)compress_buffer, (int)prefix);
        if (!svx::decompress_prefixed(compress_buffer, prefix, buf->data_unsafe_pls_use_carefully(), (int)info.raw_size)) {
            logs::error("Unable to read file [%s], section [%s] decompressed size mismatch (expected %u).",
                        debug_path, info.name, info.raw_size);
            return false;
        }
    }

    const uint32_t actual = crc32(buf->get_data(), info.raw_size);
    if (actual != info.crc) {
        logs::error("Unable to read file [%s], section [%s] is corrupt (crc %08x, expected %08x).",
                    debug_path, info.name, actual, info.crc);
        return false;
    }

    return true;
}

bool ChunkSerializer::io_failure_cleanup(const char* action, const char* reason) {
    const char* format = "Unable to %s file, %s.";
    size_t size_f = strlen(format);
    size_t size_a = strlen(action);
    size_t size_r = strlen(reason);
    int size = size_f + size_a + size_r - 4 + 1; // remove the size of the format characters, add one character for string termination
    std::vector<char> text(size);
    snprintf(text.data(), size, format, action, reason);
    logs::error(text.data());
    clear();
    return false;
}

bool ChunkSerializer::serialize(pcstr filename, int offset, e_file_format format, const int version, void (*init_schema)(e_file_format _format, const int _version)) {
    clear();
    file_path = filename;
    file_offset = offset;
    file_format = format;
    file_version = version;

    // open file handle
    vfs::path fs_path = vfs::path(file_path).resolve();
    if (fs_path.empty()) {
        fs_path = file_path;
    }

    file_sectioned = (file_format == FILE_FORMAT_SAVE_FILE_EXT);

    // Android SAF paths are not real filesystem paths — POSIX rename() cannot publish .tmp → final.
    const bool atomic_write = !platform.is_android() && (file_offset == 0);
    const vfs::path write_path = atomic_write ? vfs::path(fs_path.c_str(), ".tmp") : fs_path;

    FILE* fp = vfs::file_open_os(write_path, "wb");
    if (!fp) {
        logs::error("Unable to write file [%s], file could not be accessed.", write_path.c_str());
        clear();
        return false;
    } else if (file_offset) {
        fseek(fp, file_offset, SEEK_SET);
    }

    auto abort_write = [&] {
        vfs::file_close_os(fp);
        if (atomic_write) {
            vfs::file_remove(write_path);
        }
        clear();
    };

    if (init_schema != nullptr) {
        init_schema(file_format, file_version);
    } else {
        logs::error("Unable to write file [%s], provided schema is invalid.", fs_path.c_str());
        abort_write();
        return false;
    }

    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->write();
    }

    if (file_sectioned) {
        if (!serialize_sectioned(fp, fs_path.c_str())) {
            abort_write();
            return false;
        }
    } else {
        for (int i = 0; i < num_chunks(); i++) {
            file_chunk_t* chunk = &file_chunks.at(i);

            int result = 0;
            if (chunk->compressed) {
                result = write_compressed_chunk(fp, chunk->buf, chunk->buf->size());
            } else {
                result = chunk->buf->to_file(chunk->buf->size(), fp);
            }

            // The last piece may be smaller than buf->size
            if (!result) {
                logs::error("Unable to write file [%s], write failure at chunk %d (%s).",
                            fs_path.c_str(), i, chunk->name);
                abort_write();
                return false;
            }
        }
    }

    vfs::file_close_os(fp);
    if (atomic_write && !vfs::file_rename_os(write_path, fs_path)) {
        logs::error("Unable to write file [%s], could not replace it with [%s].",
                    fs_path.c_str(), write_path.c_str());
        vfs::file_remove(write_path);
        clear();
        return false;
    }

    vfs::sync_em_fs();

    logs::info("File write successful: %s %i@ --- VERSION: %i ---", file_path.c_str(),
               file_offset,
               file_version);

    return true;
}

bool ChunkSerializer::build_svx_section_payload(const file_chunk_t* chunk, int index, pcstr debug_path,
                                              svx::prefixed_payload* out, uint32_t* out_raw_size, uint32_t* out_crc) {
    if (!chunk->VALID) {
        // a chunk without an io_buffer has no state to write and no name to look
        // it up by later; the .svx schema never pushes one
        logs::error("Unable to write file [%s], chunk %d (%s) has no io_buffer.",
                    debug_path, index, chunk->name);
        return false;
    }

    const uint32_t raw_size = (uint32_t)chunk->buf->size();
    const uint8_t* raw = chunk->buf->get_data();

    if (raw_size > (uint32_t)svx::CODEC_SCRATCH_SIZE) {
        logs::error("Unable to write file [%s], chunk %d (%s) is %u bytes, over the compress buffer.",
                    debug_path, index, chunk->name, raw_size);
        return false;
    }

    svx::compress_prefixed(raw, raw_size, chunk->compressed != 0,
                           compress_buffer, svx::CODEC_SCRATCH_SIZE, out);
    *out_raw_size = raw_size;
    *out_crc = crc32(raw, raw_size);
    return true;
}

bool ChunkSerializer::write_svx_section(FILE* fp, const file_chunk_t* chunk, int index, pcstr debug_path) {
    svx::prefixed_payload payload;
    uint32_t raw_size = 0;
    uint32_t crc = 0;
    if (!build_svx_section_payload(chunk, index, debug_path, &payload, &raw_size, &crc)) {
        return false;
    }
    return svx::write_section(fp, chunk->name, payload, raw_size, crc, index, debug_path);
}

bool ChunkSerializer::serialize_sectioned(FILE* fp, pcstr debug_path) {
    if (!svx::write_file_header(fp, (uint32_t)file_version, (uint32_t)num_chunks(), debug_path)) {
        return false;
    }

    for (int i = 0; i < num_chunks(); i++) {
        if (!write_svx_section(fp, &file_chunks.at(i), i, debug_path)) {
            return false;
        }
    }
    return true;
}

const svx::section_info* ChunkSerializer::find_svx_section(const svx::section_list& sections, pcstr name, int* out_matches) {
    const svx::section_info* found = nullptr;
    int matches = 0;
    for (const auto& s : sections) {
        if (strcmp(s.name, name) == 0) {
            found = &s;
            matches++;
        }
    }
    if (out_matches) {
        *out_matches = matches;
    }
    return found;
}

bool ChunkSerializer::load_svx_chunk_payload(vfs::reader reader, file_chunk_t* chunk, const svx::section_info& info, pcstr debug_path) {
    if ((int)info.raw_size > chunk->buf->size()) {
        chunk->resize((int)info.raw_size);
    }

    if (!read_section_payload(reader, info, chunk->buf, debug_path)) {
        return false;
    }

    chunk->present = true;
    return true;
}

void ChunkSerializer::warn_unknown_svx_sections(const svx::section_list& sections) {
    for (const auto& s : sections) {
        bool known = false;
        for (int i = 0; i < num_chunks() && !known; i++) {
            known = (strcmp(s.name, file_chunks.at(i).name) == 0);
        }
        if (!known) {
            logs::warn("File [%s] has unknown section [%s] (%u bytes), skipped.",
                       file_path.c_str(), s.name, s.raw_size);
        }
    }
}

bool ChunkSerializer::apply_svx_chunk_state(file_chunk_t* chunk) {
    if (!chunk->VALID) {
        return true;
    }

    if (chunk->present) {
        chunk->iob->read(file_version);
        return true;
    }

    if (!chunk->iob->has_default()) {
        logs::error("Unable to read file [%s], required chunk [%s] is missing.",
                    file_path.c_str(), chunk->name);
        return false;
    }

    logs::info("chunk [%s] missing from [%s], defaults applied", chunk->name, file_path.c_str());
    chunk->iob->apply_default(file_version);
    return true;
}

bool ChunkSerializer::unserialize_sectioned(vfs::reader reader, void (*init_schema)(e_file_format _format, const int _version)) {
    svx::scan_header hdr = {};
    svx::section_list sections;

    const svx::e_scan_result res = svx::scan(reader, file_offset, hdr, sections);
    if (res != svx::SCAN_OK) {
        logs::error("Unable to read file [%s], container scan failed (%s).",
                    file_path.c_str(), svx::scan_result_str(res));
        clear();
        return false;
    }

    file_version = (int)hdr.save_data_version;
    file_sectioned = true;
    init_schema(file_format, file_version);

    int missing = 0;
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t* chunk = &file_chunks.at(i);
        OZZY_PROFILER_SECTION(_, chunk->name);

        int matches = 0;
        const svx::section_info* found = find_svx_section(sections, chunk->name, &matches);
        if (matches > 1) {
            logs::warn("File [%s] has section [%s] %d times, using the last.",
                       file_path.c_str(), chunk->name, matches);
        }

        if (found == nullptr) {
            chunk->present = false;
            missing++;
            continue;
        }

        if (!load_svx_chunk_payload(reader, chunk, *found, file_path.c_str())) {
            clear();
            return false;
        }
    }

    warn_unknown_svx_sections(sections);

    for (int i = 0; i < num_chunks(); ++i) {
        if (!apply_svx_chunk_state(&file_chunks.at(i))) {
            clear();
            return false;
        }
    }

    logs::info("File read successful: %s %i@ --- CONTAINER rev %u, VERSION %i, %u sections (%d missing) ---",
               file_path.c_str(), file_offset, hdr.container_rev, file_version,
               (uint32_t)sections.size(), missing);

    return true;
}

bool ChunkSerializer::unserialize(vfs::reader reader, int offset, e_file_format format,
                                const int (*determine_file_version)(pcstr fnm, int ofst),
                                void (*init_schema)(e_file_format _format, const int _version)) {
    OZZY_PROFILER_FUNCTION();

    if (!reader) {
        logs::error("Unable to read file, file could not be accessed.");
        clear();
        return false;
    }

    // first, clear up the manager data and set the new file info
    clear();
    file_path = reader->debug_info();
    file_offset = offset;
    file_format = format;

    if (init_schema == nullptr) {
        logs::error("Unable to read file [%s], provided schema is invalid.", file_path.c_str());
        clear();
        return false;
    }

    if (svx::is_container(reader, offset)) {
        return unserialize_sectioned(reader, init_schema);
    }

    return unserialize_legacy(reader, determine_file_version, init_schema);
}

bool ChunkSerializer::unserialize_legacy(vfs::reader reader,
                                       const int (*determine_file_version)(pcstr fnm, int ofst),
                                       void (*init_schema)(e_file_format _format, const int _version)) {
    reader->seek(file_offset);

    // determine file version based on provided format
    if (determine_file_version == nullptr) {
        file_version = 1;
    } else {
        file_version = determine_file_version(file_path, file_offset);
        if (file_version == -1) {
            logs::info("Unable to read file [%s], file version/format is invalid ", file_path.c_str());
            clear();
            return false;
        }
    }

     init_schema(file_format, file_version);

    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t* chunk = &file_chunks.at(i);
        OZZY_PROFILER_SECTION(_, chunk->name);

        long offs = reader->tell();

        bool result = false;
        if (chunk->compressed) {
            result = read_compressed_chunk(reader, chunk->buf, chunk->buf->size());
            if (!result) {
                logs::error("Unable to read file[%s] chunk[%s], decompression failed.", file_path.c_str(), chunk->name);
                clear();
                return false;
            }
        } else {
            int got = chunk->buf->from_file(chunk->buf->size(), reader);
            int exp = chunk->buf->size();
            result = (got == exp);
            if (!result) {
                logs::info("Incorrect buffer size, expected %i, found %i", exp, got);
                logs::error("Unable to read file [%s], chunk size incorrect.", file_path.c_str());
                clear();
                return false;
            }
        }

        // a positional file has every chunk of its schema at a fixed place, so there
        // is no such thing as a missing one here
        chunk->present = true;

        // ******** DEBUGGING ********
        //export_unzipped(chunk); // export uncompressed buffer data to zip folder
        //if (true) {
        //    log_hex(chunk, i, offs, num_chunks()); // print full chunk read log info
        //}
        // ***************************
    }

    // load GAME STATE from buffers
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID) {
            file_chunks.at(i).iob->read(file_version);
        }
    }

    logs::info("File read successful: %s %i@ --- VERSION HEADER: %i ---",
               file_path.c_str(),
               file_offset,
               file_version);

    return true;
}
