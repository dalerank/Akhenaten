#include "ui_scope_property.h"

#include "city/city.h"

const xstring scope_city("city");

bvariant ui_scope_property::get_property(const xstring &domain, const xstring &name) const {
    if (domain == scope_city) {
        return g_city.get_property(domain, name);
    }

    return {};
}