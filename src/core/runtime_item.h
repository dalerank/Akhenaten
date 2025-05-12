#pragma once

#include "core/xstring.h"
#include "core/archive.h"

namespace config
{

struct runtime
{
    pcstr _section;

    runtime(pcstr s);

    virtual void reset() {}
    virtual void init() {}
    virtual void load(archive arch) = 0;
};

} // config