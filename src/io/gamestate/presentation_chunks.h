#pragma once

#include <cstddef>

class io_buffer;

struct city_view_orientation_chunk {
    static constexpr const char* name = "city_view_orientation";
    static void bind_data(io_buffer* iob);
};

struct city_view_camera_chunk {
    static constexpr const char* name = "city_view_camera";
    static void bind_data(io_buffer* iob);
};

struct city_sounds_chunk {
    static constexpr const char* name = "city_sounds";
    static void bind_data(io_buffer* iob);
};

struct mods_chunk {
    static constexpr const char* name = "mods";
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};

struct clouds_chunk {
    static constexpr const char* name = "clouds";
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};
