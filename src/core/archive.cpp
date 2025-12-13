#include "core/archive.h"

#include "graphics/animation.h"
#include "graphics/image_desc.h"

#include "mujs/mujs.h"

g_archive g_config_arch{ nullptr };

void archive::getproperty(int idx, pcstr name) {
    js_getproperty((js_State*)state, idx, name);
}

void archive::getproperty(archive arch, int idx, pcstr name) {
    js_getproperty((js_State *)(arch.state), idx, name);
}

bool archive::isarray(int idx) {
    return js_isarray((js_State*)state, idx);
}

int archive::getlength(int idx) {
    return js_getlength((js_State*)state, idx);
}

void archive::getindex(int idx, int i) {
    js_getindex((js_State*)state, idx, i);
}

bool archive::isnumber(int idx) {
    return (js_isnumber((js_State*)state, idx) || js_iscnumber((js_State*)state, idx));
}

bool archive::isstring(int idx) {
    return js_isstring((js_State *)state, idx);
}

bool archive::isboolean(int idx) {
    return js_isboolean((js_State *)state, idx);
}

double archive::tonumber(int idx) {
    return js_tonumber((js_State*)state, idx);
}

pcstr archive::tostring(int idx) {
    return js_tostring((js_State *)state, idx);
}

bool archive::toboolean(int idx) {
    return js_toboolean((js_State *)state, idx);
}

void archive::pop(int num) {
    js_pop((js_State *)state, num);
}

void archive::pop(archive arch, int n) {
    js_pop((js_State *)(arch.state), n);
}

bool archive::isobject(int idx) {
    return js_isobject((js_State *)state, idx);
}

bool archive::isobject(archive arch, int idx) {
    return js_isobject((js_State *)(arch.state), idx);
}

void archive::pushiterator(archive arch, int idx, int own) {
    js_pushiterator((js_State *)(arch.state), idx, own);
}

pcstr archive::nextiterator(archive arch, int idx) {
    return js_nextiterator((js_State *)(arch.state), idx);
}

void archive::getglobal(pcstr name) {
    js_getglobal((js_State *)state, name);
}

pcstr lang_get_string(int group, int index);
pcstr archive::r_string(pcstr name) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    pcstr result = "";
    if (js_isundefined(vm, -1)) {
        ;
    } else if (js_isstring(vm, -1)) {
        result = js_tostring(vm, -1);
    } else if (js_isarray(vm, -1)) {
        int length = js_getlength(vm, -1);
        vec2i gx;
        if (length == 2) {
            js_getindex(vm, -1, 0); gx.x = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
            js_getindex(vm, -1, 1); gx.y = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
        }

        result = lang_get_string(gx.x, gx.y);
    } else if (js_isobject(vm, -1)) {
        js_getproperty(vm, -1, "group"); int group = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "id"); int id = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        result = lang_get_string(group, id);
    }
    js_pop(vm, 1);
    return result;
}

std::vector<std::string> archive::r_array_str(pcstr name) {
    auto vm = (js_State *)state;

    js_getproperty(vm, -1, name);
    std::vector<std::string> result;
    if (js_isarray(vm, -1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            pcstr v = js_tostring(vm, -1);
            result.emplace_back(v);
            js_pop(vm, 1);
        }
    }
    if (js_isundefined(vm, -1)) {
        int i = 0;
        ;
    }
    if (js_isobject(vm, -1)) {
        int i = 0;
        ;
    }
    js_pop(vm, 1);

    return result;
}

std::vector<std::string> archive::to_array_str() {
    auto vm = (js_State *)state;

    std::vector<std::string> result;
    if (js_isarray(vm, -1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            pcstr v = js_tostring(vm, -1);
            result.emplace_back(v);
            js_pop(vm, 1);
        }
    }
    if (js_isundefined(vm, -1)) {
        int i = 0;
        ;
    }
    if (js_isobject(vm, -1)) {
        int i = 0;
        ;
    }

    return result;
}

pcstr archive::to_string() {
    auto vm = (js_State *)state;

    if (js_isundefined(vm, -1)) {
        return "";
    } else if (js_isstring(vm, -1)) {
        return js_tostring(vm, -1);
    } 

    return "";
}

archive::variant_t archive::to_variant() {
    auto vm = (js_State *)state;

    variant_t result;
    pcstr name = "unknown";
    if (js_isundefined(vm, -1)) {
        result = variant_t(variant_none_t{ name });
    } else if (js_isstring(vm, -1)) {
        const xstring str = js_tostring(vm, -1);
        result = variant_t(str);
    } else if (js_isboolean(vm, -1)) {
        const bool v = js_toboolean(vm, -1);
        result = variant_t(v);
    } else if (js_isnumber(vm, -1)) {
        const float f = js_tonumber(vm, -1);
        result = variant_t(f);
    } else if (js_isobject(vm, -1)) {
        result = variant_t(variant_object_t{ name });
    } else if (js_isarray(vm, -1)) {
        result = variant_t(variant_array_t{ name });
    }

    return result;
}

