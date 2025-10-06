#pragma once

#include <cstdint>
#include "core/xstring.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "grid/point.h"
#include "core/fixed_memory_resource.h"
#include "core/svector.h"
#include "core/stable_array.h"
#include "graphics/image_desc.h"

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <variant>

struct animation_t;

struct archive {
    void *state = nullptr;
    inline archive(void *_vm) : state(_vm) {}

    pcstr r_string(pcstr name);
    std::vector<std::string> r_array_str(pcstr name);
    std::vector<std::string> to_array_str();
    int r_int(pcstr name, int def = 0);
    float r_float(pcstr name, float def = 0.f);
    uint32_t r_uint(pcstr name, uint32_t def = 0);
    bool r_bool(pcstr name, bool def = false);
    vec2i r_size2i(pcstr name, pcstr w = "w", pcstr h = "h");
    vec2i r_vec2i(pcstr name, pcstr x = "x", pcstr y = "y");
    tile2i r_tile2i(pcstr name, pcstr i = "i", pcstr j = "j");
    bool r_anim(pcstr name, animation_t &anim);
    bool r_desc(pcstr name, image_desc &desc);

    enum e_variant_type {
        vt_none = 0,
        vt_float,
        vt_bool,
        vt_string,
        vt_vec2i,
        vt_array,
        vt_object
    };
    struct variant_none_t { xstring name; }; // fake type for none
    struct variant_array_t { xstring name; }; // fake type for array
    struct variant_object_t { xstring name; }; // fake type for object

    using variant_t = std::variant<variant_none_t, float, bool, xstring, vec2i, variant_array_t, variant_object_t>;
    variant_t r_variant(pcstr name);
    variant_t to_variant();

    std::vector<vec2i> r_array_vec2i(pcstr name, pcstr px = "x", pcstr py = "y");

