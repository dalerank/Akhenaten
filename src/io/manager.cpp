#include "manager.h"
#include "core/string.h"
#include "core/log.h"
#include "core/zip.h"
#include "core/crc32.h"
#include "core/profiler.h"
#include "io/gamestate/boilerplate.h"
#include "platform/platform.h"

#include <cassert>
#include <cinttypes>
#include <string.h>

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

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

FileIOManager FILEIO;

///

void file_chunk_t::resize(int new_size) {
    // safe_realloc_for_size deletes the old buffer when the size differs, so the
    // io_buffer must be re-hooked or its cached p_buf dangles. io_buffer objects are
    // globals shared between schemas, so re-hook even when the size matches: the same
    // io_buffer may currently point at a different chunk's buffer.
    safe_realloc_for_size(&buf, new_size);
    if (iob != nullptr) {
        iob->hook(buf, new_size, compressed != 0, name);
    }
}

void FileIOManager::clear() {
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

buffer* FileIOManager::push_chunk(int size, bool compressed, const char* name, io_buffer* iob) {
    // add empty piece onto the stack if we're beyond the current capacity
    if (alloc_index >= file_chunks.size())
        file_chunks.push_back(file_chunk_t());

    // fill info
    file_chunk_t& chunk = file_chunks.at(alloc_index);
    chunk.compressed = compressed;
    // clear() only walks the previous schema's chunk count, so a shorter schema in
    // between (a map load between two save loads) leaves stale flags behind here
    chunk.present = false;
    chunk.iob = iob;
    chunk.VALID = (iob != nullptr);

    if (::strlen(name) > svx::NAME_LEN) {
        // the name is the lookup key inside a sectioned file - silently truncating it
        // would produce two chunks that collide on load
        logs::error("chunk name [%s] is longer than %d chars and will not fit a section header",
                    name, svx::NAME_LEN);
        assert(false);
    }
    strncpy_safe(chunk.name, name, sizeof(chunk.name));

    chunk.resize(size);

    // advance allocator index
    alloc_index++;

    // return linked buffer pointer so that it can be assigned for read/write access later
    return chunk.buf;
}
const int FileIOManager::num_chunks() {
    return alloc_index;
}

static char compress_buffer[COMPRESS_BUFFER_SIZE];
static bool read_compressed_chunk(vfs::reader reader, buffer* buf, int filepiece_size) {
    // check that the stream size isn't above maximum temp buffer
    if (filepiece_size > COMPRESS_BUFFER_SIZE)
        return false;

    // read 32-bit int header denoting size of compressed chunk
    uint32_t chunk_size = 0;
    reader->r(&chunk_size, 4);

    // if file signature says "uncompressed" well man, it's uncompressed. read as normal ignoring the directive
    if ((unsigned int)chunk_size == UNCOMPRESSED) {
        if (buf->from_file(filepiece_size, reader) != filepiece_size)
            return false;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        reader->r((void*)compress_buffer, chunk_size);
        // if (csize != chunk_size) {
        //     logs::info("Incorrect chunk size, expected %i, found %i", chunk_size, csize);
        //     return false;
        // }
        int bsize = zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size);
        if (bsize != buf->size()) {
            logs::info("Incorrect buffer size, expected %u, found %i", buf->size(), bsize);
            return false;
        }
        //        if (fread(compress_buffer, 1, chunk_size, fp) != chunk_size
        //            || zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(),
        //            &filepiece_size) !=
        //               buf->size())
        //            return 0;
    }
    //    buf->force_validate_unsafe_pls_use_carefully();

    return true;
}
static bool write_compressed_chunk(FILE* fp, buffer* buf, int bytes_to_write) {
    if (bytes_to_write > COMPRESS_BUFFER_SIZE)
        return false;

    int output_size = COMPRESS_BUFFER_SIZE;
    if (zip_compress(buf->get_data(), bytes_to_write, compress_buffer, &output_size)) {
        //        write_int32(fp, output_size);
        fwrite(&output_size, 4, 1, fp);
        fwrite(compress_buffer, 1, output_size, fp);
    } else {
        // unable to compress: write uncompressed
        //        write_int32(fp, UNCOMPRESSED);
        output_size = UNCOMPRESSED;
        fwrite(&output_size, 4, 1, fp);
        fwrite(buf->get_data(), 1, bytes_to_write, fp);
    }
    return true;
}

