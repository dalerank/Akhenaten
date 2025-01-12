#pragma once

#include <core/speed.h>
#include <graphics/image.h>
#include <graphics/painter.h>

constexpr int CLOUD_ROWS = 4;
constexpr int CLOUD_COLUMNS = 4;
constexpr int NUM_CLOUDS = CLOUD_ROWS * CLOUD_COLUMNS;
constexpr float CLOUD_SPEED_DEFAULT = .3;

enum e_cloud_status {
    e_cloud_status_inactive,
    e_cloud_status_created,
    e_cloud_status_moving
};

struct speed {
    speed_type x;
    speed_type y;
};

struct cloud_type {
    image_t img;
    int x = 0;
    int y = 0;
    int render_x = 0;
    int render_y = 0;
    e_cloud_status status = e_cloud_status_inactive;
    speed speed = {};
    float scale_x = 1.f;
    float scale_y = 1.f;
    int side = 0;
    int angle = 0;
};

struct cloud_data {
    cloud_type clouds[NUM_CLOUDS];
    int movement_timeout = 0;
    int pause_frames = 0;
    float cloud_speed = CLOUD_SPEED_DEFAULT;
};

extern cloud_data g_cloud_data;

void clouds_pause();

void clouds_draw(painter &ctx, int x_offset, int y_offset, int x_limit, int y_limit);