    template<typename T, typename C>
    inline void r_array_num(pcstr name, C &arr) {
        arr.clear();
        getproperty(-1, name);
        if (isarray(-1)) {
            int length = getlength(-1);

            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                double v = isnumber(-1) ? tonumber(-1) : 0.0;
                arr.push_back(static_cast<T>(v));
                pop(1);
            }
        }
        pop(1);
    }

    template<typename T>
    inline void r_stable_array(pcstr name, T &arr);

    template<class T>
    inline T r_type(pcstr name, T def = (T)0) { return (T)r_int(name, def); }

    template<size_t S, typename T = int>
    inline void r_sarray(pcstr name, std::array<T, S> &v);

    template<typename T, std::size_t N>
    inline void r(pcstr name, std::array<T, N>& v) { this->r_sarray<N, T>(name, v); }

    template<typename T, std::size_t N, typename = std::enable_if_t<std::is_enum_v<T> || std::is_arithmetic_v<T>>>
    inline void r(pcstr name, svector<T, N> &v) { this->r_array_num<T>(name, v); }

    template<typename T>
    void r(T& s);

    template<typename T>
    void r(pcstr name, T& v);

    template<typename T>
    inline void r(pcstr name, std::unordered_set<T> &v) {
        v.clear();
        this->r_array(name, [&] (archive arch) {
            T itemv;
            arch.r(itemv);
            v.insert(itemv);
        });
    }

    template<typename N, typename T>
    inline void r(pcstr name, std::unordered_map<N, T> &v) {
        v.clear();
        this->r_objects(name, [&] (pcstr key, archive arch) {
            auto &itemv = v[key];
            itemv.key = key;
            arch.r(itemv);
        });
    }

    template<typename T = int>
    inline std::vector<T> r_array_num(pcstr name) {
        getproperty(-1, name);
        std::vector<T> result;
        if (isarray(-1)) {
            int length = getlength(-1);

            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                float v = isnumber(-1) ? (float)tonumber(-1) : 0.f;
                result.push_back((T)v);
                pop(1);
            }
        }
        pop(1);
        return result;
    }

    template<typename T>
    inline void r_array_str(pcstr name, T& arr) {
        arr.clear();
        getproperty(-1, name);
        if (isarray(-1)) {
            int length = getlength(-1);

            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                pcstr v = isstring(-1) ? tostring(-1) : "";
                arr.push_back(v);
                pop(1);
            }
        }
        pop(1);
    }

    template<typename T = int>
    static inline std::vector<T> r_array_num(archive arch) {
        std::vector<T> result;
        if (arch.isarray(-1)) {
            int length = arch.getlength(-1);

            for (int i = 0; i < length; ++i) {
                arch.getindex(-1, i);
                float v = arch.isnumber(-1) ? (float)arch.tonumber(-1) : 0.f;
                result.push_back((T)v);
                arch.pop(1);
            }
        }
        return result;
    }

    template<typename T>
    inline void r_section(pcstr name, T read_func) {
        getproperty(-1, name);
        if (isobject(-1)) {
            read_func(state);
        }
        pop(1);
    }

    template<typename T>
    inline void r_array(pcstr name, T read_func) {
        getproperty(-1, name);
        r_array_impl(read_func);
        pop(1);
    }

    template<typename T, typename F>
    inline void r_array(pcstr name, T &arr, F read_func) {
        getproperty(-1, name);
        r_array_impl(arr, read_func);
        pop(1);
    }

    vec2i r_vec2i_impl(pcstr x, pcstr y);
    bool r_desc_impl(image_desc &desc);

    template<typename T>
    inline void r_objects(pcstr name, T read_func) {
        this->r_section(name, [this, &read_func] (archive s_arch) {
            fixed_memory_resource<xstring, 128> keys_buffer;
            std::pmr::vector<xstring> keys{ &keys_buffer };
            {
                pcstr key;
                pushiterator(s_arch, -1, 1);
                while ((key = nextiterator(s_arch, -1))) {
                    keys.push_back(key);
                }
                pop(s_arch, 1);
            }

            for (const auto &key : keys) {
                getproperty(s_arch, -1, key.c_str());
                //const bool isobj = isobject(s_arch, -1);
                read_func(key.c_str(), s_arch);
                pop(s_arch, 1);
            }
        });
    }

    template<typename T>
    inline void r_variants_impl(archive s_arch, T &container) {
        fixed_memory_resource<pcstr, 128> keys_buffer;
        std::pmr::vector<pcstr> keys{ &keys_buffer };
        {
            pcstr key;
            pushiterator(s_arch, -1, 1);
            while ((key = nextiterator(s_arch, -1))) {
                keys.push_back(key);
            }
            pop(s_arch, 1);
        }

        for (const auto &key : keys) {
            getproperty(s_arch, -1, key);
            if (isstring(-1)) {
                const xstring str = tostring(-1);
                container.set(key, str);
            } else if (isboolean(-1)) {
                const bool v = toboolean(-1);
                container.set(key, v);
            } else if (isnumber(-1)) {
                const float f = tonumber(-1);
                container.set(key, f);
            } else if (isobject(-1)) {
                ;
                // result = variant_t(variant_object_t{ name });
            } else if (isarray(-1)) {
                ;
                //result = variant_t(variant_array_t{ name });
            }
            pop(s_arch, 1);
        }
    }

    template<typename T>
    inline void r_variants(pcstr name, T &container) {
        this->r_section(name, [&] (archive s_arch) {
            r_variants_impl(s_arch, container);
        });
    }

