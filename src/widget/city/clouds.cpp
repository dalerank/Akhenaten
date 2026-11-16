#include "widget/city/clouds.h"

#include "core/app.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/speed.h"
#include "dev/debug.h"
#include "game/game.h"
#include "game/game_config.h"
#include "graphics/color.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "graphics/window.h"
#include "io/gamestate/chunks.h"
#include "io/io_buffer.h"
#include "js/js_game.h"
#include "platform/renderer.h"
#include "widget/widget_city.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>

clouds_t g_clouds;

e_cloud_status_tokens_t ANK_CONFIG_ENUM(e_cloud_status_tokens);

void ANK_REGISTER_CONFIG_ITERATOR(config_load_clouds_config) {
    auto &clouds_config = g_clouds.config;
    g_config_arch.r("clouds_config", clouds_config);

    g_clouds.init_cloud_images();
}

constexpr float PI = 3.14159265358979323846;

namespace {
    // Clouds change every drawn frame. libc rand() still feeds the simulation, so they must neither
    // draw from it nor reseed it (random_int() calls srand(time) once a second).
    std::minstd_rand& clouds_rng() {
        static std::minstd_rand rng((unsigned)std::time(nullptr));
        return rng;
    }

    int clouds_random_between(const int min, const int max) {
        const int diff = max - min;
        return diff > 0 ? min + (int)(clouds_rng()() % (unsigned)diff) : min;
    }

    double clouds_random_fractional() {
        auto& rng = clouds_rng();
        return double(rng() - rng.min()) / double(rng.max() - rng.min());
    }
} // namespace

static int random_from_min_to_range(int min, int range) {
    return min + clouds_random_between(0, range);
}

void clouds_t::position_ellipse(ellipse &e, const int cloud_width, const int cloud_height) {
    const double angle = clouds_random_fractional() * PI * 2;

    e.pos.x = static_cast<int>(
      static_cast<float>(config.cloud_width) / 2 + clouds_random_fractional() * cloud_width * cos(angle));
    e.pos.y = static_cast<int>(
      static_cast<float>(config.cloud_height) / 2 + clouds_random_fractional() * cloud_height * sin(angle));

    e.width = random_from_min_to_range(static_cast<int>(config.cloud_width * config.cloud_size_ratio / 2), static_cast<int>(config.cloud_width * config.cloud_size_ratio));
    e.height = random_from_min_to_range(static_cast<int>(config.cloud_height * config.cloud_size_ratio / 2), static_cast<int>(config.cloud_height * config.cloud_size_ratio));

    e.half_width = e.width / 2;
    e.half_height = e.height / 2;
    e.squared_width = e.width * e.width;
    e.squared_height = e.height * e.height;

    e.width_times_height = e.squared_width * e.squared_height;
    e.radius = e.half_width > e.half_height ? e.half_width : e.half_height;
}

int clouds_t::ellipse_is_inside_bounds(const ellipse &e) {
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

    if (alpha > 255) {
        alpha = 255;
    }

    pixels[pixel] = ALPHA_TRANSPARENT | (alpha << COLOR_BITSHIFT_ALPHA);
}