// Reads one section payload into the chunk buffer and checks it against the CRC
// recorded when it was written. The payload always carries the compression prefix,
// so the schema's compressed flag plays no part here.
static bool read_section_payload(vfs::reader reader, const svx::section_info& info, buffer* buf, pcstr debug_path) {
    if (info.raw_size > COMPRESS_BUFFER_SIZE || (int)info.raw_size > buf->size()) {
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
        if (prefix > COMPRESS_BUFFER_SIZE || prefix > info.payload_size) {
            logs::error("Unable to read file [%s], section [%s] bad compressed size %u.",
                        debug_path, info.name, prefix);
            return false;
        }
        reader->r((void*)compress_buffer, (int)prefix);
        int out_size = (int)info.raw_size;
        const int bsize = zip_decompress(compress_buffer, (int)prefix, buf->data_unsafe_pls_use_carefully(), &out_size);
        if (bsize != (int)info.raw_size) {
            logs::error("Unable to read file [%s], section [%s] decompressed to %d, expected %u.",
                        debug_path, info.name, bsize, info.raw_size);
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

bool FileIOManager::io_failure_cleanup(const char* action, const char* reason) {
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

bool FileIOManager::serialize(pcstr filename, int offset, e_file_format format, const int version, void (*init_schema)(e_file_format _format, const int _version)) {
    // first, clear up the manager data and set the new file info
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

    // only the expanded save format gets the sectioned container; .sav / .map / .pak
    // stay byte-compatible with the original game
    file_sectioned = (file_format == FILE_FORMAT_SAVE_FILE_EXT);

    const bool atomic_write = (file_offset == 0);
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
        vfs::file_close(fp);
        if (atomic_write) {
            vfs::file_remove(write_path);
        }
        clear();
    };

    // init file chunks and buffer collection
    if (init_schema != nullptr) {
        init_schema(file_format, file_version);
    } else {
        logs::error("Unable to write file [%s], provided schema is invalid.", fs_path.c_str());
        abort_write();
        return false;
    }

    // fill chunks with bound data
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->write();
    }

    // serialize chunks to disk
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

    // close file handle
    vfs::file_close(fp);

    // publish the finished file over the target in one step
    if (atomic_write && !vfs::file_rename(write_path, fs_path)) {
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

bool FileIOManager::serialize_sectioned(FILE* fp, pcstr debug_path) {
    svx::file_header hdr = {};
    memcpy(hdr.magic, svx::MAGIC, sizeof(hdr.magic));
    hdr.container_rev = svx::CONTAINER_REV;
    hdr.save_data_version = (uint32_t)file_version;
    hdr.section_count = (uint32_t)num_chunks();
    hdr.section_header_size = (uint16_t)sizeof(svx::section_header);
    hdr.epilog_size = (uint16_t)sizeof(svx::section_epilog);

    if (fwrite(&hdr, sizeof(hdr), 1, fp) != 1) {
        logs::error("Unable to write file [%s], container header write failed.", debug_path);
        return false;
    }

    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t* chunk = &file_chunks.at(i);

        if (!chunk->VALID) {
            // a chunk without an io_buffer has no state to write and no name to look
            // it up by later; the .svx schema never pushes one
            logs::error("Unable to write file [%s], chunk %d (%s) has no io_buffer.",
                        debug_path, i, chunk->name);
            return false;
        }

        const uint32_t raw_size = (uint32_t)chunk->buf->size();
        const uint8_t* raw = chunk->buf->get_data();

        if (raw_size > COMPRESS_BUFFER_SIZE) {
            logs::error("Unable to write file [%s], chunk %d (%s) is %u bytes, over the compress buffer.",
                        debug_path, i, chunk->name, raw_size);
            return false;
        }

        uint32_t prefix = svx::PAYLOAD_UNCOMPRESSED;
        const void* body = raw;
        uint32_t body_size = raw_size;

        int compressed_size = COMPRESS_BUFFER_SIZE;
        if (chunk->compressed && zip_compress(raw, (int)raw_size, compress_buffer, &compressed_size)) {
            prefix = (uint32_t)compressed_size;
            body = compress_buffer;
            body_size = (uint32_t)compressed_size;
        }

        svx::section_header sh = {};
        const size_t name_len = ::strlen(chunk->name);
        memcpy(sh.name, chunk->name, (name_len < svx::NAME_LEN) ? name_len : svx::NAME_LEN);
        sh.payload_size = (uint32_t)sizeof(prefix) + body_size;
        sh.raw_size = raw_size;
        // crc covers the uncompressed data: that keeps it meaningful across zlib
        // changes and makes it usable for diffing two saves section by section
        sh.crc = crc32(raw, raw_size);

        svx::section_epilog ep = {};
        ep.mark_begin = svx::EPILOG_MARK;
        ep.mark_end = svx::EPILOG_MARK;
        memcpy(ep.name, sh.name, svx::NAME_LEN);

        const bool ok = (fwrite(&sh, sizeof(sh), 1, fp) == 1)
                        && (fwrite(&prefix, sizeof(prefix), 1, fp) == 1)
                        && (body_size == 0 || fwrite(body, 1, body_size, fp) == body_size)
                        && (fwrite(&ep, sizeof(ep), 1, fp) == 1);

        if (!ok) {
            logs::error("Unable to write file [%s], write failure at section %d (%s).",
                        debug_path, i, chunk->name);
            return false;
        }
    }

    return true;
}

bool FileIOManager::unserialize_sectioned(vfs::reader reader, void (*init_schema)(e_file_format _format, const int _version)) {
    svx::file_header hdr = {};
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

    // locate every schema chunk by name and read it; section order in the file is
    // irrelevant, only the names matter
    int missing = 0;
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t* chunk = &file_chunks.at(i);
        OZZY_PROFILER_SECTION(_, chunk->name);

        const svx::section_info* found = nullptr;
        int matches = 0;
        for (const auto& s : sections) {
            if (strcmp(s.name, chunk->name) == 0) {
                found = &s; // a duplicated name is odd but the last one wins
                matches++;
            }
        }

        if (matches > 1) {
            logs::warn("File [%s] has section [%s] %d times, using the last.",
                       file_path.c_str(), chunk->name, matches);
        }

        if (found == nullptr) {
            chunk->present = false;
            missing++;
            continue;
        }

        // a chunk that grew since this file was written keeps its schema size and
        // reads the missing tail as zeroes; one that shrank still needs room for
        // everything the file holds
        if ((int)found->raw_size > chunk->buf->size()) {
            chunk->resize((int)found->raw_size);
        }

        if (!read_section_payload(reader, *found, chunk->buf, file_path.c_str())) {
            clear();
            return false;
        }

        chunk->present = true;
    }

    // anything in the file this build does not know about
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

    // load GAME STATE from buffers, in schema order - the file order is free, the
    // order state is applied in is not, since binds may rely on earlier chunks
    for (int i = 0; i < num_chunks(); ++i) {
        file_chunk_t* chunk = &file_chunks.at(i);
        if (!chunk->VALID) {
            continue;
        }

        if (chunk->present) {
            chunk->iob->read(file_version);
            continue;
        }

        // A defaulter is how a chunk declares itself optional: it can be absent
        // because the save predates it, and it knows how to reset its own state.
        // A chunk without one is mandatory - its absence means a damaged file, not an
        // old one, and loading on would silently produce a city missing whole systems.
        if (!chunk->iob->has_default()) {
            logs::error("Unable to read file [%s], required chunk [%s] is missing.",
                        file_path.c_str(), chunk->name);
            clear();
            return false;
        }

        logs::info("chunk [%s] missing from [%s], defaults applied", chunk->name, file_path.c_str());
        chunk->iob->apply_default(file_version);
    }

    logs::info("File read successful: %s %i@ --- CONTAINER rev %u, VERSION %i, %u sections (%d missing) ---",
               file_path.c_str(), file_offset, hdr.container_rev, file_version,
               (uint32_t)sections.size(), missing);

    return true;
}

bool FileIOManager::unserialize(vfs::reader reader, int offset, e_file_format format,
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

    // A container announces itself with its magic, and the reader already holds the
    // whole file, so the version comes straight from the header. Everything else -
    // original Pharaoh files and .svx written before this format - goes through the
    // positional reader, which reopens the file by path to sniff its version.
    svx::file_header probe = {};
    if (svx::peek_header(reader, offset, probe)) {
        return unserialize_sectioned(reader, init_schema);
    }

    return unserialize_legacy(reader, determine_file_version, init_schema);
}

bool FileIOManager::unserialize_legacy(vfs::reader reader,
                                       const int (*determine_file_version)(pcstr fnm, int ofst),
                                       void (*init_schema)(e_file_format _format, const int _version)) {
    // always rewind: this path reads chunk after chunk from wherever the cursor is,
    // and the container probe upstream has already moved it
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

    // init file chunks and buffer collection
    init_schema(file_format, file_version);

    // read file contents into buffers
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