protected:
    template<typename T>
    inline bool r_array_impl(T read_func) {
        if (!isarray(-1)) {
            return false;
        }

        int length = getlength(-1);
        for (int i = 0; i < length; ++i) {
            getindex(-1, i);

            if (isobject(-1)) {
                read_func(state);
            }

            pop(1);
        }
        return true;
    }

    template<typename T, typename F>
    inline bool r_array_impl(T &arr, F read_func) {
        if (!isarray(-1)) {
            return false;
        }

        arr.clear();
        int length = getlength(-1);
        using value_type = typename T::value_type;
        for (int i = 0; i < length; ++i) {
            getindex(-1, i);

            if (isobject(-1)) {
                arr.push_back(value_type());
                read_func(state, arr.back());
            }

            pop(1);
        }
        return true;
    }

    template<typename T>
    inline void r_struct(pcstr name, T &v);

    template<typename T>
    inline void r_struct(pcstr name, std::unordered_map<xstring, T> &v) {
        this->r_objects(name, [&] (pcstr key, archive sarch) {
            auto &item = v[key];
            sarch.r<T>(item);
        });
    }

    template<typename T>
    inline void r_struct(pcstr name, std::vector<T> &v) {
        if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>) {
            this->r_array_num<T>(name, v);
        } else {
            this->r_array(name, v, [] (archive it_arch, T &it) {
                it_arch.r<T>(it);
            });
        }
    }

    template<typename T>
    inline void r_struct(pcstr name, stable_array<T> &v) {
        this->r_stable_array(name, v);
    }

    template<typename T, std::size_t N>
    inline void r_struct(pcstr name, std::array<T, N> &v) { this->r_sarray<N, T>(name, v); }

    template<typename T, std::size_t N>
    inline void r_struct(pcstr name, svector<T, N> &v) {
        if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>) {
            this->r_array_num<T>(name, v);
        } else {
            this->r_array(name, v, [] (archive it_arch, T &it) {
                it_arch.r<T>(it);
            });
        }
    }

    void getproperty(int idx, pcstr name);
    static void getproperty(archive arch, int idx, pcstr name);
    bool isarray(int idx);
    int getlength(int idx);
    void getindex(int idx, int i);
    bool isnumber(int idx);
    bool isstring(int idx);
    bool isboolean(int idx);
    double tonumber(int idx);
    pcstr tostring(int idx);
    bool toboolean(int idx);
    void pop(int num);
    static void pop(archive arch, int n);
    bool isobject(int idx);
    static bool isobject(archive arch, int idx);
    static void pushiterator(archive arch, int idx, int own);
    static pcstr nextiterator(archive arch, int idx);
    void getglobal(pcstr name);
};

struct g_archive : public archive {
    template<typename T>
    inline void r_array(pcstr name, T read_func) {
        if (!state) {
            return;
        }

        getglobal(name);
        r_array_impl(read_func);
        pop(1);
    }

    template<typename T, typename F>
    inline void r_array(pcstr name, T &arr, F read_func) {
        if (!state) {
            return;
        }

        getglobal(name);
        r_array_impl(arr, read_func);
        pop(1);
    }

    template<typename T, std::size_t N>
    inline void r(pcstr name, svector<T, N> &v);

    template<typename T>
    inline void r(pcstr name, std::unordered_set<T>& v) {
        this->r_array(name, [&] (archive arch) {
            T itemv; arch.r(itemv);
            v.insert(itemv);
        });
    }

    template<typename T, std::size_t N>
    inline void r(pcstr name, std::array<T, N> &v);

    template<typename T>
    inline void r_stable_array(pcstr name, T &arr);

    template<typename T>
    inline void r(pcstr name, stable_array<T>& arr) {
        r_stable_array(name, arr);
    }

    template<typename T>
    inline bool r_section(pcstr name, T read_func) {
        if (!state) {
            return true;
        }

        bool ok = false;
        getglobal(name);
        if (isobject(-1)) {
            read_func(state);
            ok = true;
        } 
        pop(1);
        return ok;
    }

    template<typename T>
    inline bool r(pcstr name, T &obj);

    void w_property(pcstr name, pcstr prop, const xstring& value);
    void w_property(pcstr name, pcstr prop, bool value);
    void w_property(pcstr name, pcstr prop, float value);
    void w_property(pcstr name, pcstr prop, vec2i value);

    bool p_isobject() {
        return state ? isobject(-1) : false;
    }

    template<typename T>
    inline void r_objects(pcstr name, T read_func) {
        if (!state) {
            return;
        }

        getglobal(name);
        if (isobject(-1)) {
            pcstr key;

            fixed_memory_resource<bstring128, 128> keys_buffer;
            std::pmr::vector<bstring128> keys{ &keys_buffer };
            pushiterator(state, -1, 1);
            while ((key = nextiterator(state, -1))) {
                keys.push_back(key);
            }
            pop(state, 1);

            for (const auto &key : keys) {
                getproperty(state, -1, key.c_str());
                //const bool isobj = isobject(state, -1);
                read_func(key.c_str(), state);
                pop(state, 1);
            }
        }
        pop(1);
    }
};

