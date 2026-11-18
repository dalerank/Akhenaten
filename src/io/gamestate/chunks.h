#pragma once

class io_buffer;

struct file_version_chunk {
    static constexpr const char* name = "file_version";
    static void bind_data(io_buffer* iob, size_t version);
};

struct chunks_schema_chunk {
    static constexpr const char* name = "chunks_schema";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk7a_chunk {
    static constexpr const char* name = "junk7a";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk7b_chunk {
    static constexpr const char* name = "junk7b";
};

struct junk9a_chunk {
    static constexpr const char* name = "junk9a";
};

struct junk9b_chunk {
    static constexpr const char* name = "junk9b";
};

struct junk10a_chunk {
    static constexpr const char* name = "junk10a";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk10b_chunk {
    static constexpr const char* name = "junk10b";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk10c_chunk {
    static constexpr const char* name = "junk10c";
};

struct junk10d_chunk {
    static constexpr const char* name = "junk10d";
};

struct junk11_chunk {
    static constexpr const char* name = "junk11";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk14_chunk {
    static constexpr const char* name = "junk14";
};

struct junk16_chunk {
    static constexpr const char* name = "junk16";
};

struct junk17_chunk {
    static constexpr const char* name = "junk17";
};

struct junk18_chunk {
    static constexpr const char* name = "junk18";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_1_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_1";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_2_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_2";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_3_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_3";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_4_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_4";
    static void bind_data(io_buffer* iob, size_t version);
};

struct junk19_chunk {
    static constexpr const char* name = "junk19";
};

struct bizarre_ordered_fields_5_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_5";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_6_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_6";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_7_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_7";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_8_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_8";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bizarre_ordered_fields_9_chunk {
    static constexpr const char* name = "bizarre_ordered_fields_9";
    static void bind_data(io_buffer* iob, size_t version);
};
