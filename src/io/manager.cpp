#include "manager.h"
#include <string.h>
#include <cinttypes>
#include "core/string.h"
#include "core/zip.h"
#include "io/log.h"
#include "core/stopwatch.h"

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

#include "SDL.h"

#ifdef _WIN32
#  ifdef _WIN64
#    define PRI_SIZET PRIu64
#  else
#    define PRI_SIZET PRIu32
#  endif
#else
#  define PRI_SIZET "zu"
#endif

FileIOManager FILEIO;

///

void FileIOManager::clear() {
    loaded = false;
    strncpy_safe(file_path, "", MAX_FILE_NAME);
    file_size = 0;
    file_offset = 0;
    file_format = FILE_FORMAT_NULL;
    file_version = -1;
    for (int i = 0; i < num_chunks(); ++i)
        file_chunks.at(i).VALID = false;
    alloc_index = 0;
}

buffer *FileIOManager::push_chunk(int size, bool compressed, const char *name, io_buffer *iob) {
    // add empty piece onto the stack if we're beyond the current capacity
    if (alloc_index >= file_chunks.size())
        file_chunks.push_back(file_chunk_t());

    // fill info
    auto chunk = &file_chunks.at(alloc_index);
    chunk->compressed = compressed;
    safe_realloc_for_size(&chunk->buf, size);
    strncpy(chunk->name, name, 99);

    // fill io_buffer content
    if (iob != nullptr) {
        iob->hook(chunk->buf, size, compressed, name);
        chunk->iob = iob;
        chunk->VALID = true;
    }

    // advance allocator index
    alloc_index++;

    // return linked buffer pointer so that it can be assigned for read/write access later
    return chunk->buf;
}
const int FileIOManager::num_chunks() {
    return alloc_index;
}

int findex;
char *fname;
static void export_unzipped(file_chunk_t *chunk) {
    char *lfile = (char *) malloc(200);
//    sprintf(lfile, "DEV_TESTING/zip/%03i_%i_%s", findex + 1, chunk->buf->size(), fname);
    sprintf(lfile, "DEV_TESTING/zip/%03i_%s", findex + 1, fname);
    FILE *log = fopen(lfile, "wb+");
    if (log)
        fwrite(chunk->buf->get_data(), chunk->buf->size(), 1, log);
    fclose(log);
    free(lfile);
}
static void log_hex(file_chunk_t *chunk, int i, int offs, int num_chunks) {
    // log first few bytes of the filepiece
    size_t s = chunk->buf->size() < 16 ? chunk->buf->size() : 16;
    char hexstr[40] = {0};
    for (int b = 0; b < s; b++) {
        char hexcode[3] = {0};
        uint8_t inbyte = chunk->buf->get_value(b);
        snprintf(hexcode, sizeof(hexcode)/sizeof(hexcode[0]), "%02X", inbyte);
        strncat(hexstr, hexcode, sizeof(hexcode)/sizeof(hexcode[0]) - 1);
        if ((b + 1) % 4 == 0 || (b + 1) == s)
            strncat(hexstr, " ", 2);
    }

    // Unfortunately, MSVCRT only supports C89 and thus, "zu" leads to segfault
    SDL_Log("Piece %s %03i/%i : %8i@ %-36s(%" PRI_SIZET ") %s", chunk->compressed ? "(C)" : "---", i + 1, num_chunks,
            offs, hexstr, chunk->buf->size(), fname);
}

static char compress_buffer[COMPRESS_BUFFER_SIZE];
static bool read_compressed_chunk(FILE *fp, buffer *buf, int filepiece_size) {
    // check that the stream size isn't above maximum temp buffer
    if (filepiece_size > COMPRESS_BUFFER_SIZE)
        return false;

    // read 32-bit int header denoting size of compressed chunk
    uint32_t chunk_size = 0;
    fread(&chunk_size, 4, 1, fp);

    // if file signature says "uncompressed" well man, it's uncompressed. read as normal ignoring the directive
    if ((unsigned int) chunk_size == UNCOMPRESSED) {
        if (buf->from_file(filepiece_size, fp) != filepiece_size)
            return false;
    } else {
        // read into buffer chunk of specified size - the actual "file piece" size is used for the output!
        int csize = fread(compress_buffer, 1, chunk_size, fp);
        if (csize != chunk_size) {
            SDL_Log("Incorrect chunk size, expected %i, found %i", chunk_size, csize);
            return false;
        }
        int bsize = zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size);
        if (bsize != buf->size()) {
            SDL_Log("Incorrect buffer size, expected %i, found %i", buf->size(), bsize);
            return false;
        }
//        if (fread(compress_buffer, 1, chunk_size, fp) != chunk_size
//            || zip_decompress(compress_buffer, chunk_size, buf->data_unsafe_pls_use_carefully(), &filepiece_size) !=
//               buf->size())
//            return 0;
    }
