#include "clouds.h"

#include "config/config.h"
#include "core/random.h"
#include "core/speed.h"
#include "game/settings.h"
#include "graphics/color.h"
#include "graphics/image.h"
#include "platform/renderer.h"

#include <cmath>
#include <cstring>

#define NUM_CLOUD_ELLIPSES 180
#define CLOUD_ALPHA_INCREASE 16

#define CLOUD_WIDTH 64
#define CLOUD_HEIGHT 64
#define CLOUD_SIZE_RATIO 0.05

#define CLOUD_SCALE 12

#define CLOUD_MIN_CREATION_TIMEOUT 200
#define CLOUD_MAX_CREATION_TIMEOUT 2400

#define CLOUD_TEXTURE_WIDTH (CLOUD_WIDTH * CLOUD_COLUMNS)
#define CLOUD_TEXTURE_HEIGHT (CLOUD_HEIGHT * CLOUD_ROWS)

// #define CLOUD_SPEED 0.3
#define CLOUD_SPEED 30 //FIXME

#define PAUSE_MIN_FRAMES 2

#define PI 3.14159265358979323846

std::vector<atlas_data_t> atlas_pages;
cloud_data g_cloud_data;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int half_width;
    int half_height;
    int radius;
    int squared_width;
    int squared_height;
    int width_times_height;
} ellipse;

static int random_from_min_to_range(int min, int range)
{
    return min + random_int_between(0, range);
}

static void position_ellipse(ellipse *e, int cloud_width, int cloud_height)
{
    double angle = random_fractional() * PI * 2;

    e->x = (int) (CLOUD_WIDTH / 2 + random_fractional() * cloud_width * cos(angle));
    e->y = (int) (CLOUD_HEIGHT / 2 + random_fractional() * cloud_height * sin(angle));

    e->width = random_from_min_to_range((int) (CLOUD_WIDTH * CLOUD_SIZE_RATIO), (int) (CLOUD_WIDTH * CLOUD_SIZE_RATIO));
    e->height = random_from_min_to_range((int) (CLOUD_HEIGHT * CLOUD_SIZE_RATIO), (int) (CLOUD_HEIGHT * CLOUD_SIZE_RATIO));

    e->half_width = e->width / 2;
    e->half_height = e->height / 2;
    e->squared_width = e->width * e->width;
    e->squared_height = e->height * e->height;

    e->width_times_height = e->squared_width * e->squared_height;
    e->radius = e->half_width > e->half_height ? e->half_width : e->half_height;
}

static int ellipse_is_inside_bounds(const ellipse *e)
{
    int x = e->x;
    int y = e->y;
    return x - e->width >= 0 && x + e->width < CLOUD_WIDTH &&
        y - e->height >= 0 && y + e->height < CLOUD_HEIGHT;
}

static void darken_pixel(color *pixels, int x, int y)
{
    int pixel = y * CLOUD_WIDTH + x;

    color alpha = pixels[pixel] >> COLOR_BITSHIFT_ALPHA;
    int darken = CLOUD_ALPHA_INCREASE >> (alpha >> 4);
    alpha = (alpha + ((darken * (255 - alpha)) >> 8));

    // Clamp
    if (alpha > 255) {
        alpha = 255;
    }

    pixels[pixel] = ALPHA_TRANSPARENT | (alpha << COLOR_BITSHIFT_ALPHA);
}

static void generate_cloud_ellipse(color *pixels, int width, int height)
{
    ellipse e;
    do {
        position_ellipse(&e, width, height);
    } while (!ellipse_is_inside_bounds(&e));

    // Do the entire diameter
    for (int x = -e.width; x <= e.width; x++) {
        darken_pixel(pixels, e.x + x, e.y);
    }

    int line_width = e.width;
    int line_delta = 0;

    // Now do all four quarters at the same time, away from the diameter
    for (int y = 1; y <= e.height; y++) {
        int line_limit = line_width - (line_delta - 1);
        int squared_y = y * y;
        while (line_limit) {
            if (line_limit * line_limit * e.squared_height + squared_y * e.squared_width <= e.width_times_height) {
                break;
            }
            line_limit--;
        }
        line_delta = line_width - line_limit;
        line_width = line_limit;

        darken_pixel(pixels, e.x, e.y - y);
        darken_pixel(pixels, e.x, e.y + y);

        for (int x = 1; x <= line_width; x++) {
            darken_pixel(pixels, e.x + x, e.y - y);
            darken_pixel(pixels, e.x + x, e.y + y);
            darken_pixel(pixels, e.x - x, e.y - y);
            darken_pixel(pixels, e.x - x, e.y + y);
        }
    }
}

