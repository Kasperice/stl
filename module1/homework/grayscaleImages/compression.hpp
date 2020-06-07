#pragma once

#include <stdint.h>

#include <array>
#include <vector>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, 240>, 160>& image);
std::array<std::array<uint8_t, 240>, 160> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& image);
