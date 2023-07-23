#include <cstring>
#include "chunks.h"
#include "io/manager.h"

static int file_version;
io_buffer *iob_file_version = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &file_version);
});
struct chunks_data_t {
    struct chunks_t {
        uint32_t compressed = 0; // 0, 1

        uint8_t unk01 = 0;
        uint16_t unk02 = 0;
        uint8_t unk03 = 0; // 0
        uint32_t unk123 = 0;

        uint32_t fields_size = 0; // 1, 4, 24, ...
        uint32_t fields_num = 0; // 1, 10, 15, 56, 51984 (???!?!!)
        uint16_t unk06 = 0; // 0
        uint16_t unk07 = 0; // 0
    } chunks[6000];
    int chunks_in_used = 0;
};

chunks_data_t g_chunks_data;

io_buffer *iob_chunks_schema = new io_buffer([](io_buffer *iob) {
    FILE *debug_file = fopen("DEV_TESTING/CHUNKS_SCHEMA.txt", "wb+");
    char temp_string[200] = "";
    iob->bind(BIND_SIGNATURE_UINT32, &g_chunks_data.chunks_in_used);
    if (debug_file) {
        sprintf(temp_string, "NUMBER OF CHUNKS: %i\n", g_chunks_data.chunks_in_used);
        fwrite(temp_string, strlen(temp_string), 1, debug_file);
    }
    for (int i = 0; i < g_chunks_data.chunks_in_used; ++i) {
        // schema chunk nums found so far:
        //    MAP: 24
        //    SAV: 175
        //    SAV (v.160+): 181
        auto chunk = &g_chunks_data.chunks[i];
        iob->bind(BIND_SIGNATURE_UINT32, &chunk->compressed);

        iob->bind(BIND_SIGNATURE_UINT8, &chunk->unk01);
        iob->bind(BIND_SIGNATURE_UINT16, &chunk->unk02);
        iob->bind(BIND_SIGNATURE_UINT8, &chunk->unk03);
//        iob->bind(BIND_SIGNATURE_UINT32, &field->unk123);

        iob->bind(BIND_SIGNATURE_UINT32, &chunk->fields_size);
        iob->bind(BIND_SIGNATURE_UINT32, &chunk->fields_num);
        iob->bind(BIND_SIGNATURE_UINT16, &chunk->unk06);
        iob->bind(BIND_SIGNATURE_UINT16, &chunk->unk07);

        if (debug_file) {
            sprintf(temp_string, "%03i: %s %6i %4i : %-5i %-6i %2i : %6i * %5i\n", i,
                    chunk->compressed ? "(C)" : "---",
                    chunk->unk06, chunk->unk07,
                    chunk->unk01, chunk->unk02, chunk->unk03,
                    chunk->fields_num, chunk->fields_size);
//            sprintf(temp_string, "%03i: %-6i %-8i %-6i %-6i %-6i\n", i,
//                    field->unk00, field->unk123, field->unk04, field->unk05, field->unk06);
            fwrite(temp_string, strlen(temp_string), 1, debug_file);
        }
    }
    fclose(debug_file);
});

io_buffer *iob_junk7a = new io_buffer(default_bind);
io_buffer *iob_junk7b = new io_buffer(default_bind);

io_buffer *iob_junk9a = new io_buffer(default_bind);
io_buffer *iob_junk9b = new io_buffer(default_bind);

#define MAX_JUNK10_FIELDS 50
struct junk10_t {
    struct {
        bool in_use = false;
        int large_data[56] = {0}; // 55 for versions < 149
        int small_data[11] = {0};
    } fields[MAX_JUNK10_FIELDS];
};

junk10_t g_junk10;
io_buffer *iob_junk10a = new io_buffer([](io_buffer *iob) {
    const int version = FILEIO.get_file_version();

    FILE *debug_file = fopen("DEV_TESTING/JUNK10.txt", "wb+");
    char temp_string[200] = "";

    for (int i = 0; i < MAX_JUNK10_FIELDS; ++i) {
        auto field = &g_junk10.fields[i];
        sprintf(temp_string, "%03i: ", i);
        fwrite(temp_string, strlen(temp_string), 1, debug_file);
        // fill ints / print debug file
        for (int j = 0; j < (version < 149 ? 55 : 56); ++j) {
            iob->bind(BIND_SIGNATURE_UINT32, &field->large_data[j]);
            switch (j) {
                case 0:
                    sprintf(temp_string, "%i ", field->large_data[j]); break;
                case 1:
                case 2:
                case 3:
                    sprintf(temp_string, "%2i ", field->large_data[j]); break;
                default:
                    sprintf(temp_string, "%4i ", field->large_data[j]); break;
            }
            fwrite(temp_string, strlen(temp_string), 1, debug_file);
        }
        // first byte is the in_use flag
        if (field->large_data[0] == 1)
            field->in_use = true;
        fwrite("\n", 1, 1, debug_file);
    }
    fclose(debug_file);
});
io_buffer *iob_junk10b = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < MAX_JUNK10_FIELDS; ++i) {
        auto field = &g_junk10.fields[i];
        // fill ints
        for (int j = 0; j < 11; ++j)
            iob->bind(BIND_SIGNATURE_UINT32, &field->small_data[j]);
    }
});
io_buffer *iob_junk10c = new io_buffer(default_bind);
io_buffer *iob_junk10d = new io_buffer(default_bind);