static void init_cloud_images()
{
    graphics_renderer()->create_custom_texture(CUSTOM_IMAGE_CLOUDS, CLOUD_TEXTURE_WIDTH, CLOUD_TEXTURE_HEIGHT);
    atlas_pages.reserve(NUM_CLOUDS);
    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloud_type *cloud = &g_cloud_data.clouds[i];
        atlas_data_t atlas_data;

        image_t *img = &cloud->img;
        img->width = CLOUD_WIDTH;
        img->height = CLOUD_HEIGHT;
        // img->atlas.id = (ATLAS_CUSTOM << IMAGE_ATLAS_BIT_OFFSET) | CUSTOM_IMAGE_CLOUDS;
        cloud->x = 0;
        cloud->y = 0;
        cloud->side = 0;
        cloud->angle = 0;
        cloud->status = e_cloud_status_inactive;
        speed_clear(cloud->speed.x);
        speed_clear(cloud->speed.y);

        atlas_data.width = img->width;
        atlas_data.height = img->height;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.texture = nullptr;

        img->atlas.index = i;
        img->atlas.offset.x = (i % CLOUD_COLUMNS) * CLOUD_WIDTH;
        img->atlas.offset.y = (i / CLOUD_COLUMNS) * CLOUD_HEIGHT;

        atlas_pages.push_back(atlas_data);
        img->atlas.p_atlas = &atlas_pages.at(i);
    }
}

// FIXME: copied from imagepak.cpp as is
static color to_argb(uint32_t c) {
    return (((c >> 24) & 0xff) << 24) | (((c & 0xff) << 16) | (((c >> 8) & 0xff) << 8) | ((c >> 16) & 0xff));
}
static int copy_to_atlas(const image_t* img) {
    int pixels_count = 0;
    const atlas_data_t *p_atlas = img->atlas.p_atlas;
    const color *pixels = img->temp_pixel_data;

    for (int y = 0; y < img->height; y++) {
        color* pixel = &p_atlas->temp_pixel_buffer[(img->atlas.offset.y + y) * p_atlas->width + img->atlas.offset.x];
        for (int x = 0; x < img->width; x++) {
            const color color = to_argb(pixels[y * img->width + x]);
            pixel[x] = color;
            pixels_count++;
        }
    }
    return pixels_count;
}

static void generate_cloud(cloud_type *cloud)
{
    color pixels[CLOUD_WIDTH * CLOUD_HEIGHT] = {};

    const int width = random_from_min_to_range(static_cast<int>((CLOUD_WIDTH * 0.15f)), static_cast<int>((CLOUD_WIDTH * 0.2f)));
    const int height = random_from_min_to_range(static_cast<int>((CLOUD_HEIGHT * 0.15f)), static_cast<int>((CLOUD_HEIGHT * 0.2f)));

    for (int i = 0; i < NUM_CLOUD_ELLIPSES; i++) {
        generate_cloud_ellipse(pixels, width, height);
    }

    const image_t *img = &cloud->img;

    graphics_renderer()->update_custom_texture_from(CUSTOM_IMAGE_CLOUDS, pixels,
        img->atlas.offset.x, img->atlas.offset.y, img->width, img->height);

    img->atlas.p_atlas->texture = graphics_renderer()->get_custom_texture(CUSTOM_IMAGE_CLOUDS);

    cloud->x = 0;
    cloud->y = 0;
    cloud->scale_x = 1 / static_cast<float>((1.5 - random_fractional()) / CLOUD_SCALE);
    cloud->scale_y = 1 / static_cast<float>((1.5 - random_fractional()) / CLOUD_SCALE);
    const int scaled_width = static_cast<int>(CLOUD_WIDTH / cloud->scale_x);
    const int scaled_height = static_cast<int>(CLOUD_HEIGHT / cloud->scale_y);
    cloud->side = static_cast<int>(sqrt(scaled_width * scaled_width + scaled_height * scaled_height));
    cloud->angle = random_int_between(0, 360);
    cloud->status = e_cloud_status_created;
}

