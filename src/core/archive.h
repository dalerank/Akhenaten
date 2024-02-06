#pragma once

#include <cstdint>
#include "core/string.h"
#include "core/vec2i.h"

#include <vector>
#include <string>

enum e_image_id : uint16_t;

struct archive {
    void *state = nullptr;
    inline archive(void *_vm) : state(_vm) {}

    pcstr r_string(pcstr name);
    std::vector<std::string> r_array_str(pcstr name);
    int r_int(pcstr name, int def = 0);
    uint32_t r_uint(pcstr name, uint32_t def = 0);
    e_image_id r_image(pcstr name);
    bool r_bool(pcstr name, bool def = false);
    vec2i r_size2i(pcstr name, pcstr w = "w", pcstr h = "h");
    vec2i r_vec2i(pcstr name, pcstr x = "x", pcstr y = "y");

    std::vector<vec2i> r_array_vec2i(pcstr name);

    template<class T>
    inline T r_type(pcstr name) { return (T)r_int(name); }

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

    vec2i r_vec2i_impl(pcstr x, pcstr y);

    template<typename T>
    inline void r_objects(pcstr name, T read_func) {
        this->r_section(name, [this, &read_func] (archive s_arch) {
            pcstr key;
            std::vector<bstring128> keys;
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

    void getproperty(int idx, pcstr name);
    static void getproperty(archive arch, int idx, pcstr name);
    bool isarray(int idx);
    int getlength(int idx);
    void getindex(int idx, int i);
    bool isnumber(int idx);
    double tonumber(int idx);
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
        getglobal(name);
        r_array_impl(read_func);
        pop(1);
    }

    template<typename T>
    inline void r_section(pcstr name, T read_func) {
        getglobal(name);
        if (isobject(-1)) {
            read_func(state);
        }
        pop(1);
    }
};

extern g_archive g_config_arch;