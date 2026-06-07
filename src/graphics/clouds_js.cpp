#include "clouds.h"

#include "core/profiler.h"
#include "core/xstring.h"
#include "grid/point.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void __clouds_reset() {
    g_clouds.init_cloud_images();
}
ANK_FUNCTION(__clouds_reset);

int __clouds_count() {
    return static_cast<int>(g_clouds.clouds.size());
}
ANK_FUNCTION(__clouds_count);

ANK_GLOBAL_OBJECT(g_clouds.config, __clouds_config,
    num_cloud_ellipses,
    cloud_alpha_increase,
    cloud_columns,
    cloud_rows,
    cloud_width,
    cloud_height,
    cloud_size_ratio,
    cloud_scale,
    cloud_min_creation_timeout,
    cloud_max_creation_timeout,
    pause_min_frames
);

xstring __clouds_cloud_status(int index) {
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        return {};
    }
    pcstr name = e_cloud_status_tokens.name(g_clouds.clouds[index].status);
    return xstring(name ? name : "UNKNOWN");
}
ANK_FUNCTION_1(__clouds_cloud_status);

float __clouds_cloud_speedx(int index) {
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        return 0.f;
    }
    return static_cast<float>(g_clouds.clouds[index].speed.x.current_speed);
}
ANK_FUNCTION_1(__clouds_cloud_speedx);

float __clouds_cloud_speedy(int index) {
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        return 0.f;
    }
    return static_cast<float>(g_clouds.clouds[index].speed.y.current_speed);
}
ANK_FUNCTION_1(__clouds_cloud_speedy);

vec2i __clouds_cloud_pos(int index) {
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        return {0, 0};
    }
    return g_clouds.clouds[index].pos;
}
ANK_FUNCTION_1(__clouds_cloud_pos);

vec2i __clouds_cloud_render_pos(int index) {
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        return {0, 0};
    }
    return g_clouds.clouds[index].render_pos;
}
ANK_FUNCTION_1(__clouds_cloud_render_pos);
