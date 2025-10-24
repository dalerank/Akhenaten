#include "clouds.h"

#include "game/game_config.h"
#include "core/random.h"
#include "core/speed.h"
#include "game/settings.h"
#include "graphics/color.h"
#include "graphics/image.h"
#include "game/game.h"
#include "platform/renderer.h"
#include "js/js_game.h"
#include "dev/debug.h"

#include <cmath>

clouds_t g_clouds;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_clouds_config) {
    auto &clouds_config = g_clouds.config;
    g_config_arch.r("clouds_config", clouds_config);

    g_clouds.init_cloud_images();
}

constexpr float PI = 3.14159265358979323846;

declare_console_ref_float(cloud_speed, g_clouds.clouds_speed)

static int random_from_min_to_range(int min, int range)
{
    return min + random_int_between(0, range);
}

void clouds_t::position_ellipse(ellipse &e, const int cloud_width, const int cloud_height)
{
    const double angle = random_fractional() * PI * 2;

    e.pos.x = static_cast<int>(static_cast<float>(config.cloud_width) / 2 + random_fractional() * cloud_width * cos(angle));
    e.pos.y = static_cast<int>(static_cast<float>(config.cloud_height) / 2 + random_fractional() * cloud_height * sin(angle));

    e.width = random_from_min_to_range(static_cast<int>(config.cloud_width * config.cloud_size_ratio / 2), static_cast<int>(config.cloud_width * config.cloud_size_ratio));
    e.height = random_from_min_to_range(static_cast<int>(config.cloud_height * config.cloud_size_ratio / 2), static_cast<int>(config.cloud_height * config.cloud_size_ratio));

    e.half_width = e.width / 2;
    e.half_height = e.height / 2;
    e.squared_width = e.width * e.width;
    e.squared_height = e.height * e.height;

    e.width_times_height = e.squared_width * e.squared_height;
    e.radius = e.half_width > e.half_height ? e.half_width : e.half_height;
}

int clouds_t::ellipse_is_inside_bounds(const ellipse& e) {
    const int x = e.pos.x;
    const int y = e.pos.y;
    return x - e.width >= 0 && x + e.width < config.cloud_width &&
        y - e.height >= 0 && y + e.height < config.cloud_height;
}

static void darken_pixel(const clouds_t::config_t &config, color *pixels, const int x, const int y) {
    const int pixel = y * config.cloud_width + x;

    color alpha = pixels[pixel] >> COLOR_BITSHIFT_ALPHA;
    const int darken = config.cloud_alpha_increase >> (alpha >> 4);
    alpha = (alpha + ((darken * (255 - alpha)) >> 8));

    // Clamp
    if (alpha > 255) {
        alpha = 255;
    }

    pixels[pixel] = ALPHA_TRANSPARENT | (alpha << COLOR_BITSHIFT_ALPHA);
}

void clouds_t::generate_cloud_ellipse(color *pixels, const int width, const  int height)
{
    ellipse e = {};
    do {
        position_ellipse(e, width, height);
    } while (!ellipse_is_inside_bounds(e));

    // Do the entire diameter
    for (int x = -e.width; x <= e.width; x++) {
        darken_pixel(config, pixels, e.pos.x + x, e.pos.y);
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

        darken_pixel(config, pixels, e.pos.x, e.pos.y - y);
        darken_pixel(config, pixels, e.pos.x, e.pos.y + y);

        for (int x = 1; x <= line_width; x++) {
            darken_pixel(config, pixels, e.pos.x + x, e.pos.y - y);
            darken_pixel(config, pixels, e.pos.x + x, e.pos.y + y);
            darken_pixel(config, pixels, e.pos.x - x, e.pos.y - y);
            darken_pixel(config, pixels, e.pos.x - x, e.pos.y + y);
        }
    }
}

void clouds_t::init_cloud_images() {
    clouds.resize(config.num_clouds());
    atlas_pages.resize(config.num_clouds());

    graphics_renderer()->create_custom_texture(CUSTOM_IMAGE_CLOUDS, config.cloud_texture_width(), config.cloud_texture_height());
    for (int i = 0; i < clouds.size(); i++) {
        cloud_t &cloud = clouds[i];
        atlas_data_t& atlas_data = atlas_pages[i];

        image_t *img = &cloud.img;
        img->width = config.cloud_width;
        img->height = config.cloud_height;
        speed_clear(cloud.speed.x);
        speed_clear(cloud.speed.y);

        atlas_data.width = img->width;
        atlas_data.height = img->height;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.texture = nullptr;

        img->atlas.index = i;
        img->atlas.offset.x = (i % config.cloud_columns) * config.cloud_width;
        img->atlas.offset.y = (i / config.cloud_columns) * config.cloud_height;

        img->atlas.p_atlas = &atlas_pages.at(i);
    }
}