void clouds_t::generate_cloud_ellipse(color *pixels, const int width, const int height) {
    ellipse e = {};
    do {
        position_ellipse(e, width, height);
    } while (!ellipse_is_inside_bounds(e));

    for (int x = -e.width; x <= e.width; x++) {
        darken_pixel(config, pixels, e.pos.x + x, e.pos.y);
    }

    int line_width = e.width;
    int line_delta = 0;

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

    g_render.create_custom_texture(CUSTOM_IMAGE_CLOUDS, config.cloud_texture_width(), config.cloud_texture_height());
    for (int i = 0; i < clouds.size(); i++) {
        cloud_t &cloud = clouds[i];
        atlas_data_t &atlas_data = atlas_pages[i];

        image_t *img = &cloud.img;
        img->width = config.cloud_width;
        img->height = config.cloud_height;
        speed_clear(cloud.speed.x);
        speed_clear(cloud.speed.y);
        cloud.status = e_cloud_status_inactive;
        cloud.pos = {0, 0};
        cloud.render_pos = {0, 0};

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

    g_render.update_custom_texture_from(CUSTOM_IMAGE_CLOUDS, pixels.data(), img->atlas.offset.x, img->atlas.offset.y, img->width, img->height);
    img->atlas.p_atlas->texture = g_render.get_custom_texture(CUSTOM_IMAGE_CLOUDS);

    cloud.pos = {0, 0};
    cloud.scale_x = 1 / static_cast<float>((1.5 - clouds_random_fractional()) / config.cloud_scale);
    cloud.scale_y = 1 / static_cast<float>((1.5 - clouds_random_fractional()) / config.cloud_scale);
    const int scaled_width = static_cast<int>(config.cloud_width * cloud.scale_x);
    const int scaled_height = static_cast<int>(config.cloud_height * cloud.scale_y);
    cloud.side = static_cast<int>(sqrt(scaled_width * scaled_width + scaled_height * scaled_height));
    cloud.angle = clouds_random_between(0, 360);
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

void clouds_t::position_cloud(cloud_t &cloud, const vec2i offset, const vec2i view_size) {
    const int margin = std::max(cloud.side, 1);
    cloud.pos = {
      offset.x + view_size.x + clouds_random_between(0, margin),
      offset.y + clouds_random_between(-margin / 2, view_size.y),
    };

    if (!cloud_intersects(cloud)) {
        cloud.status = e_cloud_status_moving;
        speed_clear(cloud.speed.x);
        speed_clear(cloud.speed.y);
        movement_timeout = clouds_random_between(config.cloud_min_creation_timeout, config.cloud_max_creation_timeout);
    }
}

void clouds_t::pause() {
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

void clouds_t::draw(painter &ctx, const vec2i offset, const vec2i view_size) {
    if (!game_features::gameplay_draw_cloud_shadows) {
        return;
    }

    if (!g_render.has_custom_texture(CUSTOM_IMAGE_CLOUDS)) {
        init_cloud_images();
    }

    double cloud_speed = 0;

    if (pause_frames) {
        pause_frames--;
    } else {
        const float clouds_mult = static_cast<float>(calc_bound(game_features::gameopt_clouds_speed.to_int(), 0, 100)) / 100.f;
        cloud_speed = clouds_mult * static_cast<float>(game_features::gameopt_game_speed.to_int()) / 100;
    }

    for (auto &cloud : clouds) {
        if (cloud.status == e_cloud_status_inactive) {
            generate_cloud(cloud);
            continue;
        }
        if (!cloud.img.atlas.p_atlas || !cloud.img.atlas.p_atlas->texture) {
            cloud.status = e_cloud_status_inactive;
            continue;
        }
        if (cloud.status == e_cloud_status_created) {
            if (movement_timeout > 0) {
                movement_timeout--;
            } else if (pause_frames <= 0) {
                position_cloud(cloud, offset, view_size);
            }
            continue;
        }

        cloud.render_pos = cloud.pos - offset;
        if (cloud.render_pos.x < -cloud.side || cloud.render_pos.x > view_size.x + cloud.side * 3
            || cloud.render_pos.y < -cloud.side * 2 || cloud.render_pos.y >= view_size.y + cloud.side) {
            cloud.status = e_cloud_status_inactive;
            continue;
        }

        speed_set_target(cloud.speed.x, -cloud_speed, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(cloud.speed.y, cloud_speed / 2, SPEED_CHANGE_IMMEDIATE, 1);
        draw_cloud(ctx, &cloud.img, cloud.render_pos, COLOR_MASK_NONE, cloud.scale_x, cloud.scale_y, cloud.angle);

        cloud.pos.x += speed_get_delta(cloud.speed.x);
        cloud.pos.y += speed_get_delta(cloud.speed.y);
    }
}

void clouds_t::draw_debug(painter &ctx) {
    OZZY_PROFILER_FUNCTION();

    const float scale = g_zoom.get_scale();
    const int view_w = (int)(g_camera.size_pixels.x / scale) + 64;
    const int view_h = (int)(g_camera.size_pixels.y / scale) + 64;
    char str[64];
    for (int i = 0; i < (int)clouds.size(); i++) {
        const cloud_t &cloud = clouds[i];
        if (cloud.status != e_cloud_status_moving) {
            continue;
        }

        if (cloud.render_pos.x + cloud.side < -64 || cloud.render_pos.x > view_w
            || cloud.render_pos.y + cloud.side < -64 || cloud.render_pos.y > view_h) {
            continue;
        }

        const int sx = (int)(cloud.render_pos.x * scale);
        const int sy = (int)(cloud.render_pos.y * scale);
        const int sw = std::max(1, (int)(cloud.img.width * cloud.scale_x * scale));
        const int sh = std::max(1, (int)(cloud.img.height * cloud.scale_y * scale));

        color col = COLOR_GREEN;
        debug_draw_rect_with_contour(sx, sy, sw, sh, col);
        debug_draw_crosshair(sx, sy);

        pcstr status_name = e_cloud_status_tokens.name(cloud.status);
        int tx = cloud.render_pos.x;
        int ty = cloud.render_pos.y;
        debug_text(ctx, str, tx, ty, 40, "C", i, col);
        ty += 10;
        debug_text_a(ctx, str, tx, ty, 0, status_name ? status_name : "?", col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "px", cloud.pos.x, col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "py", cloud.pos.y, col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "rx", cloud.render_pos.x, col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "ry", cloud.render_pos.y, col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "ang", cloud.angle, col);
        ty += 10;
        debug_text(ctx, str, tx, ty, 40, "side", cloud.side, col);
    }
}

void clouds_t::draw_city(painter &ctx) {
    OZZY_PROFILER_FUNCTION();

    if (game.paused
        || (!g_window_manager.window_is("window_city")
            && !g_window_manager.window_is("window_city_military")
            && !g_window_manager.window_is("window_city_warship")
            && !g_window_manager.window_is("window_city_transport"))) {
        pause();
    }

    auto mm_view = g_camera.get_scrollable_pixel_limits();
    const vec2i offset = {
        g_camera.camera_position.x - mm_view.min.x,
        g_camera.camera_position.y - mm_view.min.y,
    };

    const float zoom = g_zoom.get_scale();
    const vec2i view_size = {
        std::max(1, (int)(g_camera.size_pixels.x / zoom)),
        std::max(1, (int)(g_camera.size_pixels.y / zoom)),
    };

    draw(ctx, offset, view_size);
}

// Cosmetic only (Enhanced): the chunk keeps the clouds where they were, nothing in the simulation reads it.
io_buffer* iob_clouds = new io_buffer(
  [](io_buffer* iob, size_t version) {
      int32_t count = (int32_t)std::min<size_t>(g_clouds.clouds.size(), 16);
      iob->bind(BIND_SIGNATURE_INT32, &count);
      for (int i = 0; i < 16; ++i) {
          vec2i dummy;
          vec2i& pos = (i < (int)g_clouds.clouds.size()) ? g_clouds.clouds[i].pos : dummy;
          iob->bind(BIND_SIGNATURE_INT32, &pos.x);
          iob->bind(BIND_SIGNATURE_INT32, &pos.y);
      }
  },
  [](size_t version) {
      for (auto& cloud : g_clouds.clouds) {
          cloud.pos = {0, 0};
      }
  });

void ANK_REGISTER_APPLICATION_MODULE(register_city_clouds_module) {
    g_screen_city.add_screen_space_effect([](painter &ctx) { g_clouds.draw_city(ctx); });
    g_debug.add_render_handler("clouds", [](painter &ctx) { g_clouds.draw_debug(ctx); });
}
