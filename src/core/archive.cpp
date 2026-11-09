#include "core/archive.h"
#include "core/log.h"

#include "graphics/animation.h"
#include "graphics/image_desc.h"
#include "mujs/jsi.h"
#include "mujs/mujs.h"

#include <string>
#include <unordered_set>
#include <vector>

g_archive g_config_arch{ nullptr };

namespace archive_check {
    bool report_keys = false;

    namespace {
        struct frame_data {
            pcstr type;
            void* state;
            std::unordered_set<std::string> keys;
        };
        std::vector<frame_data> g_frames;
        std::vector<std::string> g_roots;
        std::unordered_set<std::string> g_reported;
        std::unordered_set<const void*> g_seen_fields;

        // One config object can be read by several readers (building params: base fields, then the
        // derived type), so read keys are collected per object and compared once per refresh.
        struct object_keys {
            std::string where;
            std::vector<std::string> own;
            std::unordered_set<std::string> read;
        };
        std::unordered_map<const void*, object_keys> g_objects;

        std::string context() {
            std::string c = g_roots.empty() ? std::string() : g_roots.back();
            if (!g_frames.empty()) {
                if (!c.empty()) {
                    c += ':';
                }
                c += g_frames.back().type;
            }
            return c;
        }

        void report(const std::string& msg) {
            if (g_reported.insert(msg).second) {
                logs::warn("%s", msg.c_str());
            }
        }
    } // namespace

    frame::frame(pcstr type_name, void* js_state) : depth(g_frames.size()) {
        g_frames.push_back({type_name, js_state, {}});
    }

    frame::~frame() {
        if (g_frames.size() <= depth) {
            return;
        }
        g_frames.resize(depth + 1);
        frame_data& f = g_frames.back();
        js_State* J = (js_State*)f.state;
        if (report_keys && J && J->isobject(-1) && !J->isarray(-1)) {
            object_keys& obj = g_objects[J->toobject(-1)];
            if (obj.where.empty()) {
                obj.where = context();
                js_pushiterator(J, -1, 1);
                js_StringNode key;
                while ((key = js_nextiterator(J, -1))) {
                    if (pcstr k = js_strnode_cstr(key)) {
                        obj.own.emplace_back(k);
                    }
                }
                js_pop(J, 1);
            }
            obj.read.insert(f.keys.begin(), f.keys.end());
        }
        g_frames.pop_back();
    }

    root::root(pcstr name) : depth(g_roots.size()) {
        g_roots.emplace_back(name ? name : "");
    }

    root::~root() {
        if (g_roots.size() > depth) {
            g_roots.resize(depth);
        }
    }

    void flush() {
        for (const auto& [ptr, obj] : g_objects) {
            for (const auto& k : obj.own) {
                if (!obj.read.count(k)) {
                    report("[config] unknown key " + obj.where + "." + k);
                }
            }
        }
        g_objects.clear();
    }

    void note_key(pcstr key) {
        if (report_keys && !g_frames.empty() && key) {
            g_frames.back().keys.insert(key);
        }
    }

    // Overloads that touch the name only when reporting: a null node or an unterminated
    // string_view must never be dereferenced on the normal path.
    static void note_key(js_StringNode key) {
        if (report_keys && key) {
            note_key(js_strnode_cstr(key));
        }
    }

    static void note_key(std::string_view key) {
        if (report_keys) {
            note_key(std::string(key).c_str());
        }
    }

    bool first_read(const void* field_addr) {
        return g_seen_fields.insert(field_addr).second;
    }

    bool key_missing(void* js_state, pcstr key) {
        auto vm = (js_State*)js_state;
        vm->getproperty(-1, js_intern(key));
        const bool missing = vm->isundefined(-1);
        js_pop(vm, 1);
        return missing;
    }

    void zeroed_default(pcstr field, const std::string& value, const void*) {
        report("[config] missing key " + context() + "." + field + " resets C++ default " + value + " to 0");
    }

    void wrong_type(pcstr key, pcstr expected) {
        report("[config] " + context() + "." + key + ": expected " + expected);
    }
} // namespace archive_check

static void get_prop(js_State* vm, pcstr name) {
    archive_check::note_key(name);
    vm->getproperty(-1, js_intern(name));
}

static void get_prop(js_State* vm, js_StringNode name) {
    archive_check::note_key(name);
    vm->getproperty(-1, name);
}

