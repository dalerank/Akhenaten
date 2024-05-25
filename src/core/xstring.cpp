#include "xstring.h"

#include "log.h"
#include "crc32.h"

#include <mutex>
#include <map>

struct xstring_container {
    std::map<uint32_t, xstring_value*> data;
    std::mutex _m;

    void verify() {
        std::scoped_lock _(_m);
        logs::info("strings verify started");
        for (const auto &it: data) {
            const auto crc = crc32(it.second->value.c_str(), it.second->length);
            bstring32 crc_str;
            assert(crc == it.second->crc);// , "error: read-only memory corruption (shared_strings)"); // itoa(value->dwCRC, crc_str, 16));
            assert(it.second->length == it.second->value.length());// , "error: read-only memory corruption (shared_strings, internal structures)");// , value->value);
        }
        logs::info("strings verify completed");
    }

    void dump(FILE *f) const {
        for (const auto &it: data) {
            fprintf(f, "ref[%4u]-len[%3u]-crc[%8X] : %s\n", it.second->reference, it.second->length, it.second->crc, it.second->value.c_str());
        }
    }

    xstring_value *dock(pcstr value) {
        if (nullptr == value) {
            return nullptr;
        }

        std::scoped_lock _(_m);

        // calc len
        const size_t s_len = strlen(value);
        const size_t s_len_with_zero = s_len + 1;
        assert(sizeof(xstring_value) + s_len_with_zero < 4096);

        // setup find structure
        uint16_t length = static_cast<uint32_t>(s_len);
        uint32_t crc = crc32(value, uint32_t(s_len));

        // search
        auto it = data.find(crc);

        // it may be the case, string is not found or has "non-exact" match
        if (it == data.end()) {
            xstring_value *new_xstr = new xstring_value;
            new_xstr->reference = 0;
            new_xstr->length = length;
            new_xstr->crc = crc;
            new_xstr->value = value;

            data.insert({crc, new_xstr});
            return new_xstr;
        }

        return it->second;
    }

    void dump() {
        std::scoped_lock _(_m);
        FILE* F = fopen("c:\\$str_dump$.txt", "w");
        dump(F);
        fclose(F);
    }

    void clean() {
        for (const auto &it : data) {
            delete it.second;
        }
        data.clear();
    }

    ~xstring_container() {
        clean();
    }
};

xstring_container *g_xstring = nullptr;

xstring_value *xstring::_dock(pcstr value) {
    if (!g_xstring) { g_xstring = new xstring_container(); }
    return g_xstring->dock(value);
}