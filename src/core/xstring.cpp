#include "xstring.h"

#include "log.h"
#include "crc32.h"

#include <mutex>

struct xstring_container;
xstring_container* g_xstring = nullptr;

struct xstring_container {
    std::mutex _m;
    static constexpr size_t buffer_size = 1024u * 256u;
    xstring_value *buffer[buffer_size];
    int num_docs;

    xstring_container() {
        num_docs = 0;
        memset(buffer, 0, sizeof(buffer));
    }

    xstring_value *find(xstring_value *value, const char *str) const {
        xstring_value *candidate = buffer[value->crc % buffer_size];
        while (candidate) {
            if (candidate->crc == value->crc && candidate->length == value->length && !memcmp(candidate->value, str, value->length)) {
                return candidate;
            }

            candidate = candidate->next;
        }

        return nullptr;
    }

    void insert(xstring_value *value) {
        xstring_value **element = &buffer[value->crc % buffer_size];
        value->next = *element;
        *element = value;
    }

    void clean() {
        std::scoped_lock _(_m);
        for (size_t i = 0; i < buffer_size; ++i) {
            xstring_value **current = &buffer[i];

            while (*current != nullptr) {
                xstring_value *value = *current;
                if (!value->reference) {
                    *current = value->next;
                    free(value);
                } else {
                    current = &value->next;
                }
            }
        }
    }

    void verify() {
        std::scoped_lock _(_m);
        logs::info("strings verify started");
        for (size_t i = 0; i < buffer_size; ++i) {
            const xstring_value *value = buffer[i];
            while (value) {
                const auto crc = crc32(value->value, value->length);
                bstring32 crc_str;
                assert(crc == value->crc);// , "error: read-only memory corruption (shared_strings)"); // itoa(value->dwCRC, crc_str, 16));
                assert(value->length == strlen(value->value));// , "error: read-only memory corruption (shared_strings, internal structures)");// , value->value);
                value = value->next;
            }
        }
        logs::info("strings verify completed");
    }

    void dump(FILE *f) const {
        for (size_t i = 0; i < buffer_size; ++i) {
            xstring_value *value = buffer[i];
            while (value) {
                fprintf(f, "ref[%4u]-len[%3u]-crc[%8X] : %s\n", value->reference, value->length, value->crc, value->value);
                value = value->next;
            }
        }
    }

    xstring_value *dock(pcstr value) {
        if (nullptr == value) {
            return nullptr;
        }

        std::scoped_lock _(_m);

        xstring_value *result = nullptr;

        // calc len
        const size_t s_len = strlen(value);
        const size_t s_len_with_zero = s_len + 1;
        assert(sizeof(xstring_value) + s_len_with_zero < 4096);

        // setup find structure
        char header[sizeof(xstring_value)];
        xstring_value *sv = (xstring_value *)header;
        sv->reference = 0;
        sv->length = static_cast<uint32_t>(s_len);
        sv->crc = crc32(value, uint32_t(s_len));

        // search
        result = find(sv, value);

#ifdef DEBUG
        const bool is_leaked_string = !strcmp(value, "enter leaked string here");
#endif // DEBUG

        // it may be the case, string is not found or has "non-exact" match
        if (nullptr == result
#ifdef DEBUG
            || is_leaked_string
#endif // DEBUG
            ) {
            result = static_cast<xstring_value *>(malloc(sizeof(xstring_value) + s_len_with_zero));

#ifdef DEBUG
            static int num_leaked_string = 0;
            if (is_leaked_string) {
                ++num_leaked_string;
                logs::info("leaked_string: %d 0x%08x", num_leaked_string, result);
            }
#endif // DEBUG

            result->reference = 0;
            result->length = sv->length;
            result->crc = sv->crc;
            memcpy(result->value, value, s_len_with_zero);

            insert(result);
        }

        return result;
    }

    void dump() {
        std::scoped_lock _(_m);
        FILE* F = fopen("c:\\$str_dump$.txt", "w");
        dump(F);
        fclose(F);
    }

    ~xstring_container() {
        clean();
    }
};

xstring_value *xstring::_dock(pcstr value) {
    if (!g_xstring) { g_xstring = new xstring_container(); }
    return g_xstring->dock(value);
}