static void check_number(js_State* vm, pcstr name) {
    if (!vm->isundefined(-1) && !vm->isnull(-1) && !vm->isnumber(-1) && !vm->isboolean(-1)) {
        archive_check::wrong_type(name, "number");
    }
}

void archive::getproperty(int idx, std::string_view name) {
    archive_check::note_key(name);
    ((js_State*)state)->getproperty(idx, js_intern(name.data()));
}

void archive::getproperty(int idx, xstring_value* name) {
    archive_check::note_key(name);
    ((js_State*)state)->getproperty(idx, name);
}

void archive::getproperty(archive arch, int idx, std::string_view name) {
    archive_check::note_key(name);
    ((js_State *)(arch.state))->getproperty(idx, js_intern(name.data()));
}

void archive::getproperty(archive arch, int idx, xstring_value* name) {
    archive_check::note_key(name);
    ((js_State*)(arch.state))->getproperty(idx, name);
}

bool archive::isarray(int idx) {
    return ((js_State*)state)->isarray(idx);
}

int archive::getlength(int idx) {
    return js_getlength((js_State*)state, idx);
}

void archive::getindex(int idx, int i) {
    js_getindex((js_State*)state, idx, i);
}

bool archive::isnumber(int idx) {
    return (((js_State*)state)->isnumber(idx) || ((js_State*)state)->iscnumber(idx));
}

bool archive::isstring(int idx) {
    return ((js_State *)state)->isstring(idx);
}

bool archive::isboolean(int idx) {
    return ((js_State *)state)->isboolean(idx);
}

double archive::tonumber(int idx) {
    return js_tonumber((js_State*)state, idx);
}

xstring archive::tostring(int idx) {
    auto pp = js_tostring((js_State*)state, idx);
    xstring result;
    result._set(pp);
    return result;
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
    return ((js_State *)state)->isobject(idx);
}

bool archive::isobject(archive arch, int idx) {
    return ((js_State *)arch.state)->isobject(idx);
}

void archive::pushiterator(archive arch, int idx, int own) {
    js_pushiterator((js_State *)(arch.state), idx, own);
}

xstring_value* archive::nextiterator(archive arch, int idx) {
    return js_nextiterator((js_State *)(arch.state), idx);
}

void archive::getglobal(std::string_view name) {
    js_getglobal((js_State *)state, name.data());
}

pcstr lang_get_string(int group, int index);

static js_StringNode property_group = js_intern("group");
static js_StringNode property_id = js_intern("id");

xstring archive::r_string_impl(pcstr name, pcstr def) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    xstring result = def;
    if (vm->isundefined(-1)) {
        ;
    } else if (vm->isstring(-1)) {
        auto pp = js_tostring(vm, -1);
        result._set(pp);
    } else if (vm->isarray(-1)) {
        int length = js_getlength(vm, -1);
        vec2i gx;
        if (length == 2) {
            js_getindex(vm, -1, 0); gx.x = !vm->isundefined(-1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
            js_getindex(vm, -1, 1); gx.y = !vm->isundefined(-1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
        }

        result = lang_get_string(gx.x, gx.y);
    } else if (vm->isobject(-1)) {
        get_prop(vm, property_group);
        int group = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);

        get_prop(vm, property_id);
        int id = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        result = lang_get_string(group, id);
    }
    js_pop(vm, 1);
    return result;
}

xstring archive::r_string(pcstr name, pcstr def) {
    return r_string_impl(name, def);
}

xstring archive::r_string(const xstring& name, pcstr def) {
    return r_string_impl(name.c_str(), def);
}

std::vector<xstring> archive::r_array_str(pcstr name) {
    auto vm = (js_State *)state;

    get_prop(vm, name);
    std::vector<xstring> result;
    if (vm->isarray(-1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            auto pp = js_tostring(vm, -1);
            xstring v;
            v._set(pp);
            result.emplace_back(v);
            js_pop(vm, 1);
        }
    }
    if (vm->isundefined(-1)) {
        int i = 0;
        ;
    }
    if (vm->isobject(-1)) {
        int i = 0;
        ;
    }
    js_pop(vm, 1);

    return result;
}

