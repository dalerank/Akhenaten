#pragma once

#include <core/speed.h>
#include <graphics/image.h>
#include <graphics/painter.h>

constexpr int CLOUD_ROWS = 4;
constexpr int CLOUD_COLUMNS = 4;
constexpr int NUM_CLOUDS = CLOUD_ROWS * CLOUD_COLUMNS;

enum cloud_status {
    STATUS_INACTIVE,
    STATUS_CREATED,
    STATUS_MOVING
};

struct speed {
    speed_type x;
    speed_type y;
};

struct cloud_type {
    image_t img;
    int x = 0;
    int y = 0;
    cloud_status status = STATUS_INACTIVE;
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
};

extern cloud_data g_cloud_data;

void clouds_pause();

void clouds_draw(painter &ctx, int x_offset, int y_offset, int x_limit, int y_limit);
