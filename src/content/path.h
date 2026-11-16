#pragma once

#include "core/xstring.h"

#include <string_view>

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
        if (len() >= capacity - 2) {
            report_truncation(c_str());
        }
    }

    // bstring formatting cuts at capacity - 2 characters without telling anyone.
    static void report_truncation(pcstr truncated);

    template <typename... Args>
    path(Args&&... args) : bstring256(fmt_arg(args)...) {
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
        pstr last_dot = nullptr;
        for (pstr p = _data; *p; ++p) {
            if (*p == '.') {
                last_dot = p;
            }
        }
        if (last_dot) {
            *last_dot = 0;
        }
    }

    void append_extension(std::string_view extension) {
        if (empty() || extension.empty()) {
            return;
        }

        const size_t cur_len = len();
        if (cur_len + 1 + extension.size() >= capacity) {
            return;
        }

        pstr end = _data + cur_len;
        *end++ = '.';
        for (char c : extension) {
            *end++ = c;
        }
        *end = 0;
    }

    void change_extension(std::string_view new_extension) {
        if (empty() || new_extension.empty()) {
            return;
        }

        pstr last_dot = nullptr;
        for (pstr p = _data; *p; ++p) {
            if (*p == '.') {
                last_dot = p;
            }
        }
        if (!last_dot) {
            return;
        }

        const size_t prefix_len = static_cast<size_t>(last_dot - _data) + 1;
        if (prefix_len + new_extension.size() >= capacity) {
            return;
        }

        pstr w = last_dot + 1;
        for (char c : new_extension) {
            *w++ = c;
        }
        *w = 0;
    }

    path basename() const {
        pcstr slash = _data;
        for (pcstr p = _data; *p; ++p) {
            if (*p == '/' || *p == '\\') {
                slash = p + 1;
            }
        }
        return path(slash);
    }

    bool contains(pcstr sub) const { return strstr(sub) != nullptr; }

    path split(pcstr delim) const {
        if (!delim || !*delim) {
            return {};
        }
        pcstr pos = strstr(delim);
        if (!pos) {
            return {};
        }
        return path(pos + ::strlen(delim));
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