std::vector<xstring> archive::to_array_str() {
    auto vm = (js_State *)state;

    std::vector<xstring> result;
    if (vm->isarray(-1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            auto pp = js_tostring(vm, -1);
            xstring v;
            v._set(pp);
            result.emplace_back(v);
            js_pop(vm, 1);
        }
    }
    if (vm->isundefined(-1)) {
        int i = 0;
        ;
    }
    if (vm->isobject(-1)) {
        int i = 0;
        ;
    }

    return result;
}

xstring archive::to_string() {
    auto vm = (js_State *)state;

    if (vm->isundefined(-1)) {
        return "";
    } else if (vm->isstring(-1)) {
        auto pp = js_tostring(vm, -1);
        xstring v;
        v._set(pp);
        return v;
    } 

    return {};
}

archive::variant_t archive::to_variant() {
    auto vm = (js_State *)state;

    variant_t result;
    pcstr name = "unknown";
    if (vm->isundefined(-1)) {
        result = variant_t(variant_none_t{ name });
    } else if (vm->isstring(-1)) {
        auto pp = js_tostring(vm, -1);
        xstring str;
        str._set(pp);
        result = variant_t(str);
    } else if (vm->isboolean(-1)) {
        const bool v = js_toboolean(vm, -1);
        result = variant_t(v);
    } else if (vm->isnumber(-1)) {
        const float f = js_tonumber(vm, -1);
        result = variant_t(f);
    } else if (vm->isobject(-1)) {
        result = variant_t(variant_object_t{ name });
    } else if (vm->isarray(-1)) {
        result = variant_t(variant_array_t{ name });
    }

    return result;
}

archive::variant_t archive::r_variant(pcstr name) {
    auto vm = (js_State *)state;

    get_prop(vm, name);
    variant_t result;
    if (vm->isundefined(-1)) {
        result = variant_t(variant_none_t{name});
    } else if (vm->isstring(-1)) {
        auto pp = js_tostring(vm, -1);
        xstring str;
        str._set(pp);
        result = variant_t(str);
    } else if (vm->isboolean(-1)) {
        const bool v = js_toboolean(vm, -1);
        result = variant_t(v);
    } else if (vm->isnumber(-1)) {
        const float f = js_tonumber(vm, -1);
        result = variant_t(f);
    } else if (vm->isobject(-1)) {
        result = variant_t(variant_object_t{ name });
    } else if (vm->isarray(-1)) {
        result = variant_t(variant_array_t{ name });
    }
    js_pop(vm, 1);

    return result;
}

std::vector<vec2i> archive::r_array_vec2i(pcstr name, pcstr px, pcstr py) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    std::vector<vec2i> result;
    if (vm->isarray(-1)) {
        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            vec2i v = r_vec2i_impl({ 0, 0 }, px, py);
            result.push_back(v);
            js_pop(vm, 1);
        }
    }
    js_pop(vm, 1);
    return result;
}

int archive::r_int(pcstr name, int def) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    check_number(vm, name);
    int result = vm->isundefined(-1) ? def : js_tointeger(vm, -1);
    js_pop(vm, 1);
    return result;
}

float archive::r_float(pcstr name, float def) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    check_number(vm, name);
    float result = vm->isundefined(-1) ? def : (float)js_tonumber(vm, -1);
    js_pop(vm, 1);
    return result;
}

uint32_t archive::r_uint(pcstr name, uint32_t def) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    check_number(vm, name);
    uint32_t result = vm->isundefined(-1) ? def : js_touint32(vm, -1);
    js_pop(vm, 1);
    return result;
}

bool archive::r_bool(pcstr name, bool def) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    bool result = vm->isundefined(-1) ? def : js_toboolean(vm, -1);
    js_pop(vm, 1);
    return result;
}

vec2i archive::r_size2i(pcstr name, vec2i def, pcstr w, pcstr h) {
    return r_vec2i(name, def, w, h);
}

vec2i archive::r_vec2i_impl(vec2i def, pcstr x, pcstr y) {
    auto vm = (js_State *)state;
    vec2i result = def;
    if (vm->isobject(-1)) {
        if (vm->isarray(-1)) {
            int length = js_getlength(vm, -1);
            if (length > 0) {
                js_getindex(vm, -1, 0); result.x = !vm->isundefined(-1) ? js_tointeger(vm, -1) : def.x; js_pop(vm, 1);
                if (length > 1) {
                    js_getindex(vm, -1, 1); result.y = !vm->isundefined(-1) ? js_tointeger(vm, -1) : def.y; js_pop(vm, 1);
                }
            }
        } else {
            get_prop(vm, x);
            result.x = !vm->isundefined(-1) ? js_tointeger(vm, -1) : def.x;
            js_pop(vm, 1);
            get_prop(vm, y);
            result.y = !vm->isundefined(-1) ? js_tointeger(vm, -1) : def.y;
            js_pop(vm, 1);
        }
    }

    return result;
}

