#pragma once

#include <vector>
#include <span>
#include <cstdint>
#include "core/custom_span.hpp"

// Input to all these functions is always a 1-byte grayscale bitmap
// Which means that each pixel is represented by a single byte where
// value 0 means black and 255 means white.
//
// All conversion functions keep the grayscale value of the pixels.
// Ondly the format of the bitmap is changed.

namespace Trex {
    // Convert 1-byte: GRAY8 to 2-byte: GRAYALPHA88
    std::vector<uint8_t> ConvertBitmapToGrayAlpha(span_const<uint8_t> input);

    // Convert 1-byte: GRAY8 to 3-byte: RGB888
    std::vector<uint8_t> ConvertBitmapToRGB(span_const<uint8_t> input);

    // Convert 1-byte: GRAY8 to 4-byte: RGBA8888
    std::vector<uint8_t> ConvertBitmapToRGBA(span_const<uint8_t> input);
}