extern g_archive g_config_arch;

struct g_archive_section {
    xstring name;

    inline int r_int(pcstr prop_name, int def = 0) {
        int result = def;
        g_config_arch.r_section(prop_name, [&] (archive arch) {
            result = arch.r_int(prop_name, def);
        });
        return result;
    }
};

#define ANK_CONFIG_STRUCT_EXPAND( x ) x
#define ANK_CONFIG_STRUCT_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define ANK_CONFIG_STRUCT_PASTE(...) ANK_CONFIG_STRUCT_EXPAND(ANK_CONFIG_STRUCT_GET_MACRO(__VA_ARGS__, \
        ANK_CONFIG_STRUCT_PASTE64, \
        ANK_CONFIG_STRUCT_PASTE63, \
        ANK_CONFIG_STRUCT_PASTE62, \
        ANK_CONFIG_STRUCT_PASTE61, \
        ANK_CONFIG_STRUCT_PASTE60, \
        ANK_CONFIG_STRUCT_PASTE59, \
        ANK_CONFIG_STRUCT_PASTE58, \
        ANK_CONFIG_STRUCT_PASTE57, \
        ANK_CONFIG_STRUCT_PASTE56, \
        ANK_CONFIG_STRUCT_PASTE55, \
        ANK_CONFIG_STRUCT_PASTE54, \
        ANK_CONFIG_STRUCT_PASTE53, \
        ANK_CONFIG_STRUCT_PASTE52, \
        ANK_CONFIG_STRUCT_PASTE51, \
        ANK_CONFIG_STRUCT_PASTE50, \
        ANK_CONFIG_STRUCT_PASTE49, \
        ANK_CONFIG_STRUCT_PASTE48, \
        ANK_CONFIG_STRUCT_PASTE47, \
        ANK_CONFIG_STRUCT_PASTE46, \
        ANK_CONFIG_STRUCT_PASTE45, \
        ANK_CONFIG_STRUCT_PASTE44, \
        ANK_CONFIG_STRUCT_PASTE43, \
        ANK_CONFIG_STRUCT_PASTE42, \
        ANK_CONFIG_STRUCT_PASTE41, \
        ANK_CONFIG_STRUCT_PASTE40, \
        ANK_CONFIG_STRUCT_PASTE39, \
        ANK_CONFIG_STRUCT_PASTE38, \
        ANK_CONFIG_STRUCT_PASTE37, \
        ANK_CONFIG_STRUCT_PASTE36, \
        ANK_CONFIG_STRUCT_PASTE35, \
        ANK_CONFIG_STRUCT_PASTE34, \
        ANK_CONFIG_STRUCT_PASTE33, \
        ANK_CONFIG_STRUCT_PASTE32, \
        ANK_CONFIG_STRUCT_PASTE31, \
        ANK_CONFIG_STRUCT_PASTE30, \
        ANK_CONFIG_STRUCT_PASTE29, \
        ANK_CONFIG_STRUCT_PASTE28, \
        ANK_CONFIG_STRUCT_PASTE27, \
        ANK_CONFIG_STRUCT_PASTE26, \
        ANK_CONFIG_STRUCT_PASTE25, \
        ANK_CONFIG_STRUCT_PASTE24, \
        ANK_CONFIG_STRUCT_PASTE23, \
        ANK_CONFIG_STRUCT_PASTE22, \
        ANK_CONFIG_STRUCT_PASTE21, \
        ANK_CONFIG_STRUCT_PASTE20, \
        ANK_CONFIG_STRUCT_PASTE19, \
        ANK_CONFIG_STRUCT_PASTE18, \
        ANK_CONFIG_STRUCT_PASTE17, \
        ANK_CONFIG_STRUCT_PASTE16, \
        ANK_CONFIG_STRUCT_PASTE15, \
        ANK_CONFIG_STRUCT_PASTE14, \
        ANK_CONFIG_STRUCT_PASTE13, \
        ANK_CONFIG_STRUCT_PASTE12, \
        ANK_CONFIG_STRUCT_PASTE11, \
        ANK_CONFIG_STRUCT_PASTE10, \
        ANK_CONFIG_STRUCT_PASTE9, \
        ANK_CONFIG_STRUCT_PASTE8, \
        ANK_CONFIG_STRUCT_PASTE7, \
        ANK_CONFIG_STRUCT_PASTE6, \
        ANK_CONFIG_STRUCT_PASTE5, \
        ANK_CONFIG_STRUCT_PASTE4, \
        ANK_CONFIG_STRUCT_PASTE3, \
        ANK_CONFIG_STRUCT_PASTE2, \
        ANK_CONFIG_STRUCT_PASTE1)(__VA_ARGS__))
