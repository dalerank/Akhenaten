#pragma once

#include "io/io_buffer.h"

#include <cstdint>
#include <utility>

template <uint16_t L>
struct save_layout_tag {};

struct save_layout_entry {
    const char* name;
    uint16_t current;
    save_layout_entry* next;

    save_layout_entry(const char* name, uint16_t current);
    static save_layout_entry* first;
};

namespace save_layouts {
    void clear();
    void set(const char* name, uint16_t layout);
    int find(const char* name);

    template <class H>
    uint16_t of() {
        const int layout = find(H::name);
        return layout > 0 ? uint16_t(layout) : H::current;
    }
} // namespace save_layouts

namespace save_layout_detail {
    template <class H, uint16_t L, class D>
    void upgrade_chain(typename H::object& o, const D& d) {
        if constexpr (L + 1 == H::current) {
            H::apply(o, d);
        } else {
            upgrade_chain<H, L + 1>(o, H::upgrade(o, d));
        }
    }

    template <class H, uint16_t L>
    void read(typename H::object& o, io_buffer* iob) {
        if constexpr (L == H::current) {
            H::bind_current(o, iob);
        } else {
            upgrade_chain<H, L>(o, H::read(o, iob, save_layout_tag<L>{}));
        }
    }

    template <class H, uint16_t... I>
    void dispatch(typename H::object& o, io_buffer* iob, uint16_t layout, std::integer_sequence<uint16_t, I...>) {
        const bool done = ((layout == I + H::oldest ? (read<H, I + H::oldest>(o, iob), true) : false) || ...);
        if (!done) {
            H::bind_current(o, iob);
        }
    }
} // namespace save_layout_detail

template <class H>
void bind_versioned(typename H::object& o, io_buffer* iob) {
    if (!iob->is_read_access()) {
        H::bind_current(o, iob);
        return;
    }
    save_layout_detail::dispatch<H>(o, iob, save_layouts::of<H>(),
      std::make_integer_sequence<uint16_t, H::current - H::oldest + 1>{});
}

template <class H>
struct save_layout_registration {
    save_layout_entry entry{H::name, H::current};
};

struct save_layouts_chunk {
    static constexpr const char* name = "layouts";
    static constexpr int NAME_LEN = 30;
    static constexpr int MAX_ENTRIES = 32;
    static constexpr int SIZE = 4 + MAX_ENTRIES * (NAME_LEN + 2);
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};
