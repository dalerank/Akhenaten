#pragma once

#include <cstdint>
#include "core/xstring.h"
#include "core/vec2i.h"
#include "core/fixed_memory_resource.h"

#include <vector>
#include <string>
#include <variant>

struct animation_t;
struct image_desc;

struct archive {
    void *state = nullptr;
    inline archive(void *_vm) : state(_vm) {}

    pcstr r_string(pcstr name);
    std::vector<std::string> r_array_str(pcstr name);
    int r_int(pcstr name, int def = 0);
    float r_float(pcstr name, float def = 0.f);
    uint32_t r_uint(pcstr name, uint32_t def = 0);
    bool r_bool(pcstr name, bool def = false);
    vec2i r_size2i(pcstr name, pcstr w = "w", pcstr h = "h");
    vec2i r_vec2i(pcstr name, pcstr x = "x", pcstr y = "y");
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

    std::vector<vec2i> r_array_vec2i(pcstr name);

    template<class T>
    inline T r_type(pcstr name, T def = (T)0) { return (T)r_int(name, def); }

    template<size_t S, typename T = int>
    inline std::array<T, S> r_sarray(pcstr name) {
        getproperty(-1, name);
        std::array<T, S> result;
        auto it = result.begin();
        if (isarray(-1)) {
            int length = getlength(-1);

            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                float v = isnumber(-1) ? (float)tonumber(-1) : 0.f;
                *it = ((T)v);
                it = std::next(it);
                pop(1);
            }
        }
        pop(1);
        return result;
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
    inline void r_array_num(pcstr name, T& arr) {
        arr.clear();
        getproperty(-1, name);
        std::vector<T> result;
        if (isarray(-1)) {
            int length = getlength(-1);

            for (int i = 0; i < length; ++i) {
                getindex(-1, i);
                float v = isnumber(-1) ? (float)tonumber(-1) : 0.f;
                arr.push_back(v);
                pop(1);
            }
        }
        pop(1);
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

    template<typename T>
    inline void r_objects(pcstr name, T read_func) {
        this->r_section(name, [this, &read_func] (archive s_arch) {
            pcstr key;

            fixed_memory_resource<bstring128, 128> keys_buffer;
            std::pmr::vector<bstring128> keys{ &keys_buffer };
            pushiterator(s_arch, -1, 1);
            while ((key = nextiterator(s_arch, -1))) {
                keys.push_back(key);
            }
            pop(s_arch, 1);

            for (const auto &key : keys) {
                getproperty(s_arch, -1, key.c_str());
                if (isobject(s_arch, -1)) {
                    read_func(key.c_str(), s_arch);
                }
                pop(s_arch, 1);
            }
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
        for (int i = 0; i < length; ++i) {
            getindex(-1, i);

            if (isobject(-1)) {
                arr.push_back({});
                read_func(state, arr.back());
            }

            pop(1);
        }
        return true;
    }

    void getproperty(int idx, pcstr name);
    static void getproperty(archive arch, int idx, pcstr name);
    bool isarray(int idx);
    int getlength(int idx);
    void getindex(int idx, int i);
    bool isnumber(int idx);
    bool isstring(int idx);
    double tonumber(int idx);
    pcstr tostring(int idx);
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

    template<typename T>
    inline void r_section(pcstr name, T read_func) {
        if (!state) {
            return;
        }

        getglobal(name);
        if (isobject(-1)) {
            read_func(state);
        }
        pop(1);
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
                if (isobject(state, -1)) {
                    read_func(key.c_str(), state);
                }
                pop(state, 1);
            }
        }
        pop(1);
    }
};

extern g_archive g_config_arch;