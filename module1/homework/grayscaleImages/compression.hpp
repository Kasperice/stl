#pragma once

#include <stdint.h>

#include <array>
#include <vector>

constexpr int height = 160;
constexpr int width = 240;

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, width>, height>& image);
std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& image);
