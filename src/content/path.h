#pragma once

#include "core/xstring.h"

namespace vfs {

/**
* Checks whether the file has the given extension
* @param filename Filename to check
* @param extension Extension
* @return boolean true if the file has the given extension, false otherwise
*/
bool file_has_extension(pcstr filename, pcstr extension);

struct path : public bstring256 {
    void unify() {
        bstring256 tmp = *this;
        clear();
        tmp.replace('\\', '/'); // Replace backslashes with slashes
        pcstr c = tmp.data();
        pstr mptr = data();
        if (c) {
            *mptr = *c;
            ++c;
        }

        for (; *c != 0; ++c) {
            if (*c == '/' && *mptr == '/') {
                const bool keep_uri_separator = (mptr > data() && *(mptr - 1) == ':');
                if (!keep_uri_separator) {
                    continue;
                }
            }

            ++mptr;
            *mptr = *c;
        }

        size_t size = mptr - _data;
        int remain = capacity - size;
        *(mptr + ((remain > 0) ? 1 : 0)) = 0;
        replace('\\', '/'); // Replace backslashes with slashes
    }

    template <typename... Args>
    path(Args&&... args) : bstring256(std::forward<Args>(args)...) {
        unify();
    }

    path& operator=(pcstr str) {
        clear();
        append(str);
        unify();
        return *this;
    }

    path& operator=(const std::string& str) {
        clear();
        append(str.c_str());
        unify();
        return *this;
    }

    path& operator=(xstring str) {
        clear();
        append(str.c_str());
        unify();
        return *this;
    }

    bool is_extension(pcstr extension) { return file_has_extension(c_str(), extension); }

    void remove_extension() {
        pstr ptr_point = ::strchr(_data, '.');
        if (ptr_point) {
            *ptr_point = 0;
        }
    }

    /**
     * Get the case sensitive and localized filename of the file
     * @param filepath File path to match to a case-sensitive file on the filesystem
     * @param localizable Whether the file may, must or must not be localized
     * @return Corrected file, or base path as fallback if the file was not found
     */
    vfs::path resolve();
    static vfs::path resolve(pcstr p) {
        vfs::path r(p);
        return r.resolve();
    }
};

}