//    buf->force_validate_unsafe_pls_use_carefully();

    return true;
}
static bool write_compressed_chunk(FILE *fp, buffer *buf, int bytes_to_write) {
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

static stopwatch WATCH;

bool FileIOManager::io_failure_cleanup(const char *action, const char *reason) {
    const char *format = "Unable to %s file, %s.";
    int size_f = strlen(format);
    int size_a = strlen(action);
    int size_r = strlen(reason);
    int size = size_f + size_a + size_r - 4 + 1; // remove the size of the format characters, add one character for string termination
    char text[size];
    snprintf(text, size, format, action, reason);
    log_error(text, 0, 0);
    clear();
    return false;
}
bool FileIOManager::serialize(const char *filename, int offset, file_format_t format, const int version,
                              void(*init_schema)(file_format_t _format, const int _version)) {

    WATCH.START();

    // first, clear up the manager data and set the new file info
    clear();
    strncpy_safe(file_path, filename, MAX_FILE_NAME);
    file_offset = offset;
    file_format = format;
    file_version = version;

    // open file handle
    FILE *fp = file_open(dir_get_file(file_path, NOT_LOCALIZED), "wb");
    if (!fp)
        return io_failure_cleanup("write", "file could not be accessed");
    else if (file_offset)
        fseek(fp, file_offset, SEEK_SET);

    // init file chunks and buffer collection
    if (init_schema != nullptr)
        init_schema(file_format, file_version);
    else
        return io_failure_cleanup("write", "provided schema is invalid");

    // fill chunks with bound data
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->write();
    }

    // serialize chunks to disk
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t *chunk = &file_chunks.at(i);

        int result = 0;
        if (chunk->compressed)
            result = write_compressed_chunk(fp, chunk->buf, chunk->buf->size());
        else
            result = chunk->buf->to_file(chunk->buf->size(), fp);

        // The last piece may be smaller than buf->size
        if (!result) {
            log_error("Unable to write file, write failure.", 0, 0);
            goto failure;
        }
    }

    // close file handle
    file_close(fp);

    SDL_Log("File write successful: %s %i@ --- VERSION: %i --- %" PRIu64 " milliseconds",
            file_path,
            file_offset,
            file_version,
            WATCH.STOP());

    return true;

failure:
    clear();
    return false;
}
bool FileIOManager::unserialize(const char *filename, int offset, file_format_t format,
                                const int(*determine_file_version)(const char *fnm, int ofst),
                                void(*init_schema)(file_format_t _format, const int _version)) {

    WATCH.START();

    // first, clear up the manager data and set the new file info
    clear();
    strncpy_safe(file_path, filename, MAX_FILE_NAME);
    file_offset = offset;
    file_format = format;

    // open file handle
    FILE *fp = file_open(dir_get_file(file_path, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to read file, file could not be accessed.", 0, 0);
        goto failure;
    } else if (file_offset)
        fseek(fp, file_offset, SEEK_SET);

    // determine file version based on provided format
    if (determine_file_version == nullptr)
        file_version = 1;
    else {
        file_version = determine_file_version(file_path, offset);
        if (file_version == -1) {
            log_info("Unable to read file, file version/format is invalid.", filename, 0);
            goto failure;
        }
    }

    // init file chunks and buffer collection
    if (init_schema != nullptr)
        init_schema(file_format, file_version);
    else {
        log_error("Unable to read file, provided schema is invalid.", 0, 0);
        goto failure;
    }

    // read file contents into buffers
    for (int i = 0; i < num_chunks(); i++) {
        file_chunk_t *chunk = &file_chunks.at(i);
        findex = i;
        fname = chunk->name;

        auto offs = ftell(fp);

        bool result = false;
        if (chunk->compressed) {
            result = read_compressed_chunk(fp, chunk->buf, chunk->buf->size());
            if (!result) {
                log_error("Unable to read file, decompression failed.", 0, 0);
                goto failure;
            }
        } else {
            int got = chunk->buf->from_file(chunk->buf->size(), fp);
            int exp = chunk->buf->size();
            result = got == exp;
            if (!result) {
                SDL_Log("Incorrect buffer size, expected %i, found %i", exp, got);
                log_error("Unable to read file, chunk size incorrect.", 0, 0);
                goto failure;
            }
        }

        // ******** DEBUGGING ********
        export_unzipped(chunk); // export uncompressed buffer data to zip folder
        if (true) log_hex(chunk, i, offs, num_chunks()); // print full chunk read log info
        // ***************************
    }

    // close file handle
    file_close(fp);

    // load GAME STATE from buffers
    for (int i = 0; i < num_chunks(); ++i) {
        if (file_chunks.at(i).VALID)
            file_chunks.at(i).iob->read();
    }

    SDL_Log("File read successful: %s %i@ --- VERSION HEADER: %i --- %" PRIu64 " milliseconds",
            file_path,
            file_offset,
            file_version,
            WATCH.STOP());

    return true;

failure:
    clear();
    return false;
}