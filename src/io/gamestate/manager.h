#ifndef OZYMANDIAS_MANAGER_H
#define OZYMANDIAS_MANAGER_H

#include <vector>
#include <core/buffer.h>
#include <core/file.h>
#include "io/io_buffer.h"

static const char MISSION_PACK_FILE[] = "mission1.pak";

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
    bool VALID = false;
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
class GamestateIO {
private:
    bool loaded = false;
    char file_path[MAX_FILE_NAME] = "";
    int file_size = 0;
    int file_offset = 0;
//    int file_version;
    file_schema_enum_t file_schema = FILE_SCHEMA_NULL;

    std::vector<file_chunk_t> file_chunks;
    int alloc_index = 0;

    void clear();
    buffer *push_chunk(int size, bool compressed, const char *name, io_buffer *iob);

public:
    const int num_chunks();
    static const int get_file_version();

    // set up list of io_buffer chunks in correct order for specific file format read/write operations
    void init_with_schema(file_schema_enum_t mapping_schema, int version);

    // write/read internal chunk cache (io_buffer sequence) to/from disk file
    bool write_to_file(const char *filename, int offset, file_schema_enum_t mapping_schema, const int version);
    bool read_from_file(const char *filename, int offset);

    // static boilerplate methods for use anywhere in the engine
    static bool write_mission(const int scenario_id);
    static bool write_savegame(const char *filename_short);
    static bool write_map(const char *filename_short);
    //
    static bool load_mission(const int scenario_id, bool start_immediately = true);
    static bool load_savegame(const char *filename_short, bool start_immediately = true);
    static bool load_map(const char *filename_short, bool start_immediately = true);
    //
    static void start_loaded_file();
    //
    static bool delete_mission(const int scenario_id);
    static bool delete_savegame(const char *filename_short);
    static bool delete_map(const char *filename_short);
};

const int get_campaign_scenario_offset(int scenario_id);
const int read_file_version(const char *filename, int offset);

#endif //OZYMANDIAS_MANAGER_H