vec2i archive::r_vec2i(pcstr name, vec2i def, pcstr x, pcstr y) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    vec2i result = r_vec2i_impl(def, x, y);
    js_pop(vm, 1);

    return result;
}

tile2i archive::r_tile2i(pcstr name, pcstr i, pcstr j) {
    auto vm = (js_State*)state;
    get_prop(vm, name);
    vec2i t = r_vec2i_impl({ 0, 0 }, i, j);
    js_pop(vm, 1);

    return tile2i(t.x, t.y);
}

js_StringNode property_pack = js_intern("pack");
js_StringNode property_offset = js_intern("offset");
js_StringNode property_duration = js_intern("duration");
js_StringNode property_max_frames = js_intern("max_frames");
js_StringNode property_path = js_intern("path");

bool archive::r_anim(pcstr name, animation_t &anim) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    bool ok = false;
    if (vm->isundefined(-1)) {
        ;
    } else if (vm->isobject(-1)) {
        get_prop(vm, property_pack);
        anim.pack = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_id);
        anim.id = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_offset);
        anim.offset = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_duration);
        anim.duration = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_max_frames);
        anim.max_frames = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        ok = true;
    }
    js_pop(vm, 1);
    return ok;
}

bool archive::r_desc(pcstr name, image_desc &desc) {
    auto vm = (js_State *)state;
    get_prop(vm, name);
    bool ok = r_desc_impl(desc);
    js_pop(vm, 1);
    return ok;
}

xstring archive::r_function(pcstr name) {
    js_State *J = (js_State *)state;
    xstring funcref;
    get_prop(J, name);
    if (J->iscallable(-1)) {
        auto pp = js_ref(J);
        funcref._set(pp);
    } else {
        js_pop(J, 1);
    }

    return funcref;
}

bool archive::r_desc_impl(image_desc &desc) {
    auto vm = (js_State *)state;
    if (vm->isundefined(-1)) {
        return false;
    }

    if (vm->isstring(-1)) {
        desc.path._set(js_tostring(vm, -1));
        return !desc.path.empty();
    }

    if (vm->isobject(-1)) {
        get_prop(vm, property_pack);
        desc.pack = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_id);
        desc.id = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        get_prop(vm, property_offset);
        desc.offset = vm->isundefined(-1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);

        get_prop(vm, property_path);
        if (!vm->isundefined(-1) && vm->isstring(-1)) {
            desc.path._set(js_tostring(vm, -1));
        }
        js_pop(vm, 1);
        return desc.valid();
    }

    return false;
}

void g_archive::w_property(pcstr name, pcstr prop, const xstring &value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (J->isundefined(-1)) {
        pop(1);
        J->newobject();
    }

    J->pushstring(value.c_str());
    js_setproperty(J, -2, js_intern(prop));
    js_setglobal(J, name);
}

void g_archive::w_property(pcstr name, pcstr prop, bool value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (J->isundefined(-1)) {
        pop(1);
        J->newobject();
    }

    js_pushboolean(J, value);
    js_setproperty(J, -2, js_intern(prop));
    js_setglobal(J, name);
}

void g_archive::w_property(pcstr name, pcstr prop, float value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (J->isundefined(-1)) {
        pop(1);
        J->newobject();
    }

    js_pushnumber(J, value);
    js_setproperty(J, -2, js_intern(prop));
    js_setglobal(J, name);
}

static js_StringNode property_x = js_intern("x");
static js_StringNode property_y = js_intern("y");

void g_archive::w_property(pcstr name, pcstr prop, vec2i value) {
    if (!state) {
        return;
    }

    auto J = (js_State *)state;
    getglobal(name);
    if (J->isundefined(-1)) {
        pop(1);
        J->newobject();
    }

    J->newobject();
    js_pushnumber(J, value.x);
    js_setproperty(J, -2, property_x);

    js_pushnumber(J, value.y);
    js_setproperty(J, -2, property_y);

    js_setproperty(J, -2, js_intern(prop));
    js_setglobal(J, name);
}
