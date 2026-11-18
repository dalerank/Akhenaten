#pragma once

class io_buffer;

struct city_view_orientation_chunk {
    static constexpr const char* name = "city_view_orientation";
    static void bind_data(io_buffer* iob, size_t version);
};

struct city_view_camera_chunk {
    static constexpr const char* name = "city_view_camera";
    static void bind_data(io_buffer* iob, size_t version);
};