#define ANK_CONFIG_STRUCT_PASTE2(func, v1) func(v1)
#define ANK_CONFIG_STRUCT_PASTE3(func, v1, v2) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE2(func, v2)
#define ANK_CONFIG_STRUCT_PASTE4(func, v1, v2, v3) ANK_CONFIG_STRUCT_PASTE2(func, v1)  ANK_CONFIG_STRUCT_PASTE3(func, v2, v3)
#define ANK_CONFIG_STRUCT_PASTE5(func, v1, v2, v3, v4) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE4(func, v2, v3, v4)
#define ANK_CONFIG_STRUCT_PASTE6(func, v1, v2, v3, v4, v5) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE5(func, v2, v3, v4, v5)
#define ANK_CONFIG_STRUCT_PASTE7(func, v1, v2, v3, v4, v5, v6) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE6(func, v2, v3, v4, v5, v6)
#define ANK_CONFIG_STRUCT_PASTE8(func, v1, v2, v3, v4, v5, v6, v7) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE7(func, v2, v3, v4, v5, v6, v7)
#define ANK_CONFIG_STRUCT_PASTE9(func, v1, v2, v3, v4, v5, v6, v7, v8) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE8(func, v2, v3, v4, v5, v6, v7, v8)
#define ANK_CONFIG_STRUCT_PASTE10(func, v1, v2, v3, v4, v5, v6, v7, v8, v9) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE9(func, v2, v3, v4, v5, v6, v7, v8, v9)
#define ANK_CONFIG_STRUCT_PASTE11(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE10(func, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define ANK_CONFIG_STRUCT_PASTE12(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE11(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define ANK_CONFIG_STRUCT_PASTE13(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE12(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define ANK_CONFIG_STRUCT_PASTE14(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE13(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define ANK_CONFIG_STRUCT_PASTE15(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE14(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define ANK_CONFIG_STRUCT_PASTE16(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE15(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define ANK_CONFIG_STRUCT_PASTE17(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE16(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define ANK_CONFIG_STRUCT_PASTE18(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE17(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define ANK_CONFIG_STRUCT_PASTE19(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE18(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define ANK_CONFIG_STRUCT_PASTE20(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE19(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define ANK_CONFIG_STRUCT_PASTE21(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE20(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define ANK_CONFIG_STRUCT_PASTE22(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE21(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define ANK_CONFIG_STRUCT_PASTE23(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE22(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define ANK_CONFIG_STRUCT_PASTE24(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE23(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define ANK_CONFIG_STRUCT_PASTE25(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE24(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define ANK_CONFIG_STRUCT_PASTE26(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE25(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define ANK_CONFIG_STRUCT_PASTE27(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE26(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define ANK_CONFIG_STRUCT_PASTE28(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE27(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define ANK_CONFIG_STRUCT_PASTE29(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE28(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define ANK_CONFIG_STRUCT_PASTE30(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE29(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define ANK_CONFIG_STRUCT_PASTE31(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE30(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define ANK_CONFIG_STRUCT_PASTE32(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE31(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define ANK_CONFIG_STRUCT_PASTE33(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE32(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define ANK_CONFIG_STRUCT_PASTE34(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE33(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define ANK_CONFIG_STRUCT_PASTE35(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE34(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define ANK_CONFIG_STRUCT_PASTE36(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE35(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define ANK_CONFIG_STRUCT_PASTE37(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE36(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define ANK_CONFIG_STRUCT_PASTE38(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE37(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define ANK_CONFIG_STRUCT_PASTE39(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE38(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define ANK_CONFIG_STRUCT_PASTE40(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE39(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define ANK_CONFIG_STRUCT_PASTE41(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE40(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define ANK_CONFIG_STRUCT_PASTE42(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE41(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define ANK_CONFIG_STRUCT_PASTE43(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE42(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define ANK_CONFIG_STRUCT_PASTE44(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE43(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define ANK_CONFIG_STRUCT_PASTE45(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE44(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define ANK_CONFIG_STRUCT_PASTE46(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE45(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define ANK_CONFIG_STRUCT_PASTE47(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE46(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define ANK_CONFIG_STRUCT_PASTE48(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE47(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define ANK_CONFIG_STRUCT_PASTE49(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE48(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define ANK_CONFIG_STRUCT_PASTE50(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE49(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define ANK_CONFIG_STRUCT_PASTE51(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE50(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define ANK_CONFIG_STRUCT_PASTE52(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE51(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define ANK_CONFIG_STRUCT_PASTE53(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE52(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define ANK_CONFIG_STRUCT_PASTE54(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE53(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define ANK_CONFIG_STRUCT_PASTE55(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE54(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define ANK_CONFIG_STRUCT_PASTE56(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE55(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define ANK_CONFIG_STRUCT_PASTE57(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE56(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define ANK_CONFIG_STRUCT_PASTE58(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE57(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define ANK_CONFIG_STRUCT_PASTE59(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE58(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define ANK_CONFIG_STRUCT_PASTE60(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE59(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define ANK_CONFIG_STRUCT_PASTE61(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE60(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define ANK_CONFIG_STRUCT_PASTE62(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE61(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define ANK_CONFIG_STRUCT_PASTE63(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE62(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define ANK_CONFIG_STRUCT_PASTE64(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) ANK_CONFIG_STRUCT_PASTE2(func, v1) ANK_CONFIG_STRUCT_PASTE63(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

