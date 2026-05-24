#pragma once

#include "core/bstring.h"

#include <string>

struct http_get_result {
    bool ok = false;
    long http_code = 0;
    std::string body;
    std::string headers;
};

http_get_result http_get(pcstr url, long timeout_sec = 10, bool capture_headers = false);