static int cloud_intersects(const cloud_type *cloud)
{
    for (auto &i : g_cloud_data.clouds) {
        const cloud_type *other = &i;
        if (other->status != e_cloud_status_moving) {
            continue;
        }
        if (other->x < cloud->x + cloud->side && other->x + other->side > cloud->x &&
            other->y < cloud->y + cloud->side && other->y + other->side > cloud->y) {
            return 1;
        }
    }
    return 0;
}

static void position_cloud(cloud_type *cloud, int x_limit, int y_limit)
{
    int offset_x = random_int_between(0, x_limit / 2);

    cloud->x = x_limit - offset_x + cloud->side;
    cloud->y = (y_limit - offset_x) / 2 - cloud->side;

    if (!cloud_intersects(cloud)) {
        cloud->status = e_cloud_status_moving;
        speed_clear(cloud->speed.x);
        speed_clear(cloud->speed.y);
        g_cloud_data.movement_timeout = random_int_between(CLOUD_MIN_CREATION_TIMEOUT, CLOUD_MAX_CREATION_TIMEOUT);
    }
}

void clouds_pause()
{
    g_cloud_data.pause_frames = PAUSE_MIN_FRAMES;
}

// FIXME: Function created for debugging reasons
void draw_cloud(painter &ctx, const image_t *img, float x, float y, color color, float scale_x, float scale_y, double angle, int disable_coord_scaling) {
    if (!img->atlas.p_atlas) {
        return;
    }

    SDL_Texture *texture = img->atlas.p_atlas->texture;
    if (!texture) {
        return;
    }

    const vec2i pos = {
        static_cast<int>(round(x)),
        static_cast<int>(round(y)),
    };
    const vec2i size = {
        img->width,
        img->height,
    };
    ctx.draw(texture, pos, img->atlas.offset, size, color, scale_x, scale_y, ImgFlag_Alpha);
}

void clouds_draw(painter &ctx, int x_offset, int y_offset, int x_limit, int y_limit)
{
// FIXME: add configuration option
//    if (!config_get(CONFIG_UI_DRAW_CLOUD_SHADOWS)) {
//        return;
//    }

    if (!graphics_renderer()->has_custom_texture(CUSTOM_IMAGE_CLOUDS)) {
        init_cloud_images();
    }

    double cloud_speed = 0;

    if (g_cloud_data.pause_frames) {
        g_cloud_data.pause_frames--;
    } else {
        cloud_speed = CLOUD_SPEED * g_settings.game_speed / 100;
    }

    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloud_type *cloud = &g_cloud_data.clouds[i];
        if (cloud->status == e_cloud_status_inactive) {
            generate_cloud(cloud);
            continue;
        }
        if (cloud->status == e_cloud_status_created) {
            if (g_cloud_data.movement_timeout > 0) {
                g_cloud_data.movement_timeout--;
            } else {
                position_cloud(cloud, x_limit, y_limit);
            }
            continue;
        }
        if (cloud->x < -cloud->side || cloud->y >= y_limit) {
            cloud->status = e_cloud_status_inactive;
            continue;
        }

        speed_set_target(cloud->speed.x, -cloud_speed, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(cloud->speed.y, cloud_speed / 2, SPEED_CHANGE_IMMEDIATE, 1);
        x_offset = 0; y_offset = 0; // FIXME
        draw_cloud(ctx, &cloud->img,
            (cloud->x - x_offset), (cloud->y - y_offset), COLOR_MASK_NONE,
            cloud->scale_x, cloud->scale_y, cloud->angle, 1);

        cloud->x += speed_get_delta(cloud->speed.x);
        cloud->y += speed_get_delta(cloud->speed.y);
    }
}