#define ANK_CONFIG_STRUCT_FROM(v1) js_j.r(#v1, js_t.v1); 

template<typename, typename = void> struct class_has_load_function : std::false_type {};
template<typename T> struct class_has_load_function<T, std::void_t<decltype(std::declval<T &>().archive_load(nullptr))>> : std::true_type {};
template<typename T> constexpr bool class_has_load_function_v = class_has_load_function<T>::value;

template<typename, typename = void> struct class_has_unload_function : std::false_type {};
template<typename T> struct class_has_unload_function<T, std::void_t<decltype(std::declval<T &>().archive_unload(nullptr))>> : std::true_type {};
template<typename T> constexpr bool class_has_unload_function_v = class_has_unload_function<T>::value;

template<typename, typename = void> struct class_has_init_function : std::false_type {};
template<typename T> struct class_has_init_function<T, std::void_t<decltype(std::declval<T &>().archive_init())>> : std::true_type {};
template<typename T> constexpr bool class_has_init_function_v = class_has_init_function<T>::value;

namespace archive_helper {
    template<typename T>
    inline void reader(archive js_j, T &js_t);

    template<>
    inline void reader<vec2i>(archive arch, vec2i &v) { v = arch.r_vec2i_impl("x", "y"); }

    template<>
    inline void reader<tile2i>(archive arch, tile2i &v) { vec2i t = arch.r_vec2i_impl("i", "j"); v = { t.x, t.y }; }

    template<>
    inline void reader<image_desc>(archive arch, image_desc &v) { arch.r_desc_impl(v); }

    template<typename T> struct class_has_archive_reader : std::false_type {};
    template<typename T> constexpr bool class_has_archive_reader_v = class_has_archive_reader<T>::value;
}

