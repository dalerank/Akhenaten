#include "clouds.h"

#include "game/game_config.h"
#include "core/random.h"
#include "core/speed.h"
#include "game/settings.h"
#include "graphics/color.h"
#include "graphics/image.h"
#include "game/game.h"
#include "platform/renderer.h"

#include "dev/debug.h"

#include <cmath>

constexpr int NUM_CLOUD_ELLIPSES = 180;
constexpr int CLOUD_ALPHA_INCREASE = 16;

constexpr int CLOUD_WIDTH = 64;
constexpr int CLOUD_HEIGHT = 64;
constexpr float CLOUD_SIZE_RATIO = 0.05;

constexpr int CLOUD_SCALE = 12;

constexpr int CLOUD_MIN_CREATION_TIMEOUT = 200;
constexpr int CLOUD_MAX_CREATION_TIMEOUT = 2400;

constexpr int CLOUD_TEXTURE_WIDTH = (CLOUD_WIDTH * CLOUD_COLUMNS);
constexpr int CLOUD_TEXTURE_HEIGHT = (CLOUD_HEIGHT * CLOUD_ROWS);

constexpr int PAUSE_MIN_FRAMES = 2;

constexpr float PI = 3.14159265358979323846;

std::vector<atlas_data_t> atlas_pages;
cloud_data g_cloud_data;

declare_console_ref_float(cloud_speed, g_cloud_data.clouds_speed)

struct ellipse {
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
};

static int random_from_min_to_range(int min, int range)
{
    return min + random_int_between(0, range);
}

static void position_ellipse(ellipse *e, const int cloud_width, const int cloud_height)
{
    const double angle = random_fractional() * PI * 2;

    e->x = static_cast<int>(static_cast<float>(CLOUD_WIDTH) / 2 + random_fractional() * cloud_width * cos(angle));
    e->y = static_cast<int>(static_cast<float>(CLOUD_HEIGHT) / 2 + random_fractional() * cloud_height * sin(angle));

    e->width = random_from_min_to_range(static_cast<int>(CLOUD_WIDTH * CLOUD_SIZE_RATIO / 2), static_cast<int>(CLOUD_WIDTH * CLOUD_SIZE_RATIO));
    e->height = random_from_min_to_range(static_cast<int>(CLOUD_HEIGHT * CLOUD_SIZE_RATIO / 2), static_cast<int>(CLOUD_HEIGHT * CLOUD_SIZE_RATIO));

    e->half_width = e->width / 2;
    e->half_height = e->height / 2;
    e->squared_width = e->width * e->width;
    e->squared_height = e->height * e->height;

    e->width_times_height = e->squared_width * e->squared_height;
    e->radius = e->half_width > e->half_height ? e->half_width : e->half_height;
}

static int ellipse_is_inside_bounds(const ellipse *e)
{
    const int x = e->x;
    const int y = e->y;
    return x - e->width >= 0 && x + e->width < CLOUD_WIDTH &&
        y - e->height >= 0 && y + e->height < CLOUD_HEIGHT;
}

static void darken_pixel(color *pixels, const int x, const int y)
{
    const int pixel = y * CLOUD_WIDTH + x;

    color alpha = pixels[pixel] >> COLOR_BITSHIFT_ALPHA;
    const int darken = CLOUD_ALPHA_INCREASE >> (alpha >> 4);
    alpha = (alpha + ((darken * (255 - alpha)) >> 8));

    // Clamp
    if (alpha > 255) {
        alpha = 255;
    }

    pixels[pixel] = ALPHA_TRANSPARENT | (alpha << COLOR_BITSHIFT_ALPHA);
}

static void generate_cloud_ellipse(color *pixels, const int width, const  int height)
{
    ellipse e = {};
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

static void generate_cloud(cloud_type *cloud) {
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

    cloud->pos = { 0, 0 };
    cloud->scale_x = 1 / static_cast<float>((1.5 - random_fractional()) / CLOUD_SCALE);
    cloud->scale_y = 1 / static_cast<float>((1.5 - random_fractional()) / CLOUD_SCALE);
    const int scaled_width = static_cast<int>(CLOUD_WIDTH * cloud->scale_x);
    const int scaled_height = static_cast<int>(CLOUD_HEIGHT * cloud->scale_y);
    cloud->side = static_cast<int>(sqrt(scaled_width * scaled_width + scaled_height * scaled_height));
    cloud->angle = random_int_between(0, 360);
    cloud->status = e_cloud_status_created;
}

static bool cloud_intersects(const cloud_type *cloud)
{
    for (auto &i : g_cloud_data.clouds) {
        const cloud_type *other = &i;
        if (other->status != e_cloud_status_moving) {
            continue;
        }
        if (other->pos.x < cloud->pos.x + cloud->side && other->pos.x + other->side > cloud->pos.x &&
            other->pos.y < cloud->pos.y + cloud->side && other->pos.y + other->side > cloud->pos.y) {
            return true;
        }
    }
    return false;
}

static void position_cloud(cloud_type *cloud, const vec2i min_pos, const vec2i limit)
{
    const int offset_x = random_int_between(0, limit.x / 2);

    cloud->pos = { limit.x - offset_x + cloud->side - min_pos.x,
                    (limit.y - offset_x) / 2 - cloud->side - min_pos.y };

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

void draw_cloud(painter &ctx, const image_t *img, const vec2i pos, const color color, const float scale_x,
                const float scale_y, const double angle) {
    if (!img->atlas.p_atlas) {
        return;
    }

    SDL_Texture *texture = img->atlas.p_atlas->texture;
    if (!texture) {
        return;
    }

    const vec2i size = {
        img->width,
        img->height,
    };
    ctx.draw(texture, pos, img->atlas.offset, size, color, scale_x, scale_y, angle, ImgFlag_Alpha, true);
}

void clouds_draw(painter &ctx, const vec2i min_pos, const vec2i offset, const vec2i limit)
{
   if (!game_features::gameplay_draw_cloud_shadows) {
       return;
   }

    if (!graphics_renderer()->has_custom_texture(CUSTOM_IMAGE_CLOUDS)) {
        init_cloud_images();
    }

    double cloud_speed = 0;

    if (g_cloud_data.pause_frames) {
        g_cloud_data.pause_frames--;
    } else {
        cloud_speed = g_cloud_data.clouds_speed * static_cast<float>(game.game_speed) / 100;
    }

    for (auto & i : g_cloud_data.clouds) {
        cloud_type *cloud = &i;
        if (cloud->status == e_cloud_status_inactive) {
            generate_cloud(cloud);
            continue;
        }
        if (cloud->status == e_cloud_status_created) {
            if (g_cloud_data.movement_timeout > 0) {
                g_cloud_data.movement_timeout--;
            } else if (g_cloud_data.pause_frames <= 0) {
                position_cloud(cloud, min_pos, limit);
            }
            continue;
        }
        if (cloud->pos.x < -cloud->side || cloud->pos.y >= limit.y) {
            cloud->status = e_cloud_status_inactive;
            continue;
        }

        cloud->render_pos = cloud->pos - offset;

        speed_set_target(cloud->speed.x, -cloud_speed, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(cloud->speed.y, cloud_speed / 2, SPEED_CHANGE_IMMEDIATE, 1);
        // FIXME: smoothen clouds somehow, right now they are blocky
        draw_cloud(ctx, &cloud->img,
            cloud->render_pos, COLOR_MASK_NONE,
            cloud->scale_x, cloud->scale_y, cloud->angle);

        cloud->pos.x += speed_get_delta(cloud->speed.x);
        cloud->pos.y += speed_get_delta(cloud->speed.y);
    }
}
