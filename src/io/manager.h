#pragma once

#include "core/buffer.h"
#include "content/vfs.h"
#include "content/file_formats.h"
#include "io/io_buffer.h"

#include <vector>

struct file_chunk_t {
    bool VALID = false;
    buffer* buf = nullptr;
    io_buffer* iob = nullptr;
    int compressed;
    char name[100];
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
    char file_path[MAX_FILE_NAME] = "";
    int file_size = 0;
    int file_offset = 0;

    e_file_format file_format = FILE_FORMAT_NULL;
    int file_version;

    std::vector<file_chunk_t> file_chunks;
    int alloc_index = 0;

    void clear();
    bool io_failure_cleanup(const char* action, const char* reason); // because I'm anal about reusing code...
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

    // write/read internal chunk cache (io_buffer sequence) to/from disk file
    bool serialize(const char* filename, int offset, e_file_format format, const int version, void (*init_schema)(e_file_format _format, const int _version));
    bool unserialize(pcstr filename, int offset, e_file_format format, const int (*determine_file_version)(pcstr _filename, int _offset),
                     void (*init_schema)(e_file_format _format, const int _version));
};

extern FileIOManager FILEIO;
