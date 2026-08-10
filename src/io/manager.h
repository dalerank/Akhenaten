#pragma once

#include "core/buffer.h"
#include "content/vfs.h"
#include "content/file_formats.h"
#include "io/io_buffer.h"
#include "io/chunk_container.h"
#include "core/hvector.h"

struct file_chunk_t {
    bool VALID = false;
    // was this chunk actually found in the file we are loading? sectioned files may
    // legitimately lack a chunk (the save predates it); the legacy reader sets this
    // for everything, since there a chunk is always at its fixed position
    bool present = false;
    buffer* buf = nullptr;
    io_buffer* iob = nullptr;
    int compressed = 0;
    char name[svx::NAME_LEN + 1] = "";

    // Reallocating the buffer invalidates the pointer the io_buffer cached in hook(),
    // so the two must never be done separately - this is the only place chunk.buf is
    // allowed to change.
    void resize(int new_size);
};

// Robust class system needed for reading/writing savestate files.
// - contains an internal collection of file pieces that are format-agnostic
// - each file piece has a BUFFER, game state is read from/writes into these
// - file contents differ between formats, so the manager needs a mapping SCHEMA
// - schemas define the arrangement of data CHUNKS inside the file
// - schemas can be assigned without reading a file, to prepare for file saving
// - upon reading a file, the manager will:
//      > open the file handle with the specified offset
//      > read the file's version header
//      > detect the proper schema automatically from the header
//      > initialize the file chunks (io_buffer) in the proper order,
//        as well as their internal memory buffer, and set up extra info
//        (e.g. size, compressed flag, name for debugging)
//      > read the file contents into the chunk cache (io_buffer sequence)
//      > close the file handle
//      > load the GAME STATE into the engine from the chunk cache

class FileIOManager {
private:
    bool loaded = false;
    vfs::path file_path = "";
    int file_size = 0;
    int file_offset = 0;

    e_file_format file_format = FILE_FORMAT_NULL;
    int file_version;

    hvector<file_chunk_t, 160> file_chunks;
    int alloc_index = 0;
    bool file_sectioned = false;

    void clear();
    bool io_failure_cleanup(const char* action, const char* reason); // because I'm anal about reusing code...

    bool serialize_sectioned(FILE* fp, pcstr debug_path);
    bool unserialize_sectioned(vfs::reader reader, void (*init_schema)(e_file_format _format, const int _version));
    bool unserialize_legacy(vfs::reader reader, const int (*determine_file_version)(pcstr _filename, int _offset),
                            void (*init_schema)(e_file_format _format, const int _version));
public:
    // push parametric chunk onto the schema
    buffer* push_chunk(int size, bool compressed, const char* name, io_buffer* iob);

    const int num_chunks();
    const int get_file_version() {
        return file_version;
    }
    const e_file_format get_file_format() {
        return file_format;
    }
    // is the file being read/written a sectioned container? the schema needs this:
    // the legacy .svx layout carries two dead chunks that the container drops
    bool is_sectioned() const {
        return file_sectioned;
    }

    // write/read internal chunk cache (io_buffer sequence) to/from disk file
    bool serialize(pcstr filename, int offset, e_file_format format, const int version, void (*init_schema)(e_file_format _format, const int _version));
    bool unserialize(vfs::reader filename, int offset, e_file_format format, const int (*determine_file_version)(pcstr _filename, int _offset),
                     void (*init_schema)(e_file_format _format, const int _version));
};

extern FileIOManager FILEIO;
