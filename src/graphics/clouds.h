#pragma once

#include <core/speed.h>
#include <graphics/image.h>
#include <graphics/painter.h>

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

struct cloud_t {
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

struct clouds_t {
    struct ellipse {
        vec2i pos;
        int width;
        int height;
        int half_width;
        int half_height;
        int radius;
        int squared_width;
        int squared_height;
        int width_times_height;
    };

    struct config_t {
        int num_cloud_ellipses = 180;
        int cloud_alpha_increase = 16;
        int cloud_columns = 4;
        int cloud_rows = 4;
        int cloud_width = 64;
        int cloud_height = 64;
        float cloud_size_ratio = 0.05;
        int cloud_scale = 12;
        int cloud_min_creation_timeout = 200;
        int cloud_max_creation_timeout = 2400;
        int pause_min_frames = 2;

        int num_clouds() const { return cloud_rows * cloud_columns; }
        int cloud_texture_width() const { return cloud_width * cloud_columns; }
        int cloud_texture_height() const { return cloud_height * cloud_rows; }
    } config;

    std::vector<cloud_t> clouds;
    std::vector<atlas_data_t> atlas_pages;

    int movement_timeout = 0;
    int pause_frames = 0;
    float clouds_speed = CLOUDS_SPEED_DEFAULT;
    
    void init_cloud_images();
    bool cloud_intersects(const cloud_t& cloud);
    void position_cloud(cloud_t& cloud, const vec2i min_pos, const vec2i limit);
    void pause();
    void draw_cloud(painter &ctx, const image_t *img, const vec2i pos, const color color, const float scale_x, const float scale_y, const double angle);
    void draw(painter &ctx, const vec2i min_pos, const vec2i offset, const vec2i limit);
    void generate_cloud(cloud_t &cloud);
    int ellipse_is_inside_bounds(const ellipse &e);
    void generate_cloud_ellipse(color *pixels, const int width, const  int height);
    void position_ellipse(ellipse &e, const int cloud_width, const int cloud_height);
};
ANK_CONFIG_STRUCT(clouds_t::config_t, num_cloud_ellipses, cloud_alpha_increase, cloud_columns, 
    cloud_rows, cloud_width, cloud_height, cloud_size_ratio, cloud_scale)

extern clouds_t g_clouds;