// The problem is that  clang SFINAE trait class_has_load_function is working incorrectly. 
// Clang checks constexpr if more strictly, and even when the condition is false, it still checks 
// the syntactic correctness of the code inside the block.
template<typename ArchiveT, typename Type> inline void call_load_if_exists_impl(ArchiveT js_j, Type &js_t, std::true_type) { js_t.archive_load(js_j); }
template<typename ArchiveT, typename Type> inline void call_load_if_exists_impl(ArchiveT js_j, Type &js_t, std::false_type) { /*nothing to do, class has no load function*/ }
template<typename ArchiveT, typename Type> inline void call_load_if_exists(ArchiveT js_j, Type &js_t) { call_load_if_exists_impl(js_j, js_t, std::bool_constant<class_has_load_function_v<Type>>{}); }

template<typename Type> inline void call_unload_if_exists_impl(Type &js_t, std::true_type) { js_t.archive_unload(); }
template<typename Type> inline void call_unload_if_exists_impl(Type &js_t, std::false_type) { /* nothing to do, class has no load function */ }
template<typename Type> inline void call_unload_if_exists(Type &js_t) { call_unload_if_exists_impl(js_t, std::bool_constant<class_has_unload_function_v<Type>>{}); }

template<typename Type> inline void call_init_if_exists_impl(Type &js_t, std::true_type) { js_t.archive_init(); }
template<typename Type> inline void call_init_if_exists_impl(Type &js_t, std::false_type) { /*nothing to do, class has no load function*/ }
template<typename Type> inline void call_init_if_exists(Type &js_t) { call_init_if_exists_impl(js_t, std::bool_constant<class_has_init_function_v<Type>>{}); }

template<typename ArchiveT, typename Type> inline bool call_struct_reader_if_exists_impl(ArchiveT js_j, Type &js_t, std::true_type) { js_j.r(js_t); return true; }
template<typename ArchiveT, typename Type> inline bool call_struct_reader_if_exists_impl(ArchiveT js_j, Type &js_t, std::false_type) { return false; /*nothing to do, class has no load function*/ }
template<typename ArchiveT, typename Type> inline bool call_struct_reader_if_exists(ArchiveT js_j, Type &js_t) { return call_struct_reader_if_exists_impl(js_j, js_t, std::bool_constant<archive_helper::class_has_archive_reader_v<Type>>{}); }


#define ANK_CONFIG_STRUCT(Type, ...)                                                              \
namespace archive_helper {                                                                        \
    template<> struct class_has_archive_reader<Type> : std::true_type {};                         \
    template<>                                                                                    \
    inline void reader<Type>(archive js_j, Type& js_t) {                                          \
        call_unload_if_exists(js_t);                                                              \
        ANK_CONFIG_STRUCT_EXPAND(ANK_CONFIG_STRUCT_PASTE(ANK_CONFIG_STRUCT_FROM, __VA_ARGS__));   \
        call_load_if_exists(js_j, js_t);                                                          \
    }                                                                                             \
}

template<> inline void archive::r<int>(pcstr name, int &v) { v = r_int(name); }
template<> inline void archive::r<int8_t>(pcstr name, int8_t &v) { v = r_int(name); }
template<> inline void archive::r<uint8_t>(pcstr name, uint8_t &v) { v = r_uint(name); }
template<> inline void archive::r<uint16_t>(pcstr name, uint16_t &v) { v = r_uint(name); }
template<> inline void archive::r<uint32_t>(pcstr name, uint32_t &v) { v = r_uint(name); }
template<> inline void archive::r<bool>(pcstr name, bool &v) { v = r_bool(name); }
template<> inline void archive::r<float>(pcstr name, float &v) { v = r_float(name); }
template<> inline void archive::r<vec2i>(pcstr name, vec2i &v) { v = r_vec2i(name); }
template<> inline void archive::r<xstring>(pcstr name, xstring &v) { v = r_string(name); }
template<> inline void archive::r<tile2i>(pcstr name, tile2i &v) { v = r_tile2i(name); }
template<> inline void archive::r<image_desc>(pcstr name, image_desc &v) { r_desc(name, v); }
template<> inline void archive::r<bstring<256>>(pcstr name, bstring<256> &v) { v = r_string(name); }

