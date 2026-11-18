#pragma once

#include "core/custom_span.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>

std::optional<size_t> zip_decompress(xspan<const uint8_t> input, xspan<uint8_t> output);
