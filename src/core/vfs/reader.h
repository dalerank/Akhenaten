#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "core/core.h"
#include "core/bstring.h"

namespace vfs {

    struct reader_base {
        inline reader_base(pcstr _debug_info, const void* data, int size)
          : __data((const uint8_t*)data), __pos(0), __size(size) {
            __debug_info = _debug_info;
        }

        inline int elapsed() const { return __size - __pos; };
        inline bool eof() const { return elapsed() <= 0; };
        inline int tell() const { return __pos; };
        inline bool seek(int64_t ptr) {
            if (ptr < 0 || ptr > __size) {
                __failed = true;
                return false;
            }
            __pos = (int)ptr;
            return true;
        };
        inline bool failed() const { return __failed; }
        inline int size() const { return __size; }
        inline void* data() const { return (void*)__data; };
        inline void* current_pointer() const { return (void*)(__data + __pos); };
        inline bool advance(int64_t cnt) { return seek((int64_t)__pos + cnt); };

        inline bool r(void* p, int64_t c) {
            if (c < 0 || c > elapsed()) {
                __failed = true;
                if (c > 0) {
                    memset(p, 0, (size_t)c);
                }
                return false;
            }
            memcpy(p, current_pointer(), (size_t)c);
            __pos += (int)c;
            return true;
        }

    private:
        bstring256 __debug_info;

    public:
        pcstr debug_info() const { return __debug_info.c_str(); }

    protected:
        const uint8_t* __data;
        int __pos;
        int __size;
        bool __failed = false;
    };

    class data_reader : public reader_base {
    public:
        inline data_reader(pcstr _debug_info, void* data, int size) : reader_base(_debug_info, data, size) {}
        virtual ~data_reader() {
            free((void*)__data);
            __data = nullptr;
        };
    };

    using reader = std::shared_ptr<data_reader>;

} // namespace vfs