#define MAX_JUNK11_FIELDS 40
struct junk11_t{
    struct {
        int data[32] = {0};
    } fields[MAX_JUNK11_FIELDS];
};
junk11_t g_junk11;

io_buffer *iob_junk11 = new io_buffer([](io_buffer *iob) {

    // the first two fields are the Map Editor's cached empire map coordinates....
    // I have absolutely no idea about the need for this, or any of the rest.
    // the third field is set to "1" when "Edit objects" is active in the editor.

    FILE *debug_file = fopen("DEV_TESTING/JUNK11.txt", "wb+");
    char temp_string[200] = "";

    for (int i = 0; i < MAX_JUNK11_FIELDS; ++i) {
        auto field = &g_junk11.fields[i];
        sprintf(temp_string, "%03i: ", i);
        fwrite(temp_string, strlen(temp_string), 1, debug_file);

        // fill ints
        for (int j = 0; j < 16; ++j) {
            iob->bind(BIND_SIGNATURE_UINT16, &field->data[j]);
            sprintf(temp_string, "%4i ", field->data[j]);
            fwrite(temp_string, strlen(temp_string), 1, debug_file);
        }
        fwrite("\n", 1, 1, debug_file);
    }
    fclose(debug_file);
});

io_buffer *iob_junk14 = new io_buffer(default_bind);

io_buffer *iob_junk16 = new io_buffer(default_bind);

io_buffer *iob_junk17 = new io_buffer(default_bind);

io_buffer *iob_junk18 = new io_buffer(default_bind);

struct {
    int current_chunk = 0;
    FILE *debug_file = nullptr;
    struct {
        struct {
            int unk00;
            int unk01;
            int unk02;
            int unk03;
            int unk04;
//            int unk04a;
//            int unk04b;
//            int unk04c;
            int unk05;
        } fields[50];
    } chunks[10];
} bizarre;
static void record_bizarre_fields(io_buffer *iob, int i) {
    auto chunk = &bizarre.chunks[i];
    char temp_string[200] = "";
    sprintf(temp_string, "CHUNK %i\n", i);
    fwrite(temp_string, strlen(temp_string), 1, bizarre.debug_file);

    int fields_num = iob->get_size() / 24;
    for (int j = 0; j < fields_num; ++j) {
        auto field = chunk->fields[j];

        iob->bind(BIND_SIGNATURE_UINT32, &field.unk00);
        iob->bind(BIND_SIGNATURE_UINT32, &field.unk01);
        iob->bind(BIND_SIGNATURE_UINT32, &field.unk02);
        iob->bind(BIND_SIGNATURE_UINT32, &field.unk03);

        iob->bind(BIND_SIGNATURE_UINT32, &field.unk04);
//        iob->bind(BIND_SIGNATURE_UINT16, &field.unk04a);
//        iob->bind(BIND_SIGNATURE_INT8, &field.unk04b);
//        iob->bind(BIND_SIGNATURE_UINT8, &field.unk04c);

        iob->bind(BIND_SIGNATURE_UINT32, &field.unk05);

        sprintf(temp_string, "%02i-%02i:     %4i %4i %4i %4i  %4i  %4i\n", i, j,
                field.unk00, field.unk01, field.unk02, field.unk03,
                field.unk04,
//                field.unk04a, field.unk04b, field.unk04c,
                field.unk05);
        fwrite(temp_string, strlen(temp_string), 1, bizarre.debug_file);
    }
}
static void bizarre_ordered_fields_bind(io_buffer *iob) {
    if (iob == iob_bizarre_ordered_fields_1) {
        bizarre.current_chunk = 0;
        bizarre.debug_file = fopen("DEV_TESTING/BIZARRE.txt", "wb+");
    } else {
        bizarre.current_chunk++;
        bizarre.debug_file = fopen("DEV_TESTING/BIZARRE.txt", "ab+");
    }
    record_bizarre_fields(iob, bizarre.current_chunk);
    fclose(bizarre.debug_file);
}

io_buffer *iob_bizarre_ordered_fields_1 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_2 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_3 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_4 = new io_buffer(bizarre_ordered_fields_bind);

io_buffer *iob_junk19 = new io_buffer(default_bind);

io_buffer *iob_bizarre_ordered_fields_5 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_6 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_7 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_8 = new io_buffer(bizarre_ordered_fields_bind);
io_buffer *iob_bizarre_ordered_fields_9 = new io_buffer(bizarre_ordered_fields_bind);