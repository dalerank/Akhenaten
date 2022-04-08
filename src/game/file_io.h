#ifndef GAME_FILE_IO_H
#define GAME_FILE_IO_H

#include <vector>
#include <core/buffer.h>
#include <core/file.h>

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
    buffer *buf;
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
//      > read the file version header
//      > detect the proper schema automatically
//      > initialize the file chunks in the proper order
//      > link the static FILESTATE BUFFERS to the ordered file chunks
//      > read the file content into the chunks' linked buffers
extern class FileManager {
private:
    bool loaded = false;
    char file_path[MAX_FILE_NAME] = "";
    int file_size = 0;
    int file_offset = 0;
    file_version_t file_version;
    file_schema_enum_t file_schema = FILE_SCHEMA_NULL;

    std::vector<file_chunk_t> file_chunks;

    buffer *push_chunk(int size, bool compressed, const char *name);
    bool load_file_headers();
    bool load_file_body();

public:
    void clear();
    const file_version_t *get_file_version();
    const int num_chunks();

    void init_with_schema(file_schema_enum_t mapping_schema, file_version_t version);

    bool read(const char *filename, int offset);
    bool write(const char *filename);

} FileIO;

file_version_t read_file_version(const char *filename, int offset);

bool game_file_io_read_scenario(const char *filename);
bool game_file_io_write_scenario(const char *filename);
bool game_file_io_read_saved_game(const char *filename, int offset);
bool game_file_io_write_saved_game(const char *filename);
bool game_file_io_delete_saved_game(const char *filename);

#endif // GAME_FILE_IO_H
