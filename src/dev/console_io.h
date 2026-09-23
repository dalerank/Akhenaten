#pragma once

#include "core/bstring.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <functional>

// Whitespace tokenizer over a console line. Commands share one instance per line:
// whatever a command leaves unread is scanned for further commands afterwards.
class console_args {
public:
    explicit console_args(pcstr line) : _cur(line ? line : "") {}

    bool empty() {
        skip_ws();
        return !*_cur;
    }

    pcstr rest() {
        skip_ws();
        return _cur;
    }

    void skip_rest() { _cur += ::strlen(_cur); }

    template<size_t N>
    bool next(bstring<N> &out) {
        pcstr begin;
        size_t len;
        if (!token(begin, len)) {
            return false;
        }
        out.clear();
        out.ncat(begin, std::min(len, N - 1));
        return true;
    }

    bool next(int &value) {
        bstring64 tok;
        if (!next(tok)) {
            return false;
        }
        char *end = nullptr;
        const long v = ::strtol(tok.c_str(), &end, 10);
        if (end == tok.c_str() || *end) {
            return false;
        }
        value = (int)v;
        return true;
    }

    bool next(float &value) {
        bstring64 tok;
        if (!next(tok)) {
            return false;
        }
        char *end = nullptr;
        const float v = ::strtof(tok.c_str(), &end);
        if (end == tok.c_str() || *end) {
            return false;
        }
        value = v;
        return true;
    }

    bool next(bool &value) {
        bstring64 tok;
        if (!next(tok)) {
            return false;
        }
        if (tok == "1" || tok == "true" || tok == "on") {
            value = true;
            return true;
        }
        if (tok == "0" || tok == "false" || tok == "off") {
            value = false;
            return true;
        }
        return false;
    }

    // atoi semantics: a missing token yields `def`, a malformed one yields 0.
    int next_int(int def = 0) {
        bstring64 tok;
        return next(tok) ? ::atoi(tok.c_str()) : def;
    }

    float next_float(float def = 0.f) {
        bstring64 tok;
        return next(tok) ? (float)::atof(tok.c_str()) : def;
    }

    bstring128 next_str() {
        bstring128 tok;
        next(tok);
        return tok;
    }

private:
    void skip_ws() {
        while (*_cur && ::isspace((unsigned char)*_cur)) {
            ++_cur;
        }
    }

    bool token(pcstr &begin, size_t &len) {
        skip_ws();
        if (!*_cur) {
            return false;
        }
        begin = _cur;
        while (*_cur && !::isspace((unsigned char)*_cur)) {
            ++_cur;
        }
        len = (size_t)(_cur - begin);
        return true;
    }

    pcstr _cur;
};

class console_output {
public:
    virtual void write(pcstr text, size_t len) = 0;

    void print(pcstr text) {
        if (text) {
            write(text, ::strlen(text));
        }
    }

    void println(pcstr text) {
        print(text);
        write("\n", 1);
    }

    template<typename... Args>
    void printf(pcstr fmt, const Args &...args) {
        bstring1024 buf;
        buf.printf(fmt, args...);
        print(buf.c_str());
    }

protected:
    ~console_output() = default;
};

using console_command_fn = std::function<void(console_args &, console_output &)>;