template<typename T>
inline void archive::r(T &s) { archive_helper::reader(*this, s); }

template<typename T>
inline void archive::r_struct(pcstr name, T &v) {
    this->r_section(name, [&] (archive sarch) {
        archive_helper::reader(sarch, v);
    });
}

template<size_t S, typename T>
inline void archive::r_sarray(pcstr name, std::array<T, S> &v) {
    getproperty(-1, name);
    auto it = v.begin();
    if (isarray(-1)) {
        int length = getlength(-1);
        length = std::min<int>(S, length);

        for (int i = 0; i < length; ++i) {
            getindex(-1, i);
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>) {
                double v = isnumber(-1) ? tonumber(-1) : 0.0;
                *it = static_cast<T>(v);
            }
            else {
                if (isobject(-1)) {
                    archive_helper::reader(*this, *it);
                }
            }
            it = std::next(it);
            pop(1);
        }
    }
    pop(1);
}

template<typename T>
inline void archive::r_stable_array(pcstr name, T &arr) {
    getproperty(-1, name);
    if (isarray(-1)) {
        int length = getlength(-1);
        using value_type = typename T::value_type;
        constexpr bool is_arithmetic = std::is_arithmetic_v<value_type>;
        if constexpr (is_arithmetic) {
            // numbers
            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                if (isnumber(-1)) {
                    double v = isnumber(-1) ? tonumber(-1) : 0.0;
                    value_type item = value_type(v);
                    arr[std::hash<value_type>()(item)] = item;
                }
                pop(1);
            }
        } else {
            // objects
            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                if (isobject(-1)) {
                    value_type item;
                    archive_helper::reader(*this, item);
                    arr[std::hash<value_type>()(item)] = item;
                }
                pop(1);
            }
        }
    }
    pop(1);
}

template<typename T>
inline void archive::r(pcstr name, T& v) {
    if constexpr (std::is_enum_v<T>) {
        v = this->r_type<T>(name);
    } else if constexpr(std::is_arithmetic_v<T>) {
        v = this->r<T>(name);
    } else {
        this->r_struct(name, v);
    }
}

template<typename T, std::size_t N>
inline void g_archive::r(pcstr name, svector<T, N> &v) {
    getglobal(name);
    v.clear();
    if (isarray(-1)) {
        int length = getlength(-1);
        length = std::min<int>(N, length);

        for (int i = 0; i < length; ++i) {
            getindex(-1, i);
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>) {
                double item = isnumber(-1) ? tonumber(-1) : 0.0;
                v.push_back(static_cast<T>(item));
            } else {
                if (isobject(-1)) {
                    T item;
                    archive_helper::reader(archive(state), item);
                    v.push_back(item);
                }
            }
            pop(1);
        }
    }
    pop(1);
}

template<typename T, std::size_t N>
inline void g_archive::r(pcstr name, std::array<T, N> &v) {
    getglobal(name);
    auto it = v.begin();
    if (isarray(-1)) {
        int length = getlength(-1);
        length = std::min<int>(N, length);

        for (int i = 0; i < length; ++i) {
            getindex(-1, i);
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>) {
                double v = isnumber(-1) ? tonumber(-1) : 0.0;
                *it = static_cast<T>(v);
            } else {
                if (isobject(-1)) {
                    archive_helper::reader(archive(state), *it);
                }
            }
            it = std::next(it);
            pop(1);
        }
    }
    pop(1);
}

template<typename T>
inline bool g_archive::r(pcstr name, T &obj) {
    if (!state) {
        return true;
    }

    return r_section(name, [&] (archive arch) { arch.r(obj); });
}

template<typename T>
inline void g_archive::r_stable_array(pcstr name, T &arr) {
    getglobal(name);
    if (isarray(-1)) {
        int length = getlength(-1);
        using value_type = typename T::value_type;
        for (int i = 0; i < length; ++i) {
            getindex(-1, i);
            if (isobject(-1)) {
                value_type item;
                archive_helper::reader(archive(state), item);
                arr[std::hash<value_type>()(item)] = item;
            }
            pop(1);
        }
    }
    pop(1);
}