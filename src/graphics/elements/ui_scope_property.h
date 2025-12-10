#pragma once

#include "core/variant.h"

struct ui_scope_property {
    bvariant get_property(const xstring &domain, const xstring &name) const;
};