#ifndef OZYMANDIAS_MANAGER_H
#define OZYMANDIAS_MANAGER_H

#include <vector>
#include <core/buffer.h>
#include <core/file.h>
#include "io_buffer.h"

enum { // MINOR versioning found so far
    FILE_144 = 144,
    FILE_147 = 147,
    FILE_149 = 149,
    FILE_150 = 150,
    FILE_160 = 160,
};

enum { // MAJOR versioning found so far
    FILE_MAP = 24,
    FILE_SAVESTATE = 175,
    FILE_SAVESTATE_EXP = 181
};

typedef enum {
    FILE_SCHEMA_NULL,
//    FILE_SCHEMA_SAV_147,
//    FILE_SCHEMA_SAV_160,
//    FILE_SCHEMA_SAV_149,
    FILE_SCHEMA_SAV,
    FILE_SCHEMA_MAP
} file_schema_enum_t;

typedef struct {
    int minor;
    int major;
} file_version_t;

typedef struct {
    buffer *buf = nullptr;
    io_buffer *iob = nullptr;
    int compressed;
    char name[100];
} file_chunk_t;

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
extern class FileManager {
private:
    bool loaded = false;
    char file_path[MAX_FILE_NAME] = "";
    int file_size = 0;
    int file_offset = 0;
    file_version_t file_version;
    file_schema_enum_t file_schema = FILE_SCHEMA_NULL;

    std::vector<file_chunk_t> file_chunks;

    buffer *push_chunk(int size, bool compressed, const char *name, io_buffer *iob);

public:
    void clear();
    file_version_t *get_file_version();
    const int num_chunks();

    // set up list of io_buffer chunks in correct order for specific file format read/write operations
    void init_with_schema(file_schema_enum_t mapping_schema, file_version_t version);

    // write/read internal chunk cache (io_buffer sequence) to/from disk file
    bool write_to_file(const char *filename, int offset, file_schema_enum_t mapping_schema, file_version_t version);
    bool read_from_file(const char *filename, int offset);

    // save/load game state to/from internal chunk cache (io_buffer sequence)
    void save_state();
    void load_state();

} FileIO;

file_version_t read_file_version(const char *filename, int offset);

#endif //OZYMANDIAS_MANAGER_H
