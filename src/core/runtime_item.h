#pragma once

#include "core/xstring.h"
#include "core/archive.h"

namespace config {

struct static_params {
    static_params();

    void archive_load();

    virtual void archive_unload() {}
    virtual void archive_init() {}
    virtual void archive_load(archive arch) = 0;
    virtual pcstr archive_section() const = 0;
};

} // config