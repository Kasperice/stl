#include "compression.hpp"

#include <algorithm>
#include <utility>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, 240>, 160>& image) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed{};

    for (const auto& row : image) {
        for (auto it = row.begin(); it != row.end();) {
            auto findIt = std::adjacent_find(it, row.end(), std::not_equal_to<int>{});
            if (findIt != row.end()) {
                findIt++;
            }
            compressed.emplace_back(*it, std::distance(it, findIt));
            it = findIt;
        }
    }

    return compressed;
}

std::array<std::array<uint8_t, 240>, 160> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& image) {
    std::array<std::array<uint8_t, 240>, 160> decompressed{};

    return decompressed;
}
