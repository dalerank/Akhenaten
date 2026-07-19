#include "graphics/image.h"

#include "core/log.h"
#include "core/profiler.h"
#include "core/xstring.h"
#include "js/js_game.h"
#include "mujs/mujs.h"

static bool __image_request_pak(js_State *J) {
    if (js_isstring(J, 1)) {
        xstring name;
        name._set(js_tostring(J, 1));
        return image_request_pak(name);
    }

    if (js_isnumber(J, 1) || js_iscnumber(J, 1)) {
        return image_request_pak(static_cast<int>(js_tonumber(J, 1)));
    }

    logs::warn("VFS: pak-queue: __image_request_pak expects id or name");
    return false;
}
ANK_FUNCTION_RAW(__image_request_pak)

static bool __image_pak_is_loaded(js_State *J) {
    if (js_isstring(J, 1)) {
        xstring name;
        name._set(js_tostring(J, 1));
        return image_pak_is_loaded(name);
    }

    if (js_isnumber(J, 1) || js_iscnumber(J, 1)) {
        return image_pak_is_loaded(static_cast<int>(js_tonumber(J, 1)));
    }

    logs::warn("VFS: pak-queue: __image_pak_is_loaded expects id or name");
    return false;
}
ANK_FUNCTION_RAW(__image_pak_is_loaded)
