#include "clouds.h"

#include "core/profiler.h"
#include "js/js_game.h"
#include "js/js_global_object.h"
#include "mujs/mujs.h"

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

static void __clouds_cloud(js_State *J) {
    const int index = static_cast<int>(js_tointeger(J, 1));
    if (index < 0 || index >= static_cast<int>(g_clouds.clouds.size())) {
        js_pushnull(J);
        return;
    }

    cloud_t &cloud = g_clouds.clouds[index];
    js_newobject(J);
    ank_global_obj_bind_field(J, js_intern("status"), &cloud.status);
    ank_global_obj_bind_field(J, js_intern("pos"), &cloud.pos);
    ank_global_obj_bind_field(J, js_intern("render_pos"), &cloud.render_pos);
    js_pushnumber(J, cloud.speed.x.current_speed);
    js_setproperty(J, -2, js_intern("speedx"));
    js_pushnumber(J, cloud.speed.y.current_speed);
    js_setproperty(J, -2, js_intern("speedy"));
}
ANK_FUNCTION_RAW(__clouds_cloud);
