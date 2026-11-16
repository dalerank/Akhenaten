#include "content/path.h"

#include "core/log.h"
#include "core/string.h"

namespace vfs {

bool file_has_extension(pcstr filename, pcstr extension) {
    if (!filename || !*filename) {
        return false;
    }

    if (!extension || !*extension) {
        return true;
    }

    pcstr last_c = filename + ::strlen(filename) - 1;
    while (last_c != filename && *last_c != '.') {
        last_c--;
    }

    if (last_c != filename) {
        last_c++;
    }

    return string_compare_case_insensitive(last_c, extension) == 0;
}

void path::report_truncation(pcstr truncated) {
    logs::error("vfs::path: path reached the %d character limit and is probably truncated: %s", (int)capacity - 2,
      truncated);
}

} // namespace vfs
