#include "Charset.hpp"
#include <stdexcept>

#include <cassert>

namespace Trex {
    Charset::Charset(uint32_t first, uint32_t last)
        : Charset(span_const<Range>({ {first,last} })) {
    }

    Charset::Charset(const std::vector<Range> &codepointRanges) {
        auto span = make_span(codepointRanges);
        fill(span);
    }

    void Charset::fill(span_const<Range> codepointRanges) {
        for (const auto &[first, last] : codepointRanges) {
            if (first > last) {
                assert(false && "Error: invalid charset range");
            }
            for (uint32_t codepoint = first; codepoint <= last; codepoint++) {
                m_Charset.insert(codepoint);
            }
        }
    }

    Charset::Charset(span_const<Range> codepointRanges) {
        fill(codepointRanges);
    }
}

