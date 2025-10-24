#pragma once

#include <core/speed.h>
#include <graphics/image.h>
#include <graphics/painter.h>

constexpr int CLOUD_ROWS = 4;
constexpr int CLOUD_COLUMNS = 4;
constexpr int NUM_CLOUDS = CLOUD_ROWS * CLOUD_COLUMNS;
constexpr float CLOUDS_SPEED_DEFAULT = .3;

enum e_cloud_status {
    e_cloud_status_inactive,
    e_cloud_status_created,
    e_cloud_status_moving
};

struct cloud_speed {
    speed_type x;
    speed_type y;
};

struct cloud_type {
    image_t img;
    vec2i pos = { 0, 0 };
    vec2i render_pos = { 0, 0 };
    e_cloud_status status = e_cloud_status_inactive;
    cloud_speed speed = {};
    float scale_x = 1.f;
    float scale_y = 1.f;
    int side = 0;
    int angle = 0;
};

struct cloud_data {
    struct config {
        int num_cloud_ellipses = 180;
    };

    std::array<cloud_type, NUM_CLOUDS> clouds;
    std::array<atlas_data_t, NUM_CLOUDS> atlas_pages;

    int movement_timeout = 0;
    int pause_frames = 0;
    float clouds_speed = CLOUDS_SPEED_DEFAULT;
    
    void init_cloud_images();
    bool cloud_intersects(const cloud_type *cloud);
    void position_cloud(cloud_type *cloud, const vec2i min_pos, const vec2i limit);
    void pause();
    void draw_cloud(painter &ctx, const image_t *img, const vec2i pos, const color color, const float scale_x, const float scale_y, const double angle);
    void draw(painter &ctx, const vec2i min_pos, const vec2i offset, const vec2i limit);
    void generate_cloud(cloud_type *cloud);
};
ANK_CONFIG_STRUCT(cloud_data::config, num_cloud_ellipses)

extern cloud_data g_clouds;