void clouds_t::generate_cloud(cloud_t &cloud) {
    std::vector<color> pixels;
    pixels.resize(config.cloud_width * config.cloud_height);

    const int width = random_from_min_to_range(static_cast<int>((config.cloud_width * 0.15f)), static_cast<int>((config.cloud_width * 0.2f)));
    const int height = random_from_min_to_range(static_cast<int>((config.cloud_height * 0.15f)), static_cast<int>((config.cloud_height * 0.2f)));

    for (int i = 0; i < config.num_cloud_ellipses; i++) {
        generate_cloud_ellipse(pixels.data(), width, height);
    }

    const image_t *img = &cloud.img;

    graphics_renderer()->update_custom_texture_from(CUSTOM_IMAGE_CLOUDS, pixels.data(),
        img->atlas.offset.x, img->atlas.offset.y, img->width, img->height);

    img->atlas.p_atlas->texture = graphics_renderer()->get_custom_texture(CUSTOM_IMAGE_CLOUDS);

    cloud.pos = { 0, 0 };
    cloud.scale_x = 1 / static_cast<float>((1.5 - random_fractional()) / config.cloud_scale);
    cloud.scale_y = 1 / static_cast<float>((1.5 - random_fractional()) / config.cloud_scale);
    const int scaled_width = static_cast<int>(config.cloud_width * cloud.scale_x);
    const int scaled_height = static_cast<int>(config.cloud_height * cloud.scale_y);
    cloud.side = static_cast<int>(sqrt(scaled_width * scaled_width + scaled_height * scaled_height));
    cloud.angle = random_int_between(0, 360);
    cloud.status = e_cloud_status_created;
}

bool clouds_t::cloud_intersects(const cloud_t &cloud) {
    for (auto &i : clouds) {
        const cloud_t *other = &i;
        if (other->status != e_cloud_status_moving) {
            continue;
        }

        if (other->pos.x < cloud.pos.x + cloud.side && other->pos.x + other->side > cloud.pos.x &&
            other->pos.y < cloud.pos.y + cloud.side && other->pos.y + other->side > cloud.pos.y) {
            return true;
        }
    }
    return false;
}

void clouds_t::position_cloud(cloud_t &cloud, const vec2i min_pos, const vec2i limit) {
    const int offset_x = random_int_between(0, limit.x / 2);

    cloud.pos = { limit.x - offset_x + cloud.side - min_pos.x,
                    (limit.y - offset_x) / 2 - cloud.side - min_pos.y };

    if (!cloud_intersects(cloud)) {
        cloud.status = e_cloud_status_moving;
        speed_clear(cloud.speed.x);
        speed_clear(cloud.speed.y);
        movement_timeout = random_int_between(config.cloud_min_creation_timeout, config.cloud_max_creation_timeout);
    }
}

void clouds_t::pause()
{
    pause_frames = config.pause_min_frames;
}

void clouds_t::draw_cloud(painter &ctx, const image_t *img, const vec2i pos, const color color, const float scale_x, const float scale_y, const double angle) {
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

void clouds_t::draw(painter &ctx, const vec2i min_pos, const vec2i offset, const vec2i limit) {
   if (!game_features::gameplay_draw_cloud_shadows) {
       return;
   }

    if (!graphics_renderer()->has_custom_texture(CUSTOM_IMAGE_CLOUDS)) {
        init_cloud_images();
    }

    double cloud_speed = 0;

    if (pause_frames) {
        pause_frames--;
    } else {
        cloud_speed = clouds_speed * static_cast<float>(game.game_speed) / 100;
    }

    for (auto &cloud : clouds) {
        if (cloud.status == e_cloud_status_inactive) {
            generate_cloud(cloud);
            continue;
        }
        if (cloud.status == e_cloud_status_created) {
            if (movement_timeout > 0) {
                movement_timeout--;
            } else if (pause_frames <= 0) {
                position_cloud(cloud, min_pos, limit);
            }
            continue;
        }
        if (cloud.pos.x < -cloud.side || cloud.pos.y >= limit.y) {
            cloud.status = e_cloud_status_inactive;
            continue;
        }

        cloud.render_pos = cloud.pos - offset;

        speed_set_target(cloud.speed.x, -cloud_speed, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(cloud.speed.y, cloud_speed / 2, SPEED_CHANGE_IMMEDIATE, 1);
        // FIXME: smoothen clouds somehow, right now they are blocky
        draw_cloud(ctx, &cloud.img, cloud.render_pos, COLOR_MASK_NONE, cloud.scale_x, cloud.scale_y, cloud.angle);

        cloud.pos.x += speed_get_delta(cloud.speed.x);
        cloud.pos.y += speed_get_delta(cloud.speed.y);
    }
}