archive::variant_t archive::r_variant(pcstr name) {
    auto vm = (js_State *)state;

    js_getproperty(vm, -1, name);
    variant_t result;
    if (js_isundefined(vm, -1)) {
        result = variant_t(variant_none_t{name});
    } else if (js_isstring(vm, -1)) {
        const xstring str = js_tostring(vm, -1);
        result = variant_t(str);
    } else if (js_isboolean(vm, -1)) {
        const bool v = js_toboolean(vm, -1);
        result = variant_t(v);
    } else if (js_isnumber(vm, -1)) {
        const float f = js_tonumber(vm, -1);
        result = variant_t(f);
    } else if (js_isobject(vm, -1)) {
        result = variant_t(variant_object_t{ name });
    } else if (js_isarray(vm, -1)) {
        result = variant_t(variant_array_t{ name });
    }
    js_pop(vm, 1);

    return result;
}

std::vector<vec2i> archive::r_array_vec2i(pcstr name, pcstr px, pcstr py) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    std::vector<vec2i> result;
    if (js_isarray(vm, -1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            vec2i v = r_vec2i_impl(px, py);
            result.push_back(v);
            js_pop(vm, 1);
        }
        js_pop(vm, 1);
    }
    return result;
}

int archive::r_int(pcstr name, int def) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    int result = js_isundefined(vm, -1) ? def : js_tointeger(vm, -1);
    js_pop(vm, 1);
    return result;
}

float archive::r_float(pcstr name, float def) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    float result = js_isundefined(vm, -1) ? def : (float)js_tonumber(vm, -1);
    js_pop(vm, 1);
    return result;
}

uint32_t archive::r_uint(pcstr name, uint32_t def) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    uint32_t result = js_isundefined(vm, -1) ? def : js_touint32(vm, -1);
    js_pop(vm, 1);
    return result;
}

bool archive::r_bool(pcstr name, bool def) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    bool result = js_isundefined(vm, -1) ? def : js_toboolean(vm, -1);
    js_pop(vm, 1);
    return result;
}

vec2i archive::r_size2i(pcstr name, pcstr w, pcstr h) {
    return r_vec2i(name, w, h);
}

vec2i archive::r_vec2i_impl(pcstr x, pcstr y) {
    auto vm = (js_State *)state;
    vec2i result(0, 0);
    if (js_isobject(vm, -1)) {
        if (js_isarray(vm, -1)) {
            int length = js_getlength(vm, -1);
            if (length > 0) {
                js_getindex(vm, -1, 0); result.x = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
                if (length > 1) {
                    js_getindex(vm, -1, 1); result.y = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
                }
            }
        } else {
            js_getproperty(vm, -1, x); result.x = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
            js_getproperty(vm, -1, y); result.y = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
        }
    }

    return result;
}

vec2i archive::r_vec2i(pcstr name, pcstr x, pcstr y) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    vec2i result = r_vec2i_impl(x, y);
    js_pop(vm, 1);

    return result;
}

tile2i archive::r_tile2i(pcstr name, pcstr i, pcstr j) {
    auto vm = (js_State*)state;
    js_getproperty(vm, -1, name);
    vec2i t = r_vec2i_impl(i, j);
    js_pop(vm, 1);

    return tile2i(t.x, t.y);
}

bool archive::r_anim(pcstr name, animation_t &anim) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    bool ok = false;
    if (js_isundefined(vm, -1)) {
        ;
    } else if (js_isobject(vm, -1)) {
        js_getproperty(vm, -1, "pack"); anim.pack = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "id"); anim.id = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "offset"); anim.offset = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "duration"); anim.duration = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "max_frames"); anim.max_frames = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        ok = true;
    }
    js_pop(vm, 1);
    return ok;
}

bool archive::r_desc(pcstr name, image_desc &desc) {
    auto vm = (js_State *)state;
    js_getproperty(vm, -1, name);
    bool ok = r_desc_impl(desc);
    js_pop(vm, 1);
    return ok;
}

xstring archive::r_function(pcstr name) {
    js_State *J = (js_State *)state;
    xstring funcref;
    js_getproperty(J, -1, name);
    if (js_iscallable(J, -1)) {
        funcref = js_ref(J);
    } else {
        js_pop(J, 1);
    }

    return funcref;
}

bool archive::r_desc_impl(image_desc &desc) {
    auto vm = (js_State *)state;
    if (js_isundefined(vm, -1)) {
        return false;
    } 
    
    if (js_isobject(vm, -1)) {
        js_getproperty(vm, -1, "pack"); desc.pack = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "id"); desc.id = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "offset"); desc.offset = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        return true;
    }

    return false;
}

void g_archive::w_property(pcstr name, pcstr prop, const xstring &value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (js_isundefined(J, -1)) {
        pop(1);
        js_newobject(J);
    }

    js_pushstring(J, value.c_str());
    js_setproperty(J, -2, prop);
    js_setglobal(J, name);
}

void g_archive::w_property(pcstr name, pcstr prop, bool value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (js_isundefined(J, -1)) {
        pop(1);
        js_newobject(J);
    }

    js_pushboolean(J, value);
    js_setproperty(J, -2, prop);
    js_setglobal(J, name);
}

void g_archive::w_property(pcstr name, pcstr prop, float value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (js_isundefined(J, -1)) {
        pop(1);
        js_newobject(J);
    }

    js_pushnumber(J, value);
    js_setproperty(J, -2, prop);
    js_setglobal(J, name);
}

void g_archive::w_property(pcstr name, pcstr prop, vec2i value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (js_isundefined(J, -1)) {
        pop(1);
        js_newobject(J);
    }

    js_newobject(J);
    js_pushnumber(J, value.x); js_setproperty(J, -2, "x");
    js_pushnumber(J, value.y); js_setproperty(J, -2, "y");
    js_setproperty(J, -2, prop);
    js_setglobal(J, name);
}
